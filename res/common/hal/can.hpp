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

/**
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

// Only include this header file once.
#ifndef __CAN_H__
#define __CAN_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>
#include <stdint.h>

// Include the hal library.
#include "hal/hal.hpp"

// If we are offering support for the MCP2515, then we need GPIO and SPI functionality.

// TODO - I presume HAL_CANSPI_ENABLE should be in target_config.hpp?

#define HAL_CANSPI_ENABLE false
#if HAL_CANSPI_ENABLE
	#include "hal/gpio.hpp"
	#include "hal/spi.hpp"
#endif

// DEFINE PUBLIC MACROS.

// SELECT NAMESPACES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

class Can_filmask_imp;
class Can_filter_bank_imp;
class Can_buffer_imp;
class Can_imp;

// FORWARD DECLARE PUBLIC CLASSES AND TYPES.

class Can_filmask;
class Can_filter_bank;
class Can_buffer;
class Can;

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

/**
 * Available CAN objects/buffers/filters are enumerated in the target specific configuration header.  These may be used for indexing into arrays of CAN peripheral components.
 * These take the form of enums similar to those shown below.
 *
 *		enum Can_id_controller {CAN_0, NB_CTRL};
 *		enum Can_id_buffer {CAN_BUF_0, CAN_BUF_1, CAN_BUF_2, CAN_BUF_3, CAN_BUF_4, CAN_BUF_5, CAN_NB_BUF};
 *		enum Can_id_filter {CAN_FIL_0, CAN_FIL_1, CAN_FIL_2, CAN_FIL_3, CAN_FIL_4, CAN_FIL_5, CAN_NB_FIL};
 *		enum Can_id_bank {CAN_BNK_0, CAN_BNK_1, CAN_BNK_2, CAN_BNK_3, CAN_BNK_4, CAN_BNK_5, CAN_NB_BNK};
 *		enum Can_id_mask {CAN_MSK_0, CAN_MSK_1, CAN_MSK_2, CAN_MSK_3, CAN_MSK_4, CAN_MSK_5, CAN_NB_MSK};
 *
 */

/**
 * Available CAN bank modes are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *		enum Can_bank_mode {CAN_BANK_FM};
 *
 */

// CANbus baudrates.
enum Can_rate {CAN_100K, CAN_125K, CAN_200K, CAN_250K, CAN_500K, CAN_1000K};

// CANbus controller modes.
enum Can_mode {CAN_NORMAL, CAN_LISTEN};

// CANbus buffer/object modes.
enum Can_buffer_mode {CAN_OBJ_RX, CAN_OBJ_TX, CAN_OBJ_RXB, CAN_OBJ_DISABLE};

// CANbus filter/mask modes.
enum Can_filmask_mode {CAN_FM_FIL, CAN_FM_MSK};

// CANbus configuration operation status.
enum Can_config_status {CAN_CFG_SUCCESS = 0, CAN_CFG_IMMUTABLE = -1, CAN_CFG_FAILED = -2};

// CANbus transfer operation status
enum Can_send_status {CAN_SND_SUCCESS = 0, CAN_SND_BUSY = -1, CAN_SND_TXFULL = -2, CAN_SND_MODERR = -3, CAN_SND_DLCERR = -4};

// CANbus interrupt status
enum Can_int_status {CAN_INT_FENA, CAN_INT_EXISTS, CAN_INT_NOINT, CAN_INT_FAILED = -1};

// CANbus buffer/object status.
enum Can_buffer_status {BUF_NOT_COMPLETED, BUF_TX_COMPLETED, BUF_RX_COMPLETED, BUF_RX_COMPLETED_DLCW, BUF_ACK_ERROR, BUF_FORM_ERROR, BUF_CRC_ERROR, BUF_STUFF_ERROR, BUF_BIT_ERROR, BUF_NOT_REACHED, BUF_DISABLE, STAT_ERROR};


// TODO - How do we handle messages with standard length IDs?

// CAN message/frame.
typedef struct
{
	uint32_t id  : 29;	// Up to 29 bits for extended identifier.
	uint32_t ext : 1;	// Flag indicating whether the message has a 29-bit extended (or 11-bit standard) ID.
	uint32_t rtr : 1;	// Flag indicating whether the filter/mask is accepting messages with the RTR bit set or not.
	uint32_t     : 1;	// Fill to 32 bits.
	uint8_t dlc  : 4;	// Data length code, four bits indicating the number of bytes in the payload.
	uint8_t	     : 4;	// Fill to 8 bits.
	uint8_t data[8];	// 8 bytes of payload data.
} Can_message;

// CAN filter/mask values.
typedef struct
{
	uint32_t id  : 29;	// Up to 29 bits for extended identifier.
	uint32_t ext :  1;	// Flag indicating whether the filter/mask has a 29-bit extended (or 11-bit standard) ID.
	uint32_t rtr :  1;	// Flag indicating whether the filter/mask is accepting messages with the RTR bit set or not.
	uint32_t     :  1;	// Fill to 32 bits.
} Can_filmask_value;

/**
 * CAN filter/mask class; abstracts either a binary filter or mask which selects which incoming CAN messages are accepted into an attached buffer.
 */
class Can_filmask
{
	friend class Can_filter_imp;
	friend class Can_imp;
	
	public:
		// Methods.
		 
		/**
		* Gets the current filter/mask value being used by the hardware filter.
		*
		* @param	Nothing.
		* @return	The current filter value.
		*/
		 Can_filmask_value get(void);
		
		/**
		* Sets the filter/mask value being used by the hardware filter/mask.
		*
		* @param	value	The new value for the filter.
		* @return	Nothing.
		*/
		 void set(Can_filmask_value value);
		
	private:
	
		// Methods.

		Can_filmask(void);	// Poisoned.

		Can_filmask(Can_filmask*);	// Poisoned.

		Can_filmask(Can_filmask_imp*);

		Can_filmask operator =(Can_filmask const&);	// Poisoned.

		//Fields.

		Can_filmask_imp* imp;			
};


/**
 * Filter bank class; abstracts a group of boolean filters and masks, which is connected to a single Can_buffer FIFO.
 */
class Can_filter_bank
{
	friend class Can_filter_bank_imp;
	friend class Can_imp;
	
	public:

		// Methods.

		/**
		 * Returns a pointer to the buffer which this bank of filters/masks is currently attached to.  If this bank is currently not attached to a buffer, then returns NULL.
		 *
		 * @param	Nothing.
		 * @return	The buffer this bank is currently attached to.
		 */
		Can_buffer* get_buffer(void);

		/**
		 * Attaches the bank to a buffer.  This automatically detaches the bank for any buffer it was previously attached to (and may cause transitional effects such as
		 * flushing the corresponding buffer).  Returns zero for success, or non-zero to indicate an error.  In the case that the target does not support mutable banks, returns
		 * CAN_CFG_IMMUTABLE to indicate that the operation is not supported on this target type.
		 *
		 * @param	buffer	The buffer which the bank should be attached to.
		 * @return		Zero for success, or non-zero for failure.
		 */
		Can_config_status set_buffer(Can_buffer& buffer);

		/**
		 * Returns the mode the bank is currently set to.
		 *
		 * @param	Nothing.
		 * @return	The mode the bank is set to.
		 */
		Can_bank_mode get_mode(void);

		/**
		 * Sets the bank to a different mode.  Depending on the target, this may change the filters/masks which the bank makes use of; accordingly, variables pointing at filters
		 * and masks in this bank must be refreshed after changing mode.  Returns zero for success, or non-zero to indicate an error.  In the case that hte target does not
		 * support mutable banks, returns CAN_CFG_IMMUTABLE to indicate that the operation is not supported on this target type.
		 *
		 * @param	mode	The mode to change the buffer to.
		 * @return		Zero for success, or non-zero for failure.
		 */
		Can_config_status set_mode(Can_bank_mode mode);

		/**
		 * Returns the number of filters/masks which are part of this bank.
		 *
		 * @param	Nothing.
		 * @return	The number of filters/masks in this bank.
		 */
		uint8_t get_num_filmasks(void);

		/**
		 * Returns an array of pointers to the filters/masks which are part of this bank.
		 *
		 * @param	Nothing.
		 * @return	Array of pointers to filters/masks in this bank.
		 */
		Can_filmask** get_filmasks(void);

	private:

		// Methods.
		
		Can_filter_bank(void);	// Poisoned.

		Can_filter_bank(Can_filter_bank*);	// Poisoned.

		Can_filter_bank(Can_filter_bank_imp*);

		Can_filter_bank operator =(Can_filter_bank const&);	// Poisoned.

		// Fields.

		Can_filter_bank_imp* imp;
};

/**
 * Buffer class; abstracts a buffer (FIFO) in a CAN peripheral which may be able to read or write messages.
 */
class Can_buffer
{
	friend class Can_buffer_imp;
	friend class Can_imp;
	
	public:

		// Methods.
		
		/**
		* Returns the mode of the object.
		*
		* @param	Nothing.
		* @return	The mode of the object.
		*/
		Can_buffer_mode get_mode(void);
		
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
		Can_config_status set_mode(Can_buffer_mode mode);
		
		/**
		* Returns the current status of the object.
		*
		* @param	Nothing.
		* @return	The current status of the buffer (one of possible CAN_BUF_STATs).
		*/
		Can_buffer_status get_status(void);
		
		/**
		* Get the message stored in the buffer
		* 
		* @param	Can_message struct to hold returned message
		* @return 	Return code indicating whether operation was successful
		*/
		Can_send_status read(Can_message& message);
		
		/**
		 * Returns the number of messages currently stored in this buffer
		 * 
		 * @param	Nothing.
		 * @return	Number of pending messages in the buffer
		 */
		uint8_t queue_length(void);
		 
		/**
		 * Write message to buffer
		 * 
		 * @param   msg    Message to write to the buffer.
		 * @return  Nothing.
		 */
		Can_send_status write(Can_message msg);
		
		/**
		 * Reset status register of buffer
		 * 
		 * @param    Nothing.
		 * @return   Nothing.
		 */
		void clear_status(void);
		
		/**
		 * Frees the first received message on the buffer
		 * 
		 * @param	 Nothing.
		 * @return	 Return code indicating whether operation was successful
		 */
		Can_config_status free_message(void);
		
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
		* @param	callback	The handler for this interrupt condition.
		* @return 				Return code indicating whether operation was successful
		*/
		Can_int_status attach_interrupt(Can_buffer_interrupt_type interrupt, void (*callback)(void));
		
		/**
		* Removes a handler for a specific object for a particular interrupt event.
		*
		* @param	interrupt	The interrupt event to dettach the handler from.
		* @return				Return code indicating whether operation was successful
		*/
		Can_int_status detach_interrupt(Can_buffer_interrupt_type interrupt);
		
		/**
		* Boolean describing whether an interrupt handler is set for this condition
		* on this buffer.
		* 
		* @param   interrupt   The MOb interrupt condition to test if enabled.
		* @return              Flag indicating whether an interrupt handler is set for this condition.
		*
		*/
		bool test_interrupt(Can_buffer_interrupt_type interrupt);
		
		/**
		* Clear interrupt flags for buffer based interrupts to exit the routine
		* 
		* @param	interrupt	The interrupt event flag to clear.
		* @return				Return code indiciating whether operation was successful.
		*/
		Can_int_status clear_interrupt_flags(Can_buffer_interrupt_type interrupt);
		
	private:
		
		// Methods.
		
		Can_buffer(void);	// Poisoned.

		Can_buffer(Can_buffer*);	// Poisoned.

		Can_buffer(Can_buffer_imp*);

		Can_buffer operator =(Can_buffer const&);	// Poisoned.

		// Fields.

		Can_buffer_imp* imp;
};

/**
 * Interface class for a CAN controller.
 */
class Can 
{
	friend class Can_imp;
	
	public:

		// Methods.

		/**
		 * Binds the interface with a CAN hardware peripheral.
		 */
		static Can bind(Can_id_controller controller);
		
		/**
		 * Called when Can instance goes out of scope
		 */
		~Can(void);
		
		/**
		 * Initializes controller for first use. Sets the baud rate for the controller.
		 * 
		 * @param    rate	Baud rate of bus to use.
		 * @return		Whether bus was successfully initialized.
		 */
		Can_config_status initialise(Can_rate rate);

		/**
		 * Master interrupt enable; enable interrupts for all sources in this CAN peripheral.
		 * 
	     * @param	 Nothing.
		 * @return    Nothing.
		 */
		void enable_interrupts(void);
	    
		/**
		 * Master interrupt disable; disable interrupts for all sources in this CAN peripheral.
		 * 
		 * @param	 Nothing.
		 * @return    Nothing.
		 */
		void disable_interrupts(void);
	    
		/**
		 * Attach interrupt handler to channel based event.
		 * 
		 * @param     interrupt		The interrupt event to attach the handler to.
		 * @param     callback		The handler for this interrupt event.
		 * @return    				Return code indiciating whether operation was successful
		 */
		Can_int_status attach_interrupt(Can_channel_interrupt_type interrupt, void (*callback)(void));
	    
		/**
		 * Detach interrupt for channel based event.
		 * 
		 * @param     interrupt		The interrupt event to detach the handler from.
		 * @return    				Return code indicating whether operation was successful.
		 */
		Can_int_status detach_interrupt(Can_channel_interrupt_type interrupt);
	    
		/**
		 * Test whether an interrupt handler is attached to an channel based event.
		 * 
		 * @param     interrupt		The interrupt event to test.
		 * @return    				Flag indicating whether interrupt event has an existing handler.
		 */
		bool test_interrupt(Can_channel_interrupt_type interrupt);
	    
		/**
		 * Clear interrupt flag for channel based events.  If called outside an ISR, this probably doesn't do anything useful.
		 * 
		 * @param	 interrupt      The interrupt event flag to clear.
		 * @return   				Return code indicating whether operation was successful
		 */
		Can_int_status clear_interrupt_flags(Can_channel_interrupt_type interrupt);
		
		/**
		 * Call during buffer based interrupt callback routine to confirm
		 * which buffer triggered the interrupt
		 * 
		 * @param	Nothing.
		 * @return 	Pointer to the buffer that triggered the interrupt rotuine
		 */
		Can_buffer* get_interrupted_buffer(void);

		/**
		 * Returns the number of filter/mask banks which are part of this CAN controller.
		 *
		 * @param	Nothing.
		 * @return	The number of filter/mask banks which are part of this controller.
		 */
		uint8_t get_num_banks(void);

		/**
		 * Returns an array or pointers to the filters/mask banks which are part of this CAN controller.  This array may either be iterated over, 
		 * or indexed into directly using the enumerated definitions provided by the target configuration for the peripheral.
		 *
		 * @param	Nothing.
		 * @return	Array of pointers to filters/mask banks in this controller.
		 */
		Can_filter_bank** get_banks(void);

		/**
		 * Returns the number of buffers which are part of this CAN controller.
		 *
		 * @param	Nothing.
		 * @return	The number of buffers which are part of this controller.
		 */
		uint8_t get_num_buffers(void);

		/**
		 * Returns an array of pointers to the buffers which are part of this CAN controller.  This array may either be iterated over, or indexed
		 * into directly using the enumerated definitions provided by the target configuration for the peripheral.
		 *
		 * @param	Nothing.
		 * @return	Array of buffers in this controller.
		 */
		Can_buffer** get_buffers(void);
    
	private:
	
		// Methods.

		Can(void);	// Poisoned.

		Can(Can*);	// Poisoned.

		Can(Can_imp*);

		Can operator =(Can const&);	// Poisoned.

		// Fields.

		Can_imp* imp;
};

#endif // __CAN_H__

// ALL DONE.

