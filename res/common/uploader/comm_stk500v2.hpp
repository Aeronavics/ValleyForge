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

/**
 *
 * 
 *  @file		comm_stk500v2.hpp
 *  A header file for an stk500v2 communications module.
 *  Currently this module is specific to the arduino bootloader.
 *  It doesnt use any of the command bits needed by a real STK500 for programming arbitrary AVRs.
 *  This is the same protocol that is used by most arduino bootloaders so this can be used to program APM boards.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		27-11-2012
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 * 
 */
 
//Only include header once.
#ifndef COMM_STK500V2_H_
#define COMM_STK500V2_H_

// INCLUDE REQUIRED HEADER FILES.
#include "comm.hpp"

#include <termios.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.


class STK500v2Module : public CommModule
{
public:

	// Functions.
	STK500v2Module();
	virtual ~STK500v2Module();
	
	virtual bool init(Params params);
	virtual bool connectToDevice();
	
	virtual bool getDeviceInfo( DeviceInfo& info);
	
	virtual bool writePage(MemoryMap& source, size_t size, size_t address);
	virtual bool verifyPage(MemoryMap& expected, size_t size, size_t address);
	virtual bool readPage(MemoryMap& destination, size_t size, size_t address);
	
	virtual bool resetDevice(bool runApplication);
	
	
private:
	// Functions.
	bool openSerial();
	bool setupSerial();
	bool closeSerial();
	bool stk500Send(uint8_t* buf, size_t buflen);
	bool stk500Recv(uint8_t* buf, size_t buflen, size_t& bytesRead);
	bool stk500Cmd(uint8_t* buf, size_t cmdlen, size_t& bytesRead);
	bool stk500Sync();
	bool stk500LoadAddress(size_t address, bool far);
	
	//Fields.
	std::string ttyPath;
	unsigned long speed;
	int ttyFd;
	termios originalTermios;
	bool savedOriginalTermios;
	
	bool connected;
	
	std::string progname;
	uint8_t signature0;
	uint8_t signature1;
	uint8_t signature2;
	uint32_t signature;
	
	uint8_t stk500SeqNo;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*COMM_STK500V2_H_*/
