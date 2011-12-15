/********************************************************************************************************************************
 *
 *  FILE: 		tc.c	
 *
 *  LIBRARY:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	15-12-2012
 *
 *	Functionality to provide implementation for timer/counters in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include ">>>TC_INSERTS_H_FILE_NAME_HERE<<<"

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

/**
* Sets the timer rate by selecting the clk src and prescaler.
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 for success, -1 for error.
*/
int8_t timer::set_rate(timer_rate rate)
{
}

/**
* Loads the timer with a value.
*
* @param value		The value the timer register will have.
* @return 0 for success, -1 for error.
*/
template <typename T>
int8_t timer::load_timer_value(T value)
{
}

/**
* Gets the value of the timer register.
*
* @param Nothing.
* @return T 	The timer value
*/
template <typename T>
T timer::get_timer_value(void)
{
}

/**
* Starts the timer.
*
* @param Nothing
* @return 0 for success, -1 for error.
*/
uint8_t timer::start(void)
{
}

/**
* Stops the timer.
*
* @param Nothing
* @return 0 for success, -1 for error.
*/
uint8_t timer::stop(void)
{
  
}

/**
* Enables the overflow interrupt on this timer
*
* @param  ISR		A pointer to the ISR that will be called when this interrupt is generated.
* @return 0 for success, -1 for error.
*/
int8_t timer::enable_tov_interrupt(void* ISR(void))
{
  
}

/**
* Disables the overflow interrupt on this timer
*
* @param  Nothing.
* @return 0 for success, -1 for error.
*/
int8_t timer::disable_tov_interrupt(void)
{
  
}

/**
* Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disable OC mode
* operation for the specified channel.
*
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
*/
int8_t timer::enable_oc(tc_oc_channel channel, tc_oc_mode mode)
{
  
}

/**
* Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
* enable OC mode itself.
*
* @param  channel		Which channel register to interrupt on.
* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.
* @return 0 for success, -1 for error.
*/
int8_t timer::enable_oc_interrupt(tc_oc_channel channel, void* ISR(void))
{
  
}

/**
* Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
* OC mode operation itself.
*
* @param channel		Which channel register to disable the interrupt on.
* @return 0 for success, -1 for error.
*/
int8_t timer::disable_oc_interrupt(tc_oc_channel channel)
{
  
}

/**
* Sets the channel value for output compare.
*
* @param channel	Which channel to set the OC value for.
* @param value		The value where when the timer reaches it, something will happen.
* @return 0 for success, -1 for error.
*/
template <typename T>
uint8_t timer::set_ocR(tc_oc_channel channel, T value)
{
  
}

/**
* Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
*/
int8_t timer::enable_ic(tc_ic_channel channel, tc_ic_mode mode)
{
  
}

/**
* Enables the input compare interrupt on this timer
*
* @param  channel		Which channel register to interrupt on.
* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.  
* @return 0 for success, -1 for error.
*/
int8_t timer::enable_ic_interrupt(uint8_t channel, void* ISR(void))
{
  
}

/**
* Disables the input compare interrupt on this timer
*
* @param channel		Which channel register to disable the interrupt on.
* @return 0 for success, -1 for error.
*/
int8_t timer::disable_ic_interrupt(uint8_t channel)
{
  
}

/**
* Reads the current input capture register value for the specified channel.
*
* @param channel	Which channel to read the IC value from.
* @return The IC register value.
*/
template <typename T>
T timer::set_ocR(tc_oc_channel channel)
{
  
}

/**
* Gets run whenever the instance of class timer goes out of scope.
* Vacates the semaphore, allowing the timer to be allocated elsewhere.
*
* @param  Nothing.
* @return Nothing.
*/
timer::~timer(void)
{
  
}

/** 
* Allows access to the timer to be relinquished and assumed elsewhere.
*
* @param  Nothing.
* @return Nothing.
*/
void timer::vacate(void)
{
  
}

/**
* Allows a process to request access to a timer and manages the semaphore
* indicating whether access has been granted or not.
*
* @param  timer	Which timer is required.
* @return A timer instance.
*/
static timer::timer_grab(tc_number timer)
{
  
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
