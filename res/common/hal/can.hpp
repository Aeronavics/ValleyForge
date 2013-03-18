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
 * A class for the CAN module of the HAL. Implements various functions relating to CAN hardware 
 * initialisation, transmission and receiving of data.
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
#include "hal/semaphore.hpp"

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

// If we are offering support for the MCP2515, then we need GPIO and SPI functionality.
#define HAL_CANSPI_ENABLE 0
#if HAL_CANSPI_ENABLE
#include "hal/gpio.hpp"
#include "hal/spi.hpp"
#endif

// FORWARD DEFINE PROTOTYPES.

class Can_object;
class Can_filter;

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum Can_rate {CAN_100K, CAN_125K, CAN_200K, CAN_250K, CAN_500K, CAN_1000K};

enum Can_mode {CAN_NORMAL, CAN_LISTEN};

enum Can_object_mode {CAN_OBJ_RX, CAN_OBJ_TX};

enum Can_interrupt_name {CAN_TX_ERROR, CAN_TX_COMPLETE, CAN_RX_ERROR, CAN_RX_COMPLETE, CAN_RX_OVERRUN};

enum Can_command_response {CAN_ACK, CAN_NAK};

typedef void (*Interrupt_fn)(Can_object&);

struct Can_message
{
	uint32_t id;
	uint8_t dlc;
	uint8_t data[8];
};

// TODO - These may need to move to implementation specific headers since they may change between platforms, and this way is a bit ugly.

// DEFINE DEVICE SPECIFIC PUBLIC TYPES AND ENUMERATIONS.

#ifdef __AVR_AT90CAN128__
enum Can_channel {CAN_0};
#endif // __AVR_AT90CAN128__
#ifdef __AVR_ATmega64M1__
enum Can_channel {CAN_0};
#endif // __AVR_ATmega64M1__

struct Can_filter_data;

struct Can_object_status;

struct Can_status;

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

/**
* @class Can_object
*
* Implements and abstraction of a hardware 'message object' in a CAN interface controller.  Message objects are essentially FIFO buffers, of size
* one or greater, into which CAN messages are received, or from which CAN messages are transmitted.  A specific CAN interface may have multiple
* message objects, some of which may be dedicated for either TX or RX operations (whilst others may be configurable).
*
* Because each message object is an abstraction of physical hardware in the corresponding interface, the class cannot be instantiated by the user.
* A set of instances is provided by the interface to match the available hardware.
*
*/
class Can_object
{
	public:
		// Methods.

		/**
		* Returns the mode of the object.
		*
		* @param	Nothing.
		* @return	The mode of the object.
		*/
		Can_object_mode get_mode(void);

		/**
		* Returns whether or not the object can change mode.
		*
		* @param	Nothing.
		* @return	Flag indicating whether the object's mode can be modified.
		*/
		bool get_multimode(void);

		/**
		* Sets the mode of the object.  This may not work, depending on whether the CAN hardware offers support for multimode objects.
		*
		* @param	mode	The mode to set the object to.
		* @return	Flag indicating whether the operation was successful.
		*/
		bool set_mode(Can_object_mode);

		/**
		* Returns the current status of the object.
		*
		* @param	Nothing.
		* @return	The current status of the object.
		*/
		Can_object_status get_status(void);

		// Fields.

	private:
		// Methods.

		Can_object(void);

		Can_object(Can_object const&);			// Poisoned.

		Can_object operator =(Can_object const&);	// Poisoned.

		// Fields.
};

/**
* @class Can_filter
*
* Implements an abstraction of a hardware filter/mask in a CAN interface controller.  Filter/masks are used by a CAN interface to route incoming
* CAN messages into the appropriate RX 'message object', or to ignore message which are not of interest.  A specific CAN interface may have
* multiple filter/masks, which may be configured by the user.
*
* Because each filter instance is an abstraction of physical hardware in the corresponding interface, the class cannot be instantiated by the user.
* A set of instances is provided by the interface to match the available hardware.
*
*/
class Can_filter
{
	public:
		// Methods.

		/**
		* Returns the CAN message object which the filter is currently routing into.
		*
		* @param	Nothing.
		* @return	The message object which the filter is routing into.
		*/
		Can_object get_object(void);

		/**
		* Returns whether or not the filter can change which CAN message object it is routing into.
		*
		* @param	Nothing.
		* @return	Flag indicating whether the filters message object can be modified.
		*/
		bool get_object_routable(void);

		/**
		* Sets the CAN message object which the filter should route into.  This may not work, depending on whether the CAN hardware offers
		* support for changing filter routing, and whether the specified message object is a suitable routing target for this filter.
		*
		* @param	object	The CAN message object which the filter should route into.
		* @return	Flag indicating whether the operation was successful.
		*/
		bool set_object(Can_object);

		/**
		* Gets the current mask value being used by the hardware filter/mask.
		*
		* @param	Nothing.
		* @return	The current mask value.
		*/
		uint32_t get_mask(void);

		/**
		* Sets the mask value being used by the hardware filter/mask.
		*
		* NOTE - Not all the bits of the mask may be used, since CAN IDs are typically only 11 or 29 bits long.  This is HW specific.
		*
		* @param	mask	The new value for the filter mask.
		* @return	Nothing.
		*/
		void set_mask(uint32_t mask);

		/**
		* Gets the current filter value being used by the hardware filter/mask.
		*
		* @param	Nothing.
		* @return	The current filter value.
		*/
		uint32_t get_filter(void);

		/**
		* Sets the filter value being used by the hardware filter/mask.
		*
		* NOTE - Not all the bits of the filter may be used, since CAN IDs are typically only 11 or 29 bits long.  This is HW specific.
		*
		* @param	filter	The new value for the filter.
		* @return	Nothing.
		*/
		void set_filter(uint32_t filter);

		// Fields.

	private:
		// Methods.

		Can_filter(void);

		Can_filter(Can_filter const&);			// Poisoned.

		Can_filter operator =(Can_filter const&);	// Poisoned.		

		// Fields.
};

/**
* @class Can_tree
*
* A class which holds abstractions of the hardware filter/masks and message objects provided by a CAN interface.
*
* Because each tree represents abstractions of physical hardware in the corresponding interface, the class cannot be instantiated by the user.
*
*/
class Can_tree
{
	public:
		// Methods.

		// Fields.

	private:
		// Methods.

		Can_tree(void);

		Can_tree(Can_tree const&);		// Poisoned.

		Can_tree operator =(Can_tree const&);	// Poisoned.		

		// Fields.
};

#if defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__)
/**
* @class Can_tree_native
*
* A class which holds abstractions of the hardware filter/masks and message objects provided by the internal CAN hardware of the target.
*
*/
class Can_tree_native : Can_tree
{
	public:
		// Methods.

		// Fields.

		#if defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__)
		Can_filter filter_0;
		Can_filter filter_1;
		Can_filter filter_2;
		Can_object object_0;
		Can_object object_1;
		Can_object object_2;
		#endif // __AVR_AT90CAN128__ || __AVR_ATmega64M1__

	private:
		// Methods.

		Can_tree_native(void);

		Can_tree_native(Can_tree_native const&);		// Poisoned.

		Can_tree_native operator =(Can_tree_native const&);	// Poisoned.		

		// Fields.
};
#endif // __AVR_AT90CAN128__ || __AVR_ATmega64M1__

#if HAL_CANSPI_ENABLE
/**
* @class Can_tree_spi
*
* A class which holds abstractions of the hardware filter/masks and message objects provided by the internal CAN hardware of the target.
*
*/
class Can_tree_native : Can_tree
{
	public:
		// Methods.

		// Fields.

		Can_filter can_0_filter_0;
		Can_filter can_0_filter_1;
		Can_object rx_object_0;
		Can_object rx_object_1;
		Can_object tx_object_0;
		Can_object tx_object_1;
		Can_object tx_object_2;

	private:
		// Methods.

		Can_tree_native(void);

		Can_tree_native(Can_tree_native const&);		// Poisoned.

		Can_tree_native operator =(Can_tree_native const&);	// Poisoned.		

		// Fields.
};
#endif // HAL_CANSPI_ENABLE

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
		* Returns the tree of filters/masks and message objects associated with this CAN interface.
		*
		* @param	Nothing.
		* @returns	A Can_tree representing the filters and objects for this particular interface.
		*/
		Can_tree get_tree(void);

		/**
		* Initialises the CAN interface with the desired configuration and also configures any relevant GPIO.
		* 
		* @param  	rate	Bus rate for the CAN interface.
		* @param	mode	The operating mode for the CAN interface.
		* @return 	Response to attempting to initialise the device.
		*/
		Can_command_response initialise(Can_rate rate, Can_mode mode);
		
		/**
		* Enables CAN related interrupts.
		*
		* @param	Nothing.
		* @return	Nothing.
		*/
		void enable_interrupts(void);
		 
		/**
		* Disables CAN related interrupts.
		*
		* @param	Nothing.
		* @return	Nothing.
		*/
		void disable_interrupt(void);
		 
		/**
		* Attaches a handler to a particular interrupt event for a specific object.  If an interrupt handler is already attached to the
		* particular interrupt condition specified, the old handler will be replaced with the new handler.
		*
		* @param	interrupt	The interrupt condition to attach the handler for.
		* @param	object		The CAN message object to attach the handler for.
		* @param	handler		The handler for this interrupt condition.
		* @return	Nothing.
		*/
		void attach_interrupt(Can_interrupt_name interrupt, Can_object object, Interrupt_fn handler);

		/**
		* Attaches a handler to a particular interrupt event that will be used if a handler has not been specified for the CAN object
		* that caused the event.  If an interrupt handler is already attached to the particular interrupt condition specified, the old
		* handler will be replaced with the new handler.
		*
		* @param	interrupt	The interrupt condition to attach the handler for.
		* @param	handler		The handler for this interrupt condition.
		* @return	Nothing.
		*/
		void attach_interrupt(Can_interrupt_name interrupt, Interrupt_fn handler);

		/**
		* Removes a handler for a specific object for a particular interrupt event.
		*
		* @param	interrupt	The interrupt condition to attach the handler from.
		* @param	object		The CAN message object to detach the handler from.
		* @return	Nothing.	
		*/
		void detach_interrupt(Can_interrupt_name interrupt, Can_object object);

		/**
		 * Removes the default handler for a particular interrupt event.
		 *
		 * @param interrupt		The interrupt condition to attach the handler from.
		 * @param object		The CAN message object to detach the handler from.
		 * @return Nothing.
		 */
		void detach_interrupt(Can_interrupt_name);

		/**
		* Function to get the status of the CAN controller.
		*
		* @param	Nothing.
		* @return	Struct indicating the current status of the CAN controller.
		*/
		Can_status get_status();
		
		/**
		* Function to send a CAN message using a particular object.  If this object is not configured as a TX object, this will fail.
		*
		* @param	obj	The CAN object to send the message with.
		* @param	msg	The message to send.
		* @return	Nothing.
		*/
		void transmit(Can_object obj, Can_message msg);

		/**
		* Function to check if a CAN object is ready for use.
		*
		* @param	obj	The object to test for readiness.
		* @return	Flag indicating if the specified CAN object is ready for use.
		*/
		bool check_ready(Can_object obj);
		
		/**
		* Function to read a message out of an object.  The object must be ready for this to suceed.
		*
		* @param  obj	The object to read the message from.
		* @return The message in the object.
		*/
		Can_message read_object(Can_object obj);

		/**
		* Function to free the CAN instance when it goes out of scope.
		*
		* @param	Nothing.
		* @return	Nothing.
		*/
		~Can(void);

		/** 
		* Allows access to the CAN interface to be relinquished and reused elsewhere.
		*
		* @param	Nothing.
		* @return	Nothing.
		*/
		void vacate(void);

#if defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__)
		/**
		* Allows a process to request access to a CAN instance and manages the semaphore
		* indicating whether access has been granted or not.
		*
		* @param	can_channel	The channel identifier of the CAN peripheral that is desired.
		* @return	A CAN instance.
		*/
		static Can grab(Can_channel can_channel);
#endif // __AVR_AT90CAN128__ || __AVR_ATmega64M1__ 
		
#if HAL_CANSPI_ENABLE
		/**
		* Allows a process to request access to a CAN instance and manages the semaphore
		* indicating whether access has been granted or not.
		*
		* @param	spi_inst	The spi instance for the bus which the SPI-CAN controller is attached to.
		* @param	int_pin		The gpio pin which is attached to the SPI-CAN controllers interrupt output.
		* @return	A CAN instance.
		*/
		static Can grab(spi& spi_inst, gpio_pin& int_pin);
#endif // HAL_CANSPI_ENABLE

	private:
		// Functions.
		
		Can(void);

		Can(Can const&);		// Poisoned.

		Can operator =(Can const&);	// Poisoned.

		// Fields.
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__CAN_H__*/

// ALL DONE.
