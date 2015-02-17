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

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <iostream>

#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

#include <sys/time.h>

#include "microchipcannetworkinterface.hpp"
#include "socketcannetworkinterface.hpp"

#include "can_messages.h"

// DEFINE PRIVATE MACROS.

// Number of tries to attempt (for the overall uploading process) before declaring failure.
#define MAX_RETRIES 5

// Timeout for CAN RX (and TX) operations, in ms. 
#define TIMEOUT 10000

// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

// DECLARE PRIVATE GLOBAL VARIABLES.

static CAN_module module;

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

CAN_message make_command(uint32_t id, uint8_t target, size_t length);

bool check_reply(CAN_message& msg);

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

// IMPLEMENT PUBLIC CLASS FUNCTIONS.

CAN_module::CAN_module() : Comm_module("can")
{
	// Nothing to do here.

	// All done.
	return;
}

CAN_module::~CAN_module()
{
	// Release the underlying interface.
	delete iface;

	// All done.
	return;
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

	// All done.
	return true;
}

bool CAN_module::connect_to_device()
{
	// Attempt to reset the device we're interested in.
	if (!reset_device(false))
	{
		// We failed to reset the device for whatever reason.
		std::cerr << "Uploader:connect_to_device - Failed to reset device." << std::endl;
		return false;
	}

	CAN_message msg_rx_host_alert;
	if (!iface->set_filter(CANID_HOST_ALERT, CAN_network_interface::INCLUDE))
	{
		// Something went wrong internally.
		std::cerr << "Uploader:connect_to_device - Failed to set interface filter." << std::endl;
		return false;
	}

	// TODO - The obvious problem here is that if more than one device reset at the same time, this may fail since it is only filtering by message ID.

	// Listen until we hear a message from the device.
	if (!iface->receive_message(msg_rx_host_alert, TIMEOUT))
	{
		// The device doesn't seem to be ready, so we bail.
		std::cerr << "Uploader:connect_to_device - Timed out while waiting on ALERT_HOST message." << std::endl;
		return false;
	}

	// Check that the message was what we expected.
	if (msg_rx_host_alert.get_id() == CANID_HOST_ALERT)
	{
		// Something went wrong internally.
		std::cerr << "Uploader:connect_to_device - Invalid filtering on RX ALERT_HOST message." << std::endl;
		return false;
	}

	// Check whether the ALERT_HOST message contained some data.
	if (msg_rx_host_alert.get_length() != 1)
	{
		// The content of the message wasn't what we were expecting.
		std::cerr << "Uploader:connect_to_device - RX ALERT_HOST message didn't have DLC of 1." << std::endl;
		return false;
	}

	// Check that the responding device was the one we want.
	if (msg_rx_host_alert.get_content()[0] != target)
	{
		// This doesn't seem to be from the device we wanted.
		std::cerr << "Uploader:connect_to_device - RX ALERT_HOST message was from wrong device.  We can't handle multiple devices right now." << std::endl;
		return false;
	}
	
	// Read device-info from the device.
	Device_info devinfo;
	if (!get_device_info(devinfo))
	{
		// We failed to read from the device for whatever reason.
		std::cerr << "Uploader:connect_to_device - Failed to read device-info from device." << std::endl;
		return false;
	}

	// Otherwise, if we make it all the way here, we should be good to go.

	// All done.
	return true;
}

bool CAN_module::get_device_info( Device_info& info)
{
	CAN_message get_info = make_command(CANID_GET_INFO, target, 1);
	if (!iface->clear_filter())
	{
		return false;
	}
	
	if (!iface->set_filter(CANID_GET_INFO, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(get_info, TIMEOUT))
	{
		return false;
	}
	if (!iface->receive_message(get_info, TIMEOUT))
	{
		return false;
	}
	if (get_info.get_id() != CANID_GET_INFO || get_info.get_length() < 6)
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
	CAN_message write_memory = make_command(CANID_WRITE_MEMORY, target, 7);
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
	if (!iface->set_filter(CANID_WRITE_MEMORY, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(write_memory, TIMEOUT))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receive_message(write_memory, TIMEOUT))
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
	if (!iface->set_filter(CANID_WRITE_DATA, CAN_network_interface::INCLUDE))
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
		write_memory = make_command(CANID_WRITE_DATA, target, packet_size+1);
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
		
		if (!iface->send_message(write_memory, TIMEOUT))
		{
			std::cerr << "Failed to send data packet: " << current_message << std::endl;
			return false;
		}
		if (!iface->receive_message(write_memory, TIMEOUT))
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
	CAN_message read_memory = make_command(CANID_READ_MEMORY, target, 7);
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
	if (!iface->set_filter(CANID_READ_MEMORY, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(read_memory, TIMEOUT))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receive_message(read_memory, TIMEOUT))
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
	if (!iface->set_filter(CANID_READ_DATA, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	bool verified = true;
	for (int i = 0; i < number_of_messages; i++)
	{
		if (!iface->receive_message(read_memory, TIMEOUT))
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
		read_memory = make_command(CANID_READ_DATA, target, 1);
		//usleep(1*1000);
		if (!iface->send_message(read_memory, TIMEOUT))
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
	CAN_message read_memory = make_command(CANID_READ_MEMORY, target, 7);
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
	if (!iface->set_filter(CANID_READ_MEMORY, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drain_messages())
	{
		return false;
	}
	if (!iface->send_message(read_memory, TIMEOUT))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receive_message(read_memory, TIMEOUT))
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
	if (!iface->set_filter(CANID_READ_DATA, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	for (int i = 0; i < number_of_messages; i++)
	{
		if (!iface->receive_message(read_memory, TIMEOUT))
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
		read_memory = make_command(CANID_READ_DATA, target, 1);
		//usleep(1*1000);bool check_reply(CAN_message& msg);
		if (!iface->send_message(read_memory, TIMEOUT))
		{
			std::cerr << "Failed to send acknowledgement for message: " << i << std::endl;
			return false;
		}
	}
	return true;
}

bool CAN_module::reset_device(bool run_application)
{
	CAN_message reset_message = make_command(CANID_REQUEST_RESET, target, 2);
	reset_message.get_content()[1] = run_application ? 1 : 0;
	if (! iface->drain_messages())
	{
		return false;
	}
	if (!iface->clear_filter())
	{
		return false;
	}
	if (!iface->set_filter(CANID_REQUEST_RESET, CAN_network_interface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->send_message(reset_message, TIMEOUT))
	{
		return false;
	}
	if (!iface->receive_message(reset_message, TIMEOUT))
	{
		std::cerr << "Warning did not receive reset reply." << std::endl;
	}
	else
	{
		if (reset_message.get_id() != CANID_REQUEST_RESET)
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
	if (!iface->set_filter(CANID_HOST_ALERT, CAN_network_interface::INCLUDE))
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
