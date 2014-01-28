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

#include "can_platform.hpp"

#define CLK_MHZ <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>	//Using the preprocessor template gets kind of ugly

typedef void (*voidFuncPtr)(void);

/********************* Forward declaration **************************/
class Can_tree;		//declared because otherwise the interface class cannot point to it
class Can_buffer;	
class Can_filter;
class Can_mask;

/************* Enumerations to represent CAN status ********************/
enum CAN_RATE {CAN_100K, CAN_125K, CAN_200K, CAN_250K, CAN_500K, CAN_1000K};
enum CAN_MODE {CAN_NORMAL, CAN_LISTEN};
enum CAN_BUF_MODE {CAN_OBJ_RX, CAN_OBJ_TX, CAN_OBJ_RXB, CAN_OBJ_DISABLE};
enum CAN_BUF_STAT {BUF_NOT_COMPLETED, BUF_TX_COMPLETED, BUF_RX_COMPLETED, BUF_RX_COMPLETED_DLCW, BUF_ACK_ERROR, BUF_FORM_ERROR, BUF_CRC_ERROR, BUF_STUFF_ERROR, BUF_BIT_ERROR, BUF_PENDING, BUF_NOT_REACHED, BUF_DISABLE};

enum CAN_INT_NAME {CAN_BUS_OFF, CAN_RX_COMPLETE, CAN_TX_COMPLETE, CAN_GEN_ERROR, CAN_TIME_OVERRUN, NB_INT};

/************** ENUMERATIONS TO REPRESENT HARDWARE *********************/
//Linux has no well-defined controller definition but have one anyways to fit the interface
#ifdef __linux__
enum CAN_CTRL {CAN_0, NB_CTRL};
#endif

// The linux has no well-defined message objects but have as many as I can to fit the interface
#ifdef __linux__
enum CAN_BUF { BUF_0 };
enum CAN_FIL { FIL_0 };
enum CAN_MSK { MSK_0 };
#endif //__Native_Linux__

typedef void (*Interrupt_fn)(Can_buffer&);

/********************* Struct definitions here ***********************/
/**
 * Struct to represent a Can frame
 */
typedef struct 
{
	uint32_t id;		///Up to 29 bits for extended identifier
	uint8_t dlc;		///Data length identifier, uses 4 bits
	uint8_t data[8];	///8 bytes of payload data
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
		 * Store an arbitrary address in its field so it can reference itself via registers.
		 * 
		 * @param   buf_num  The number to assign to this buffer.
		 * @return  Nothing.
		 */
		void set_number(uint8_t buf_num);
		
		/** 
		 * Get the arbitrary registry reference address of this buffer
		 * 
		 * @param    Nothing.
		 * @return   Address of this buffer
		 */
		uint8_t get_number(void);
		
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
		* Sets the mode of the object.  This may not work, depending on 
		* whether the CAN hardware offers support for multimode objects.
		*
		* @param	mode	The mode to set the object to.
		* @return   Flag indicating whether operation was successful.
		*/
		bool set_mode(CAN_BUF_MODE mode);
		
		/**
		* Returns the current status of the object.
		*
		* @param	Nothing.
		* @return	The current status of the buffer (one of possible CAN_BUF_STATs).
		*/
		CAN_BUF_STAT get_status(void);
		
		/**
		 * Read what is in the buffer (moves it away from buffer and
		 * into memory).
		 * 
		 * @param   Nothing.
		 * @return  The message contained in buffer.
		 */
		Can_message read(void);
		 
		 /**
		  * Write message to buffer
		  * 
		  * @param   msg    Message to write to the buffer.
		  * @return  Nothing.
		  */
		void write(Can_message msg);
		
		/**
		 * Reset status register of buffer
		 * 
		 * @param    Nothing.
		 * @return   Nothing.
		 */
		void clear_status(void);
		
		/**
		 * Enables interrupt on the buffer
		 * 
		 * @param    Nothing.
		 * @return   Nothing.
		 */
		void enable_interrupt(void);
		
		/**
		 * Disables interrupt on the buffer
		 * 
		 * @param    Nothing
		 * @return   Nothing
		 */
		void disable_interrupt(void);
		
		/**
		* Attaches a handler to a particular interrupt event for object based
		* interrupts. Original interrupt will be overwritten if a handler already
		* exists (use test interrupt to see what interrupt conditions are used).
		*
		* @param	interrupt	The interrupt condition to attach the handler for.
		* @param	userFunc	The handler for this interrupt condition.
		*/
		void attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void));
		
		/**
		* Removes a handler for a specific object for a particular interrupt event.
		*
		* @param	interrupt	The interrupt condition to dettach the handler from.
		* @return	Nothing.	
		*/
		void detach_interrupt(CAN_INT_NAME interrupt);
		
		/**
		 * Boolean describing whether an interrupt handler is set for this condition
		 * on this buffer.
		 * 
		 * @param   interrupt   The MOb interrupt condition to test if enabled.
		 * @return              Flag indicating whether an interrupt handler is set for this condition.
		 *
		 */
		bool test_interrupt(CAN_INT_NAME interrupt);
		
	private:
	// METHODS

		
	// FIELDS
		uint8_t buf_no;		//constructor needs this value
		CAN_BUF_MODE mode;	//current mode of the buffer
};

/**
 * Filter class, this object can program filter values
 */
class Can_filter
{
	public:
	//METHODS		 
		/**
		 * Store an arbitrary address in its field so it can reference itself via registers.
		 * 
		 * @param   fil_num    The number to assign to this filter.
		 * @return  Nothing.
		 */
		 void set_number(uint8_t fil_num);
		
		/**
		 * Returns buffer this filter is linked to.
		 * 
		 * @param   Nothing.
		 * @return  Pointer to buffer linked to this filter.
		 */
		 Can_buffer* get_buffer(void);
		 
		/**
		 * Returns whether filter can be re-assigned to a different 
		 * buffer.
		 * 
		 * @param   Nothing.
		 * @return  Nothing.
		 */
		 bool get_routable(void);
		 
		/**
		 * Sets the buffer linked to this filter
		 * 
		 * @param   buffer   Buffer to link this filter to.
		 * @return  Nothing.
		 */
		 void set_buffer(Can_buffer* buffer);
		 
		/**
		 * Returns the mask this is linked to
		 * 
		 * @param	Nothing.
		 * @return  Pointer to the mask linked to this filter
		 */
		 Can_mask* get_mask(void);
		 
		/**
		 * Sets the mask linked to this buffer
		 * 
		 * @param    mask    The mask to link this filter to.
		 * @return   Nothing.
		 */
		 void set_mask(Can_mask* mask);
		 
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
		* @param    RTR		Setting of the RTR bit.
		* 
		* @return	Nothing.
		*/
		 void set_filter_val(uint32_t filter, bool RTR);
		
		 
	
	private:
	//METHODS

	
	//FIELDS
		uint8_t fil_no;	//constructor needs this value
		Can_buffer* buffer_link;
		Can_mask* mask_link;
		uint32_t filter_data;				
};

/**
 * Filter class, this object can program mask values
 */
class Can_mask
{
	public:
		/**
		 * Store an arbitrary address in its field so it can reference itself via registers.
		 * 
		 * @param    msk_num    The number to assign to this mask    
		 * @return   Nothing
		 */
		void set_number(uint8_t msk_num);
		
		/**
		 * Get the value this mask currently has
		 * 
		 * @param    Nothing
		 * @return   The current mask value
		 */
		uint32_t get_mask_val(void);
		
		/**
		 * Set the value of this mask
		 * 
		 * @param    mask    New value for this mask
		 * @return   Nothing
		 */
		void set_mask_val(uint32_t mask, bool RTR);
		
	private:
		uint8_t msk_no;
		uint32_t mask_data;	
};


/**
 * Interface class for a CAN controller
 */
class Can 
{
	public:
	// METHODS
		/**
		 * Binds the interface with the hardware implementation.
		 */
		static Can bind(CAN_CTRL controller);
		
		/**
		 * Initializes controller for first use. Sets the baud rate for
		 * the controller.
		 * 
		 * @param    rate   Baud rate of bus to use.
		 * @return 	 Whether bus was successfully initialized.
		 */
		bool initialise(CAN_RATE rate);
		
		/**
		 * Set the buffer transfer direction e.g. receive, trasmit 
		 * or disabled the buffer.
		 * 
		 * @param    buffer_name    Name of the buffer to set (use the enums)..
		 * @param    mode           Mode to set buffer to.
		 * @return   Nothing.
		 */
		void set_buffer_mode(CAN_BUF buffer_name, CAN_BUF_MODE mode);
		
	    /**
	     * Reads message from buffer specified.
	     * 
	     * @param    buffer_name    Name of the buffer to be read (use the enums).
	     * @return   The message inside the buffer.
	     */
	    Can_message read(CAN_BUF buffer_name);
	    
	    /**
	     * Transmits message from the buffer specified. Note the tranmission flag 
	     * is not cleared in this function. Uses extended identifier.
	     * 
	     * @param    buffer_name    Name of the buffer to be used for sending (use the enums).
	     * @param    message		The message to send (struct with identifer and data length).
	     * @return   Flag indicating whether operation was successful.
	     */
	    bool transmit(CAN_BUF buffer_name, Can_message msg);
	   
	   /**
	    * Determine the status of a buffer.
	    * 
	    * @param     buffer_name	Name of the buffer to be asssessed (use the enums).
	    * @return 	 Status of the buffer.
	    */
	    CAN_BUF_STAT get_buffer_status(CAN_BUF buffer_name);
	    
	   /**
	    * Clear the status register of selected buffer.
	    * 
	    * @param     buffer_name    Name of the buffer to clear status (use the enums).
	    * @return    Nothing.
	    */
	    void clear_buffer_status(CAN_BUF buffer_name);
	    
	   /**
	    * Set the value of the selected filter.
	    * 
	    * @param     filter_name	Name of filter to be modified.
	    * @param     filter_val		Value to be written to filter.
	    * @param     RTR			Setting of the RTR filter bit.	
	    */
	    void set_filter_val(CAN_FIL filter_name, uint32_t filter_val, bool RTR);
	    
	   /**
	    * Retrieve the value the selected filter has stored
	    * 
	    * @param	 filter_name    Name of filter retrieve value.
	    * @return    The value stored in the filter.
	    */
	    uint32_t get_filter_val(CAN_FIL filter_name);
	    
	   /**
	    * Set the value of the selected mask.
	    * 
	    * @param     mask_name  	Name of the mask to be modified.
	    * @param     mask_val		Value to be written to the mask.
	    * @param     RTR			Setting of the RTR mask bit.
	    */
	    void set_mask_val(CAN_MSK mask_name, uint32_t mask_val, bool RTR);
	    
	   /**
	    * Retreive the value the selected mask has stored
	    * 
	    * @param     mask_name      Name of the mask to retrieve value.
	    * @return    The value stored in the mask.
	    */
	    uint32_t get_mask_val(CAN_MSK mask_name);
	    
	   /**
	    * Master interrupt enable.
	    * 
	    * @param	 Nothing.
	    * @return    Nothing.
	    */
	    void enable_interrupts(void);
	    
	   /**
	    * Master interrupt disable.
	    * 
	    * @param	 Nothing.
	    * @return    Nothing.
	    */
	    void disable_interrupts(void);
	    
	   /**
	    * Enable interrupts on selected buffer.
	    * 
	    * @param     buffer_name	Name of the buffer to have interrupt enabled.
	    * @return	 Nothing.
	    */
	    void enable_buffer_interrupt(CAN_BUF buffer_name);
	    
	   /**
	    * Disable interrupts on selected buffer.
	    * 
	    * @param     buffer_name    Name of the buffer to have interrupt disabled.
	    * @return    Nothing.
	    */
	    void disable_buffer_interrupt(CAN_BUF buffer_name);
	    
	   /**
	    * Attach interrupt handler to selected buffer based event.
	    * 
	    * @param     buffer_name	Name of buffer to attach interrupt to.
	    * @param     interrupt		The interrupt event to attach the handler to.
	    * @param     userFunc 		The handler for this interrupt condition.
	    * @return    Nothing.
	    */
	    void attach_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt, void (*userFunc)(void));
	    
	   /**
	    * Attach interrupt handler to channel based event.
	    * 
	    * @param     interrupt		The interrupt event to attach the handler to.
	    * @param     userFunc		The handler for this interrupt event.
	    * @return    Nothing.
	    */
	    void attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void));
	    
	   /**
	    * Detach interrupt on selected buffer
	    * 
	    * @param     buffer_name	Name of buffer to detach interrupt from.
	    * @param     interrupt		The interrupt event to detach the handler from.
	    * @return    Nothing.
	    */
	    void detach_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt);
	    
	   /**
	    * Detach interrupt on CAN channel
	    * 
	    * @param     interrupt		The interrupt event to detach the handler from.
	    * @return    Nothing.
	    */
	    void detach_interrupt(CAN_INT_NAME interrupt);
	    
	   /**
	    * Test whether existing handler is attached to an event on this buffer
	    * 
	    * @param     buffer_name    The name of buffer to test interrupt.
	    * @param     interrupt		The interrupt event to test.
	    * @return    Flag indicating whether interrupt event has an existing handler.
	    */
	    bool test_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt);
	    
	   /**
	    * Test whether existing handler is attached to an event on the channel
	    * 
	    * @param     interrupt		The interrupt event to test.
	    * @return    Flag indicating whether interrupt event has an existing handler.
	    */
	    bool test_interrupt(CAN_INT_NAME interrupt);
	    
	   /**
	    * Return the name of the buffer that triggered the current interrupt. 
	    * Should only call inside handler function as return value may not be
	    * valid outside of a handler
	    * 
	    * @param     Nothing.
	    * @return    Name of the buffer that triggered the interrupt.
	    */
	    CAN_BUF get_interrrupted_buffer(void);
	    
	   /**
	    * Clear interrupt flags of controller based interrupts.
	    * 
	    * @param	 interrupt      The interrupt event flag to clear.
	    * @return    Nothing.
	    */
	    void clear_controller_interrupts(CAN_INT_NAME interrupt);
    
	
	private:
		Can(Can_tree* imp);	//called by link function
		Can_tree* Can_controller;
		
};

#endif
