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
 *  FILE: 		bootloader_module_canspi.h
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	7-1-2013
 *
 *	Matching header file for bootloader_module_canspi.c.  Provides a bootloader_module which only supports CAN via SPI
 *	programming.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __bootloader_module_canspi_H__
#define __bootloader_module_canspi_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

#include "bootloader_module.hpp"

// Include the bootloader can module information sharing struct type.
#include "application_interface/application_interface_module_constants_canspi.hpp"

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

class bootloader_module_canspi: public Bootloader_module
{
	public:

		// Class types.
		
			// Struct for CAN message information.
		struct Message_info
		{
			bool confirmed_send;
			bool message_received;
			uint16_t message_type;
			uint16_t dlc;
			uint8_t message[8]; // CAN messages can only be 8 bytes long.
		};

		// Class fields.

		volatile Message_info reception_message; // This will be updated by ISR(PCINT2_vect)
		Message_info transmission_message;

		// Class methods.
	
		/**
		 *	Destroys the module when it goes out of scope.  Not that this DOESN'T exit the module properly, so the exit function
		 *	still needs to be called.
		 *	
		 */
		virtual ~bootloader_module_canspi();

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
		 *	Procedure when a REQUEST_RESET message is received. Either starts the application or resets the Bootloader.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void request_reset_procedure();

		/**
		 *	Procedure when a GET_INFO message is received. Sends the host information about the microcontroller.
		 * 
		 *	NOTE - Host information is the device signature and the bootloader version 
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void get_info_procedure(void);

		/**
		 *	Procedure when a WRITE_MEMORY message is received. Saves the Flash page number and the length of code that is to be written to.
		 *
		 *	TAKES:		buffer			The firmware_page buffer for flash writing details to be stored in.
		 *
		 *	RETURNS:	Nothing.
		 */
		void write_memory_procedure(Firmware_page& current_firmware_page);

		/**
		 *	Procedure when a WRITE_DATA message is received. Saves message data into a buffer which can then be written to the FLASH.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void write_data_procedure(Firmware_page& current_firmware_page);
	
		/**
		 *	Procedure when a READ_MEMORY message is received. Saves the Flash page number and the length of code to read.
		 *
		 *	TAKES:		buffer			The firmware_page buffer for flash reading details to be stored in.
		 *
		 *	RETURNS:	Nothing.
		 */
		void read_memory_procedure(Firmware_page& current_firmware_page);

		/**
		 *	Sends the copy of the FLASH page in CAN messages.
		 *
		 *	TAKES:		buffer			The firmware_page buffer that the flash page has been copied to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void send_flash_page(Firmware_page& current_firmware_page);

		/**
		 *	Executes the corresnponding procedure for a uploader command message received.
		 *
		 *	TAKES:		buffer			The firmware_page buffer that is used for reading and writing the flash memory.
		 *
		 *	RETURNS:	Nothing.
		 */
		void filter_message(Firmware_page& current_firmware_page);

		/**
		 *	Sends the uploader a message informing it that the microcontroller is awaiting firmware messages.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void alert_uploader(void);
};

// DECLARE PUBLIC GLOBAL VARIABLES.

extern bootloader_module_canspi module;

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


#endif // __bootloader_module_canspi_H__

// ALL DONE.
