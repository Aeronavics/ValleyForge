/********************************************************************************************************************************
 *
 *  FILE: 		can_message_ids.hpp
 *
 *  AUTHOR: 		George Wareing
 *
 *  DATE CREATED:	24-1-2012
 *
 *	Header file that contains the CAN message IDs. 
 *
 ********************************************************************************************************************************/




	//Bootloader message ids
#define BOOTLOADER_BASE_ID 0x120 // TODO - Yet to be finalised.

enum message_id {RESET_REQUEST = BOOTLOADER_BASE_ID, GET_INFO = BOOTLOADER_BASE_ID + 1, 
			WRITE_MEMORY = BOOTLOADER_BASE_ID + 2, WRITE_DATA = BOOTLOADER_BASE_ID + 3, 
			READ_MEMORY = BOOTLOADER_BASE_ID + 4, READ_DATA = BOOTLOADER_BASE_ID + 5, ALERT_UPLOADER = 0x2FF};
