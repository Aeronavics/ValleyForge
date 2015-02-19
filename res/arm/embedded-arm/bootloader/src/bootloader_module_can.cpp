// Copyright (C) 2013  Unison Networks Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/********************************************************************************************************************************
 *
 *  FILE: 		bootloader_module_can.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	30-11-2012
 *
 *	Provides a bootloader module which only supports CAN programming.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#warning #include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"
#include "bootloader_module_can.hpp"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.
#include "stm32f4xx/stm32f4xx.h"

// Include can message ids.
#include "can_messages.h"

// DEFINE PRIVATE MACROS.

// Bootloader Information.

#define BOOTLOADER_START_ADDRESS	0x00000000

// CAN baud rate values.
#warning #define CAN_BAUD_RATE	<<<TC_INSERTS_CAN_BAUD_RATE_HERE>>>
#warning #define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>
#define CAN_BAUD_RATE	250
#define CLK_SPEED_IN_MHZ	168
#define APB1_PRESCALER	4

#if (CLK_SPEED_IN_MHZ / APB1_PRESCALER == 42)
	#if (CAN_BAUD_RATE == 1000)
		#define CAN_BAUD_RATE_PRESCALER			2
		#define CAN_BAUD_RATE_TIME_SEGMENT_1	14
		#define CAN_BAUD_RATE_TIME_SEGMENT_2	6
	#elif (CAN_BAUD_RATE == 500)
		#define CAN_BAUD_RATE_PRESCALER			4
		#define CAN_BAUD_RATE_TIME_SEGMENT_1	14
		#define CAN_BAUD_RATE_TIME_SEGMENT_2	6
	#elif (CAN_BAUD_RATE == 250)
		#define CAN_BAUD_RATE_PRESCALER			8
		#define CAN_BAUD_RATE_TIME_SEGMENT_1	14
		#define CAN_BAUD_RATE_TIME_SEGMENT_2	6
	#elif (CAN_BAUD_RATE == 200)
		#define CAN_BAUD_RATE_PRESCALER			10
		#define CAN_BAUD_RATE_TIME_SEGMENT_1	14
		#define CAN_BAUD_RATE_TIME_SEGMENT_2	6
	#elif (CAN_BAUD_RATE == 125)
		#define CAN_BAUD_RATE_PRESCALER			16
		#define CAN_BAUD_RATE_TIME_SEGMENT_1	14
		#define CAN_BAUD_RATE_TIME_SEGMENT_2	6
	#elif (CAN_BAUD_RATE == 100)
		#define CAN_BAUD_RATE_PRESCALER			20
		#define CAN_BAUD_RATE_TIME_SEGMENT_1	14
		#define CAN_BAUD_RATE_TIME_SEGMENT_2	6
 	#else
 		#error "Invalid CAN baud rate."
	#endif
#else
	#error "CAN bootloader module does not have a CAN baud rate configuration for this CPU clock rate."
#endif

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// Time in units of MODULE_EVENT_PERIOD (in ms) between sending out ALERT_UPLOADER messages while the bootloader is waiting for communications to begin.
const uint16_t ALERT_UPLOADER_TIMEOUT = 50;

// Time in units of MODULE_EVENT_PERIOD (in ms) between the last message arriving, and the bootloader giving up and assuming it has lost comms.
const uint16_t COMMS_TIMEOUT = 1000;

#warning const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;
const uint8_t NODE_ID = 120;

// State flags.
bool communication_started;
bool communication_recent;
bool ready_to_send_page;
bool message_confirmation_success; 
bool write_details_stored;

// Flag indicating an error has occurred.  Currently, once an error occurs, there is no way to clear it other than a reset.
bool error;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
 *	Initializes the CAN peripheral for the selected CAN communication.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void init_can(void);

/**
 *	Sends a message on the CAN network.
 *
 *	NOTE - Message details are defined in the tranmit_message object.
 *
 *	TAKES:		transmission_message		object containing the message identifier, DLC and data to send.
 *
 *	RETURNS:	Nothing.
 */
void transmit_CAN_message(bootloader_module_can::Message_info& transmit_message);

/**
 *	Resets the CAN peripheral to default settings.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void reset_can(void);

/**
 *	Sends a confirmation message to the uploader.
 * 
 *	NOTE - The message contains one byte informing the uploader whether the message received 
 *			was valid(1) or invalid(0).
 *
 *	TAKES:		confirmation_successful		the validity of the previously received message
 *
 *	RETURNS:	Nothing.
 */
void confirm_reception(bool confirmation_successful);

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_can::~bootloader_module_can()
{
	// All done.
	return;
}

void bootloader_module_can::init(void)
{
	// Initialize the CAN controller.
	init_can();

	// All done.
	return;
}

void bootloader_module_can::exit(void)
{
	// Reset the CAN controller so that the application code finds it untouched.
	reset_can();

	// All done.
	return;
}

void bootloader_module_can::event_idle()
{
	// Send the buffer once the flash page has been copied to it.
	if (!buffer.ready_to_read && ready_to_send_page)
	{
		ready_to_send_page = false;
		send_flash_page(buffer);
	}

	// Check if we've received a new message.
	if (reception_message.message_received)
	{
		// Handle the incoming message.
		filter_message(buffer);
	}

	// All done.
	return;
}

void bootloader_module_can::event_periodic()
{
	// Number of ticks since an alert uploader message was last issued.
	static uint16_t alert_ticks = 0;

	// Check if we've started communications yet.
	if (!communication_started)
	{
		// We haven't started communication yet, so we post a message every so often to alert the uploader that we're ready.

		// Increment the number of ticks since we last posted an alert.
		alert_ticks++;

		// Check if we're due to post another message.
		if (alert_ticks >= ALERT_UPLOADER_TIMEOUT)
		{
			// Send the ALERT_UPLOADER message.
			alert_uploader();

			// Reset the number of alert ticks since the last message.
			alert_ticks = 0;
		}
	}
	else
	{
		// Reset the alert ticks.
		alert_ticks = 0;
	}

	// Number of ticks since a message was last received.
	static uint16_t comms_ticks = 0;

	if (communication_started && !communication_recent)
	{
		// Increment the number of ticks since we've last heard from the uploader.
		comms_ticks++;

		// Check if it seems like the comms have died.
		if (comms_ticks >= COMMS_TIMEOUT)
		{
			// Reset the comms timeout.
			comms_ticks = 0;
		}
	}
	else
	{
		// Clear the comms timeout.
		comms_ticks = 0;

		// We're back to square one again.
		communication_started = false;

		// Change the status of the bootloader.
		if (!error)
		{
			set_bootloader_state(BOOT_IDLE);
		}
	}

	// Communications have no longer been received 'recently'.
	communication_recent = false;

	// All done.
	return;
}

void get_bootloader_module_information(Shared_bootloader_module_constants* bootloader_module_information)
{
	bootloader_module_information->node_id = NODE_ID;
	bootloader_module_information->baud_rate = CAN_BAUD_RATE;

	// All done.
	return;
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void confirm_reception(bool confirmation_successful)
{
	module.transmission_message.dlc = 1;

	// Reply to the uploader whether the received message was successful or not.
	if (confirmation_successful)
	{
		module.transmission_message.message[0] = 1;
	}
	else
	{
		module.transmission_message.message[0] = 0;
	}

	// Confirmation message will have the same ID as the message it is confirming.
	module.transmission_message.message_type = module.reception_message.message_type;

	transmit_CAN_message(module.transmission_message);

	// All done.
	return;
}

void init_can(void)
{
	// Tx->PB9, Rx->PB8
	RCC->APB1ENR		|= RCC_APB1ENR_CAN1EN;  // Enable the clock for CAN1.
	RCC->AHB1ENR		|= RCC_AHB1ENR_GPIOBEN; // Enable the clock for PORTB.

	// CONFIGURE GPIO
	// Configure the pins as their alternate functions.
	GPIOB->MODER		|= GPIO_MODER_MODER8_1;
	GPIOB->MODER		|= GPIO_MODER_MODER9_1;
	// Configure output type to be push-pull
	GPIOB->OTYPER		&= ~(GPIO_OTYPER_OT_8);
	GPIOB->OTYPER		&= ~(GPIO_OTYPER_OT_9);
	// Configure the output speed to 50MHz.
	GPIOB->OSPEEDR		|= GPIO_OSPEEDER_OSPEEDR8_1;
	GPIOB->OSPEEDR		|= GPIO_OSPEEDER_OSPEEDR9_1;
	// Enable the pullup resistor.
	GPIOB->PUPDR		|= GPIO_PUPDR_PUPDR8_0;
	GPIOB->PUPDR		|= GPIO_PUPDR_PUPDR9_0;
	// Select the CAN alternate function.
	GPIOB->AFR[1]		|= (0x9 << 0);
	GPIOB->AFR[1]		|= (0x9 << 4);

	// CONFIGURE CAN
	// Exit from sleep mode.
	CAN1->MCR			&= ~(CAN_MCR_SLEEP);
	// Begin CAN initialisation.
	CAN1->MCR 			= (CAN_MCR_INRQ | CAN_MCR_NART);  // Init mode, disable automatic transmission.
	// CAN1->IER			= (CAN_IER_FMPIE0 | CAN_IER_TMEIE);  // Enable FIFO message pending and transmit mailbox empty interrupts.
	// Configure the baud rate.
	CAN1->BTR 			&= ~(CAN_BTR_BRP | CAN_BTR_TS1 | CAN_BTR_TS2 | CAN_BTR_SJW);
	CAN1->BTR			|= (((CAN_BAUD_RATE_PRESCALER - 1) << 0) | ((CAN_BAUD_RATE_TIME_SEGMENT_1 - 1) << 16) | ((CAN_BAUD_RATE_TIME_SEGMENT_2 - 1) << 20) | (0x3 << 24));
	// Enable LoopBack Mode
	#warning "Loopback mode enabled. CAN Rx disabled."
	CAN1->BTR 			|= CAN_BTR_LBKM;
	// Leave Init Mode
	CAN1->MCR			&= ~(CAN_MCR_INRQ);

	// CONFIGURE CAN FILTER
	// Enter filter initialisation mode.
	CAN1->FMR			|= CAN_FMR_FINIT;
	// Disable CAN filter for modification.
	CAN1->FA1R			&= ~(CAN_FA1R_FACT0);
	// Set filter scale to single 32-bit operation.
	CAN1->FS1R			|= CAN_FS1R_FSC0;
	// Fill the identifier and mask registers.
	CAN1->sFilterRegister[0].FR1	= CANID_BASE_ID;
	CAN1->sFilterRegister[0].FR2	= 0xFFFE;
	// Select Filter Mode
	CAN1->FM1R			&= ~(CAN_FM1R_FBM0);
	// Activate the filter.
	CAN1->FA1R			|= CAN_FA1R_FACT0;
	// Leave filter initialisation mode.
	CAN1->FMR			&= ~(CAN_FMR_FINIT);

	// All done.
	return;
}

void transmit_CAN_message(bootloader_module_can::Message_info& transmit_message)
{
	while ((CAN1->TSR & CAN_TSR_TME0) != CAN_TSR_TME0)
	{
		// Wait for the mailbox to be free.
		continue;
	}

	// Set the Message ID.
	// Use a Standard (11-bit) Message ID.
	CAN1->sTxMailBox[0].TIR |= (transmit_message.message_type << 21);
	// Set the message type as Data (as opposed to Remote).
	CAN1->sTxMailBox[0].TIR &= ~(0x02);
	// Set the DLC.
	CAN1->sTxMailBox[0].TDTR |= transmit_message.dlc;
	// Set the data values.
	CAN1->sTxMailBox[0].TDLR = (((uint32_t)transmit_message.message[3] << 24) | 
									((uint32_t)transmit_message.message[2] << 16) |
									((uint32_t)transmit_message.message[1] << 8) | 
									((uint32_t)transmit_message.message[0]));
    CAN1->sTxMailBox[0].TDHR = (((uint32_t)transmit_message.message[7] << 24) | 
									((uint32_t)transmit_message.message[6] << 16) |
									((uint32_t)transmit_message.message[5] << 8) |
									((uint32_t)transmit_message.message[4]));

    // Transmit data.
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

    // Wait until the transmission is complete.
    while (CAN1->TSR & CAN_TSR_RQCP0 == CAN_TSR_RQCP0) {
    	// Do nothing.
    	continue;
    }

    // If the transmission failed, set the error state.
    if ((CAN1->TSR & CAN_TSR_TERR0 == CAN_TSR_TERR0) && (CAN1->TSR & CAN_TSR_TXOK0 != CAN_TSR_TXOK0))
    {
    	// Change the bootloader status to indicate an error.
    	set_bootloader_state(BOOT_ERROR);

    	// Set our own error flag.
    	error = true;
    }

    // All done.
    return;
}

void reset_can(void)
{
	// Reset the CAN controller to it's state after a hardware reset.
	RCC->APB1RSTR |= (RCC_APB1RSTR_CAN1RST | RCC_APB1RSTR_CAN2RST);

	// All done.
	return;
}

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

void bootloader_module_can::request_reset_procedure()
{
	confirm_reception(message_confirmation_success);  // Always successful.

	if (reception_message.message[0] == 0)
	{
		reboot_to_bootloader();

		// We will never reach here.
	}
	else
	{
		reboot_to_application();

		// We will never reach here.
	}

	// We will never reach here.
	return;
}

void bootloader_module_can::get_info_procedure(void)
{
	transmission_message.dlc = 6;
	transmission_message.message_type = CANID_GET_INFO;

	// Insert Device Signature.
	uint8_t device_signature[4];
	get_device_signature(device_signature);

	transmission_message.message[0] = device_signature[0];
	transmission_message.message[1] = device_signature[1];
	transmission_message.message[2] = device_signature[2];
	transmission_message.message[3] = device_signature[3];

	// Insert bootloader version.
	uint16_t bootloader_version = get_bootloader_version();

	transmission_message.message[4] = static_cast<uint8_t>(bootloader_version >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(bootloader_version);

	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

void bootloader_module_can::write_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32-bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
									((static_cast<uint32_t>(reception_message.message[1])) << 16) |
									((static_cast<uint32_t>(reception_message.message[2])) << 8) |
									(static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16-bit code length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
										(static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in the message details.
	if ((current_firmware_page.code_length > SPM_PAGESIZE))
	{
		// Message failure.
		message_confirmation_success = false;
		write_details_stored = false;
	}
	else
	{
		// Message success.
		write_details_stored = true;
		current_firmware_page.current_byte = 0;
	}

	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::write_data_procedure(Firmware_page& current_firmware_page)
{
	if (write_details_stored)
	{
		// Check for possible array overflow.
		if ((current_firmware_page.current_byte + reception_message.dlc) > current_firmware_page.code_length)
		{
			reception_message.dlc = current_firmware_page.code_length - current_firmware_page.current_byte;
		}

		// Store data from received message (message data of 7 bytes) into the buffer (byte by byte).
		for (uint8_t i = 0; i < reception_message.dlc; i++)
		{
			current_firmware_page.data[current_firmware_page.current_byte + i] = reception_message.message[i];
		}

		// Increment the current byte in the buffer.
		current_firmware_page.current_byte += reception_message.dlc;

		// Check if the buffer is ready to be written to the flash.
		if (current_firmware_page.current_byte >= (current_firmware_page.code_length))
		{
			current_firmware_page.ready_to_write = true;
			current_firmware_page.current_byte = 0;
			write_details_stored = false;
		}
		else
		{
			// Message failure.
			message_confirmation_success = false;
		}

		confirm_reception(message_confirmation_success);

		// All done.
		return;
	}
}

void bootloader_module_can::read_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32-bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
								 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
								 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
								 (static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
										(static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details.
	if ((current_firmware_page.code_length > SPM_PAGESIZE))
	{
		// Message failure.
		message_confirmation_success = false;
	}
	else
	{
		// Message success.
		current_firmware_page.ready_to_read = true;
		ready_to_send_page = true; // Allow sending the flash page once it is read.
	}
	
	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::send_flash_page(Firmware_page& current_firmware_page)
{
	transmission_message.message_type = CANID_READ_DATA;
	current_firmware_page.current_byte = 0;
	reception_message.confirmed_send = false;

	// Send the flash page in 8-byte messages. Confirmation message must be received from the uploader after each message.
	while (current_firmware_page.current_byte < current_firmware_page.code_length)
	{
		// Determine the length of the message, just in case we are closer than 8 bytes and need to send a smaller message.
		transmission_message.dlc = (current_firmware_page.code_length - current_firmware_page.current_byte);
		if (transmission_message.dlc > 8)
		{
			transmission_message.dlc = 8;
		}

		// Create message.
		for (uint8_t i = 0; i < transmission_message.dlc; i++)
		{
			transmission_message.message[i] = current_firmware_page.data[current_firmware_page.current_byte + i];
		}

		// Increment current_byte for the next iteration.
		current_firmware_page.current_byte += transmission_message.dlc;

		transmit_CAN_message(transmission_message);

		// Wait for confirmation or command message to return from the uploader.
		while (!reception_message.confirmed_send && !reception_message.message_received)
		{
			// Do nothing.
		}

		// Exit the sending of the flash page if an uploader command message is received.
		// Allows the uploader to stop the rading if it sees a message is lost.
		if (reception_message.message_received)
		{
			// Abort sending the flash page.
			break;
		}

		reception_message.confirmed_send = false;
	}

	// All done.
	return;
}

void bootloader_module_can::filter_message(Firmware_page& current_firmware_page)
{
	// NOTE - Testing the NODE_ID shouldn't actually be required, because the ISR should have filtered other messages out.

	// NOTE - We test the NODE_ID first, then the actual message type, solely because it makes the code a little tidier.

	// If this message is intended for this node, then data[0] should match our own NODE_ID.
	if (reception_message.dlc < 1)
	{
		// This can't possibly be a message for us, because it doesn't have any data, and all our messages should.
		reception_message.message_received = false;
		return;
	}
	else
	{
		// This might be a message for us; check if the NODE_ID matches.
		if (reception_message.message[0] != NODE_ID)
		{
			// This isn't a message for us, because the ID doesn't match.
			reception_message.message_received = false;
			return;
		}
	}
	// Else, it might be a message for us, depending on what the actual message ID is.

	// NOTE - If a message is intended for us, we BREAK, but if its not one of ours, we RETURN.

	// Determine the corresponding behavior for the received message.
	switch (reception_message.message_type)
	{
		case CANID_REQUEST_RESET:
			request_reset_procedure();
			break;

		case CANID_GET_INFO:
			get_info_procedure();
			break;
			
		case CANID_WRITE_MEMORY:
			write_memory_procedure(current_firmware_page);
			break;

		case CANID_WRITE_DATA:
			write_data_procedure(current_firmware_page);
			break;

		case CANID_READ_MEMORY:
			read_memory_procedure(current_firmware_page);
			break;

		default:
			// This message isn't for us, because it's not an ID which we recognise.
			reception_message.message_received = false;
			return;
	}
	
	// Now that we've handled the message, don't need to worry about it again.
	reception_message.message_received = false;

	// We've now started communications.
	communication_started = true;
	communication_recent = true;

	// Change the status of the bootloader.
	if (!error)
	{
		set_bootloader_state(BOOT_COMMUNICATING);
	}

	// Restart the bootloader timeout, so we don't reboot halfway through a transfer.
	set_bootloader_timeout(false);
	set_bootloader_timeout(true);
	
	// All done.
	return;
}

void bootloader_module_can::alert_uploader(void)
{
	// Assemble the message to send.
	transmission_message.message_type = CANID_HOST_ALERT;
	transmission_message.dlc = 1;
	transmission_message.message[0] = NODE_ID;

	// Actually send the message.
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

/**
 * ISR for interupts from CAN controller.
 * This routine only operates on received messages, it reads the ID, DLC and data from the CAN controller into a Message_info object.
 * The ISR also sets a flag to tell Bootloader that a new message has been received, or that a confirmation message has been received.
 */
extern "C" void CAN1_RX0_IRQHandler(void)
{
	// Store the message ID.
	module.reception_message.message_type = (uint16_t)((uint32_t)0x000007FF & (CAN1->sFIFOMailBox[0].RIR >> 21));

	// A confirmation message received.
	if (module.reception_message.message_type == CANID_READ_DATA)
	{
		module.reception_message.confirmed_send = true;
	}
	// An uploader command message received.
	else
	{
		// Store the DLC.
		module.reception_message.dlc = (uint16_t)((uint8_t)0x0F & CAN1->sFIFOMailBox[0].RDTR);
		if (module.reception_message.dlc > 7)  // We use 7 here since we count from zero, not from one.
		{
			module.reception_message.dlc = 7;  // This check is required as CAN controller may give a value greater than 8.
		}

		// Store the message.
		module.reception_message.message[0] = (uint8_t)0xFF & CAN1->sFIFOMailBox[0].RDLR;
		module.reception_message.message[1] = (uint8_t)0xFF & (CAN1->sFIFOMailBox[0].RDLR >> 8);
		module.reception_message.message[2] = (uint8_t)0xFF & (CAN1->sFIFOMailBox[0].RDLR >> 16);
		module.reception_message.message[3] = (uint8_t)0xFF & (CAN1->sFIFOMailBox[0].RDLR >> 24);
		module.reception_message.message[4] = (uint8_t)0xFF & CAN1->sFIFOMailBox[0].RDHR;
		module.reception_message.message[5] = (uint8_t)0xFF & (CAN1->sFIFOMailBox[0].RDHR >> 8);
		module.reception_message.message[6] = (uint8_t)0xFF & (CAN1->sFIFOMailBox[0].RDHR >> 16);
		module.reception_message.message[7] = (uint8_t)0xFF & (CAN1->sFIFOMailBox[0].RDHR >> 24);

		// Tell the bootloader that the message was received.
		module.reception_message.message_received = true;

		// Default the message confirmation to successful
		message_confirmation_success = true;
	}

	// Release the FIFO so the next message can be seen.
	CAN1->RF0R |= CAN_RF0R_RFOM0;

	// All done.
	return;
}
	
// ALL DONE.
