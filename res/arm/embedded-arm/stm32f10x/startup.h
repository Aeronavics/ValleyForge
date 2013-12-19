/********************************************************************************************************************************
 *
 *  FILE: 		startup.h
 *
 *  TARGET:		STM32F10x
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	17th December 2013
 *
 *	This is the header file which matches startup.c...
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__
#define __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// DEFINE PUBLIC PREPROCESSOR MACROS.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// DECLARE PUBLIC GLOBAL VARIABLES.

// External symbols with the address of important sections in memory are provided by the linker.
extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _estack;

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif // __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__

// ALL DONE.
