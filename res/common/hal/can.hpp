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
 *  @author		Paul Davey & George Xian
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

// Include the hal library.
#include "hal/hal.hpp"


/*
 * CAN peripheral organisation on different hardware:
 * 
 * AVR
 * 
 *  The AVR uses a full CAN controller. It has a number of message objects each has its own buffer, mask and filter
 *    - AT90CAN128 has 15MOb and the Atmega64M1 has 6MOb
 *    - Each MOb has a fixed connection to its buffer and filter
 *    - MOb are used for both transmit and receive (in transmit mode the same data as the filter is used for the message ID)
 * 
 *    - One interrupt shared by the whole CAN peripheral, there are flags for module wide sitations and ones in the buffer concerned if such an interrupt is triggered.
 * 
 * MCP2515
 * 
 *  The MCP 2515 has two receive buffers, each buffer has a mask associated with it and a number of filters. It also has three transmit buffers.
 *    - 2 Recv buffers, 3 Transmit buffers, separate.
 *    - 2 Masks (1 per buffer), 6 filters (2 on one buffer, 4 on the other buffer) Masks affect all filters on that buffer.
 * 
 *    - One interrupt line used by the controller chip, an SPI transfer must be used to query status after the interrupt
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
#define HAL_CANSPI_ENABLE false
#if HAL_CANSPI_ENABLE
	#include "hal/gpio.hpp"
	#include "hal/spi.hpp"
#endif

#define CLK_MHZ <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>	//Using the preprocessor template gets kind of ugly

/********************* Forward declaration **************************/
class Can_tree;		//declared because otherwise the interface class cannot point to it
class Can_buffer;	//declared so typedef will work at top

/************* Enumerations to represent CAN status ********************/
enum CAN_RATE {CAN_100K, CAN_125K, CAN_200K, CAN_250K, CAN_500K, CAN_1000K};
enum CAN_MODE {CAN_NORMAL, CAN_LISTEN};
enum CAN_BUF_MODE {CAN_OBJ_RX, CAN_OBJ_TX};
enum CAN_BUF_STAT {BUF_NOT_COMPLETE, BUF_TX_COMPLETED, BUF_RX_COMPLETED, BUF_RX_COMPLETED_DLCW, BUF_ACK_ERROR, BUF_FORM_ERROR, BUF_CRC_ERROR, BUF_STUFF_ERROR, BUF_BIT_ERROR, BUF_PENDING, BUF_NOT_REACHED, BUF_DISABLE};

enum CAN_INT_NAME {CAN_TX_ERROR, CAN_TX_COMPLETE, CAN_RX_ERROR, CAN_RX_COMPLETE, CAN_RX_OVERRUN};

/************** ENUMERATIONS TO REPRESENT HARDWARE *********************/
//AVRs only have 1 CAN controller
#if (defined(__AVR_ATmega64M1__)) || (defined( __AVR_AT90CAN128__))
enum CAN_CTRL {CAN_0, NB_CTRL};

// This needs to be defined to hold the relevent data for a filter on this platform, on the AVR this is a 32 bit ID and a 32 bit mask,
// with defined bit positions for the extended frame flag and the remote transmit flag.
typedef struct 
{
	uint32_t id;
	uint32_t mask;
} Can_filter_data;

#endif


// The ATMega64M1 has 6 message object
#ifdef __AVR_ATmega64M1__
enum CAN_BUF { OBJ_0, OBJ_1, OBJ_2, OBJ_3, OBJ_4, OBJ_5, NB_BUF };
enum CAN_FIL { FILTER_0, FILTER_1, FILTER_2, FILTER_3, FILTER_4, FILTER_5, NB_FIL };
#endif //__AVR_ATmega64M1__

// The AT90CAN128 has 15 message object
#ifdef __AVR_AT90CAN128__
enum CAN_BUF { OBJ_0, OBJ_1, OBJ_2, OBJ_3, OBJ_4, OBJ_5, OBJ_6, OBJ_7, OBJ_8, OBJ_9, OBJ_10, OBJ_11, OBJ_12, OBJ_13, OBJ_14, NB_BUF };
enum CAN_FIL { FILTER_0, FILTER_1, FILTER_2, FILTER_3, FILTER_4, FILTER_5, FILTER_6, FILTER_7, FILTER_8, FILTER_9, FILTER_10, FILTER_11, FILTER_12, FILTER_13, FILTER_14, NB_FIL };
#endif //__AVR_AT90CAN128__

typedef void (*Interrupt_fn)(Can_buffer&);


/********************* Struct definitions here ***********************/
typedef struct 
{
	uint32_t id;	//Up to 29 bits for extended identifier
	uint8_t dlc;	//Data length identifier, uses 4 bits
	uint8_t data[8];//8 bytes of actual data
} Can_message;


/********************* Class definitions here ************************/
/**
 * Buffer class, this object can read buffer data, trasmit data by writing
 * to transmit buffer and attach buffer based interrupts */
class Can_buffer
{
	public:
	// METHODS
		/**
		 * Store its address in its field so it can reference itself via registers
		 */
		void set_number(CAN_BUF buf_num);
		
		/**
		* Returns the mode of the object.
		*
		* @param	Nothing.
		* @return	The mode of the object.
		*/
		CAN_BUF_MODE get_mode(void);
		
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
		bool set_mode(CAN_BUF_MODE mode);
		
		/**
		* Returns the current status of the object.
		*
		* @param	Nothing.
		* @return	The current status of the object.
		*/
		CAN_BUF_STAT get_status(void);
		
		/**
		 * Read what is in the buffer (moves it away from buffer and
		 * into memory)
		 * 
		 * @return  The message contained in buffer
		 */
		Can_message read(void);
		 
		 /**
		  * Transmit message by writing to a buffer assigned for transmission
		  * 
		  * @param  Message to send
		  */
		void transmit(Can_message msg);
		
		/**
		 * Delete contents of buffer
		 */
		void clear(void);
		
		/**
		* Attaches a handler to a particular interrupt event for a specific object.  If an interrupt handler is already attached to the
		* particular interrupt condition specified, the old handler will be replaced with the new handler.
		*
		* @param	interrupt	The interrupt condition to attach the handler for.
		* @param	object		The CAN message object to attach the handler for.
		* @param	handler		The handler for this interrupt condition.
		* @return	Nothing.
		*/
		void attach_interrupt(CAN_INT_NAME interrupt, Interrupt_fn handler);
		
		/**
		* Removes a handler for a specific object for a particular interrupt event.
		*
		* @param	interrupt	The interrupt condition to attach the handler from.
		* @param	object		The CAN message object to detach the handler from.
		* @return	Nothing.	
		*/
		void detach_interrupt(CAN_INT_NAME interrupt);
		
		
	private:
	// METHODS

		
	// FIELDS
		CAN_BUF MOb_no;		//constructor needs this value
		CAN_BUF_MODE mode;
};

/**
 * Filter class, this object can program filter and mask values
 */
class Can_filter
{
	public:
	//METHODS		 
		/**
		 * Store its address in its field so it can reference itself via registers
		 */
		 void set_number(CAN_FIL fil_num);
		
		/**
		 * Returns buffer this is linked to
		 * 
		 * @return     pointer to buffer linked to this filter
		 */
		 Can_buffer* get_buffer(void);
		 
		/**
		 * Returns whether filter can be re-assigned to a different 
		 * buffer
		 */
		 bool get_routable(void);
		 
		/**
		 * Sets the buffer linked to this filter
		 * 
		 * @return Flag indicating whether its possible
		 */
		 bool set_buffer(Can_buffer* buffer);
		 
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
		uint32_t get_filter_val(void);
		
		/**
		* Sets the filter value being used by the hardware filter/mask.
		*
		* NOTE - Not all the bits of the filter may be used, since CAN IDs are typically only 11 or 29 bits long.  This is HW specific.
		*
		* @param	filter	The new value for the filter.
		* @return	Nothing.
		*/
		void set_filter_val(uint32_t filter);
		
		 
	
	private:
	//METHODS

	
	//FIELDS
		CAN_FIL fil_no;	//constructor needs this value
		// Which buffer does this filter affect (depending on hardware configuration, this can be optional)
		Can_buffer* buffer_link;
		Can_filter_data filter_data;						
		
};

/**
 * Interface class for a CAN controller
 */
class Can 
{
	public:
	// METHODS
		/**
		 * Links up the created instance with the hardware implementationn
		 */
		static Can link(CAN_CTRL controller);
		
		/**
		 * Initializes controller for first use. Clears all buffers and
		 * enables MObs
		 */
		void initialise(CAN_RATE rate);
		
	    /**
	     * Reads message from buffer specified
	     * 
	     * @param buffer_name   Name of the buffer to be read (use the enums)
	     */
	    Can_message read(CAN_BUF buffer_name);
	    
	    
    
	
	private:
		Can(Can_tree* imp);	//called by link function
		Can_tree* Can_controller;
};

#endif
