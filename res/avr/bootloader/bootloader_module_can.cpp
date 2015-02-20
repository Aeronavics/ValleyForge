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

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <avr/interrupt.h>

// Include can message ids.
#include "can_messages.h"

// DEFINE PRIVATE MACROS.

// Bootloader information.

#define BOOTLOADER_START_ADDRESS <<<TC_INSERTS_BOOTLOADER_START_ADDRESS_HERE>>>

// CAN peripheral information.
#if defined (__AVR_AT90CAN128__)
	#define NUMBER_OF_MOB_PAGES 15
#else
	#define NUMBER_OF_MOB_PAGES 6
#endif

// CAN Baud rate values.
#define CAN_BAUD_RATE <<<TC_INSERTS_CAN_BAUD_RATE_HERE>>>
#define CLK_SPEED_IN_MHZ <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>

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
 	#else
 		#error "Invalid CAN baud rate."
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

const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;

// State flags.
bool communication_started;
bool communication_recent;
bool ready_to_send_page;
bool write_details_stored;

// Flag indicating an error has occurred.  Currently, once an error occurs, there is no way to clear it other than a reset.
volatile bool error;

// NOTE - Invalid commands received via CAN don't count as errors, handling them is 'normal' behaviour.  An error is like CAN transmission fails.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_can::~bootloader_module_can()
{
	// All done.
	return;
}

void bootloader_module_can::init(void)
{	
	// Initialise the module.

	// Initialize the CAN controller.

	uint8_t mob_number = 0;

	// Reset the CAN controller.
	CANGCON = (1 << SWRES);
	
	// Reset all of the MObs as they have no default value upon reset.
	for (mob_number = 0; mob_number < NUMBER_OF_MOB_PAGES; mob_number++)
	{
		// Select CAN page.
		CANPAGE = (mob_number << 4);
		CANSTMOB = 0x00; // Clear all flags.
		CANCDMOB = 0x00; // Disables MObs.
	}
	
	// Set up bit timing.
	CANBT1 = CAN_BAUD_RATE_CONFIG_1;
	CANBT2 = CAN_BAUD_RATE_CONFIG_2;
	CANBT3 = CAN_BAUD_RATE_CONFIG_3;

	// Id's for reception.
	uint16_t id = CANID_BASE_ID;

	// Choose the MObs to set up.

	// MOB NUMBER 0 - Reception MOb.
	mob_number = 0;
	CANPAGE = (mob_number << 4);
	
	CANIDT1 = id >> 3;; // Set MOb ID.
	CANIDT2 = id << 5;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	
	CANIDM1 = 0xFE; // Set MOb masking ID.
	CANIDM2 = 0x00; // At the moment are filtering first two hex numbers e.g id=0x123, filter = 0x12z - where z can be any number.
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	
	CANCDMOB = ((1 << CONMOB1) | 8); // Enable the MOb for reception of 8 data bytes, 
	                                 //in standard format(11 bit identifier) with no automatic reply.

	// MOB NUMBER 1 - Transmission MOb.
	mob_number = 1;
	CANPAGE = (mob_number << 4);
	
	CANIDT1 = 0x00; // Set MOb ID.
	CANIDT2 = 0x00; // Will be set by bootloader before transmission.
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;

	CANIDM1 = 0x00; // Set MOb masking ID.
	CANIDM2 = 0x00;
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	
	// Enable the interupts for the MObs enabled.
	CANIE1 = 0x00;
	CANIE2 = (1 << IEMOB0); // Enable interupts on MOb0 (interupt occurs on reception of message).

	// Enable general interupts.
	CANGIE = ((1 << ENIT) | (1 << ENRX)); // Enable receive interupt through CAN_IT.

	// Enable CAN communication.
	CANGCON = (1 << ENASTB); // Sets the AVR pins to Tx and Rx.

	// All done.
	return;
}

void bootloader_module_can::exit(void)
{
	// Just disable the CAN controller.  The rest doesn't matter.
	CANGCON = (1 << SWRES);

	// TODO - This isn't true!?  What if the application code assumes some CAN registers we touched are all zeroes?

	// All done.
	return;
}

void bootloader_module_can::event_idle()
{
	// Check if we've recieved a new message.
	if (message_received)
	{		
		// Handle the incoming message.
		filter_message();
	}	

	// Check if we've just finished reading a flash page that we want to send.
	if (!buffer.ready_to_read && ready_to_send_page)
	{
		// We're no longer ready to send the page, we're actually queuing it up for transmission.
		ready_to_send_page = false;
		transmission_queued = true;
	}

	// Check if we've already sent a message, and we're waiting for the uploader to confirm it.
	if (transmission_unconfirmed)
	{
		// We don't do anything, we just wait for confirmation to arrive.
	}
	else
	{
		// Otherwise, if we're still in the middle of sending a page, we send another chunk.
		if (transmission_queued)
		{
			// Send another chunk of bytes.
			send_read_data();	

			// Increment the current_byte for next message.
			buffer.current_byte += transmission_message.dlc;

			// Now, we need to wait for confirmation before we do this again.
			transmission_unconfirmed = true;

			// If that was the last chunk, then we haven't anything more to do.
			if (buffer.current_byte >= buffer.code_length)
			{
				transmission_queued = false;
			}			
		}
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
			send_alert_host();

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
		// Increment the number of ticks since we've heard from the uploader.
		comms_ticks++;

		// Check if it seems like the comms have died.
		if (comms_ticks >= COMMS_TIMEOUT)
		{
			// Reset the comms timeout
			comms_ticks = 0;
		}
	}
	else
	{
		// Clear the comms timeout.
		comms_ticks = 0;

		// We're back to square one again.
		communication_started = false;
		transmission_queued = false;
		transmission_unconfirmed = false;

		// Change the status of the bootloader.
		if (!error)
		{
			set_bootloader_state(IDLE);
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
	// Avoids name mangling for the shared jumptable.
extern "C" void get_bootloader_module_information_BL(Shared_bootloader_module_constants* bootloader_module_information)
{
	get_bootloader_module_information(bootloader_module_information);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

void bootloader_module_can::transmit_CAN_message()
{
	// Select tranmitting MOB.
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
	CANIDT2 = (transmission_message.message_type << 5);
	CANIDT1 = (transmission_message.message_type >> 3);
	
	// Set message.
	for (uint8_t i = 0; i < transmission_message.dlc; i++)
	{
		CANMSG = transmission_message.message[i];
	}
	
	// Enable tranmission with desired message length.
	CANCDMOB = ((1 << CONMOB0) | (transmission_message.dlc));
	
	// Wait until the message has sent or an error occured.
	// When the termination is not present on the bus the bootloader seems to get stuck in this loop and reset due to watchdog timeouts or similar.
	// This does not seem to set any of the error flags in the MOB even though it should.
	// TODO - determine why the bootloader gets stuck here and ensure that it does not.
	while (((CANSTMOB & (1 << TXOK)) == 0) && ((CANSTMOB & (1 << AERR)) == 0) && ((CANSTMOB & (1 << BERR)) == 0))
	{
		// Do nothing.
	}
	
	//If the loop exited but did not do so due to a TXOK condition we set the error state.
	if (!(CANSTMOB & (1 << TXOK)))
	{
		// Change the bootloader status to indicate an error.
		set_bootloader_state(ERROR);

		// Set our own error flag.
		error = true;
	}

	// Disable transmit.
	CANCDMOB = 0x00;
	
	// Clear interrupt flags.
	CANSTMOB = 0x00;

	// All done.
	return;
}

void bootloader_module_can::handle_request_reset()
{
	// If we were in the middle of transmitting page data, we abandon that idea.
	transmission_unconfirmed = false;
	transmission_queued = false;

	// Confirm the reset command, since the reset command is always successful.
	send_confirm_rxup(CANID_REQUEST_RESET, true);
	
	// Reboot to either the application or the bootloader, depending on what was requested.
	if (!reception_message.message[1])
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

void bootloader_module_can::handle_get_info(void)
{	
	// TODO - At the moment, the bootloader doesn't bother sending a confirmation, since it just sends the info directly.

	// If we were in the middle of transmitting page data, we abandon that idea.
	transmission_unconfirmed = false;
	transmission_queued = false;

	// Send the device information.
	send_device_info();

	// All done.
	return;
}

void bootloader_module_can::handle_write_memory(void)
{
	// If we were in the middle of transmitting page data, we abandon that idea.
	transmission_unconfirmed = false;
	transmission_queued = false;

	// Initially, we'll assume the command to be sane.
	bool command_ok = true;

	// Check the DLC was what we expected.
	if (reception_message.dlc != 7)
	{
		command_ok = false;
	}
	else
	{
		// Store the 32 bit page number.
		buffer.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
									 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
									 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
									 (static_cast<uint32_t>(reception_message.message[3])));

		// Store the 16 bit code_length.
		buffer.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
											(static_cast<uint16_t>(reception_message.message[5])));

		// Check for errors in message details.
		if ((buffer.code_length > SPM_PAGESIZE) || (buffer.page >= BOOTLOADER_START_ADDRESS))
		{
			// Something was wrong with the command.  Probably the specified address was invalid.
			command_ok = false;

			// Invalidate the write details, so the uploader can't write to a bad location.
			write_details_stored = false;
		}
		else
		{
			// The command seems ok.

			// Enable the write details, which means now the uploader should be able to provide the actual data to write.
			write_details_stored = true;

			// We start writing at the first byte of the specified page.
			buffer.current_byte = 0;
		}
	}

	// Confirm the command, now we've worked out whether it was sane or not.
	send_confirm_rxup(CANID_WRITE_MEMORY, command_ok);

	// All done.
	return;
}

void bootloader_module_can::handle_write_data(void)
{
	// If we were in the middle of transmitting page data, we abandon that idea.
	transmission_unconfirmed = false;
	transmission_queued = false;

	// Initially, we'll assume the command to be sane.
	bool command_ok = true;

	// Only write to buffer if a valid memory address and code length have already been provided.
	if (write_details_stored)
	{
		// Check for possible array overflow.
		if ((buffer.current_byte + (reception_message.dlc - 1)) > buffer.code_length)
		{
			// Limit the DLC if we're up to the last byte.
			reception_message.dlc = (buffer.code_length - buffer.current_byte) + 1;

			// NOTE - The message DLC has to be one longer than the number of bytes, because of the node ID in the first byte.
		}

		// Store data from received message (max seven bytes because of node ID) into the buffer.
		for (uint8_t i = 1; i < reception_message.dlc; i++)
		{
			buffer.data[buffer.current_byte + i - 1] = reception_message.message[i];
		}

		// Increment the current byte in buffer.
		buffer.current_byte += (reception_message.dlc - 1);

		// Check if the buffer is ready to be written to flash.
		if (buffer.current_byte >= (buffer.code_length))
		{
			// Queue up writing the buffer into flash.
			buffer.ready_to_write = true;

			// We need new address details before we can write more data.
			write_details_stored = false;
		}
	}
	else
	{
		// Something was wrong with the command.  Probably trying to write data before setting the destination details.
		command_ok = false;
	}

	// Confirm the command, now we've worked out whether it was sane or not.
	send_confirm_rxup(CANID_WRITE_DATA, command_ok);

	// All done.
	return;
}

void bootloader_module_can::handle_read_memory(void)
{	
	// If we were in the middle of transmitting page data, we abandon that idea.
	transmission_unconfirmed = false;
	transmission_queued = false;

	// Initially, we'll assume the command to be sane.
	bool command_ok = true;

	// Check the DLC was what we expected.
	if (reception_message.dlc != 7)
	{
		command_ok = false;
	}
	else
	{
		// Store the 32 bit page number.
		buffer.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
									 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
									 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
									 (static_cast<uint32_t>(reception_message.message[3])));

		// Store the 16 bit code_length.
		buffer.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
											(static_cast<uint16_t>(reception_message.message[5])));

		// Start from the first byte.
		buffer.current_byte = 0;

		// Check for errors in message details.
		if ((buffer.code_length > SPM_PAGESIZE) || (buffer.page >= BOOTLOADER_START_ADDRESS))
		{
			// Something was wrong with the command.  Probably the specified address was invalid.
			command_ok = false;
		}
		else
		{
			// The command seems ok.

			// Queue up reading a page from flash into a buffer, and then sending the buffer.
			buffer.ready_to_read = true;
			ready_to_send_page = true;
		}
	}
	
	// Confirm the command, now we've worked out whether it was sane or not.
	send_confirm_rxup(CANID_READ_MEMORY, command_ok);

	// All done.
	return;
}

void bootloader_module_can::filter_message(void)
{
	// Whatever the case, we won't need to worry about this same message again.
	message_received = false;

	// NOTE - We test the NODE_ID first, then the actual message type, solely because it makes the code a little tidier.

	// If this message is intended for this node, then data[0] should match our own NODE_ID.
	if (reception_message.dlc < 1)
	{
		// This can't possibly be a message for us, because it doesn't have any data, and all our messages should.
		return;
	}
	else
	{
		// This might be a message for us; check if the NODE_ID matches.
		if (reception_message.message[0] != NODE_ID)
		{
			// This isn't a message for us, because the ID doesn't match.
			return;
		}
	}
	// Else, it might be a message for us, depending on what the actual message ID is.

	// NOTE - If a message is intended for us, we BREAK, but if its not one of ours, we RETURN.

	// Determine the corresponding behavior for the received message.
	switch (reception_message.message_type)
	{
		case CANID_REQUEST_RESET:
			handle_request_reset();
			break;

		case CANID_GET_INFO:
			handle_get_info();
			break;
			
		case CANID_WRITE_MEMORY:
			handle_write_memory();
			break;

		case CANID_WRITE_DATA:
			handle_write_data();
			break;

		case CANID_READ_MEMORY:
			handle_read_memory();
			break;

		case CANID_READ_DATA:
			// This is a confirmation message from the uploader, indicating that it received the page we sent ok.

			// If we were previously transmitting a message, we aren't any longer.
			module.transmission_unconfirmed = false;
			break;

		default:
			// This message isn't for us, because it's not an ID which we recognise.
			return;
	}

	// We've now started communications.
	communication_started = true;
	communication_recent = true;

	// Change the status of the bootloader.
	if (!error)
	{
		set_bootloader_state(COMMUNICATING);
	}

	// Restart the bootloader timeout, so we don't reboot halfway through a transfer.
	set_bootloader_timeout(false);
	set_bootloader_timeout(true);
	
	// All done.
	return;
}

void bootloader_module_can::send_alert_host(void)
{
	// Assemble the message to send.
	transmission_message.message_type = CANID_HOST_ALERT;
	transmission_message.dlc = 1;
	transmission_message.message[0] = NODE_ID;

	// Actually send the message.
	transmit_CAN_message();

	// All done.
	return;
}	

void bootloader_module_can::send_confirm_rxup(uint16_t id, bool success)
{
	// Assemble the message to send.
	transmission_message.message_type = id;
	transmission_message.dlc = 1;
	transmission_message.message[0] = (true) ? 1 : 0;
	
	// Actually send the message.	
	transmit_CAN_message();

	// All done.
	return;
}

void bootloader_module_can::send_device_info(void)
{
	// Fetch the device signaure.
	uint8_t device_signature[4];
	get_device_signature(device_signature);

	// Fetch the bootloader version.
	uint16_t bootloader_version = get_bootloader_version();
	
	// Assemble the message to send.
	transmission_message.message_type = CANID_GET_INFO;
	transmission_message.dlc = 6;
	transmission_message.message[0] = device_signature[0];
	transmission_message.message[1] = device_signature[1];
	transmission_message.message[2] = device_signature[2];
	transmission_message.message[3] = device_signature[3];
	transmission_message.message[4] = static_cast<uint8_t>(bootloader_version >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(bootloader_version);
	
	// Actually send the message.
	transmit_CAN_message();

	// All done.
	return;
}

void bootloader_module_can::send_read_data()
{
	// Assemble the message to send.
	
	transmission_message.message_type = CANID_READ_DATA;

	// Determine the length of message, just in case we are closer than 8 bytes and need to send a smaller message.
	transmission_message.dlc = (buffer.code_length - buffer.current_byte);
	if (transmission_message.dlc > 8)
	{
		transmission_message.dlc = 8;
	}

	// Create message.
	for (uint8_t i = 0; i < transmission_message.dlc; i++)
	{
		transmission_message.message[i] = buffer.data[buffer.current_byte + i];
	}

	// Actually send the message.
	transmit_CAN_message();

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

/**
 * ISR for interupts from CAN controller.
 * This routine only operates on received messages, it reads the ID, DLC and data from the CAN controller into a Message_info object.
 * The ISR also sets a flag to tell Bootloader that a new message has been received, or that a confirmation message has been received.
 */
#if defined (__AVR_AT90CAN128__)
ISR(CANIT_vect)
#else
ISR(CAN_INT_vect)
#endif
{
	// Save curent MOb page for current operations. 
	uint8_t saved_MOb = CANPAGE;

	// Select the reception MOb0.
	uint8_t mob_number = 0;
	CANPAGE = (mob_number << 4);
	
	// Check that the interrupt was from message reception.
	if (CANSTMOB & (1 << RXOK))
	{
		// Store message id.
		module.reception_message.message_type = ((CANIDT1 << 3) | (CANIDT2 >> 5));
			
		// If the previously recieved message hasn't been handled yet, then panic.
		if (module.message_received)
		{
			// We don't have much option but to discard the previous message.  But try alert the user about this.

			// Change the bootloader status to indicate an error.
			set_bootloader_state(ERROR);

			// Set our own error flag.
			error = true;
		}

		// Store DLC of incoming message.
		module.reception_message.dlc = ((CANCDMOB & 0x0F));

		// TODO - No idea why this check is necessary?  Is the mask used above not correct?

		// Make sure the DLC is within range.
		if (module.reception_message.dlc > 8)
		{
			module.reception_message.dlc = 8;
		}

		// Store the message payload.
		for (uint8_t i = 0; i < module.reception_message.dlc; i++)
		{
			module.reception_message.message[i] = CANMSG; 
		}

		// NOTE - The CANPAGE index auto increments, reading CANMSG will increment to the next byte for the next iteration.
			
		// Tell the synchronous part of the module that a message was received.
		module.message_received = true;
	}

	// Reset status flags.
	CANSTMOB = 0x00;

	// Reenable reception for MOb0.
	CANCDMOB = ((1 << CONMOB1) | (8));

	// Restore previous MOb page.
	CANPAGE = saved_MOb;

	// All done.
	return;
}
	
// ALL DONE.
