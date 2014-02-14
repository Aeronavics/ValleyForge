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
 *  FILE: 		can.cpp	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	14-11-2013
 *
 *	Functionality to provide implementation for CAN in AVR
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include "can_platform.hpp"

#include <stdio.h>
#include <avr/io.h>
#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>


// DEFINE PRIVATE MACROS.

#define CLK_MHZ <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>	// Replaces the need to use the <<< syntax to get clock speed	

#define ENABLE_TOUT_LOOP  1000000;						// Controller enable timeout.

/* different interrupt vector names for different AVRs, stupid I know */
#if defined(__AVR_AT90CAN128__)
	#define GEN_CAN_IT_VECT CANIT_vect
	#define OVR_TIM_IT_VECT OVRIT_vect
#elif defined (__AVR_ATmega64M1__)
	#define GEN_CAN_IT_VECT CAN_INT_vect
	#define OVR_TIM_IT_VECT CAN_TOVF_vect
#endif


// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

volatile static voidFuncPtr bufIntFunc[CAN_NUM_BUFFERS][CAN_NUM_BUF_INT];
volatile static voidFuncPtr chanIntFunc[CAN_NUM_CHAN_INT];

volatile Can_id_buffer interrupt_service_buffer;
volatile 
bool in_interrupt = false;

/**
 * Private, target specific implementation class for public Can_filmask class.
 */
class Can_filmask_imp
{
	public:
	
		// Methods.

		/**
		 * Create a new Can_filmask_imp which controls the specified CAN filter/mask.
		 * This constructor sets it to filter mode.
		 * 
		 * @param	filter	The id of the CAN filter for this driver to interface with.
		 */
		 Can_filmask_imp(Can_id_filter filter);
		 
		/**
		 * Create a new Can_filmask_imp which controls the specified CAN filter/mask.
		 * This constructor sets it to filter mode.
		 * 
		 * @param	mask	The id of the CAN mask for thsi driver to interface with.
		 */
		 Can_filmask_imp(Can_id_mask mask);
		 
		/**
		* Gets the current filter/mask value being used by the hardware filter/mask.
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
		 
		/**
		 * Returns whether this object represents a filter or a mask
		 * 
		 * @param	Nothing.
		 * @return	Nothing.
		 */
		 Can_filmask_mode get_mode(void);
		
	private:
	
		// Methods.
		
		Can_filmask_imp(void);	// Poisoned.

		Can_filmask_imp(Can_filmask_imp*);	// Poisoned.

		Can_filmask_imp operator =(Can_filmask_imp const&);	// Poisoned.

		//Fields.		
		
		Can_id_filmask filmask_no;
		
		Can_filmask_value filmask_val;
		
		Can_filmask_mode filmask_mode;
};

/**
 * Private, target specific implementation class for public Can_filter_bank class.
 */
class Can_filter_bank_imp
{
	friend class Can_imp;
	
	public:

		// Methods.

		/**
		 * Create a new Can_filter_bank_imp which controls the specified CAN filter bank.
		 * 
		 * @param	bank	The id of the CAN bank for this driver to interface with.
		 */
		 Can_filter_bank_imp(Can_id_bank bank);

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
		
		Can_filter_bank_imp(void);	// Poisoned.

		Can_filter_bank_imp(Can_filter_bank_imp*);	// Poisoned.

		Can_filter_bank_imp operator =(Can_filter_bank_imp const&);	// Poisoned.

		// Fields.
		
		Can_id_bank bnk_no;
		
		Can_bank_mode bnk_mode;
		
		Can_filmask* filmasks[2];		//for AVR, always {filter, mask}
		
		Can_buffer* buffer_link;
};

/**
 * Private, target specific implementation class for public Can_buffer class.
 */
class Can_buffer_imp
{
	friend class Can_imp;
	
	public:

		// Methods.
		
		/**
		 * Create a new Can_buffer_imp which controls the specified CAN buffer.
		 * 
		 * @param	buffer	The id of the CAN buffer for this driver to interface with.
		 */
		 Can_buffer_imp(Can_id_buffer buffer);
		
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
		 * Get the the message in the buffer
		 * 
		 * @param   Can_message struct to store the incoming message.
		 * @return  Return code indicating whether operation was successful.
		 */
		Can_config_status read(Can_message* msg);
		 
		/**
		 * Write message to buffer
		 * 
		 * @param   msg    Message to write to the buffer.
		 * @return  Nothing.
		 */
		Can_send_status write(Can_message msg);
		
		/**
		 * Get the number of message in the buffer
		 * 
		 * @param	Nothing.
		 * @return 	Number of messages in the buffer
		 */
		uint8_t queue_length(void);
		
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
		* @param	callback	The handler for this interrupt condition.
		*/
		Can_int_status attach_interrupt(Can_buffer_interrupt_type interrupt, void (*callback)(void));
		
		/**
		* Removes a handler for a specific object for a particular interrupt event.
		*
		* @param	interrupt	The interrupt condition to dettach the handler from.
		* @return	Nothing.	
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
		 * Clears the interrupt flag for buffer based events. For AVRs, this clears the 
		 * status of the buffer, so DO NOT call this outside an ISR
		 * 
		 * @param	interrupt	The MOb interrupt event flag of clear.
		 * @return 				Return code indicating whether operation was successful
		 */
		Can_int_status clear_interrupt_flags(Can_buffer_interrupt_type interrupt);
		
	private:
		
		// Methods.
		
		Can_buffer_imp(void);	// Poisoned.

		Can_buffer_imp(Can_buffer_imp*);	// Poisoned.

		Can_buffer_imp operator =(Can_buffer_imp const&);	// Poisoned.

		// Fields.
		
		Can_id_buffer buf_no;
		
		Can_buffer_mode buf_mode;
		
		Can_filter_bank* bank_link;
};

/**
 * Private, target specific implementation class for public Can class.
 */
class Can_imp
{
	public:

		// Methods.
	
		/**
		 * Create a new Can_imp which controls the specified CAN peripheral.
		 * 
		 * @param	controller	The id of the CAN peripheral/channel/controller for this driver to interface with.
		 */
		 Can_imp(Can_id_controller controller);
		
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
		 * @return    Nothing.class Can_filter_bank
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
		 * @return    				Return code indicating whether operation was successful/
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
		 * @return    Flag indicating whether interrupt event has an existing handler.
		 */
		bool test_interrupt(Can_channel_interrupt_type interrupt);
	    
		/**
		 * Clear interrupt flag for channel based events.  If called outside an ISR, this probably doesn't do anything useful.
		 * 
		 * @param	 interrupt      The interrupt event flag to clear.
		 * @return  				Return code indicating whether operation was successful.
		 */
		Can_int_status clear_interrupt_flags(Can_channel_interrupt_type interrupt);

		/**
		 * Returns the number of filter/mask banks which are part of this CAN controller.
		 *
		 * @param	Nothing.
		 * @return	The number of filter/mask banks which are part of this controller.
		 */
		uint8_t get_num_banks(void);

		/**
		 * Returns an array of pointers to the filters/mask banks which are part of this CAN controller.  This array may either be iterated over,
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
		 * @return	Array of pointers to buffers in this controller.
		 */
		Can_buffer** get_buffers(void);
    
	private:

		// Methods.
		
		Can_imp(void);	// Poisoned.

		Can_imp(Can_imp*);	// Poisoned.

		Can_imp operator =(Can_imp const&);	// Poisoned.

		// Fields.
		
			// *** TARGET CONFIGURATION SPECIFIC.

			// Objects for the CAN tree.
			
			// NOTE - Because the AVR has only one CAN controller/channel, these can be declared here.  If a target had multiple channels with
			//		  a non-homogenous tree structure, then these would have to be moved to a separate struct and pointed to.
			
			Can_buffer* buffers[CAN_NUM_BUFFERS];
			Can_filter_bank* banks[CAN_NUM_BANKS];
			Can_filmask* filters[CAN_NUM_FILTERS];
			Can_filmask* masks[CAN_NUM_MASKS];
			
			#if (defined(__AVR_ATmega64M1__) || defined(__AVR_AT90CAN128__))
			Can_buffer_imp buf_0i;
			Can_buffer_imp buf_1i;
			Can_buffer_imp buf_2i;
			Can_buffer_imp buf_3i;
			Can_buffer_imp buf_4i;
			Can_buffer_imp buf_5i;
			
			Can_buffer buf_0;
			Can_buffer buf_1;
			Can_buffer buf_2;
			Can_buffer buf_3;
			Can_buffer buf_4;			
			Can_buffer buf_5;
			
			Can_filter_bank_imp bnk_0i;
			Can_filter_bank_imp bnk_1i;
			Can_filter_bank_imp bnk_2i;
			Can_filter_bank_imp bnk_3i;
			Can_filter_bank_imp bnk_4i;
			Can_filter_bank_imp bnk_5i;
			
			Can_filter_bank bnk_0;
			Can_filter_bank bnk_1;
			Can_filter_bank bnk_2;
			Can_filter_bank bnk_3;
			Can_filter_bank bnk_4;
			Can_filter_bank bnk_5;
			
			Can_filmask_imp fil_0i;
			Can_filmask_imp fil_1i;
			Can_filmask_imp fil_2i;
			Can_filmask_imp fil_3i;
			Can_filmask_imp fil_4i;
			Can_filmask_imp fil_5i;
			
			Can_filmask fil_0;
			Can_filmask fil_1;
			Can_filmask fil_2;
			Can_filmask fil_3;
			Can_filmask fil_4;
			Can_filmask fil_5;
			
			Can_filmask_imp msk_0i;
			Can_filmask_imp msk_1i;
			Can_filmask_imp msk_2i;
			Can_filmask_imp msk_3i;
			Can_filmask_imp msk_4i;
			Can_filmask_imp msk_5i;
			
			Can_filmask msk_0;
			Can_filmask msk_1;
			Can_filmask msk_2;
			Can_filmask msk_3;
			Can_filmask msk_4;
			Can_filmask msk_5;			
			#endif
			
			#if defined(__AVR_AT90CAN128__)
			Can_buffer_imp buf_6i;
			Can_buffer_imp buf_7i;
			Can_buffer_imp buf_8i;
			Can_buffer_imp buf_9i;
			Can_buffer_imp buf_10i;
			Can_buffer_imp buf_11i;
			Can_buffer_imp buf_12i;
			Can_buffer_imp buf_13i;
			Can_buffer_imp buf_14i;
			
			Can_buffer buf_6;
			Can_buffer buf_7;
			Can_buffer buf_8;
			Can_buffer buf_9;
			Can_buffer buf_10;			
			Can_buffer buf_11;
			Can_buffer buf_12;
			Can_buffer buf_13;
			Can_buffer buf_14;
			
			Can_filter_bank_imp bnk_6i;
			Can_filter_bank_imp bnk_7i;
			Can_filter_bank_imp bnk_8i;
			Can_filter_bank_imp bnk_9i;
			Can_filter_bank_imp bnk_10i;
			Can_filter_bank_imp bnk_11i;
			Can_filter_bank_imp bnk_12i;
			Can_filter_bank_imp bnk_13i;
			Can_filter_bank_imp bnk_14i;
			
			Can_filter_bank bnk_6;
			Can_filter_bank bnk_7;
			Can_filter_bank bnk_8;
			Can_filter_bank bnk_9;
			Can_filter_bank bnk_10;
			Can_filter_bank bnk_11;
			Can_filter_bank bnk_12;
			Can_filter_bank bnk_13;
			Can_filter_bank bnk_14;
			
			Can_filmask_imp fil_6i;
			Can_filmask_imp fil_7i;
			Can_filmask_imp fil_8i;
			Can_filmask_imp fil_9i;
			Can_filmask_imp fil_10i;
			Can_filmask_imp fil_11i;
			Can_filmask_imp fil_12i;
			Can_filmask_imp fil_13i;
			Can_filmask_imp fil_14i;
			
			Can_filmask fil_6;
			Can_filmask fil_7;
			Can_filmask fil_8;
			Can_filmask fil_9;
			Can_filmask fil_10;
			Can_filmask fil_11;			
			Can_filmask fil_12;			
			Can_filmask fil_13;			
			Can_filmask fil_14;
			
			Can_filmask_imp msk_6i;
			Can_filmask_imp msk_7i;
			Can_filmask_imp msk_8i;
			Can_filmask_imp msk_9i;
			Can_filmask_imp msk_10i;
			Can_filmask_imp msk_11i;
			Can_filmask_imp msk_12i;
			Can_filmask_imp msk_13i;
			Can_filmask_imp msk_14i;			
			
			Can_filmask msk_6;
			Can_filmask msk_7;
			Can_filmask msk_8;
			Can_filmask msk_9;
			Can_filmask msk_10;
			Can_filmask msk_11;			
			Can_filmask msk_12;			
			Can_filmask msk_13;			
			Can_filmask msk_14;
			#endif
			
			// *** TARGET AGNOSTIC.
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

// Can_filmask.

Can_filmask::Can_filmask(Can_filmask_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

Can_filmask_value Can_filmask::get(void)
{
	return imp->get();
}

void Can_filmask::set(Can_filmask_value value)
{
	imp->set(value);
}


// Can_filter_bank.

Can_filter_bank::Can_filter_bank(Can_filter_bank_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

Can_buffer* Can_filter_bank::get_buffer(void)
{
	return imp->get_buffer();
}

Can_config_status Can_filter_bank::set_buffer(Can_buffer& buffer)
{
	return imp->set_buffer(buffer);
}

Can_bank_mode Can_filter_bank::get_mode(void)
{
	return imp->get_mode();
}

Can_config_status Can_filter_bank::set_mode(Can_bank_mode mode)
{
	return imp->set_mode(mode);
}

uint8_t Can_filter_bank::get_num_filmasks(void)
{
	return imp->get_num_filmasks();
}

Can_filmask** Can_filter_bank::get_filmasks(void)
{
	return imp->get_filmasks();
}

// Can_buffer.

Can_buffer::Can_buffer(Can_buffer_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

Can_buffer_mode Can_buffer::get_mode(void)
{
	return imp->get_mode();
}

bool Can_buffer::get_multimode(void)
{
	return imp->get_multimode();
}

Can_config_status Can_buffer::set_mode(Can_buffer_mode mode)
{
	return imp->set_mode(mode);
}

Can_buffer_status Can_buffer::get_status(void)
{
	return imp->get_status();
}

Can_config_status Can_buffer::read(Can_message* message)
{
	return imp->read(message);
}

Can_send_status Can_buffer::write(Can_message msg)
{
	return imp->write(msg);
}

uint8_t Can_buffer::queue_length(void)
{
	return imp->queue_length();
}

void Can_buffer::clear_status(void)
{
	imp->clear_status();
}

void Can_buffer::enable_interrupt(void)
{
	imp->enable_interrupt();
}

void Can_buffer::disable_interrupt(void)
{
	imp->disable_interrupt();
}

Can_int_status Can_buffer::attach_interrupt(Can_buffer_interrupt_type interrupt, void (*callback)(void))
{
	return imp->attach_interrupt(interrupt, callback);
}

Can_int_status Can_buffer::detach_interrupt(Can_buffer_interrupt_type interrupt)
{
	return imp->detach_interrupt(interrupt);
}

bool Can_buffer::test_interrupt(Can_buffer_interrupt_type interrupt)
{
	return imp->test_interrupt(interrupt);
}

// Can.

Can::Can(Can_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

Can Can::bind(Can_id_controller controller)
{
	// *** TARGET CONFIGURATION SPECIFIC.
	
	// There already exists a static instance of the implementation class for each of the CAN peripherals.
	static Can_imp can_imp_0 = Can_imp(CAN_0);
	
	// NOTE - In the case of AVR devices, there is only one CAN peripheral, so we don't really have any logic here.
	
	// Create an interface class and attach the relevant implementation to it.
	Can new_can = Can(&can_imp_0);
	
	// *** TARGET AGNOSTIC.
	
	// Return the newly created interface.
	return new_can;
}

Can_config_status Can::initialise(Can_rate rate)
{
	return imp->initialise(rate);
}

void Can::enable_interrupts(void)
{
	imp->enable_interrupts();
}

void Can::disable_interrupts(void)
{
	imp->disable_interrupts();
}

Can_int_status Can::attach_interrupt(Can_channel_interrupt_type interrupt, void (*callback)(void))
{
	return imp->attach_interrupt(interrupt, callback);
}

Can_int_status Can::detach_interrupt(Can_channel_interrupt_type interrupt)
{
	return imp->detach_interrupt(interrupt);
}

bool Can::test_interrupt(Can_channel_interrupt_type interrupt)
{
	return imp->test_interrupt(interrupt);
}

Can_int_status Can::clear_interrupt_flags(Can_channel_interrupt_type interrupt)
{
	return imp->clear_interrupt_flags(interrupt);
}

uint8_t Can::get_num_banks(void)
{
	return imp->get_num_banks();
}

Can_filter_bank** Can::get_banks(void)
{
	return imp->get_banks();
}

uint8_t Can::get_num_buffers(void)
{
	return imp->get_num_buffers();
}

Can_buffer** Can::get_buffers(void)
{
	return imp->get_buffers();
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).

// Can_filmask.

Can_filmask_imp::Can_filmask_imp(Can_id_filter filter)
{
	filmask_no = static_cast<Can_id_filmask>(filter);
	filmask_mode = CAN_FM_FIL;
}

Can_filmask_imp::Can_filmask_imp(Can_id_mask mask)
{
	filmask_no = static_cast<Can_id_filmask>(mask);
	filmask_mode = CAN_FM_MSK;
}

Can_filmask_value Can_filmask_imp::get(void)
{
	return filmask_val;	
}

void Can_filmask_imp::set(Can_filmask_value value)
{
	Can_set_mob(filmask_no);	//select the corresponding MOb
	
	if (filmask_mode == CAN_FM_FIL)
	{
		//set the ID
		uint32_t id = value.id;
		switch(value.ext)
		{
			case(0): 
				Can_set_std_id(id); 
				break;
			case(1): 
				Can_set_ext_id(id); 
				break;
		}
		
		//set the RTR
		switch(value.rtr)
		{
			case(0): 
				Can_clear_rtr(); 
				break;
			case(1): 
				Can_set_rtr(); 
				break;
		}
	}
	else if (filmask_mode == CAN_FM_MSK)
	{
		//set the ID
		uint32_t id = value.id;
		switch(value.ext)
		{
			case(0): 
				Can_set_std_msk(id); 
				break;
			case(1): 
				Can_set_ext_msk(id); 
				break;
		}
		
		//set the RTR
		switch(value.rtr)
		{
			case(0): 
				Can_clear_rtrmsk(); 
				break;
			case(1): 
				Can_set_rtrmsk(); 
				break;
		}			
	}
	
	filmask_val = value;	//cache the set value
}

// Can_filter_bank.

Can_filter_bank_imp::Can_filter_bank_imp(Can_id_bank bank)
{
	bnk_no = bank;
	bnk_mode = CAN_BNK_MODE_FM;
}

Can_buffer* Can_filter_bank_imp::get_buffer(void)
{
	return buffer_link;
}

Can_config_status Can_filter_bank_imp::set_buffer(Can_buffer& buffer)
{
	return CAN_CFG_IMMUTABLE;	//1 bank is fixed to one buffer in AVRs
}

Can_bank_mode Can_filter_bank_imp::get_mode(void)
{
	return bnk_mode;
}

Can_config_status Can_filter_bank_imp::set_mode(Can_bank_mode mode)
{
	return CAN_CFG_IMMUTABLE;
}

uint8_t Can_filter_bank_imp::get_num_filmasks(void)
{
	return 2;	// always filter/mask pair in banks for AVR
}

Can_filmask** Can_filter_bank_imp::get_filmasks(void)
{
	return filmasks;
}

// Can_buffer.

Can_buffer_imp::Can_buffer_imp(Can_id_buffer buffer)
{
	buf_no = buffer;
}

Can_buffer_mode Can_buffer_imp::get_mode(void)
{
	return buf_mode;
}

bool Can_buffer_imp::get_multimode(void)
{
	return true;
}

Can_config_status Can_buffer_imp::set_mode(Can_buffer_mode mode)
{
	Can_set_mob(buf_no);	//select the corresponding MOb
	
	switch(mode)
	{
		case (CAN_OBJ_TX):
		{
			Can_config_tx();
			Can_clear_rplv();
			break;
		}
		case (CAN_OBJ_RX):
		{
			Can_config_rx();
			Can_clear_rplv();
			break;
		}
		case (CAN_OBJ_RXB):
		{
			Can_config_rx_buffer();
			break;
		}
		case (CAN_OBJ_DISABLE):
		{
			Can_mob_abort();
			break;
		}
	}
	buf_mode = mode;
	return CAN_CFG_SUCCESS;
}

Can_buffer_status Can_buffer_imp::get_status(void)
{
	Can_set_mob(buf_no);				//select the corresponding MOb
	
	uint8_t canstmob_copy = CANSTMOB;	//copy for test integrity
	
	if ((canstmob_copy & CONMOB_MSK) == 0x00)
	{
		return BUF_DISABLE;
	}
	
	Can_buffer_status status = STAT_ERROR;
	
	switch (canstmob_copy)
	{
		case (MOB_RX_COMPLETED_DLCW): 	
			status = BUF_RX_COMPLETED_DLCW;
			break;
		case (MOB_RX_COMPLETED): 		
			status = BUF_RX_COMPLETED;
			break;
		case (MOB_TX_COMPLETED): 		
			status = BUF_TX_COMPLETED;
			break;
		case (MOB_ACK_ERROR): 			
			status = BUF_ACK_ERROR;
			break;
		case (MOB_FORM_ERROR): 
			status = BUF_FORM_ERROR;
			break;
		case (MOB_CRC_ERROR):			
			status = BUF_CRC_ERROR;
			break;
		case (MOB_STUFF_ERROR):
			status = BUF_STUFF_ERROR;
			break;
		case (MOB_BIT_ERROR):
			status = BUF_BIT_ERROR;
			break;
		case (MOB_NOT_REACHED):
			status = BUF_NOT_REACHED;
			break;
		case (0x00):					
			status = BUF_NOT_COMPLETED;
			break;
	}
	
	return status;
}

Can_config_status Can_buffer_imp::read(Can_message* msg)
{
	Can_set_mob(buf_no);	//select the corresponding MOb
	
	if (get_status() == BUF_RX_COMPLETED || get_status() == BUF_RX_COMPLETED_DLCW)
	{	
		/* read arbitration */
		msg->dlc = Can_get_dlc();
		
		uint32_t id;
		if (Can_get_ide())
		{
			msg->ext = 1;
			Can_get_ext_id(id);
		}
		else 
		{
			msg->ext = 0;
			Can_get_std_id(id);
		}
		msg->id = id;
		
		/* read the payload */
		for (uint8_t i=0; i<msg->dlc; i++)
		{
			msg->data[i] = CANMSG;	//CANMSG is auto-incremented
		}
		
		Can_clear_mob();
		
		return CAN_CFG_SUCCESS;
	}
	else
	{
		return CAN_CFG_FAILED;
	}
}

uint8_t Can_buffer_imp::queue_length(void)
{
	if (get_status() == BUF_RX_COMPLETED || get_status() == BUF_RX_COMPLETED_DLCW)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Can_send_status Can_buffer_imp::write(Can_message msg)
{
	Can_set_mob(buf_no);	//select the corresponding MOb	
	
	if (get_status() != BUF_TX_COMPLETED)
	{	
		/* reset filter/mask values */
		Can_clear_rtr();
		Can_clear_idemsk();
		Can_clear_rtrmsk();
		
		Can_clear_mob();
		
		/* set arbitration */
		Can_filmask_value tmp_filmask_val;
		tmp_filmask_val.ext = msg.ext;
		tmp_filmask_val.id = msg.id;
		tmp_filmask_val.rtr = msg.rtr;
		bank_link->get_filmasks()[0]->set(tmp_filmask_val);	//in AVRs, set the corresponding filter to set the message arbitration
		
		if (msg.dlc > 8)
		{
			return CAN_SND_DLCERR;
		}
		else
		{
			Can_clear_dlc();
			Can_set_dlc(msg.dlc);							//data length code is the only one not covered by corresponding filter
		}
		
		/* write to buffer */
		for (uint8_t i=0; i<msg.dlc; i++)
		{
			CANMSG = msg.data[i];		// CANMAG  is auto-incremented
		}
		
		set_mode(CAN_OBJ_TX);
		return CAN_SND_SUCCESS;
		
		// once message transmission is complete, user must call clear_status()
	}
	else
	{
		return CAN_SND_MODERR;
	}	
}

void Can_buffer_imp::clear_status(void)
{
	Can_set_mob(buf_no);	//select the corresponding MOb	
	
	Can_clear_status_mob();
}

void Can_buffer_imp::enable_interrupt(void)
{
	if (buf_no < 8)
	{
		CANIE2 |= (1<<buf_no);
	}
	else
	{
		CANIE1 |= (1<<(buf_no-8));
	}
}

void Can_buffer_imp::disable_interrupt(void)
{
	if (buf_no < 8)
	{
		CANIE2 &= ~(1<<buf_no);
	}
	else
	{
		CANIE1 &= ~(1<<(buf_no-8));
	}
}

Can_int_status Can_buffer_imp::attach_interrupt(Can_buffer_interrupt_type interrupt, void (*callback)(void))
{
	Can_int_status ret_code;
	
	/* Check whether callback already exists and adjust return code accordingly */
	if (bufIntFunc[buf_no][interrupt])
	{
		ret_code = CAN_INT_EXISTS;
	}
	else
	{
		ret_code = CAN_INT_NOINT;
	}
	
	/* Enable the interrupt mask for the chosen interrupt type, this is only done once in the program.
	 * Successive detaching and re-attaching does not write to the the mask register.
	 * Return code indicating whether mask register has been written will overwite the 
	 * return code for whether callback exists as set above.
	 * 
	 * Note: Callback will only be attached to one MOb but the event mask is enabled for all MObs */
	 
	switch (interrupt)
	{
		case (CAN_RX_COMPLETE):
			if (!(CANGIE & (1<<ENRX)))
			{
				ret_code = CAN_INT_FENA;
			}
			CANGIE |= (1<<ENRX);
			break;
		case (CAN_TX_COMPLETE):
			if (!(CANGIE & (1<<ENTX)))
			{
				ret_code = CAN_INT_FENA;
			}
			CANGIE |= (1<<ENTX);
			break;
		case (CAN_GEN_ERROR):
			if (!(CANGIE & (1<<ENERR)))
			{
				ret_code = CAN_INT_FENA;
			}
			CANGIE |= (1<<ENERR);
			break;
	}

	bufIntFunc[buf_no][interrupt] = callback;	// attach the callback
	
	return ret_code;
}

Can_int_status Can_buffer_imp::detach_interrupt(Can_buffer_interrupt_type interrupt)
{
	//note: only callback is removed, the vector isn't masked off because other MObs may still use it
	
	if (bufIntFunc[buf_no][interrupt])
	{
		return CAN_INT_EXISTS;		// removed callback
	}
	else
	{
		return CAN_INT_NOINT;		// no callback to remove
	}
	
	bufIntFunc[buf_no][interrupt] = NULL;
}

bool Can_buffer_imp::test_interrupt(Can_buffer_interrupt_type interrupt)
{
	Can_set_mob(buf_no);	//select the corresponding MOb	
	
	switch(interrupt)
	{
		case (CAN_RX_COMPLETE): return (CANGIE & (1 << ENRX));
		case (CAN_TX_COMPLETE): return (CANGIE & (1 << ENTX));
		case (CAN_GEN_ERROR): 	return (CANGIE & (1 << ENERR));
		default:				return false;
	}
}

Can_int_status Can_buffer_imp::clear_interrupt_flags(Can_buffer_interrupt_type interrupt)
{
	Can_int_status ret_code = CAN_INT_NOINT;
	Can_buffer_status status = get_status();
	switch (interrupt)
	{
		case (CAN_RX_COMPLETE):
			if (status == BUF_RX_COMPLETED || status == BUF_RX_COMPLETED_DLCW)
			{
				clear_status();
				ret_code = CAN_INT_EXISTS;		// a receive interrupt actually occured
			}
			else
			{
				ret_code = CAN_INT_NOINT;		// a receive interrupt never occcured
			}
			break;
		case (CAN_TX_COMPLETE):
			if (status == BUF_TX_COMPLETED)
			{
				clear_status();
				ret_code = CAN_INT_EXISTS;		// a transmit interrupt actually occured
			}
			else
			{
				ret_code = CAN_INT_NOINT;		// a transmit interrupt never occured
			}
			break;
		case (CAN_GEN_ERROR):
			if (status == BUF_ACK_ERROR || status == BUF_FORM_ERROR || status == BUF_CRC_ERROR || status == BUF_STUFF_ERROR || status == BUF_BIT_ERROR)
			{
				ret_code = CAN_INT_EXISTS;		// an error interrupt actually occured
			}
			else
			{
				ret_code = CAN_INT_NOINT;		// an error interrupt never occured
			}
	}
	
	return ret_code;
}

// Can.

Can_imp::Can_imp(Can_id_controller controller) :

// *** TARGET CONFIGURATION SPECIFIC.

// NOTE - We have to use an initialiser list here.
	#if (defined (__AVR_ATmega64M1__) || defined(__AVR_AT90CAN128__))
	/* This target has MOb 0-6 */
	
	/* buffer types */
	//buffer imps
	buf_0i(CAN_BUF_0),
	buf_1i(CAN_BUF_1),
	buf_2i(CAN_BUF_2),
	buf_3i(CAN_BUF_3),
	buf_4i(CAN_BUF_4),
	buf_5i(CAN_BUF_5),
	
	//buffers
	buf_0((Can_buffer_imp*) NULL),
	buf_1((Can_buffer_imp*) NULL),
	buf_2((Can_buffer_imp*) NULL),
	buf_3((Can_buffer_imp*) NULL),
	buf_4((Can_buffer_imp*) NULL),
	buf_5((Can_buffer_imp*) NULL),
	
	/* bank types */
	//bank imps
	bnk_0i(CAN_BNK_0),
	bnk_1i(CAN_BNK_1),
	bnk_2i(CAN_BNK_2),
	bnk_3i(CAN_BNK_3),
	bnk_4i(CAN_BNK_4),
	bnk_5i(CAN_BNK_5),
	
	//banks
	bnk_0((Can_filter_bank_imp*) NULL),
	bnk_1((Can_filter_bank_imp*) NULL),
	bnk_2((Can_filter_bank_imp*) NULL),
	bnk_3((Can_filter_bank_imp*) NULL),
	bnk_4((Can_filter_bank_imp*) NULL),
	bnk_5((Can_filter_bank_imp*) NULL),
	
	/* filter tyes */
	//filter imps
	fil_0i(CAN_FIL_0),
	fil_1i(CAN_FIL_1),
	fil_2i(CAN_FIL_2),
	fil_3i(CAN_FIL_3),
	fil_4i(CAN_FIL_4),
	fil_5i(CAN_FIL_5),
	
	//filters
	fil_0((Can_filmask_imp*) NULL),
	fil_1((Can_filmask_imp*) NULL),
	fil_2((Can_filmask_imp*) NULL),
	fil_3((Can_filmask_imp*) NULL),
	fil_4((Can_filmask_imp*) NULL),
	fil_5((Can_filmask_imp*) NULL),
	
	/* mask types */
	//mask imps
	msk_0i(CAN_MSK_0),
	msk_1i(CAN_MSK_1),
	msk_2i(CAN_MSK_2),
	msk_3i(CAN_MSK_3),
	msk_4i(CAN_MSK_4),
	msk_5i(CAN_MSK_5),
	
	//masks
	msk_0((Can_filmask_imp*) NULL),
	msk_1((Can_filmask_imp*) NULL),
	msk_2((Can_filmask_imp*) NULL),
	msk_3((Can_filmask_imp*) NULL),
	msk_4((Can_filmask_imp*) NULL),
	msk_5((Can_filmask_imp*) NULL)
	#endif
	
	#if defined(__AVR_AT90CAN128__)
	/* buffer types */
	//buffer imps
	,	// Don't remove this comma! It allows continuation of the list above.
	buf_6i(CAN_BUF_6),
	buf_7i(CAN_BUF_7),
	buf_8i(CAN_BUF_8),
	buf_9i(CAN_BUF_9),
	buf_10i(CAN_BUF_10),
	buf_11i(CAN_BUF_11),
	buf_12i(CAN_BUF_12),
	buf_13i(CAN_BUF_13),
	buf_14i(CAN_BUF_14),
	
	//buffers
	buf_6((Can_buffer_imp*) NULL),
	buf_7((Can_buffer_imp*) NULL),
	buf_8((Can_buffer_imp*) NULL),
	buf_9((Can_buffer_imp*) NULL),
	buf_10((Can_buffer_imp*) NULL),
	buf_11((Can_buffer_imp*) NULL),
	buf_12((Can_buffer_imp*) NULL),
	buf_13((Can_buffer_imp*) NULL),
	buf_14((Can_buffer_imp*) NULL),
	
	/* bank types */
	//bank imps
	bnk_6i(CAN_BNK_6),
	bnk_7i(CAN_BNK_7),
	bnk_8i(CAN_BNK_8),
	bnk_9i(CAN_BNK_9),
	bnk_10i(CAN_BNK_10),
	bnk_11i(CAN_BNK_11),
	bnk_12i(CAN_BNK_12),
	bnk_13i(CAN_BNK_13),
	bnk_14i(CAN_BNK_14),
	
	//banks
	bnk_6((Can_filter_bank_imp*) NULL),
	bnk_7((Can_filter_bank_imp*) NULL),
	bnk_8((Can_filter_bank_imp*) NULL),
	bnk_9((Can_filter_bank_imp*) NULL),
	bnk_10((Can_filter_bank_imp*) NULL),
	bnk_11((Can_filter_bank_imp*) NULL),
	bnk_12((Can_filter_bank_imp*) NULL),
	bnk_13((Can_filter_bank_imp*) NULL),
	bnk_14((Can_filter_bank_imp*) NULL),
	
	/* filter tyes */
	//filter imps
	fil_6i(CAN_FIL_6),
	fil_7i(CAN_FIL_7),
	fil_8i(CAN_FIL_8),
	fil_9i(CAN_FIL_9),
	fil_10i(CAN_FIL_10),
	fil_11i(CAN_FIL_11),
	fil_12i(CAN_FIL_12),
	fil_13i(CAN_FIL_13),
	fil_14i(CAN_FIL_14),
	
	//filters
	fil_6((Can_filmask_imp*) NULL),
	fil_7((Can_filmask_imp*) NULL),
	fil_8((Can_filmask_imp*) NULL),
	fil_9((Can_filmask_imp*) NULL),
	fil_10((Can_filmask_imp*) NULL),
	fil_11((Can_filmask_imp*) NULL),
	fil_12((Can_filmask_imp*) NULL),
	fil_13((Can_filmask_imp*) NULL),
	fil_14((Can_filmask_imp*) NULL),
	
	/* mask types */
	//mask imps
	msk_6i(CAN_MSK_6),
	msk_7i(CAN_MSK_7),
	msk_8i(CAN_MSK_8),
	msk_9i(CAN_MSK_9),
	msk_10i(CAN_MSK_10),
	msk_11i(CAN_MSK_11),
	msk_11i(CAN_MSK_12),
	msk_11i(CAN_MSK_13),
	msk_11i(CAN_MSK_14),
	
	//masks
	msk_6((Can_filmask_imp*) NULL),
	msk_7((Can_filmask_imp*) NULL),
	msk_8((Can_filmask_imp*) NULL),
	msk_9((Can_filmask_imp*) NULL),
	msk_10((Can_filmask_imp*) NULL),
	msk_11((Can_filmask_imp*) NULL),
	msk_12((Can_filmask_imp*) NULL),
	msk_13((Can_filmask_imp*) NULL),
	msk_14((Can_filmask_imp*) NULL)
	#endif
	

// *** TARGET AGNOSTIC.
{
	// *** TARGET CONFIGURATION SPECIFIC.
	
	// NOTE - In the case of AVR devices, there is only one CAN peripheral, so we don't really have any logic here.
	
	// Complete the CAN tree.
	
	#if (defined (__AVR_ATmega64M1__) || defined(__AVR_AT90CAN128__))
	/* This target also has MOb 6-15 */
	
	/* ***** Linking to implemenation and adding to arrays ***** */
	/* buffer types */
	// set imps for buf interfacer
	buf_0.imp = &buf_0i;
	buf_1.imp = &buf_1i;
	buf_2.imp = &buf_2i;
	buf_3.imp = &buf_3i;
	buf_4.imp = &buf_4i;
	buf_5.imp = &buf_5i;
	
	// put the buffers in an array
	buffers[0] = &buf_0;
	buffers[1] = &buf_1;
	buffers[2] = &buf_2;
	buffers[3] = &buf_3;
	buffers[4] = &buf_4;
	buffers[5] = &buf_5;
	
	/* bank types */
	// set imps for bnk interfacer
	bnk_0.imp = &bnk_0i;
	bnk_1.imp = &bnk_1i;
	bnk_2.imp = &bnk_2i;
	bnk_3.imp = &bnk_3i;
	bnk_4.imp = &bnk_4i;
	bnk_5.imp = &bnk_5i;
	
	// put banks in an array
	banks[0] = &bnk_0;
	banks[1] = &bnk_1;
	banks[2] = &bnk_2;
	banks[3] = &bnk_3;
	banks[4] = &bnk_4;
	banks[5] = &bnk_5;
	
	/* filter types */
	// set imps for fil interfacer
	fil_0.imp = &fil_0i;
	fil_1.imp = &fil_1i;
	fil_2.imp = &fil_2i;
	fil_3.imp = &fil_3i;
	fil_4.imp = &fil_4i;
	fil_5.imp = &fil_5i;
	
	// put filters in an array
	filters[0] = &fil_0;
	filters[1] = &fil_1;
	filters[2] = &fil_2;
	filters[3] = &fil_3;
	filters[4] = &fil_4;
	filters[5] = &fil_5;

	/* mask types */
	// set imps for msk interfacer
	msk_0.imp = &msk_0i;
	msk_1.imp = &msk_1i;
	msk_2.imp = &msk_2i;
	msk_3.imp = &msk_3i;
	msk_4.imp = &msk_4i;
	msk_5.imp = &msk_5i;
	
	// put masks in an array
	masks[0] = &msk_0;
	masks[1] = &msk_1;
	masks[2] = &msk_2;
	masks[3] = &msk_3;
	masks[4] = &msk_4;
	masks[5] = &msk_5;
	
	#endif
	
	#if defined(__AVR_AT90CAN128__)
	/* buffer types */
	// set imps for buf interfacer
	buf_6.imp = &buf_6i;
	buf_7.imp = &buf_7i;
	buf_8.imp = &buf_8i;
	buf_9.imp = &buf_9i;
	buf_10.imp = &buf_10i;
	buf_11.imp = &buf_11i;
	buf_12.imp = &buf_12i;
	buf_13.imp = &buf_13i;
	buf_14.imp = &buf_14i;
	
	// put the buffers in an array
	buffers[6] = &buf_6;
	buffers[7] = &buf_7;
	buffers[8] = &buf_8;
	buffers[9] = &buf_9;
	buffers[10] = &buf_10;
	buffers[11] = &buf_11;
	buffers[12] = &buf_12;
	buffers[13] = &buf_13;
	buffers[14] = &buf_14;
	
	/* bank types */
	// set imps for bnk interfacer
	bnk_6.imp = &bnk_6i;
	bnk_7.imp = &bnk_7i;
	bnk_8.imp = &bnk_8i;
	bnk_9.imp = &bnk_9i;
	bnk_10.imp = &bnk_10i;
	bnk_11.imp = &bnk_11i;
	bnk_12.imp = &bnk_12i
	bnk_13.imp = &bnk_13i
	bnk_14.imp = &bnk_14i
	
	// put banks in an array
	banks[6] = &bnk_6;
	banks[7] = &bnk_7;
	banks[8] = &bnk_8;
	banks[9] = &bnk_9;
	banks[10] = &bnk_10;
	banks[11] = &bnk_11;
	banks[12] = &bnk_12;
	banks[13] = &bnk_13;
	banks[14] = &bnk_14;
	
	/* filter types */
	// set imps for fil interfacer
	fil_6.imp = &fil_6i;
	fil_7.imp = &fil_7i;
	fil_8.imp = &fil_8i;
	fil_9.imp = &fil_9i;
	fil_10.imp = &fil_10i;
	fil_11.imp = &fil_11i;
	fil_12.imp = &fil_12i;
	fil_13.imp = &fil_13i;
	fil_14.imp = &fil_14i;
	
	// put filters in an array
	filters[6] = &fil_6;
	filters[7] = &fil_7;
	filters[8] = &fil_8;
	filters[9] = &fil_9;
	filters[10] = &fil_10;
	filters[11] = &fil_11;
	filters[12] = &fil_12;
	filters[13] = &fil_13;
	filters[14] = &fil_14;

	/* mask types */
	// set imps for msk interfacer
	msk_6.imp = &msk_6i;
	msk_7.imp = &msk_7i;
	msk_8.imp = &msk_8i;
	msk_9.imp = &msk_9i;
	msk_10.imp = &msk_10i;
	msk_11.imp = &msk_11i;
	msk_12.imp = &msk_12i;
	msk_13.imp = &msk_13i;
	msk_14.imp = &msk_14i;
	
	// put masks in an array
	masks[6] = &msk_6;
	masks[7] = &msk_7;
	masks[8] = &msk_8;
	masks[9] = &msk_9;
	masks[10] = &msk_10;
	masks[11] = &msk_11;
	masks[12] = &msk_12;
	masks[13] = &msk_13;
	masks[14] = &msk_14;
	#endif
	
	/* ***** Assembling tree ***** */
	
	for (uint8_t i=0; i<CAN_NUM_BANKS; i++)
	{
		banks[i]->imp->buffer_link = buffers[i];
		banks[i]->imp->filmasks[0] = filters[i];
		banks[i]->imp->filmasks[1] = masks[i];
		
		buffers[i]->imp->bank_link = banks[i];
	}
	
	// *** TARGET AGNOSTIC.
	
	// All done.
	return;
}

Can_config_status Can_imp::initialise(Can_rate rate)
{
	/* reset CAN peripheral */
	Can_reset();
	
	
	for (uint8_t i=0; i<CAN_NUM_BUFFERS; i++)
	{
		Can_full_abort();
		Can_clear_mob();
		Can_clear_mask_mob();
		
		buffers[i]->clear_status();
		buffers[i]->set_mode(CAN_OBJ_DISABLE);
	}
	
	/* baud rate pre-scaler settings */
	uint8_t CONF_CANBT1 = 0x00;
	uint8_t CONF_CANBT2 = 0x00;
	uint8_t CONF_CANBT3 = 0x00;
	
	//Set CANBT registers to obtain correct baud rate given clock speed
	if (CLK_MHZ == 16)
	{
		if (rate == CAN_100K)		//< -- 100Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x12;       // Tscl  = 10x Tclkio = 625 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_125K)	//< -- 125Kb/s, 16x Tscl, sampling at 75%	
		{
			CONF_CANBT1 = 0x0E;       // Tscl  = 8x Tclkio = 500 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points	
		}
		else if (rate == CAN_200K)	//< -- 200Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 312.5 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_250K)	//< -- 250Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x0E;       // Tscl  = 4x Tclkio = 250 ns
			CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_500K)  //< -- 500Kb/s, 8x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x02;       // Tscl = 4x Tclkio = 125 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
		else if (rate == CAN_1000K)
		{
			CONF_CANBT1 = 0x00;       // Tscl  = 2x Tclkio = 0.0625 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x36;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}		
	}
	if (CLK_MHZ == 12)
	{
		if (rate == CAN_100K)      //< -- 100Kb/s, 20x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0A;       // Tscl  = 6x Tclkio = 500 ns
			CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K) //< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0A;       // Tscl  = 6x Tclkio = 500 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_200K) //< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x04;       // Tscl  = 3x Tclkio = 250 ns
			CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
		else if (rate == CAN_250K) //< -- 250Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x0A;       // Tscl  = 3x Tclkio = 250 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K) //< -- 500Kb/s, 12x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 166.666 ns
			CONF_CANBT2 = 0x08;       // Tsync = 1x Tscl, Tprs = 5x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x25;       // Tpsh1 = 3x Tscl, Tpsh2 = 3x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K) //< -- 1 Mb/s, 12x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 83.333 ns
	        CONF_CANBT2 = 0x08;       // Tsync = 1x Tscl, Tprs = 5x Tscl, Tsjw = 1x Tscl
            CONF_CANBT3 = 0x25;       // Tpsh1 = 3x Tscl, Tpsh2 = 3x Tscl, 3 sample points
		}
	}
	if (CLK_MHZ == 8)
	{
		if (rate == CAN_100K)       //< -- 100Kb/s, 16x Tscl, sampling at 75%
	    {
			//only works for ATMega64M1
	        CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 625 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)  //< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			//only works for ATMega64M1
	        CONF_CANBT1 = 0x0E;       // Tscl  = 4x Tclkio = 500 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points

		}
	    else if (rate == CAN_200K)  //< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
			//isn't supported by PCAN
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_250K)  //< -- 250Kb/s, 16x Tscl, sampling at 75%
	    {
			//only works for ATMega64M1
	        CONF_CANBT1 = 0x06;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)  //< -- 500Kb/s, 8x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x00;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x36;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K) //< -- 1 Mb/s, 8x Tscl, sampling at 75%
	    {
			//sparringly works for both chips, have to be careful about bus length and capacitance etc
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 125 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	}
	Can_conf_bt();	//write CONF_CANBTx values to registers to set baud rate
	Can_enable();	//write to CANGCON register to enable controller
	
	/* CAN peripheral is not immediately enabled, poll until timeout 
	 * before return fail code */
	uint32_t poll_t = ENABLE_TOUT_LOOP;
	while (~(CANGSTA & (1<<ENFG)) && poll_t)
	{
		poll_t -= 1;
	}
	
	if (poll_t > 0)
	{
		return CAN_CFG_SUCCESS;
	}
	else
	{
		return CAN_CFG_FAILED;
	}
}

void Can_imp::enable_interrupts(void)
{
	CANGIE |= (1<<ENIT);	
}

void Can_imp::disable_interrupts(void)
{
	CANGIE &= ~(1<<ENIT);
}

Can_int_status Can_imp::attach_interrupt(Can_channel_interrupt_type interrupt, void (*callback)(void))
{
	Can_int_status ret_code;
	
	/* determine return code */
	if (chanIntFunc[interrupt])
	{
		ret_code = CAN_INT_EXISTS;	// replacing an exsting callback
	}
	else
	{
		ret_code = CAN_INT_NOINT;	// added a new callback
	}
	
	/* unmasking the interrupt vectors, unlike buffers, this is bus-wide
	 * so mask does get turned off and on when the callbacks are detached
	 * and re-attached */
	switch (interrupt)
	{
		case (CAN_TIME_OVERRUN):
			CANGIE |= (1<<ENOVRT);
			break;
		case (CAN_BUS_OFF):
			CANGIE |= (1<<ENBOFF);
			break;
	}	
	
	chanIntFunc[interrupt] = callback;	// attach callback
	
	return ret_code;
}

Can_int_status Can_imp::detach_interrupt(Can_channel_interrupt_type interrupt)
{
	Can_int_status ret_code;
	
	/* determine return code */
	if (chanIntFunc[interrupt])
	{
		ret_code = CAN_INT_EXISTS;	// removed a callback
	}
	else
	{
		ret_code = CAN_INT_NOINT;	// there was no callback to remove
	}
	
	/* masking the interrupt vectors, unlike buffers, this is bus-wide
	 * so mask does get turned off and on when the callbacks are detached
	 * and re-attached */
	switch(interrupt)
	{
		case (CAN_TIME_OVERRUN):
			CANGIE &= ~(1<<ENOVRT);
			break;
		case (CAN_BUS_OFF):
			CANGIE &= ~(1<<ENBOFF);			
			break;
	}
	
	chanIntFunc[interrupt] = NULL;	// detach callblack
	
	return ret_code;
}

bool Can_imp::test_interrupt(Can_channel_interrupt_type interrupt)
{
	switch(interrupt)
	{
		case(CAN_TIME_OVERRUN): return (CANGIE & (1<<ENOVRT));
		case(CAN_BUS_OFF): 		return (CANGIE & (1<<ENBOFF));
		default: 				return false;
	}
}

Can_int_status Can_imp::clear_interrupt_flags(Can_channel_interrupt_type interrupt)
{
	Can_int_status ret_code = CAN_INT_NOINT;

	/* writing logical one resets the flag */
	switch(interrupt)
	{
		case (CAN_BUS_OFF):
			/* determine return code */
			if (CANGIT & (1<<BOFFIT))
			{
				ret_code = CAN_INT_EXISTS;	
			}
			else
			{
				ret_code = CAN_INT_NOINT;	// interrupt flag was never set
			}
			CANGIT |= (1<<BOFFIT);		// clearing flag
			break;
			
		case (CAN_TIME_OVERRUN): 
			/* determine return code */
			if (CANGIT & (1<<OVRTIM))
			{
				ret_code = CAN_INT_EXISTS;
			}
			else
			{
				ret_code = CAN_INT_NOINT;	// interrupt flag was never set
			}
			CANGIT |= (1<<OVRTIM);
			break;
	}
	
	return ret_code;
}

uint8_t Can_imp::get_num_banks(void)
{
	return CAN_NUM_BUFFERS;	//1 to 1 correspondence between buffers and banks in AVR
}

Can_filter_bank** Can_imp::get_banks(void)
{
	return banks;
}

uint8_t Can_imp::get_num_buffers(void)
{
	return CAN_NUM_BUFFERS;
}

Can_buffer** Can_imp::get_buffers(void)
{
	return buffers;
}


// IMPLEMENT INTERRUPT SERVICE ROUTINES.
/* Note: HAL functions not used here because of speed and also 
 * because they cannot be accessed from here */
 
// CAN transfer complete or error vector
SIGNAL(GEN_CAN_IT_VECT)
{
	in_interrupt = true;
	
	/* find out whether a mob interrupt occured */
	uint8_t canhpmob_copy_masked = CANHPMOB & 0b1111<<4;
	if (canhpmob_copy_masked)
	{
		CANPAGE &= ~(0b1111<<4);					//clear mob selection bits
		CANPAGE |= canhpmob_copy_masked;	//select highest priority mob	
		interrupt_service_buffer = static_cast<Can_id_buffer>(canhpmob_copy_masked>>4);
		
		/* check MOb status and check whether the callback pointer valid before executing */
		if ((CANSTMOB & MOB_RX_COMPLETED) && (bufIntFunc[interrupt_service_buffer][CAN_RX_COMPLETE]))
		{
			bufIntFunc[interrupt_service_buffer][CAN_RX_COMPLETE]();
		}
		else if ((CANSTMOB & MOB_TX_COMPLETED) && (bufIntFunc[interrupt_service_buffer][CAN_TX_COMPLETE]))
		{
			bufIntFunc[interrupt_service_buffer][CAN_TX_COMPLETE]();
		}
		else if ((CANSTMOB & ERR_MOB_MSK) && (bufIntFunc[interrupt_service_buffer][CAN_GEN_ERROR]))
		{
			bufIntFunc[interrupt_service_buffer][CAN_GEN_ERROR]();
		}
		
		// user must clear interrupt flag on their callback function
	}
	
	// execute channel interrupt callback
	if (CANGIT & (1<<6))
	{
		chanIntFunc[CAN_BUS_OFF]();
	}
	
	in_interrupt = false;
}

// CAN timer overrun vector
SIGNAL(OVR_TIM_IT_VECT)
{
	chanIntFunc[CAN_TIME_OVERRUN]();
}

// ALL DONE.
