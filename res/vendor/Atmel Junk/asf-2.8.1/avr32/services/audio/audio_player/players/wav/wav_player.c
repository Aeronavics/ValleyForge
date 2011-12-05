/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file ******************************************************************
 *
 * \brief WAV player.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ***************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "compiler.h"
#include "com_task.h"
#include "audio_interface.h"
#include "file.h"

#include "audio_mixer.h"
#include "pcmfmt.h"
#include "conf_audio_player.h"
#include "wavdecode.h"

#define IN_BUFFER_SIZE 512

bool WAVFileGetData(struct tWavInfo *WavInfo)
{
  // How many bytes actually got.
  uint32_t num_bytes_got = 0;

  if(WavInfo->in_buffer_left)
  {
     file_seek(WavInfo->in_buffer_left, FS_SEEK_CUR_RE);
  }

 // gpio_set_gpio_pin(AVR32_PIN_PA07);


  // Copy the requested data from the WAV file to the frame buffer.
  nav_checkdisk_disable();
  if ( ((num_bytes_got = file_read_buf(WavInfo->buffer, IN_BUFFER_SIZE)) < IN_BUFFER_SIZE && !file_eof()))
  {
//    fprintf(stderr, "** Error while reading the WAV file at byte offset %llu.\r\n", offset);
    return false;
  }
  nav_checkdisk_enable();
  //gpio_clr_gpio_pin(AVR32_PIN_PA07);

  WavInfo->buffer_current_pos = WavInfo->buffer;
  WavInfo->in_buffer_left = num_bytes_got;
  return true;
}

extern Ai_player_flag_t g_player_flag;
extern uint32_t  g_player_duration;
extern uint32_t  g_player_currentTime_ms;

bool play_wav(const char *filename, bool verbose)
{
   struct tWavInfo WavInfo;

   bool retval;

   WavInfo.pcm_current_buf = 0;
   WavInfo.pcm_samples_length[WavInfo.pcm_current_buf] = 0;

   gpio_clr_gpio_pin(AVR32_PIN_PA07);
   // Open the WAV file.
   if (!file_open(FOPEN_MODE_R))
   {
      //    fputs("** Cannot open the WAV file.\r\n", stderr);
      goto lerror;
   }

   // Init WavInfo Structure

   // Allocate input buffer

   if((WavInfo.buffer = malloc(IN_BUFFER_SIZE)) == NULL)
   {
      goto lerror;
   }

   WavInfo.in_buffer_left = 0;


   // Allocate the PCM buffers.
   //for (i = 0; i < sizeof(pPCMBuf) / sizeof(pPCMBuf[0]); i++)
   //{
   //  if ((pPCMBuf[i] = malloc(PCM_BUF_BYTE_SIZE)) == NULL)
   //  {
   //      fputs("** Cannot allocate the PCM buffers.\r\n", stderr);
   //    goto lerror;
   //  }
   //}

   // Decode WAV file Header
   if(!wav_header_decode(&WavInfo))
   {
      return;
   }

   // Start the renderer.


   //fputs("Playing WAV file... Press any key to stop.\r\n", stdout);
   audio_mixer_dacs_setup( WavInfo.sampling_rate,
                           WavInfo.nChannels,
                           16,
                           false);

   g_player_currentTime_ms = 0;
   // While there are decoded samples to render.
   while (WAV_Decode(&WavInfo))
   {
      do
      {
      com_task();
      }
      while( g_player_flag.status == PLAYER_FLAG_PAUSE && fat_check_mount_select_open() );


      // Make sure the renderer has started consuming the last block of
      // reconstructed data retrieved.
      while (!audio_mixer_dacs_output(NULL, 0));

      // Render reconstructed data.
      audio_mixer_dacs_output(WavInfo.pcm_samples[WavInfo.pcm_current_buf], WavInfo.pcm_samples_length[WavInfo.pcm_current_buf] / WavInfo.nChannels);

      // Change current PCM buffer.
      WavInfo.pcm_current_buf ^= 1;
      WavInfo.pcm_samples_length[WavInfo.pcm_current_buf] = 0;




      if( g_player_flag.status == PLAYER_FLAG_STOP )
      {
         // Playback stopped
         goto lerror;
      }
   }



  retval = true;
  goto lexit;

lerror:
  retval = false;

lexit:

   // Wait for end of rendering.
   audio_mixer_dacs_flush();



   WAV_Decode_End(&WavInfo);
   // Close the decoder and free all allocated memories.

   free(WavInfo.buffer);
   file_close();

   return retval;
}
