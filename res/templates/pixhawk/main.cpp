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
 *	Description goes here...
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <nuttx/config.h>
#include <stdio.h>
#include <errno.h>

// DEFINE PRIVATE MACROS.

// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

enum private_enum_type {PRIVATE_ENUM_TYPE_0, PRIVATE_ENUM_TYPE_1};

class Private_class_type
{
	public:
		// Fields.

		bool public_class_field;

		// Methods.

		/**
		 * This is a public class method.
		 *
		 * @param	Nothing.
		 * @return	Nothing.
		 */
		void public_class_method(void);

	private:
		// Fields.

		bool private_class_field;

		// Methods.

		/**
		 * This is a private class method.
		 *
		 * @param	Nothing.
		 * @return	Nothing.
		 */
		void private_class_method(void);

		Private_class_type(void);	// Poisoned.
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

/*
 * This is a private function.
 *
 * @param	Nothing.
 * @return	Nothing.
 */
void private_function(void);

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

int <<<TC_INSERTS_FILE_BASENAME_HERE>>>(void)
{
	// TODO - This.

	// All done.
	return 0;
}

// IMPLEMENT PUBLIC CLASS FUNCTIONS.

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void private_function(void)
{
	// TODO - This.

	// All done.
	return;
}

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// ALL DONE.
