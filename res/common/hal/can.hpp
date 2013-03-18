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

/**
 *
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		can.hpp
 *  A header file for the CAN Module of the HAL.
 * 
 *  @brief 
 *  This is the header file which matches can.cpp.  Implements various functions relating to CAN, transmission
 *  and receiving of messages.
 * 
 *  @author		Paul Davey
 *
 *  @date		1-02-2013
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2013  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  @section Description
 *
 * A class for the CAN module of the HAL. Implements various functions relating to CAN 
 *  initialisation, transmission and receiving of messages.
 */

// Only include this header file once.
#ifndef __CAN_H__
#define __CAN_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the semaphore library
#include "semaphore.hpp"

// Include the hal library.
#include "hal/hal.hpp"

#include "can_platform.hpp"

/*
 * CAN peripheral organisation on different hardware:
 * 
 * AVR
 * 
 *  The AVR CAN module has a number of message object buffers, each buffer has its own mask and filter.
 *    - N buffers.
 *    - N acceptance filters. each of the Mask and Filter variety.
 *    - buffers and filters have 1-1 correspondance and this cannot be changed.
 *    - buffers are used for both transmit and receive (in transmit mode the same data as the filter is used for the message ID)
 * 
 *    - One interrupt shared by the whole CAN peripheral, there are flags for module wide sitations and ones in the buffer concerned if such an interrupt is triggered.
 * 
 * MCP2515
 * 
 *  The MCP 2515 has two receive buffers, each buffer has a mask associated with it and a number of filters. It also has three transmit buffers.
 *    - 2 Recv buffers, 3 Transmit buffers, separate.
 *    - 2 Masks (1 per buffer), 6 filters (2 on one buffer, 4 on the other buffer) Masks affect all filters on that buffer.
 * 
 *    - One interrupt line used by the controller chip, an SPI transfer must be used to query status after the interrupt.
 * 
 * STM32
 * 
 * The STM32 CAN peripheral has FIFO buffers for transmission and reception, it also has a bank of filters that are somewhat customisable.
 *   - 1 transmit FIFO with 3 slots.
 *   - 2 receive FIFOs each with 3 slots.
 *   - atleast 14 filter banks (28 in the connectivity line, shared between the two CAN controllers)
 *   - Filters can be configured to be Mask + filter or exact ID filters.
 *   - Filters are assigned to one of the two receive FIFOs.
 *   
 *   - Multiple interrupts, one for each receive FIFO, one for transmission and one for status changes and error conditions.
 * 
 * Given the differences in filtering schemes the interface has been chosen to allow different definitions of various structures and enums to account for the different number of filters and behaviour of filters.
 * Not all of the interface functions will do something on all platforms.
 * For example the set_obj_for_filter will not work on AVR or MCP platforms since these have static relationships with the buffers on these platforms,
 *  the get_object_for_filter function will however work on all platforms.
 */

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum Can_rate {CAN_100K, CAN_125K, CAN_200K, CAN_250K, CAN_500K, CAN_1000K};

enum Can_mode {CAN_NORMAL, CAN_LISTEN};

enum Can_obj_mode { RECEIVE, TRANSMIT };

enum Interrupt_name { TX_ERROR, TX_COMPLETE, RX_ERROR, RX_COMPLETE, RX_OVERRUN };

typedef void (*Interrupt_fn)(can_object&);

struct CAN_message
{
	uint32_t id;
	uint8_t dlc;
	uint8_t data[8];
};

// FORWARD DEFINE PRIVATE PROTOTYPES.


// DEFINE PUBLIC CLASSES.

/**
 * @class Can
 * 
 * Implements various functions relating to CAN initialisation, transmission
 * and receiving of data.
 * 
 */
class Can
{
	public:
		// Functions.
		
		/**
		 * Initialises the SPI interface with the desired Master/Slave parameters and configures the
		 * relevant GPIO.
		 * 
		 * @param  configuration	Configuration for SPI interface (master/slave)
		 * @return 0 for success, -1 for error.
		 */
		int8_t initialise(Can_rate rate, Can_mode mode);
		
		/**
		 * Enables the CAN related interrupts.
		 */
		void enable_interrupts();
		 
		/**
		 * Disables the CAN related interrupts.
		 */
		void disable_interrupt();
		 
		/**
		 * Attaches a handler to a particular interrupt event for a specific object.
		 *
		 * @param interrupt		The interrupt condition to attach the handler for.
		 * @param object		The CAN message object to attach the handler for.
		 * @param handler		The handler for this interrupt condition.
		 * @return Nothing.
		 */
		void attach_interrupt(Interrupt_name interrupt, Can_object object, Interrupt_fn handler);

		/**
		 * Removes a handler for a specific object for a particular interrupt event.
		 *
		 * @param interrupt		The interrupt condition to attach the handler from.
		 * @param object		The CAN message object to detach the handler from.
		 * @return Nothing.
		 */
		void detach_interrupt(Interrupt_name interrupt, Can_object object);

		/**
		 * Attaches a handler to a particular interrupt event that will be used if a handler has not been given for the object that caused the event.
		 *
		 * @param interrupt		The interrupt condition to attach the handler for.
		 * @param handler		The handler for this interrupt condition
		 * @return Nothing.
		 */
		void attach_interrupt(Interrupt_name interrupt, Interrupt_fn handler);

		/**
		 * Removes the default handler for a particular interrupt event.
		 *
		 * @param interrupt		The interrupt condition to attach the handler from.
		 * @param object		The CAN message object to detach the handler from.
		 * @return Nothing.
		 */
		void detach_interrupt(Interrupt_name);

		/**
		 * Function to get the status of the CAN controller.
		 *
		 * @param  Nothing.
		 * @return A Can_status struct indicating the current status of the CAN controller.
		 */
		Can_status get_status();
		
		/**
		 * Function to get the status of a particular message object in the CAN controller.
		 *
		 * @param  object	The object to get the status of.
		 * @return A Can_status struct indicating the current status of the message object.
		 */
		Can_obj_status get_status(Can_object object);
		
		/**
		 * Function to send a can message using a particular object.
		 *
		 * @param  obj	The object to send the message with.
		 * @param  msg	The message to send.
		 * @return Nothing.
		 */
		void transmit(Can_object obj, Can_message msg);

		/**
		 * Function to check if a CAN object is ready for use.
		 *
		 * @param  obj	The object to send the message with.
		 * @return True if the object is ready for use, false if not.
		 */
		bool check_ready(Can_object obj);
		
		/**
		 * Function to read a message out of an object, the object must be ready.
		 *
		 * @param  obj	The object to read the message from.
		 * @return The message in the object.
		 */
		Can_message read_object(Can_object obj);
		
		/**
		 * Function to configure a receive filter.
		 * 
		 * @param filter	The filter to configure.
		 * @param data		The platform specific data for initialising the filter.
		 * @return Nothing.
		 */
		void configure_rx_filter(Can_filter filter, Can_filter_data data);

		/**
		 * Function to retrieve the object associated with a particular receive filter.
		 * 
		 * @param filter	The filter to retrieve the object for.
		 * @return The object being retrieved.
		 */
		Can_object get_obj_from_filter(Can_filters filter);
		
		/**
		 * Function to set which object is associated with a receive filter.
		 * 
		 * @param filter	The filter to set the object for.
		 * @param obj		The object to associate with this filter.
		 * @return Nothing.
		 */
		void set_obj_for_filter(Can_filters filter, Can_object obj);
		
		/**
		 * Function to configure the mode of a CAN message object.
		 * 
		 * @param obj	The object to configure.
		 * @param mode	The mode to set the object to.
		 * @return Nothing.
		 */
		void set_obj_mode(Can_object obj, Can_obj_mode mode);

		/**
		 * Function to free the CAN instance when it goes out of scope.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		~Can(void);

		/** 
		 * Allows access to the CAN interface to be relinquished and reused elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);

		/**
		 * Allows a process to request access to a CAN instance and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  can_number	The number of a CAN that is desired.
		 * @return A CAN instance.
		 */
		static Can grab(Can_number can_number);
		
		/**
		 * Allows a process to request access to a CAN instance and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  spi_inst	The spi instance for the bus which the SPI-CAN controller is attached to.
		 * @param  int_pin	The gpio pin which is attached to the SPI-CAN controllers interrupt output.
		 * @return A CAN instance.
		 */
		static Can grab(spi spi_inst, gpio_pin int_pin);

	private:
		// Functions.
		
		Can(void);	// Poisoned.

		Can operator =(Can const&);	// Poisoned.

		// Fields.

};
	  


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__CAN_H__*/

// ALL DONE.
