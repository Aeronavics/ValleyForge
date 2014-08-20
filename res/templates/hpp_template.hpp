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

// Only include this header file once.
#ifndef __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__
#define __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include >>>TC_INSERTS_IO_FILE_NAME_HERE<<<

// Include the STDINT fixed width types.
#include >>>TC_INSERTS_STDINT_FILE_NAME_HERE<<<

// DEFINE PUBLIC MACROS.

// SELECT NAMESPACES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

enum public_enum_type {PUBLIC_ENUM_TYPE_0, PUBLIC_ENUM_TYPE_1};

class Public_class_type
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

		Public_class_type(void);	// Poisoned.
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

/**
 * Description of what the function does...
 *
 * @param	Details of arguments to the function.
 * @return	Details of return value from the function.
 */
int main(void);

// IMPLEMENT PUBLIC STATIC INLINE FUNCTIONS.

#endif // __<<<TC_INSERTS_UC_FILE_BASENAME_HERE>>>_H__

// ALL DONE.
