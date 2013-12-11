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
#include <util/delay.h>

#define F_CPU (<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>000000)	//Used for delaying
#define ENABLE_TOUT_MS  500;									//Controller enable timeout

//different interrupt vector names for different micros
#if defined(__AVR_AT90CAN128__)
	#define GEN_CAN_IT_VECT CANIT_vect
	#define OVR_TIM_IT_VECT OVRIT_vect
#elif defined (__AVR_ATmega64M1__)
	#define GEN_CAN_IT_VECT CAN_INT_vect
	#define OVR_TIM_IT_VECT CAN_TOVF_vect
#endif

/**********************************************************************/
volatile static voidFuncPtr intFunc[NB_BUF][NB_INT];
volatile CAN_BUF interrupt_service_buffer;

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

void Can_filter::set_mask_val(uint32_t mask, bool RTR)
{
	Can_set_mob(fil_no);
	Can_set_ext_msk(mask);
	
	if (RTR)
	{
		Can_set_rtrmsk();
	}
	else
	{
		Can_clear_rtrmsk();
	}
	filter_data.mask = mask;	//store as field so registers don't need to be accessed again
}

void Can_filter::set_filter_val(uint32_t filter, bool RTR)
{
	Can_set_mob(fil_no);
	Can_set_ext_id(filter);
	
	if (RTR)
	{
		Can_set_rtr();
	}
	else
	{
		Can_clear_rtr();
	}
	
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
		
		/**
		 * Enable interrupts on the controller
		 */
		void enable_interrupts(void);
		
		/**
		 * Disables interrupts on the controller
		 */
		void disable_interrupts(void);
		
		/**
		 * Attach CAN channel interrupts, will overwrite existing interrupt
		 * 
		 * @param    interrupt   The interrupt condition to attach the handler to
		 * @param    userFunc     The handler for this interrupt condition.
		 * 
		 */
		void attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void));
		
		/**
		 * Detach interrupt to CAN channel
		 * 
		 * @param    interrupt   The interrupt condition to detach the handler from
		 */
		void detach_interrupt(CAN_INT_NAME interrupt);
		
		/**
		 * Returns true if interrupt condition has handelr attached
		 * 
		 * @param    interrupt   The bus interrupt condition to test if enabled 
		 * @return   Boolean describing whether an interrupt handler is set for this condition
		 * 
		 */ 			 
		bool test_interrupt(CAN_INT_NAME interrupt);
		
	
	//Fields
		Can_filter filter[NB_FIL];
		Can_buffer buffer[NB_BUF];
};

Can_tree::Can_tree(void)
{
	for (CAN_BUF i=OBJ_0; i<NB_BUF; i++)
	{
		buffer[i] = Can_buffer();	
		buffer[i].set_number(i);	//assign arbitrary index to buffer, CANPAGE access uses this number
	}
	
	for (CAN_FIL i=FILTER_0; i<NB_FIL; i++)
	{
		filter[i] = Can_filter();  
		filter[i].set_number(i);	//assign arbitrary index to filter
		filter[i].set_buffer(&buffer[i]);	//link filter to corresponding buffer using index
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
		for (CAN_BUF i=OBJ_0; i<NB_BUF; i++)
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
 * Can my_can = Can::link(CAN_0);	//link to hardware implementation
 * my_can.initialize(CAN_500K);		//set the baud rate to 500K
 * 
 * Can_message my_msg;
 * my_msg.id = 0x00;
 * my_msg.dlc = 8;
 * my_msg.data = "01234567";	//note: this represents a message, its not a string literal
 * my_can.transmit(OBJ_0, my_msg);	//transmit message using buffer 0
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

bool Can::initialise(CAN_RATE rate)
{
	//Assignment to prevent warnings, it will always be assigned a value if tool chain is configured properly
	uint8_t CONF_CANBT1 = 0x00;
	uint8_t CONF_CANBT2 = 0x00;
	uint8_t CONF_CANBT3 = 0x00;
	
	Can_reset();
	
	//clear all buffers
	for (CAN_BUF i=OBJ_0; i<NB_BUF; i++)
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
			//doesn't work for both chips
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
		_delay_ms(1);
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
		
		Can_controller->filter[buffer_name].set_filter_val(msg.id, false);		//setting the ID of the corresponding MOb filter in transmission is equivalent to setting its identifier
		Can_controller->filter[buffer_name].set_mask_val(0x00, false);	//make all masks 0 because trasmission does not use it
				
		Can_controller->buffer[buffer_name].write(msg);
		Can_clear_rplv(); 	//set reply off
		Can_controller->buffer[buffer_name].set_mode(CAN_OBJ_TX);		//enable tx mode to start sending message
		
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

void Can::set_mask_val(CAN_FIL filter_name, uint32_t mask_val, bool RTR)
{
	Can_controller->filter[filter_name].set_mask_val(mask_val, RTR);
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

bool clear_controller_interrupts(CAN_INT_NAME interrupt)
{
	//writing logical one resets the flag
	switch (interrupt)
	{
		case (CAN_BUS_OFF):
			CANGIT |= (1<<BOFFIT);
		case (CAN_TIME_OVERRUN):
			CANGIT |= (1<<OVRTIM);
	}
}

/**********************************************************************/
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
 
 
