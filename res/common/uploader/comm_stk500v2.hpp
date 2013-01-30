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
 *  @file		comm_stk500v2.hpp
 *  A header file for an stk500v2 communications module.
 *  Currently this module is specific to the arduino bootloader.
 *  It doesnt use any of the command bits needed by a real STK500 for programming arbitrary AVRs.
 *  This is the same protocol that is used by most arduino bootloaders so this can be used to program APM boards.
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
#ifndef __COMM_STK500V2_H__
#define __COMM_STK500V2_H__

// INCLUDE REQUIRED HEADER FILES.
#include "comm.hpp"

#include <termios.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.


class STK500v2_module : public Comm_module
{
public:

	// Functions.
	STK500v2_module();
	virtual ~STK500v2_module();
	
	virtual bool init(Params params);
	virtual bool connect_to_device();
	
	virtual bool get_device_info( Device_info& info);
	
	virtual bool write_page(Memory_map& source, size_t size, size_t address);
	virtual bool verify_page(Memory_map& expected, size_t size, size_t address);
	virtual bool read_page(Memory_map& destination, size_t size, size_t address);
	
	virtual bool reset_device(bool run_application);
	
	
private:
	// Functions.
	bool open_serial();
	bool setup_serial();
	bool close_serial();
	bool stk500_send(uint8_t* buf, size_t buf_len);
	bool stk500_recv(uint8_t* buf, size_t buf_len, size_t& bytes_read);
	bool stk500_cmd(uint8_t* buf, size_t cmd_len, size_t& bytes_read);
	bool stk500_sync();
	bool stk500_load_address(size_t address, bool far);
	
	//Fields.
	std::string tty_path;
	unsigned long speed;
	int tty_fd;
	termios original_termios;
	bool saved_original_termios;
	
	bool connected;
	
	std::string prog_name;
	uint8_t signature0;
	uint8_t signature1;
	uint8_t signature2;
	uint32_t signature;
	
	uint8_t stk500_seq_no;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__COMM_STK500V2_H__*/

//ALL DONE.
