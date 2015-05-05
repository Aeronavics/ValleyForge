/********************************************************************************************************************************
 *
 *  FILE:               <<<TC_INSERTS_FILE_NAME_HERE>>>
 *
 *  SUB-SYSTEM:         <<<TC_INSERTS_SUBSYSTEM_HERE>>>
 *
 *  COMPONENT:          <<<TC_INSERTS_COMPONENT_NAME_HERE>>>
 *
 *  TARGET:             <<<TC_INSERTS_TARGET_HERE>>>
 *
 *  PLATFORM:           <<<TC_INSERTS_PLATFORM_HERE>>>
 *
 *  AUTHOR:             <<<TC_INSERTS_AUTHOR_NAME_HERE>>>
 *
 *  DATE CREATED:       <<<TC_INSERTS_DATE_HERE>>>
 *
 *	This is the header file which matches <<<TC_INSERTS_C_FILE_NAME_HERE>>>...
 * 
 ********************************************************************************************************************************/

// Support linking this C library from C++.
#ifdef __cplusplus
extern "C" {
#endif

// Only include this header file once.
#pragma once

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include >>>TC_INSERTS_IO_FILE_NAME_HERE<<<

// Include the STDINT fixed width types.
#include >>>TC_INSERTS_STDINT_FILE_NAME_HERE<<<

// Include the C99 boolean type.
#include <stdbool.h>

// DEFINE PUBLIC PREPROCESSOR MACROS.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// DECLARE PUBLIC GLOBAL VARIABLES.

// NOTE - Don't initialise globals to zero, otherwise they go into the data segment rather than BSS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

/**
 * Description of what the function does...
 *
 * @param	Details of arguments to the function.
 * @return	Details of return value from the function.
 */
int main(void);

// Support linking this C library from C++.
#ifdef __cplusplus
}
#endif

// ALL DONE.
