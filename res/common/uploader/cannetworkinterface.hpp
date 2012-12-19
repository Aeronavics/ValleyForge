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

/**
 *
 * 
 *  @file		cannetworkinterface.hpp
 *  A header file for the abstract base class for CAN Network interfaces.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		5-12-2012
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
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
#ifndef CANNETWORKINTERFACE_H_
#define CANNETWORKINTERFACE_H_

// INCLUDE REQUIRED HEADER FILES.

#include <set>
#include <string>
#include <stdint.h>
#include <deque>
#include "util.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

typedef std::set<uint32_t> FilterSet;

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

/**
 *  A CAN message class, this class represents a CAN message that could be received or transmitted over a CAN network.
 * 
 */
class CANMessage
{
public:
	
	// Functions.
	CANMessage();
	CANMessage( uint32_t id, size_t length, uint8_t* data);
	
	const uint8_t* getData() const;
	size_t getLength() const;
	uint32_t getId() const;
	
	void setLength(size_t newLength);
	void setId(uint32_t newId);
	uint8_t* getContent();
	
private:
	
	// Functions.
	
	// Fields.
	uint32_t id;
	size_t length;
	uint8_t data[8];
};

/**
 * A queue of CAN Messages.
 */
typedef std::deque<CANMessage> CANMessageQueue;

/**
 *  This class implements a generic can network interface.
 */
class CANNetworkInterface
{
public:

	enum action
	{
		INCLUDE,
		EXCLUDE
	};
	
	enum mode
	{
		INCLUDE_ALL,
		EXCLUDE_ALL_BUT_FILTER,
		INCLUDE_ALL_BUT_FILTER
	};

	// Functions.
	CANNetworkInterface();
	virtual ~CANNetworkInterface()=0;
	
	/**
	 * This method is called to initialise the can network interface, typical parameters are things like bitrate and termination resistance being on.
	 */
	virtual bool init(Params params)=0;
	
	/**
	 * This method is called to send a single CANMessage, a timeout is supplied for waiting for successful transmission.
	 * Returns true on success and false on failure.
	 * If it returns false it does not necessarily mean that the message wont be sent in future.
	 */
	virtual bool sendMessage(const CANMessage& msg, uint32_t timeout)=0;
	/**
	 * This method is called to receive a can message, a timeout is supplied to allow it to not block indefinately.
	 * It returns true if a message was received and false on failure.
	 */
	virtual bool receiveMessage( CANMessage& msg, uint32_t timeout)=0;
	/**
	 * This method will dump all the messages from the received messages queue.
	 * Returns true on success and false on failure.
	 */
	virtual bool drainMessages()=0;
	
	/**
	 * Sets a filter to include or exclude certain ID's from being received.
	 */
	virtual bool setFilter( uint32_t id, action act);
	/**
	 * Sets the default action for things not found in a filter.
	 * If INCLUDE_ALL is given it will ignore all filtering.
	 * If INCLUDE_ALL_BUT_FILTER is given it will use only the exclusion filter.
	 * If EXCLUDE_ALL_BUT_FILTER is given it will use only the inclusion filter.
	 */
	virtual bool setFilterMode( mode m);
	/**
	 * Remove a filter on an ID.
	 */
	virtual bool removeFilter( uint32_t id);
	/**
	 * Clear all filters.
	 */
	virtual bool clearFilter();
	
	
	
protected:
	// Functions.
	/**
	 * Returns true if the message is to be allowed, false if it is to be dropped.
	 */
	virtual bool filter(uint32_t id);
	
	//Fields.
	FilterSet inclusionFilter;
	FilterSet exclusionFilter;
	mode filterMode;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*CANNETWORKINTERFACE_H_*/
