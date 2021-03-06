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
 *  FILE: 		bootloader_module_can.h
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	30-11-2012
 *
 *	Matching header file for bootloader_module_can.c.  Provides a bootloader_module which only supports CAN
 *	programming.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __bootloader_module_can_H__
#define __bootloader_module_can_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

#include "bootloader_module.hpp"

// Include the bootloader can module information sharing struct type.
#include "application_interface/application_interface_module_constants_can.hpp"

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

class bootloader_module_can : public Bootloader_module
{
	public:
		
		// Struct for CAN message information.
		struct Message_info
		{
			uint16_t message_type;
			uint16_t dlc;
			uint8_t message[8]; // CAN message payloads can only be 8 bytes long.
		};

		// Fields.

		volatile Message_info reception_message; // This will be updated by CANIT ISR.

		volatile bool message_received; // This will be updated by CANIT ISR.
		
		Message_info transmission_message;

		// Flag indicating we are in the process of sending the current flash page as a series of messages.
		bool transmission_queued;

		// Flag indicating that we're waiting for a transmitted message to be confirmed by the uploader.
		bool transmission_unconfirmed;

		// Methods.
	
		/**
		 *	Destroys the module when it goes out of scope.  Note - that this DOESN'T exit the module properly, so the exit function
		 *	still needs to be called.
		 *	
		 */
		virtual ~bootloader_module_can();

		/**
		 *	Starts up the module; initialize whatever peripherals are required, configures interrupts, etc.
		 *
		 *	NOTE - There is no reporting of whether the initialization was successful.  Bootloader code is assumed to ALWAYS work.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void init(void);

		/**
		 *	Shuts down the module; deactivate whatever peripherals were used, etc.
		 *
		 *	NOTE - The module must deactivate EVERYTHING it uses, so that the application code starts in a predictable state.
		 *
		 *	NOTE - There is no reporting of whether the shutdown was successful.  Bootloader code is assumed to ALWAYS work.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void exit();

		/**
		 *	Performs functionality which must be executed every cycle of the bootloader mainloop.
		 *
		 *	NOTE - Flash pages received asynchronously will not be written to flash if this blocks continuously.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void event_idle();

		/**
		 *	Performs functionality which must be executed on a periodic basis.  The function will be called with a period defined by the const
		 *	value MODULE_EVENT_PERIOD.
		 *
		 *	NOTE - This function is called from an ISR.  It must not block for extended periods.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void event_periodic();

	private:

		// Class types.

		// Class fields.

		// Class methods.

		/**
		 *	Sends the current TX message over CAN.
		 *
		 *	NOTE - Message details are defined in the transmit_message field.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void transmit_CAN_message();

		/**
		 *	Procedure when a REQUEST_RESET message is received. Either starts the application or resets the Bootloader.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void handle_request_reset();

		/**
		 *	Procedure when a GET_INFO message is received. Sends the host information about the microcontroller.
		 * 
		 *	NOTE - Host information is the device signature and the bootloader version 
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void handle_get_info(void);

		/**
		 *	Procedure when a WRITE_MEMORY message is received. Saves the Flash page number and the length of code that is to be written to.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void handle_write_memory(void);

		/**
		 *	Procedure when a WRITE_DATA message is received. Saves message data into a buffer which can then be written to the FLASH.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void handle_write_data(void);
	
		/**
		 *	Procedure when a READ_MEMORY message is received. Saves the Flash page number and the length of code to read.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void handle_read_memory(void);

		/**
		 *	Handles incoming CAN messages, performing the appropriate behaviour depending on the type of message.
		 *
		 *	NOTE - Message details are defined in the reception_message field.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void filter_message(void);

		/**
		 *	Sends the uploader a message informing it that the microcontroller is awaiting firmware messages.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void send_alert_host(void);

		/**
		 * Sends the uploader a message confirming the receipt of a command message.
		 *
		 * TAKES:	id		The CAN message ID of the command message which was received.
		 *			success	Flag indicating whether the received command was successful or not.
		 *
		 * RETURNS:	Nothing.
		 */
		void send_confirm_rxup(uint16_t id, bool success);

		/**
		 * Sends the uploader a message containing information about this device information.
		 *
		 * TAKES:	Nothing.
		 *
		 * RETURNS: Nothing.
		 */
		 void send_device_info(void);

		/**
		 *	Sends the uploader a message containing some bytes from the current firmware page.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void send_read_data(void);		 
};

// DECLARE PUBLIC GLOBAL VARIABLES.

extern bootloader_module_can module;

// DEFINE PUBLIC FUNCTION PROTOTYPES.

/**
 *	Stores bootloader module information in a struct that is shared with the application.
 * 
 *  NOTE - This function can be accessed by the application.
 *
 *	TAKES: 		bootloader_module_information		struct that bootloader module information is stored.
 *
 *	RETURNS: 	Nothing.
 */
void get_bootloader_module_information(Shared_bootloader_module_constants* bootloader_module_information);


#endif // __bootloader_module_can_H__

// ALL DONE.
