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
#ifndef __BOOTLOADER_MODULE_CAN_H__
#define __BOOTLOADER_MODULE_CAN_H__

// INCLUDE REQUIRED HEADER FILES.

#include "bootloader_module.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.
#define MESSAGE_LENGTH 8 //CAN messages can only be 8 bytes long and the first byte of these messages will be the node id.
#define NODE_ID 0xAA //Will be chosen by user by toolchain
#define base_id 0x120 //Yet to be finalised


class bootloader_module_can : public bootloader_module
{
	public:
		
		enum message_id {START_RESET = base_id, GET_INFO = base_id+1, WRITE_MEMORY = base_id+2, WRITE_DATA = base_id+3, READ_MEMORY = base_id+4, READ_DATA = base_id+5, ALERT_HOST = 0x2FF};


		//Struct for CAN message information
		struct message_info
		{
			bool confirmed_send;
			bool message_received;
			uint16_t message_type;
			uint16_t dlc;
			uint8_t message[MESSAGE_LENGTH];
		};
		volatile message_info reception_message;//(VOLATILE - will be updated by CANIT ISR)
		message_info transmission_message;


		// Functions.
	
		/**
		 *	Destroys the module when it goes out of scope.  Not that this DOESN'T exit the module properly, so the exit function
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
		 *	Procedure when a start_reset message is received. Either starts the application or resets the Boot Loader.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		firmware_finished			The flag to tell Boot loader that the program update is completed.
		 *
		 *	RETURNS:	Nothing.
		 */
		void start_reset_procedure(bool& firmware_finished_flag);

		/**
		 *	Procedure when a get_info message is received. Sends the host information about the microcontroller.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void get_info_procedure(void);

		/**
		 *	Procedure when a write_memory message is received. Saves the Flash page to write to and the length of code to write to.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void write_memory_procedure(firmware_page& current_firmware_page);

		/**
		 *	Procedure when a write_data message is received. Saves message data into buffer which can then be written to the FLASH.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void write_data_procedure(firmware_page& current_firmware_page);
	
		/**
		 *	Procedure when a read_memory message is received. Saves the Flash page to read and the length of code to read.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void read_memory_procedure(firmware_page& current_firmware_page);

		/**
		 *	Sends the copy of the FLASH page in messages.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void send_flash_page(firmware_page& current_firmware_page);

		/**
		 *	Executes the procedure required for the received message.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		buffer			The firmware_page buffer.
		 *
		 *			firmware_finished	The flag to set if the host requests to start the application.
		 *
		 *	RETURNS:	Nothing.
		 */
		void filter_message(firmware_page& current_firmware_page, firmware_page& read_current_firmware_page, bool& firmware_finished_flag);

		/**
		 *	Send host a message informing that the microcontroller is awaiting firmware messages.
		 *
		 *	NOTE - Nothing.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void alert_host(void);


		//
		//
		//TEST function
		//
		void can_test(uint32_t i);

	private:
};

extern bootloader_module_can module;


// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__BOOTLOADER_MODULE_CAN_H__*/

// ALL DONE.
