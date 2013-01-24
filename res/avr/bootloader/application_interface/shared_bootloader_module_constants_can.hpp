/********************************************************************************************************************************
 *
 *  FILE: 		shared_bootloader_module_constants_can.hpp
 *
 *  AUTHOR: 		George
 *
 *  DATE CREATED:	24-1-2012
 *
 *	Header file that contains the struct of information that can be accessed from the bootloader communication module.
 *
 ********************************************************************************************************************************/
 
struct shared_bootloader_module_constants{
	uint8_t node_id;
	uint16_t baud_rate;
};
