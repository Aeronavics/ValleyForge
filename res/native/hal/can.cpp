// Copyright (C) 2013  Unison Networks Ltd
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
 *  FILE: 		can.cpp	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	13-12-2013
 *
 *	Functionality to provide implementation for CAN with SocketCAN
 ********************************************************************************************************************************/
 
// INCLUDE THE MATCHING HEADER FILE.
#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include "can_platform.hpp"

#include <stdio.h>		//probably used here for debug only
#include <stdlib.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <string.h>

/**********************************************************************/
// Typdefs
/**********************************************************************/
// Interrupts expected to work very differently here

/**********************************************************************/
class Can_tree
{
	//there's really no reason for this class to exist as the kernel itself 
	//will deal with the whole interface binding stuff, however to keep 
	//the interface consistent, it remains as a dummy
};

static Can_tree Can_tree_imps[NB_CTRL];

/**********************************************************************/
/**
 * Creating socket occurs for every operation, putting these series of 
 * commands under one function removes the need to do it every single
 * time
 */
int create_socket(int can_index)
{
	int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	struct ifreq ifr;
	memset(&ifr, 0x0, sizeof(ifr));
	
	char* address_str;
	sprintf(address_str, "can%d", can_index);
	strcpy(ifr.ifr_name, address_str);
	
	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;;
	
	::bind(s, (struct sockaddr *)&addr, sizeof(addr));
	
	return s;
}

/**********************************************************************/
Can::Can(Can_tree* imp)
{
	Can_controller = imp;
	return;
}

Can Can::bind(CAN_CTRL controller)
{	
	return Can(&Can_tree_imps[controller]);
}

bool Can::initialise(CAN_RATE rate)
{
	return true;
}

void Can::set_buffer_mode(CAN_BUF buffer_name, CAN_BUF_MODE mode)
{

}

Can_message Can::read(CAN_BUF buffer_name)
{
	/* ************** Create file descriptor ************** */
	int s = create_socket(static_cast<int>(buffer_name));

	/* ************** Reading message ************** */
	struct can_frame frame;
	::recv(s, &frame, sizeof(frame), 0);
	

	close(s);
	
	Can_message msg;
	msg.id = frame.can_id;
	msg.dlc = frame.can_dlc;
	for (uint8_t i=0; i<msg.dlc; i++)
	{
		msg.data[i] = frame.data[i];
	}
	
	return msg;	
}

bool Can::transmit(CAN_BUF buffer_name, Can_message msg)
{
	/* ************** Create file descriptor ************** */
	int s = create_socket(static_cast<int>(buffer_name));

	/* ************** Creating frame ************** */
	struct can_frame frame;
	frame.can_id = msg.id;
	frame.can_dlc = msg.dlc;
	for (uint8_t i=0; i<frame.can_dlc; i++)
	{
		frame.data[i] = msg.data[i];
	}
	
	/* ************** Writing frame to buffer **************** */
	int ret;
	while ((ret = send(s, &frame, sizeof(frame), 0)) < sizeof(frame))
	{
		if (ret < 0)
		{
			return false;	//send error
		}
	}
		
	if (close(s) < 0)
	{
		return false;	//file descriptor closing error
	}
	else
	{
		return true;	//whew! no errors
	}
}

void Can::clear_buffer_status(CAN_BUF buffer_name)
{
	
}

void Can::set_filter_val(CAN_FIL filter_name, uint32_t filter_val, bool RTR)
{
	/* ************** Create file descriptor ************** */
	int s = create_socket(static_cast<int>(filter_name));
	
	/* ************** Creating filter data ************** */ 
	struct can_filter rfilter;
	rfilter.can_id = filter_val;
	
	/* ************** Setting filter data *************** */
	::setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
	close(s);
}

void Can::set_mask_val(CAN_FIL filter_name, uint32_t mask_val, bool RTR)
{
	/* ************** Create file descriptor ************** */
	int s = create_socket(static_cast<int>(filter_name));
	
	/* ************** Creating filter data ************** */ 
	struct can_filter rfilter;
	rfilter.can_mask = mask_val;
	
	/* ************** Setting filter data *************** */
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
	close(s);
}


 
