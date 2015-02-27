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
 *  FILE: 		socketcannetworkinterface.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		CAN Interface
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	10-12-2012
 *
 *	Implementation of the common functions for the SocketCAN Network Interface
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "socketcannetworkinterface.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/time.h>

#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <iostream>
#include <sstream>
#include <vector>


// DEFINE PRIVATE MACROS.

#define SET_ATOMIC(var) (__sync_bool_compare_and_swap(&(var), false, true))
#define RESET_ATOMIC(var) (__sync_bool_compare_and_swap(&(var), true, false))

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.
CAN_message parse_frame(can_frame frame);

// IMPLEMENT PUBLIC FUNCTIONS.



Socket_CAN_network_interface::Socket_CAN_network_interface() :
	quit(false),
	inited(false),
	recv_queue_lock(PTHREAD_MUTEX_INITIALIZER)
{
	//Nothing to do here.
}

Socket_CAN_network_interface::~Socket_CAN_network_interface()
{
	SET_ATOMIC(quit);
	if (inited)
	{
		int rc = pthread_join(socket_thread, NULL);
	}
	if (CAN_socket)
	{
		close(CAN_socket);
	}
}

bool Socket_CAN_network_interface::init(Params params)
{
	ifreq ifr;
	sockaddr_can addr;
	can_filter filter;
	
	
	bool haveBitrate = false;
	int bitrate = 1000000;
	bool termination = false;
	bool haveCanIface = false;
	std::string canIface; 
	std::string bitrateStr;
	if (params.find("bitrate") != params.end())
	{
		bitrateStr = params["bitrate"];
		haveBitrate = true;
	}
	if (haveBitrate)
	{
		bitrate = strtoul(bitrateStr.c_str(), NULL, 10);
	}
	if (params.find("termination") != params.end())
	{
		std::string terminationStr = params["termination"];
		if (terminationStr == "on")
		{
			termination = true;
		}
	}
	if (params.find("iface") != params.end())
	{
		canIface = params["iface"];
		haveCanIface = true;
	}
	if (!haveCanIface)
	{
		std::cerr << "No can interface specified." << std::endl;
		return false;
	}
	
	//Change bitrate?
	std::stringstream ss;
	ss << "sudo ip link set " << canIface << " down; sudo ip link set " << canIface << " up type can bitrate " << bitrate << " restart-ms 100 " <<  std::endl;
	
	system(ss.str().c_str());
	
	
	//Change mode?
	
	
	//Change termination? 
	
	
	
	//Do socket init here.
	CAN_socket =  socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (CAN_socket < 0)
	{
		std::cerr << "Could not create CAN socket." << std::endl;
		perror("Socket");
		return false;
	}
	
	addr.can_family = AF_CAN;
	
	strcpy(ifr.ifr_name, canIface.c_str());
	if (ioctl(CAN_socket, SIOCGIFINDEX, &ifr) < 0)
	{
		perror("Failed to get interface index");
		return false;
    }
	
	addr.can_ifindex = ifr.ifr_ifindex;
	
	int rc = bind(CAN_socket, (sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
	{
		perror("Failed to bind socket");
		return false;
	}
	
	filter.can_id = 0;
	filter.can_mask = 0;
	setsockopt(CAN_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(struct can_filter));
	
	rc = pthread_create(&socket_thread, NULL, socket_thread_func, (void*) this);
	if (rc != 0)
	{
		return false;
	}
	
	inited = true;
	
	return true;
}
	
bool Socket_CAN_network_interface::send_message(const CAN_message& msg, uint32_t timeout)
{
	can_frame frame;
	frame.can_id = msg.get_id();
	frame.can_dlc = msg.get_length();
	for (size_t i = 0; i < msg.get_length(); i++)
	{
		frame.data[i] = msg.get_data()[i];
	}

	int sent = write(CAN_socket, &frame, sizeof(frame));
	
	if (sent != sizeof(frame))
	{
		perror("Could not send");
		return false;
	}
	// std::cout << std::hex;
	// std::cout << "Sent     ID: " << msg.get_id() << " DLC: " << msg.get_length() << std::endl;
	// std::cout << std::dec;
	return true;
}


bool Socket_CAN_network_interface::receive_message( CAN_message& msg, uint32_t timeout)
{

	timeval start, now;
	gettimeofday(&start, NULL);
	//std::cout << "TRying receive" << std::endl;
	while (recv_queue.empty())
	{
		gettimeofday(&now, NULL);
		uint32_t msec = (now.tv_usec - start.tv_usec)/100000;
		// msec += (now.tv_sec - start.tv_sec)*1000;
		//msec += (now.tv_usec - start.tv_usec);
		if (msec > (timeout * 1000)) 	// timeout is given in ms
		{

			//std::cout << "Timeout" << std::endl;
			return false;
		}
	}
	//std::cout << "Got message" << std::endl;
	pthread_mutex_lock( &recv_queue_lock );
	msg = recv_queue.front();
	recv_queue.pop_front();
	pthread_mutex_unlock( &recv_queue_lock);
	return true;
	
}

bool Socket_CAN_network_interface::drain_messages()
{
	pthread_mutex_lock( &recv_queue_lock );
	recv_queue.clear();
	pthread_mutex_unlock( &recv_queue_lock );
	return true;
}

// IMPLEMENT PRIVATE FUNCTIONS.

void* Socket_CAN_network_interface::socket_thread_func(void* param)
{
	Socket_CAN_network_interface* obj = static_cast<Socket_CAN_network_interface*> (param);
	while (!__sync_fetch_and_add(&obj->quit, 0))
	{
		obj->process_socket_events();
	}
	return 0;
}

void Socket_CAN_network_interface::process_socket_events()
{
	//Receive a message and stuff it in the recv_queue.
	can_frame frame;
	timeval timeout;
	fd_set waitset;
	int numberReady;
	FD_ZERO(&waitset);
	FD_SET(CAN_socket, &waitset);
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 250 * 1000;
	
	numberReady = select(CAN_socket+1, &waitset, NULL, NULL, &timeout);
	if (numberReady == 0)
	{
		return;
	}
	else if (numberReady == -1)
	{
		if (errno != EINTR)
		{
			//Error message.
			perror("Select Failed");
			return;
		}
	}
	else
	{

		int bytes_read = read( CAN_socket, &frame, sizeof(frame) );
		if (bytes_read == sizeof(frame))
		{
			CAN_message msg = parse_frame(frame);
			if (filter(msg.get_id()))
			{
				pthread_mutex_lock( &recv_queue_lock );
				recv_queue.push_back(msg);
				pthread_mutex_unlock( &recv_queue_lock );
			}
			// std::cout << std::hex;
			// std::cout << "Received ID: " << msg.get_id() << " DLC: " << msg.get_length() << std::endl;
			// std::cout << std::dec;
	
		}
		else
		{
			perror("Receive");
		}
	}
	
	
}

CAN_message parse_frame(can_frame frame)
{
	CAN_message msg;
	uint32_t id = frame.can_id;
	id &= CAN_EFF_MASK;
	msg.set_id(id);
	msg.set_length(frame.can_dlc);
	for (size_t i = 0; i < frame.can_dlc; i++)
	{
		msg.get_content()[i] = frame.data[i];
	}
	return msg;
}

//ALL DONE.
