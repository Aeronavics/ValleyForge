// Copyright (C) 2011  Unison Networks Ltd
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

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <avr/interrupt.h>

// Include can message ids
#include "../../../res/common/can_messages.hpp"

// DEFINE CONSTANTS

	// Bootloader information
#define BOOTLOADER_START_ADDRESS	<<<TC_INSERTS_BOOTLOADER_START_ADDRESS_HERE>>>
const uint8_t ALERT_UPLOADER_PERIOD = 10;// x10 the event_periodic() period. Period to send each alert_host message before communication has begun
const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;

	// CAN peripheral infromation
#if defined (__AVR_AT90CAN128__)
	#define NUMBER_OF_MOB_PAGES 15
#else
	#define NUMBER_OF_MOB_PAGES 6
#endif

	// CAN Baud rate values.
#define CAN_BAUD_RATE	<<<TC_INSERTS_CAN_BAUD_RATES_HERE>>>
#define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>

#if (CLK_SPEED_IN_MHZ == 16)
	#if (CAN_BAUD_RATE == 1000)
		#define CAN_BAUD_RATE_CONFIG_1	0x02
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 500)
		#define CAN_BAUD_RATE_CONFIG_1	0x06
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 250)
		#define CAN_BAUD_RATE_CONFIG_1	0x0E
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 200)
		#define CAN_BAUD_RATE_CONFIG_1	0x12
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 125)
		#define CAN_BAUD_RATE_CONFIG_1	0x1E
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 100)
		#define CAN_BAUD_RATE_CONFIG_1	0x26
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#endif
#elif (CLK_SPEED_IN_MHZ == 8)
	#if (CAN_BAUD_RATE == 1000)
		#define CAN_BAUD_RATE_CONFIG_1	0x00
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x12
	#elif (CAN_BAUD_RATE == 500)
		#define CAN_BAUD_RATE_CONFIG_1	0x02
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 250)
		#define CAN_BAUD_RATE_CONFIG_1	0x06
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 200)
		#define CAN_BAUD_RATE_CONFIG_1	0x08
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 125)
		#define CAN_BAUD_RATE_CONFIG_1	0x0E
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 100)
		#define CAN_BAUD_RATE_CONFIG_1	0x12
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#endif
#endif

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

	// State flags
bool communication_started;
bool ready_to_send_page;
bool message_confirmation_success; 
bool write_details_stored;

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
void transmit_can_message(bootloader_module_can::Message_info& transmit_message);

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
 * 			was valid(1) or invalid(0).
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
	// Initialize flags
	communication_started = false;
	ready_to_send_page = false;
	write_details_stored = false;
	reception_message.message_received = false;
	
	// Initialize the CAN controller.
	init_can();
	
	// All done.
	return;
}

void bootloader_module_can::exit(void)
{
	// Reset the CAN controller to its original state.
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
	
	// All done.
	return;
}


void bootloader_module_can::event_periodic()
{
	static uint8_t alert_count = 0; 
	 
	// Check for a new message.
	if (!reception_message.message_received)
	{
		// Check if communication with host has already occured.
		if (!communication_started)
		{
			alert_count++;
			if (alert_count == ALERT_UPLOADER_PERIOD)
			{
				// Send message to uploader to inform that the bootloader is awaiting messages.
				alert_uploader();
				alert_count = 0;
			}
		}
	}
	else
	{
		// If we are filtering a message then communication with the uploader must have occured
		communication_started = true;
		
		// Filter messages.	
		filter_message(buffer);

		// Restart the bootloader timeout.
		set_bootloader_timeout(false);
		set_bootloader_timeout(true);
	}

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
	// Avoids name mangling for the shared jumptable
extern "C" void get_bootloader_module_information_BL(Shared_bootloader_module_constants* arg){
	get_bootloader_module_information(arg);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void confirm_reception(bool confirmation_successful)
{
	module.transmission_message.dlc = 1;
	
	//Reply to the uploader whether the received message was successful or not
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
	
	transmit_can_message(module.transmission_message);

	// All done.
	return;
}

void init_can(void)
{
	uint8_t mob_number = 0;

	// Reset the CAN controller.
	CANGCON = (1 << SWRES);
	
	// Reset all of the MObs as they have no default value.
	for (mob_number = 0; mob_number < NUMBER_OF_MOB_PAGES; mob_number++)
	{
		// Select CAN page.
		CANPAGE = (mob_number << 4);
		CANSTMOB = 0x00; // Clear all flags.
		CANCDMOB = 0x00; // Disables MObs.
	}
	
	// Set up bit-timing and CAN timing.
	CANBT1 = CAN_BAUD_RATE_CONFIG_1;
	CANBT2 = CAN_BAUD_RATE_CONFIG_2;
	CANBT3 = CAN_BAUD_RATE_CONFIG_3;

	// Id's for reception.
	uint16_t id = BASE_ID;

	// Choose the MObs to set up.
	//
	// MOB NUMBER 0 - Reception MOb.
	mob_number = 0;
	CANPAGE = (mob_number << 4);
	
	CANIDT1 = id >> 3;; // Set MOb ID
	CANIDT2 = id << 5;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	
	CANIDM1 = 0xFE; // Set MOb masking ID
	CANIDM2 = 0x00; // At the moment are filtering first two hex numbers e.g id=0x123, filter = 0x12z - where z can be any number
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	
	CANCDMOB = ((1 << CONMOB1) | 8); // Enable the MOb for the mode. In this case for reception of 8 data bytes, 
	                                 //in standard format(11 bit identifier) with no automatic reply.

	// MOB NUMBER 1 - Transmission MOb.
	mob_number = 1;
	CANPAGE = (mob_number << 4);
	
	CANIDT1 = 0x00; // Set MOb ID
	CANIDT2 = 0x00; // Will be set by user.
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;

	CANIDM1 = 0x00; // Set MOb masking ID
	CANIDM2 = 0x00; // All to zero for transmit.
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	
	// Enable the interupts for the MObs enabled.
	CANIE1 = 0x00;
	CANIE2 = (1 << IEMOB0); // Enable interupts on MOb0 (interupt occurs on reception of message).

	// Enable general interupts
	CANGIE = ((1 << ENIT) | (1 << ENRX)); // Enable receive interupt through CAN_IT.

	// Enable can communication.
	CANGCON = (1 << ENASTB); // Sets the AVR pins to Tx and Rx.

	// All done.
	return;
}

void transmit_can_message(bootloader_module_can::Message_info& transmit_message)
{
	// Select tranmitting MOB
	uint8_t mob_number = 1;
	CANPAGE = (mob_number << 4); // MOb1.
	
	// Wait until MOb1 is ready to use.
	while (CANEN2 & (1 << ENMOB1))
	{
		// Do nothing.
	}
	
	// Clear interupt flags.
	CANSTMOB = 0x00;
	
	// Set message id.
	CANIDT4 = 0x00;
	CANIDT3 = 0x00;
	CANIDT2 = (transmit_message.message_type << 5);
	CANIDT1 = (transmit_message.message_type >> 3);
	
	// Set message.
	for (uint8_t i = 0; i < transmit_message.dlc; i++)
	{
		CANMSG = transmit_message.message[i];
	}
	
	// Enable tranmission with desired message length.
	CANCDMOB = ((1 << CONMOB0) | (transmit_message.dlc));
	
	// Wait until the message has sent or error occured
	while (((CANSTMOB & (1 << TXOK)) == 0) && ((CANSTMOB & (1 << AERR)) == 0))
	{
		// Do nothing.
	}	

	// Disable transmit
	CANCDMOB = 0x00;
	
	// Clear interupt flags
	CANSTMOB = 0x00;

	// All done.
	return;
}

void reset_can(void)
{
	CANGCON = (1 << SWRES);

	// All done.
	return;
}

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

void bootloader_module_can::reset_request_procedure()
{
	confirm_reception(message_confirmation_success);// Always successful
	
	if(reception_message.message[0] == 0)
	{
		// Reboot the microcontroller back to the bootloader again.
		reboot_to_bootloader();

		// We will never reach here.
	}
	else
	{
		// Reboot to the application.
		reboot_to_application();

		// We will never reach here.
	}

	// We will never reach here.
	return;
}

void bootloader_module_can::get_info_procedure(void)
{
	transmission_message.dlc = 6;
	transmission_message.message_type = GET_INFO;
	
	// Insert Device signaure
	uint8_t device_signature[4];
	get_device_signature(device_signature);
	
	transmission_message.message[0] = device_signature[0];
	transmission_message.message[1] = device_signature[1];
	transmission_message.message[2] = device_signature[2];
	transmission_message.message[3] = device_signature[3];
	
	// Insert bootloader version
	uint16_t bootloader_version = get_bootloader_version();
	
	transmission_message.message[4] = static_cast<uint8_t>(bootloader_version >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(bootloader_version);
	
	transmit_can_message(transmission_message);

	// All done.
	return;
}

void bootloader_module_can::write_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32 bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
				     ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
				     ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
				     (static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
	                                    (static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details
	if ((current_firmware_page.code_length > SPM_PAGESIZE) || (current_firmware_page.page >= BOOTLOADER_START_ADDRESS))
	{
		// Message failure
		message_confirmation_success = false;
		write_details_stored = false;
	}
	else
	{
		// Message success
		write_details_stored = true;
		current_firmware_page.current_byte = 0;
	}

	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::write_data_procedure(Firmware_page& current_firmware_page)
{
	// Only write to buffer if a memory address and length have been provided
	if (write_details_stored)
	{
		// Check for possible array overflow.
		if ((current_firmware_page.current_byte + reception_message.dlc) > current_firmware_page.code_length)
		{
			reception_message.dlc = current_firmware_page.code_length - current_firmware_page.current_byte; // Limit the dlc.
		}

		// Store data from received message(message data of 7 bytes) into the buffer(byte by byte).
		for (uint8_t i = 0; i < reception_message.dlc; i++)
		{
			current_firmware_page.data[current_firmware_page.current_byte + i] = reception_message.message[i];
		}

		// Increment the current byte in buffer.
		current_firmware_page.current_byte += reception_message.dlc;

		// Check if the buffer is ready to be written to the flash.
		if (current_firmware_page.current_byte >= (current_firmware_page.code_length))
		{
			current_firmware_page.ready_to_write = true;
			current_firmware_page.current_byte = 0;
			write_details_stored = false;
		}
	}
	else
	{
		// Message failure
		message_confirmation_success = false;
	}

	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::read_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32 bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
				     ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
				     ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
				     (static_cast<uint32_t>(reception_message.message[3])));
	
	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
	                                    (static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details
	if ((current_firmware_page.code_length > SPM_PAGESIZE) || (current_firmware_page.page >= BOOTLOADER_START_ADDRESS))
	{
		// Message failure
		message_confirmation_success = false;
	}
	else
	{
		// Message success
		current_firmware_page.ready_to_read = true;
		ready_to_send_page = true;// Allow sending the flash page once it is read
	}
	
	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::send_flash_page(Firmware_page& current_firmware_page)
{
	transmission_message.message_type = READ_DATA;
	current_firmware_page.current_byte = 0; // Start at the beginning of buffer.
	reception_message.confirmed_send = false;
	
	// Send the flash page in 8 byte messages, confirmation message must be received from uploader after each message.
	while (current_firmware_page.current_byte < current_firmware_page.code_length)
	{
		// Determine the length of message, just in case we are closer than 8 bytes and need to send a smaller message.
		transmission_message.dlc = (current_firmware_page.code_length - current_firmware_page.current_byte);
		if (transmission_message.dlc > 8) // Limit to 8 byte messages.
		{
			transmission_message.dlc = 8;
		}

		// Create message.
		for (uint8_t i = 0; i < transmission_message.dlc; i++)
		{
			transmission_message.message[i] = current_firmware_page.data[current_firmware_page.current_byte + i];
		}

		// Increment the current_byte for next iteration.
		current_firmware_page.current_byte += transmission_message.dlc;		
		
		// Send the message.
		transmit_can_message(transmission_message);
		
		// Wait for confirmation message to return from host or a uploader command message.
		while(!reception_message.confirmed_send && !reception_message.message_received)	
		{
			// Do nothing.
		}
		
		// Exits the sending of the flash page if a uploader command message is received.
		// Allows the host to stop the reading if it sees a message is lost.
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
	// Determine the corresponding procedure for the received message.
	
	if (reception_message.message_type == REQUEST_RESET)
	{
		reset_request_procedure();

		// We will never reach here.
	}	
	else if (reception_message.message_type == GET_INFO)
	{
		get_info_procedure();
		reception_message.message_received = false;
	}
	else if (reception_message.message_type == WRITE_MEMORY)
	{
		write_memory_procedure(current_firmware_page);
		reception_message.message_received = false;
	}
	else if (reception_message.message_type == WRITE_DATA)
	{
		write_data_procedure(current_firmware_page);
		reception_message.message_received = false;
	}
	else if(reception_message.message_type == READ_MEMORY)
	{
		read_memory_procedure(current_firmware_page);
		reception_message.message_received = false;
	}

	// All done.
	return;
}

void bootloader_module_can::alert_uploader(void)
{
	transmission_message.dlc = 8;
	transmission_message.message_type = HOST_ALERT;
	for(uint8_t i = 0; i < transmission_message.dlc; i++)
	{
		transmission_message.message[i] = 0xFF; // TODO - delete
	}
	transmit_can_message(transmission_message);

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.



/**
 * ISR for interupts from CAN controller.
 * This routine only operates on received messages, it reads the ID, DLC and data from the CAN controller into a Message_info object.
 * The ISR also sets a flag to tell Boot loader that a new message has been received, or that a confirmation message has been received.
 */
#if defined (__AVR_AT90CAN128__)
ISR(CANIT_vect)
#else
ISR(CAN_INT_vect)
#endif
{
	// Save curent MOb page for current program operations. 
	uint8_t saved_MOb = CANPAGE;

	// Select the reception MOb0.
	uint8_t mob_number = 0;
	CANPAGE = (mob_number << 4);
	
	// Check that the interrupt was from message reception.
	if (CANSTMOB & (1 << RXOK))
	{
		// Check node ID, if not the same exit ISR.
		// Node ID is the first byte of data,  checking this will then auto increment to second byte of can message.
		if (CANMSG == NODE_ID)
		{
			// Store message id.
			module.reception_message.message_type = ((CANIDT1 << 3) | (CANIDT2 >> 5));
			
			// A confirmation message received.
			if (module.reception_message.message_type == READ_DATA)
			{
				module.reception_message.confirmed_send = true;
			}				
			// A uploader command message received.
			else
			{
				// Store dlc.
				module.reception_message.dlc = ((CANCDMOB & 0x0F) - 1); // Minus 1 as the first byte was taken up by the node ID.
				if (module.reception_message.dlc > 7)
				{
					module.reception_message.dlc = 7; // Check required as CAN controller may give greater than 8 dlc value.
				}

				// Store the message.
				for (uint8_t i = 0; i < module.reception_message.dlc; i++)
				{
					// NOTE - The CANPAGE index auto increments, accessing CANMSG will increment to next byte for next iteration.
					module.reception_message.message[i] = CANMSG; 
				}
			
				// Tell Boot loader that the message was received.
				module.reception_message.message_received = true;
				
				// Default the message confirmation to successful
				message_confirmation_success = true;
			}
		}
	}

	// Reset status flags.
	CANSTMOB = 0x00;

	// Reenable reception for MOb.
	CANCDMOB = ((1 << CONMOB1) | (8));

	// Restore previous MOb page.
	CANPAGE = saved_MOb;

	// All done.
	return;
}
	
// ALL DONE.
