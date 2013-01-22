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
 *  @file		socketcannetworkinterface.hpp
 *  A header file for a generic SocketCAN network interface.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		10-12-2012
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
#ifndef SOCKETCANNETWORKINTERFACE_H_
#define SOCKETCANNETWORKINTERFACE_H_

// INCLUDE REQUIRED HEADER FILES.

#include "cannetworkinterface.hpp"

#include <sys/socket.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class SocketCANNetworkInterface : public CANNetworkInterface
{
public:


	// Functions.
	SocketCANNetworkInterface();
	virtual ~SocketCANNetworkInterface();
	
	virtual bool init(Params params);
	
	virtual bool sendMessage(const CANMessage& msg, uint32_t timeout);
	virtual bool receiveMessage( CANMessage& msg, uint32_t timeout);
	virtual bool drainMessages();
	
protected:
	// Functions.
	static void* SocketThreadFunc(void*);
	void processSocketEvents();
	
	//Fields.
	CANMessageQueue recvQueue;
	pthread_mutex_t recvQueueLock;
	
	
	
	pthread_t SocketThread;
	
	int CANSocket;
	bool quit;
	bool inited;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*SOCKETCANNETWORKINTERFACE_H_*/
