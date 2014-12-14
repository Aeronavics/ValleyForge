/********************************************************************************************************************************
 *
 *  FILE: 		<<<TC_INSERTS_FILE_NAME_HERE>>>
 *
 *  SUB-SYSTEM:		<<<TC_INSERTS_SUBSYSTEM_HERE>>>
 *
 *  COMPONENT:		<<<TC_INSERTS_COMPONENT_NAME_HERE>>>
 *
 *  TARGET:		<<<TC_INSERTS_TARGET_HERE>>>
 *
 *  PLATFORM:		<<<TC_INSERTS_PLATFORM_HERE>>>
 *
 *  AUTHOR: 		<<<TC_INSERTS_AUTHOR_NAME_HERE>>>
 *
 *  DATE CREATED:	<<<TC_INSERTS_DATE_HERE>>>
 *
 *	Description goes here...
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DEFINE PRIVATE CLASSES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int <<<TC_INSERTS_FILE_BASENAME_HERE>>>(int argc, char *argv[])
#endif
{
  printf("Hello, World!!\n");
  return 0;
}

// IMPLEMENT PUBLIC CLASS FUNCTIONS.

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

// ALL DONE.