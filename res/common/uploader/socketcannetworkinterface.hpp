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
 * Copyright (C) 2012  Unison Networks Ltd
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
#ifndef __SOCKETCANNETWORKINTERFACE_H__
#define __SOCKETCANNETWORKINTERFACE_H__

// INCLUDE REQUIRED HEADER FILES.

#include "cannetworkinterface.hpp"

#include <sys/socket.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class Socket_CAN_network_interface : public CAN_network_interface
{
public:


	// Functions.
	Socket_CAN_network_interface();
	virtual ~Socket_CAN_network_interface();
	
	virtual bool init(Params params);
	
	virtual bool send_message(const CAN_message& msg, uint32_t timeout);
	virtual bool receive_message( CAN_message& msg, uint32_t timeout);
	virtual bool drain_messages();
	
protected:
	// Functions.
	static void* socket_thread_func(void*);
	void process_socket_events();
	
	//Fields.
	CAN_message_queue recv_queue;
	pthread_mutex_t recv_queue_lock;
	
	
	
	pthread_t socket_thread;
	
	int CAN_socket;
	bool quit;
	bool inited;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__SOCKETCANNETWORKINTERFACE_H__*/
