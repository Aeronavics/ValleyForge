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
 *  DATE CREATED:	14-11-2012
 *
 *	Functionality to provide implementation for CAN in AVR
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.
#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

/**********************************************************************/
// Allows object enums to be iterated, inelegantly, this must be defined for every implementation because it shouldn't be in in h file
CAN_BUF operator++(CAN_BUF& f, int)
{
	int temp = f;
	return f = static_cast<CAN_BUF> (++temp);
}

CAN_FIL operator++(CAN_FIL& f, int)
{
	int temp = f;
	return f = static_cast<CAN_FIL> (++temp);
}


/**********************************************************************/
/**
 * Can buffer class
 */
void Can_buffer::set_number(CAN_BUF buf_num)
{
	buf_no = buf_num;
}

CAN_BUF_MODE Can_buffer::get_mode(void)
{
	return mode;	
}

bool Can_buffer::get_multimode(void)
{
	return true;	//true for AVR implementation
}

void Can_buffer::set_mode(CAN_BUF_MODE mode)
{
	Can_set_mob(buf_no);	//set CANPAGE to MOb of interest
	
	if (mode == CAN_OBJ_RX)
	{
		Can_config_rx();
		mode = CAN_OBJ_RX;
	}
	else if (mode == CAN_OBJ_TX)
	{
		Can_config_tx();
		mode = CAN_OBJ_TX;	
	}
	else if (mode == CAN_OBJ_RXB)
	{
		Can_config_rx_buffer();
	}
	else if (mode == CAN_OBJ_DISABLE)
	{
		DISABLE_MOB;
	}
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
	Can_set_dlc(msg.dlc);
	for (uint8_t i=0; i<msg.dlc; i++)
	{
		CANMSG = msg.data[i];	//writing data to buffer, note CANMSG is auto-incremented
	}
}

void Can_buffer::clear(void)
{
	Can_set_mob(buf_no);
	Can_clear_mob();
}

void Can_buffer::clear_status(void)
{
	Can_set_mob(buf_no);
	Can_clear_status_mob();
}

CAN_BUF_STAT Can_buffer::get_status(void)
{	
	//by using CANEN registers, CANPAGE doesn't have to be written
	if (buf_no < 8)
	{
		if ((CANEN2 & (1<<buf_no)) == 0x00)
		{
			return BUF_DISABLE;
		}	
	}
	else
	{
		if ((CANEN1 & (1<<(buf_no-8))) == 0x00)
		{
			return BUF_DISABLE;
		}
	}
	
	//these operations however need to poll the correct buffer using CANPAGE	
	Can_set_mob(buf_no);
	uint8_t canstmob_copy = CANSTMOB; // Copy for test integrity
	    
	// If MOb is ENABLE, test if MOb is COMPLETED
    // - MOb Status = 0x20 then MOB_RX_COMPLETED
    // - MOb Status = 0x40 then MOB_TX_COMPLETED
    // - MOb Status = 0xA0 then MOB_RX_COMPLETED_DLCW
    uint8_t mob_status = canstmob_copy & ((1<<DLCW)|(1<<TXOK)|(1<<RXOK));
    
	if (mob_status == MOB_RX_COMPLETED)
	{ 
		return BUF_RX_COMPLETED;
	}
	else if (mob_status == MOB_TX_COMPLETED)
	{
		Can_mob_abort();
		Can_clear_status_mob();
		return BUF_TX_COMPLETED;
	}
	else if (mob_status == MOB_RX_COMPLETED_DLCW)
	{
		// deal with standard and extended frame stuff to be implemented
		
		Can_mob_abort();        // Freed the MOB
        Can_clear_status_mob();
		return BUF_RX_COMPLETED_DLCW;
	}
	
	// If MOb is ENABLE & NOT_COMPLETED, test if MOb is in ERROR
    // - MOb Status bit_0 = MOB_ACK_ERROR
    // - MOb Status bit_1 = MOB_FORM_ERROR
    // - MOb Status bit_2 = MOB_CRC_ERROR
    // - MOb Status bit_3 = MOB_STUFF_ERROR
    // - MOb Status bit_4 = MOB_BIT_ERROR
	mob_status = canstmob_copy & ERR_MOB_MSK;
	if (mob_status == MOB_ACK_ERROR)
	{
		return BUF_ACK_ERROR;
	}
	else if (mob_status == MOB_FORM_ERROR)
	{
		return BUF_FORM_ERROR;
	}
	else if (mob_status == MOB_CRC_ERROR)
	{
		return BUF_CRC_ERROR;
	}
	else if (mob_status == MOB_STUFF_ERROR)
	{
		return BUF_STUFF_ERROR;
	}
	else if (mob_status == MOB_BIT_ERROR)
	{
		return BUF_BIT_ERROR;
	}
	
	// If CANSTMOB = 0 then MOB_NOT_COMPLETED
	return BUF_NOT_COMPLETE;
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

void Can_buffer::attach_interrupt(CAN_INT_NAME interrupt, Interrupt_fn handler)
{
	Can_set_mob(buf_no);
	
	if (interrupt == CAN_RX_COMPLETE)
	{
		CANGIE |= (1 << 5);	
	}
	else if (interrupt == CAN_TX_COMPLETE)
	{
		CANGIE |= (1 << 4);
	}
	else if (interrupt == CAN_RX_ERROR)
	{
		CANGIE |= (1 << 1);
	}
	//TODO: Make the interrupt handler work
}

/**********************************************************************/
/**
 * Can filter class
 */

void Can_filter::set_number(CAN_FIL fil_num)
{
	fil_no = fil_num;
}

bool Can_filter::set_buffer(Can_buffer* buffer)
{
	buffer_link = buffer;
	return true;	//Always true for AVRs since their link is fixed, also it cannot be called in runtime
}

bool Can_filter::get_routable(void)
{
	return false;	//Always false for AVRs since their link is fixed
}

uint32_t Can_filter::get_mask_val(void)
{
	return filter_data.mask;
}

uint32_t Can_filter::get_filter_val(void)
{
	return filter_data.id;
}

void Can_filter::set_mask_val(uint32_t mask)
{
	Can_set_mob(fil_no);
	Can_set_ext_msk(mask);
	filter_data.mask = mask;	//store as field so registers don't need to be accessed again
}

void Can_filter::set_filter_val(uint32_t filter)
{
	Can_set_mob(fil_no);
	Can_set_ext_id(filter);
	filter_data.id = filter;	//store as field so registers don't need to be accessed again
}

/**********************************************************************/
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
class Can_tree
{
	public:
	//Methods
		/**
		 * Constructor for AVR specific implementation:
		 * Buffers and filters are created and assigned arbitrary indices,
		 * each filter is then linked to its respective buffer by this index.
		 */
		Can_tree(void);
		
		/**
		 * Enables the controller
		 */
		void enable(void);
		
	
	//Fields
		Can_filter filter[NB_FIL];
		Can_buffer buffer[NB_BUF];
};

Can_tree::Can_tree(void)
{
	for (CAN_BUF i=OBJ_0; i<NB_BUF; i++)
	{
		buffer[i] = Can_buffer();	//assign arbitrary index to buffer, CANPAGE access uses this number
		buffer[i].set_number(i);
	}
	
	for (CAN_FIL i=FILTER_0; i<NB_FIL; i++)
	{
		filter[i] = Can_filter();  //assign arbitrary index to filter
		filter[i].set_number(i);
		filter[i].set_buffer(&buffer[i]);	//link filter to corresponding buffer using index
	}
	return;
}

void Can_tree::enable(void)
{
	Can_enable();
}

static Can_tree Can_tree_imps[NB_CTRL];


/**********************************************************************/

/**
 * Interface class for CAN controller, users create an instance of this 
 * and links it to the pre-instantiated instance reflecting the single
 * hardware CAN controller
 * 
 * Example usage transmitting 'Hello world' over CAN:
 * init_hal();						//hal library mainly covers semaphores which are not used for CAN but still think its better to call this
 * int_on();						//turn interrupts on (not sure if this applies to CAN interrupts
 * 
 * Can my_can = Can::link(CAN_0);	//link to hardware implementation
 * my_can.initialize(CAN_100K);		//set the baud rate to 100K
 * 
 * Can_message my_msg;
 * my_msg.id = 0x00;
 * my_msg.dlc = 12;
 * my_msg.data = "Hello World!";
 * my_can.transmit(my_msg);
 */
 
Can::Can(Can_tree* imp)
{
	Can_controller = imp;	
	return;
}

//Method implementations
Can Can::link(CAN_CTRL controller)
{
	return Can(&Can_tree_imps[controller]);
}

void Can::initialise(CAN_RATE rate)
{
	//Assignment to prevent warnings, it will always be assigned a value if tool chain is configured properly
	uint8_t CONF_CANBT1 = 0x00;
	uint8_t CONF_CANBT2 = 0x00;
	uint8_t CONF_CANBT3 = 0x00; 
	
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
	        CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 625 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)       //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x0E;       // Tscl  = 4x Tclkio = 500 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_200K)       //!< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_250K)       //!< -- 250Kb/s, 16x Tscl, sampling at 75%
	    {
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
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 125 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x12;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	}
	
	Can_reset();
	Can_conf_bt();	//assign registers the above values of CONF_CANBT to set baudrate
	CANPAGE &= ~(1<<AINC);	//set CANMSG to auto-increment
	
	//clear all buffers
	for (CAN_BUF i=OBJ_0; i<NB_BUF; i++)
	{
		Can_controller->buffer[i].clear();
		Can_controller->buffer[i].clear_status();
		Can_set_ide();	//this library always communicates with the an extended identifier
	}
	Can_controller->enable();	//write to CANGCON register to enable the controller
}

void Can::set_buffer_mode(CAN_BUF buffer_name, CAN_BUF_MODE mode)
{
	Can_controller->buffer[buffer_name].set_mode(mode);
}

Can_message Can::read(CAN_BUF buffer_name)
{
	Can_message msg = Can_controller->buffer[buffer_name].read();
	return msg;
}

bool Can::transmit(CAN_BUF buffer_name, Can_message msg)
{
	if (Can_controller->buffer[buffer_name].get_status() == BUF_DISABLE)	//disabled means free
	{
		Can_controller->buffer[buffer_name].clear();
		Can_controller->buffer[buffer_name].clear_status();
		//setting the ID of the corresponding MOb filter in transmission is equivalent to setting its identifier
		Can_controller->filter[buffer_name].set_filter_val(msg.id);
		Can_controller->filter[buffer_name].set_mask_val(0x00000000);	//make all masks 0 because trasmission does not use it
				
		Can_controller->buffer[buffer_name].write(msg);
		Can_controller->buffer[buffer_name].set_mode(CAN_OBJ_TX);	//enable tx mode to start sending message
		return true;
	}
	else
	{
		return false;	//wasn't free
	}
}

CAN_BUF_STAT Can::get_buffer_status(CAN_BUF buffer_name)
{
	return Can_controller->buffer[buffer_name].get_status();
}

void Can::clear_buffer(CAN_BUF buffer_name)
{
	Can_controller->buffer[buffer_name].clear();
}
