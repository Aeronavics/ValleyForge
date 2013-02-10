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
 *  FILE: 		avr_magic.hpp
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	22-12-2011
 *
 *	This is the header file which matches avr_magic.cpp.  Performs some magic, neccesary because C++ support by avr-gcc is not
 *	complete.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __AVR_MAGIC_H__
#define __AVR_MAGIC_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the standard C library.
#include <stdlib.h>

// DO SOME MAGIC...

// Some approximate implementation of the C++ 'new' and 'delete' operators.

void* operator new(size_t size);

void operator delete(void* ptr);

// These are neccesary because avr-libc doesn't actually implement everything that it needs to.  NOTE - They should never actually get called.

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard*);
extern "C" void __cxa_guard_release (__guard*);
extern "C" void __cxa_guard_abort (__guard*);

extern "C" void __cxa_pure_virtual(void); 

extern "C" void atexit(void);

#endif /*__AVR_MAGIC_H__*/

// ALL DONE.
