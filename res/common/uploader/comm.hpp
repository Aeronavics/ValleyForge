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
 *  @file		comm.hpp
 *  A header file for the abstract base class for comms modules.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		27-11-2012
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
#ifndef __COMM_H__
#define __COMM_H__

// INCLUDE REQUIRED HEADER FILES.

#include <map>
#include <string>

#include <stdint.h>

#include "memory.hpp"
#include "util.hpp"


// DEFINE PUBLIC TYPES AND ENUMERATIONS.

class Comm_module;

typedef std::map<std::string, Comm_module*> Comm_module_registry;

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

/**
 *  Class to hold the info gotten about the device, such as signatures, bootloader versions and names.
 */
class Device_info
{
public:
	
	// Functions.
	
	std::string get_name();
	void set_name(std::string new_name);
	uint32_t get_signature();
	void set_signature(uint32_t new_signature);
	uint8_t get_version_minor();
	void set_version_minor(uint8_t new_version);
	uint8_t get_version_major();
	void set_version_major(uint8_t vew_version);
	
private:
	
	// Functions.
	
	// Fields.
	std::string name;
	uint32_t signature;
	uint8_t version_minor;
	uint8_t version_major;
};

/**
 * This is the abstract base class for all communication modules.
 * This defines the interface needed to be able to program a microcontroller.
 * 
 * Subclasses of this will implement these methods according to how the specific communication method requires the operations to be performed.
 * 
 */
class Comm_module
{
public:

	// Functions.
	Comm_module(std::string name);
	virtual ~Comm_module()=0;
	
	/**
	 *  This function is called to initialise the communication module,
	 *  currently the uploader assumes that after calling this all other methods of this class will work.
	 */
	virtual bool init(Params params)=0;
	/**
	 *  This function is used to connect to the bootloader on the device.
	 */
	virtual bool connect_to_device()=0;
	
	/**
	 *  This function is called by the uploader to retrieve the device info of the connected device,
	 *  this information is used by the uploader to determine if the device it is connected to is the device it was told to program.
	 */
	virtual bool get_device_info( Device_info& info)=0;
	
	/**
	 *  This function is called by the uploader to write a page to the device,
	 *  it supplies the memory map to read the page from, the size of the page and the start address of the page.
	 */
	virtual bool write_page(Memory_map& source, size_t size, size_t address)=0;
	/**
	 *  This function is called by the uploader to verify that a page has been written correctly,
	 *  it supplies the memory map containing the expected memory contents, the size of the page and the starting address.
	 */
	virtual bool verify_page(Memory_map& expected, size_t size, size_t address)=0;
	/**
	 *  This function is called by the uploader to read a page of memory from the device into a memory map,
	 *  it supplies the memory map to write into, the size of the page to read and the start address.
	 */
	virtual bool read_page(Memory_map& destination, size_t size, size_t address)=0;
	
	/**
	 *  The uploader will call this function to reset the target, with a boolean parameter specifying whether it starts the application or returns to the bootloader.
	 */
	virtual bool reset_device(bool run_application)=0;
	
	/**
	 *  This method will return the map that holds all of the existing communication modules.
	 */
	static Comm_module_registry& get_registry();
	
	
private:
	// Functions.
	
	//Fields.
	static Comm_module_registry* the_registry;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__COMM_H__*/

//ALL DONE.

