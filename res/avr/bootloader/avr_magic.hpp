/********************************************************************************************************************************
 *
 *  FILE: 		avr_magic.h
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	22-12-2011
 *
 *	This is the header file which matches avr_magic.c.  Performs some magic, neccesary because C++ support by avr-gcc is not
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

#endif /*__AVR_MAGIC_H__*/

// ALL DONE.
