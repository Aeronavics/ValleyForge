// Copyright (C) 2013  Unison Networks Ltd
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
 *  FILE: 		shared_bootloader_module_constants_canspi.hpp
 *
 *  AUTHOR: 		George
 *
 *  DATE CREATED:	24-1-2012
 *
 *	Header file that contains the struct of information that can be accessed from the bootloader communication module.
 *
 ********************************************************************************************************************************/
 
struct Shared_bootloader_module_constants{
	uint8_t node_id;
	uint16_t baud_rate;
};
