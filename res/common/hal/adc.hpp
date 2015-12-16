// Copyright (C) 2015  Aeronavics Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/**
 *
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		adc.hpp
 *  A header file for the ADC Module of the HAL.
 * 
 *  @brief 
 *  This is the header file which matches adc.cpp.  Implements various functions relating to ADC, transmission
 *  and receiving of messages.
 * 
 *  @author		Sam Dirks
 *
 *  @date		7-12-2015
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2015  Aeronavics Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  @section Description
 *
 * A class for the ADC module of the HAL. Implements various functions relating to ADC hardware 
 * initialisation and ADC of analogue inputs.
 */

#pragma once

// Include the standard C++ definitions.
#include <stddef.h>
#include <stdint.h>

// Include the hal library.
#include "hal/hal.hpp"

// DEFINE PUBLIC MACROS.

// SELECT NAMESPACES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

class Adc_imp;

// FORWARD DECLARE PUBLIC CLASSES AND TYPES.

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

struct Adc_clock_mode
{
	Adc_clock_src_pre clock_src_pre;
	Adc_speed_mode speed_mode;
};

// ADC configuration operation status.
enum Adc_command_status {ADC_CFG_SUCCESS = 0, ADC_CFG_IMMUTABLE = -1, ADC_CFG_FAILED = -2};

class Adc
{
	public:
		// Methods
		
		/**
		 *  Bind the interface to the ADC hardware peripheral.
		 */
		static Adc* bind(void);
		
		~Adc(void);
		
		//Adc common access functions
		//***********************************************************************************/
		
		/**
		 * Set the clock mode of the analogue to digital converter.
		 *
		 * @param	clock_mode The clockmode to set.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_clock_mode(Adc_clock_mode clock_mode);
		
		/**
		 * Enable and disable auxiliary adc supplies.
		 *
		 * @param	auxiliary_supply The auxiliary adc supply to enable or disable.
		 * @param	enable           True to enable, false to disable supply.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status configure_auxiliary_supplies(Adc_auxiliary_supply auxiliary_supply, bool enabled);
		
		/**
		 * Set the multi adc mode.
		 *
		 * @param	multi_adc_mode The multi adc mode to use. See target specific documentation for modes supported.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_multi_adc_mode(Adc_multi_adc_mode multi_adc_mode);
		
		/**
		 * Set the dma mode to use with a multi adc mode.
		 *
		 * @param multi_adc_dma_mode    The dma mode to use. See target specific documentation for modes supported.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_multi_adc_dma_mode(Adc_multi_adc_dma_mode multi_adc_dma_mode);
		
		//Adc unit access functions
		//***********************************************************************************/
		
		/**
		 * Enable the ADC.
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status enable(Adc_unit adc_unit);
		
		/**
		 * Disable the ADC.
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status disable(Adc_unit adc_unit);
		
		/**
		 * Initialise the ADC to default settings
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status initialise(Adc_unit adc_unit);
		
		/**
		 * Start an ADC conversion.
		 *
		 * @param 	adc_unit       The adc unit to which to send the command.
		 * @param	conv_channel   The adc conversion channel which to start.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status start_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel);
		
		/**
		 * Stop an ADC conversion.
		 *
		 * @param 	adc_unit       The adc unit to which to send the command.
		 * @param	conv_channel   The adc conversion channel which to stop.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status stop_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel);
		
		/**
		 * Set the length and each of the inputs to read for a conversion sequence. Adc_input type will be target
		 * dependent to support differential inputs. To prevent the configuration from differing from the programmers
		 * view attempts to set unsupported sequences will fail.
		 *
		 * @param 	adc_unit        The adc unit to which to send the command.
		 * @param	conv_channel    The conversion channel of which to set the conversion sequence.
		 * @param	sequence_length The length of the conversion sequence being set.
		 * @param	input_channel   An array of pointers to arrays that contain the inputs for each position in the conversion sequence.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_conv_sequence_and_length(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t sequence_length, Adc_input_channel** input_channel);
		
		/**
		 * Set the adc to convert only one channel.
		 *
		 * @param	adc_unit        The adc unit to which to send the command.
		 * @param	conv_channel    The conversion channel of which to set the conversion sequence.
		 * @param	input_channel   A pointer to the input to use. This is a pointer to allow an array of two entries to be used for trgets supporting differential inputs.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_single_conversion_input(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_input_channel* input_channel);
		
		/**
		 * Allow setting of input mode unipolar or bipolar.
		 *
		 * @param	adc_unit     The adc unit to which to send the command.
		 * @param	input_mode   The input mode to set.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_input_unipolar_bipolar(Adc_unit adc_unit, Adc_input_mode input_mode);
		
		/**
		 * Get the result of an analogue to digital conversion.
		 * resut_number is the index of the entry in the result buffer to read, valid values will be target dependent.
		 *
		 * @param	adc_unit      The adc unit to which to send the command.
		 * @param	conv_channel  The conversion channel of which to read the adc result.
		 * @param	result_number The result number to read. See target specific documentation for valid options.
		 * @return	The result of the adc operation, see target specific documentation for format.
		 */
		uint32_t get_result(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t result_number);
		
		/**
		 * Check if the previously started conversion has been completed.
		 *
		 * @param	adc_unit      The adc unit to which to send the command.
		 * @param	conv_channel  The conversion channel of which to read the adc result.
		 * @return	Whether the adc conversion has been completed.
		 */
		Adc_conversion_status is_conversion_complete(Adc_unit adc_unit, Adc_conv_channel conv_channel);
		
		/**
		 * Set the data alignment of the converted result
		 *
		 * @param	adc_unit       The adc unit to which to send the command.
		 * @param	data_alignment The alignment of the data.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_data_alignment(Adc_unit adc_unit, Adc_data_alignment data_alignment);
		
		/**
		 * Set the resolution of the analogue to digital conversions
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @param	resolution  The adc resolution to set.
		 * @return	Zero for success, or non-zero for failure. 
		 */
		Adc_command_status set_resolution(Adc_unit adc_unit, Adc_resolution resolution);
		
		/**
		 * Set the operating mode of the adc unit.
		 *
		 * @param 	adc_unit       The adc unit to which to send the command.
		 * @param	operating_mode The operating mode to set the adc unit to. See target specific documentation for options.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_operating_mode(Adc_unit adc_unit, Adc_operating_mode operating_mode);
		
		/**
		 * Set the sampling time of the adc input channels. For ADCs that only have global sampling time setting
		 * channel_number is ignored.
		 *
		 * @param 	adc_unit       The adc unit to which to send the command.
		 * @param	sampling_time  The sampling time to set.
		 * @param	channel_number The channel number of which to set the sampling time. See documentation
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_sampling_time(Adc_unit adc_unit, Adc_sampling_time sampling_time, size_t channel_number);
		
		/**
		 * Set the reference source to use for analogue to digital conversion.
		 *
		 * @param 	adc_unit         The adc unit to which to send the command.
		 * @param	reference_source The adc reference source to use.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_reference_source(Adc_unit adc_unit, Adc_reference_source reference_source);
		
		/**
		 * Enable an adc interrupt with callback.
		 *
		 * @param 	adc_unit         The adc unit to which to send the command.
		 * @param	interrupt_source The adc interrupt source to enable.
		 * @param	callback         The callback to attach. See target specific documentation for context data type.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status enable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source, Callback callback);
		
		/**
		 * Disable an adc interrupt.
		 *
		 * @param 	adc_unit         The adc unit to which to send the command.
		 * @param	interrupt_source The adc interrupt source to disable.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status disable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source);
		
		/**
		 * Set the trigger source to start an analogue to digital conversion.
		 *
		 * @param 	adc_unit       The adc unit to which to send the command.
		 * @param	conv_channel   The conversion channel of which to set the trigger source.
		 * @param	trigger_source The trigger source to use.
		 * @param	trigger_edge   The edge transition of the source to trigger on.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_trigger_source(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_trigger_source trigger_source, Adc_trigger_edge trigger_edge);
		
		/**
		 * Set the mode of the adc watchdog.
		 *
		 * @param 	adc_unit      The adc unit to which to send the command.
		 * @param	watchdog	  The watchdog of which to set the mode.
		 * @param	watchdog_mode The watchdog mode top set.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_watchdog_mode(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_mode watchdog_mode);
		
		/**
		 * Set the thresholds of the adc watchdog.
		 *
		 * @param 	adc_unit       The adc unit to which to send the command.
		 * @param	watchdog	   The watchdog of which to set thresholds.
		 * @param	threshold_high The high threshold of the watchdog.
		 * @param	threshold_low  The low threshold of the watchdog.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_watchdog_thresholds(Adc_unit adc_unit, Adc_watchdog watchdog, uint16_t threshold_high, uint16_t threshold_low);
		
		/**
		 * Set the channel that the watchdog monitors.
		 *
		 * @param 	adc_unit         The adc unit to which to send the command.
		 * @param	watchdog         The watchdog of which to set the monitoring channel.
		 * @param	watchdog_channel The watchdog channel to monitor.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_watchdog_channel(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_channel watchdog_channel);
		
		/**
		 * Set the DMA mode of the adc unit.
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @param	dma_mode    
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_dma_mode(Adc_unit adc_unit, Adc_dma_mode dma_mode);
		
		/**
		 * Set the oversampling mode.
		 *
		 * @param 	adc_unit          The adc unit to which to send the command.
		 * @param	oversampling_mode The oversampling mode to use.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_oversampling_mode(Adc_unit adc_unit, Adc_oversampling_mode oversampling_mode);
		
		/**
		 * Set the oversampling configuration.
		 *
		 * @param 	adc_unit           The adc unit to which to send the command.
		 * @param	oversampling_ratio The oversampling ratio to use.
		 * @param	oversampling_shift The right bit shit to apply to the oversampled value.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_oversampling_configuration(Adc_unit adc_unit, Adc_oversampling_ratio oversampling_ratio, Adc_oversampling_shift oversampling_shift);
		
		/**
		 * Get the adc to perform a calibration.
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status calibrate_adc(Adc_unit adc_unit);
		
		/**
		 * Get the calibration factor from the adc.
		 *
		 * @param 	adc_unit           The adc unit to which to send the command.
		 * @return	The calabration factor of the adc.
		 */
		uint32_t get_adc_calibration_factor(Adc_unit adc_unit);
		
		/**
		 * Set the calibration factor of the adc.
		 *
		 * @param 	adc_unit    The adc unit to which to send the command.
		 * @param	calibration_factor
		 * @return	Zero for success, or non-zero for failure.
		 */
		Adc_command_status set_calibration_factor(Adc_unit adc_unit, uint32_t calibration_factor);
		
	private:
		// Methods
		
		Adc(void); // Poisoned.
	
		Adc(Adc*); // Poisoned.
		
		Adc(Adc_imp*);
		
		Adc operator =(Adc const&); // Poisoned.
		
		// Fields
		
		Adc_imp* imp;
};

// ALL done.