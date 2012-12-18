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

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

#include "bootloader_module.hpp"

#include <avr/io.h>

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

const uint16_t BOOTLOADER_VERSION = 0x0100; // const uint8_t BOOTLOADER_VERSION = <<<TC_INSERTS_BOOTLOADER_VERSION_HERE>>>;

#define MESSAGE_LENGTH 8 // CAN messages can only be 8 bytes long and the first byte of these messages will be the node id.

const uint8_t NODE_ID = 0xFF; // const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;

#define BASE_ID 0x120 // TODO - Yet to be finalised.

// In case of using a  microcontroller with a 32-bit device signature.
#define DEVICE_SIGNATURE_0 0x00
#define DEVICE_SIGNATURE_1 SIGNATURE_0
#define DEVICE_SIGNATURE_2 SIGNATURE_1
#define DEVICE_SIGNATURE_3 SIGNATURE_2

// The CAN controller MObs.
#if defined (__AVR_AT90CAN128__)
	#define NUMBER_OF_MOB_PAGES 15
#else
	#define NUMBER_OF_MOB_PAGES 6
#endif

// CAN Baud rate values.
#define CAN_BAUD_RATE		1000	// TODO - Replace with this: <<<TC_INSERTS_CAN_BAUD_RATES_HERE>>>
#define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>> // TODO - May need a check for more clock speed, calculation would be better but more difficult.

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

class bootloader_module_can : public bootloader_module
{
	public:

		// Class types.
		
		enum message_id {RESET_REQUEST = BASE_ID, GET_INFO = BASE_ID + 1, WRITE_MEMORY = BASE_ID + 2, WRITE_DATA = BASE_ID + 3, READ_MEMORY = BASE_ID + 4,
				 READ_DATA = BASE_ID + 5, ALERT_UPLOADER = 0x2FF};
		
			// Struct for CAN message information.
		struct message_info
		{
			bool confirmed_send;
			bool message_received;
			uint16_t message_type;
			uint16_t dlc;
			uint8_t message[MESSAGE_LENGTH];
		};

		// Class fields.

		volatile message_info reception_message; // This will be updated by CANIT ISR.
		message_info transmission_message;

		bool communication_started;

		// Class methods.
	
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
		 *	Procedure when a start_reset message is received. Either starts the application or resets the Boot Loader.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void reset_request_procedure();

		/**
		 *	Procedure when a get_info message is received. Sends the host information about the microcontroller.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void get_info_procedure(void);

		/**
		 *	Procedure when a write_memory message is received. Saves the Flash page to write to and the length of code to write to.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void write_memory_procedure(firmware_page& current_firmware_page);

		/**
		 *	Procedure when a write_data message is received. Saves message data into buffer which can then be written to the FLASH.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void write_data_procedure(firmware_page& current_firmware_page);
	
		/**
		 *	Procedure when a read_memory message is received. Saves the Flash page to read and the length of code to read.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void read_memory_procedure(firmware_page& current_firmware_page);

		/**
		 *	Sends the copy of the FLASH page in messages.
		 *
		 *	TAKES:		buffer			The firmware_page buffer to be written to.
		 *
		 *	RETURNS:	Nothing.
		 */
		void send_flash_page(firmware_page& current_firmware_page);

		/**
		 *	Executes the procedure required for the received message.
		 *
		 *	TAKES:		buffer			The firmware_page buffer.
		 *			firmware_finished	The flag to set if the host requests to start the application.
		 *
		 *	RETURNS:	Nothing.
		 */
		void filter_message(firmware_page& current_firmware_page);

		/**
		 *	Send host a message informing that the microcontroller is awaiting firmware messages.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		void alert_uploader(void);
};

// DECLARE PUBLIC GLOBAL VARIABLES.

extern bootloader_module_can module;

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif // __BOOTLOADER_MODULE_CAN_H__

// ALL DONE.
