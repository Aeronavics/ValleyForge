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
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>


// DEFINE PRIVATE MACROS.

#define SET_ATOMIC(var) (__sync_bool_compare_and_swap(&(var), false, true))
#define RESET_ATOMIC(var) (__sync_bool_compare_and_swap(&(var), true, false))

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.
CANMessage parse_frame(can_frame frame);

// IMPLEMENT PUBLIC FUNCTIONS.



SocketCANNetworkInterface::SocketCANNetworkInterface() :
	quit(false),
	recvQueueLock(PTHREAD_MUTEX_INITIALIZER)
{
}

SocketCANNetworkInterface::~SocketCANNetworkInterface()
{
	SET_ATOMIC(quit);
	int rc = pthread_join(SocketThread, NULL);
	if (CANSocket)
	{
		close(CANSocket);
	}
}

bool SocketCANNetworkInterface::init(Params params)
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
	CANSocket =  socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (CANSocket < 0)
	{
		std::cerr << "Could not create CAN socket." << std::endl;
		perror("Socket");
		return false;
	}
	
	addr.can_family = AF_CAN;
	
	strcpy(ifr.ifr_name, canIface.c_str());
	if (ioctl(CANSocket, SIOCGIFINDEX, &ifr) < 0)
	{
		perror("Failed to get interface index");
		return false;
    }
	
	addr.can_ifindex = ifr.ifr_ifindex;
	
	int rc = bind(CANSocket, (sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
	{
		perror("Failed to bind socket");
		return false;
	}
	
	filter.can_id = 0;
	filter.can_mask = 0;
	setsockopt(CANSocket, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(struct can_filter));
	
	rc = pthread_create(&SocketThread, NULL, SocketThreadFunc, (void*) this);
	if (rc != 0)
	{
		return false;
	}
	
	
	
	//~ SET_ATOMIC(drain);
	//~ usleep(500000);
	//~ RESET_ATOMIC(drain);
	//~ 
	//~ std::cout << "Sleeping" << std::endl;
	//~ usleep(500000);
	//~ std::cout << "Waking" << std::endl;
	
	return true;
}
	
bool SocketCANNetworkInterface::sendMessage(const CANMessage& msg, uint32_t timeout)
{
	can_frame frame;
	frame.can_id = msg.getId();
	frame.can_dlc = msg.getLength();
	for (size_t i = 0; i < msg.getLength(); i++)
	{
		frame.data[i] = msg.getData()[i];
	}
	int sent = write(CANSocket, &frame, sizeof(frame));
	if (sent != sizeof(frame))
	{
		perror("Could not send");
		return false;
	}
	//std::cout << "Sent Message: ID: " << msg.getId() << std::endl;
	return true;
}


bool SocketCANNetworkInterface::receiveMessage( CANMessage& msg, uint32_t timeout)
{

	timeval start, now;
	gettimeofday(&start, NULL);
	//std::cout << "TRying receive" << std::endl;
	while (recvQueue.empty())
	{
		gettimeofday(&now, NULL);
		uint32_t msec = (now.tv_usec - start.tv_usec)/1000;
		msec += (now.tv_sec - start.tv_sec)*1000;
		if (msec > timeout )
		{
			//std::cout << "Timeout" << std::endl;
			return false;
		}
	}
	//std::cout << "Got message" << std::endl;
	pthread_mutex_lock( &recvQueueLock );
	msg = recvQueue.front();
	recvQueue.pop_front();
	pthread_mutex_unlock( &recvQueueLock);
	return true;
	
}

bool SocketCANNetworkInterface::drainMessages()
{
	pthread_mutex_lock( &recvQueueLock );
	recvQueue.clear();
	pthread_mutex_unlock( &recvQueueLock );
	return true;
}

// IMPLEMENT PRIVATE FUNCTIONS.

void* SocketCANNetworkInterface::SocketThreadFunc(void* param)
{
	SocketCANNetworkInterface* obj = static_cast<SocketCANNetworkInterface*> (param);
	while (!__sync_fetch_and_add(&obj->quit, 0))
	{
		obj->processSocketEvents();
	}
	return 0;
}

void SocketCANNetworkInterface::processSocketEvents()
{
	//Receive a message and stuff it in the recvQueue.
	can_frame frame;
	timeval timeout;
	fd_set waitset;
	int numberReady;
	FD_ZERO(&waitset);
	FD_SET(CANSocket, &waitset);
	
	timeout.tv_sec = 0;
	timeout.tv_usec = 250 * 1000;
	
	numberReady = select(CANSocket+1, &waitset, NULL, NULL, &timeout);
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
		int bytes_read = read( CANSocket, &frame, sizeof(frame) );
		if (bytes_read == sizeof(frame))
		{
			CANMessage msg = parse_frame(frame);
			if (filter(msg.getId()))
			{
				pthread_mutex_lock( &recvQueueLock );
				recvQueue.push_back(msg);
				pthread_mutex_unlock( &recvQueueLock );
			}
			//std::cout << "Received message: ID: " << msg.getId() << std::endl;
		}
		else
		{
			perror("Receive");
		}
	}
	
	
}

CANMessage parse_frame(can_frame frame)
{
	CANMessage msg;
	uint32_t id = frame.can_id;
	id &= CAN_EFF_MASK;
	msg.setId(id);
	msg.setLength(frame.can_dlc);
	for (size_t i = 0; i < frame.can_dlc; i++)
	{
		msg.getContent()[i] = frame.data[i];
	}
	return msg;
}
