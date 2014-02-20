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
 *  DATE CREATED:	13-12-2013
 *
 *	Functionality to provide implementation for CAN with SocketCAN
 ********************************************************************************************************************************/
 
// INCLUDE THE MATCHING HEADER FILE.
#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include "can_platform.hpp"

#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h> 
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <string.h>

// DEFINE PRIVATE MACROS.


// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

int s;	// unfortunately, the use of a tree data structure meant that the children can't readily access parent fields, thus the socket is global


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
		
		Can_filmask* filmasks[8];		// up to 4 filter/mask pairs, filter and masks are adjacent
		
		Can_buffer* buffer_link;
		
		struct can_filter rfilters[4];	// SocketCAN filter type
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
		 * @param   msg		Can_message struct to store the incoming message.
		 * @return  Return code indicating whether operation was successful.
		 */
		Can_send_status read(Can_message& msg);
		
		/**
		 * Spin until buffer has a message before reading
		 * 
		 * @param	msg		Can_message struct to store the incoming message.
		 * @return	Return code indicating whether operation was successful.
		 */
		Can_send_status blocking_read(Can_message& msg);
		 
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
		 * Frees the first received message on the buffer
		 * 
		 * @param	Nothing.
		 * @return	Return code indicating whether operation was successful
		 */
		Can_config_status free_message(void);
		
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
		
		/**
		 * Close the socket for SocketCAN
		 */
		void close(void);
    
	private:

		// Methods.
		
		Can_imp(void);	// Poisoned.

		Can_imp(Can_imp*);	// Poisoned.

		Can_imp operator =(Can_imp const&);	// Poisoned.

		// Fields.
		
			// *** TARGET CONFIGURATION SPECIFIC.

			// Objects for the CAN tree.
			
			// NOTE - Only managed to get one buffer working on SocketCAN
			
			Can_buffer* buffers[CAN_NUM_BUFFERS];
			Can_filter_bank* banks[CAN_NUM_BANKS];
			Can_filmask* filters[CAN_NUM_FILTERS];
			Can_filmask* masks[CAN_NUM_MASKS];
			
			Can_buffer_imp buf_0i;
			Can_buffer buf_0;

			Can_filter_bank_imp bnk_0i;
			Can_filter_bank bnk_0;

			Can_filmask_imp fil_0i;
			Can_filmask_imp fil_1i;
			Can_filmask_imp fil_2i;
			Can_filmask_imp fil_3i;
			
			Can_filmask fil_0;
			Can_filmask fil_1;
			Can_filmask fil_2;
			Can_filmask fil_3;
			
			Can_filmask_imp msk_0i;
			Can_filmask_imp msk_1i;
			Can_filmask_imp msk_2i;
			Can_filmask_imp msk_3i;
			
			Can_filmask msk_0;
			Can_filmask msk_1;
			Can_filmask msk_2;
			Can_filmask msk_3;
			
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

Can_send_status Can_buffer::read(Can_message& message)
{
	return imp->read(message);
}

Can_send_status Can_buffer::blocking_read(Can_message& message)
{
	return imp->blocking_read(message);
}

Can_send_status Can_buffer::write(Can_message msg)
{
	return imp->write(msg);
}

Can_config_status Can_buffer::free_message(void)
{
	return imp->free_message();
}

uint8_t Can_buffer::queue_length(void)
{
	return imp->queue_length();
}

void Can_buffer::clear_status(void)
{
	imp->clear_status();
}

// Can.

Can::Can(Can_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

Can::~Can(void)
{
	imp->close();
}

Can Can::bind(Can_id_controller controller)
{
	// *** TARGET CONFIGURATION SPECIFIC.
	
	// There already exists a static instance of the implementation class for each of the CAN peripherals.
	static Can_imp can_imp_0 = Can_imp(CAN_0);
	
	// NOTE - There is only one CAN peripheral, so we don't really have any logic here.
	
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


// IMPLEMENT PRIVATE CLASS METHODS

// Can_filmask_imp

Can_filmask_imp::Can_filmask_imp(Can_id_filter filter)
{
	// constructor creates a filter 
	filmask_mode = CAN_FM_FIL;
	filmask_no = static_cast<Can_id_filmask>(filter);
}

Can_filmask_imp::Can_filmask_imp(Can_id_mask mask)
{
	// constructor creates a mask
	filmask_mode = CAN_FM_MSK;
	filmask_no = static_cast<Can_id_filmask>(mask);
}

Can_filmask_value Can_filmask_imp::get(void)
{
	return filmask_val;
}

void Can_filmask_imp::set(Can_filmask_value value)
{
	// must use set_buffer() operation to apply this value onto socket	
	filmask_val = value;	
}


// Can_filter_bank_imp

Can_filter_bank_imp::Can_filter_bank_imp(Can_id_bank bank)
{
	bnk_no = bank;
}

Can_config_status Can_filter_bank_imp::set_buffer(Can_buffer& buffer)
{
	buffer_link = &buffer;
	
	/* *** write to SocketCAN filter object *** */
	for (int i=0; i<bnk_mode-1; i++)
	{	
		/* filter */
		uint8_t fil_index = 2*i;		// even number
		
		if (filmasks[fil_index]->get().ext)
		{
			rfilters[i].can_id = filmasks[fil_index]->get().id & CAN_EFF_MASK;
			// assume EFF bit has been cleared since an assignment to a masked value was used
			rfilters[i].can_id |= (CAN_EFF_FLAG);	// set extended id
		}
		else
		{
			rfilters[i].can_id = filmasks[fil_index]->get().id & CAN_SFF_MASK;
			// assume EFF bit has been cleared since an assignment to a masked value was used
		}
		
		if (filmasks[fil_index]->get().rtr)
		{
			// assume RTR bit has been cleared since an assignment to a mask value was used
			rfilters[i].can_id |= CAN_RTR_FLAG;
		}
		
		/* mask */
		uint8_t msk_index = 2*i+1;		// odd number
		if (filmasks[msk_index]->get().ext)
		{
			rfilters[i].can_mask = filmasks[msk_index]->get().id & CAN_EFF_MASK;
		}
		else
		{
			rfilters[i].can_mask = filmasks[msk_index]->get().id & CAN_SFF_MASK;
		}
		
		if (filmasks[msk_index]->get().rtr)
		{
			rfilters[i].can_mask |= CAN_RTR_FLAG;
		}
		
	}
	
	for (int i=bnk_mode; i<CAN_NUM_FILTERS; i++)
	{
		/* since mallocing is avoided, 4 filter/mask pairs have been allocated
		 * but only use as many as bnk_mode field suggests (0-4 pairs),
		 * writing the rest of the pair's mask values to 0 makes that filter
		 * inactive */
		rfilters[i].can_id = 0;
		rfilters[i].can_mask = 0;
	}
	
	/* Apply the filter settings to socket:
	 * Some inelegant abstraction here, setting the buffer of this bank 
	 * is what applies the filters to the socket. Writing to the 
	 * filmasks only stores the chosen value to be written by this operation 
	 * later. If you want to change the value, make this operation again */
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilters, sizeof(rfilters));
	
	return CAN_CFG_SUCCESS;
}

uint8_t Can_filter_bank_imp::get_num_filmasks(void)
{
	return 2*(bnk_mode+1);
}

Can_filmask** Can_filter_bank_imp::get_filmasks(void)
{
	return filmasks;
}

Can_buffer* Can_filter_bank_imp::get_buffer(void)
{
	return buffer_link;
}

Can_bank_mode Can_filter_bank_imp::get_mode(void)
{
	return bnk_mode;
}

Can_config_status Can_filter_bank_imp::set_mode(Can_bank_mode mode)
{
	// this determines the number of rfilters elements to setsockopt with
	bnk_mode = mode;
	return CAN_CFG_SUCCESS;
}


// Can_buffer_imp

Can_buffer_imp::Can_buffer_imp(Can_id_buffer buffer)
{
	buf_no = buffer;
}

Can_send_status Can_buffer_imp::read(Can_message& msg)
{
	fcntl(s, F_SETFL, O_NONBLOCK); 		// put into non blocking mode
	
	Can_send_status ret_code = blocking_read(msg);
	
	fcntl(s, F_SETFL, O_SYNC); 			// put into blocking mode (actually O_SYNC is guess)
	
	return CAN_SND_SUCCESS;
}

Can_send_status Can_buffer_imp::blocking_read(Can_message& msg)
{
	struct can_frame frame;
	
	/* read from CAN interface */
	int nbytes = ::read(s, &frame, sizeof(struct can_frame));
	
	/* error checking */
	if (nbytes < 0)
	{
		return CAN_SND_MODERR;
	} 
	
	/* wrap ValleyForge frame over SocketCAN frame */
	msg.dlc = frame.can_dlc;
	
	if (msg.id & CAN_RTR_FLAG)		// if bit 30 == 1, then RTR
	{
		msg.rtr = 1;
	}
	
	if (msg.id & CAN_EFF_FLAG)		// if MSB == 1, then extended
	{
		msg.ext = 1;
		msg.id = frame.can_id | CAN_EFF_MASK;
	}
	else
	{
		msg.id = frame.can_id | CAN_SFF_MASK;
	}
	
	for (int i=0; i<msg.dlc; i++)
	{
		msg.data[i] = frame.data[i];
	}
	
	set_mode(CAN_OBJ_RX);
	
	return CAN_SND_SUCCESS;
}

Can_send_status Can_buffer_imp::write(Can_message msg)
{
	if (msg.dlc > 8)
	{
		return CAN_SND_DLCERR;
	}
	
	/* wrap SocketCAN frame over ValleyForge frame */
	struct can_frame frame;
	
	frame.can_id = msg.id;				// copy ValleyForge frame id to SocketCAN frame
	
	if (msg.ext == 1)
	{
		frame.can_id |= CAN_EFF_FLAG;	// make MSB = 1 for extended
	}
	
	if (msg.rtr == 1)
	{
		frame.can_id |= CAN_RTR_FLAG;	// make bit 30 = 1 for RTR	
	}
	
	frame.can_dlc = msg.dlc;
	
	for (int i=0; i<msg.dlc; i++)
	{
		frame.data[i] = msg.data[i];
	}
	
	/* write to CAN interface */
	int nbytes = ::write(s, &frame, sizeof(frame));
	
	/* error checking */
	if (nbytes < 0)
	{
		return CAN_SND_MODERR;
	}
	
	set_mode(CAN_OBJ_TX);
	
	return CAN_SND_SUCCESS;
}

Can_buffer_mode Can_buffer_imp::get_mode(void)
{
	/* more leaky abstraction: the buffer can always receive or transmit, 
	 * this method simply returns the mode of the last transfer.
	 */
	return buf_mode;
}

bool Can_buffer_imp::get_multimode(void)
{
	return true;
}

Can_config_status Can_buffer_imp::set_mode(Can_buffer_mode mode)
{
	buf_mode = mode;	// just caches the mode, doesn't have any hardware significance
	
	return CAN_CFG_SUCCESS;
}

Can_buffer_status Can_buffer_imp::get_status(void)
{
	/* for SocketCAN, this is useful for getting errors only, there is no
	 * need to manually reset buffer status after transmission or reception */
	 
	 // NB: Haven't figured out how to properly implement this
	 return BUF_NOT_COMPLETED;
}

Can_config_status Can_buffer_imp::free_message(void)
{
	return CAN_CFG_IMMUTABLE;
}

uint8_t Can_buffer_imp::queue_length(void)
{
	// queuing is managed by the OS, it doesn't really matter from user POV
	
	return 0;
}

void Can_buffer_imp::clear_status(void)
{
	// irrelevant for this target, do nothing
}


// Can_imp

Can_imp::Can_imp(Can_id_controller controller):

	buf_0i(CAN_BUF_0),
	buf_0((Can_buffer_imp*) NULL),
	
	bnk_0i(CAN_BNK_0),
	bnk_0((Can_filter_bank_imp*) NULL),
	
	fil_0i(CAN_FIL_0),
	fil_1i(CAN_FIL_1),
	fil_2i(CAN_FIL_2),
	fil_3i(CAN_FIL_3),
	
	fil_0((Can_filmask_imp*) NULL),
	fil_1((Can_filmask_imp*) NULL),
	fil_2((Can_filmask_imp*) NULL),
	fil_3((Can_filmask_imp*) NULL),
	
	msk_0i(CAN_MSK_0),
	msk_1i(CAN_MSK_1),
	msk_2i(CAN_MSK_2),
	msk_3i(CAN_MSK_3),
	
	msk_0((Can_filmask_imp*) NULL),
	msk_1((Can_filmask_imp*) NULL),
	msk_2((Can_filmask_imp*) NULL),
	msk_3((Can_filmask_imp*) NULL)
	
{
	/* ***** Linking to implemenation and adding to arrays ***** */
	buf_0.imp = &buf_0i;
	buffers[0] = &buf_0;
	
	bnk_0.imp = &bnk_0i;
	banks[0] = &bnk_0;
	
	fil_0.imp = &fil_0i;
	fil_1.imp = &fil_1i;
	fil_2.imp = &fil_2i;
	fil_3.imp = &fil_3i;
	
	filters[0] = &fil_0;
	filters[1] = &fil_1;
	filters[2] = &fil_2;
	filters[3] = &fil_3;
	
	msk_0.imp = &msk_0i;
	msk_1.imp = &msk_1i;
	msk_2.imp = &msk_2i;
	msk_3.imp = &msk_3i;
	
	masks[0] = &msk_0;
	masks[1] = &msk_1;
	masks[2] = &msk_2;
	masks[3] = &msk_3;
	
	/* ***** Assembling tree ***** */
	banks[0]->imp->buffer_link = buffers[0];		// only one buffer and one bank
	
	for (uint8_t i=0; i<CAN_NUM_FILTERS; i++)
	{
		banks[0]->imp->filmasks[2*i] = filters[i];	// even index is filter
		banks[0]->imp->filmasks[2*i+1] = masks[i];	// odd index is mask
	}
	
	/* ***** Creating the socket ***** */	
	struct ifreq ifr; 
	struct sockaddr_can addr; 
	struct can_frame frame; 

	memset(&ifr, 0x0, sizeof(ifr)); 
	memset(&addr, 0x0, sizeof(addr)); 
	memset(&frame, 0x0, sizeof(frame)); 

	/* open CAN_RAW socket */ 
	s = socket(PF_CAN, SOCK_RAW, CAN_RAW); 

	/* create the interface name and convert to interface index */
	char* interface_name; 
	if (controller == CAN_0)
	{
		interface_name = "can0";
		strcpy(ifr.ifr_name, interface_name);
	}
	ioctl(s, SIOCGIFINDEX, &ifr); 

	/* setup address for bind */ 
	addr.can_ifindex = ifr.ifr_ifindex; 
	addr.can_family = PF_CAN; 

	/* bind socket to the can0 interface */ 
	::bind(s, (struct sockaddr *)&addr, sizeof(addr));
	printf("Successfully binded socket to [%s] interface\n", interface_name);
}

Can_config_status Can_imp::initialise(Can_rate rate)
{	
	switch (rate)
	{
		case (CAN_1000K): 
			system("sudo echo \"i 0x0014 e\" >/dev/pcan32");
			break;
		case (CAN_500K):
			system("sudo echo \"i 0x001C e\" >/dev/pcan32");
			break;
		case (CAN_250K):
			system("sudo echo \"i 0x011C e\" >/dev/pcan32");
			break;
		case (CAN_100K):
			system("sudo echo \"i 0x432F e\" >/dev/pcan32");
			break;
		default:
			fprintf(stderr, "initialise: baud rate not supported by HAL, defaulting to 500K\n");	
			system("sudo echo \"i 0x001C e\" >/dev/pcan32");
	}
	
	return CAN_CFG_SUCCESS;
}

uint8_t Can_imp::get_num_banks(void)
{
	return CAN_NUM_BANKS;
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
 
void Can_imp::close(void)
{
	::close(s);
}
