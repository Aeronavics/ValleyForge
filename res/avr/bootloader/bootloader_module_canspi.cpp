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

// Include can message ids.
#include "can_messages.hpp"

	// Delay used for reseting the mcp2515 .
#define F_CPU 16000000UL  // 16 MHz crystal oscillator on the mcp2515.
#include <util/delay.h>

// DEFINE CONSTANTS

	// MCP2515 interfacing.
#define PIN_CHANGE_INTERUPT_VECTOR				<<<TC_INSERTS_INT_VECTOR_HERE>>>
#define PIN_CHANGE_INTERRUPT_CONFIG_NUMBER		<<<TC_INSERTS_INT_VECTOR_CONFIG_NUMBER_HERE>>>
#define PIN_CHANGE_INTERRUPT_NUMBER 			<<<TC_INSERTS_INT_NUMBER_HERE>>>

#define PCMSK_ADDRESS_OFFSET 					0x6B
#define PIN_CHANGE_INTERRUPT_MASK_REGISTER 		_SFR_MEM8(PCMSK_ADDRESS_OFFSET + PIN_CHANGE_INTERRUPT_CONFIG_NUMBER)

#define PORT_MULTIPLIER		3
enum port_offset {P_READ, P_MODE, P_WRITE};
enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14}; 
 
#define SS_PORT_NUM  			<<<TC_INSERTS_SS_PORT_HERE>>>
#define SS_PIN_NUM  			<<<TC_INSERTS_SS_PIN_HERE>>>
#define SCK_PORT_NUM 			<<<TC_INSERTS_SCK_PORT_HERE>>>
#define SCK_PIN_NUM  			<<<TC_INSERTS_SCK_PIN_HERE>>>
#define MOSI_PORT_NUM  			<<<TC_INSERTS_MOSI_PORT_HERE>>>
#define MOSI_PIN_NUM  			<<<TC_INSERTS_MOSI_PIN_HERE>>>
#define INT_MCP2515_PORT_NUM  	<<<TC_INSERTS_INT_PORT_HERE>>>
#define INT_MCP2515_PIN_NUM  	<<<TC_INSERTS_INT_PIN_HERE>>>

#define SS_READ		_SFR_IO8((SS_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define SS_WRITE	_SFR_IO8((SS_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define SS_MODE		_SFR_IO8((SS_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define SS_PIN		( 1 << SS_PIN_NUM )

#define SCK_READ	_SFR_IO8((SCK_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define SCK_WRITE	_SFR_IO8((SCK_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define SCK_MODE	_SFR_IO8((SCK_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define SCK_PIN		( 1 << SCK_PIN_NUM )

#define MOSI_READ		_SFR_IO8((MOSI_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define MOSI_WRITE		_SFR_IO8((MOSI_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define MOSI_MODE		_SFR_IO8((MOSI_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define MOSI_PIN		( 1 << MOSI_PIN_NUM )

	// Different definitions in the avr library (_SFR_IO8 & _SFR_MEM8).
#if (INT_MCP2515_PORT_NUM < PORT_H)
	#define INT_MCP2515_READ		_SFR_IO8((INT_MCP2515_PORT_NUM * PORT_MULTIPLIER) + P_READ)
	#define INT_MCP2515_WRITE		_SFR_IO8((INT_MCP2515_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
	#define INT_MCP2515_MODE		_SFR_IO8((INT_MCP2515_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#else
	#define PORT_H_ADDRESS_OFFSET 0x100
	#define INT_MCP2515_READ		_SFR_MEM8(((INT_MCP2515_PORT_NUM - PORT_H) * PORT_MULTIPLIER) + PORT_H_ADDRESS_OFFSET + P_READ)
	#define INT_MCP2515_WRITE		_SFR_MEM8(((INT_MCP2515_PORT_NUM - PORT_H) * PORT_MULTIPLIER) + PORT_H_ADDRESS_OFFSET + P_WRITE)
	#define INT_MCP2515_MODE		_SFR_MEM8(((INT_MCP2515_PORT_NUM - PORT_H) * PORT_MULTIPLIER) + PORT_H_ADDRESS_OFFSET + P_MODE)
#endif

#define INT_MCP2515_PIN		( 1 << INT_MCP2515_PIN_NUM )


	// Bootloader information.
#define BOOTLOADER_START_ADDRESS	<<<TC_INSERTS_BOOTLOADER_START_ADDRESS_HERE>>>
const uint8_t ALERT_UPLOADER_PERIOD = 10;// x10 the event_periodic() period. Period to send each alert_host message before communication has begun.
const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;

	//CAN BIT TIMING.
#define CAN_BAUD_RATE	<<<TC_INSERTS_CAN_BAUD_RATES_HERE>>>
#if (CAN_BAUD_RATE == 1000)
	// 16MHz crystal, 1Mbps baud rate, 75% sampling rate, TQ = 0.125us.
	
	// Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1.
	#define CAN_SJW 0

	// Prescalar = 2 BRP = (Fosc*TQ)/2 - 1.
	#define  CAN_BRP  0

	// Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1.
	#define CAN_PS1 2

	// Propagation delay = 2. PRSEG2 = Propagation delay - 1.
	#define CAN_PRS 1

	// Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1.
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 500)
	// 16MHz crystal, 500kbps baud rate, 75% sampling rate, TQ = 0.25us.

	// Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1.
	#define CAN_SJW 0

	// Prescalar = 4. BRP = (Fosc*TQ)/2 - 1.
	#define  CAN_BRP  1

	// Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1.
	#define CAN_PS1 2

	// Propagation delay = 2. PRSEG2 = Propagation delay - 1.
	#define CAN_PRS 1

	// Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1.
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 250)
	// 16MHz crystal, 250kbps baud rate, 75% sampling rate, TQ = 0.5us.

	// Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1.
	#define CAN_SJW 0

	// Prescalar = 8. BRP = (Fosc*TQ)/2 - 1.
	#define  CAN_BRP  3

	// Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1.
	#define CAN_PS1 2

	// Propagation delay = 2. PRSEG2 = Propagation delay - 1.
	#define CAN_PRS 1

	// Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1.
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 200)
	// 16MHz crystal, 200kbps baud rate, 75% sampling rate, TQ = 0.625us.

	// Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1.
	#define CAN_SJW 0

	// Prescalar = 10. BRP = (Fosc*TQ)/2 - 1.
	#define  CAN_BRP  4

	// Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1.
	#define CAN_PS1 2

	// Propagation delay = 2. PRSEG2 = Propagation delay - 1.
	#define CAN_PRS 1

	// Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1.
	#define CAN_PS2 1
	
#elif (CAN_BAUD_RATE == 125)
	// 16MHz crystal, 125kbps baud rate, 75% sampling rate, TQ = 1us.

	// Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1.
	#define CAN_SJW 0

	// Prescalar = 16. BRP = (Fosc*TQ)/2 - 1.
	#define  CAN_BRP  7

	// Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1.
	#define CAN_PS1 2

	// Propagation delay = 2. PRSEG2 = Propagation delay - 1.
	#define CAN_PRS 1

	// Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1.
	#define CAN_PS2 1

#elif (CAN_BAUD_RATE == 100)
	// 16MHz crystal, 100kbps baud rate, 75% sampling rate, TQ = 1.25us.

	// Synchronization Jump Width = 1TQ. SJW = Synchronization Jump Width - 1.
	#define CAN_SJW 0

	// Prescalar = 20. BRP = (Fosc*TQ)/2 - 1.
	#define  CAN_BRP  9

	// Phase segment_1 = 3. PHSEG1 =  Phase segment_1 - 1.
	#define CAN_PS1 2

	// Propagation delay = 2. PRSEG2 = Propagation delay - 1.
	#define CAN_PRS 1

	// Phase segment_2 = 2. PHSEG2 =  Phase segment_2 - 1.
	#define CAN_PS2 1

#endif

	// Mcp2515 registers.
#define MCP_RXF0SIDH	0x00 
#define MCP_RXF0SIDL	0x01 
#define MCP_RXF0EID8	0x02 
#define MCP_RXF0EID0	0x03 
#define MCP_RXF1SIDH	0x04 
#define MCP_RXF1SIDL	0x05 
#define MCP_RXF1EID8	0x06 
#define MCP_RXF1EID0	0x07 
#define MCP_RXF2SIDH	0x08 
#define MCP_RXF2SIDL	0x09 
#define MCP_RXF2EID8	0x0A 
#define MCP_RXF2EID0	0x0B 
#define MCP_BFPCTRL		0x0C 
#define MCP_TXRTSCTRL	0x0D 
#define MCP_CANSTAT		0x0E 
#define MCP_CANCTRL		0x0F 
#define MCP_RXF3SIDH	0x10 
#define MCP_RXF3SIDL	0x11 
#define MCP_RXF3EID8	0x12 
#define MCP_RXF3EID0	0x13 
#define MCP_RXF4SIDH	0x14 
#define MCP_RXF4SIDL	0x15 
#define MCP_RXF4EID8	0x16 
#define MCP_RXF4EID0	0x17 
#define MCP_RXF5SIDH	0x18 
#define MCP_RXF5SIDL	0x19 
#define MCP_RXF5EID8	0x1A 
#define MCP_RXF5EID0	0x1B 
#define MCP_TEC			0x1C 
#define MCP_REC			0x1D 
#define MCP_RXM0SIDH	0x20 
#define MCP_RXM0SIDL	0x21 
#define MCP_RXM0EID8	0x22 
#define MCP_RXM0EID0	0x23 
#define MCP_RXM1SIDH	0x24 
#define MCP_RXM1SIDL	0x25 
#define MCP_RXM1EID8	0x26 
#define MCP_RXM1EID0	0x27 
#define MCP_CNF3		0x28 
#define MCP_CNF2		0x29 
#define MCP_CNF1		0x2A 
#define MCP_CANINTE		0x2B 
#define MCP_CANINTF		0x2C 
#define MCP_EFLG		0x2D 
#define MCP_TXB0CTRL	0x30 
#define MCP_TXB1CTRL	0x40 
#define MCP_TXB2CTRL	0x50 
#define MCP_RXB0CTRL	0x60 
#define MCP_RXB0SIDH	0x61 
#define MCP_RXB1CTRL	0x70 
#define MCP_RXB1SIDH	0x71 
 
	// Mcp2515 instructions.
#define MCP_WRITE		0x02 
#define MCP_READ		0x03 
#define MCP_BITMOD		0x05 
#define MCP_RESET		0xC0 
#define MCP_LOAD_TX0	0x40 // Load transmit buffer(from the TXBnSIDH).
#define MCP_RTS_TX0		0x81 // Request to send.
#define MCP_READ_RX0	0x90 // Read receive buffer(from the RXBnSIDH register).
#define MCP_READ_STATUS	0xA0 

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

	// State flags
bool communication_started;
bool ready_to_send_page;
bool message_confirmation_success; 
bool write_details_stored;
volatile uint8_t pin_int_mcp2515_state; // State of the INT pin from mcp2515, updated by PIN_CHANGE_INTERUPT_VECTOR.

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
 *	Sends a message on the CAN network.
 *
 *	NOTE - Message details are defined in the tranmission_message object.
 *
 *	TAKES:		transmission_message		object containing the message identifier, DLC and data to send.
 *
 *	RETURNS:	Nothing.
 */
void transmit_CAN_message(bootloader_module_canspi::Message_info& tranmission_message);

/**
 *	Sends a confirmation message to the uploader.
 * 
 *	NOTE - The message contains one byte informing the uploader whether the message received 
 * 			was valid(1) or invalid(0).
 *
 *	TAKES:		confirmation_successful		the validity of the previously received message
 *
 *	RETURNS:	Nothing.
 */
void confirm_reception_mcp2515(bool confirmation_successful);

/**
 *	Resets the mcp2515 to default settings.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void reset_mcp2515();

/**
 *	Initializes the spi communication with mcp2515.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void init_spi(void);

/**
 *	Shifts out and receives 1 byte in spi communication.
 *
 *	TAKES:		data		information to be shifted out.
 *
 *	RETURNS:	1 byte of information received during the shift.
 */
uint8_t read_write_spi(uint8_t data);

/**
 *	Receives 1 byte in spi communication.
 *
 *	NOTE - A meaningless byte is sent in order to shift in data.
 * 
 *	TAKES:		Nothing.
 *
 *	RETURNS:	1 byte of information received during the communication.
 */
uint8_t just_read_spi(void);

/**
 *	Shifts out 1 byte in spi communication.
 *
 *	TAKES:		data		information to be shifted out.
 *
 *	RETURNS:	Nothing.
 */
void just_write_spi(uint8_t data);

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

/**
 *	Overwrites a registers in mcp2515.
 *
 *	TAKES:		address		register address in mcp2515
 * 				data		register value to write	
 *
 *	RETURNS:	Nothing
 */
void write_register_mcp2515(uint8_t address, uint8_t data);

/**
 *	Reads a register in mcp2515.
 *
 *	TAKES:		address		register address in mcp2515
 *
 *	RETURNS:	current register value
 */
uint8_t read_register_mcp2515(uint8_t address);

/**
 *	Modifies bits in a register.
 *
 *	TAKES:		address		register address in mcp2515
 * 				data		register value to write (before masking)
 * 				mask		mask that determines which bits are modified
 * 
 *	RETURNS:	Nothing
 */
void modify_bits_mcp2515(uint8_t address, uint8_t mask, uint8_t data);

/**
 *	Requests mcp2515 to send the tranmission buffer.
 *
 *	TAKES:		Nothing
 * 
 *	RETURNS:	Nothing
 */
void request_to_send_mcp2515(void);

/**
 *	Retreves CAN received message information from mcp2515.
 *
 *	TAKES:		reception_message		object which the id,dlc,data will be stored.
 * 
 *	RETURNS:	The node identifier from the received message.
 */
uint8_t read_rx_buffer_mcp2515(volatile bootloader_module_canspi::Message_info& reception_message);

/**
 *	Loads information into tranmission buffer in mcp2515.
 *
 *	TAKES:		transmission_message		object containing the id,dlc,data to send.
 * 
 *	RETURNS:	Nothing
 */
void load_tx_buffer_mcp2515(bootloader_module_canspi::Message_info& tranmission_message);

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
uint8_t read_status_mcp2515(void);

/**
 *	Inilialize CAN communication on mcp2515
 *
 *	TAKES:		Nothing
 * 
 *	RETURNS:	Nothing
 */
void init_CAN_mcp2515(void);


// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_canspi::~bootloader_module_canspi()
{
	// All done.
	return;
}

void bootloader_module_canspi::init(void)
{
	// Initialize flags.
	communication_started = false;
	ready_to_send_page = false;
	write_details_stored = false;
	reception_message.message_received = false;
	
	// Initialize the external CAN controller.
	init_mcp2515();
	
	// All done.
	return;
}

void bootloader_module_canspi::exit(void)
{
	init_spi();
	
	reset_mcp2515();
	
	// Reset spi peripheral to intial startup values.
	SS_MODE &= ~SS_PIN;
	SCK_MODE &= ~SCK_PIN;
	MOSI_MODE &= ~MOSI_PIN;
	SPCR = 0x00;
	
	// Reset interrupt pin.
	PIN_CHANGE_INTERRUPT_MASK_REGISTER &= ~(1 << PIN_CHANGE_INTERRUPT_NUMBER);
	PCICR &= ~(1 << PIN_CHANGE_INTERRUPT_CONFIG_NUMBER);

	// All done.
	return;
}

void bootloader_module_canspi::event_idle()
{
	// Send the buffer once the flash page has been copied to it.
	if (!buffer.ready_to_read && ready_to_send_page)
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
		// Check if communication with host has already occured.
		if (!communication_started)
		{
			alert_count++;
			if (alert_count == ALERT_UPLOADER_PERIOD)
			{
				// Send message to host to uploader that bootloader is awaiting messages.
				alert_uploader();
				alert_count = 0;
			}
		}
	}
	else
	{
		communication_started = true;
		
		filter_message(buffer);

		// Restart the bootloader timeout.
		set_bootloader_timeout(false);
		set_bootloader_timeout(true);
	}

	// All done.
	return;
}

void get_bootloader_module_information(Shared_bootloader_module_constants* bootloader_module_information)
{
	bootloader_module_information->node_id = NODE_ID;
	bootloader_module_information->baud_rate = CAN_BAUD_RATE;
	
	// All done.
	return;
}
	// Avoids name mangling for the shared jumptable.
extern "C" void get_bootloader_module_information_BL(Shared_bootloader_module_constants* arg){
	get_bootloader_module_information(arg);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void confirm_reception_mcp2515(bool confirmation_successful)
{
	module.transmission_message.dlc = 1;

	// Reply to the uploader whether the received message was successful or not.
	if (confirmation_successful)
	{
		module.transmission_message.message[0] = 1;
	}
	else
	{
		module.transmission_message.message[0] = 0;
	}
	
	// Confirmation message will have the same ID as the message it is confirming.
	module.transmission_message.message_type = module.reception_message.message_type;
	
	transmit_CAN_message(module.transmission_message);

	// All done.
	return;
}

void init_mcp2515(void)
{
	// Set up pin change interupt, this will be used for interupt from INT pin of mcp2515.
	PIN_CHANGE_INTERRUPT_MASK_REGISTER |= (1 << PIN_CHANGE_INTERRUPT_NUMBER);
	PCICR |= (1 << PIN_CHANGE_INTERRUPT_CONFIG_NUMBER);
	INT_MCP2515_MODE &= ~INT_MCP2515_PIN; // Input for INT pin.
	pin_int_mcp2515_state = (INT_MCP2515_READ & INT_MCP2515_PIN);// Get intial state of pin.
	 
	// Initialize spi communication.
	init_spi();
	
	// Initialize CAN communication.
	init_CAN_mcp2515();
	
	// All done.
	return;
}

void transmit_CAN_message(bootloader_module_canspi::Message_info& tranmission_message)
{
	load_tx_buffer_mcp2515(tranmission_message);
	request_to_send_mcp2515();
	
	// Wait until the tranmission is complete.
	uint8_t status_register, control_register;
	status_register = read_status_mcp2515();
	while (!(status_register & (0x08)))// If transmission finished, this flag is set then exit.
	{
		status_register = read_status_mcp2515();
		
		// Check for error conditions.
		control_register = read_register_mcp2515(MCP_TXB0CTRL);
		if (control_register & 0x10)// Transmission error occured.
		{
			// Exit transmission if error occurs.
			break;
		}
	}
	modify_bits_mcp2515(MCP_CANINTF, 0x04, 0x00);// Reset the tranmission finished flag. 
	
	// All done.
	return;
}

void reset_mcp2515()
{
	// Execute instruction.
	select_slave();
	just_write_spi(MCP_RESET);
	deselect_slave();
	
	// Wait 128 cycles to allow oscillator to stabilize.
	_delay_us(8);// Equivalent to 128 clock cycles at 16MHz.
	
	// All done.
	return;
}

void init_spi(void)
{
	// Outputs set for MOSI,SCK,SS.
	SS_MODE |= SS_PIN;
	MOSI_MODE |= MOSI_PIN;
	SCK_MODE |= SCK_PIN;
	
	// Enable spi as master with sck = fclk/4.
	SPCR |= (1<<SPE) | (1<<MSTR);

	// All done.
	return;
}

uint8_t read_write_spi(uint8_t data)   
{   
	// Set data to send into SPI data register.
	SPDR = data;   
	
	// Wait for transmission complete.
	while (!(SPSR & (1<<SPIF)));
	
	// return data from SPI shift register.
	return SPDR;
}

uint8_t just_read_spi(void)
{
	return read_write_spi(0x00);// Meaningless write but return the read.
}

void just_write_spi(uint8_t data)
{
	read_write_spi(data);
	
	// All done.
	return;
}

void select_slave(void)
{
	SS_WRITE &= ~SS_PIN;// Drive cs low. 
	
	// All done.
	return;
}

void deselect_slave(void)
{
	SS_WRITE |= SS_PIN;// Drive cs high.
	
	// All done.
	return;
}

void write_register_mcp2515(uint8_t address, uint8_t data)
{
	// Execute instruction.
	select_slave();
	just_write_spi(MCP_WRITE);
	just_write_spi(address);
	just_write_spi(data);
	deselect_slave();
	
	// All done.
	return;
}

uint8_t read_register_mcp2515(uint8_t address)
{
	uint8_t read_data;
	
	// Execute instruction.
	select_slave();
	just_write_spi(MCP_READ);
	just_write_spi(address);
	read_data = just_read_spi();
	deselect_slave();
	
	return read_data;
}

void modify_bits_mcp2515(uint8_t address, uint8_t mask, uint8_t data)
{
	// Execute instruction.
	select_slave();
	just_write_spi(MCP_BITMOD);
	just_write_spi(address);
	just_write_spi(mask);
	just_write_spi(data);
	deselect_slave();
	
	// All done.
	return;
}

void request_to_send_mcp2515(void)
{
	// Select transmission buffer 0.
	uint8_t instruction = MCP_RTS_TX0;
	
	// Execute instruction.
	select_slave();
	just_write_spi(instruction);
	deselect_slave();
	
	// All done.
	return;
}

uint8_t read_rx_buffer_mcp2515(volatile bootloader_module_canspi::Message_info& reception_message)
{
	uint8_t temp_buffer[11];
	
	// Select the reception buffer 0.
	uint8_t instruction = MCP_READ_RX0;
	
	// Execute instruction.
	select_slave();
	just_write_spi(instruction);
	temp_buffer[0] = just_read_spi();// Save RXBnSIDH.
	temp_buffer[1] = just_read_spi();// Save RXBnSIDL.
	just_read_spi();// Don't save RXBnEID8.
	just_read_spi();// Don't save RXBnEID0.
	temp_buffer[2] = just_read_spi();// Save RXBnDLC.
	temp_buffer[3] = just_read_spi();// Save the NODE_ID from RXBnD0.
	for (uint8_t i = 4; i < 11; i++)// Save RXBnD1 to RXBnD7.
	{
		temp_buffer[i] = just_read_spi();
	}
	deselect_slave();
	
	// Extract information from the buffer.
	reception_message.message_type = ((static_cast<uint16_t>(temp_buffer[0])) << 3) |
									 ((static_cast<uint16_t>(temp_buffer[1])) >> 5);
									 
	reception_message.dlc = (temp_buffer[2] & (0x0F)) - 1;// Minus 1 as the first byte was taken up by the node ID.
	if (reception_message.dlc > 7)
	{
		reception_message.dlc = 7; // This check is required as CAN controller may give greater than 8 dlc value.
	}
	
	for (uint8_t i = 0; i < reception_message.dlc; i++)
	{
		reception_message.message[i] = temp_buffer[i + 4];
	}
	
	return temp_buffer[3];// Return the node id.
}

void load_tx_buffer_mcp2515(bootloader_module_canspi::Message_info& tranmission_message)
{
	uint8_t temp_buffer[11];
	
	// Select the transmission buffer 0.
	uint8_t instruction = MCP_LOAD_TX0;

	// Input information into buffer.
	temp_buffer[0] = tranmission_message.message_type >> 3;
	temp_buffer[1] = tranmission_message.message_type << 5;
	temp_buffer[2] = tranmission_message.dlc;
	for (uint8_t i = 0; i < tranmission_message.dlc; i++)
	{
		 temp_buffer[i + 3] = tranmission_message.message[i];
	}
	
	// Execute instruction
	select_slave();
	just_write_spi(instruction);
	just_write_spi(temp_buffer[0]);// Set TXBnSIDH.
	just_write_spi(temp_buffer[1]);// Set TXBnSIDL.
	just_write_spi(0x00);// Set TXBnEID8.
	just_write_spi(0x00);// Set TXBnEID0.
	just_write_spi(temp_buffer[2]);// Set TXBnDLC.
	for (uint8_t i = 3; i < (tranmission_message.dlc + 3); i++)// Set TXBnD0 to TXBnD7 - or exit if less.
	{
		just_write_spi(temp_buffer[i]);
	}
	deselect_slave();
	
	// All done.
	return;
}

uint8_t read_status_mcp2515(void)
{
	uint8_t status;
	
	// Execute instruction.
	select_slave();
	just_write_spi(MCP_READ_STATUS);
	status = just_read_spi();
	deselect_slave();
	
	return status;
}

void init_CAN_mcp2515(void)
{
	uint8_t current_mode;
	
	// Reset mcp2515.
	reset_mcp2515();
	
	// Configuration mode set.
	modify_bits_mcp2515(MCP_CANCTRL, 0xE0, 0x80);
	
	// Wait until the mode is configuration mode.
	current_mode = read_register_mcp2515(MCP_CANSTAT);
	while ((current_mode & 0xE0) != 0x80)
	{
		current_mode = read_register_mcp2515(MCP_CANSTAT);
		// Do nothing
	}
	
	// Setup CAN bit timing.
	uint8_t cnfg1, cnfg2, cnfg3;
	
	cnfg1 = (CAN_SJW << 6) | (CAN_BRP);
	cnfg2 = (0x80) | (CAN_PS1 << 3) | (CAN_PRS);// 0x80-allows setting of PHSEG2 in cnfg3.
	cnfg3 = (CAN_PS2);
	
	write_register_mcp2515(MCP_CNF1, cnfg1);
	write_register_mcp2515(MCP_CNF2, cnfg2);
	write_register_mcp2515(MCP_CNF3, cnfg3);
	
	
	// Set up masks and filters.
	uint16_t id = BASE_ID;
	
	write_register_mcp2515(MCP_RXF0SIDH, (id >> 3));// Load into RXB0.
	write_register_mcp2515(MCP_RXF0SIDL, (id << 5));
	write_register_mcp2515(MCP_RXM0SIDH, 0xFE);// Allow partial filtering.
	write_register_mcp2515(MCP_RXM0SIDL, 0x00);

	// Set up buffer.
	write_register_mcp2515(MCP_RXB0CTRL, 0x20);// Accept messages that fit filter critera and are standard CAN format.
	
	// Set up interupt.
	write_register_mcp2515(MCP_CANINTE, 0x01);// Set interupt for reception buffer 0
	
	// Enable CAN communication.
	write_register_mcp2515(MCP_CANCTRL, 0x00);// Set to normal mode.
	
	// Wait until the mode is normal mode.
	current_mode = read_register_mcp2515(MCP_CANSTAT);
	while ((current_mode & 0xE0) != 0x00)
	{
		current_mode = read_register_mcp2515(MCP_CANSTAT);
		// Do nothing.
	}

	// All done.
	return;
}


// IMPLEMENT PRIVATE CLASS FUNCTIONS.

void bootloader_module_canspi::request_reset_procedure()
{
	confirm_reception_mcp2515(message_confirmation_success);// Always successful.
	
	if (reception_message.message[0] == 0)
	{
		reboot_to_bootloader();

		// We will never reach here.
	}
	else
	{
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
	
	// Insert Device signaure.
	uint8_t device_signature[4];
	get_device_signature(device_signature);
	
	transmission_message.message[0] = device_signature[0];
	transmission_message.message[1] = device_signature[1];
	transmission_message.message[2] = device_signature[2];
	transmission_message.message[3] = device_signature[3];
	
	// Insert bootloader version.
	uint16_t bootloader_version = get_bootloader_version();
	
	transmission_message.message[4] = static_cast<uint8_t>(bootloader_version >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(bootloader_version);
	
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

void bootloader_module_canspi::write_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32 bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
								 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
								 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
								 (static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
										(static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details.
	if ((current_firmware_page.code_length > SPM_PAGESIZE) || (current_firmware_page.page >= BOOTLOADER_START_ADDRESS))
	{
		// Message failure.
		message_confirmation_success = false;
		write_details_stored = false;
	}
	else
	{
		// Message success.
		write_details_stored = true;
		current_firmware_page.current_byte = 0;
	}
	
	confirm_reception_mcp2515(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_canspi::write_data_procedure(Firmware_page& current_firmware_page)
{
	// Only wrtie to buffer if a memory address and length have been provided.
	if(write_details_stored)
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
			write_details_stored = false;
		}
	}
	else
	{
		// Message failure.
		message_confirmation_success = false;
	}

	confirm_reception_mcp2515(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_canspi::read_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32 bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
								 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
								 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
								 (static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
										(static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details.
	if ((current_firmware_page.code_length > SPM_PAGESIZE) || (current_firmware_page.page >= BOOTLOADER_START_ADDRESS))
	{
		// Message failure.
		message_confirmation_success = false;
	}
	else
	{
		// Message success.
		current_firmware_page.ready_to_read = true;
		ready_to_send_page = true; // Allow sending the flash page once it is read.
	}
	
	confirm_reception_mcp2515(message_confirmation_success);
	
	// All done.
	return;
}

void bootloader_module_canspi::send_flash_page(Firmware_page& current_firmware_page)
{
	transmission_message.message_type = READ_DATA;
	current_firmware_page.current_byte = 0;
	reception_message.confirmed_send = false; 
	
	// Send the flash page in 8 byte messages, confirmation message must be received from uploader after each message.
	while (current_firmware_page.current_byte < current_firmware_page.code_length)
	{
		// Determine the length of message, just in case we are closer than 8 bytes and need to send a smaller message.
		transmission_message.dlc = (current_firmware_page.code_length - current_firmware_page.current_byte);
		if (transmission_message.dlc > 8)
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

		transmit_CAN_message(transmission_message);
		
		// Wait for confirmation message to return from uploader or a uploader command message.
		while (!reception_message.confirmed_send && !reception_message.message_received)	
		{
			// Do nothing.
		}
		
		// Exits the sending of the flash page if a uploader command message is received.
		// Allows the host to stop the reading if it sees a message is lost.
		if (reception_message.message_received)
		{
			// Abort sending the flash page.
			break;
		}
		reception_message.confirmed_send = false;
	}

	// All done.
	return;
}

void bootloader_module_canspi::filter_message(Firmware_page& current_firmware_page)
{
	// Determine the corresponding procedure for the received message.
	switch (reception_message.message_type)
	{
		case REQUEST_RESET:
			request_reset_procedure();
			break;
			// We will never reach here.

		case GET_INFO:
			get_info_procedure();
			reception_message.message_received = false;
			break;
			
		case WRITE_MEMORY:
			write_memory_procedure(current_firmware_page);
			reception_message.message_received = false;
			break;

		case WRITE_DATA:
			write_data_procedure(current_firmware_page);
			reception_message.message_received = false;
			break;

		case READ_MEMORY:
			read_memory_procedure(current_firmware_page);
			reception_message.message_received = false;
			break;
			
	}

	// All done.
	return;
}

void bootloader_module_canspi::alert_uploader(void)
{
	transmission_message.dlc = 8;
	transmission_message.message_type = HOST_ALERT;
	for (uint8_t i = 0; i < transmission_message.dlc; i++)
	{
		transmission_message.message[i] = 0xFF; // No significance.
	}
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

/**
 * ISR for for the interupt from INT pin from mcp2515.
 * NOTE - procedure only executed on falling edge of the INT pin.
 * This routine only operates on received messages, it reads the ID, DLC and data from the CAN controller into a Message_info object.
 * The ISR also sets a flag to tell Boot loader that a new message has been received, or that a confirmation message has been received.
 */
ISR(PIN_CHANGE_INTERUPT_VECTOR)
{
	// Check that the pin change was from the INT pin.
	if (pin_int_mcp2515_state != (INT_MCP2515_READ & INT_MCP2515_PIN))
	{
		// Record new state.
		pin_int_mcp2515_state = (INT_MCP2515_READ & INT_MCP2515_PIN);
		
		// Only carries out ISR if pin on a falling edge - since the INT pin from mcp2515 drives low on interupt.
		if (pin_int_mcp2515_state != 0)
		{
			uint8_t node_id;
			node_id = read_rx_buffer_mcp2515(module.reception_message);
		
			// Check node ID, if not the same exit ISR.
			if (node_id == NODE_ID)
			{
				// A confirmation message received.
				if (module.reception_message.message_type == READ_DATA)
				{
					module.reception_message.confirmed_send = true;
				}
				// A uploader command message received.
				else
				{
					// Tell Bootloader that the message was received.
					module.reception_message.message_received = true;
					
					//Default the message confirmation to successful.
					message_confirmation_success = true;
				}
			}
		}
	}
	modify_bits_mcp2515(MCP_CANINTF, 0x01, 0x00);// Reset the reception interupt flag.
}
	
// ALL DONE.
