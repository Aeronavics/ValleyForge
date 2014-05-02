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
 *  DATE CREATED:	17-11-2012
 *
 *	Functionality to provide implementation for CAN in STM32
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.
#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include "can_platform.hpp"

#include "hal/gpio.hpp"

#define ENABLE_TOUT_MS  1000000;			//Controller enable timeout

// DEFINE PRIVATE MACROS

enum FM_BANK_MODE {BANK_NN, BANK_FF, BANK_FM};	//represents de-activated, filter list or filter-mask mode

// DECLARE PRIVATE GLOBAL VARIABLES

bool can_filter_init_mode = false;

volatile static voidFuncPtr intFunc[NUM_BUF][NB_INT];
volatile CAN_BUF interrupt_service_buffer;

Can_filter filters[MAX_NUM_FIL];
Can_mask masks[MAX_NUM_MSK];

// IMPLEMENT PUBLIC FUNCTIONS

/**
 * Can buffer class
 */
void Can_buffer::set_number(uint8_t buf_num)
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
	return false;	//STM32 buffers are fixed mode
}

bool Can_buffer::set_mode(CAN_BUF_MODE mode)
{
	return false;	//STM32 buffers are fixed mode
}

Can_message Can_buffer::read(void)
{
	Can_message rec_msg;
	if (buf_no == BUF_3 || buf_no == BUF_4)
	{
		rec_msg.id = static_cast<uint32_t>(0x0003FFFF) & (CAN->sFIFOMailBox[buf_no].RIR >> 3);
		rec_msg.dlc = static_cast<uint8_t>(0x0000000F) & CAN->sFIFOMailBox[buf_no].RDTR;
		
		rec_msg.data[0] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDLR);
		rec_msg.data[1] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDLR >> 8);
		rec_msg.data[2] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDLR >> 16);
		rec_msg.data[3] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDLR >> 24);

		rec_msg.data[4] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDHR);
		rec_msg.data[5] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDHR >> 8);
		rec_msg.data[6] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDHR >> 16);
		rec_msg.data[7] = static_cast<uint8_t>(0x000000FF) & (CAN->sFIFOMailBox[buf_no].RDHR >> 24);
	}
	else
	{
		rec_msg.id = 0;
		rec_msg.dlc = 255;			//fail code 
	}
	
	if (buf_no == 3)
	{
		CAN->RF0R |= CAN_RFxR_RFOMx;	//release message
	}
	else if (buf_no == 4)
	{
		CAN->RF1R |= CAN_RFxR_RFOMx;
	}
	
	return rec_msg;	
}

void Can_buffer::write(Can_message msg)
{
	//clear the whole register
	CAN->sTxMailBox[buf_no].TIR = static_cast<uint32_t>(0x00000000);
	
	//set message ID
	CAN->sTxMailBox[buf_no].TIR |= static_cast<uint32_t>(msg.id<<3) | CAN_TIR_EXTID_MASK;	
	
	//clear RTR bit so message is data frame not remote frame
	CAN->sTxMailBox[buf_no].TIR &= ~CAN_TIR_RTR;											
	
	//write message to buffer
	CAN->sTxMailBox[buf_no].TDLR = ((static_cast<uint32_t>(msg.data[3]) << 24) | 
							        (static_cast<uint32_t>(msg.data[2]) << 16) | 
							        (static_cast<uint32_t>(msg.data[1]) <<  8) | 
							        (static_cast<uint32_t>(msg.data[0]))
							       );
	
	CAN->sTxMailBox[buf_no].TDHR = ((static_cast<uint32_t>(msg.data[7]) << 24) | 
							        (static_cast<uint32_t>(msg.data[6]) << 16) | 
							        (static_cast<uint32_t>(msg.data[5]) <<  8) | 
							        (static_cast<uint32_t>(msg.data[4]))
							       );
							  
	//setup data length code
	CAN->sTxMailBox[buf_no].TDTR &= ~CAN_TDTxR_DLC_MASK;
	CAN->sTxMailBox[buf_no].TDTR |= msg.dlc & CAN_TDTxR_DLC_MASK;
							  
	//submit transmission request
	CAN->sTxMailBox[buf_no].TIR |= CAN_TIR_TXRQ;
}

void Can_buffer::clear_status(void)
{
	if (buf_no >=0 && buf_no < 3)
	{
		/* for transmit buffers, the request bit is cleared */
		uint32_t bit_to_clear;
		switch(buf_no)
		{
			case(0):
				bit_to_clear = CAN_TSR_RQCP0;
				break;
			case(1):
				bit_to_clear = CAN_TSR_RQCP1;
				break;
			case(2):
				bit_to_clear = CAN_TSR_RQCP2;
				break;
		}
		CAN->TSR |= bit_to_clear;
	}
	else if (buf_no >= 3 && buf_no < 5)	
	{
		/* for receive buffers, the last message is freed, allowing the next message to be read */
		switch(buf_no)
		{
			case(3):
				CAN->RF0R |= CAN_RFxR_RFOMx;
				break;				
			case(4):
				CAN->RF1R |= CAN_RFxR_RFOMx;
				break;
		}
	}
}

CAN_BUF_STAT Can_buffer::get_status(void)
{	
	if (buf_no >= 0 && buf_no < 3)			//register checks for transmission buffers
	{
		/* create reference registry value for corresponding buffer */
		uint32_t txok_template;
		uint32_t err_template;

		if (buf_no == 0)
		{
			txok_template = CAN_TSR_TXOK0 | CAN_TSR_RQCP0;
			err_template = CAN_TSR_TERR0 | CAN_TSR_RQCP0;
		}
		else if (buf_no == 1)
		{
			txok_template = CAN_TSR_TXOK1 | CAN_TSR_RQCP1;	
			err_template = CAN_TSR_TERR1 | CAN_TSR_RQCP1;
		}
		else if (buf_no == 2)
		{
			txok_template = CAN_TSR_TXOK2 | CAN_TSR_RQCP2;	
			err_template = CAN_TSR_TERR2 | CAN_TSR_RQCP2;
		}
		
		/* check status of chosen buffer and return */
		if (CAN->TSR & txok_template)		//transmission complete case
		{
			return BUF_TX_COMPLETED;
		}
		else if (CAN->TSR & err_template)	//error case
		{
			//read a more specific error register to determine error type
			switch (CAN->ESR & CAN_ESR_LEC_MASK)
			{
				case(CAN_ESR_STUFF_ERROR): return BUF_STUFF_ERROR; 
				case(CAN_ESR_FORM_ERROR): return BUF_FORM_ERROR; 
				case(CAN_ESR_ACK_ERROR): return BUF_ACK_ERROR; 
				case(CAN_ESR_CRC_ERROR): return BUF_CRC_ERROR; 
			}
			
		}
	}
	else if (buf_no >= 3 && buf_no < 5)		//register checks for reception buffers
	{
		/* decide what register to check */
		volatile uint32_t* reg_to_check;
		if (buf_no == 3)
		{
			reg_to_check = &CAN->RF0R;	
		}
		else if (buf_no == 4)
		{
			reg_to_check = &CAN->RF1R;
		}
		
		if (*reg_to_check & CAN_RFxR_FMP_MASK) 
		{
			return BUF_RX_COMPLETED;
		}
	}
	else
	{
		return BUF_NOT_COMPLETED;
	}
}

void Can_buffer::enable_interrupt(void)
{
	
}

void Can_buffer::disable_interrupt(void)
{
	
}

void Can_buffer::attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void))
{
	
}

void Can_buffer::detach_interrupt(CAN_INT_NAME interrupt)
{
	
}

bool Can_buffer::test_interrupt(CAN_INT_NAME interrupt)
{
	//TODO: Add interrupts
	return false;
}

/* ****************************************************************** */
/**
 * Can filter class
 */
 
void Can_filter::set_number(uint8_t fil_num)
{
	fil_no = fil_num;
}

Can_buffer* Can_filter::get_buffer(void)
{
	return buffer_link;	
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
	return true;	//STM32 filters are configurable
}

void Can_filter::set_buffer(Can_buffer* buffer)
{
	buffer_num = buffer->get_number();
	
	if (buffer_num == 3)
	{
		CAN->FFA1R &= ~(1<<fil_no);
	}
	else if (buffer_num == 4)
	{
		CAN->FFA1R |= (1<<fil_no);
	}
	
	buffer_link = buffer;
}

uint32_t Can_filter::get_filter_val(void)
{
	return filter_data;
}

void Can_filter::set_filter_val(uint32_t filter, bool RTR)
{
	
}

/* ****************************************************************** */
/**
 * Can mask class
 */
 
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
	
}

/* ****************************************************************** */
/**
 * For STM32, masks an filters are configured from banks. Each bank consists
 * of 2 32bit registers. Which can be configured as a filter list or filter
 * mask
 */
class Fm_bank
{
	public:
		/**
		 * Set an arbitrary value so it can address itself in registers
		 * 
		 * @param bank_num		Index this bank should have
		 * @return Nothing.
		 */
		void set_number(uint8_t bank_num)
		{
			bank_no = bank_num;
		}
		
		/**
		 * Activate or deactivate the filter bank
		 * 
		 * @param state			True for activate or false for deactivate
		 * @return Nothing.
		 */
		void set_active(bool state)
		{
			if (state)
			{
				CAN->FA0R |= (1<<bank_num);
			}
			else
			{
				CAN->FA0R &= ~(1<<bank_num);
			}
		}
		
		CAN_FM_MODE reg_0_mode = CAN_FM_OFF;
		CAN_FM_MODE reg_1_mode = CAN_FM_OFF;
		
		void* rep_object_0;		//pointer to the 1st either a filter or mask register this represents
		void* rep_object_1;		//pointer to the 2nd either a filter or mask register this represents
			
	private:
		uint8_t bank_no;

} 


/* ****************************************************************** */
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
		 * Constructor for STM32 specific implementation:
		 * Buffers, filters and masks are created and assigned arbitrary indices
		 * User must link filters and masks to buffers at run time
		 * 
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 Can_tree(void);
		 
		/**
		 * Enables the controller
		 * 
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 void enable(void);
		 
		/**
		 * Enable interrupts on the controller
		 * 
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 void enable_interrupts(void);
		 
		/**
		 * Attach CAN channel interrupts, wil overwrite the existing interrupt
		 * 
		 * @param  interrupt	The interrupt event to attach handler to
		 * @param  userFunc		The handler for this interrupt event
		 * @return Nothing.
		 */
		 void attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void));
		
		/**
		 * Detach interrupt to CAN channel
		 * 
		 * @param  interrupt   The interrupt event to detach the handler from
		 * @return Nothing.
		 */
		 void detach_interrupt(CAN_INT_NAME interrupt);
		
		/**
		 * Returns true if interrupt condition has handler attached
		 * 
		 * @param  interrupt   The bus interrupt condition to test if enabled 
		 * @return Boolean describing whether an interrupt handler is set for this condition
		 * 
		 */ 			 
		 bool test_interrupt(CAN_INT_NAME interrupt);
		
	
	//Fields
		 Can_buffer buffers[NUM_BUF];
		
		 Fm_bank banks[NUM_BANKS];
		 
};

Can_tree::Can_tree(void)
{
	for (uint8_t i=0; i<NUM_BUF; i++)
	{
		buffers[i].set_number(i);
		banks[i].set_number(i);
	}
	
	
	/* Setup filters and masks */
	CAN->FMR |= CAN_FMR_FINIT;		//put filters into initialization mode
	can_filter_init_mode = true;	
}

void Can_tree::enable(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_CANEN;	//enable peripheral CAN clock 
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //enable alternate function clock
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//enable clock for GPIO A, where the CAN pins are located
	
	//creating address descriptor for receive pin PA11
	IO_pin_address rx_pin_address;
	rx_pin_address.port = PORT_A;
	rx_pin_address.pin = PIN_11;
	
	//creating address descriptor for transmit pin PA12
	IO_pin_address tx_pin_address;
	tx_pin_address.port = PORT_A;
	tx_pin_address.pin = PIN_12;
	
	//instantiating interfaces for the pins
	Gpio_pin rx_pin = Gpio_pin::grab(rx_pin_address);
	Gpio_pin tx_pin = Gpio_pin::grab(tx_pin_address);
	
	//set the pins to the correct modes
	rx_pin.set_mode(GPIO_INPUT_PD);
	tx_pin.set_mode(GPIO_AF_PP);
}

static Can_tree Can_tree_imps[NB_CTRL];

/* ****************************************************************** */

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
 
Can::Can(Can_tree* imp)
{
	Can_controller = imp;	
	return;
}

//Method implementations
Can Can::bind(CAN_CTRL controller)
{
	return Can(&Can_tree_imps[controller]);
}

bool Can::initialise(CAN_RATE rate)
{
	//set bus to initialization mode, no auto retransmission configuration
	CAN->MCR |= (CAN_MCR_INRQ | CAN_MCR_NART);
	
	uint32_t brp = <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>000000;
	uint32_t div;
	
	switch(rate)
	{
		case(CAN_100K):
			div = 100000;
			break;
		case(CAN_125K):
			div = 125000;
			break;
		case(CAN_200K):
			div = 200000;
			break;
		case(CAN_250K):
			div = 250000;
			break;
		case(CAN_500K):
			div = 500000;
			break;
		case(CAN_1000K):
			div = 1000000;
			break;
	}		
	
	brp = (brp/18)/div;		//TODO: double check 18 actualy works
	CAN->BTR &= ~(((        0x03) << 24) | ((        0x07) << 20) | ((         0x0F) << 16) | (          0x1FF)); 
	CAN->BTR |=  ((((4-1) & 0x03) << 24) | (((5-1) & 0x07) << 20) | (((12-1) & 0x0F) << 16) | ((brp-1) & 0x1FF));
	
	CAN->MCR &= ~CAN_MCR_INRQ;			//get out of initialization mode
	CAN->FMR &= ~CAN_FMR_FINIT;			//get out of initialization mode for filters
	can_filter_init_mode = false;
	
	//give some time to exit initialization mode, if it doesn't when timeout expired return false
	uint32_t timeout = ENABLE_TOUT_MS;	
	while ((CAN->MSR & CAN_MCR_INRQ) && timeout)
	{
		timeout -= 1;
	};
	
	if (timeout <= 0)
	{
		return false;
	}
	else 
	{
		return true;
	}
}

void Can::set_buffer_mode(CAN_BUF buffer_name, CAN_BUF_MODE mode)
{
	//do nothing, STM32 buffer modes are fixed		
}

Can_message Can::read(CAN_BUF buffer_name)
{	
	return Can_controller->buffers[buffer_name].read();
}

bool Can::transmit(CAN_BUF buffer_name, Can_message msg)
{
	if (buffer_name == BUF_0 || buffer_name  == BUF_1 || buffer_name == BUF_2)
	{
		Can_controller->buffers[buffer_name].write(msg);
		return true;
	}
	else
	{
		return false;
	}
}

CAN_BUF_STAT Can::get_buffer_status(CAN_BUF buffer_name)
{
	return Can_controller->buffers[buffer_name].get_status();	
}

void Can::clear_buffer_status(CAN_BUF buffer_name)
{
	Can_controller->buffers[buffer_name].clear_status();	
}

void Can::set_filter_val(CAN_FIL filter_name, uint32_t filter_val, bool RTR)
{
	
}

uint32_t Can::get_filter_val(CAN_FIL filter_name)
{
		
}

bool Can::set_bank_filter(CAN_FIL filter_name, CAN_FM_MODE mode)
{	
	bank_index = filter_name/2;
	if (mode == CAN_FM_FIL)
	{
		Can_controller->banks[bank_index].set_active(true);
		if (filter_name%2 == 0)		
		{
			//even
			Can_controller->banks[bank_index].reg_0_mode = mode;
			Can_controller->banks[bank_index].rep_object_0 = &filters[filter_name];
		}
		else if (filter_name%2 == 1)
		{
			//odd
			Can_controller->banks[bank_index].reg_1_mode = mode;
			Can_controller->banks[bank_index].rep_object_1 = &filters[filter_name];
			
		}
	}
	else if (mode == CAN_FM_OFF)
	{
		if (filter_name%2 == 0)		
		{
			if (Can_controller->banks[bank_index].reg_1_mode == CAN_FM_OFF)
			{
				Can_controller->banks[bank_index].reg
			}
			
			//even
			Can_controller->banks[bank_index].reg_0_mode = mode;
			Can_controller->banks[bank_index].rep_object_0 = NULL;
		}
		else if (filter_name%2 == 1)                
		{
			//odd
			Can_controller->banks[bank_index].reg_1_mode = mode;
			Can_controller->banks[bank_index].rep_object_1 = NULL;
		}
	}
	else
	{
		return false;
	}
}

bool Can::set_bank_mask(CAN_MSK mask_name, CAN_FM_MODE mode)
{
	if (mode == CAN_FM_MSK)
	{
		Can_controller->banks[mask_name].reg_0_mode = mode;
		Can_controller->banks[mask_name].rep_object_0 = mask_name;
	}
	else if (mode == CAN_FM_OFF)
	{
		Can_controller->banks[mask_name].reg_0_mode = mode;
		Can_controller->banks[mask_name].rep_object_0 = NULL;
	}
	else
	{
		return false;
	}
}

void Can::set_mask_val(CAN_MSK mask_name, uint32_t mask_val, bool RTR)
{
	
}

uint32_t Can::get_mask_val(CAN_MSK mask_name)
{
	
}

void Can::enable_interrupts(void)
{

}

void Can::disable_interrupts(void)
{

}

void Can::enable_buffer_interrupt(CAN_BUF buffer_name)
{

}

void Can::disable_buffer_interrupt(CAN_BUF buffer_name)
{

}

void Can::attach_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt, void (*userFunc)(void))
{

}

void Can::attach_interrupt(CAN_INT_NAME interrupt, void (*userFunc)(void))
{

}

void Can::detach_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt)
{

}

void Can::detach_interrupt(CAN_INT_NAME interrupt)
{

}

bool Can::test_interrupt(CAN_BUF buffer_name, CAN_INT_NAME interrupt)
{
	//TODO: Add interrupts
	return false;
}

bool Can::test_interrupt(CAN_INT_NAME interrupt)
{
	//TODO: Add interrupts
	return false;
}

CAN_BUF Can::get_interrrupted_buffer(void)
{

}

bool clear_controller_interrupts(CAN_INT_NAME interrupt)
{
	//TODO: Add interrupts
	return false;
}
