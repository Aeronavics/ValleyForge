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
 *  @file		microchipcannetworkinterface.hpp
 *  A header file for the Microchip CAN network interface.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		5-12-2012
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
#ifndef MICROCHIPCANNETWORKINTERFACE_H_
#define MICROCHIPCANNETWORKINTERFACE_H_

// INCLUDE REQUIRED HEADER FILES.

#include "cannetworkinterface.hpp"

#include <libusb-1.0/libusb.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

class libUSBContextHolder;
class USBMessage;

// DEFINE PUBLIC CLASSES.

class MicrochipCANNetworkInterface : public CANNetworkInterface
{
public:


	// Functions.
	MicrochipCANNetworkInterface();
	virtual ~MicrochipCANNetworkInterface();
	
	virtual bool init(Params params);
	
	virtual bool sendMessage(const CANMessage& msg, uint32_t timeout);
	virtual bool receiveMessage( CANMessage& msg, uint32_t timeout);
	virtual bool drainMessages();
	
protected:
	// Functions.
	static void* USBThreadFunc(void*);
	void processUSBEvents(void* m);
	void processMessage(USBMessage& m);
	
	//Fields.
	CANMessageQueue recvQueue;
	pthread_mutex_t recvQueueLock;
	
	
	
	pthread_t USBThread;
	
	libusb_device_handle* CANDevice;
	libUSBContextHolder* ctxHolder;
	bool quit;
	bool drain;
	bool transmitted;
	bool overflow;
	int index;
	
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*MICROCHIPCANNETWORKINTERFACE_H_*/
