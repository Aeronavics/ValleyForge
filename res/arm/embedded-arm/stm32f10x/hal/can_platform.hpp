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
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		can_platform.hpp
 *  A header file for the AVR platform specific types for the CAN Module of the HAL.
 * 
 *  @brief 
 *  This is the header file which implements various public types and enums that will differ between platforms for the can module.
 * 
 *  @author		George Xian
 *
 *  @date		7-02-2013
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
 *  @section Description
 *
 * These are the public enums and types that are specific to the AVR platform.
 */

// Only include this header file once
#ifndef __CAN_PLATFORM_H__

// INCLUDE REQUIRED HEADER FILES

// DEFINE PUBLIC MACROS
/* **** Register bit names **** */
#define RCC_APB1ENR_CANEN	(1<<25)	
#define RCC_APB2ENR_AFIOEN	(1<<0)
#define RCC_APB2ENR_IOPAEN  (1<<2)

#define CAN_MCR_INRQ (1<<0)
#define CAN_MCR_NART (1<<4)

#define CAN_RFxR_RFOMx (1<<5);

#define CAN_TIR_RTR (1<<1)
#define CAN_TIR_TXRQ (1<<0)

#define CAN_TSR_RQCP0 (1<<0)
#define CAN_TSR_RQCP1 (1<<8)
#define CAN_TSR_RQCP2 (1<<16)
#define CAN_TSR_TXOK0 (1<<1)
#define CAN_TSR_TXOK1 (1<<9)
#define CAN_TSR_TXOK2 (1<<17)
#define CAN_TSR_TERR0 (1<<3)
#define CAN_TSR_TERR1 (1<<11)
#define CAN_TSR_TERR2 (1<<19)

#define CAN_FMR_FINIT (1<<0)

/* **** Masks **** */
#define CAN_TIR_EXTID_MASK (0b11111111111111111111111111111<<3)
#define CAN_TDTxR_DLC_MASK (0b1111)

#define CAN_ESR_LEC_MASK (0b111<<4)

#define CAN_RFxR_FMP_MASK 0b11

/* **** Value representations **** */
#define CAN_ESR_NO_ERROR 0b000
#define CAN_ESR_STUFF_ERROR 0b001
#define CAN_ESR_FORM_ERROR 0b010
#define CAN_ESR_ACK_ERROR 0b011
#define CAN_ESR_CRC_ERROR 0b110


#endif
