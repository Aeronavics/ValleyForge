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

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
 *	CAN controller initialization function.
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
	//Initialize the CAN controller.
	CAN_init();
	
	// All done.
	return;
}

void bootloader_module_can::exit(void)
{
	//Reset the CAN controller to original conditions.
	CAN_reset();

	// All done.
	return;
}

void bootloader_module_can::event_idle()
{
	// All done.
	return;
}

void bootloader_module_can::event_periodic()
{
	// Check for a new message.
	if (!reception_message.message_received)
	{
		// The mailbox is empty.

		// Check if communication with host has already occured.
		if(!communication_started)
		{
			// TODO - This is going to send the alert message once every 10ms at the moment.  This might be too often?  If so, then you will to
			//	  only send the alert once every so many times through here.
		
			// Send message to host to say that bootloader is awaiting messages.
			alert_uploader();
		}
	}
	else
	{
		//Filter messages.	
		filter_message(buffer, read_buffer);

		//If we are filtering a message then communication with host must have occured
		communication_started = true;

		// Restart the bootloader timeout.
		set_bootloader_timeout(false);
		set_bootloader_timeout(true);
	}
}

// TODO - These ones below should probably all be private.

void bootloader_module_can::reset_request_procedure()
{
	confirm_reception();
	
	if(reception_message.message[0] == 0)
	{
		// Reboot the microcontroller back to the bootloader again.
		reboot_to_bootloader();

		// We will never reach here.
	}
	else
	{
		// TODO - This starts the application directly without a reboot.  There is also reboot_to_application() if you wanted that instead?

		// Start the application.
		start_application();

		// We will never reach here.
	}

	// We will never reach here.
	return;
}

void bootloader_module_can::get_info_procedure(void)
{
	transmission_message.dlc = 7;
	transmission_message.message_type = GET_INFO;
	
	//Insert Device signaure
	transmission_message.message[0] = DEVICE_SIGNATURE_0;
	transmission_message.message[1] = DEVICE_SIGNATURE_1;
	transmission_message.message[2] = DEVICE_SIGNATURE_2;
	transmission_message.message[3] = DEVICE_SIGNATURE_3;
	
	//Insert bootloader version
	transmission_message.message[4] = static_cast<uint8_t>(BOOTLOADER_VERSION >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(BOOTLOADER_VERSION);
	
	//test
	//transmission_message.message[6] = NODE_ID;
	
	transmit_CAN_message(transmission_message);
}

void bootloader_module_can::write_memory_procedure(firmware_page& current_firmware_page)
{
	//Store the 32bit page number
	current_firmware_page.page = (((uint32_t)reception_message.message[0]) << 24)|(((uint32_t)reception_message.message[1]) << 16)|(((uint32_t)reception_message.message[2]) << 8)|((uint32_t)reception_message.message[3]);

	//Store the 16bit code_length
	current_firmware_page.code_length = (reception_message.message[4] << 8)|(reception_message.message[5]);
	
	//Limit code_length to page size
	if(current_firmware_page.code_length > SPM_PAGESIZE)
	{
		current_firmware_page.code_length = SPM_PAGESIZE;
	}
	
	//Start at the beginning of the page
	current_firmware_page.current_byte = 0;

	confirm_reception();
}

void bootloader_module_can::write_data_procedure(firmware_page& current_firmware_page)
{
	//Check for possible array overflow
	if((current_firmware_page.current_byte + reception_message.dlc) > current_firmware_page.code_length)
	{
		reception_message.dlc = current_firmware_page.code_length - current_firmware_page.current_byte;//Limit the dlc
	}

	//store data from filter buffer(message data of 7 bytes) into the current_firmware_page(byte by byte)
	for(uint8_t i = 0 ; i < reception_message.dlc ; i++)
	{
		current_firmware_page.data[current_firmware_page.current_byte + i] = reception_message.message[i];
	}

	//Increment the current byte in buffer
	current_firmware_page.current_byte += reception_message.dlc;
	
	//Check if the buffer is reay to be written to the flash
	if(current_firmware_page.current_byte >= (current_firmware_page.code_length -1))
	{
		current_firmware_page.ready_to_flash = true;
		current_firmware_page.current_byte = 0;
	}

	confirm_reception();
}

void bootloader_module_can::read_memory_procedure(firmware_page& current_firmware_page)
{
	//Store the 16bit page number
	current_firmware_page.page = (((uint32_t)reception_message.message[0]) << 24)|(((uint32_t)reception_message.message[1]) << 16)|(((uint32_t)reception_message.message[2]) << 8)|((uint32_t)reception_message.message[3]);
	
	//Store the 16bit code_length
	current_firmware_page.code_length = (reception_message.message[4] << 8)|(reception_message.message[5]);

	//Limit code_length to page size
	if(current_firmware_page.code_length > SPM_PAGESIZE)
	{
		current_firmware_page.code_length = SPM_PAGESIZE;
	}
	
	confirm_reception();
}

void bootloader_module_can::send_flash_page(firmware_page& current_firmware_page)
{
	transmission_message.message_type = READ_DATA;
	current_firmware_page.current_byte = 0;//Start at the start of buffer
	reception_message.confirmed_send = false;//Initialize for this procedure
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
		current_firmware_page.current_byte += transmission_message.dlc;		
		
		//Send the message
		transmit_CAN_message(transmission_message);
		
		//Wait for confirmation message to return from host
		while(reception_message.confirmed_send == false && reception_message.message_received == false){}
		
		//Allow the host to stop the the reading if it sees a message is lost. Host must send another message to the bootloader
		if((reception_message.message_received == true))
		{
			break;//breaks the while loop
		}

		reception_message.confirmed_send = false;
	}
}

void bootloader_module_can::filter_message(firmware_page& current_firmware_page, firmware_page& read_current_firmware_page)
{
	if(reception_message.message_type == RESET_REQUEST)
	{
		reset_request_procedure();

		// TODO - The above function will never return, because it results in a CPU reset.  Is that what you wanted?

		// We will never reach here.
	}	

	else if(reception_message.message_type == GET_INFO)
	{
		get_info_procedure();
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == WRITE_MEMORY)
	{
		write_memory_procedure(current_firmware_page);
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == WRITE_DATA)
	{
		write_data_procedure(current_firmware_page);
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == READ_MEMORY)
	{
		//Allow for reading the flash
		if(read_current_firmware_page.ready_to_read_flash == false)
		{	
			read_memory_procedure(read_current_firmware_page);
			read_current_firmware_page.ready_to_read_flash = true;
		}
		else
		{
			reception_message.message_received = false;//Reseting here allows the program to loop again in order to read the flash page. Also before sending so host 									//can send another read memory message to reset the read memory
			read_current_firmware_page.ready_to_read_flash = false;//Must be above sending to ensure the sending can be reset
			send_flash_page(read_current_firmware_page);
		}
	}

}

void bootloader_module_can::alert_uploader(void)//Send host a message to inform that the bootloader is awaiting messages
{
	transmission_message.dlc = 8;
	transmission_message.message_type = ALERT_UPLOADER;
	for(uint8_t i = 0 ; i < transmission_message.dlc ; i++)
	{
		transmission_message.message[i] = 0xFF;//No significance
	}
	transmit_CAN_message(transmission_message);
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

	//resets the CAN controller
	CANGCON = (1<<SWRES);
	
	//reset all of the MObs as they have no default value(may not need to reset all as they do not all need to be used)
	for(mob_number = 0 ; mob_number < NUMBER_OF_MOB_PAGES ; mob_number++)
	{
		//select can page	
		CANPAGE = (mob_number<<4);
		
		//Set all MOb registers to zero
		CANSTMOB = 0x00;//Clear all flags
		CANCDMOB = 0x00;//Disables MObs
	}
	
	//Set up bit-timing and CAN timing
	CANBT1 = CAN_BAUD_RATE_CONFIG_1;
	CANBT2 = CAN_BAUD_RATE_CONFIG_2;
	CANBT3 = CAN_BAUD_RATE_CONFIG_3;
	
	//CANCON = ?;//CAN timing prescalar

	
	//Id's for reception
	uint16_t id;
	id = BASE_ID;

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
	while (((CANSTMOB & (1<<TXOK)) == 0)&&((CANSTMOB & (1<<AERR)) == 0))//May need to check for more errors otherwise we will be in here forever
	{}	

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
#if defined (__AVR_AT90CAN128__)
ISR(CANIT_vect)
#else
ISR(CAN_INT_vect)
#endif
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
