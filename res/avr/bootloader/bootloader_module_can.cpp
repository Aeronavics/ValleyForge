// Copyright (C) 2011  Unison Networks Ltd
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
 *  FILE: 		bootloader_module_can.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	30-11-2012
 *
 *	Provides a bootloader module which only supports CAN programming.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.
/**
 *	CAN controller initialization function.
 *
 *	NOTE - Nothing.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void CAN_init(void);

/**
 *	Send a message on the CAN network.
 *
 *	NOTE - Message details are defined in the tranmission_message object.
 *
 *	TAKES:		transmission_message		object containg the id,dlc,data to send.
 *
 *	RETURNS:	Nothing.
 */
void transmit_CAN_message(bootloader_module_can::message_info& transmit_message);

/**
 *	CAN controller reset function.
 *
 *	NOTE - Nothing.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void CAN_reset(void);

/**
 *	Send a confirmation message back to host.
 *
 *	NOTE - Nothing.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void confirm_reception(void);

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_can::~bootloader_module_can()
{
	// All done.
	return;
}


void bootloader_module_can::init(void)
{
	//Initialize the CAN controller
	CAN_init();
	
	//
	
	return;
}


void bootloader_module_can::exit(void)
{
	//Reset the CAN controller to original conditions
	CAN_reset();
	//
	return;
}

//
//
//TEST function
//
void bootloader_module_can::can_test(uint16_t i)
{
	transmission_message.dlc = 2;
	transmission_message.message_type = 0x4ff;
	transmission_message.message[0] = (i >> 8);
	transmission_message.message[1] = i;
	transmit_CAN_message(transmission_message);
}
//
//
//
//

void bootloader_module_can::read_memory_procedure(volatile firmware_page& current_firmware_page)
{
	confirm_reception();

	//Store the 16bit page number
	current_firmware_page.page = (reception_message.message[0] << 8)|(reception_message.message[1]);
	
	//Store the 16bit code_length
	current_firmware_page.code_length = (reception_message.message[2] << 8)|(reception_message.message[3]);

	//Limit code_length to page size
	if(current_firmware_page.code_length > PAGE_SIZE)
	{
		current_firmware_page.code_length = PAGE_SIZE;
	}
}


void bootloader_module_can::write_data_procedure(volatile firmware_page& current_firmware_page)
{
	confirm_reception();
	
	//Check for possible array overflow
	if((current_firmware_page.current_byte + reception_message.dlc) > PAGE_SIZE)
	{
		reception_message.dlc = PAGE_SIZE - current_firmware_page.current_byte;//Limit the dlc
	}

	//store data from filter buffer(message data of 7 bytes) into the current_firmware_page(byte by byte)
	for(uint8_t i = 0 ; i < reception_message.dlc ; i++)
	{
		//may need to check not to overflow data buffer
		current_firmware_page.data[current_firmware_page.current_byte + i] = reception_message.message[i];//May need to check for overflow
	}

	//Increment the current byte in buffer
	current_firmware_page.current_byte += reception_message.dlc;
	
	//Check if the buffer is reay to be written to the flash
	if(current_firmware_page.current_byte >= (current_firmware_page.code_length -1))//check if buffer is full of desired code
	{
		current_firmware_page.ready_to_flash = true;
		current_firmware_page.current_byte = 0;
	}
}


void bootloader_module_can::get_info_procedure(void)
{
	transmission_message.dlc = 8;//if is longer than 8 bytes then must transmitt more messages
	transmission_message.message_type = GET_INFO;
	
	for(uint8_t i = 0 ; i < transmission_message.dlc ; i++)
	{
		transmission_message.message[i] = i;//Not yet determined
	}
	transmit_CAN_message(transmission_message);
}


void bootloader_module_can::write_memory_procedure(volatile firmware_page& current_firmware_page)
{
	confirm_reception();

	//Store the 16bit page number
	current_firmware_page.page = (reception_message.message[0] << 8)|(reception_message.message[1]);
	
	//Store the 16bit code_length
	current_firmware_page.code_length = (reception_message.message[2] << 8)|(reception_message.message[3]);
	
	//Limit code_length to page size
	if(current_firmware_page.code_length > PAGE_SIZE)
	{
		current_firmware_page.code_length = PAGE_SIZE;
	}
	
	//Start at the beginning of the page	
	current_firmware_page.current_byte = 0;
}


void bootloader_module_can::send_flash_page(volatile firmware_page& current_firmware_page)
{
	transmission_message.message_type = READ_DATA;//Same as host message
	current_firmware_page.current_byte = 0;//Start at the start of buffer
	while(current_firmware_page.current_byte < current_firmware_page.code_length)
	{
		//Determine the length of message, just in case we are closer than 8 bytes and need to send a smaller message
		transmission_message.dlc = (current_firmware_page.code_length - current_firmware_page.current_byte);
		if(transmission_message.dlc > 8)//Limit to 8 byte messages
		{
			transmission_message.dlc = 8;
		}

		//create message
		for(uint8_t i = 0 ; i < transmission_message.dlc ; i++)
		{
			transmission_message.message[i] = current_firmware_page.data[current_firmware_page.current_byte + i];
		}

		//Increment the current_byte for next loop
		current_firmware_page.current_byte = current_firmware_page.current_byte + transmission_message.dlc;//Last loop should make this equal to code_length		
		
		//Send the message
		transmit_CAN_message(transmission_message);
		
		//Wait for confirmation message to return from host
		while(reception_message.confirmed_send == false){};
		reception_message.confirmed_send = false;
	}
}


void bootloader_module_can::alert_host(void)//Send host a message to inform that the bootloader is awaiting messages
{
	transmission_message.dlc = 8;
	transmission_message.message_type = ALERT_HOST;//First bit will alway be zero so choose from 0-7 for it
	for(uint8_t i = 0 ; i < transmission_message.dlc ; i++)
	{
		transmission_message.message[i] = 0xFF;//No significance
	}
	transmit_CAN_message(transmission_message);
}


void bootloader_module_can::start_reset_procedure(volatile bool& firmware_finished_flag)
{
	confirm_reception();
	
	if(reception_message.message[0] == 0)
	{
		//use watchdog timer to reset the micro
		wdt_disable();
		wdt_enable(0);//WDT0_15MS = 0
		while(1){}
	}
	else
	{
		firmware_finished_flag = true;
	}
}


void bootloader_module_can::filter_message(firmware_page& current_firmware_page, bool& firmware_finished_flag)
{
	//Filter messages.
	if(reception_message.message_type == WRITE_DATA)
	{
		//write_data_procedure(buffer);//Need to take out the hard codes
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == READ_MEMORY)
	{
		//Allow for reading the flash
		if(current_firmware_page.ready_to_read_flash == false)
		{	
			read_memory_procedure(buffer);
			current_firmware_page.ready_to_read_flash == true;
		}
		else
		{
			send_flash_page(buffer);
			current_firmware_page.ready_to_read_flash == false;
			reception_message.message_received = false;//Reseting here allows the program to loop again in order to read the flash page
		}
	}

	else if(reception_message.message_type == GET_INFO)
	{
		get_info_procedure();
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == START_RESET)
	{
		start_reset_procedure(firmware_finished_flag);
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == WRITE_MEMORY)
	{
		write_memory_procedure(buffer);
		reception_message.message_received = false;
	}
}



// IMPLEMENT PRIVATE FUNCTIONS.
void confirm_reception(void)
{
	module.transmission_message.dlc = 0;//currently reply empty message with host message id
	module.transmission_message.message_type = module.reception_message.message_type;
	transmit_CAN_message(module.transmission_message);
}


void CAN_init(void)
{
	uint8_t mob_number = 0;
	uint8_t number_of_mobs = 15;//ATmega64m1 = 6, AT90CAN128 = 15

	//resets the CAN controller
	CANGCON = (1<<SWRES);
	
	//reset all of the MObs as they have no default value(may not need to reset all as they do not all need to be used)
	for(mob_number = 0 ; mob_number < number_of_mobs ; mob_number++)
	{
		//select can page	
		CANPAGE = (mob_number<<4);
		
		//Set all MOb registers to zero
		CANSTMOB = 0x00;//Clear all flags
		CANCDMOB = 0x00;//Disables MObs
	}
	
	//Set up bit-timing and CAN timing (use data sheet to select desired bit timing)
	CANBT1 = 0x02;//125kbps	0x1E	1Mbps   0x02
	CANBT2 = 0x04;//	0x04		0x04
	CANBT3 = 0x13;//	0x13		0x13
	//CANCON = ?;//CAN timing prescalar

	
	//Id's for reception
	uint16_t id;
	id = base_id;

	//Choose the MObs to set up
	//
	//
	//MOB NUMBER 0
	//Reception MOb
	mob_number = 0;
	CANPAGE = (mob_number<<4);
	
	CANIDT1 = id>>3;;//Set MOb ID if receiving MOb.
	CANIDT2 = id<<5;//
	CANIDT3 = 0x00;//
	CANIDT4 = 0x00;//
	
	CANIDM1 = 0xFE;//Set MOb masking ID if receiving MOb.
	CANIDM2 = 0x00;//		//At the moment are filtering first two hex numbers e.g id=0x123, filter = 0x12z - where z can be any number
	CANIDM3 = 0x00;//
	CANIDM4 = 0x00;//
	
	CANCDMOB = (1<<CONMOB1)|(8);//Enable the MOb for the mode. In this case for reception of 8 data bytes, in standard format(11 bits) with no automatic reply.
	//Should not do this for the tranmtting messages as they will begin to transmitt.
	//
	//
	//MOB NUMBER 1
	//Tranmission MOb
	mob_number = 1;
	CANPAGE = (mob_number<<4);
	
	CANIDT1 = 0x00;//Set MOb ID if receiving MOb.
	CANIDT2 = 0x00;//Will be set by user
	CANIDT3 = 0x00;//
	CANIDT4 = 0x00;//

	CANIDM1 = 0x00;//Set MOb masking ID if receiving MOb.
	CANIDM2 = 0x00;//All to zero for tranmit
	CANIDM3 = 0x00;//
	CANIDM4 = 0x00;//
	

	//Enable the interupts for the MObs enabled
	CANIE1 = 0x00;
	CANIE2 = (1<<IEMOB0);//Enable interupts on MOb0(reception needs interupt).

	//Enable general interupts
	CANGIE = (1<<ENIT)|(1<<ENRX);//Enable receive and CAN_IT

	//Enable can communication
	CANGCON = (1<<ENASTB);//Sets the AVR pins to Tx and Rx
}

void transmit_CAN_message(bootloader_module_can::message_info& transmit_message)
{
	//Select tranmitting page
	uint8_t mob_number = 1;
	CANPAGE = (mob_number<<4);//MOb1
	
	//Wait until MOb1 is ready to use
	while(CANEN2 & (1<<ENMOB1)){};
	
	//Clear interupt flags
	CANSTMOB = 0x00;
	
	//Set message id
	CANIDT4 = 0x00;
	CANIDT3 = 0x00;
	CANIDT2 = transmit_message.message_type << 5;
	CANIDT1 = transmit_message.message_type >> 3;
	
	//Set message
	for(uint8_t i = 0 ; i < transmit_message.dlc ; i++)
	{
		CANMSG = transmit_message.message[i];
	}
	
	//Enable tranmission with desired message length
	CANCDMOB = (1<<CONMOB0)|(transmit_message.dlc);
	
	//Wait until the message has sent
	while ((CANSTMOB & (1<<TXOK)) == 0){};//May need to check for errors otherwise we will be in here forever

	//Disable transmit
	CANCDMOB = 0x00;
	
	//Clear interupt flags
	CANSTMOB = 0x00;
}

void CAN_reset(void)
{
	CANGCON = (1<<SWRES);
}


//Interupt service routine for interupts from CAN controller
//This routine only operates on received messages, reads the ID, DLC, data. Sets a flag to tell Boot loader that a new message has been received.
ISR(CANIT_vect)//Different for ATMega64M1
{
	//Save curent MOb page for current program operations. 
	uint8_t saved_MOb = CANPAGE;

	//Select the reception MOb0
	uint8_t mob_number = 0;
	CANPAGE = (mob_number<<4);
	
	//Check that the interupt was a reception(RXOK)
	if(CANSTMOB & (1<<RXOK))
	{
		//Check node ID, if not the same exit ISR
		//Node ID is the first byte of data, this will then auto increment to second byte
		if(CANMSG == NODE_ID)
		{
			//Store message id
			module.reception_message.message_type = (CANIDT1<<3)|(CANIDT2>>5);
			
			//A confirmation message received
			if(module.reception_message.message_type == module.READ_DATA)
			{
				module.reception_message.confirmed_send = true;
			}				
			//A host command message received
			else
			{
				//Store dlc
				module.reception_message.dlc = (CANCDMOB & 0x0F) - 1;//Minus 1 as the first byte was taken up by the node ID
				if(module.reception_message.dlc > 7)
				{
					module.reception_message.dlc = 7;//Check required as CAN controller may give greater than 8 dlc value. 
				}

				//Store the message
				for(uint8_t i = 0 ; i < module.reception_message.dlc ; i++)
				{
					module.reception_message.message[i] = CANMSG;//The CANPAGE index auto increments
				}
			
				//Tell Boot loader that the message was received
				module.reception_message.message_received = true;
			}
		}
	}
	//Reset status flags
	CANSTMOB = 0x00;

	//Reenable reception for MOb
	CANCDMOB = (1<<CONMOB1)|(8);

	//Restore previous MOb page
	CANPAGE = saved_MOb;

}

// ALL DONE.
