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
 *  FILE: 		can.cpp	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	14-11-2012
 *
 *	Functionality to provide implementation for CAN in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"
#include "can_platform.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

/********************************************************************************************************************************/

class Can_imp
{
	public:
		//Methods
		Can_command_response initialise(Can_rate rate, Can_mode mode);
		
		void transmit(Can_object obj, Can_message msg);
		
	private:
		//Methods
		
		//Fields
		
}

Can_command_response Can_imp::initialise(Can_rate rate, Can_mode mode)
{
	#ifndef <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>
		#  error  This CLK_SPEED_IN_MHZ is not set
	#endif

	//Set global variables depending on required baud rate at the chosen clock speed
	#if <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>> == 16000             //!< Fclkio = 16 MHz, Tclkio = 62.5 ns
		if (rate == CAN_100K)       //!< -- 100Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x12;       // Tscl  = 10x Tclkio = 625 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)  //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0E;       // Tscl  = 8x Tclkio = 500 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_200K)  //!< -- 200Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 312.5 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
		else if (rate == CAN_250K)       //!< -- 250Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x06;       // Tscl  = 4x Tclkio = 250 ns
			CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)       //!< -- 500Kb/s, 8x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x06;       // Tscl = 4x Tclkio = 250 ns
			CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x13;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K)      //!< -- 1 Mb/s, 8x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 125 ns
			CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x13;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}

	#elif <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>> == 12000           //!< Fclkio = 12 MHz, Tclkio = 83.333 ns
	    if (rate == CAN_100K)      //!< -- 100Kb/s, 20x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0A;       // Tscl  = 6x Tclkio = 500 ns
			CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)      //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x0A;       // Tscl  = 6x Tclkio = 500 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_200K)       //!< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
			CONF_CANBT1 = 0x04;       // Tscl  = 3x Tclkio = 250 ns
			CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
		else if (rate == CAN_250K)      //!< -- 250Kb/s, 16x Tscl, sampling at 75%
		{
			CONF_CANBT1 = 0x04;       // Tscl  = 3x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)       //!< -- 500Kb/s, 12x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 166.666 ns
			CONF_CANBT2 = 0x08;       // Tsync = 1x Tscl, Tprs = 5x Tscl, Tsjw = 1x Tscl
			CONF_CANBT3 = 0x25;       // Tpsh1 = 3x Tscl, Tpsh2 = 3x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K)      //!< -- 1 Mb/s, 12x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 83.333 ns
	        CONF_CANBT2 = 0x08;       // Tsync = 1x Tscl, Tprs = 5x Tscl, Tsjw = 1x Tscl
            CONF_CANBT3 = 0x25;       // Tpsh1 = 3x Tscl, Tpsh2 = 3x Tscl, 3 sample points
		}

	#elif <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>> == 8000              //!< Fclkio = 8 MHz, Tclkio = 125 ns
	    if (rate == CAN_100K)       //!< -- 100Kb/s, 16x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x08;       // Tscl  = 5x Tclkio = 625 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_125K)       //!< -- 125Kb/s, 16x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x06;       // Tscl  = 4x Tclkio = 500 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_200K)       //!< -- 200Kb/s, 20x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0E;       // Tsync = 1x Tscl, Tprs = 8x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x4B;       // Tpsh1 = 6x Tscl, Tpsh2 = 5x Tscl, 3 sample points
		}
	    else if (rate == CAN_250K)       //!< -- 250Kb/s, 16x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x0C;       // Tsync = 1x Tscl, Tprs = 7x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x37;       // Tpsh1 = 4x Tscl, Tpsh2 = 4x Tscl, 3 sample points
		}
	    else if (rate == CAN_500K)       //!< -- 500Kb/s, 8x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x02;       // Tscl  = 2x Tclkio = 250 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	    else if (rate == CAN_1000K)      //!< -- 1 Mb/s, 8x Tscl, sampling at 75%
	    {
	        CONF_CANBT1 = 0x00;       // Tscl  = 1x Tclkio = 125 ns
	        CONF_CANBT2 = 0x04;       // Tsync = 1x Tscl, Tprs = 3x Tscl, Tsjw = 1x Tscl
	        CONF_CANBT3 = 0x13;       // Tpsh1 = 2x Tscl, Tpsh2 = 2x Tscl, 3 sample points
		}
	#else
	#   error The CLK_SPEED_IN_MHZ is not set
	#endif
	
	Can_conf_bt()	//configure fixed baud rate by assigning CANBT registers to the values above
	
	Can_reset()
	can_clear_all_mob();
	Can_enable();
	
	if (mode == CAN_LISTEN)
	{
		CANGCON |= (1<<LISTEN)  //turn the LISTEN bit (Bit 3) of CANGCON on
	}
	else if (mode = CAN_NORMAL)
	{
		CANGCON &= !(1<<LISTEN)	//turn the LISTEN bit (Bit 3) of CANGCON off
	}
	
	
	
	
	
}


