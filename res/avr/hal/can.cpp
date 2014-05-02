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

#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

#define ENABLE_TOUT_MS  1000;				// Controller enable timeout.

//different interrupt vector names for different micros
#if defined(__AVR_AT90CAN128__)
	#define GEN_CAN_IT_VECT CANIT_vect
	#define OVR_TIM_IT_VECT OVRIT_vect
#elif defined (__AVR_ATmega64M1__)
	#define GEN_CAN_IT_VECT CAN_INT_vect
	#define OVR_TIM_IT_VECT CAN_TOVF_vect
#endif

// DEFINE PRIVATE MACROS.

#define CLK_MHZ <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>

// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

/**
 * Private, target specific implementation class for public Can_filter class.
 */
class Can_filter_imp
{
	public:
	
		// Methods.

		/**
		 * Create a new Can_filer_imp which controls the specified CAN filter.
		 * 
		 * @param	filter	The id of the CAN filter for this driver to interface with.
		 */
		 Can_filter_imp(Can_id_filter filter);
		 
		/**
		* Gets the current filter value being used by the hardware filter.
		*
		* @param	Nothing.
		* @return	The current filter value.
		*/
		 uint32_t get(void);
		
		/**
		* Sets the filter value being used by the hardware filter/mask.
		*
		* @param	value	The new value for the filter.
		* @return	Nothing.
		*/
		 void set(Can_filmask_value value);
		
	private:
	
		// Methods.
		
		Can_filter_imp(void);	// Poisoned.

		Can_filter_imp(Can_filter_imp*);	// Poisoned.

		Can_filter_imp operator =(Can_filter_imp const&);	// Poisoned.

		//Fields.		
};

/**
 * Private, target specific implementation class for public Can_imp class.
 */
class Can_mask_imp
{
	public:
		
		// Methods.
		
		/**
		 * Create a new Can_mask_imp which controls the specified CAN mask.
		 * 
		 * @param	mask	The id of the CAN mask for this driver to interface with.
		 */
		 Can_mask_imp(Can_id_mask mask);
		
		/**
		 * Gets the current mask value being used by the hardware filter/mask.
		 * 
		 * @param    Nothing.
		 * @return   The current mask value.
		 */
		uint32_t get(void);
		
		/**
		 * Sets the filter value being used by the hardware filter/mask.
		 * 
		 * @param    value    New value for this mask.
		 * @return   	      Nothing.
		 */
		void set(Can_filmask_value value);
		
	private:

		// Methods.
		
		Can_mask_imp(void);	// Poisoned.

		Can_mask_imp(Can_mask_imp*);	// Poisoned.

		Can_mask_imp operator =(Can_mask_imp const&);	// Poisoned.
	
		// Fields.	
};

/**
 * Private, target specific implementation class for public Can_filter_bank class.
 */
class Can_filter_bank_imp
{
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
};

/**
 * Private, target specific implementation class for public Can_buffer class.
 */
class Can_buffer_imp
{
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
		bool set_mode(Can_buffer_mode mode);
		
		/**
		* Returns the current status of the object.
		*
		* @param	Nothing.
		* @return	The current status of the buffer (one of possible CAN_BUF_STATs).
		*/
		Can_buffer_status get_status(void);
		
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
		* @param	callback	The handler for this interrupt condition.
		*/
		void attach_interrupt(Can_interrupt_type interrupt, void (*callback)(void));
		
		/**
		* Removes a handler for a specific object for a particular interrupt event.
		*
		* @param	interrupt	The interrupt condition to dettach the handler from.
		* @return	Nothing.	
		*/
		void detach_interrupt(Can_interrupt_type interrupt);
		
		/**
		 * Boolean describing whether an interrupt handler is set for this condition
		 * on this buffer.
		 * 
		 * @param   interrupt   The MOb interrupt condition to test if enabled.
		 * @return              Flag indicating whether an interrupt handler is set for this condition.
		 *
		 */
		bool test_interrupt(Can_interrupt_type interrupt);
		
	private:
		
		// Methods.
		
		Can_buffer_imp(void);	// Poisoned.

		Can_buffer_imp(Can_buffer_imp*);	// Poisoned.

		Can_buffer_imp operator =(Can_buffer_imp const&);	// Poisoned.

		// Fields.
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
		bool initialise(Can_rate rate);

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
		 * @return    Nothing.
		 */
		void attach_interrupt(Can_interrupt_type interrupt, void (*callback)(void));
	    
		/**
		 * Detach interrupt for channel based event.
		 * 
		 * @param     interrupt		The interrupt event to detach the handler from.
		 * @return    Nothing.
		 */
		void detach_interrupt(Can_interrupt_type interrupt);
	    
		/**
		 * Test whether an interrupt handler is attached to an channel based event.
		 * 
		 * @param     interrupt		The interrupt event to test.
		 * @return    Flag indicating whether interrupt event has an existing handler.
		 */
		bool test_interrupt(Can_interrupt_type interrupt);
	    
		/**
		 * Clear interrupt flag for channel based events.  If called outside an ISR, this probably doesn't do anything useful.
		 * 
		 * @param	 interrupt      The interrupt event flag to clear.
		 * @return    Nothing.
		 */
		void clear_controller_interrupts(Can_interrupt_type interrupt);

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
			
			Can_buffer_imp buf_0i;
			Can_buffer buf_0;
			
			Can_buffer_imp buf_1i;
			Can_buffer buf_1;
			
			Can_filter_bank* banks[CAN_NUM_BANKS];
			
			Can_filter_bank_imp bnk_0i;
			Can_filter_bank bnk_0;
			
			Can_filter_bank_imp bnk_1i;
			Can_filter_bank bnk_1;
			
			Can_filter* filters[CAN_NUM_FILTERS];
			
			Can_filter_imp fil_0i;
			Can_filter fil_0;
			
			Can_filter_imp fil_1i;
			Can_filter fil_1;
			
			Can_filter_imp fil_2i;
			Can_filter fil_2;
			
			Can_mask* masks[CAN_NUM_MASKS];
			
			Can_mask_imp msk_0i;
			Can_mask msk_0;
			
			Can_mask_imp msk_1i;
			Can_mask msk_1;
			
			Can_mask_imp msk_2i;
			Can_mask msk_2;
			
			// *** TARGET AGNOSTIC.
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

// Can_filmask.

Can_filmask::~Can_filmask(void)
{
	// This is a pure virtual destructor for an abstract base class.  It does not do anything.
	return;
}

// Can_filter.

Can_filter::Can_filter(Can_filter_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

uint32_t Can_filter::get(void)
{
	return imp->get();
}

void Can_filter::set(Can_filmask_value value)
{
	imp->set(value);
}

// Can_mask.

Can_mask::Can_mask(Can_mask_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

uint32_t Can_mask::get(void)
{
	return imp->get();
}

void Can_mask::set(Can_filmask_value value)
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

bool Can_buffer::set_mode(Can_buffer_mode mode)
{
	return imp->set_mode(mode);
}

Can_buffer_status Can_buffer::get_status(void)
{
	return imp->get_status();
}

Can_message Can_buffer::read(void)
{
	return imp->read();
}

void Can_buffer::write(Can_message msg)
{
	imp->write(msg);
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

void Can_buffer::attach_interrupt(Can_interrupt_type interrupt, void (*callback)(void))
{
	imp->attach_interrupt(interrupt, callback);
}

void Can_buffer::detach_interrupt(Can_interrupt_type interrupt)
{
	imp->detach_interrupt(interrupt);
}

bool Can_buffer::test_interrupt(Can_interrupt_type interrupt)
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

bool Can::initialise(Can_rate rate)
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

void Can::attach_interrupt(Can_interrupt_type interrupt, void (*callback)(void))
{
	imp->attach_interrupt(interrupt, callback);
}

void Can::detach_interrupt(Can_interrupt_type interrupt)
{
	imp->detach_interrupt(interrupt);
}

bool Can::test_interrupt(Can_interrupt_type interrupt)
{
	return imp->test_interrupt(interrupt);
}

void Can::clear_controller_interrupts(Can_interrupt_type interrupt)
{
	imp->clear_controller_interrupts(interrupt);
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

// Can_filter.

Can_filter_imp::Can_filter_imp(Can_id_filter filter){}

uint32_t Can_filter_imp::get(void){return 0;}

void Can_filter_imp::set(Can_filmask_value value){}

// Can_mask.

Can_mask_imp::Can_mask_imp(Can_id_mask mask){}

uint32_t Can_mask_imp::get(void){return 0;}

void Can_mask_imp::set(Can_filmask_value value){}

// Can_filter_bank.

Can_filter_bank_imp::Can_filter_bank_imp(Can_id_bank bank){}

Can_buffer* Can_filter_bank_imp::get_buffer(void){}

Can_config_status Can_filter_bank_imp::set_buffer(Can_buffer& buffer){}

Can_bank_mode Can_filter_bank_imp::get_mode(void){}

Can_config_status Can_filter_bank_imp::set_mode(Can_bank_mode mode){}

uint8_t Can_filter_bank_imp::get_num_filmasks(void){}

Can_filmask** Can_filter_bank_imp::get_filmasks(void){}

// Can_buffer.

Can_buffer_imp::Can_buffer_imp(Can_id_buffer buffer){}

Can_buffer_mode Can_buffer_imp::get_mode(void){}

bool Can_buffer_imp::get_multimode(void){}

bool Can_buffer_imp::set_mode(Can_buffer_mode mode){}

Can_buffer_status Can_buffer_imp::get_status(void){}

Can_message Can_buffer_imp::read(void){}

void Can_buffer_imp::write(Can_message msg){}

void Can_buffer_imp::clear_status(void){}

void Can_buffer_imp::enable_interrupt(void){}

void Can_buffer_imp::disable_interrupt(void){}

void Can_buffer_imp::attach_interrupt(Can_interrupt_type interrupt, void (*callback)(void)){}

void Can_buffer_imp::detach_interrupt(Can_interrupt_type interrupt){}

bool Can_buffer_imp::test_interrupt(Can_interrupt_type interrupt){}

// Can.

Can_imp::Can_imp(Can_id_controller controller) :

// *** TARGET CONFIGURATION SPECIFIC.

// NOTE - We have to use an initialiser list here.

buf_0i(CAN_BUF_0),
buf_0((Can_buffer_imp*) NULL),
buf_1i(CAN_BUF_1),
buf_1((Can_buffer_imp*) NULL),
bnk_0i(CAN_BNK_0),
bnk_0((Can_filter_bank_imp*) NULL),
bnk_1i(CAN_BNK_1),
bnk_1((Can_filter_bank_imp*) NULL),
fil_0i(CAN_FIL_0),
fil_0((Can_filter_imp*) NULL),
fil_1i(CAN_FIL_1),
fil_1((Can_filter_imp*) NULL),
fil_2i(CAN_FIL_2),
fil_2((Can_filter_imp*) NULL),
msk_0i(CAN_MSK_0),
msk_0((Can_mask_imp*) NULL),
msk_1i(CAN_MSK_1),
msk_1((Can_mask_imp*) NULL),
msk_2i(CAN_MSK_2),
msk_2((Can_mask_imp*) NULL)

// *** TARGET AGNOSTIC.
{
	// *** TARGET CONFIGURATION SPECIFIC.
	
	// NOTE - In the case of AVR devices, there is only one CAN peripheral, so we don't really have any logic here.
	
	// Complete the CAN tree.
	
	buf_0.imp = &buf_0i;
	buffers[0] = &buf_0;
	
	buf_1.imp = &buf_1i;
	buffers[1] = &buf_1;
	
	bnk_0.imp = &bnk_0i;
	banks[0] = &bnk_0;
	
	bnk_1.imp = &bnk_1i;
	banks[1] = &bnk_1;
	
	fil_0.imp = &fil_0i;
	filters[0] = &fil_0;

	fil_1.imp = &fil_1i;
	filters[1] = &fil_1;
	
	fil_2.imp = &fil_2i;
	filters[2] = &fil_2;

	msk_0.imp = &msk_0i;
	masks[0] = &msk_0;

	msk_1.imp = &msk_1i;
	masks[1] = &msk_1;
	
	msk_2.imp = &msk_2i;
	masks[2] = &msk_2;
	
	// *** TARGET AGNOSTIC.
	
	// All done.
	return;
}

bool Can_imp::initialise(Can_rate rate){}

void Can_imp::enable_interrupts(void){}

void Can_imp::disable_interrupts(void){}

void Can_imp::attach_interrupt(Can_interrupt_type interrupt, void (*callback)(void)){}

void Can_imp::detach_interrupt(Can_interrupt_type interrupt){}

bool Can_imp::test_interrupt(Can_interrupt_type interrupt){}

void Can_imp::clear_controller_interrupts(Can_interrupt_type interrupt){}

uint8_t Can_imp::get_num_banks(void){}

Can_filter_bank** Can_imp::get_banks(void){}

uint8_t Can_imp::get_num_buffers(void){}

Can_buffer** Can_imp::get_buffers(void){}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// ALL DONE.


























/*
volatile static voidFuncPtr intFunc[NB_BUF][NB_INT];
volatile CAN_BUF interrupt_service_buffer;
*/

/*void Can_buffer::set_number(uint8_t buf_num)
{
	buf_no = buf_num;
}

uint8_t Can_buffer::get_number(void)
{
	return buf_no;
}

CAN_BUF_MODE Can_buffer::get_mode(void)
{
	return mode;	
}

bool Can_buffer::get_multimode(void)
{
	return true;	//true for AVR implementation
}

bool Can_buffer::set_mode(CAN_BUF_MODE mode)
{
	Can_set_mob(buf_no);	//set CANPAGE to MOb of interest
	
	switch (mode)
	{
		case (CAN_OBJ_RX):
			Can_config_rx();
			mode = CAN_OBJ_RX;
			break;
	
		case (CAN_OBJ_TX):
			Can_config_tx();
			mode = CAN_OBJ_TX;	
			break;
			
		case (CAN_OBJ_RXB):
			Can_config_rx_buffer();
			mode = CAN_OBJ_RXB;
			break;
			
		case (CAN_OBJ_DISABLE):
			DISABLE_MOB;
			mode = CAN_OBJ_DISABLE;
	}
	return true;	//maybe this should return void
}

Can_message Can_buffer::read(void)
{
	Can_set_mob(buf_no);	//set CANPAGE to MOb of interested
	
	Can_message msg;
	msg.dlc = Can_get_dlc();
	for (uint8_t i=0; i<msg.dlc; i++)
	{
		msg.data[i] = CANMSG; 		//reading data from buffer, note CANMSG is auto-incremented
	}
	
	return msg;
}

void Can_buffer::write(Can_message msg)
{
	Can_set_mob(buf_no);	//set CANPAGE to MOb of interested
	Can_clear_dlc();
	Can_set_dlc(msg.dlc);
	for (uint8_t i=0; i<msg.dlc; i++)
	{
		CANMSG = msg.data[i];	//writing data to buffer, note CANMSG is auto-incremented
	}
}

void Can_buffer::clear_status(void)
{
	Can_set_mob(buf_no);
	Can_clear_status_mob();
}

CAN_BUF_STAT Can_buffer::get_status(void)
{	
	Can_set_mob(buf_no);
	uint8_t canstmob_copy = CANSTMOB;	//copy for test integrity
	
	if ((CANCDMOB & CONMOB_MSK) == 0x00)
	{
		return BUF_DISABLE;
	}
	
	switch (canstmob_copy)
	{
		case (MOB_RX_COMPLETED):
			return BUF_RX_COMPLETED;
		case (MOB_TX_COMPLETED):
			return BUF_TX_COMPLETED;
		case (MOB_RX_COMPLETED_DLCW):
			return BUF_RX_COMPLETED_DLCW;
		case (MOB_ACK_ERROR):
			return BUF_ACK_ERROR;
		case (MOB_FORM_ERROR):
			return BUF_FORM_ERROR;
		case (MOB_CRC_ERROR):
			return BUF_CRC_ERROR;
		case (MOB_STUFF_ERROR):
			return BUF_STUFF_ERROR;
		case (MOB_BIT_ERROR):
			return BUF_BIT_ERROR;
		case (0x00):
			return BUF_NOT_COMPLETED;
	}
}

void Can_buffer::enable_interrupt(void)
{
	if (buf_no < 8)
	{
		CANIE2 |= (1<<(buf_no));
	}
	else
	{
		CANIE1 |= (1<<(buf_no-8));
	}
}

void Can_buffer::disable_interrupt(void)
{
	if (buf_no < 8)
	{
		CANIE2 &= ~(1<<(buf_no));
	}
	else
	{
		CANIE1 &= ~(1<<(buf_no));
	}
}

void Can_buffer::attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void))
{
	//note: interrupt handler is only attached to one buffer, but the interrupt event is universally enabled	
	switch(interrupt)
	{
		case (CAN_RX_COMPLETE):	
			CANGIE |= (1 << ENRX);
			intFunc[buf_no][interrupt] = userFunc;
			break;
		case (CAN_TX_COMPLETE):
			CANGIE |= (1 << ENTX);
			intFunc[buf_no][interrupt] = userFunc;
			break;
		case (CAN_GEN_ERROR):
			CANGIE |= (1 << ENERG);
			intFunc[buf_no][interrupt] = userFunc;
			break;
		default:
			//do nothing, this case is used to prevent warnings
			break;
	}
}

void Can_buffer::detach_interrupt(CAN_INT_NAME interrupt)
{
	Can_set_mob(buf_no);
	switch(interrupt)
	{
		case (CAN_RX_COMPLETE):
			CANGIE &= ~(1 << ENRX);
			break;
		case (CAN_TX_COMPLETE):
			CANGIE &= ~(1 << ENTX);
			break;
		case (CAN_GEN_ERROR):
			CANGIE &= ~(1 << ENERG);
			break;
		default:
			//do nothing, this case is used to prevent warnings
			break;
	}
}

bool Can_buffer::test_interrupt(CAN_INT_NAME interrupt)
{
	Can_set_mob(buf_no);
	switch(interrupt)
	{
		case (CAN_RX_COMPLETE):
			return (CANGIE & (1 << ENRX));
		case (CAN_TX_COMPLETE):
			return (CANGIE & (1 << ENTX));
		case (CAN_GEN_ERROR):
			return (CANGIE & (1 << ENERG));
		default:
			return false;
	}
}

void Can_filter::set_number(uint8_t fil_num)
{
	fil_no = fil_num;
}

Can_buffer* Can_filter::get_buffer(void)
{
	return buffer_link;
}

void Can_filter::set_buffer(Can_buffer* buffer)
{
	buffer_link = buffer;
}

Can_mask* Can_filter::get_mask(void)
{
	return mask_link;
}

void Can_filter::set_mask(Can_mask* mask)
{
	mask_link = mask;
}

bool Can_filter::get_routable(void)
{
	return false;	//Always false for AVRs since their link is fixed
}

uint32_t Can_filter::get_filter_val(void)
{
	return filter_data;
}

void Can_filter::set_filter_val(uint32_t filter, bool RTR)
{
	Can_set_mob(fil_no);	//For AVRs, filters are not distinct from MOb
	Can_set_ext_id(filter);
	
	if (RTR)
	{
		Can_set_rtr();
	}
	else
	{
		Can_clear_rtr();
	}
	
	filter_data = filter;	//store as field so registers don't need to be accessed again
}

void Can_mask::set_number(uint8_t msk_num)
{
	msk_no = msk_num;
}

uint32_t Can_mask::get_mask_val(void)
{
	return mask_data;
}

void Can_mask::set_mask_val(uint32_t mask, bool RTR)
{
	Can_set_mob(msk_no);	//For AVRs, masks are not distinct from MOb
	Can_set_ext_msk(mask);
	
	if (RTR)
	{
		Can_set_rtrmsk();
	}
	else
	{
		Can_clear_rtrmsk();
	}
	mask_data = mask;	//store as field so registers don't need to be accessed again
}

*/

/**
 * Actual implementation of Can controller, all instances of Can controller
 * created will point to an instance of this class. There will be as many
 * instances as there are controllers in hardware. This class serves as
 * a parent class to enclose the smaller elements and also a manager
 * for CAN channel fields and methods. 
 * 
 * Though not meant to be interfaced by user, functions are declared 
 * public because it is not declared in header and thus is invisible 
 * outside this source.
 */

//class Can_tree
//{
//	public:
//	//Methods
//		/**
//		 * Constructor for AVR specific implementation:
//		 * Buffers and filters are created and assigned arbitrary indices,
//		 * each filter is then linked to its respective buffer by this index.
//		 */
//		Can_tree(void);
//		
//		/**
//		 * Enables the controller
//		 */
//		void enable(void);
//		
//		/**
//		 * Enable interrupts on the controller
//		 */
//		void enable_interrupts(void);
//		
//		/**
//		 * Disables interrupts on the controller
//		 */
//		void disable_interrupts(void);
//		
//		/**
//		 * Attach CAN channel interrupts, will overwrite existing interrupt
//		 * 
//		 * @param    interrupt   The interrupt condition to attach the handler to
//		 * @param    userFunc     The handler for this interrupt condition.
//		 * 
//		 */
//		void attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void));
//		
//		/**
//		 * Detach interrupt to CAN channel
//		 * 
//		 * @param    interrupt   The interrupt condition to detach the handler from
//		 */
//		void detach_interrupt(CAN_INT_NAME interrupt);
//		
//		/**
//		 * Returns true if interrupt condition has handler attached
//		 * 
//		 * @param    interrupt   The bus interrupt condition to test if enabled 
//		 * @return   Boolean describing whether an interrupt handler is set for this condition
//		 * 
//		 */ 			 
//		bool test_interrupt(CAN_INT_NAME interrupt);
//		
//	
//	//Fields
//		Can_mask mask[NB_MSK];
//		Can_filter filter[NB_FIL];
//		Can_buffer buffer[NB_BUF];
//};

/*
Can_tree::Can_tree(void)
{
	for (uint8_t i=0; i<static_cast<uint8_t>(NB_BUF); i++)
	{
		buffer[i].set_number(static_cast<CAN_BUF>(i));	//assign arbitrary index to buffer, CANPAGE access uses this number
	}
	
	for (uint8_t i=0; i<static_cast<uint8_t>(NB_FIL); i++)
	{  
		filter[i].set_number(i);	//assign arbitrary index to filter
		filter[i].set_buffer(&buffer[i]);	//link filter to corresponding buffer using index
		filter[i].set_mask(&mask[i]);		//link mask to corresponding filter using index
	}
	
	for (uint8_t i=0; i<static_cast<uint8_t>(NB_MSK); i++)
	{
		CAN_MSK n = static_cast<CAN_MSK>(i);
		mask[n].set_number(n);
	}
	
	return;
}

void Can_tree::enable(void)
{
	Can_enable();
}

void Can_tree::enable_interrupts(void)
{
	CANGIE |= (1<<ENIT);	
}

void Can_tree::disable_interrupts(void)
{
	CANGIE &= ~(1<<ENIT);
}

void Can_tree::attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void))
{
	bool interrupt_valid;
	switch (interrupt)
	{
		case (CAN_TIME_OVERRUN):
			CANGIE |= (1 << ENOVRT);
			interrupt_valid = true;
			break;
		case (CAN_BUS_OFF):
			CANGIE |= (1 << ENBOFF);
			interrupt_valid = true;
			break;
		default:
			interrupt_valid = false;
			break;
	}
	
	if (interrupt_valid)	
	{
		//for channel based interrupts, must apply to ALL MOb vectors due to the way interrupt functions are addressed
		for (uint8_t i=BUF_0; i<NB_BUF; i++)
		{
			intFunc[i][interrupt];	
		}
	}
}

void Can_tree::detach_interrupt(CAN_INT_NAME interrupt)
{
	switch(interrupt)
	{
		case (CAN_TIME_OVERRUN):
			CANGIE &= ~(1<<ENOVRT);
			break;
		case (CAN_BUS_OFF):
			CANGIE &= ~(1<<ENBOFF);
			break;
		default:
			//do nothing, this case is used to prevent warnings
			break;
	}
}

bool Can_tree::test_interrupt(CAN_INT_NAME interrupt)
{
	switch(interrupt)
	{
		case (CAN_TIME_OVERRUN):
			return (CANGIE & (1<<ENOVRT));
		case (CAN_BUS_OFF):
			return (CANGIE & (1<<ENBOFF));
		default:
			return false;
	}		
}

static Can_tree Can_tree_imps[NB_CTRL];

*/
/**********************************************************************/

/**
 * Interface class for CAN controller, users create an instance of this 
 * and links it to the pre-instantiated instance reflecting the single
 * hardware CAN controller
 * 
 * Example usage transmitting 'Hello world' over CAN:
 * init_hal();						//hal library mainly covers semaphores which are not used for CAN but still think its better to call this
 * int_on();						//turn interrupts on (not sure if this applies to CAN interrupts)
 * 
 * Can my_can = Can::bind(CAN_0);	//link to hardware implementation
 * my_can.initialize(CAN_500K);		//set the baud rate to 500K
 * 
 * Can_message my_msg;
 * my_msg.id = 0x00;
 * my_msg.dlc = 8;
 * my_msg.data = "01234567";		//note: this represents a message, its not a string literal
 * my_can.transmit(OBJ_0, my_msg);	//transmit message using buffer 0
 */
 /*
Can::Can(Can_tree* imp)
{
	Can_controller = imp;	
	return;
}

//Method implementations
Can Can::bind(CAN_CTRL controller)
{
	if (!can_initialised)
	{
		init_can();
	}

	int_off();
	if (Can_tree_imps[controller].TX_pin_s->check_free() && Can_tree_imps[controller].RX_pin_s->check_free())
	{
		//procure semaphores (will always be free here because interrupt off and state just checked)
		Can_tree_imps[controller].TX_pin_s->procure();
		Can_tree_imps[controller].RX_pin_s->procure();
		
		int_restore();
		return Can(&Can_tree_imps[controller]);
	} 
	else
	{
		int_restore();
		return NULL;
	}
}

bool Can::initialise(CAN_RATE rate)
{
	//Assignment to prevent warnings, it will always be assigned a value if tool chain is configured properly
	uint8_t CONF_CANBT1 = 0x00;
	uint8_t CONF_CANBT2 = 0x00;
	uint8_t CONF_CANBT3 = 0x00;
	
	Can_reset();
	
	//clear all buffers
	for (uint8_t i=BUF_0; i<NB_BUF; i++)
	{
		Can_controller->buffer[i].set_mode(CAN_OBJ_DISABLE);
		Can_controller->buffer[i].clear_status();	
	}
	
	//Set CANBT registers to obtain correct baud rate given clock speed
	//Warning: anything below 500K has not been fully tested
	if (CLK_MHZ == 16)             //!< Fclkio = 16 MHz, Tclkio = 62.5 ns
	{
		if (rate == CAN_100K)       //!< -- 100Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x12;       // Tscl  = 10x Tclkio = 625 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)  //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0E;       // Tscl  = 8x Tclkio = 500 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_200K)  //!< -- 200Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 312.5 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_250K)       //!< -- 250Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x0E;       // Tscl  = 4x Tclkio = 250 ns
			CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)       //!< -- 500Kb/s, 8x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x02;       // Tscl = 4x Tclkio = 125 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K)      //!< -- 1 Mb/s, 8x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x00;       // Tscl  = 2x Tclkio = 0.0625 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x36;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	}
	else if (CLK_MHZ == 12)           //!< Fclkio = 12 MHz, Tclkio = 83.333 ns
	{
	    if (rate == CAN_100K)      //!< -- 100Kb/s, 20x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0A;       // Tscl  = 6x Tclkio = 500 ns
			CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)      //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0A;       // Tscl  = 6x Tclkio = 500 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_200K)       //!< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x04;       // Tscl  = 3x Tclkio = 250 ns
			CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
		else if (rate == CAN_250K)      //!< -- 250Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x0A;       // Tscl  = 3x Tclkio = 250 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)       //!< -- 500Kb/s, 12x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 166.666 ns
			CONF_CANBT2 = 0x08;       // Tsync = 1x Tscl, Tprs = 5x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x25;       // Tpsh1 = 3x Tscl, Tpsh2 = 3x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K)      //!< -- 1 Mb/s, 12x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 83.333 ns
	        CONF_CANBT2 = 0x08;       // Tsync = 1x Tscl, Tprs = 5x Tscl, Tsjw = 1x Tscl
            CONF_CANBT3 = 0x25;       // Tpsh1 = 3x Tscl, Tpsh2 = 3x Tscl, 3 sample points
		}
	}
	else if (CLK_MHZ == 8)              //!< Fclkio = 8 MHz, Tclkio = 125 ns
	{
	    if (rate == CAN_100K)       //!< -- 100Kb/s, 16x Tscl, sampling at 75%
	    {
			//only works for ATMega64M1
	        CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 625 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)       //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			//only works for ATMega64M1
	        CONF_CANBT1 = 0x0E;       // Tscl  = 4x Tclkio = 500 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points

		}
	    else if (rate == CAN_200K)       //!< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
			//isn't supported by PCAN
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_250K)       //!< -- 250Kb/s, 16x Tscl, sampling at 75%
	    {
			//only works for ATMega64M1
	        CONF_CANBT1 = 0x06;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)       //!< -- 500Kb/s, 8x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x00;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x36;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K)      //!< -- 1 Mb/s, 8x Tscl, sampling at 75%
	    {
			//sparringly works for both chips, have to be careful about bus length and capacitance etc
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 125 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	}
	Can_conf_bt();	//assign registers the above values of CONF_CANBT to set baudrate
	
	Can_controller->enable();	//write to CANGCON register to enable the controller
	
	//poll CAN controller initialization status
	uint16_t poll_t = ENABLE_TOUT_MS;
	while (!(CANGSTA & (1<<ENFG)) && poll_t)
	{
		poll_t -= 1;			
	}
	
	if (poll_t > 0)
	{
		return true;	//CAN controller successfully initialized
	}
	else
	{
		return false;	//CAN controller failed to initialize
	}
	
}

void Can::set_buffer_mode(CAN_BUF buffer_name, CAN_BUF_MODE mode)
{
	Can_controller->buffer[buffer_name].set_mode(mode);
}

Can_message Can::read(CAN_BUF buffer_name)
{
	Can_clear_rplv();
	Can_message msg = Can_controller->buffer[buffer_name].read();
	return msg;
}

bool Can::transmit(CAN_BUF buffer_name, Can_message msg)
{
	if (Can_controller->buffer[buffer_name].get_status() == BUF_DISABLE)	//disabled means free
	{
		Can_controller->buffer[buffer_name].clear_status();
		
		Can_controller->filter[buffer_name].set_filter_val(msg.id, false);	//setting the ID of the corresponding MOb filter in transmission is equivalent to setting its identifier
		Can_controller->mask[buffer_name].set_mask_val(0x00, false);		//make all masks 0 because trasmission does not use it
				
		Can_controller->buffer[buffer_name].write(msg);
		Can_clear_rplv(); 	//set reply off
		Can_controller->buffer[buffer_name].set_mode(CAN_OBJ_TX);			//enable tx mode to start sending message
		
		return true;
	}
	else
	{
		return false;		//wasn't free
	}
}

CAN_BUF_STAT Can::get_buffer_status(CAN_BUF buffer_name)
{
	return Can_controller->buffer[buffer_name].get_status();
}

void Can::clear_buffer_status(CAN_BUF buffer_name)
{
	Can_controller->buffer[buffer_name].clear_status();
}

void Can::set_filter_val(CAN_FIL filter_name, uint32_t filter_val, bool RTR)
{
	Can_controller->filter[filter_name].set_filter_val(filter_val, RTR);
}

uint32_t Can::get_filter_val(CAN_FIL filter_name)
{
	return Can_controller->filter[filter_name].get_filter_val();
}

void Can::set_mask_val(CAN_MSK mask_name, uint32_t mask_val, bool RTR)
{
	Can_controller->mask[mask_name].set_mask_val(mask_val, RTR);
}

uint32_t Can::get_mask_val(CAN_MSK mask_name)
{
	return Can_controller->mask[mask_name].get_mask_val();
}

void Can::enable_interrupts(void)
{
	Can_controller->enable_interrupts();
}

void Can::disable_interrupts(void)
{
	Can_controller->disable_interrupts();
}

void Can::enable_buffer_interrupt(CAN_BUF buffer_name)
{
	Can_controller->buffer[buffer_name].enable_interrupt();
}

void Can::disable_buffer_interrupt(CAN_BUF buffer_name)
{
	Can_controller->buffer[buffer_name].disable_interrupt();
}

void Can::attach_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt, void (*userFunc)(void))
{
	Can_controller->buffer[buffer_name].attach_interrupt(interrupt, userFunc);
}

void Can::attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void))
{
	Can_controller->attach_interrupt(interrupt, userFunc);
}

void Can::detach_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt)
{
	Can_controller->buffer[buffer_name].detach_interrupt(interrupt);
}

void Can::detach_interrupt(CAN_INT_NAME interrupt)
{
	Can_controller->detach_interrupt(interrupt);
}

bool Can::test_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt)
{
	return Can_controller->buffer[buffer_name].test_interrupt(interrupt);
}

bool Can::test_interrupt(CAN_INT_NAME interrupt)
{
	return Can_controller->test_interrupt(interrupt);
}

CAN_BUF Can::get_interrrupted_buffer(void)
{
	return interrupt_service_buffer;
}

bool Can::clear_controller_interrupts(CAN_INT_NAME interrupt)
{
	//writing logical one resets the flag
	switch (interrupt)
	{
		case (CAN_BUS_OFF):
			CANGIT |= (1<<BOFFIT);
		case (CAN_TIME_OVERRUN):
			CANGIT |= (1<<OVRTIM);
		default:
			break;
	}
	
	return true;
}


//CAN Interrupt declarations
 //Note: These address registers at the low level rather than call 
 //API functions to reduce function call overhead
 //
 //Note: User must reset interrupt flags themselves
 
SIGNAL(GEN_CAN_IT_VECT)	//CAN Trasfer complete interrupt
{	
	volatile uint8_t canpage_save = CANHPMOB & 0xF0;		
	CANPAGE = canpage_save;					//Select highest priority MOb
	interrupt_service_buffer = static_cast<CAN_BUF>(CANPAGE >> 4);

	if (CANSTMOB & MOB_RX_COMPLETED)
	{
		intFunc[(CANPAGE>>4)][CAN_RX_COMPLETE]();
		return;
	}
	else if (CANSTMOB & MOB_TX_COMPLETED)
	{
		intFunc[(CANPAGE>>4)][CAN_TX_COMPLETE]();
		return;
	}
	else if (CANSTMOB & ERR_MOB_MSK)
	{
		intFunc[(CANPAGE>>4)][CAN_GEN_ERROR]();
		return;
	}
			
}
 
SIGNAL(OVR_TIM_IT_VECT)	//CAN Timer overrun error interrupt
{
	volatile uint8_t canpage_save = CANHPMOB & 0xF0;
	CANPAGE = canpage_save;
	intFunc[(CANPAGE>>4)][CAN_TIME_OVERRUN]();
}
 */
 
