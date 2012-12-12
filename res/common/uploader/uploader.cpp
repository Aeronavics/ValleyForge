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

#include "ihex.hpp"
#include "memory.hpp"
#include "options.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>

#include <unistd.h>

#define MAX_RETRIES 10

// DECLARE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT MAIN FUNCTION.
int main(int argc, char* argv[])
{
	Options opts;
	if (!opts.readFromArgs(argc, argv))
	{
		opts.printUsage();
		return 1;
	}
	
	std::string filename = opts.getInputFile();
	size_t memorySize = opts.getMemorySize();
	
	MemoryMap memory(memorySize, MemoryMap::FLASH);
	
	if (!memory.readFromFile(filename))
	{
		std::cerr << "Failed to read input file." << std::endl;
		opts.printUsage();
		return 1;
	}
	
	CommModule* commModule = opts.getCommsModule();
	if (commModule == NULL)
	{
		std::cerr << "Unknown communication module selected" << std::endl;
		return 1;
	}
	
	if (!commModule->init(opts.getCommsParams()))
	{
		std::cerr << "Failed to initialise communication module" << std::endl;
		return 1;
	}
	
	DeviceInfo info;
	
	if (!commModule->getDeviceInfo(info))
	{
		std::cerr << "Failed to retrieve device info" << std::endl;
		return 1;
	}
	
	std::cout << "Name: " << info.getName() << " Signature: " << info.getSignature() << std::endl;
	//Check signature.
	if (info.getSignature() != opts.getSignature())
	{
		std::cerr << "Signature Mismatch" << std::endl;
		return 1;
	}
	
	size_t endPage;
	if (!memory.findLastAllocatedPage(opts.getPageSize(), endPage))
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
	int maxPage = endPage/opts.getPageSize();
	
	for (size_t pageAddress = 0; pageAddress <= endPage; pageAddress += opts.getPageSize())
	{
		retries = 0;
		int pageNumber = pageAddress/opts.getPageSize();
		do
		{
			std::cout << "Writing page: " <<  pageNumber << " of : " << maxPage << std::endl;
			if (!commModule->writePage(memory, opts.getPageSize(), pageAddress))
			{
				failed = true;
			}
			else
			{
				failed = false;
			}
			retries++;
		
		}
		while (failed && retries < MAX_RETRIES);
		
		if (failed)
		{
			std::cerr << "Failed to write flash page at: " << pageAddress << std::endl;
			return 1;
		}
		
		retries = 0;
		do
		{
			std::cout << "Verifying page: " <<  pageNumber << " of : " << maxPage << std::endl;
			if (!commModule->verifyPage(memory, opts.getPageSize(), pageAddress))
			{
				failed = true;
			}
			else
			{
				failed = false;
			}
			retries++;
		}
		while (failed && retries < MAX_RETRIES);
		
		if (failed)
		{
			std::cerr << "Verify flash page at: " << pageAddress << " Failed" << std::endl;
			return 1;
		}
	}
	//~ 
	
	
	//~ if (!commModule->writePage(memory, 256, 256))
	//~ {
		//~ std::cerr << "Failed to write second page of flash memory." << std::endl;
		//~ return 1;
	//~ }
	//~ 
	//~ 
	//~ 
	//~ if (!commModule->verifyPage(memory, 256, 256))
	//~ {
		//~ std::cerr << "Verify of second page of flash failed." << std::endl;
		//~ return 1;
	//~ }
	
	//~ if (!commModule->readPage(memory, 256, 0))
	//~ {
		//~ std::cerr << "Read of first page of flash failed." << std::endl;
		//~ return 1;
	//~ }
	//~ 
	//~ char buf[3];
	//~ for ( size_t i = 0; i < 256; i++ )
	//~ {
		//~ snprintf(buf, 3, "%02X", memory.getMemory()[i]);
		//~ buf[2] = '\0';
		//~ std::cout << buf << ((i % 16 != 15) ? " " : "\n");
	//~ }
	
	if (!commModule->resetDevice(true))
	{
		std::cerr << "Failed to reset device." << std::endl;
		return 1;
	}
	
	return 0;
}

// IMPLEMENT PRIVATE FUNCTIONS.
 
