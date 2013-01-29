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
#ifndef __CANNETWORKINTERFACE_H__
#define __CANNETWORKINTERFACE_H__

// INCLUDE REQUIRED HEADER FILES.

#include <deque>
#include <set>
#include <string>

#include <stdint.h>


#include "util.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

typedef std::set<uint32_t> Filter_set;

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

/**
 *  A CAN message class, this class represents a CAN message that could be received or transmitted over a CAN network.
 * 
 */
class CAN_message
{
public:
	
	// Functions.
	CAN_message();
	CAN_message( uint32_t id, size_t length, uint8_t* data);
	
	const uint8_t* get_data() const;
	size_t get_length() const;
	uint32_t get_id() const;
	
	void set_length(size_t new_length);
	void set_id(uint32_t new_id);
	uint8_t* get_content();
	
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
typedef std::deque<CAN_message> CAN_message_queue;

/**
 *  This class implements a generic can network interface.
 */
class CAN_network_interface
{
public:

	enum Action
	{
		INCLUDE,
		EXCLUDE
	};
	
	enum Mode
	{
		INCLUDE_ALL,
		EXCLUDE_ALL_BUT_FILTER,
		INCLUDE_ALL_BUT_FILTER
	};

	// Functions.
	CAN_network_interface();
	virtual ~CAN_network_interface()=0;
	
	/**
	 * This method is called to initialise the can network interface, typical parameters are things like bitrate and termination resistance being on.
	 */
	virtual bool init(Params params)=0;
	
	/**
	 * This method is called to send a single CAN_message, a timeout is supplied for waiting for successful transmission.
	 * Returns true on success and false on failure.
	 * If it returns false it does not necessarily mean that the message wont be sent in future.
	 */
	virtual bool send_message(const CAN_message& msg, uint32_t timeout)=0;
	/**
	 * This method is called to receive a can message, a timeout is supplied to allow it to not block indefinately.
	 * It returns true if a message was received and false on failure.
	 */
	virtual bool receive_message( CAN_message& msg, uint32_t timeout)=0;
	/**
	 * This method will dump all the messages from the received messages queue.
	 * Returns true on success and false on failure.
	 */
	virtual bool drain_messages()=0;
	
	/**
	 * Sets a filter to include or exclude certain ID's from being received.
	 */
	virtual bool set_filter( uint32_t id, Action act);
	/**
	 * Sets the default action for things not found in a filter.
	 * If INCLUDE_ALL is given it will ignore all filtering.
	 * If INCLUDE_ALL_BUT_FILTER is given it will use only the exclusion filter.
	 * If EXCLUDE_ALL_BUT_FILTER is given it will use only the inclusion filter.
	 */
	virtual bool set_filter_mode( Mode m);
	/**
	 * Remove a filter on an ID.
	 */
	virtual bool remove_filter( uint32_t id);
	/**
	 * Clear all filters.
	 */
	virtual bool clear_filter();
	
	
	
protected:
	// Functions.
	/**
	 * Returns true if the message is to be allowed, false if it is to be dropped.
	 */
	virtual bool filter(uint32_t id);
	
	//Fields.
	Filter_set inclusion_filter;
	Filter_set exclusion_filter;
	Mode filter_mode;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__CANNETWORKINTERFACE_H__*/

//ALL DONE.
