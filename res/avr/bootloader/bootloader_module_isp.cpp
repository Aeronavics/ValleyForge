/********************************************************************************************************************************
 *
 *  FILE: 		bootloader_module_isp.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	21-12-2011
 *
 *	Provides a bootloader module which only supports regular ISP programming, i.e. doesn't do anything.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_isp::~bootloader_module_isp()
{
	// All done.
	return;
}

void bootloader_module_isp::init(void)
{
	// TODO - This.

	// For the moment, we just tell the bootloader to run the application right away.
	firmware_finished = true;

	// All done.
	return;
}

void bootloader_module_isp::exit(void)
{
	// TODO - This.

	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
