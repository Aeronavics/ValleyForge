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

#include "FreeRTOS.h"
#include "task.h"

#include <stdlib.h>
#include <string.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DEFINE PRIVATE CLASSES.

// DECLARE PRIVATE GLOBAL VARIABLES.

#define TEST_FUNC_PRIORITY			( tskIDLE_PRIORITY + 2 )

// DEFINE PRIVATE FUNCTION PROTOTYPES.

static void testFunction (void *pvParameters);

/*
 * The idle hook is used to scheduler co-routines.
 */
void vApplicationIdleHook( void );

extern "C" void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName );



// IMPLEMENT PUBLIC STATIC FUNCTIONS.

int main(void)
{
	/* Create the tasks defined within this file. */
	xTaskCreate( testFunction, ( signed char * ) "Tester", configMINIMAL_STACK_SIZE, NULL, TEST_FUNC_PRIORITY, NULL );
	
	/* In this port, to use preemptive scheduler define configUSE_PREEMPTION 
	as 1 in portmacro.h.  To use the cooperative scheduler define 
	configUSE_PREEMPTION as 0. */
	vTaskStartScheduler();

	return 0;
}

// IMPLEMENT PUBLIC CLASS FUNCTIONS.

static void testFunction (void *pvParameters)
{
	const portTickType xDelay = 500/ portTICK_RATE_MS;	

     for( ;; )
     {
        //Do Something
         vTaskDelay( xDelay );
     }
    
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	 
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}



// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

// ALL DONE.
