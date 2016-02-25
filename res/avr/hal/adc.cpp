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

/********************************************************************************************************************************
 *
 *  FILE: 			servo.cpp
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Sam Dirks
 *
 *  DATE CREATED:	13-11-2015
 *
 *	Functionality to provide servo operation for avr microprocessors.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>
#include <avr/io.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

class Adc_imp
{
	public:
		// Methods
		
		Adc_imp(void);
		
		~Adc_imp(void);
		
		//Adc common access functions
		//***********************************************************************************/

		Adc_command_status set_clock_mode(Adc_clock_mode clock_mode);

		Adc_command_status configure_auxiliary_supplies(Adc_auxiliary_supply auxiliary_supply, bool enabled);

		Adc_command_status set_multi_adc_mode(Adc_multi_adc_mode multi_adc_mode);

		Adc_command_status set_multi_adc_dma_mode(Adc_multi_adc_dma_mode multi_adc_dma_mode);
		
		//Adc unit access functions
		//***********************************************************************************/
		
		Adc_command_status enable(Adc_unit adc_unit);

		Adc_command_status disable(Adc_unit adc_unit);

		Adc_command_status initialise(Adc_unit adc_unit);

		Adc_command_status start_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel);

		Adc_command_status stop_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel);

		Adc_command_status set_conv_sequence_and_length(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t sequence_length, Adc_input_channel** input_channel);

		Adc_command_status set_single_conversion_input(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_input_channel* input_channel);

		Adc_command_status set_input_unipolar_bipolar(Adc_unit adc_unit, Adc_input_mode input_mode);

		uint32_t get_result(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t result_number);
		
		Adc_conversion_status is_conversion_complete(Adc_unit adc_unit, Adc_conv_channel conv_channel);

		Adc_command_status set_data_alignment(Adc_unit adc_unit, Adc_data_alignment data_alignment);

		Adc_command_status set_resolution(Adc_unit adc_unit, Adc_resolution resolution);

		Adc_command_status set_operating_mode(Adc_unit adc_unit, Adc_operating_mode operating_mode);

		Adc_command_status set_sampling_time(Adc_unit adc_unit, Adc_sampling_time sampling_time, size_t channel_number);

		Adc_command_status set_reference_source(Adc_unit adc_unit, Adc_reference_source reference_source);

		Adc_command_status enable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source, Callback callback);
		
		Adc_command_status disable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source);

		Adc_command_status set_trigger_source(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_trigger_source trigger_source, Adc_trigger_edge trigger_edge);

		Adc_command_status set_watchdog_mode(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_mode watchdog_mode);

		Adc_command_status set_watchdog_thresholds(Adc_unit adc_unit, Adc_watchdog watchdog, uint16_t threshold_high, uint16_t threshold_low);

		Adc_command_status set_watchdog_channel(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_channel watchdog_channel);
		
		Adc_command_status set_dma_mode(Adc_unit adc_unit, Adc_dma_mode dma_mode);
		
		Adc_command_status set_oversampling_mode(Adc_unit adc_unit, Adc_oversampling_mode oversampling_mode);
		
		Adc_command_status set_oversampling_configuration(Adc_unit adc_unit, Adc_oversampling_ratio oversampling_ratio, Adc_oversampling_shift oversampling_shift);
		
		Adc_command_status calibrate_adc(Adc_unit adc_unit);
		
		uint32_t get_adc_calibration_factor(Adc_unit adc_unit);
		
		Adc_command_status set_calibration_factor(Adc_unit adc_unit, uint32_t calibration_factor);
		
	private:
		// Methods
		
		// Fields
		
		Adc_input_channel current_input_channel = ADC_INPUT_CHANNEL_0; // This initial value has no effect as the digital input will be enabled on first input change.
};

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// DECLARE PRIVATE GLOBAL VARIABLES.
Callback callback_vector;

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

Adc* Adc::bind(void)
{
	// Return a singleton instance
	static Adc singleton;
	
	return &singleton;
}

Adc::Adc(void)
{
	static Adc_imp implementation;
	imp = &implementation;
}

Adc::~Adc(void)
{
	// Do nothing.
}

//Adc common access functions
//***********************************************************************************/
Adc_command_status Adc::set_clock_mode(Adc_clock_mode clock_mode)
{
	return imp->set_clock_mode(clock_mode);
}

Adc_command_status Adc::configure_auxiliary_supplies(Adc_auxiliary_supply auxiliary_supply, bool enabled)
{
	return imp->configure_auxiliary_supplies(auxiliary_supply, enabled);
}

Adc_command_status Adc::set_multi_adc_mode(Adc_multi_adc_mode multi_adc_mode)
{
	return imp->set_multi_adc_mode(multi_adc_mode);
}

Adc_command_status Adc::set_multi_adc_dma_mode(Adc_multi_adc_dma_mode multi_adc_dma_mode)
{
	return imp->set_multi_adc_dma_mode(multi_adc_dma_mode);
}

//Adc unit access functions
//***********************************************************************************/

Adc_command_status Adc::enable(Adc_unit adc_unit)
{
	return imp->enable(adc_unit);
}

Adc_command_status Adc::disable(Adc_unit adc_unit)
{
	return imp->disable(adc_unit);
}

Adc_command_status Adc::initialise(Adc_unit adc_unit)
{
	return imp->initialise(adc_unit);
}

Adc_command_status Adc::start_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel)
{
	return imp->start_conversion(adc_unit, conv_channel);
}

Adc_command_status Adc::stop_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel)
{
	return imp->stop_conversion(adc_unit, conv_channel);
}

Adc_command_status Adc::set_conv_sequence_and_length(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t sequence_length, Adc_input_channel** input_channel)
{
	return imp->set_conv_sequence_and_length(adc_unit, conv_channel, sequence_length, input_channel);
}

Adc_command_status Adc::set_single_conversion_input(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_input_channel* input_channel)
{
	return imp->set_single_conversion_input(adc_unit, conv_channel, input_channel);
}

Adc_command_status Adc::set_input_unipolar_bipolar(Adc_unit adc_unit, Adc_input_mode input_mode)
{
	return imp->set_input_unipolar_bipolar(adc_unit, input_mode);
}

uint32_t Adc::get_result(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t result_number)
{
	return imp->get_result(adc_unit, conv_channel, result_number);
}

Adc_conversion_status Adc::is_conversion_complete(Adc_unit adc_unit, Adc_conv_channel conv_channel)
{
	return imp->is_conversion_complete(adc_unit, conv_channel);
}

Adc_command_status Adc::set_data_alignment(Adc_unit adc_unit, Adc_data_alignment data_alignment)
{
	return imp->set_data_alignment(adc_unit, data_alignment);
}

Adc_command_status Adc::set_resolution(Adc_unit adc_unit, Adc_resolution resolution)
{
	return imp->set_resolution(adc_unit, resolution);
}

Adc_command_status Adc::set_operating_mode(Adc_unit adc_unit, Adc_operating_mode operating_mode)
{
	return imp->set_operating_mode(adc_unit, operating_mode);
}

Adc_command_status Adc::set_sampling_time(Adc_unit adc_unit, Adc_sampling_time sampling_time, size_t channel_number)
{
	return imp->set_sampling_time(adc_unit, sampling_time, channel_number);
}

Adc_command_status Adc::set_reference_source(Adc_unit adc_unit, Adc_reference_source reference_source)
{
	return imp->set_reference_source(adc_unit, reference_source);
}

Adc_command_status Adc::enable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source, Callback callback)
{
	return imp->enable_interrupt(adc_unit, interrupt_source, callback);
}

Adc_command_status Adc::disable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source)
{
	return imp->disable_interrupt(adc_unit, interrupt_source);
}

Adc_command_status Adc::set_trigger_source(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_trigger_source trigger_source, Adc_trigger_edge trigger_edge)
{
	return imp->set_trigger_source(adc_unit, conv_channel, trigger_source, trigger_edge);
}

Adc_command_status Adc::set_watchdog_mode(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_mode watchdog_mode)
{
	return imp->set_watchdog_mode(adc_unit, watchdog, watchdog_mode);
}

Adc_command_status Adc::set_watchdog_thresholds(Adc_unit adc_unit, Adc_watchdog watchdog, uint16_t threshold_high, uint16_t threshold_low)
{
	return imp->set_watchdog_thresholds(adc_unit, watchdog, threshold_high, threshold_low);
}

Adc_command_status Adc::set_watchdog_channel(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_channel watchdog_channel)
{
	return imp->set_watchdog_channel(adc_unit, watchdog, watchdog_channel);
}

Adc_command_status Adc::set_dma_mode(Adc_unit adc_unit, Adc_dma_mode dma_mode)
{
	return imp->set_dma_mode(adc_unit, dma_mode);
}

Adc_command_status Adc::set_oversampling_mode(Adc_unit adc_unit, Adc_oversampling_mode oversampling_mode)
{
	return imp->set_oversampling_mode(adc_unit, oversampling_mode);
}

Adc_command_status Adc::set_oversampling_configuration(Adc_unit adc_unit, Adc_oversampling_ratio oversampling_ratio, Adc_oversampling_shift oversampling_shift)
{
	return imp->set_oversampling_configuration(adc_unit, oversampling_ratio, oversampling_shift);
}

Adc_command_status Adc::calibrate_adc(Adc_unit adc_unit)
{
	return imp->calibrate_adc(adc_unit);
}

uint32_t Adc::get_adc_calibration_factor(Adc_unit adc_unit)
{
	return imp->get_adc_calibration_factor(adc_unit);
}

Adc_command_status Adc::set_calibration_factor(Adc_unit adc_unit, uint32_t calibration_factor)
{
	return imp->set_calibration_factor(adc_unit, calibration_factor);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).

Adc_imp::Adc_imp(void)
{
	// Do nothing.
}

Adc_imp::~Adc_imp(void)
{
	// Do nothing.
}

//Adc common access functions
//***********************************************************************************/

Adc_command_status Adc_imp::set_clock_mode(Adc_clock_mode clock_mode)
{
	// NOTE - The ATmega328 implementation does not make use of Adc_speed_mode
	
	switch (clock_mode.clock_src_pre)
	{
		case ADC_SRC_INT_PRE_2:
		{
			ADCSRA &= ~((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_SRC_INT_PRE_4:
		{
			ADCSRA |= (1<<ADPS1);
			ADCSRA &= ~((1<<ADPS0) | (1<<ADPS2));
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_SRC_INT_PRE_8:
		{
			ADCSRA |= (1<<ADPS0) | (1<<ADPS1);
			ADCSRA &= ~(1<<ADPS2);
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_SRC_INT_PRE_16:
		{
			ADCSRA |= (1<<ADPS2);
			ADCSRA &= ~((1<<ADPS0) | (1<<ADPS1));
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_SRC_INT_PRE_32:
		{
			ADCSRA |= (1<<ADPS0) | (1<<ADPS2);
			ADCSRA &= ~(1<<ADPS1);
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_SRC_INT_PRE_64:
		{
			ADCSRA |= (1<<ADPS1) | (1<<ADPS2);
			ADCSRA &= ~(1<<ADPS0);
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_SRC_INT_PRE_128:
		{
			ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
			return ADC_CFG_SUCCESS;
			break;
		}
		default:
		{
			return ADC_CFG_FAILED;
			break;
		}
	}
	
	// We should never reach here.
	return ADC_CFG_FAILED;
}

Adc_command_status Adc_imp::configure_auxiliary_supplies(Adc_auxiliary_supply auxiliary_supply, bool enabled)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_multi_adc_mode(Adc_multi_adc_mode multi_adc_mode)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_multi_adc_dma_mode(Adc_multi_adc_dma_mode multi_adc_dma_mode)
{
	return ADC_CFG_IMMUTABLE;
}

//Adc unit access functions
//***********************************************************************************/

Adc_command_status Adc_imp::enable(Adc_unit adc_unit)
{
	ADCSRA |= (1<<ADEN);
	
	return ADC_CFG_SUCCESS;
}

Adc_command_status Adc_imp::disable(Adc_unit adc_unit)
{
	ADCSRA &= ~(1<<ADEN);
	
	return ADC_CFG_SUCCESS;
}

Adc_command_status Adc_imp::initialise(Adc_unit adc_unit)
{
	// Clear each of the configureation registers to reset defaults. Clock settings are left  untouched.
	ADCSRA = ADCSRA & 0x07;
	ADCSRB = 0x00;
	ADMUX = 0x00;
	
	return ADC_CFG_SUCCESS;
}

Adc_command_status Adc_imp::start_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel)
{
	if ((ADCSRA & (1<<ADSC)) != 0)
	{
		return ADC_CFG_FAILED;
	}
	else
	{
		ADCSRA |= (1<<ADSC);
		return ADC_CFG_SUCCESS;
	}
	
	// We should never reach here.
	return ADC_CFG_FAILED;
}

Adc_command_status Adc_imp::stop_conversion(Adc_unit adc_unit, Adc_conv_channel conv_channel)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_conv_sequence_and_length(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t sequence_length, Adc_input_channel** input_channel)
{
	// NOTE - Input pins on avr prosessors must have their digital input stage disabled to prevent excessive power consumption when used as analog inputs.
	// Ensure the sequence is of the correct length.
	if (sequence_length == 1)
	{
		// Enable the digital input for the analog input being switched away from if the current input is a digital pin.
		if (current_input_channel <= ADC_INPUT_CHANNEL_5)
		{
			DIDR0 &= ~(1<<current_input_channel);
			current_input_channel = input_channel[0][0];
		}
		
		// Disable the digital input if the new input is a digital pin. 
		if (input_channel[0][0] <= ADC_INPUT_CHANNEL_5)
		{
			DIDR0 |= (1<<input_channel[0][0]);
		}
		
		ADMUX = (ADMUX & ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3))) | (input_channel[0][0] & ((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3)));
		return ADC_CFG_SUCCESS;
	}
	else
	{
		return ADC_CFG_FAILED;
	}
	
	// We should never reach here.
	return ADC_CFG_FAILED;
}

Adc_command_status Adc_imp::set_single_conversion_input(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_input_channel* input_channel)
{
	// TODO - Test change to taking input channel as a pointer.
	Adc_input_channel* inputs[1] = {input_channel};
	Adc_input_channel** input = inputs;
	set_conv_sequence_and_length(adc_unit, conv_channel, 1, input);
	
	return ADC_CFG_SUCCESS;
}

Adc_command_status Adc_imp::set_input_unipolar_bipolar(Adc_unit adc_unit, Adc_input_mode input_mode)
{
	return ADC_CFG_IMMUTABLE;
}

uint32_t Adc_imp::get_result(Adc_unit adc_unit, Adc_conv_channel conv_channel, size_t result_number)
{
	uint32_t result = 0;
	result = ADCL;
	result |= ADCH << 8;
	
	ADCSRA &= ~(1<<ADIF); // Clear the conversion complete flag.
	
	return (result & 0xFFFF); // using mask to ensure zeros at non result bits.
}

Adc_conversion_status Adc_imp::is_conversion_complete(Adc_unit adc_unit, Adc_conv_channel conv_channel)
{
	if ((ADCSRA & (1<<ADIF)) != 0)
	{
		return ADC_CONVERSION_COMPLETE;
	}
	
	return ADC_CONVERSION_NOT_COMPLETE;
}

Adc_command_status Adc_imp::set_data_alignment(Adc_unit adc_unit, Adc_data_alignment data_alignment)
{
	switch (data_alignment)
	{
		case ADC_DATA_RIGHT_ALIGNED:
		{
			ADMUX &= ~(1<<ADLAR);
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_DATA_LEFT_ALIGNED:
		{
			ADMUX |= (1<<ADLAR);
			return ADC_CFG_SUCCESS;
			break;
		}
		default:
		{
			return ADC_CFG_FAILED;
			break;
		}
	}
	
	// We should never reach here.
	return ADC_CFG_FAILED;
}

Adc_command_status Adc_imp::set_resolution(Adc_unit adc_unit, Adc_resolution resolution)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_operating_mode(Adc_unit adc_unit, Adc_operating_mode operating_mode)
{
	switch (operating_mode)
	{
		case ADC_OPERATING_MODE_MANUAL:
		{
			ADCSRA &= ~(1<<ADATE);
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_OPERATING_MODE_TRIGGERED:
		{
			ADCSRA |= (1<<ADATE);
			return ADC_CFG_SUCCESS;
			break;
		}
		default:
		{
			return ADC_CFG_FAILED;
			break;
		}
	}
	
	// We should never reach here.
	return ADC_CFG_FAILED;
}

Adc_command_status Adc_imp::set_sampling_time(Adc_unit adc_unit, Adc_sampling_time sampling_time, size_t channel_number)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_reference_source(Adc_unit adc_unit, Adc_reference_source reference_source)
{
	switch (reference_source)
	{
		case ADC_REFERENCE_SOURCE_AREF:
		{
			ADMUX &= ~((1<<REFS0) | (1<<REFS1));
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_REFERENCE_SOURCE_AVCC_CAP:
		{
			// NOTE - Must maintain order of set and clear to ensure a reserved state is not entered.
			ADMUX &= ~(1<<REFS1);
			ADMUX |= (1<<REFS0);
			return ADC_CFG_SUCCESS;
			break;
		}
		case ADC_REFERENCE_SOURCE_1_1V_CAP:
		{
			ADMUX |= (1<<REFS0) | (1<<REFS1);
			return ADC_CFG_SUCCESS;
			break;
		}
		default:
		{
			return ADC_CFG_FAILED;
			break;
		}
	}
	
	// We should never reach here.
	return ADC_CFG_FAILED;
}

Adc_command_status Adc_imp::enable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source, Callback callback)
{
	callback_vector = callback;
	
	ADCSRA |= (1<<ADIE);
	
	return ADC_CFG_SUCCESS;
}
	
Adc_command_status Adc_imp::disable_interrupt(Adc_unit adc_unit, Adc_interrupt_source interrupt_source)
{
	callback_vector = nullptr;
	
	ADCSRA &= ~(1<<ADIE);
	
	return ADC_CFG_SUCCESS;
}

Adc_command_status Adc_imp::set_trigger_source(Adc_unit adc_unit, Adc_conv_channel conv_channel, Adc_trigger_source trigger_source, Adc_trigger_edge trigger_edge)
{
	// NOTE - adc_unit, conv_channel and trigger_edge are not used for the 328p AVR microcontroller.
	
	ADCSRB = (ADCSRB & ~((1<<ADTS0) | (1<<ADTS1) | (1<<ADTS2))) | (trigger_source & ((1<<ADTS0) | (1<<ADTS1) | (1<<ADTS2)));

	return ADC_CFG_SUCCESS;
}

Adc_command_status Adc_imp::set_watchdog_mode(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_mode watchdog_mode)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_watchdog_thresholds(Adc_unit adc_unit, Adc_watchdog watchdog, uint16_t threshold_high, uint16_t threshold_low)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_watchdog_channel(Adc_unit adc_unit, Adc_watchdog watchdog, Adc_watchdog_channel watchdog_channel)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_dma_mode(Adc_unit adc_unit, Adc_dma_mode dma_mode)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_oversampling_mode(Adc_unit adc_unit, Adc_oversampling_mode oversampling_mode)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_oversampling_configuration(Adc_unit adc_unit, Adc_oversampling_ratio oversampling_ratio, Adc_oversampling_shift oversampling_shift)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::calibrate_adc(Adc_unit adc_unit)
{
	return ADC_CFG_IMMUTABLE;
}

uint32_t Adc_imp::get_adc_calibration_factor(Adc_unit adc_unit)
{
	return ADC_CFG_IMMUTABLE;
}

Adc_command_status Adc_imp::set_calibration_factor(Adc_unit adc_unit, uint32_t calibration_factor)
{
	return ADC_CFG_IMMUTABLE;
}

// IMPLEMENT INTERRUPT HANDLERS

ISR(ADC_vect)
{
	static uint32_t result;
	result = ADCL;
	result |= ADCH << 8;
	result &= 0xFFFF; // using mask to ensure zeros at non result bits.
	
	if (callback_vector != nullptr)
	{
		callback_vector((void*)&result);
	}
}

// ALL DONE.