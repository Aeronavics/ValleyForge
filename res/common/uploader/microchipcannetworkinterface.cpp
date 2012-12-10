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
 *  FILE: 		microchipcannetworkinterface.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		CAN Interface
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	5-12-2012
 *
 *	Implementation of the common functions for the Microchip CAN Network Interface
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "microchipcannetworkinterface.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.
#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>


// DEFINE PRIVATE MACROS.

#define VID	0x04D8
#define PID	0x0A30

#define IN_ENDPOINT		0x81
#define OUT_ENDPOINT	0x01

#define MESSAGE_LENGTH 19
#define MESSAGE_CHECKSUM_LOCATION 18

#define IN_ENDPOINT_READ_SIZE (MESSAGE_LENGTH*90)

#define CAN_ALIVE 0xF5
#define USB_ALIVE 0xF7
#define RECEIVE_MESSAGE 0xE3
#define TRANSMIT_MESSAGE_RESPONSE 0xE2

#define CHANGE_BIT_RATE 0xA1
#define TRANSMIT_MESSAGE_EV 0xA3
#define CHANGE_CAN_MODE 0xAB
#define SETUP_TERMINATION_RESISTANCE 0xA8

#define CAN_MODE_CONFIG 1
#define CAN_MODE_NORMAL 2
#define CAN_MODE_LISTEN_ONLY 3

#define EIDH 1
#define EIDL 2
#define SIDH 3
#define SIDL 4
#define DLC 5
#define DATA_START 6
#define DATA_END 13
#define INDEX 14

// DEFINE PRIVATE TYPES AND STRUCTS.

class libUSBContextHolder
{
public:
	libUSBContextHolder()
	{
		if (libusb_init(&context) != 0)
		{
			std::cerr << "Failed to initialise libusb." << std::endl;
			exit(1);
		}
	}
	~libUSBContextHolder()
	{
		libusb_exit(context);
	}
	
	libusb_context* getContext()
	{
		return context;
	}
private:
	libusb_context* context;
};

class USBMessage
{
public:
	USBMessage() :
		content(MESSAGE_LENGTH, 0)
	{
	}
	USBMessage(uint8_t* buffer, size_t length) :
		content(buffer, buffer+length)
	{		
	}
	
	std::vector<uint8_t>& getContent()
	{
		return content;
	}
	
	void setChecksum(uint8_t checksum)
	{
		content[MESSAGE_CHECKSUM_LOCATION] = checksum;
	}
	
	uint8_t calculateChecksum()
	{
		uint8_t checksum = 0;
		for (size_t i = 0; i < MESSAGE_CHECKSUM_LOCATION; i++)
		{
			checksum += content[i];
		}
		return checksum;
	}
	
private:
	std::vector<uint8_t> content;
};

typedef std::deque<USBMessage> MessageQueue;

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.
CANMessage parseReceivedCANMessage(USBMessage& m);
void printBuffer(uint8_t* buffer, size_t length);
std::string messageName(uint8_t command);
uint32_t parseId(uint8_t* buffer);
void unparseId(uint32_t id, uint8_t* buffer, bool extended);
void printMessage(uint8_t* buffer, size_t length);
bool sendUSBMessage(USBMessage& msg, libusb_device_handle* device);

// IMPLEMENT PUBLIC FUNCTIONS.



MicrochipCANNetworkInterface::MicrochipCANNetworkInterface() :
	CANDevice(NULL),
	quit(0),
	recvQueueLock(PTHREAD_MUTEX_INITIALIZER)
{
	ctxHolder = new libUSBContextHolder;
}

MicrochipCANNetworkInterface::~MicrochipCANNetworkInterface()
{
	__sync_fetch_and_add(&quit, 1);
	int rc = pthread_join(USBThread, NULL);
	if (CANDevice)
	{
		libusb_close(CANDevice);
	}
	delete ctxHolder;
}

bool MicrochipCANNetworkInterface::init(Params params)
{
	bool haveBitrate = false;
	int bitrate = 1000;
	bool termination= false;
	std::string bitrateStr;
	if (params.find("bitrate") != params.end())
	{
		bitrateStr = params["bitrate"];
		haveBitrate = true;
	}
	if (haveBitrate)
	{
		bitrate = strtoul(bitrateStr.c_str(), NULL, 10);
		bitrate /= 1000;
	}
	if (params.find("termination") != params.end())
	{
		std::string terminationStr = params["termination"];
		if (terminationStr == "on")
		{
			termination = true;
		}
	}
	libusb_context* ctx = ctxHolder->getContext();
	CANDevice = libusb_open_device_with_vid_pid(ctx, VID, PID);
	if (CANDevice == NULL)
	{
		std::cerr << "Device could not be found or an error occurred." << std::endl;
		return false;
	}
	
	if (libusb_reset_device(CANDevice))
	{
		std::cerr << "Device re-enumerates on reset." << std::endl;
		return false;
	}
	
	if (libusb_claim_interface(CANDevice, 0))
	{
		std::cerr << "Could not claim interface on device, is something else using it?" << std::endl;
		return false;
	}
	
	int rc = pthread_create(&USBThread, NULL, USBThreadFunc, (void*) this);
	if (rc != 0)
	{
		return false;
	}
	
	USBMessage msg;
	
	//Change bitrate command.
	msg.getContent()[0] = CHANGE_BIT_RATE;
	msg.getContent()[1] = (bitrate >> 8) & 0xFF;
	msg.getContent()[2] = (bitrate) & 0xFF;
	msg.setChecksum(msg.calculateChecksum());

	if (!sendUSBMessage(msg, CANDevice))
	{
		std::cerr << "Could not send bitrate change message" << std::endl;
	}
	
	//Change mode command.
	msg.getContent()[0] = CHANGE_CAN_MODE;
	msg.getContent()[1] = CAN_MODE_NORMAL;
	msg.setChecksum(msg.calculateChecksum());

	if (!sendUSBMessage(msg, CANDevice))
	{
		std::cerr << "Could not send mode change message" << std::endl;
	}
	
		//Change mode command.
	msg.getContent()[0] = SETUP_TERMINATION_RESISTANCE;
	msg.getContent()[1] = termination ? 0 : 1;
	msg.setChecksum(msg.calculateChecksum());

	if (!sendUSBMessage(msg, CANDevice))
	{
		std::cerr << "Could not send termination change message" << std::endl;
	}
	
	__sync_fetch_and_add(&drain,1);
	usleep(500000);
	__sync_fetch_and_add(&drain,-1);
	
	std::cout << "Sleeping" << std::endl;
	usleep(500000);
	std::cout << "Waking" << std::endl;
	
	return true;
}
	
bool MicrochipCANNetworkInterface::sendMessage(const CANMessage& msg, uint32_t timeout)
{
	USBMessage sendMessage;
	
	//Transmit Message command.
	sendMessage.getContent()[0] = TRANSMIT_MESSAGE_EV;
	char buf[9];
	snprintf(buf, 9, "%X", msg.getId());
	buf[8] = '\0';
	std::cerr << "ID: " << buf << ", ";
	unparseId(msg.getId(), &(sendMessage.getContent()[1]), false);
	std::cerr << "Length: " << msg.getLength() << std::endl;
	sendMessage.getContent()[DLC] = msg.getLength();
	for (size_t i = 0; i < msg.getLength(); i++)
	{
		sendMessage.getContent()[DATA_START+i] = msg.getData()[i];
	}
	sendMessage.getContent()[INDEX] = 0;
	sendMessage.setChecksum(sendMessage.calculateChecksum());
	sendUSBMessage(sendMessage, CANDevice);
	timeval start, now;
	gettimeofday(&start, NULL);
	while (!__sync_fetch_and_add(&transmitted, 0))
	{
		gettimeofday(&now, NULL);
		uint32_t msec = (now.tv_usec - start.tv_usec)/1000;
		msec += (now.tv_sec - start.tv_sec)*1000;
		if (msec > timeout )
		{
			return false;
		}
	}
	__sync_fetch_and_add(&transmitted, -1);
	return true;
}


bool MicrochipCANNetworkInterface::receiveMessage( CANMessage& msg, uint32_t timeout)
{
	timeval start, now;
	gettimeofday(&start, NULL);
	while (recvQueue.empty())
	{
		gettimeofday(&now, NULL);
		uint32_t msec = (now.tv_usec - start.tv_usec)/1000;
		msec += (now.tv_sec - start.tv_sec)*1000;
		if (msec > timeout )
		{
			return false;
		}
	}
	pthread_mutex_lock( &recvQueueLock );
	msg = recvQueue.front();
	recvQueue.pop_front();
	pthread_mutex_unlock( &recvQueueLock);
	return true;
	
}

bool MicrochipCANNetworkInterface::drainMessages()
{
	pthread_mutex_lock( &recvQueueLock );
	recvQueue.clear();
	pthread_mutex_unlock( &recvQueueLock );
	return true;
}

// IMPLEMENT PRIVATE FUNCTIONS.

void* MicrochipCANNetworkInterface::USBThreadFunc(void* param)
{
	MicrochipCANNetworkInterface* obj = static_cast<MicrochipCANNetworkInterface*> (param);
	while (__sync_fetch_and_add(&obj->quit, 0) == 0)
	{
		obj->processUSBEvents();
	}
	return 0;
}

void MicrochipCANNetworkInterface::processUSBEvents()
{
	uint8_t buffer[IN_ENDPOINT_READ_SIZE];
	size_t length = 0;
	int transferred;
	//~ timeval now, then;
	//~ int period = 5;
	MessageQueue messageQueue;
	
	//~ USBMessage sendMessage;
	//~ 
	//~ //Transmit Message command.
	//~ sendMessage.getContent()[0] = TRANSMIT_MESSAGE_EV;
	//~ unparseId(0x123, &(sendMessage.getContent()[1]), false);
	//~ sendMessage.getContent()[DLC] = 8;
	//~ sendMessage.getContent()[DATA_START] = 0xDE;
	//~ sendMessage.getContent()[DATA_START+1] = 0xAD;
	//~ sendMessage.getContent()[DATA_START+2] = 0xBE;
	//~ sendMessage.getContent()[DATA_START+3] = 0xEF;
	//~ sendMessage.getContent()[DATA_START+4] = 0xDE;
	//~ sendMessage.getContent()[DATA_START+5] = 0xAD;
	//~ sendMessage.getContent()[DATA_START+6] = 0xCA;
	//~ sendMessage.getContent()[DATA_START+7] = 0xFE;
	//~ sendMessage.getContent()[INDEX] = 1;
	//~ sendMessage.setChecksum(sendMessage.calculateChecksum());
	int rc ;
	if ((rc = libusb_bulk_transfer(CANDevice, IN_ENDPOINT, buffer+length, IN_ENDPOINT_READ_SIZE, &transferred, 500)))
		{
			std::cerr << "Could not read from the in endpoint: " << libusb_error_name(rc) << std::endl;
			perror("Actual Error");
			__sync_fetch_and_add(&quit, 1);
			return;
		}
		
		//std::cout << "Transferred: " << transferred << std::endl;
		if (transferred % MESSAGE_LENGTH == 0 & !__sync_fetch_and_add(&drain,0))
		{
			
			//std::cout << "Got a whole number of messages." << std::endl;
			length += transferred;
			
			size_t curPos = 0;

			while (length - curPos >= MESSAGE_LENGTH)
			{
				//std::cout << "Current Position in buffer: " << curPos << std::endl;
				uint8_t checksum = 0;
				bool allFs = true;
				for ( size_t i = 1; i < MESSAGE_CHECKSUM_LOCATION; i++)
				{
					checksum += buffer[i+curPos];
					if (buffer[i+curPos] != 0xFF)
					{
						allFs = false;
					}
				}
				if (checksum != buffer[MESSAGE_CHECKSUM_LOCATION+curPos])
				{
					if (!allFs)
					{
						//Increase error counter?
						std::cout << "Checksum Error" << std::endl;
						std::cout << "Calculated Checksum: " << (size_t)checksum << std::endl;
						std::cout << "Message Checksum: " << (size_t)buffer[MESSAGE_CHECKSUM_LOCATION+curPos] << std::endl;
					}
				}
				else
				{
					messageQueue.push_back(USBMessage(buffer+curPos, MESSAGE_LENGTH));
				}
				curPos += MESSAGE_LENGTH;
			}
			
			memmove(buffer, buffer+curPos, length-curPos);
			length = length - curPos;
		}
		
		if (!messageQueue.empty())
		{
			USBMessage m = messageQueue.front();
			messageQueue.pop_front();
			//printBuffer(&(m.getContent()[0]), m.getContent().size());
			printMessage(&(m.getContent()[0]), m.getContent().size());
			processMessage(m);
			
		}
		
		//~ gettimeofday(&now, NULL);
		//~ if ( (now.tv_sec > (then.tv_sec + period)) )
		//~ {
			//~ sendUSBMessage(sendMessage, CANDevice);
			//~ then = now;
		//~ }
		
}

void MicrochipCANNetworkInterface::processMessage(USBMessage& m)
{
	if (m.getContent()[0] == RECEIVE_MESSAGE)
	{
		pthread_mutex_lock( &recvQueueLock);
		CANMessage msg = parseReceivedCANMessage(m);
		if (filter(msg.getId()))
		{
			std::cout << "Received" << std::endl;
			recvQueue.push_back(msg);
		}
		pthread_mutex_unlock( &recvQueueLock);
	}
	if (m.getContent()[0] == TRANSMIT_MESSAGE_RESPONSE)
	{
		__sync_fetch_and_add(&transmitted, 1);
	}
}

CANMessage parseReceivedCANMessage(USBMessage& m)
{
	uint32_t id = parseId(&(m.getContent()[1]));
	size_t length = m.getContent()[5];
	uint8_t data[8];
	for (size_t i = 0; i < length; i++)
	{
		data[i] = m.getContent()[6+i];
	}
	return CANMessage(id, length, &data[0]);
}

void printBuffer(uint8_t* buffer, size_t length)
{
	char buf[3];
	for (size_t i = 0; i < length; i++)
	{
		snprintf(buf, 3, "%02X", buffer[i]);
		buf[2] = '\0';
		std::cout << buf << ((i % 16 != 15) ? " " : "\n");
	}
	std::cout << std::endl;
}

std::string messageName(uint8_t command)
{
	switch (command)
	{
		case CAN_ALIVE:
			return "Alive Ping from CAN micro";
			break;
		case USB_ALIVE:
			return "Alive Ping from USB micro";
			break;
		case RECEIVE_MESSAGE:
			return "Received CAN Message";
			break;
		default:
			return "Unknown message type";
			break;
	}
}

uint32_t parseId(uint8_t* buffer)
{
	bool isExtendedId = false;
	uint8_t eIdHi = (*buffer);
	buffer++;
	uint8_t eIdLo = (*buffer);
	buffer++;
	uint8_t sIdHi = (*buffer);
	buffer++;
	uint8_t sIdLo = (*buffer);
	
	isExtendedId = eIdLo & 0x08 == 0x08;
	uint32_t id;
	
	//This is done regardless.
	id = sIdHi;
	id <<= 3;
	id |= (sIdLo >> 5) & 0x07;
	
	if (isExtendedId)
	{
		//If its extended we also put in the bottom 2 bits from the standard ID lo byte and the extended ID bytes as follows.
		id <<= 2;
		id |= (sIdLo & 0x03);
		id <<= 8;
		id |= eIdHi;
		id <<= 8;
		id |= eIdLo;
	}

	return id;
}

void unparseId(uint32_t id, uint8_t* buffer, bool extended)
{
	uint8_t eIdHi = 0;
	uint8_t eIdLo = 0;
	uint8_t sIdHi = 0;
	uint8_t sIdLo = 0;
	
	if (extended)
	{
		
	}
	else
	{
		sIdLo = (id & 0x07) << 5;
		sIdHi = (id >> 3) & 0xFF;
	}
	buffer[0] = eIdHi;
	buffer[1] = eIdLo;
	buffer[2] = sIdHi;
	buffer[3] = sIdLo;
}

void printMessage(uint8_t* buffer, size_t length)
{
	if (length == MESSAGE_LENGTH)
	{
		//~ std::cout << messageName(buffer[0]) << ", ";
		int bitrate;
		std::string mode;
		char buf[9];
		switch (buffer[0])
		{
			//~ case CAN_ALIVE:
				//~ std::cout << "TX Error Count: " << (size_t)buffer[1] << ", ";
				//~ std::cout << "RX Error Count: " << (size_t)buffer[2] << ", ";
				//~ std::cout << "CAN Overflow: " << (buffer[3] ? "Yes" : "No") << ", ";
				//~ std::cout << "Bus Off: " << (buffer[4] ? "Yes" : "No") << ", ";
				//~ bitrate = ((int)buffer[5] << 8) + buffer[6];
				//~ std::cout << "Bitrate: " << bitrate << ", ";
				//~ switch (buffer[9] & 0xE0)
				//~ {
					//~ case 0x60:
						//~ mode = "Listen Only";
						//~ break;
					//~ case 0x80:
						//~ mode = "Config Mode";
						//~ break;
					//~ case 0x00:
						//~ mode = "Normal Mode";
						//~ break;
					//~ default: 
						//~ mode = "Unknown Mode";
				//~ }
				//~ std::cout << "Mode: " << mode << ", ";
				//~ std::cout << "Version Number: " << (size_t)buffer[10] << "." << (size_t)buffer[11] << ", ";
				//~ std::cout << "Debug Mode: " << (buffer[12] ? "On" : "Off");
				//~ std::cout << std::endl;
				//~ break;
			//~ case USB_ALIVE:
				//~ std::cout << "Termination: " << (buffer[1] ? "Off" : "On") << ", ";
				//~ std::cout << "Version Number: " << (size_t)buffer[2] << "." << (size_t)buffer[3];
				//~ std::cout << std::endl;
				//~ break;
			case RECEIVE_MESSAGE:
				std::cout << "ID bytes: ";
				for (size_t i = 0; i < 4; i++)
				{
					snprintf(buf, 3, "%02X", buffer[1+i]);
					buf[2] = '\0';
					std::cout << buf << ((i < 3) ? " " : ", ");
				}
				snprintf(buf, 9, "%X", parseId(buffer+1));
				buf[8] = '\0';
				std::cout << "ID: " << buf << ", ";
				std::cout  << "DLC: " << (size_t)buffer[5] << ", ";
				std::cout << "Data: ";
				for (size_t i = 0; i < (size_t)buffer[5]; i++)
				{
					snprintf(buf, 3, "%02X", buffer[6+i]);
					buf[2] = '\0';
					std::cout << buf << ((i < 7) ? " " : ", ");
					
				}
				std::cout << std::endl;
				break;
			case TRANSMIT_MESSAGE_RESPONSE:
				std::cout << "TransmitResponse" << std::endl;
				break;
			default:
				
				break;
		}
		
		//~ for (size_t i = 0; i < length; i++)
		//~ {
			//~ snprintf(buf, 3, "%02X", buffer[i]);
			//~ buf[2] = '\0';
			//~ std::cout << buf << ((i % 16 != 15) ? " " : "\n");
		//~ }
		//~ std::cout << std::endl;
	}
}

bool sendUSBMessage(USBMessage& msg, libusb_device_handle* device)
{
	int transferred;
	if(libusb_bulk_transfer(device, OUT_ENDPOINT, &(msg.getContent()[0]), msg.getContent().size(), &transferred, 500))
	{
		std::cerr << "Failed to send message to CAN device." << std::endl;
		return false;
	}
	if (transferred != msg.getContent().size())
	{
		std::cerr << "Right number of bytes not sent to CAN device sent: " << transferred << " Expected to send: " << msg.getContent().size() << std::endl;
		return false;
	}
	return true;
}

