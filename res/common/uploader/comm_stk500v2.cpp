// Copyright (C) 2012  Unison Networks Ltd
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
 *  FILE: 		comm_stk500v2.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Comm Modules
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	27-11-2012
 *
 *	Implementation of the stk500v2 communications protocol.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "comm_stk500v2.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <iostream>

#include <errno.h>
#include <fcntl.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>

#include "command.h"

// DEFINE PRIVATE MACROS.

#define MAX_RETRIES 5
#define TIMEOUT 10

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

static STK500v2_module module;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

speed_t get_speed(unsigned long speed);
bool set_cts_dtr(int fd, bool on);
bool serial_drain(int fd);
bool serial_send(int fd, uint8_t* buf, size_t buf_len);
bool serial_recv(int fd, uint8_t* buf, size_t buf_len, size_t& bytes_read);


// IMPLEMENT PUBLIC FUNCTIONS.

STK500v2_module::STK500v2_module() :
	Comm_module("stk500v2")
{
	//Nothing to do here.
}

STK500v2_module::~STK500v2_module()
{
	close_serial();
}

bool STK500v2_module::init(Params params)
{
	bool have_tty = false;
	bool have_speed = false;
	std::string speed_str;
	if (params.find("tty") != params.end())
	{
		tty_path = params["tty"];
		have_tty = true;
	}
	if (params.find("speed") != params.end())
	{
		speed_str = params["speed"];
		have_speed = true;
	}
	
	if (! have_tty)
	{
		return false;
	}
	if (! have_speed)
	{
		speed = 115200;
	}
	else
	{
		speed = strtoul(speed_str.c_str(),NULL,10);
	}
	stk500_seq_no = 0;
	connected = false;
	if (!open_serial())
	{
		return false;
	}
	if (!setup_serial())
	{
		return false;
	}
	return reset_device(false);
}

bool STK500v2_module::connect_to_device()
{
	connected = stk500_sync();
	
	if (connected)
	{
		return true;
	}
	
	return false;
}

bool STK500v2_module::get_device_info( Device_info& info)
{
	//Maximum message length for stk500 buffer.
	uint8_t buffer[275];
	size_t reply_length;
	
	buffer[0] = CMD_READ_SIGNATURE_ISP;
	buffer[4] = 0;
	reply_length = 275;
	if (!stk500_cmd(buffer, 5, reply_length) || reply_length < 4)
	{
		return false;
	}
	signature0 = buffer[2];
	buffer[4] = 1;
	reply_length = 275;
	if (!stk500_cmd(buffer, 5, reply_length) || reply_length < 4)
	{
		return false;
	}
	signature1 = buffer[2];
	buffer[4] = 2;
	reply_length = 275;
	if (!stk500_cmd(buffer, 5, reply_length) || reply_length < 4)
	{
		return false;
	}
	signature2 = buffer[2];
	
	signature = signature0 << 16 | signature1 << 8 | signature2;
	
	info.set_name(prog_name);
	info.set_signature(signature);
	return true;
}

bool STK500v2_module::write_page(Memory_map& source, size_t size, size_t address)
{
	if (!stk500_load_address(address >> 1, source.get_size() > 64*1024))
	{
		return false;
	}
	//Maximum message length buffer.
	uint8_t buffer[275];
	size_t reply_length = 275;
	
	//The bootloader doesn't actually support doing a chip erase 
	//but this is how it resets its erase address that it uses while programming a page at a time.
	//Unfortunately due to how it does that this function must be used to write pages starting from 0
	//and continuing in sequence to the last page written, these must be contiguous or the position it is erasing
	//and the position it is programming will get out of sync.
	if (address == 0)
	{
		buffer[0] = CMD_CHIP_ERASE_ISP;
		if (!stk500_cmd(buffer, 1, reply_length))
		{
			return false;
		}
	}
	reply_length = 275;
	buffer[0] = CMD_PROGRAM_FLASH_ISP;
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = (size) & 0xFF;
	for (size_t i = 0; i < size; i++)
	{
		if (source.get_allocated_map()[address+i] == Memory_map::ALLOCATED)
		{
			buffer[i+10] = source.get_memory()[address+i];
		}
		else
		{
			buffer[i+10] = 0xFF;
		}
	}
	if (!stk500_cmd(buffer, 10+size, reply_length))
	{
		return false;
	}
	return true;
}

bool STK500v2_module::verify_page(Memory_map& expected, size_t size, size_t address)
{
	if (!stk500_load_address(address >> 1, expected.get_size() > 64*1024))
	{
		return false;
	}
	//Maximum message length buffer.
	uint8_t buffer[275];
	
	buffer[0] = CMD_READ_FLASH_ISP;
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = (size) & 0xFF;
	
	size_t reply_length = 275;
	if (!stk500_cmd(buffer, 3, reply_length))
	{
		return false;
	}
	if (reply_length != size+3)
	{
		return false;
	}
	
	for (size_t i = 0; i < size; i++)
	{
		if (expected.get_allocated_map()[address+i] == Memory_map::ALLOCATED &&
			expected.get_memory()[address+i] != buffer[2+i])
		{
			std::cerr << "Verify failure at address: " << address+i << 
			  " Expected: " << (int)expected.get_memory()[address+i] << " " << (int)expected.get_memory()[address+i+1] <<
			  " Got: " << (int)buffer[2+i] << " " << (int)buffer[2+i+1] << std::endl;
			return false;
		}
	} 
	
	return true;
}

bool STK500v2_module::read_page(Memory_map& destination, size_t size, size_t address)
{
	if (!stk500_load_address(address >> 1, destination.get_size() > 64*1024))
	{
		return false;
	}
	//Maximum message length buffer.
	uint8_t buffer[275];
	
	buffer[0] = CMD_READ_FLASH_ISP;
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = (size) & 0xFF;
	
	size_t reply_length = 275;
	if (!stk500_cmd(buffer, 3, reply_length))
	{
		return false;
	}
	if (reply_length != size+3)
	{
		return false;
	}
	
	for (size_t i = 0; i < size; i++)
	{
		destination.get_memory()[address+i] = buffer[2+i];
		destination.get_allocated_map()[address+i] = Memory_map::ALLOCATED;
	}
	
	return true;
}

bool STK500v2_module::reset_device(bool run_application)
{
	//Do the reset here by holding the DTR line low for a time then releasing it.
	set_cts_dtr(tty_fd, false);
	usleep( 50 * 1000);
	set_cts_dtr(tty_fd, true);
	usleep( 50 * 1000);
	if (run_application)
	{
		return true;
	}
	return connect_to_device();
}


bool STK500v2_module::open_serial()
{
	tty_fd = open(tty_path.c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY );
	if (tty_fd < 0 || !isatty(tty_fd))
	{
		return false;
	}
	return true;
}

bool STK500v2_module::setup_serial()
{
	//This is mostly written useing the avrdude setspeed function in its posix serial implementation.
	if (!isatty(tty_fd))
	{
		return false;
	}
	speed_t serial_speed = get_speed(speed);
	termios serial_params;
	int result_code;
	result_code = tcgetattr(tty_fd, &serial_params);
	if (result_code < 0)
	{
		return false;
	}
	
	if (!saved_original_termios)
	{
		original_termios = serial_params;
		saved_original_termios = true;
	}
	
	serial_params.c_iflag = IGNBRK;
	serial_params.c_oflag = 0;
	serial_params.c_lflag = 0;
	serial_params.c_cflag = (CS8 | CREAD | CLOCAL);
	serial_params.c_cc[VMIN] = 1;
	serial_params.c_cc[VTIME] = 0;
	
	cfsetospeed(&serial_params, serial_speed);
	cfsetispeed(&serial_params, serial_speed);
	
	result_code = tcsetattr(tty_fd, TCSANOW, &serial_params);
	if (result_code < 0)
	{
		return false;
	}
	
	//Clear the nonblocking flag since the port is now set for no flow control and local.
	result_code = fcntl(tty_fd, F_GETFL, 0);
	if (result_code != -1)
	{
		fcntl(tty_fd, F_SETFL, result_code & ~O_NONBLOCK);
	}
	
	return true;
}

bool STK500v2_module::close_serial()
{
	if (saved_original_termios)
	{
		int result_code = tcsetattr(tty_fd, TCSANOW | TCSADRAIN, &original_termios);
		if (result_code != 0)
		{
			//Emit error here in future when errors messages are added in.
		}
		saved_original_termios = false;
	}
	
	close(tty_fd);
	return true;
}

bool STK500v2_module::stk500_send(uint8_t* buf, size_t buf_len)
{
	//Buffer for message, max message length is 275.
	uint8_t buffer[275 + 6];
	
	if (buf_len > 275)
	{
		return false;
	}
	buffer[0] = MESSAGE_START;
	buffer[1] = stk500_seq_no;
	buffer[2] = buf_len / 256;
	buffer[3] = buf_len % 256;
	buffer[4] = TOKEN;
	//Copy the message into the buffer.
	memcpy(buffer+5, buf, buf_len);
	buffer[buf_len+5] = 0;
	for (size_t i = 0; i < buf_len+5; i++)
	{
		buffer[buf_len+5] ^= buffer[i];
	}
	
	return serial_send(tty_fd, buffer, buf_len+6);
	
}

bool STK500v2_module::stk500_recv(uint8_t* buf, size_t buf_len, size_t& bytes_read)
{
	enum states{
		START,
		SEQNO,
		LEN1,
		LEN2,
		TOK,
		DATA,
		CKSUM,
		DONE
	};
	states state = START;
	uint8_t c;
	uint8_t checksum;
	bool timeout = false;
	size_t message_length;
	size_t current_length = 0;
	
	uint32_t now, start;
	timeval tv;
	gettimeofday(&tv, NULL);
	start = tv.tv_sec;
	
	while ((state != DONE) && (!timeout))
	{
		if (!serial_recv(tty_fd, &c, 1, bytes_read))
		{
			return false;
		}
		checksum ^= c;
		
		switch (state)
		{
			case START:
			
				if (c == MESSAGE_START)
				{
					checksum = MESSAGE_START;
					state = SEQNO;
				}
				
				break;
			case SEQNO:
			
				if (c == stk500_seq_no)
				{
					stk500_seq_no++;
					state = LEN1;
				}
				else
				{
					state = START;
				}
				
				break;
			case LEN1:
			
				message_length = ((size_t)c)*256;
				state = LEN2;
				
				break;
			case LEN2:
			
				message_length += (size_t)c;
				state = TOK;
				
				break;
			case TOK:
			
				if (c == TOKEN)
				{
					state = DATA;
				}
				else
				{
					state = START;
				}
				
				break;
			case DATA:
			
				if (current_length < buf_len)
				{
					buf[current_length] = c;
				}
				else
				{
					return false;
				}
				
				if (current_length == 0 && c == ANSWER_CKSUM_ERROR)
				{
					return false;
				}
				
				current_length++;
				
				if (current_length == message_length)
				{
					state = CKSUM;
				}
				
				break;	
			case CKSUM:
				
				if (checksum == 0)
				{
					state = DONE;
				}
				else
				{
					state = START;
					return false;
				}
				
				break;
			case DONE:
			
				//Nothing to do.
			
				break;
			default:
				
				std::cout << "Unknown state in stk500v2Recv" << std::endl;
				return false;
				
				break;
		}
		
		gettimeofday(&tv, NULL);
		now = tv.tv_sec;
		
		if ((now - start) > TIMEOUT)
		{
			timeout = true;
			return false;
		}
	}
	
	bytes_read = message_length;
	return true;
}

/**
 * @param buf The buffer containing the command and which will have the response placed into it.
 * @param cmd_len The length of the command to send.
 * @param bytes_read Expected to contain the maximum number of bytes to read, and will be set to the actual message length.
 * 
 */
bool STK500v2_module::stk500_cmd(uint8_t* buf, size_t cmd_len, size_t& bytes_read)
{
	size_t buf_length = bytes_read;
	
	stk500_send(buf, cmd_len);
	
	bool status = stk500_recv(buf, buf_length, bytes_read);
	
	if (status)
	{	
		if (buf[1] == STATUS_CMD_OK)
		{
			return true;
		}
	}
		
	return false;
}

bool STK500v2_module::stk500_sync()
{
	if (!serial_drain(tty_fd))
	{
		return false;
	}
	uint8_t command[1];
	uint8_t response[32];
	
	int tries = 0;
	bool done = false;
	while( !done && tries < MAX_RETRIES )
	{
		command[0] = CMD_SIGN_ON;
		stk500_send(command, 1);
		size_t read;
		if (stk500_recv(response, sizeof(response), read))
		{
			if (response[0] == CMD_SIGN_ON && response[1] == STATUS_CMD_OK && read > 3)
			{
				done = true;
				prog_name = std::string((char*)&response[3],(size_t)response[2]);
				return true;
			}
		}
		tries++;
		
	}
	return false;
}

bool STK500v2_module::stk500_load_address(size_t address, bool far)
{
	//Max message length for stk500.
	uint8_t buffer[275];
	
	buffer[0] = CMD_LOAD_ADDRESS;
	
	buffer[1] = (((address & ~(1 << 31)) | ((far ? 1 : 0) << 31)) >> 24) & 0xFF;
	buffer[2] = (address >> 16) & 0xFF;
	buffer[3] = (address >> 8) & 0xFF;
	buffer[4] = (address) & 0xFF;
	size_t reply_length = 275;
	return stk500_cmd(buffer, 5, reply_length);
}


// IMPLEMENT PRIVATE FUNCTIONS.

speed_t get_speed(unsigned long speed)
{
	switch (speed)
	{
		case 1200:
			return B1200;
		case 2400:
			return B2400;
		case 4800:
			return B4800;
		case 9600:
			return B9600;
		case 19200:
			return B19200;
		case 38400:
			return B38400;
		case 57600:
			return B57600;
		case 115200:
			return B115200;
		default:
			return B115200;
	}
}

bool set_cts_dtr(int fd, bool on)
{
	int result;
	unsigned int ctl;
	
	result = ioctl(fd, TIOCMGET, &ctl);
	if (result < 0)
	{
		return false;
	}
	
	if (on)
	{
		ctl |= TIOCM_DTR | TIOCM_CTS;
	}
	else
	{
		ctl &= ~(TIOCM_DTR | TIOCM_CTS);
	}
	
	result = ioctl(fd, TIOCMSET, &ctl);
	if (result < 0)
	{
		return false;
	}
	
	return true;
}

bool serial_drain(int fd)
{
	timeval timeout;
	fd_set waitset;
	int number_ready;
	FD_ZERO(&waitset);
	FD_SET(fd, &waitset);
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 250 * 1000;
	bool drained = false;
	
	while (!drained)
	{
		number_ready = select(fd+1, &waitset, NULL, NULL, &timeout);
		if (number_ready == 0)
		{
			drained = true;
		}
		else if (number_ready == -1)
		{
			if (errno != EINTR)
			{
				//Error.
				return false;
			}
		}
		else
		{
			char c;
			int return_code = read(fd, &c, 1);
			if (return_code < 0)
			{
				//Error.
				return false;
			}
		}
	}
	return true;
}

bool serial_send(int fd, uint8_t* buf, size_t buf_len)
{
	size_t length = buf_len;
	uint8_t* bufPtr = buf;
	ssize_t result = 0;
	
	if (length == 0)
	{
		return true;
	}
	
	while (length > 0)
	{
		result = write(fd, bufPtr, (length > 1024) ? 1024 : length);
		if (result < 0)
		{
			//Error.
			return false;
		}
		bufPtr += result;
		length -= result;
	}
	return true;
}

bool serial_recv(int fd, uint8_t* buf, size_t buf_len, size_t& bytes_read)
{
	timeval timeout;
	fd_set waitset;
	int number_ready;
	FD_ZERO(&waitset);
	FD_SET(fd, &waitset);
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000 * 1000;
	bool have_read = false;
	
	while (!have_read)
	{
		number_ready = select(fd+1, &waitset, NULL, NULL, &timeout);
		if (number_ready == 0)
		{
			//Error.
			std::cerr << "Error" << std::endl;
			return false;
		}
		else if (number_ready == -1)
		{
			if (errno != EINTR || errno != EAGAIN)
			{
				//Error.
				std::cerr << "Error" << std::endl;
				return false;
			}
		}
		else
		{
			int return_code = read(fd, buf, buf_len);
			if (return_code < 0)
			{
				return false;
			}
			bytes_read = return_code;
			have_read = true;
		}
	}
	return true;
}

//ALL DONE.
