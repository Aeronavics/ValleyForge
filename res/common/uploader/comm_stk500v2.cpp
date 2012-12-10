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
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <memory.h>

#include "command.h"

// DEFINE PRIVATE MACROS.

#define MAX_RETRIES 5
#define TIMEOUT 10

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

static STK500v2Module module;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

speed_t getSpeed(unsigned long speed);
bool setCTSDTR(int fd, bool on);
bool serialDrain(int fd);
bool serialSend(int fd, uint8_t* buf, size_t buflen);
bool serialRecv(int fd, uint8_t* buf, size_t buflen, size_t& bytesRead);


// IMPLEMENT PUBLIC FUNCTIONS.

STK500v2Module::STK500v2Module() :
	CommModule("stk500v2")
{
	
}

STK500v2Module::~STK500v2Module()
{
	closeSerial();
}

bool STK500v2Module::init(Params params)
{
	bool haveTTY = false;
	bool haveSpeed = false;
	std::string speedStr;
	if (params.find("tty") != params.end())
	{
		ttyPath = params["tty"];
		haveTTY = true;
	}
	if (params.find("speed") != params.end())
	{
		speedStr = params["speed"];
		haveSpeed = true;
	}
	
	if (! haveTTY)
	{
		return false;
	}
	if (! haveSpeed)
	{
		speed = 115200;
	}
	else
	{
		speed = strtoul(speedStr.c_str(),NULL,10);
	}
	stk500SeqNo = 0;
	connected = false;
	if (!openSerial())
	{
		return false;
	}
	if (!setupSerial())
	{
		return false;
	}
	return resetDevice(false);
}

bool STK500v2Module::connectToDevice()
{
	connected = stk500Sync();
	
	if (connected)
	{
		return true;
	}
	
	return false;
}

bool STK500v2Module::getDeviceInfo( DeviceInfo& info)
{
	//Maximum message length for stk500 buffer.
	uint8_t buffer[275];
	size_t replyLength;
	
	buffer[0] = CMD_READ_SIGNATURE_ISP;
	buffer[4] = 0;
	replyLength = 275;
	if (!stk500Cmd(buffer, 5, replyLength) || replyLength < 4)
	{
		return false;
	}
	signature0 = buffer[2];
	buffer[4] = 1;
	replyLength = 275;
	if (!stk500Cmd(buffer, 5, replyLength) || replyLength < 4)
	{
		return false;
	}
	signature1 = buffer[2];
	buffer[4] = 2;
	replyLength = 275;
	if (!stk500Cmd(buffer, 5, replyLength) || replyLength < 4)
	{
		return false;
	}
	signature2 = buffer[2];
	
	signature = signature0 << 16 | signature1 << 8 | signature2;
	
	info.setName(progname);
	info.setSignature(signature);
	return true;
}

bool STK500v2Module::writePage(MemoryMap& source, size_t size, size_t address)
{
	if (!stk500LoadAddress(address >> 1, source.getSize() > 64*1024))
	{
		return false;
	}
	//Maximum message length buffer.
	uint8_t buffer[275];
	size_t replyLength = 275;
	
	//The bootloader doesn't actually support doing a chip erase 
	//but this is how it resets its erase address that it uses while programming a page at a time.
	//Unfortunately due to how it does that this function must be used to write pages starting from 0
	//and continuing in sequence to the last page written, these must be contiguous or the position it is erasing
	//and the position it is programming will get out of sync.
	if (address == 0)
	{
		buffer[0] = CMD_CHIP_ERASE_ISP;
		if (!stk500Cmd(buffer, 1, replyLength))
		{
			return false;
		}
	}
	replyLength = 275;
	buffer[0] = CMD_PROGRAM_FLASH_ISP;
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = (size) & 0xFF;
	for (size_t i = 0; i < size; i++)
	{
		if (source.getAllocatedMap()[address+i] == MemoryMap::ALLOCATED)
		{
			buffer[i+10] = source.getMemory()[address+i];
		}
		else
		{
			buffer[i+10] = 0xFF;
		}
	}
	if (!stk500Cmd(buffer, 10+size, replyLength))
	{
		return false;
	}
	return true;
}

bool STK500v2Module::verifyPage(MemoryMap& expected, size_t size, size_t address)
{
	if (!stk500LoadAddress(address >> 1, expected.getSize() > 64*1024))
	{
		return false;
	}
	//Maximum message length buffer.
	uint8_t buffer[275];
	
	buffer[0] = CMD_READ_FLASH_ISP;
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = (size) & 0xFF;
	
	size_t replyLength = 275;
	if (!stk500Cmd(buffer, 3, replyLength))
	{
		return false;
	}
	if (replyLength != size+3)
	{
		return false;
	}
	
	for (size_t i = 0; i < size; i++)
	{
		if (expected.getAllocatedMap()[address+i] == MemoryMap::ALLOCATED &&
			expected.getMemory()[address+i] != buffer[2+i])
		{
			std::cerr << "Verify failure at address: " << address+i << 
				" Expected: " << (int)expected.getMemory()[address+i] << " " << (int)expected.getMemory()[address+i+1] <<
				" Got: " << (int)buffer[2+i] << " " << (int)buffer[2+i+1] << std::endl;
			return false;
		}
	} 
	
	return true;
}

bool STK500v2Module::readPage(MemoryMap& destination, size_t size, size_t address)
{
	if (!stk500LoadAddress(address >> 1, destination.getSize() > 64*1024))
	{
		return false;
	}
	//Maximum message length buffer.
	uint8_t buffer[275];
	
	buffer[0] = CMD_READ_FLASH_ISP;
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = (size) & 0xFF;
	
	size_t replyLength = 275;
	if (!stk500Cmd(buffer, 3, replyLength))
	{
		return false;
	}
	if (replyLength != size+3)
	{
		return false;
	}
	
	for (size_t i = 0; i < size; i++)
	{
		destination.getMemory()[address+i] = buffer[2+i];
		destination.getAllocatedMap()[address+i] = MemoryMap::ALLOCATED;
	}
	
	return true;
}

bool STK500v2Module::resetDevice(bool runApplication)
{
	//Do the reset here by holding the DTR line low for a time then releasing it.
	setCTSDTR(ttyFd, false);
	usleep( 50 * 1000);
	setCTSDTR(ttyFd, true);
	usleep( 50 * 1000);
	if (runApplication)
	{
		return true;
	}
	return connectToDevice();
}


bool STK500v2Module::openSerial()
{
	ttyFd = open(ttyPath.c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY );
	if (ttyFd < 0 || !isatty(ttyFd))
	{
		return false;
	}
	return true;
}

bool STK500v2Module::setupSerial()
{
	//This is mostly written useing the avrdude setspeed function in its posix serial implementation.
	if (!isatty(ttyFd))
	{
		return false;
	}
	speed_t serialSpeed = getSpeed(speed);
	termios serialparams;
	int resultCode;
	resultCode = tcgetattr(ttyFd, &serialparams);
	if (resultCode < 0)
	{
		return false;
	}
	
	if (!savedOriginalTermios)
	{
		originalTermios = serialparams;
		savedOriginalTermios = true;
	}
	
	serialparams.c_iflag = IGNBRK;
	serialparams.c_oflag = 0;
	serialparams.c_lflag = 0;
	serialparams.c_cflag = (CS8 | CREAD | CLOCAL);
	serialparams.c_cc[VMIN] = 1;
	serialparams.c_cc[VTIME] = 0;
	
	cfsetospeed(&serialparams, serialSpeed);
	cfsetispeed(&serialparams, serialSpeed);
	
	resultCode = tcsetattr(ttyFd, TCSANOW, &serialparams);
	if (resultCode < 0)
	{
		return false;
	}
	
	//Clear the nonblocking flag since the port is now set for no flow control and local.
	resultCode = fcntl(ttyFd, F_GETFL, 0);
	if (resultCode != -1)
	{
		fcntl(ttyFd, F_SETFL, resultCode & ~O_NONBLOCK);
	}
	
	return true;
}

bool STK500v2Module::closeSerial()
{
	if (savedOriginalTermios)
	{
		int resultCode = tcsetattr(ttyFd, TCSANOW | TCSADRAIN, &originalTermios);
		if (resultCode != 0)
		{
			//Emit error here in future when errors messages are added in.
		}
		savedOriginalTermios = false;
	}
	
	close(ttyFd);
	return true;
}

bool STK500v2Module::stk500Send(uint8_t* buf, size_t buflen)
{
	//Buffer for message, max message length is 275.
	uint8_t buffer[275 + 6];
	
	if (buflen > 275)
	{
		return false;
	}
	buffer[0] = MESSAGE_START;
	buffer[1] = stk500SeqNo;
	buffer[2] = buflen / 256;
	buffer[3] = buflen % 256;
	buffer[4] = TOKEN;
	//Copy the message into the buffer.
	memcpy(buffer+5, buf, buflen);
	buffer[buflen+5] = 0;
	for (size_t i = 0; i < buflen+5; i++)
	{
		buffer[buflen+5] ^= buffer[i];
	}
	
	return serialSend(ttyFd, buffer, buflen+6);
	
}

bool STK500v2Module::stk500Recv(uint8_t* buf, size_t buflen, size_t& bytesRead)
{
	enum states{
		sSTART,
		sSEQNO,
		sLEN1,
		sLEN2,
		sTOKEN,
		sDATA,
		sCKSUM,
		sDONE
	};
	states state = sSTART;
	uint8_t c;
	uint8_t checksum;
	bool timeout = false;
	size_t messageLength;
	size_t currentLength = 0;
	
	uint32_t now, start;
	timeval tv;
	gettimeofday(&tv, NULL);
	start = tv.tv_sec;
	
	while ((state != sDONE) && (!timeout))
	{
		if (!serialRecv(ttyFd, &c, 1, bytesRead))
		{
			return false;
		}
		checksum ^= c;
		
		switch (state)
		{
			case sSTART:
			
				if (c == MESSAGE_START)
				{
					checksum = MESSAGE_START;
					state = sSEQNO;
				}
				
				break;
			case sSEQNO:
			
				if (c == stk500SeqNo)
				{
					stk500SeqNo++;
					state = sLEN1;
				}
				else
				{
					state = sSTART;
				}
				
				break;
			case sLEN1:
			
				messageLength = ((size_t)c)*256;
				state = sLEN2;
				
				break;
			case sLEN2:
			
				messageLength += (size_t)c;
				state = sTOKEN;
				
				break;
			case sTOKEN:
			
				if (c == TOKEN)
				{
					state = sDATA;
				}
				else
				{
					state = sSTART;
				}
				
				break;
			case sDATA:
			
				if (currentLength < buflen)
				{
					buf[currentLength] = c;
				}
				else
				{
					return false;
				}
				
				if (currentLength == 0 && c == ANSWER_CKSUM_ERROR)
				{
					return false;
				}
				
				currentLength++;
				
				if (currentLength == messageLength)
				{
					state = sCKSUM;
				}
				
				break;	
			case sCKSUM:
				
				if (checksum == 0)
				{
					state = sDONE;
				}
				else
				{
					state = sSTART;
					return false;
				}
				
				break;
			case sDONE:
			
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
	
	bytesRead = messageLength;
	return true;
}

/**
 * @param buf The buffer containing the command and which will have the response placed into it.
 * @param cmdlen The length of the command to send.
 * @param bytesRead Expected to contain the maximum number of bytes to read, and will be set to the actual message length.
 * 
 */
bool STK500v2Module::stk500Cmd(uint8_t* buf, size_t cmdlen, size_t& bytesRead)
{
	size_t buflength = bytesRead;
	
	stk500Send(buf, cmdlen);
	
	bool status = stk500Recv(buf, buflength, bytesRead);
	
	if (status)
	{	
		if (buf[1] == STATUS_CMD_OK)
		{
			return true;
		}
	}
		
	return false;
}

bool STK500v2Module::stk500Sync()
{
	if (!serialDrain(ttyFd))
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
		stk500Send(command, 1);
		size_t read;
		if (stk500Recv(response, sizeof(response), read))
		{
			if (response[0] == CMD_SIGN_ON && response[1] == STATUS_CMD_OK && read > 3)
			{
				done = true;
				progname = std::string((char*)&response[3],(size_t)response[2]);
				return true;
			}
		}
		tries++;
		
	}
	return false;
}

bool STK500v2Module::stk500LoadAddress(size_t address, bool far)
{
	//Max message length for stk500.
	uint8_t buffer[275];
	
	buffer[0] = CMD_LOAD_ADDRESS;
	
	buffer[1] = (((address & ~(1 << 31)) | ((far ? 1 : 0) << 31)) >> 24) & 0xFF;
	buffer[2] = (address >> 16) & 0xFF;
	buffer[3] = (address >> 8) & 0xFF;
	buffer[4] = (address) & 0xFF;
	size_t replyLength = 275;
	return stk500Cmd(buffer, 5, replyLength);
}


// IMPLEMENT PRIVATE FUNCTIONS.

speed_t getSpeed(unsigned long speed)
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

bool setCTSDTR(int fd, bool on)
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

bool serialDrain(int fd)
{
	timeval timeout;
	fd_set waitset;
	int numberReady;
	FD_ZERO(&waitset);
	FD_SET(fd, &waitset);
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 250 * 1000;
	bool drained = false;
	
	while (!drained)
	{
		numberReady = select(fd+1, &waitset, NULL, NULL, &timeout);
		if (numberReady == 0)
		{
			drained = true;
		}
		else if (numberReady == -1)
		{
			if (errno != EINTR)
			{
				//Error message.
				return false;
			}
		}
		else
		{
			char c;
			int returnCode = read(fd, &c, 1);
			if (returnCode < 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool serialSend(int fd, uint8_t* buf, size_t buflen)
{
	size_t length = buflen;
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
			//Error message.
			return false;
		}
		bufPtr += result;
		length -= result;
	}
	return true;
}

bool serialRecv(int fd, uint8_t* buf, size_t buflen, size_t& bytesRead)
{
	timeval timeout;
	fd_set waitset;
	int numberReady;
	FD_ZERO(&waitset);
	FD_SET(fd, &waitset);
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000 * 1000;
	bool haveRead = false;
	
	while (!haveRead)
	{
		numberReady = select(fd+1, &waitset, NULL, NULL, &timeout);
		if (numberReady == 0)
		{
			//Error.
			std::cerr << "Error" << std::endl;
			return false;
		}
		else if (numberReady == -1)
		{
			if (errno != EINTR || errno != EAGAIN)
			{
				//Error message.
				std::cerr << "Error" << std::endl;
				return false;
			}
		}
		else
		{
			int returnCode = read(fd, buf, buflen);
			if (returnCode < 0)
			{
				return false;
			}
			bytesRead = returnCode;
			haveRead = true;
		}
	}
	return true;
}
