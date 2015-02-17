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
 *  @file		can_messages.h
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

// Support linking this C library from C++.
#ifdef __cplusplus
extern "C" {
#endif

// Only include this header file once.
#ifndef __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__
#define __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__

// DEFINE PUBLIC PREPROCESSOR MACROS.

#define CANID_HOST_ALERT 0x2FF

#define CANID_BASE_ID 0x120

#define CANID_REQUEST_RESET CANID_BASE_ID
#define CANID_GET_INFO (CANID_BASE_ID + 1)
#define CANID_WRITE_MEMORY (CANID_BASE_ID + 2)
#define CANID_WRITE_DATA (CANID_BASE_ID + 3)
#define CANID_READ_MEMORY (CANID_BASE_ID + 4)
#define CANID_READ_DATA (CANID_BASE_ID + 5)

#endif // __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__

// Support linking this C library from C++.
#ifdef __cplusplus
}
#endif

// ALL DONE.
