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
#include <vector>

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
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

#define SET_ATOMIC(var) (__sync_bool_compare_and_swap(&(var), false, true))
#define RESET_ATOMIC(var) (__sync_bool_compare_and_swap(&(var), true, false))

// DEFINE PRIVATE TYPES AND STRUCTS.

class libUSB_context_holder
{
public:
	libUSB_context_holder()
	{
		if (libusb_init(&context) != 0)
		{
			std::cerr << "Failed to initialise libusb." << std::endl;
			exit(1);
		}
	}
	~libUSB_context_holder()
	{
		libusb_exit(context);
	}
	
	libusb_context* get_context()
	{
		return context;
	}
private:
	libusb_context* context;
};

class USB_message
{
public:
	USB_message() :
		content(MESSAGE_LENGTH, 0)
	{
	}
	USB_message(uint8_t* buffer, size_t length) :
		content(buffer, buffer+length)
	{		
	}
	
	std::vector<uint8_t>& get_content()
	{
		return content;
	}
	
	void set_checksum(uint8_t checksum)
	{
		content[MESSAGE_CHECKSUM_LOCATION] = checksum;
	}
	
	uint8_t calculate_checksum()
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

typedef std::deque<USB_message> Message_queue;

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.
CAN_message parse_received_CAN_message(USB_message& m);
void print_buffer(uint8_t* buffer, size_t length);
std::string message_name(uint8_t command);
uint32_t parse_id(uint8_t* buffer);
void unparse_id(uint32_t id, uint8_t* buffer, bool extended);
void print_message(uint8_t* buffer, size_t length);
bool send_USB_message(USB_message& msg, libusb_device_handle* device);

// IMPLEMENT PUBLIC FUNCTIONS.



Microchip_CAN_network_interface::Microchip_CAN_network_interface() :
	recv_queue_lock(PTHREAD_MUTEX_INITIALIZER),
	CAN_device(NULL),
	quit(false),
	drain(false),
	transmitted(false),
	overflow(false),
	inited(false)
{
	ctx_holder = new libUSB_context_holder;
}

Microchip_CAN_network_interface::~Microchip_CAN_network_interface()
{
	SET_ATOMIC(quit);
	if (inited)
	{
		pthread_join(USB_thread, NULL);
	}
	if (CAN_device)
	{
		libusb_close(CAN_device);
	}
	delete ctx_holder;
}

bool Microchip_CAN_network_interface::init(Params params)
{
	index = 0;
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
	libusb_context* ctx = ctx_holder->get_context();
	CAN_device = libusb_open_device_with_vid_pid(ctx, VID, PID);
	if (CAN_device == NULL)
	{
		std::cerr << "Device could not be found or an error occurred." << std::endl;
		return false;
	}
	
	if (libusb_reset_device(CAN_device))
	{
		std::cerr << "Device re-enumerates on reset." << std::endl;
		return false;
	}
	
	if (libusb_claim_interface(CAN_device, 0))
	{
		std::cerr << "Could not claim interface on device, is something else using it?" << std::endl;
		return false;
	}
	
	int rc = pthread_create(&USB_thread, NULL, USB_thread_func, (void*) this);
	if (rc != 0)
	{
		return false;
	}
	
	USB_message msg;
	
	//Change bitrate command.
	msg.get_content()[0] = CHANGE_BIT_RATE;
	msg.get_content()[1] = (bitrate >> 8) & 0xFF;
	msg.get_content()[2] = (bitrate) & 0xFF;
	msg.set_checksum(msg.calculate_checksum());

	if (!send_USB_message(msg, CAN_device))
	{
		std::cerr << "Could not send bitrate change message" << std::endl;
	}
	
	//Change mode command.
	msg.get_content()[0] = CHANGE_CAN_MODE;
	msg.get_content()[1] = CAN_MODE_NORMAL;
	msg.set_checksum(msg.calculate_checksum());

	if (!send_USB_message(msg, CAN_device))
	{
		std::cerr << "Could not send mode change message" << std::endl;
	}
	
		//Change mode command.
	msg.get_content()[0] = SETUP_TERMINATION_RESISTANCE;
	msg.get_content()[1] = termination ? 0 : 1;
	msg.set_checksum(msg.calculate_checksum());

	if (!send_USB_message(msg, CAN_device))
	{
		std::cerr << "Could not send termination change message" << std::endl;
	}
	
	SET_ATOMIC(drain);
	usleep(500000);
	RESET_ATOMIC(drain);
	
	//std::cout << "Sleeping" << std::endl;
	usleep(500000);
	//std::cout << "Waking" << std::endl;
	
	inited = true;
	
	return true;
}
	
bool Microchip_CAN_network_interface::send_message(const CAN_message& msg, uint32_t timeout)
{
	USB_message sendMessage;
	timeval start, now;
	//Transmit Message command.
	sendMessage.get_content()[0] = TRANSMIT_MESSAGE_EV;
	char buf[9];
	snprintf(buf, 9, "%X", msg.get_id());
	buf[8] = '\0';
	//std::cerr << "ID: " << buf << ", ";
	unparse_id(msg.get_id(), &(sendMessage.get_content()[1]), false);
	//std::cerr << "Length: " << msg.getLength() << std::endl;
	sendMessage.get_content()[DLC] = msg.get_length();
	for (size_t i = 0; i < msg.get_length(); i++)
	{
		sendMessage.get_content()[DATA_START+i] = msg.get_data()[i];
	}
	sendMessage.get_content()[INDEX] = index++;
	if (index > 2)
	{
		index = 0;
	}
	sendMessage.set_checksum(sendMessage.calculate_checksum());
	send_USB_message(sendMessage, CAN_device);
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
	RESET_ATOMIC(transmitted);
	return true;
}


bool Microchip_CAN_network_interface::receive_message( CAN_message& msg, uint32_t timeout)
{
	if (__sync_fetch_and_add(&overflow, 0))
	{
		drain_messages();
		RESET_ATOMIC(overflow);
		return false;
	}
		
	timeval start, now;
	gettimeofday(&start, NULL);
	while (recv_queue.empty())
	{
		gettimeofday(&now, NULL);
		uint32_t msec = (now.tv_usec - start.tv_usec)/1000;
		msec += (now.tv_sec - start.tv_sec)*1000;
		if (msec > timeout )
		{
			return false;
		}
	}
	pthread_mutex_lock( &recv_queue_lock );
	msg = recv_queue.front();
	recv_queue.pop_front();
	pthread_mutex_unlock( &recv_queue_lock);
	return true;
	
}

bool Microchip_CAN_network_interface::drain_messages()
{
	pthread_mutex_lock( &recv_queue_lock );
	recv_queue.clear();
	pthread_mutex_unlock( &recv_queue_lock );
	return true;
}

// IMPLEMENT PRIVATE FUNCTIONS.

void* Microchip_CAN_network_interface::USB_thread_func(void* param)
{
	Microchip_CAN_network_interface* obj = static_cast<Microchip_CAN_network_interface*> (param);
	Message_queue message_queue;
	while (__sync_fetch_and_add(&obj->quit, 0) == 0)
	{
		obj->process_USB_events(&message_queue);
	}
	return 0;
}

void Microchip_CAN_network_interface::process_USB_events(void* m)
{
	uint8_t buffer[IN_ENDPOINT_READ_SIZE];
	size_t length = 0;
	int transferred;
	Message_queue& message_queue = *(static_cast<Message_queue*>(m));
	
	
	int rc ;
	if ((rc = libusb_bulk_transfer(CAN_device, IN_ENDPOINT, buffer+length, IN_ENDPOINT_READ_SIZE, &transferred, 500)))
		{
			std::cerr << "Could not read from the in endpoint: " << libusb_error_name(rc) << std::endl;
			perror("Actual Error");
			SET_ATOMIC(quit);
			return;
		}
		
		//std::cout << "Transferred: " << transferred << std::endl;
		if ((transferred % MESSAGE_LENGTH == 0) & !__sync_fetch_and_add(&drain,0))
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
					message_queue.push_back(USB_message(buffer+curPos, MESSAGE_LENGTH));
				}
				curPos += MESSAGE_LENGTH;
			}
			
			memmove(buffer, buffer+curPos, length-curPos);
			length = length - curPos;
		}
		
		int processed = 0;
		
		while (!message_queue.empty() && processed < 10)
		{
			//std::cout << "Processing: " << processed << std::endl;
			USB_message m = message_queue.front();
			message_queue.pop_front();
			//printBuffer(&(m.get_content()[0]), m.get_content().size());
			print_message(&(m.get_content()[0]), m.get_content().size());
			process_message(m);
			processed++;
		}
		
		
}

void Microchip_CAN_network_interface::process_message(USB_message& m)
{
	if (m.get_content()[0] == RECEIVE_MESSAGE)
	{
		pthread_mutex_lock( &recv_queue_lock);
		CAN_message msg = parse_received_CAN_message(m);
		if (filter(msg.get_id()))
		{
			//std::cout << "Received" << std::endl;
			recv_queue.push_back(msg);
		}
		pthread_mutex_unlock( &recv_queue_lock);
	}
	if (m.get_content()[0] == TRANSMIT_MESSAGE_RESPONSE)
	{
		SET_ATOMIC(transmitted);
	}
	if (m.get_content()[0] == CAN_ALIVE)
	{
		if (m.get_content()[3])
		{
			//std::cout << "Overflow" << std::endl;
			SET_ATOMIC(overflow);
		}
	}
}

CAN_message parse_received_CAN_message(USB_message& m)
{
	uint32_t id = parse_id(&(m.get_content()[1]));
	size_t length = m.get_content()[5];
	uint8_t data[8];
	for (size_t i = 0; i < length; i++)
	{
		data[i] = m.get_content()[6+i];
	}
	return CAN_message(id, length, &data[0]);
}

void print_buffer(uint8_t* buffer, size_t length)
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

std::string message_name(uint8_t command)
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

uint32_t parse_id(uint8_t* buffer)
{
	bool is_extended_id = false;
	uint8_t eIdHi = (*buffer);
	buffer++;
	uint8_t eIdLo = (*buffer);
	buffer++;
	uint8_t sIdHi = (*buffer);
	buffer++;
	uint8_t sIdLo = (*buffer);
	
	is_extended_id = (eIdLo & 0x08) == 0x08;
	uint32_t id;
	
	//This is done regardless.
	id = sIdHi;
	id <<= 3;
	id |= (sIdLo >> 5) & 0x07;
	
	if (is_extended_id)
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

void unparse_id(uint32_t id, uint8_t* buffer, bool extended)
{
	uint8_t eIdHi = 0;
	uint8_t eIdLo = 0;
	uint8_t sIdHi = 0;
	uint8_t sIdLo = 0;
	
	if (extended)
	{
		//TODO: Currently we do not handle extended IDs, in future these would be expanded to the microchip form here.
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

//This is a debugging function.
void print_message(uint8_t* buffer, size_t length)
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
				snprintf(buf, 9, "%X", parse_id(buffer+1));
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

bool send_USB_message(USB_message& msg, libusb_device_handle* device)
{
	int transferred;
	if(libusb_bulk_transfer(device, OUT_ENDPOINT, &(msg.get_content()[0]), msg.get_content().size(), &transferred, 500))
	{
		std::cerr << "Failed to send message to CAN device." << std::endl;
		return false;
	}
	if (transferred != msg.get_content().size())
	{
		std::cerr << "Right number of bytes not sent to CAN device, sent: " << transferred << " Expected to send: " << msg.get_content().size() << std::endl;
		return false;
	}
	return true;
}

//ALL DONE.
