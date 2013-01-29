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
 *  FILE: 		comm_CAN.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Comm Modules
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	6-12-2012
 *
 *	Implementation of the stk500v2 communications protocol.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "comm_CAN.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

#include "microchipcannetworkinterface.hpp"
#include "socketcannetworkinterface.hpp"

#include "can_messages.hpp"


// DEFINE PRIVATE MACROS.

#define MAX_RETRIES 5
#define TIMEOUT 10

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

static CAN_module module;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

CAN_message make_command(uint32_t id, uint8_t target, size_t length);
bool check_reply(CAN_message& msg);

// IMPLEMENT PUBLIC FUNCTIONS.

CAN_module::CAN_module() :
	Comm_module("can")
{
	//Nothing to do here.
}

CAN_module::~CAN_module()
{
	delete iface;
}

bool CAN_module::init(Params params)
{
	connected = false;
	bool have_CAN_type = false;
	std::string can_type;
	bool have_target = false;
	if (params.find("can-type") != params.end())
	{
		can_type = params["can-type"];
		have_CAN_type = true;
	}
	if (params.find("target") != params.end())
	{
		have_target = true;
		char* end;
		target = strtoul(params["target"].c_str(), &end, 16);
		if ((end - params["target"].c_str()) != params["target"].length())
		{
			//std::cerr << *end << std::endl;
			std::cerr << "Invalid target node ID" << std::endl;
			return false;
		}
	}
	if (have_CAN_type)
	{
		if (can_type == "socket")
		{
			iface = new Socket_CAN_network_interface;
		}
		if (can_type == "microchip")
		{
			iface = new Microchip_CAN_network_interface;
		}
	}
	else
	{
		iface = new Microchip_CAN_network_interface;
	}
	if (!have_target)
	{
		std::cerr << "No target node ID given." << std::endl;
		return false;
	}
	if (!iface->init(params))
	{
		std::cerr << "Failed To init Network interface" << std::endl;
		return false;
	}
	if (!iface->set_filter_mode(CAN_network_interface::EXCLUDE_ALL_BUT_FILTER))
	{
		std::cerr << "Failed to set filter mode" << std::endl;
		return false;
	}
	if (!iface->clear_filter())
	{
		std::cerr << "Failed to clear filters." << std::endl;
	}
	//~ if (!iface->set_filter(HOST_ALERT, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->set_filter(REQUEST_RESET, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->set_filter(GET_INFO, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->set_filter(WRITE_MEMORY, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->set_filter(WRITE_DATA, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->set_filter(READ_MEMORY, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->set_filter(READ_DATA, CAN_network_interface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	
	return reset_device(false);
}

bool CAN_module::connect_to_device()
{
	CAN_message msg;
	if (!iface->set_filter(HOST_ALERT, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->receive_message(msg, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply." << std::endl;
		return false;
	}
	if (msg.get_id() == 0x2FF)
	{
		
		Device_info temp;
		if (get_device_info(temp))
		{
			connected = true;
		}
	}
	if (connected)
	{
		return true;
	}
	
	std::cerr << "Failed to Connect to device." << std::endl;
	return false;
}

bool CAN_module::get_device_info( Device_info& info)
{
	CAN_message get_info = make_command(GET_INFO, target, 1);
	if (!iface->clear_filter())
	{
		return false;
	}
	
	if (!iface->set_filter(GET_INFO, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(get_info, TIMEOUT*1000))
	{
		return false;
	}
	if (!iface->receive_message(get_info, TIMEOUT*1000))
	{
		return false;
	}
	if (get_info.get_id() != GET_INFO || get_info.get_length() < 6)
	{
		return false;
	}
	info.set_name("CAN Bootloader");
	const uint8_t* data = get_info.get_data();
	uint32_t signature = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
	info.set_signature(signature);
	info.set_version_major(data[4]);
	info.set_version_minor(data[5]);
	return true;
}

bool CAN_module::write_page(Memory_map& source, size_t size, size_t address)
{
	CAN_message write_memory = make_command(WRITE_MEMORY, target, 7);
	uint8_t* data = write_memory.get_content();
	data[1] = (address >> 24) & 0xFF;
	data[2] = (address >> 16) & 0xFF;
	data[3] = (address >> 8) &0xFF;
	data[4] = (address) & 0xFF;
	data[5] = (size >> 8) &0xFF;
	data[6] = (size) & 0xFF;
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(WRITE_MEMORY, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(write_memory, TIMEOUT*1000))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receive_message(write_memory, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply" << std::endl;
		return false;
	}
	if (!check_reply(write_memory))
	{
		std::cerr << "Reply indicates failure, WritePage" << std::endl;
		return false;
	}
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(WRITE_DATA, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	size_t remaining = size;
	size_t current_message = 0;
	while (remaining > 0)
	{
		//std::cout << "Sending Message: " << current_message << std::endl;
		size_t packet_size = (remaining > 7) ? 7 : remaining;
		write_memory = make_command(WRITE_DATA, target, packet_size+1);
		for (size_t j = 0; j < packet_size; j++)
		{
			if (source.get_allocated_map()[address+(current_message*7)+j] == Memory_map::ALLOCATED)
			{
				write_memory.get_content()[j+1] = source.get_memory()[address+(current_message*7)+j];
			}
			else
			{
				write_memory.get_content()[j+1] = 0xFF;
			}
		}
		
		if (!iface->send_message(write_memory, TIMEOUT*1000))
		{
			std::cerr << "Failed to send data packet: " << current_message << std::endl;
			return false;
		}
		if (!iface->receive_message(write_memory, TIMEOUT*1000))
		{
			std::cerr << "Failed to receive message acknowledge, WritePage: " << current_message << std::endl;
			return false;
		}
		if (!check_reply(write_memory))
		{
			std::cerr << "Acknowledge indicates failure:" << current_message << std::endl;
			return false;
		}
		remaining -= packet_size;
		current_message++;
	}
	return true;
}

bool CAN_module::verify_page(Memory_map& expected, size_t size, size_t address)
{
	CAN_message read_memory = make_command(READ_MEMORY, target, 7);
	uint8_t* data = read_memory.get_content();
	data[1] = (address >> 24) & 0xFF;
	data[2] = (address >> 16) & 0xFF;
	data[3] = (address >> 8) &0xFF;
	data[4] = (address) & 0xFF;
	data[5] = (size >> 8) & 0xFF;
	data[6] = (size) & 0xFF;
	
	int number_of_messages = (size/8);
	//std::cout << number_of_messages << std::endl;
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(READ_MEMORY, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(read_memory, TIMEOUT*1000))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receive_message(read_memory, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply" << std::endl;
		return false;
	}
	if (!check_reply(read_memory))
	{
		std::cerr << "Reply indicates failure, VerifyPage" << std::endl;
		return false;
	}
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(READ_DATA, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	bool verified = true;
	for (int i = 0; i < number_of_messages; i++)
	{
		if (!iface->receive_message(read_memory, TIMEOUT*1000))
		{
			std::cerr << "Failed to receive message: " << i << std::endl;
			return false;
		}
		for (size_t j = 0; j < read_memory.get_length(); j++)
		{
			//std::cout << "Verifying address: " << (address+(i*8)+j) << std::endl;
			if (expected.get_allocated_map()[address+(i*8)+j] == Memory_map::ALLOCATED)
			{
				if (expected.get_memory()[address+(i*8)+j] != read_memory.get_data()[j])
				{
					std::cout << "Verification failed." << std::endl;
					verified = false;
				}
			}
		}
		read_memory = make_command(READ_DATA, target, 1);
		//usleep(1*1000);
		if (!iface->send_message(read_memory, TIMEOUT*1000))
		{
			bool check_reply(CAN_message& msg);
			std::cerr << "Failed to send acknowledgement for message: " << i << std::endl;
			return false;
		}
	}
	return verified;
}

bool CAN_module::read_page(Memory_map& destination, size_t size, size_t address)
{
	CAN_message read_memory = make_command(READ_MEMORY, target, 7);
	uint8_t* data = read_memory.get_content();
	data[1] = (address >> 24) & 0xFF;
	data[2] = (address >> 16) & 0xFF;
	data[3] = (address >> 8) &0xFF;
	data[4] = (address) & 0xFF;
	data[5] = (size >> 8) & 0xFF;
	data[6] = (size) & 0xFF;
	int number_of_messages = (size/8);
	//std::cout << number_of_messages << std::endl;
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(READ_MEMORY, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(read_memory, TIMEOUT*1000))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receive_message(read_memory, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply" << std::endl;
		return false;
	}
	if (!check_reply(read_memory))
	{
		std::cerr << "Reply indicates failure, ReaDPage" << std::endl;
		return false;
	}
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(READ_DATA, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	for (int i = 0; i < number_of_messages; i++)
	{
		if (!iface->receive_message(read_memory, TIMEOUT*1000))
		{
			std::cerr << "Failed to receive message: " << i << std::endl;
			return false;
		}
		for (size_t j = 0; j < read_memory.get_length(); j++)
		{
			//std::cout << "Writing to address: " << (address+(i*8)+j) << std::endl;
			destination.get_memory()[address+(i*8)+j] = read_memory.get_data()[j];
			destination.get_allocated_map()[address+(i*8)+j] = Memory_map::ALLOCATED;
		}
		read_memory = make_command(READ_DATA, target, 1);
		//usleep(1*1000);bool check_reply(CAN_message& msg);
		if (!iface->send_message(read_memory, TIMEOUT*1000))
		{
			std::cerr << "Failed to send acknowledgement for message: " << i << std::endl;
			return false;
		}
	}
	return true;
}

bool CAN_module::reset_device(bool run_application)
{
	CAN_message reset_message = make_command(REQUEST_RESET, target, 2);
	reset_message.get_content()[1] = run_application ? 1 : 0;
	if (! iface->drain_messages())
	{
		return false;
	}
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(REQUEST_RESET, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->send_message(reset_message, TIMEOUT*1000))
	{
		return false;
	}
	if (!iface->receive_message(reset_message, TIMEOUT*1000))
	{
		std::cerr << "Warning did not receive reset reply." << std::endl;
	}
	else
	{
		if (reset_message.get_id() != REQUEST_RESET)
		{
			std::cerr << "Did not receive reset confirmation instead received something else." << std::endl;
			return false;
		}
		else
		{
			if (!check_reply(reset_message))
			{
				std::cerr << "Reset reply indicates failure." << std::endl;
				return false;
			}
		}
	}
	if (!iface->clear_filter())
	{
		return false;
	}
	if (! iface->drain_messages())
	{
		return false;
	}
	if (run_application)
	{
		return true;
	}
	if (!iface->set_filter(HOST_ALERT, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	return connect_to_device();
}

CAN_message make_command(uint32_t id, uint8_t target, size_t length)
{
	CAN_message msg;
	msg.set_id(id);
	msg.set_length(length);
	msg.get_content()[0]=target;
	return msg;
}

bool check_reply(CAN_message& msg)
{
	if (msg.get_length() < 1)
	{
		return false;
	}
	return msg.get_data()[0] != 0;
}

//ALL DONE.
