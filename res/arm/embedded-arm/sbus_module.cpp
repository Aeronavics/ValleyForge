/********************************************************************************************************************************
 *
 *  FILE:               sbus.cpp
 *
 *  SUB-SYSTEM:         avionics
 *
 *  COMPONENT:          airside/airside_router_stm32
 *
 *  TARGET:             STM32F103VCT6
 *
 *  PLATFORM:           BareMetal
 *
 *  AUTHOR:             Anton Slooten
 *
 *  DATE CREATED:       17-8-2017
 *
 *	Description goes here...
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "sbus_module.hpp"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

// DEFINE PRIVATE MACROS.

// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// NOTE - Don't initialise globals to zero, otherwise they go into the data segment rather than BSS.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

// IMPLEMENT PUBLIC CLASS METHODS.
Sbus::Sbus(void)
{

}
Sbus::~Sbus(void)
{

}

bool Sbus::Decode_sbus(uint8_t * buffer, uint8_t buffer_data_size, Sbus_data * channel_data)
{
	for(uint8_t counter = 0; counter < CHANNELS; counter++){
			//reset the channel data to prevent stale data lingering. somehow
			channel_data->data[counter] = 0;
	}
	//check start and stop bits.
	if(buffer[0] != 0x0F ||!(buffer[24] != 0x00 || buffer[24] != 0b00100000 || buffer[24] != 0b00101000 || buffer[24] != 0b00100100 )){
		return false;//the first byte was not correct. Therefore we cannot assume the rest is OK
	}
	//map data
	channel_data->data[0]  = ((buffer[1] | ((uint16_t) buffer[2]) << 8) & 0x07FF);
	channel_data->data[1]  = ((buffer[2] >> 3  | ((uint16_t) buffer[3])  << 5) & 0x07FF);
	channel_data->data[2]  = ((buffer[3] >> 6  | ((uint16_t) buffer[4])  << 2  | ((uint16_t) buffer[5]) << 10) & 0x07FF);
	channel_data->data[3]  = ((buffer[5] >> 1  | ((uint16_t) buffer[6])  << 7) & 0x07FF);
	channel_data->data[4]  = ((buffer[6] >> 4  | ((uint16_t) buffer[7])  << 4) & 0x07FF);
	channel_data->data[5]  = ((buffer[7] >> 7  | ((uint16_t) buffer[8])  << 1  | ((uint16_t) buffer[9]) << 9) & 0x07FF);
	channel_data->data[6]  = ((buffer[9] >> 2  | ((uint16_t) buffer[10]) << 6) & 0x07FF);
	channel_data->data[7]  = ((buffer[10] >> 5 | ((uint16_t) buffer[11]) << 3) & 0x07FF);
	channel_data->data[8]  = ((buffer[12] 	   | ((uint16_t) buffer[13]) << 8) & 0x07FF);
	channel_data->data[9]  = ((buffer[13] >> 3 | ((uint16_t) buffer[14]) << 5) & 0x07FF);
	channel_data->data[10] = ((buffer[14] >> 6 | ((uint16_t) buffer[15]) << 2  | ((uint16_t) buffer[16]) << 10) & 0x07FF);
	channel_data->data[11] = ((buffer[16] >> 1 | ((uint16_t) buffer[17]) << 7) & 0x07FF);
	channel_data->data[12] = ((buffer[17] >> 4 | ((uint16_t) buffer[18]) << 4) & 0x07FF);
	channel_data->data[13] = ((buffer[18] >> 7 | ((uint16_t) buffer[19]) << 1  | ((uint16_t) buffer[20]) << 9) & 0x07FF);
	channel_data->data[14] = ((buffer[20] >> 2 | ((uint16_t) buffer[21]) << 6) & 0x07FF);
	channel_data->data[15] = ((buffer[21] >> 5 | ((uint16_t) buffer[22]) << 3) & 0x07FF);
//map more data
	channel_data->channels.channel17 = (buffer[23] & (1 << 0)) != 0;
	channel_data->channels.channel18 = (buffer[23] & (1 << 1)) != 0;
	//pull out statuses from the sbus signal
	if((buffer[23] & (1 << 2)) != 0){
		channel_data->frame_status = SBUS_SIGNAL_LOST;
	}
	else if((buffer[23] & (1 << 3))){
		channel_data->frame_status = SBUS_SIGNAL_FAILSAFE;
	}
	else
		channel_data->frame_status = SBUS_SIGNAL_OK;
			//all gravy, lets return
	return true;
}
bool Sbus::Encode_sbus(uint16_t * channel_data, uint8_t channel_data_size, uint8_t * sbus_out_data, uint8_t sbus_data_size)
{
	//sbus_data_size should be 25. This is manditory
	if(sbus_data_size != 25 && channel_data_size != 18){
		return false;
	}
	sbus_out_data[0] = 0x0F; 

	// 16 channels of 11 bit data
  	sbus_out_data[1] = (uint8_t)  ((channel_data[0]  & 0x07FF));
  	sbus_out_data[2] = (uint8_t)  ((channel_data[0]  & 0x07FF)>>8 |  (channel_data[1] & 0x07FF)<<3);
  	sbus_out_data[3] = (uint8_t)  ((channel_data[1]  & 0x07FF)>>5 |  (channel_data[2] & 0x07FF)<<6);
  	sbus_out_data[4] = (uint8_t)  ((channel_data[2]  & 0x07FF)>>2);
  	sbus_out_data[5] = (uint8_t)  ((channel_data[2]  & 0x07FF)>>10 | (channel_data[3] & 0x07FF)<<1);
  	sbus_out_data[6] = (uint8_t)  ((channel_data[3]  & 0x07FF)>>7 |  (channel_data[4] & 0x07FF)<<4);
  	sbus_out_data[7] = (uint8_t)  ((channel_data[4]  & 0x07FF)>>4 |  (channel_data[5] & 0x07FF)<<7);
  	sbus_out_data[8] = (uint8_t)  ((channel_data[5]  & 0x07FF)>>1);
  	sbus_out_data[9] = (uint8_t)  ((channel_data[5]  & 0x07FF)>>9 |  (channel_data[6] & 0x07FF)<<2);
  	sbus_out_data[10] = (uint8_t) ((channel_data[6]  & 0x07FF)>>6 |  (channel_data[7] & 0x07FF)<<5);
  	sbus_out_data[11] = (uint8_t) ((channel_data[7]  & 0x07FF)>>3);
  	sbus_out_data[12] = (uint8_t) ((channel_data[8]  & 0x07FF));
  	sbus_out_data[13] = (uint8_t) ((channel_data[8]  & 0x07FF)>>8 |  (channel_data[9] & 0x07FF)<<3);
  	sbus_out_data[14] = (uint8_t) ((channel_data[9]  & 0x07FF)>>5 |  (channel_data[10] & 0x07FF)<<6);  
  	sbus_out_data[15] = (uint8_t) ((channel_data[10] & 0x07FF)>>2);
  	sbus_out_data[16] = (uint8_t) ((channel_data[10] & 0x07FF)>>10 | (channel_data[11] & 0x07FF)<<1);
  	sbus_out_data[17] = (uint8_t) ((channel_data[11] & 0x07FF)>>7 |  (channel_data[12] & 0x07FF)<<4);
  	sbus_out_data[18] = (uint8_t) ((channel_data[12] & 0x07FF)>>4 |  (channel_data[13] & 0x07FF)<<7);
  	sbus_out_data[19] = (uint8_t) ((channel_data[13] & 0x07FF)>>1);
  	sbus_out_data[20] = (uint8_t) ((channel_data[13] & 0x07FF)>>9 |  (channel_data[14] & 0x07FF)<<2);
  	sbus_out_data[21] = (uint8_t) ((channel_data[14] & 0x07FF)>>6 |  (channel_data[15] & 0x07FF)<<5);
  	sbus_out_data[22] = (uint8_t) ((channel_data[15] & 0x07FF)>>3);

  	// flags
	sbus_out_data[23] = 0x00; //? no digital channels? TODO: Fix this

	// footer
	sbus_out_data[24] = 0x00;
	return true;
}
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS METHODS.

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// ALL DONE.
