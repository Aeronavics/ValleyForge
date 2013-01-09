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
#ifndef __BOOTLOADER_MODULE_CANSPI_H__
#define __BOOTLOADER_MODULE_CANSPI_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

#include "bootloader_module.hpp"

#include <avr/io.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

	//Device infromation
const uint16_t BOOTLOADER_VERSION = 0x0100; // const uint8_t BOOTLOADER_VERSION = <<<TC_INSERTS_BOOTLOADER_VERSION_HERE>>>;

const uint8_t ALERT_UPLOADER_PERIOD = 10;//x10 ms to send each alert_host message before communication has begun

// In case of using a  microcontroller with a 32-bit device signature.
#define DEVICE_SIGNATURE_0 0x00
#define DEVICE_SIGNATURE_1 SIGNATURE_0
#define DEVICE_SIGNATURE_2 SIGNATURE_1
#define DEVICE_SIGNATURE_3 SIGNATURE_2

// Define the address at which the bootloader code starts (the RWW section).  This is MCU specific.
#if defined (__AVR_AT90CAN128__)	// Can just import the BOOT_START from the avr.cfg.
	#define BOOTLOADER_START_ADDRESS	0x1E000 // TODO - BOOTLOADER_START_ADDRESS	<<<TC_INSERTS_BOOTLOADER_START_ADDRESS_HERE>>>
#elif defined (__AVR_ATmega2560__)
	#define BOOTLOADER_START_ADDRESS	0x3E000
#else
	#define BOOTLOADER_START_ADDRESS 	0xF000 // ATMEGA64M1
#endif

//CAN BIT TIMING
//
#define CAN_BAUD_RATE	<<<TC_INSERTS_CAN_BAUD_RATES_HERE>>>
	// Note - only parameter that changes is BRP
#if (CAN_BAUD_RATE == 1000)
	//16MHz crystal, 1Mbps baud rate, 75% sampling rate, TQ = 0.125us
	//
	//Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1
	#define CAN_SJW 0

	//Prescalar = 2 BRP = (Fosc*TQ)/2 - 1
	#define  CAN_BRP  0

	//Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1
	#define CAN_PS1 2

	//Propagation delay = 2. PRSEG2 = Propagation delay - 1
	#define CAN_PRS 1

	//Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 500)
	//16MHz crystal, 500kbps baud rate, 75% sampling rate, TQ = 0.25us
	//
	//Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1
	#define CAN_SJW 0

	//Prescalar = 4. BRP = (Fosc*TQ)/2 - 1
	#define  CAN_BRP  1

	//Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1
	#define CAN_PS1 2

	//Propagation delay = 2. PRSEG2 = Propagation delay - 1
	#define CAN_PRS 1

	//Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 250)
	//16MHz crystal, 250kbps baud rate, 75% sampling rate, TQ = 0.5us
	//
	//Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1
	#define CAN_SJW 0

	//Prescalar = 8. BRP = (Fosc*TQ)/2 - 1
	#define  CAN_BRP  3

	//Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1
	#define CAN_PS1 2

	//Propagation delay = 2. PRSEG2 = Propagation delay - 1
	#define CAN_PRS 1

	//Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 200)
	//16MHz crystal, 200kbps baud rate, 75% sampling rate, TQ = 0.625us
	//
	//Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1
	#define CAN_SJW 0

	//Prescalar = 10. BRP = (Fosc*TQ)/2 - 1
	#define  CAN_BRP  4

	//Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1
	#define CAN_PS1 2

	//Propagation delay = 2. PRSEG2 = Propagation delay - 1
	#define CAN_PRS 1

	//Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 125)
	//16MHz crystal, 125kbps baud rate, 75% sampling rate, TQ = 1us
	//
	//Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1
	#define CAN_SJW 0

	//Prescalar = 16. BRP = (Fosc*TQ)/2 - 1
	#define  CAN_BRP  7

	//Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1
	#define CAN_PS1 2

	//Propagation delay = 2. PRSEG2 = Propagation delay - 1
	#define CAN_PRS 1

	//Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1
	#define CAN_PS2 1

#elif (CAN_BAUD_RATE == 100)
	//16MHz crystal, 100kbps baud rate, 75% sampling rate, TQ = 1.25us
	//
	//Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1
	#define CAN_SJW 0

	//Prescalar = 20. BRP = (Fosc*TQ)/2 - 1
	#define  CAN_BRP  9

	//Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1
	#define CAN_PS1 2

	//Propagation delay = 2. PRSEG2 = Propagation delay - 1
	#define CAN_PRS 1

	//Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1
	#define CAN_PS2 1

#endif

//REGISTER ADDRESSES
//
#define MCP_RXF0SIDH	0x00 
#define MCP_RXF0SIDL	0x01 
#define MCP_RXF0EID8	0x02 
#define MCP_RXF0EID0	0x03 
#define MCP_RXF1SIDH	0x04 
#define MCP_RXF1SIDL	0x05 
#define MCP_RXF1EID8	0x06 
#define MCP_RXF1EID0	0x07 
#define MCP_RXF2SIDH	0x08 
#define MCP_RXF2SIDL	0x09 
#define MCP_RXF2EID8	0x0A 
#define MCP_RXF2EID0	0x0B 
#define MCP_BFPCTRL		0x0C 
#define MCP_TXRTSCTRL	0x0D 
#define MCP_CANSTAT		0x0E 
#define MCP_CANCTRL		0x0F 
#define MCP_RXF3SIDH	0x10 
#define MCP_RXF3SIDL	0x11 
#define MCP_RXF3EID8	0x12 
#define MCP_RXF3EID0	0x13 
#define MCP_RXF4SIDH	0x14 
#define MCP_RXF4SIDL	0x15 
#define MCP_RXF4EID8	0x16 
#define MCP_RXF4EID0	0x17 
#define MCP_RXF5SIDH	0x18 
#define MCP_RXF5SIDL	0x19 
#define MCP_RXF5EID8	0x1A 
#define MCP_RXF5EID0	0x1B 
#define MCP_TEC			0x1C 
#define MCP_REC			0x1D 
#define MCP_RXM0SIDH	0x20 
#define MCP_RXM0SIDL	0x21 
#define MCP_RXM0EID8	0x22 
#define MCP_RXM0EID0	0x23 
#define MCP_RXM1SIDH	0x24 
#define MCP_RXM1SIDL	0x25 
#define MCP_RXM1EID8	0x26 
#define MCP_RXM1EID0	0x27 
#define MCP_CNF3		0x28 
#define MCP_CNF2		0x29 
#define MCP_CNF1		0x2A 
#define MCP_CANINTE		0x2B 
#define MCP_CANINTF		0x2C 
#define MCP_EFLG		0x2D 
#define MCP_TXB0CTRL	0x30 
#define MCP_TXB1CTRL	0x40 
#define MCP_TXB2CTRL	0x50 
#define MCP_RXB0CTRL	0x60 
#define MCP_RXB0SIDH	0x61 
#define MCP_RXB1CTRL	0x70 
#define MCP_RXB1SIDH	0x71 
 

//INSTRUCTIONS
//
#define MCP_WRITE		0x02 
 
#define MCP_READ		0x03 
 
#define MCP_BITMOD		0x05 
  
#define MCP_RESET		0xC0 

// Load transmit buffer(from the TXBnSIDH)
#define MCP_LOAD_TX0	0x40 
#define MCP_LOAD_TX1	0x42 
#define MCP_LOAD_TX2	0x44 

// Request to send
#define MCP_RTS_TX0		0x81 
#define MCP_RTS_TX1		0x82 
#define MCP_RTS_TX2		0x84 
#define MCP_RTS_ALL		0x87 
 
 // Read receive buffer(from the RXBnSIDH register)
#define MCP_READ_RX0	0x90 
#define MCP_READ_RX1	0x94 

// Read status - gives important status
#define MCP_READ_STATUS	0xA0 

// Read the filter match,message type, buffer received
#define MCP_RX_STATUS	0xB0 


#define BASE_ID 0x120 // TODO - Yet to be finalised.

const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;

#define MESSAGE_LENGTH 8 // CAN messages can only be 8 bytes long and the first byte of these messages will be the node id.



class bootloader_module_canspi: public bootloader_module
{
	public:

		// Class types.
		
		enum message_id {RESET_REQUEST = BASE_ID, GET_INFO = BASE_ID + 1, WRITE_MEMORY = BASE_ID + 2, WRITE_DATA = BASE_ID + 3, 
						 READ_MEMORY = BASE_ID + 4, READ_DATA = BASE_ID + 5, ALERT_UPLOADER = 0x2FF};
		
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

		volatile message_info reception_message; // This will be updated by ISR(INT4_vect)
		message_info transmission_message;

			// Class flags
		bool communication_started;
		bool ready_to_send_page;
		bool message_confirmation_success; 
		bool write_address_stored;
		
		volatile uint8_t pin_K0_state;// State of the INT pin from mcp2515

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
		 *	Procedure when a start_reset message is received. Will either reboot to the bootloader or the application.
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

extern bootloader_module_canspi module;

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif // __BOOTLOADER_MODULE_CANSPI_H__

// ALL DONE.
