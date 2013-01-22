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
 *  @file		comm_CAN.hpp
 *  A header file for the CAN communications module.
 *  This module implements the CAN bootloader protocol and allows uploading firmware to a particular device on the CAN network.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		6-12-2012
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
#ifndef COMM_CAN_H_
#define COMM_CAN_H_

// INCLUDE REQUIRED HEADER FILES.
#include "comm.hpp"
#include "cannetworkinterface.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.


class CANModule : public CommModule
{
public:

	// Functions.
	CANModule();
	virtual ~CANModule();
	
	virtual bool init(Params params);
	virtual bool connectToDevice();
	
	virtual bool getDeviceInfo( DeviceInfo& info);
	
	virtual bool writePage(MemoryMap& source, size_t size, size_t address);
	virtual bool verifyPage(MemoryMap& expected, size_t size, size_t address);
	virtual bool readPage(MemoryMap& destination, size_t size, size_t address);
	
	virtual bool resetDevice(bool runApplication);
	
	
private:
	// Functions.
	
	//Fields.
	bool connected;
	uint8_t target;
	CANNetworkInterface* iface;
	
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*COMM_CAN_H_*/
