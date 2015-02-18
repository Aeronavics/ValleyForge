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
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file		target_config.hpp
 * Provides definitions for to be used in implementations.
 * 
 * 
 * @author 		Zac Frank
 *
 * @date		15-12-2011
 *  
 * @section Licence
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
 * @brief
 * This contains device specific definitions for avr. Information such as timer size, interrupt
 * specifications and so on are defined here.
 */
 
// Only include this header file once.
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// DEFINITIONS WHICH ARE SPECIFIC TO NATIVE OPERATING SYSTEM.

#ifdef __linux__
	
	/* CAN */
	#define CAN_NUM_BUFFERS  1
	#define CAN_NUM_FILTERS  4
	#define CAN_NUM_MASKS 	4
	#define CAN_NUM_BANKS	1

 	enum Can_id_controller { CAN_0 };
	
	enum Can_id_buffer { CAN_BUF_0 };
	enum Can_id_filmask{ CAN_FM_0, CAN_FM_1, CAN_FM_2, CAN_FM_3 };
	enum Can_id_filter { CAN_FIL_0, CAN_FIL_1, CAN_FIL_2, CAN_FIL_3 };
	enum Can_id_mask   { CAN_MSK_0, CAN_MSK_1, CAN_MSK_2, CAN_MSK_3 };
	enum Can_id_bank   { CAN_BNK_0 }; 
	enum Can_bank_mode { CAN_BNK_MODE_1FM, CAN_BNK_MODE_2FM, CAN_BNK_MODE_3FM, CAN_BNK_MODE_4FM };
	
	enum Can_buffer_interrupt_type {};
	enum Can_channel_interrupt_type {};

#else
	#error "No HAL configuration for this target."
#endif

// DEFINITIONS WHICH ARE COMMON TO ALL NATIVE TARGETS.	

#endif // __TARGET_CONFIG_H__

// ALL DONE.
