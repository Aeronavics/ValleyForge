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

    //flag to tell us late if we actually want to decode this.
    bool decode_frame = true;
    //check start and stop bits.
    //There appears to be multiple end bytes available pending on the module.
    if (buffer[0] != 0x0F || !(buffer[24] == 0x00 || buffer[24] == 0b00100000 || buffer[24] == 0b00101000 || buffer[24] == 0b00100100))
    {
        //Our data is incomplete or the frame does not check out. The data cannot be assumed to be correct
        decode_frame = false;
    }
    else
    {
        //our start and stop bit checkout. Let us check the status of the signal

        /**
         * Buffer 1 seems to have interesting behavior, this might be some telemetry that we do not know about
         * if data0 is 0x7c and data 1 is 0x00, then it is almost certainly an issue,
         * so lets just ignore it
         */
        uint16_t data_1, data_2;
        data_1 = ((buffer[1] | ((uint16_t) buffer[2]) << 8) & 0x07FF);
        data_2 = ((buffer[2] >> 3 | ((uint16_t) buffer[3]) << 5) & 0x07FF);

        if ((data_1 == 0x7C) && (data_2 == 0x00))
        {
            decode_frame = false;
        }

        /**
         * Here we actually look at the signal and see if we are actually going to use this data.
         */
        bool sig_lost = ((buffer[23] & (1 << 2)) != 0);
        bool failsafe = ((buffer[23] & (1 << 3)) != 0);

        //pull out statuses from the sbus signal
        if (sig_lost && !failsafe)
        {
            //this is the only where we are not sure what our data is
            //Therefore if this is the case, for the love of something divine, DO NOT OUTPUT THIS VALUE
            channel_data->frame_status = SBUS_SIGNAL_LOST;
            //return false so we do not overwrite old data.
            decode_frame = false;
        }
        else if (!sig_lost && failsafe)
        {
            //we are in failsafe, but have regained our signal
            channel_data->frame_status = SBUS_SIGNAL_FAILSAFE;
            decode_frame = false;
        }
        else if (sig_lost && failsafe)
        {
            //there is no signal, and we are in failsafe.
            channel_data->frame_status = SBUS_SIGNAL_FAILSAFE_AND_LOST;
        }
        else
        {
            //we are currently fine.
            channel_data->frame_status = SBUS_SIGNAL_OK;
        }

        //check whether or not we are going to decode this frame.
        if (decode_frame)
        {
            for (uint8_t counter = 0; counter < CHANNELS; counter++)
            {
                //reset the channel data to prevent stale data lingering. somehow
                channel_data->data[counter] = 0;
            }


            channel_data->data[0] = data_1;
            channel_data->data[1] = data_2;
            channel_data->data[2] = ((buffer[3] >> 6 | ((uint16_t) buffer[4]) << 2 | ((uint16_t) buffer[5]) << 10) & 0x07FF);
            channel_data->data[3] = ((buffer[5] >> 1 | ((uint16_t) buffer[6]) << 7) & 0x07FF);
            channel_data->data[4] = ((buffer[6] >> 4 | ((uint16_t) buffer[7]) << 4) & 0x07FF);
            channel_data->data[5] = ((buffer[7] >> 7 | ((uint16_t) buffer[8]) << 1 | ((uint16_t) buffer[9]) << 9) & 0x07FF);
            channel_data->data[6] = ((buffer[9] >> 2 | ((uint16_t) buffer[10]) << 6) & 0x07FF);
            channel_data->data[7] = ((buffer[10] >> 5 | ((uint16_t) buffer[11]) << 3) & 0x07FF);
            channel_data->data[8] = ((buffer[12] | ((uint16_t) buffer[13]) << 8) & 0x07FF);
            channel_data->data[9] = ((buffer[13] >> 3 | ((uint16_t) buffer[14]) << 5) & 0x07FF);
            channel_data->data[10] = ((buffer[14] >> 6 | ((uint16_t) buffer[15]) << 2 | ((uint16_t) buffer[16]) << 10) & 0x07FF);
            channel_data->data[11] = ((buffer[16] >> 1 | ((uint16_t) buffer[17]) << 7) & 0x07FF);
            channel_data->data[12] = ((buffer[17] >> 4 | ((uint16_t) buffer[18]) << 4) & 0x07FF);
            channel_data->data[13] = ((buffer[18] >> 7 | ((uint16_t) buffer[19]) << 1 | ((uint16_t) buffer[20]) << 9) & 0x07FF);
            channel_data->data[14] = ((buffer[20] >> 2 | ((uint16_t) buffer[21]) << 6) & 0x07FF);
            channel_data->data[15] = ((buffer[21] >> 5 | ((uint16_t) buffer[22]) << 3) & 0x07FF);
            //map more data
            channel_data->channels.channel17 = (buffer[23] & (1 << 0)) != 0;
            channel_data->channels.channel18 = (buffer[23] & (1 << 1)) != 0;
        }
    }
    /**
     * Clear the buffer so that we can be sure no old data is coming through.
     */
    for (uint8_t i = 0; i < buffer_data_size; i++)
    {
        buffer[i] = 0;
    }
    return decode_frame;
}

bool Sbus::Encode_sbus(SBUS_data_t * channel_data, uint8_t channel_data_size, uint8_t * sbus_out_data, uint8_t sbus_data_size)
{
    //sbus_data_size should be 25. This is manditory
    if (sbus_data_size != 25 && channel_data_size != 18)
    {
        return false;
    }
    sbus_out_data[0] = 0x0F;

    // 16 channels of 11 bit data
    sbus_out_data[1] = (uint8_t) ((channel_data->data[0] & 0x07FF));
    sbus_out_data[2] = (uint8_t) ((channel_data->data[0] & 0x07FF) >> 8 | (channel_data->data[1] & 0x07FF) << 3);
    sbus_out_data[3] = (uint8_t) ((channel_data->data[1] & 0x07FF) >> 5 | (channel_data->data[2] & 0x07FF) << 6);
    sbus_out_data[4] = (uint8_t) ((channel_data->data[2] & 0x07FF) >> 2);
    sbus_out_data[5] = (uint8_t) ((channel_data->data[2] & 0x07FF) >> 10 | (channel_data->data[3] & 0x07FF) << 1);
    sbus_out_data[6] = (uint8_t) ((channel_data->data[3] & 0x07FF) >> 7 | (channel_data->data[4] & 0x07FF) << 4);
    sbus_out_data[7] = (uint8_t) ((channel_data->data[4] & 0x07FF) >> 4 | (channel_data->data[5] & 0x07FF) << 7);
    sbus_out_data[8] = (uint8_t) ((channel_data->data[5] & 0x07FF) >> 1);
    sbus_out_data[9] = (uint8_t) ((channel_data->data[5] & 0x07FF) >> 9 | (channel_data->data[6] & 0x07FF) << 2);
    sbus_out_data[10] = (uint8_t) ((channel_data->data[6] & 0x07FF) >> 6 | (channel_data->data[7] & 0x07FF) << 5);
    sbus_out_data[11] = (uint8_t) ((channel_data->data[7] & 0x07FF) >> 3);
    sbus_out_data[12] = (uint8_t) ((channel_data->data[8] & 0x07FF));
    sbus_out_data[13] = (uint8_t) ((channel_data->data[8] & 0x07FF) >> 8 | (channel_data->data[9] & 0x07FF) << 3);
    sbus_out_data[14] = (uint8_t) ((channel_data->data[9] & 0x07FF) >> 5 | (channel_data->data[10] & 0x07FF) << 6);
    sbus_out_data[15] = (uint8_t) ((channel_data->data[10] & 0x07FF) >> 2);
    sbus_out_data[16] = (uint8_t) ((channel_data->data[10] & 0x07FF) >> 10 | (channel_data->data[11] & 0x07FF) << 1);
    sbus_out_data[17] = (uint8_t) ((channel_data->data[11] & 0x07FF) >> 7 | (channel_data->data[12] & 0x07FF) << 4);
    sbus_out_data[18] = (uint8_t) ((channel_data->data[12] & 0x07FF) >> 4 | (channel_data->data[13] & 0x07FF) << 7);
    sbus_out_data[19] = (uint8_t) ((channel_data->data[13] & 0x07FF) >> 1);
    sbus_out_data[20] = (uint8_t) ((channel_data->data[13] & 0x07FF) >> 9 | (channel_data->data[14] & 0x07FF) << 2);
    sbus_out_data[21] = (uint8_t) ((channel_data->data[14] & 0x07FF) >> 6 | (channel_data->data[15] & 0x07FF) << 5);
    sbus_out_data[22] = (uint8_t) ((channel_data->data[15] & 0x07FF) >> 3);

    sbus_out_data[23] = 0x00;
    //here we encode the sbus signals back into the stream.
    bool sig_lost = false, failsafe = false;
    //put the statuses back into the signal
    if (channel_data->frame_status == SBUS_SIGNAL_LOST)
    {
        sig_lost = true;
        failsafe = false;
    }
    else if (channel_data->frame_status == SBUS_SIGNAL_FAILSAFE)
    {
        sig_lost = false;
        failsafe = true;
    }
    else if (channel_data->frame_status == SBUS_SIGNAL_FAILSAFE_AND_LOST)
    {
        //there is no signal, and we are in failsafe.
        sig_lost = true;
        failsafe = true;
    }
    if(sig_lost)
    {
        sbus_out_data[23] |= (1 << 2);
    }
    else
    {
        sbus_out_data[23] &= ~(1 << 2);
    }
    if(failsafe)
    {
        sbus_out_data[23] |= (1 << 3);
    }
    else
    {
        sbus_out_data[23] &= ~(1 << 3);
    }
    // footer
    sbus_out_data[24] = 0x00;
    return true;
}
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS METHODS.

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// ALL DONE.
