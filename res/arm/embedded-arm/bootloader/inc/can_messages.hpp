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

/**
 *
 * 
 *  @file		can_messages.hpp
 *  A header file listing the CAN message IDs used by the toolchain.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		24-01-2013
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2013  Unison Networks Ltd
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


#define HOST_ALERT 0x2FF

#define BASE_ID 0x120

#define REQUEST_RESET BASE_ID
#define GET_INFO (BASE_ID+1)
#define WRITE_MEMORY (BASE_ID+2)
#define WRITE_DATA (BASE_ID+3)
#define READ_MEMORY (BASE_ID+4)
#define READ_DATA (BASE_ID+5)

// ALL DONE.

