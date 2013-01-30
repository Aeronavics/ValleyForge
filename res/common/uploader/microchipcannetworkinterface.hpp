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
#ifndef __MICROCHIPCANNETWORKINTERFACE_H__
#define __MICROCHIPCANNETWORKINTERFACE_H__

// INCLUDE REQUIRED HEADER FILES.

#include "cannetworkinterface.hpp"

#include <libusb-1.0/libusb.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

class libUSB_context_holder;
class USB_message;

// DEFINE PUBLIC CLASSES.

class Microchip_CAN_network_interface : public CAN_network_interface
{
public:


	// Functions.
	Microchip_CAN_network_interface();
	virtual ~Microchip_CAN_network_interface();
	
	virtual bool init(Params params);
	
	virtual bool send_message(const CAN_message& msg, uint32_t timeout);
	virtual bool receive_message( CAN_message& msg, uint32_t timeout);
	virtual bool drain_messages();
	
protected:
	// Functions.
	static void* USB_thread_func(void*);
	void process_USB_events(void* m);
	void process_message(USB_message& m);
	
	//Fields.
	CAN_message_queue recv_queue;
	pthread_mutex_t recv_queue_lock;
	
	
	
	pthread_t USB_thread;
	
	libusb_device_handle* CAN_device;
	libUSB_context_holder* ctx_holder;
	bool quit;
	bool drain;
	bool transmitted;
	bool overflow;
	bool inited;
	int index;
	
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__MICROCHIPCANNETWORKINTERFACE_H__*/

//ALL DONE.

