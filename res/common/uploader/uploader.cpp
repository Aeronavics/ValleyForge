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
 *  FILE: 		uploader.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Main frontend file
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	19-11-2012
 *
 *	Frontend for the flashing tools.
 *
 ********************************************************************************************************************************/
 
// INCLUDE REQUIRED HEADER FILES.

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include "ihex.hpp"
#include "memory.hpp"
#include "options.hpp"


#define MAX_RETRIES 10

// DECLARE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT MAIN FUNCTION.
int main(int argc, char* argv[])
{
	Options opts;
	if (!opts.read_from_args(argc, argv))
	{
		opts.print_usage();
		return 1;
	}
	
	std::string filename = opts.get_input_file();
	size_t memory_size = opts.get_memory_size();
	
	Memory_map memory(memory_size, Memory_map::FLASH);
	
	if (!memory.read_from_file(filename))
	{
		std::cerr << "Failed to read input file." << std::endl;
		opts.print_usage();
		return 1;
	}
	
	Comm_module* comm_module = opts.get_comms_module();
	if (comm_module == NULL)
	{
		std::cerr << "Unknown communication module selected" << std::endl;
		return 1;
	}
	
	if (!comm_module->init(opts.get_comms_params()))
	{
		std::cerr << "Failed to initialise communication module" << std::endl;
		return 1;
	}
	
	Device_info info;
	
	if (!comm_module->get_device_info(info))
	{
		std::cerr << "Failed to retrieve device info" << std::endl;
		return 1;
	}
	
	std::cout << "Name: " << info.get_name() << " Signature: " << info.get_signature() << std::endl;
	//Check signature.
	if (info.get_signature() != opts.get_signature())
	{
		std::cerr << "Signature Mismatch" << std::endl;
		return 1;
	}
	
	size_t end_page;
	if (!memory.find_last_allocated_page(opts.get_page_size(), end_page))
	{
		std::cerr << "Could not find a last allocated page, is the memory map empty?" << std::endl;
		return 1;
	}
	
	//~ for (size_t i = 0; i < endPage+opts.getPageSize(); i++)
	//~ {
		//~ std::cout << ((memory.getAllocatedMap()[i] == MemoryMap::ALLOCATED) ? (uint8_t)memory.getMemory()[i] : (uint8_t)0xFF);
	//~ }
	
	
	int retries = 0;
	bool failed = false;
	int max_page = end_page/opts.get_page_size();
	
	for (size_t page_address = 0; page_address <= end_page; page_address += opts.get_page_size())
	{
		retries = 0;
		int page_number = page_address/opts.get_page_size();
		do
		{
			std::cout << "Writing page: " <<  page_number + 1 << " of : " << max_page + 1;
			std::cout.flush();
			if (!comm_module->write_page(memory, opts.get_page_size(), page_address))
			{
				failed = true;
			}
			else
			{
				failed = false;
			}
			retries++;
			std::cout << "\r                                        " << "\r";
		}
		while (failed && retries < MAX_RETRIES);
		
		if (failed)
		{
			std::cerr << "Failed to write flash page at: " << page_address << std::endl;
			return 1;
		}
		
		retries = 0;
		do
		{
			std::cout << "Verifying page: " <<  page_number + 1 << " of : " << max_page + 1;
			std::cout.flush();
			if (!comm_module->verify_page(memory, opts.get_page_size(), page_address))
			{
				failed = true;
			}
			else
			{
				failed = false;
			}
			retries++;
			if (page_address != end_page)
			{
				std::cout << "\r                                          " << "\r";
			}
		}
		while (failed && retries < MAX_RETRIES);
		
		
		if (failed)
		{
			std::cerr << "Verify flash page at: " << page_address << " Failed" << std::endl;
			return 1;
		}
	}
	
	std::cout << std::endl;	

	
	if (!comm_module->reset_device(true))
	{
		std::cerr << "Failed to reset device." << std::endl;
		return 1;
	}
	
	return 0;
}

// IMPLEMENT PRIVATE FUNCTIONS.

//ALL DONE.
 
