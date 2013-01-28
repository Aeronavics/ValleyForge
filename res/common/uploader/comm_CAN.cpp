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

static CANModule module;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

CANMessage makeCommand(uint32_t id, uint8_t target, size_t length);
bool checkReply(CANMessage& msg);

// IMPLEMENT PUBLIC FUNCTIONS.

CANModule::CANModule() :
	CommModule("can")
{
	
}

CANModule::~CANModule()
{
	delete iface;
}

bool CANModule::init(Params params)
{
	connected = false;
	bool haveCANType = false;
	std::string canType;
	bool haveTarget = false;
	if (params.find("can-type") != params.end())
	{
		canType = params["can-type"];
		haveCANType = true;
	}
	if (params.find("target") != params.end())
	{
		haveTarget = true;
		char* end;
		target = strtoul(params["target"].c_str(), &end, 16);
		if ((end - params["target"].c_str()) != params["target"].length())
		{
			//std::cerr << *end << std::endl;
			std::cerr << "Invalid target node ID" << std::endl;
			return false;
		}
	}
	if (haveCANType)
	{
		if (canType == "socket")
		{
			iface = new SocketCANNetworkInterface;
		}
		if (canType == "microchip")
		{
			iface = new MicrochipCANNetworkInterface;
		}
	}
	else
	{
		iface = new MicrochipCANNetworkInterface;
	}
	if (!haveTarget)
	{
		std::cerr << "No target node ID given." << std::endl;
		return false;
	}
	if (!iface->init(params))
	{
		std::cerr << "Failed To init Network interface" << std::endl;
		return false;
	}
	if (!iface->setFilterMode(CANNetworkInterface::EXCLUDE_ALL_BUT_FILTER))
	{
		std::cerr << "Failed to set filter mode" << std::endl;
		return false;
	}
	if (!iface->clearFilter())
	{
		std::cerr << "Failed to clear filters." << std::endl;
	}
	//~ if (!iface->setFilter(HOST_ALERT, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->setFilter(REQUEST_RESET, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->setFilter(GET_INFO, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->setFilter(WRITE_MEMORY, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->setFilter(WRITE_DATA, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->setFilter(READ_MEMORY, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	//~ if (!iface->setFilter(READ_DATA, CANNetworkInterface::INCLUDE))
	//~ {
		//~ std::cerr << "Failed to set filter" << std::endl;
		//~ return false;
	//~ }
	
	return resetDevice(false);
}

bool CANModule::connectToDevice()
{
	CANMessage msg;
	if (!iface->setFilter(HOST_ALERT, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->receiveMessage(msg, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply." << std::endl;
		return false;
	}
	if (msg.getId() == 0x2FF)
	{
		
		DeviceInfo temp;
		if (getDeviceInfo(temp))
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

bool CANModule::getDeviceInfo( DeviceInfo& info)
{
	CANMessage getInfo = makeCommand(GET_INFO, target, 1);
	if (!iface->clearFilter())
	{
		return false;
	}
	
	if (!iface->setFilter(GET_INFO, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drainMessages())
	{
		return false;
	}
	if (!iface->sendMessage(getInfo, TIMEOUT*1000))
	{
		return false;
	}
	if (!iface->receiveMessage(getInfo, TIMEOUT*1000))
	{
		return false;
	}
	if (getInfo.getId() != GET_INFO || getInfo.getLength() < 6)
	{
		return false;
	}
	info.setName("CAN Bootloader");
	const uint8_t* data = getInfo.getData();
	uint32_t signature = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
	info.setSignature(signature);
	info.setVersionMajor(data[4]);
	info.setVersionMinor(data[5]);
	return true;
}

bool CANModule::writePage(MemoryMap& source, size_t size, size_t address)
{
	CANMessage writeMemory = makeCommand(WRITE_MEMORY, target, 7);
	uint8_t* data = writeMemory.getContent();
	data[1] = (address >> 24) & 0xFF;
	data[2] = (address >> 16) & 0xFF;
	data[3] = (address >> 8) &0xFF;
	data[4] = (address) & 0xFF;
	data[5] = (size >> 8) &0xFF;
	data[6] = (size) & 0xFF;
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(WRITE_MEMORY, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drainMessages())
	{
		return false;
	}
	if (!iface->sendMessage(writeMemory, TIMEOUT*1000))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receiveMessage(writeMemory, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply" << std::endl;
		return false;
	}
	if (!checkReply(writeMemory))
	{
		std::cerr << "Reply indicates failure, WritePage" << std::endl;
		return false;
	}
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(WRITE_DATA, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	size_t remaining = size;
	size_t currentMessage = 0;
	while (remaining > 0)
	{
		//std::cout << "Sending Message: " << currentMessage << std::endl;
		size_t packetSize = (remaining > 7) ? 7 : remaining;
		writeMemory = makeCommand(WRITE_DATA, target, packetSize+1);
		for (size_t j = 0; j < packetSize; j++)
		{
			if (source.getAllocatedMap()[address+(currentMessage*7)+j] == MemoryMap::ALLOCATED)
			{
				writeMemory.getContent()[j+1] = source.getMemory()[address+(currentMessage*7)+j];
			}
			else
			{
				writeMemory.getContent()[j+1] = 0xFF;
			}
		}
		
		if (!iface->sendMessage(writeMemory, TIMEOUT*1000))
		{
			std::cerr << "Failed to send data packet: " << currentMessage << std::endl;
			return false;
		}
		if (!iface->receiveMessage(writeMemory, TIMEOUT*1000))
		{
			std::cerr << "Failed to receive message acknowledge, WritePage: " << currentMessage << std::endl;
			return false;
		}
		if (!checkReply(writeMemory))
		{
			std::cerr << "Acknowledge indicates failure:" << currentMessage << std::endl;
			return false;
		}
		remaining -= packetSize;
		currentMessage++;
	}
	return true;
}

bool CANModule::verifyPage(MemoryMap& expected, size_t size, size_t address)
{
	CANMessage readMemory = makeCommand(READ_MEMORY, target, 7);
	uint8_t* data = readMemory.getContent();
	data[1] = (address >> 24) & 0xFF;
	data[2] = (address >> 16) & 0xFF;
	data[3] = (address >> 8) &0xFF;
	data[4] = (address) & 0xFF;
	data[5] = (size >> 8) & 0xFF;
	data[6] = (size) & 0xFF;
	
	int numberOfMessages = (size/8);
	//std::cout << numberOfMessages << std::endl;
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(READ_MEMORY, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drainMessages())
	{
		return false;
	}
	if (!iface->sendMessage(readMemory, TIMEOUT*1000))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receiveMessage(readMemory, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply" << std::endl;
		return false;
	}
	if (!checkReply(readMemory))
	{
		std::cerr << "Reply indicates failure, VerifyPage" << std::endl;
		return false;
	}
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(READ_DATA, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	bool verified = true;
	for (int i = 0; i < numberOfMessages; i++)
	{
		if (!iface->receiveMessage(readMemory, TIMEOUT*1000))
		{
			std::cerr << "Failed to receive message: " << i << std::endl;
			return false;
		}
		for (size_t j = 0; j < readMemory.getLength(); j++)
		{
			//std::cout << "Verifying address: " << (address+(i*8)+j) << std::endl;
			if (expected.getAllocatedMap()[address+(i*8)+j] == MemoryMap::ALLOCATED)
			{
				if (expected.getMemory()[address+(i*8)+j] != readMemory.getData()[j])
				{
					std::cout << "Verification failed." << std::endl;
					verified = false;
				}
			}
		}
		readMemory = makeCommand(READ_DATA, target, 1);
		//usleep(1*1000);
		if (!iface->sendMessage(readMemory, TIMEOUT*1000))
		{bool checkReply(CANMessage& msg);
			std::cerr << "Failed to send acknowledgement for message: " << i << std::endl;
			return false;
		}
	}
	return verified;
}

bool CANModule::readPage(MemoryMap& destination, size_t size, size_t address)
{
	CANMessage readMemory = makeCommand(READ_MEMORY, target, 7);
	uint8_t* data = readMemory.getContent();
	data[1] = (address >> 24) & 0xFF;
	data[2] = (address >> 16) & 0xFF;
	data[3] = (address >> 8) &0xFF;
	data[4] = (address) & 0xFF;
	data[5] = (size >> 8) & 0xFF;
	data[6] = (size) & 0xFF;
	int numberOfMessages = (size/8);
	//std::cout << numberOfMessages << std::endl;
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(READ_MEMORY, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->drainMessages())
	{
		return false;
	}
	if (!iface->sendMessage(readMemory, TIMEOUT*1000))
	{
		std::cerr << "Failed to send read memory command" << std::endl;
		return false;
	}
	if (!iface->receiveMessage(readMemory, TIMEOUT*1000))
	{
		std::cerr << "Failed to receive reply" << std::endl;
		return false;
	}
	if (!checkReply(readMemory))
	{
		std::cerr << "Reply indicates failure, ReaDPage" << std::endl;
		return false;
	}
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(READ_DATA, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	for (int i = 0; i < numberOfMessages; i++)
	{
		if (!iface->receiveMessage(readMemory, TIMEOUT*1000))
		{
			std::cerr << "Failed to receive message: " << i << std::endl;
			return false;
		}
		for (size_t j = 0; j < readMemory.getLength(); j++)
		{
			//std::cout << "Writing to address: " << (address+(i*8)+j) << std::endl;
			destination.getMemory()[address+(i*8)+j] = readMemory.getData()[j];
			destination.getAllocatedMap()[address+(i*8)+j] = MemoryMap::ALLOCATED;
		}
		readMemory = makeCommand(READ_DATA, target, 1);
		//usleep(1*1000);bool checkReply(CANMessage& msg);
		if (!iface->sendMessage(readMemory, TIMEOUT*1000))
		{
			std::cerr << "Failed to send acknowledgement for message: " << i << std::endl;
			return false;
		}
	}
	return true;
}

bool CANModule::resetDevice(bool runApplication)
{
	CANMessage resetMessage = makeCommand(REQUEST_RESET, target, 2);
	resetMessage.getContent()[1] = runApplication ? 1 : 0;
	if (! iface->drainMessages())
	{
		return false;
	}
	if (!iface->clearFilter())
	{
		return false;
	}
	if (!iface->setFilter(REQUEST_RESET, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	if (!iface->sendMessage(resetMessage, TIMEOUT*1000))
	{
		return false;
	}
	if (!iface->receiveMessage(resetMessage, TIMEOUT*1000))
	{
		std::cerr << "Warning did not receive reset reply." << std::endl;
	}
	else
	{
		if (resetMessage.getId() != REQUEST_RESET)
		{
			std::cerr << "Did not receive reset confirmation instead received something else." << std::endl;
			return false;
		}
		else
		{
			if (!checkReply(resetMessage))
			{
				std::cerr << "Reset reply indicates failure." << std::endl;
				return false;
			}
		}
	}
	if (!iface->clearFilter())
	{
		return false;
	}
	if (! iface->drainMessages())
	{
		return false;
	}
	if (runApplication)
	{
		return true;
	}
	if (!iface->setFilter(HOST_ALERT, CANNetworkInterface::INCLUDE))
	{
		std::cerr << "Failed to set filter" << std::endl;
		return false;
	}
	return connectToDevice();
}

CANMessage makeCommand(uint32_t id, uint8_t target, size_t length)
{
	CANMessage msg;
	msg.setId(id);
	msg.setLength(length);
	msg.getContent()[0]=target;
	return msg;
}

bool checkReply(CANMessage& msg)
{
	if (msg.getLength() < 1)
	{
		return false;
	}
	return msg.getData()[0] != 0;
}
