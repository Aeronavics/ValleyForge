/********************************************************************************************************************************
 *
 *  FILE:               sbus.hpp
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
 *	This is the header file which matches sbus.cpp...
 *
 ********************************************************************************************************************************/

// Only include this header file once.
#pragma once

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
// #include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// DEFINE PUBLIC MACROS.

// SELECT NAMESPACES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.
#define CHANNELS 18
typedef struct SBUS_Channels_t  {
        int16_t channel1;
        int16_t channel2;
        int16_t channel3;
        int16_t channel4;
        int16_t channel5;
        int16_t channel6;
        int16_t channel7;
        int16_t channel8;
        int16_t channel9;
        int16_t channel10;
        int16_t channel11;
        int16_t channel12;
        int16_t channel13;
        int16_t channel14;
        int16_t channel15;
        int16_t channel16;
        int16_t channel17;
        int16_t channel18;
} SBUS_Channels;
enum Sbus_frame_status{SBUS_SIGNAL_UNSET, SBUS_SIGNAL_OK, SBUS_SIGNAL_LOST, SBUS_SIGNAL_FAILSAFE};

typedef struct SBUS_data_t {
	Sbus_frame_status frame_status;
	union {
    int16_t data[CHANNELS];
    SBUS_Channels channels;
	};
} Sbus_data;



class Sbus
{
	public:
		// Fields.

		// Methods.

		/**
		 * This method decodes a stream of Sbus data into an array of channels.
		 *
		 * @param	sbus_data Pointer to sbus data.
		 * @param size of said sbus data array
		 * @param channel_data of decoded sbus data
		 * @param channel_data_size size of channel_data array. Will always be 1/2 of the sbus_data_size
		 * @return	nothing
		 */
		static bool Decode_sbus(uint8_t * buffer, uint8_t buffer_data_size, Sbus_data * channel_data);
		/**
		 * This method decodes a stream of Sbus data into an array of channels.
		 *
		 * @param channel_data of raw data to be encoded into sbus
		 * @param channel_data_size size of channel_data array.
		 * @param	sbus_data Pointer to encoded sbus data.
		 * @param size of said sbus data array. Will always be 2x channel_data_size
		 * @return	nothing
		 */
		void Encode_sbus(uint16_t* channel_data, uint8_t channel_data_size, uint8_t * sbus_data, uint8_t sbus_data_size);

		Sbus(void);
		~Sbus(void);

	private:
		// Fields.

};

// DECLARE PUBLIC GLOBAL VARIABLES.

// NOTE - Don't initialise globals to zero, otherwise they go into the data segment rather than BSS.

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC INLINE FUNCTIONS.

// ALL DONE.
