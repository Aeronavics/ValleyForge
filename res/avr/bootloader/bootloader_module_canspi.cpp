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
 *  FILE: 		bootloader_module_canspi.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	7-1-2013
 *
 *	Provides a bootloader module which only supports CAN via SPI programming.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <avr/interrupt.h>
#include <avr/eeprom.h>

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
 *	Initializes the mcp2515 with the desired CAN configuration
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void init_mcp2515(void);

/**
 *	Send a message on the CAN network.
 *
 *	NOTE - Message details are defined in the tranmission_message object.
 *
 *	TAKES:		transmission_message		object containing the id,dlc,data to send.
 *
 *	RETURNS:	Nothing.
 */
void transmit_CAN_message(bootloader_module_canspi::message_info& tranmission_message);

/**
 *	Send a confirmation message back to host.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void confirm_reception_mcp2515(bool confirmation_successful);

/**
 *	Reset the mcp2515
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void mcp2515_reset();


/*
 * 
 * SPI function prototypes
 * 
 */
/**
 *	Initializes the spi communication with mcp2515.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void spi_init(void);


/**
 *	Shifts out and receives 1 byte in spi communication.
 *
 *	TAKES:		data		information to be shifted out.
 *
 *	RETURNS:	1 byte of information received during the shift.
 */
uint8_t spi_readwrite(uint8_t data);

/**
 *	Receives 1 byte in spi communication.
 *
 *	NOTE - A meaningless byte is sent in order to shift in data.
 * 
 *	TAKES:		Nothing.
 *
 *	RETURNS:	1 byte of information received during the communication.
 */
uint8_t spi_justread(void);

/**
 *	Shifts out 1 byte in spi communication.
 *
 *	TAKES:		data		information to be shifted out.
 *
 *	RETURNS:	Nothing.
 */
void spi_justwrite(uint8_t data);

/**
 *	Selects the slave for spi communication.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void select_slave(void);

/**
 *	Deselects the slave for spi communication.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void deselect_slave(void);


/*
 * 
 * CAN-MCP2515 via spi function prototypes
 * 
 */
/**
 *	Overwrites a registers in mcp2515.
 *
 *	TAKES:		address		register address in mcp2515
 * 				data		register value to write	
 *
 *	RETURNS:	Nothing
 */
void mcp2515_write_register(uint8_t address, uint8_t data);

/**
 *	Reads a register in mcp2515.
 *
 *	TAKES:		address		register address in mcp2515
 *
 *	RETURNS:	current register value
 */
uint8_t mcp2515_read_register(uint8_t address);

/**
 *	Modifies bits in a register.
 *
 *	TAKES:		address		register address in mcp2515
 * 				data		register value to write (before masking)
 * 				mask		mask that determines which bits are modified
 * 
 *	RETURNS:	Nothing
 */
void mcp2515_modify_bits(uint8_t address, uint8_t mask, uint8_t data);

/**
 *	Requests mcp2515 to send a tranmission buffer.
 *
 *	TAKES:		tx_buffer		The number of the transmission buffer (0-2)
 * 
 *	RETURNS:	Nothing
 */
void mcp2515_request_to_send(uint8_t tx_buffer);

/**
 *	Retreves CAN received message information from mcp2515.
 *
 *	TAKES:		rx_buffer		The number of the reception buffer (0-1)
 * 				reception_message		object which the id,dlc,data will be stored.
 * 
 *	RETURNS:	The node identifier from the received message.
 */
uint8_t mcp2515_read_rx_buffer(uint8_t rx_buffer, volatile bootloader_module_canspi::message_info& reception_message);

/**
 *	Loads information into tranmission buffer in mcp2515.
 *
 *	TAKES:		tx_buffer		The number of the transmission buffer (0-2)
 * 				transmission_message		object containing the id,dlc,data to send.
 * 
 *	RETURNS:	Nothing
 */
void mcp2515_load_tx_buffer(uint8_t tx_buffer, bootloader_module_canspi::message_info& tranmission_message);

/**
 *	Reads status bits from mcp2515.
 *
 *	NOTE - status bits are CANINTF.RX0IF, CANINTF.RX1IF, TXB0CNTTRL.TXREQ, CANINTF.TX0IF, 
 * 					TXB1CNTTRL.TXREQ, CANINTF.TX1IF, TXB2CNTTRL.TXREQ, CANINTF.TX2IF
 *
 *	TAKES:		Nothing
 * 
 *	RETURNS:	Nothing
 */
uint8_t mcp2515_read_status(void);

/**
 *	Inilialize CAN communication on mcp2515
 *
 *	TAKES:		Nothing
 * 
 *	RETURNS:	Nothing
 */
void mcp2515_init_CAN(void);


// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_canspi::~bootloader_module_canspi()
{
	// All done.
	return;
}

void bootloader_module_canspi::init(void)
{
	//Initialize flags
	communication_started = false;
	ready_to_send_page = false;
	write_address_stored = false;
	reception_message.message_received = false;
	
	//Initialize the external CAN controller.
	init_mcp2515();
	
	// All done.
	return;
}

void bootloader_module_canspi::exit(void)
{
	// Must initialize the spi communication before reset instrustion can be sent
	spi_init();
	
	// Reset the mcp2515 to its original state.
	mcp2515_reset();
	
	// Reset spi peripheral to intial startup values 
	DDRB = 0x00;// Reset all spi pins to inputs
	SPCR = 0x00;

	// All done.
	return;
}

void bootloader_module_canspi::event_idle()
{
	if(!buffer.ready_to_read && ready_to_send_page)// Send the buffer once it has been read to
	{
		ready_to_send_page = false;
		send_flash_page(buffer);
	}
	
	// All done.
	return;
}


void bootloader_module_canspi::event_periodic()
{
	static uint8_t alert_count = 0; 
	 
	// Check for a new message.
	if (!reception_message.message_received)
	{
		// The mailbox is empty.

		// Check if communication with host has already occured.
		if(!communication_started)
		{
			alert_count++;
			if(alert_count == ALERT_UPLOADER_PERIOD)
			{
				// Send message to host to say that bootloader is awaiting messages.
				alert_uploader();
				alert_count = 0;
			}
		}
	}
	else
	{
		// If we are filtering a message then communication with host must have occured
		communication_started = true;
		
		// Filter messages.	
		filter_message(buffer);

		// Restart the bootloader timeout.
		set_bootloader_timeout(false);
		set_bootloader_timeout(true);
	}

	// All done.
	return;
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void confirm_reception_mcp2515(bool confirmation_successful)
{
	//Reply to the host whether the received message was successful or not
	module.transmission_message.dlc = 1;
	if(confirmation_successful)
	{
		module.transmission_message.message[0] = 1;
	}
	else
	{
		module.transmission_message.message[0] = 0;
	}
	module.transmission_message.message_type = module.reception_message.message_type;
	transmit_CAN_message(module.transmission_message);

	// All done.
	return;
}

void init_mcp2515(void)
{
	//Set up pin change interupt on pinK0, this will be use for interupt from INT pin of mcp2515.
	PCMSK2 |= (1<<PCINT16);
	PCICR |= (1<<PCIE2);
	DDRK &= ~(1<<DDD0);
	module.pin_K0_state = (PINK & (1<<PIN0));// Get intial state of pin
	
	// Initialize spi communication
	spi_init();
	
	// Initialize CAN communication
	mcp2515_init_CAN();
}

void transmit_CAN_message(bootloader_module_canspi::message_info& tranmission_message)
{
	mcp2515_load_tx_buffer(0, tranmission_message);
	mcp2515_request_to_send(0);
	
	// Wait until the tranmission is complete
	uint8_t status_register, control_register;
	status_register = mcp2515_read_status();
	while(!(status_register & (0x08)))// If transmission finished, this flag is set then exit
	{
		status_register = mcp2515_read_status();
		// Check for error conditions
		control_register = mcp2515_read_register(MCP_TXB0CTRL);
		if(control_register & 0x10)// Transmission error occured
		{
			// TODO - set some flag so that whatever is using it is informed an error has occured
			break;
		}
	}
	mcp2515_modify_bits(MCP_CANINTF, 0x04, 0x00);// Reset the tranmission finished flag. 
}

void mcp2515_reset()
{
	// Execute instruction
	select_slave();
	spi_justwrite(MCP_RESET);
	deselect_slave();
	
	//wait 128 cycles to allow oscillator to stabilize
	_delay_ms(10);// TODO - implement the delay with a timer
}

/*
 * 
 * SPI functions
 * 
 */
void spi_init(void)
{
	DDRB = (1<<DDB2)|(1<<DDB1)|(1<<DDB0);// Outputs set for MOSI,SCK,SS.
	SPCR |= (1<<SPE)|(1<<MSTR);// enable spi as master with sck = fclk/4
}

uint8_t spi_readwrite(uint8_t data)   
{   
	// set data to send into SPI data register   
	SPDR = data;   
	// Wait for transmission complete    
	while(!(SPSR & (1<<SPIF))); 
	// return data read from SPI   
	return SPDR;
}

uint8_t spi_justread(void)
{
	return spi_readwrite(0x00);// Meaningless write but return the read.
}

void spi_justwrite(uint8_t data)
{
	spi_readwrite(data);
}

void select_slave(void)
{
	PORTB &= ~(1<<PB0);// Drive cs low.
}

void deselect_slave(void)
{
	PORTB |= (1<<PB0);// Drive cs high.
}


/*
 * 
 * CAN-MCP2515 via spi
 * 
 */
void mcp2515_write_register(uint8_t address, uint8_t data)
{
	// Execute instruction
	select_slave();
	spi_justwrite(MCP_WRITE);
	spi_justwrite(address);
	spi_justwrite(data);
	deselect_slave();
}

uint8_t mcp2515_read_register(uint8_t address)
{
	uint8_t read_data;
	
	// Execute instruction
	select_slave();
	spi_justwrite(MCP_READ);
	spi_justwrite(address);
	read_data = spi_justread();
	deselect_slave();
	
	return read_data;
}

void mcp2515_modify_bits(uint8_t address, uint8_t mask, uint8_t data)
{
	// Execute instruction
	select_slave();
	spi_justwrite(MCP_BITMOD);
	spi_justwrite(address);
	spi_justwrite(mask);
	spi_justwrite(data);
	deselect_slave();
}

void mcp2515_request_to_send(uint8_t tx_buffer)
{
	uint8_t instruction = 0;
	
	// Select the desired buffer instruction
	if(tx_buffer == 2)
	{
		instruction = MCP_RTS_TX2;
	}
	else if(tx_buffer == 1)
	{
		instruction = MCP_RTS_TX1;
	}
	else if(tx_buffer == 0)
	{
		instruction = MCP_RTS_TX0;
	}
	
	// Execute instruction
	select_slave();
	spi_justwrite(instruction);
	deselect_slave();
}

uint8_t mcp2515_read_rx_buffer(uint8_t rx_buffer, volatile bootloader_module_canspi::message_info& reception_message)
{
	uint8_t instruction = 0;
	uint8_t temp_buffer[11];
	
	// Select the desired buffer instruction
	if(rx_buffer == 0)
	{
		instruction = MCP_READ_RX0;
	}
	else if(rx_buffer == 1)
	{
		instruction = MCP_READ_RX1;
	}
	
	// Execute instruction
	select_slave();
	spi_justwrite(instruction);
	temp_buffer[0] = spi_justread();// Save RXBnSIDH
	temp_buffer[1] = spi_justread();// Save RXBnSIDL
	spi_justread();// Don't save RXBnEID8
	spi_justread();// Don't save RXBnEID0
	temp_buffer[2] = spi_justread();// Save RXBnDLC
	temp_buffer[3] = spi_justread();// Save the NODE_ID from RXBnD0
	for(uint8_t i = 4 ; i < 11 ; i++)// Save RXBnD1 to RXBnD7
	{
		temp_buffer[i] = spi_justread();
	}
	deselect_slave();
	
	// Extract information from the buffer
	reception_message.message_type = ((static_cast<uint16_t>(temp_buffer[0])) << 3)|((static_cast<uint16_t>(temp_buffer[1])) >> 5);
	reception_message.dlc = (temp_buffer[2]&(0x0F)) - 1;// Minus 1 as the first byte was taken up by the node ID.
	if (reception_message.dlc > 7)
	{
		reception_message.dlc = 7; // Check required as CAN controller may give greater than 8 dlc value.
	}
	for(uint8_t i = 0 ; i < reception_message.dlc ; i++)
	{
		reception_message.message[i] = temp_buffer[i + 4];
	}
	
	return temp_buffer[3];// Return the node id
}

void mcp2515_load_tx_buffer(uint8_t tx_buffer, bootloader_module_canspi::message_info& tranmission_message)
{
	uint8_t instruction = 0;
	uint8_t temp_buffer[11];
	
	// Select the desired buffer instruction
	if(tx_buffer == 0)
	{
		instruction = MCP_LOAD_TX0;
	}
	else if(tx_buffer == 1)
	{
		instruction = MCP_LOAD_TX1;
	}
	else if(tx_buffer == 2)
	{
		instruction = MCP_LOAD_TX2;
	}

	// Input information into buffer
	temp_buffer[0] = tranmission_message.message_type >> 3;
	temp_buffer[1] = tranmission_message.message_type << 5;
	temp_buffer[2] = tranmission_message.dlc;
	for(uint8_t i = 0 ; i < tranmission_message.dlc ; i++)
	{
		 temp_buffer[i + 3] = tranmission_message.message[i];
	}
	
	// Execute instruction
	select_slave();
	spi_justwrite(instruction);
	spi_justwrite(temp_buffer[0]);// Set TXBnSIDH
	spi_justwrite(temp_buffer[1]);// Set TXBnSIDL
	spi_justwrite(0x00);// Set TXBnEID8
	spi_justwrite(0x00);// Set TXBnEID0
	spi_justwrite(temp_buffer[2]);// Set TXBnDLC
	for(uint8_t i = 3 ; i < (tranmission_message.dlc + 3) ; i++)// Set TXBnD0 to TXBnD7 - or exit if less
	{
		spi_justwrite(temp_buffer[i]);
	}
	deselect_slave();
}

uint8_t mcp2515_read_status(void)
{
	uint8_t status;
	
	// Execute instruction
	select_slave();
	spi_justwrite(MCP_READ_STATUS);
	status = spi_justread();
	deselect_slave();
	
	return status;
}

void mcp2515_init_CAN(void)
{
	uint8_t current_mode;
	
	// Reset mcp2515
	mcp2515_reset();
	
	// Configuration mode set on restart
	mcp2515_modify_bits(MCP_CANCTRL, 0xE0, 0x80);
	
	// Wait until the mode is configuration mode
	current_mode = mcp2515_read_register(MCP_CANSTAT);
	while((current_mode & 0xE0) != 0x80)
	{
		current_mode = mcp2515_read_register(MCP_CANSTAT);
		// Do nothing
	}
	
	// Setup CAN bit timing
	uint8_t cnfg1, cnfg2, cnfg3;
	
	cnfg1 = (CAN_SJW << 6)|(CAN_BRP);
	cnfg2 = (0x80)|(CAN_PS1 << 3)|(CAN_PRS);// 0x80-allows setting of PHSEG2 in cnfg3
	cnfg3 = (CAN_PS2);
	
	mcp2515_write_register(MCP_CNF1, cnfg1);
	mcp2515_write_register(MCP_CNF2, cnfg2);
	mcp2515_write_register(MCP_CNF3, cnfg3);
	
	
	// Set up masks and filters
	uint16_t id = BASE_ID;
	
	mcp2515_write_register(MCP_RXF0SIDH, (id >> 3));// Load into RXB0
	mcp2515_write_register(MCP_RXF0SIDL, (id << 5));
	mcp2515_write_register(MCP_RXM0SIDH, 0xFE);// Allow partial filtering
	mcp2515_write_register(MCP_RXM0SIDL, 0x00);

	//Set up buffer
	mcp2515_write_register(MCP_RXB0CTRL, 0x20);// Accept messages that fit filter critera and are standard CAN format
	
	//Set up interupt
	mcp2515_write_register(MCP_CANINTE, 0x01);// Set interupt for receive buffer 0
	
	// Enable CAN communication
	mcp2515_write_register(MCP_CANCTRL, 0x00);// Set to normal mode.
	
	// Wait until the mode is normal mode
	current_mode = mcp2515_read_register(MCP_CANSTAT);
	while((current_mode & 0xE0) != 0x00)
	{
		current_mode = mcp2515_read_register(MCP_CANSTAT);
		// Do nothing
	}
}


// IMPLEMENT PRIVATE CLASS FUNCTIONS.

void bootloader_module_canspi::reset_request_procedure()
{
	confirm_reception_mcp2515(message_confirmation_success);// Always successful
	
	if(reception_message.message[0] == 0)
	{
		// Reboot the microcontroller back to the bootloader again.
		reboot_to_bootloader();

		// We will never reach here.
	}
	else
	{
		// Reboot to the application.
		reboot_to_application();

		// We will never reach here.
	}

	// We will never reach here.
	return;
}

void bootloader_module_canspi::get_info_procedure(void)
{
	transmission_message.dlc = 6;
	transmission_message.message_type = GET_INFO;
	
	//Insert Device signaure
	transmission_message.message[0] = DEVICE_SIGNATURE_0;
	transmission_message.message[1] = DEVICE_SIGNATURE_1;
	transmission_message.message[2] = DEVICE_SIGNATURE_2;
	transmission_message.message[3] = DEVICE_SIGNATURE_3;
	
	//Insert bootloader version
	transmission_message.message[4] = static_cast<uint8_t>(BOOTLOADER_VERSION >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(BOOTLOADER_VERSION);
	
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

void bootloader_module_canspi::write_memory_procedure(firmware_page& current_firmware_page)
{
	// Store the 32bit page number.
	current_firmware_page.page = ((static_cast<uint32_t>(reception_message.message[0])) << 24) |
				     ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
				     ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
				     (static_cast<uint32_t>(reception_message.message[3]));

	// Store the 16bit code_length.
	current_firmware_page.code_length = (reception_message.message[4] << 8) | (reception_message.message[5]);

	//Check for errors in message details
	if (current_firmware_page.code_length > SPM_PAGESIZE || current_firmware_page.page >= BOOTLOADER_START_ADDRESS)//TODO - import the value from TC
	{
		//Message failure
		message_confirmation_success = false;
		write_address_stored = false;
	}
	else
	{
		//Message success
		write_address_stored = true;
		current_firmware_page.current_byte = 0;
	}

	confirm_reception_mcp2515(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_canspi::write_data_procedure(firmware_page& current_firmware_page)
{
	// Only wrtie to buffer if a memory address and length have been provided
	if(write_address_stored)
	{
		// Check for possible array overflow.
		if ((current_firmware_page.current_byte + reception_message.dlc) > current_firmware_page.code_length)
		{
			reception_message.dlc = current_firmware_page.code_length - current_firmware_page.current_byte; // Limit the dlc.
		}

		// Store data from filter buffer(message data of 7 bytes) into the current_firmware_page(byte by byte).
		for (uint8_t i = 0; i < reception_message.dlc; i++)
		{
			current_firmware_page.data[current_firmware_page.current_byte + i] = reception_message.message[i];
		}

		// Increment the current byte in buffer.
		current_firmware_page.current_byte += reception_message.dlc;

		// Check if the buffer is ready to be written to the flash.
		if (current_firmware_page.current_byte >= (current_firmware_page.code_length))
		{
			current_firmware_page.ready_to_write = true;
			current_firmware_page.current_byte = 0;
			write_address_stored = false;
		}
	}
	else
	{
		// Message failure
		message_confirmation_success = false;
	}

	confirm_reception_mcp2515(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_canspi::read_memory_procedure(firmware_page& current_firmware_page)
{
	// Store the 16bit page number.
	current_firmware_page.page = ((static_cast<uint32_t>(reception_message.message[0])) << 24) |
				     ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
				     ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
				     (static_cast<uint32_t>(reception_message.message[3]));
	
	// Store the 16bit code_length.
	current_firmware_page.code_length = (reception_message.message[4] << 8) | (reception_message.message[5]);

	// Check for errors in message details
	if (current_firmware_page.code_length > SPM_PAGESIZE || current_firmware_page.page >= BOOTLOADER_START_ADDRESS)//TODO - import the value from TC
	{
		// Message failure
		message_confirmation_success = false;
	}
	else
	{
		// Message success
		current_firmware_page.ready_to_read = true;
		ready_to_send_page = true;// Allow sending the flash page once it is read
	}
	
	confirm_reception_mcp2515(message_confirmation_success);
	
	// All done.
	return;
}

void bootloader_module_canspi::send_flash_page(firmware_page& current_firmware_page)
{
	transmission_message.message_type = READ_DATA;
	current_firmware_page.current_byte = 0; // Start at the start of buffer.
	reception_message.confirmed_send = false; // Require confirmation after every flash page sent
	while (current_firmware_page.current_byte < current_firmware_page.code_length)
	{
		// Determine the length of message, just in case we are closer than 8 bytes and need to send a smaller message.
		transmission_message.dlc = (current_firmware_page.code_length - current_firmware_page.current_byte);
		if (transmission_message.dlc > 8) // Limit to 8 byte messages.
		{
			transmission_message.dlc = 8;
		}

		// Create message.
		for (uint8_t i = 0; i < transmission_message.dlc; i++)
		{
			transmission_message.message[i] = current_firmware_page.data[current_firmware_page.current_byte + i];
		}

		// Increment the current_byte for next loop.
		current_firmware_page.current_byte += transmission_message.dlc;		
		
		// Send the message.
		transmit_CAN_message(transmission_message);
		
		// Wait for confirmation message to return from host.
		while(!reception_message.confirmed_send && !reception_message.message_received)	
		{
			// Do nothing.
		}
		
		// Allow the host to stop the the reading if it sees a message is lost. Host must send another message to the bootloader.
		if (reception_message.message_received)
		{
			// Abort sending the page.
			break;
		}

		reception_message.confirmed_send = false;
	}

	// All done.
	return;
}

void bootloader_module_canspi::filter_message(firmware_page& current_firmware_page)
{
	if (reception_message.message_type == RESET_REQUEST)
	{
		reset_request_procedure();

		// TODO - The above function will never return, because it results in a CPU reset.  Is that what you wanted?

		// We will never reach here.
	}	

	else if (reception_message.message_type == GET_INFO)
	{
		get_info_procedure();
		reception_message.message_received = false;
	}

	else if (reception_message.message_type == WRITE_MEMORY)
	{
		write_memory_procedure(current_firmware_page);
		reception_message.message_received = false;
	}

	else if (reception_message.message_type == WRITE_DATA)
	{
		write_data_procedure(current_firmware_page);
		reception_message.message_received = false;
	}

	else if(reception_message.message_type == READ_MEMORY)
	{
		read_memory_procedure(current_firmware_page);
		reception_message.message_received = false;
	}

	// All done.
	return;
}

void bootloader_module_canspi::alert_uploader(void)
{
	transmission_message.dlc = 8;
	transmission_message.message_type = ALERT_UPLOADER;
	for(uint8_t i = 0; i < transmission_message.dlc; i++)
	{
		transmission_message.message[i] = 0xFF; // No significance.
	}
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// Interupt service routine for the INT pin from mcp2515
// Evaluates the CAN message received.
ISR(PCINT2_vect)
{
	// Check that the pin change was from the pin K0
	if(module.pin_K0_state != (PINK & (1<<PIN0)))
	{
		// Record new state.
		module.pin_K0_state = (PINK & (1<<PIN0));
		
		//Only carries out ISR if pin on a falling edge - since the INT pin from mcp2515 drives low on interupt
		if(module.pin_K0_state != 0)
		{
			uint8_t node_id;
			node_id = mcp2515_read_rx_buffer(0, module.reception_message);
		
			// Check node ID, if not the same exit ISR.
			if(node_id == NODE_ID)
			{
				// A confirmation message received.
				if (module.reception_message.message_type == module.READ_DATA)
				{
					module.reception_message.confirmed_send = true;
				}
				// A host command message received.
				else
				{
					// Tell Boot loader that the message was received.
					module.reception_message.message_received = true;
					
					//Default the message confirmation to successful
					module.message_confirmation_success = true;
				}
			}
		}
	}
	mcp2515_modify_bits(MCP_CANINTF, 0x01, 0x00);// Reset the reception interupt flag
}
	
// ALL DONE.
