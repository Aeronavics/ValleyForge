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
 *  @file		comm_CAN.hpp
 *  A header file for the CAN communications module.
 *  This module implements the CAN bootloader protocol and allows uploading firmware to a particular device on the CAN network.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		6-12-2012
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
#ifndef __COMM_CAN_H__
#define __COMM_CAN_H__

// INCLUDE REQUIRED HEADER FILES.

#include "cannetworkinterface.hpp"
#include "comm.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.


class CAN_module : public Comm_module
{
public:

	// Functions.
	CAN_module();
	virtual ~CAN_module();
	
	virtual bool init(Params params);
	virtual bool connect_to_device();
	
	virtual bool get_device_info( Device_info& info);
	
	virtual bool write_page(Memory_map& source, size_t size, size_t address);
	virtual bool verify_page(Memory_map& expected, size_t size, size_t address);
	virtual bool read_page(Memory_map& destination, size_t size, size_t address);
	
	virtual bool reset_device(bool run_application);
	
	
private:
	// Functions.
	
	//Fields.
	bool connected;
	uint8_t target;
	CAN_network_interface* iface;
	
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__COMM_CAN_H__*/

//ALL DONE.
