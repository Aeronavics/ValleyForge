/********************************************************************************************************************************
 *
 *  FILE: 		tc.c	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	15-12-2011
 *
 *	Functionality to provide implementation for timer/counters in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "tc.h"

// INCLUDE SYSTEM HEADER FILES

#include <avr/io.h>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.
/*Number of interrupts of all types across all timers & channels.*/
#define NUM_TIMER_INTERRUPTS	23	


// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
* Starts Timer 0 by manipulating the TCCR0A & TCCR0B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* * @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer0(timer_rate rate);

/**
* Starts Timer 1 by manipulating the TCCR1A & TCCR1B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer1(timer_rate rate);

/**
* Starts Timer 2 by manipulating the TCCR2A & TCCR2B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer2(timer_rate rate);

/**
* Starts Timer 3 by manipulating the TCCR3A & TCCR3B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer3(timer_rate rate);

/**
* Starts Timer 4 by manipulating the TCCR4A & TCCR4B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer4(timer_rate rate);

/**
* Starts Timer 5 by manipulating the TCCR5A & TCCR5B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer5(timer_rate rate);

/**
* Enables Output Compare operation on Timer Counter 0.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer0(tc_oc_channel channel, tc_oc_mode mode);

/**
* Enables Output Compare operation on Timer Counter 1.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer1(tc_oc_channel channel, tc_oc_mode mode);

/**
* Enables Output Compare operation on Timer Counter 2.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer2(tc_oc_channel channel, tc_oc_mode mode);

/**
* Enables Output Compare operation on Timer Counter 3.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer3(tc_oc_channel channel, tc_oc_mode mode);

/**
* Enables Output Compare operation on Timer Counter 4.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer4(tc_oc_channel channel, tc_oc_mode mode);

/**
* Enables Output Compare operation on Timer Counter 5.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer5(tc_oc_channel channel, tc_oc_mode mode);

/**
* Enables input capture mode for Timer Counter 1.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
*/
int8_t enable_ic_timer1(tc_ic_channel channel, tc_ic_mode mode);

/**
* Enables input capture mode for Timer Counter 3.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
*/
int8_t enable_ic_timer3(tc_ic_channel channel, tc_ic_mode mode);

/**
* Enables input capture mode for Timer Counter 4.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
*/
int8_t enable_ic_timer4(tc_ic_channel channel, tc_ic_mode mode);

/**
* Enables input capture mode for Timer Counter 5.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
*/
int8_t enable_ic_timer5(tc_ic_channel channel, tc_ic_mode mode);

// DEFINE PRIVATE TYPES AND STRUCTS.

/**
 * Class to implement the functionality
 * required for the timer/counters.
 */
class timer_imp
{
    public:
      
	// Functions
	
	/**
	* Sets the timer rate by selecting the clk src and prescaler.
	* 
	* Store the timer number, prescalar and clock settings into fields
	* within the implementation.
	* 
	* @param  timer_rate	Settings for clock source and prescaler.
	* @return 0 for success, -1 for error.
	*/
	int8_t set_rate(timer_rate rate, timer_indentifier timer);
	
	
	/**
	* Loads the timer with a value.
	*
	* @param value		The value the timer register will have.
 	* @return 0 for success, -1 for error.
	*/
	template <typename T>
	int8_t load_timer_value(T value);
	

	/**
	* Gets the value of the timer register.
	*
	* @return T 	The timer value
	*/
	template <typename T>
	T get_timer_value(void);
	

	/**
	* Starts the timer.
	*
	* @return 0 for success, -1 for error.
	*/
	int8_t start(void);
	

	/**
	* Stops the timer.
	*
	* @return 0 for success, -1 for error.
	*/
	int8_t stop(void);	

	/**
	* Enables the overflow interrupt on this timer
	*
	* @param  ISR		A pointer to the ISR that will be called when this interrupt is generated.
	* @return 0 for success, -1 for error.
	*/
	int8_t enable_tov_interrupt(void* ISR(void));
	
	/**
	* Disables the overflow interrupt on this timer
	*
	* @param  Nothing.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_tov_interrupt(void);
	
	/**
	* Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disable OC mode
	* operation for the specified channel.
	*
	* @param channel		Which OC channel should be enabled.
	* @param mode			Which mode the OC channel should be set to.
	*/
	int8_t enable_oc(tc_oc_channel channel, tc_oc_mode mode);
	
	/**
	* Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
	* enable OC mode itself.
	*
	* @param  channel		Which channel register to interrupt on.
	* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.
	* @return 0 for success, -1 for error.
	*/
	int8_t enable_oc_interrupt(tc_oc_channel channel, void* ISR(void));
	
	/**
	* Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
	* OC mode operation itself.
	*
	* @param channel		Which channel register to disable the interrupt on.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_oc_interrupt(tc_oc_channel channel);
	
	/**
	* Sets the channel value for output compare.
	*
	* @param channel	Which channel to set the OC value for.
	* @param value		The value where when the timer reaches it, something will happen.
	* @return 0 for success, -1 for error.
	*/
	template <typename T>
	uint8_t set_ocR(tc_oc_channel channel, T value);

	/**
	* Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
	* operation for the specified channel.
	*
	* @param channel		Which IC channel should be enabled.
	* @param mode			Which mode the IC channel should be set to.
	*/
	int8_t enable_ic(tc_ic_channel channel, tc_ic_mode mode);

	/**
	* Enables the input compare interrupt on this timer
	*
	* @param  channel		Which channel register to interrupt on.
	* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.  
	* @return 0 for success, -1 for error.
	*/
	int8_t enable_ic_interrupt(uint8_t channel, void* ISR(void));

	/**
	* Disables the input compare interrupt on this timer
	*
	* @param channel		Which channel register to disable the interrupt on.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_ic_interrupt(uint8_t channel);

	/**
	* Reads the current input capture register value for the specified channel.
	*
	* @param channel	Which channel to read the IC value from.
	* @return The IC register value.
	*/
	template <typename T>
	T get_ocR(tc_oc_channel channel);

	/** 
	* Allows access to the timer to be relinquished and assumed elsewhere.
	*
	* @param  Nothing.
	* @return Nothing.
	*/
	void vacate(void);
	
	//Private functions
	
	//Fields
	/**
	* Identifier of the current timer it is attached to
	*/
	timer_identifier timer_id;
      
	/**
	* Preserved prescalar value and clock source
	*/
	timer_rate preserved_rate;
  
}

// DECLARE PRIVATE GLOBAL VARIABLES.

volatile static voidFuncPtr timerInterrupts[NUM_TIMER_INTERRUPTS];

/*Create an array of timer implementation*/
timer_imp timer_imps[NUM_TIMERS];	/*TODO Possibly make into a two-dimensional array of some sort to provide semaphores on each channel of each timer*/

/*Enumerated list of timer interrupts for use in accessing the appropriate function pointer from the function pointer array*/
enum timer_interrupts {TIMER0_COMPA_int, TIMER0_COMPB_int, TIMER0_OVF_int, TIMER1_CAPT_int, TIMER1_COMPA_int, TIMER1_COMPB_int, TIMER1_OVF_int, TIMER2_CAPT_int, TIMER2_COMPA_int, TIMER2_COMPB_int, TIMER2_OVF_int, TIMER3_CAPT_int, TIMER3_COMPA_int, TIMER3_COMPB_int, TIMER3_COMPC_int, TIMER3_OVF_int, TIMER4_CAPT_int, TIMER4_COMPA_int, TIMER4_COMPB_int, TIMER3_COMPC_int, TIMER4_OVF_int, TIMER5_CAPT_int, TIMER5_COMPA_int, TIMER5_COMPB_int, TIMER5_COMPC_int, TIMER5_OVF_int};

// IMPLEMENT PUBLIC FUNCTIONS.

/**
* Sets the timer rate by selecting the clk src and prescaler.
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 for success, -1 for error.
*/
int8_t timer::set_rate(timer_rate rate)
{
  /*Preserve the prescalar and clock source now*/
  preserved_rate = rate;
  
  /*Call the set_rate function within the implementation
   * to save the timer number and prescalar settings etc*/
  (imp->set_rate(rate, timer_id));
  
  return 0;
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
  return(imp->load_timer_value(timer_id.number));
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
  return(imp->get_timer_value <T> (timer_id.number));
}

/**
* Starts the timer.
*
* @param Nothing
* @return 0 for success, -1 for error.
*/
int8_t timer::start(void)
{
  return(imp->start(preserved_rate, timer_id.number));
}

/**
* Stops the timer.
*
* @param Nothing
* @return 0 for success, -1 for error.
*/
int8_t timer::stop(void)
{
  return(imp->stop(timer_id.number));
}

/**
* Enables the overflow interrupt on this timer
*
* @param  ISR		A pointer to the ISR that will be called when this interrupt is generated.
* @return 0 for success, -1 for error.
*/
int8_t timer::enable_tov_interrupt(void* ISR(void))
{
  return(imp->enable_tov_interrupt(void* ISR(void)));
}

/**
* Disables the overflow interrupt on this timer
*
* @param  Nothing.
* @return 0 for success, -1 for error.
*/
int8_t timer::disable_tov_interrupt(void)
{
  return(imp->disable_tov_interrupt());
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
  return (imp->enable_oc(tc_oc_channel, tc_oc_mode mode));
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
  return (imp->enable_oc(tc_oc_channel, ISR);
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
  return (imp->disable_oc_interrupt(channel));
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
  return (imp->set_ocR <T> (channel, value));
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
  return (imp->enable_ic(channel, mode));
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
  return (imp->enable_ic_interrupt(channel, ISR));
}

/**
* Disables the input compare interrupt on this timer
*
* @param channel		Which channel register to disable the interrupt on.
* @return 0 for success, -1 for error.
*/
int8_t timer::disable_ic_interrupt(uint8_t channel)
{
  return (imp->disable_ic_interrupt(channel, ISR));
}

/**
* Reads the current input capture register value for the specified channel.
*
* @param channel	Which channel to read the IC value from.
* @return The IC register value.
*/
template <typename T>
T timer::get_ocR(tc_oc_channel channel)
{
  return (imp->get_ocR(channel));
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
  /*TODO vacate the timer semaphore here*/
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
static timer timer::grab(tc_number timer)
{
  /* TODO add possible semaphore functionality in here*/
  
  /* Save the timer number in a field within the implementation here*/
  timer_id.number = timer;
  
  /* Set the local field 'imp' pointer to point to the specific
   * implementation of timer_imp */
  return timer(&timer_imps[timer]);
  
}

// IMPLEMENT PRIVATE FUNCTIONS.

timer::timer(timer_imp* implementation)
{
  /*attach the timer implementation*/
  imp = implementation;
}

/**
* Sets the timer rate by selecting the clk src and prescaler.
* 
* Store the timer number, prescalar and clock settings into fields
* within the implementation.
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::set_rate(timer_rate rate, timer_indentifier timer)
{
  /*Preserve the clock and prescalar settings as well as the timer number
    * within the implementation fields*/
  preserved_rate = rate;
  timer_id = timer;
}

/**
* Loads the timer with a value.
*
* @param value		The value the timer register will have.
* @return 0 for success, -1 for error.
*/
template <typename T>
int8_t timer_imp::load_timer_value(T value)
{
  /*Switch which TCNTn registers are edited based on the timer number*/
  switch(timer_id.number)
  {
    case TC_0:
    {
      //stop the timer	(to avoid a compare match on restart)
      /*edit the TCNT0 register*/
      TCNT0 = value;
      //restart the timer
      break;
    }
    case TC_1:
    {
      //stop the timer	(to avoid a compare match on restart)
      /*edit the TCNT1H & TCNT1L (combined TCNT1) registers*/
      TCNT1 = value;
      //restart the timer
      break;
    }
    case TC_2:
    {
      //stop the timer	(to avoid a compare match on restart)
      /*edit the TCNT2 register*/
      TCNT2 = value;
      //restart the timer
      break;
    }
    case TC_3:
    {
      //stop the timer	(to avoid a compare match on restart)
      /*edit the TCNT3H & TCNT3L (combined TCNT3) registers*/
      TCNT3 = value;
      //restart the timer
      break;
    }
    case TC_4:
    {
      //stop the timer	(to avoid a compare match on restart)
      /*edit the TCNT4H & TCNT4L (combined TCNT4) registers*/
      TCNT4 = value;
      //restart the timer
      break;
    }
    case TC_5:
    {
      //stop the timer	(to avoid a compare match on restart)
      /*edit the TCNT5H & TCNT5L (combined TCNT5) registers*/
      TCNT5 = value;
      //restart the timer
      break;
    }
  }
}

/**
* Gets the value of the timer register.
*
* @return T 	The timer value
*/
template <typename T>
T timer_imp::get_timer_value(void)
{
  /*Switch which TCNTn registers are read based on the timer number*/
  switch(timer_id.number)
  {
    case TC_0:
    {
      /*read the TCNT0 register*/
      return (TCNT0);
      break;
    }
    case TC_1:
    {
      /*read the TCNT1 register*/
      return (TCNT1);
      break;
    }
    case TC_2:
    {
      /*read the TCNT2 register*/
      return (TCNT2);
      break;
    }
    case TC_3:
    {
      /*read the TCNT3 register*/
      return (TCNT3);
      break;
    }
    case TC_4:
    {
      /*read the TCNT4 register*/
      return (TCNT4);
      break;
    }
    case TC_5:
    {
      /*read the TCNT5 register*/
      return (TCNT5);
      break;
    }
  }
}

/**
* Starts the timer.
*
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::start(void)
{
  /*Switch which registers are edited based on the timer number*/
  switch(timer_id.number)
  {
    case TC_0:
    {
      /*edit the TCCR0A and TCCR0B registers*/
      start_timer0(preserved_rate);
      break;
    }
    case TC_1:
    {
      /*edit the TCCR1A and TCCR1B registers*/
      start_timer1(preserved_rate);
      break;
    }
    case TC_2:
    {
      /*edit the TCCR2A and TCCR2B registers*/
      start_timer2(preserved_rate);
      break;
    }
    case TC_3:
    {
      /*edit the TCCR3A and TCCR3B registers*/
      start_timer3(preserved_rate);
      break;
    }
    case TC_4:
    {
      /*edit the TCCR4A and TCCR4B registers*/
      start_timer4(preserved_rate);
      break;
    }
    case TC_5:
    {
      /*edit the TCCR5A and TCCR5B registers*/
      start_timer5(preserved_rate);
      break;
    }
  }
  return 0;	//How to return -1 in case of an error?
}

/**
* Stops the timer.
*
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::stop(void)
{
  /*Switch which TCNTn registers are edited based on the timer number*/
  switch(timer_id.number)
  {
    case TC_0:
    {
      /*edit the TCCR0B register*/
      TCCR0B &= (~(1 << CS02) & ~(1 << CS01) & ~(1 << CS00));
      break;
    }
    case TC_1:
    {
      /*edit the TCCR1B register*/
      TCCR1B &= (~(1 << CS12) & ~(1 << CS11) & ~(1 << CS10))
      break;
    }
    case TC_2:
    {
      /*edit the TCCR2B register*/
      TCCR2B &= (~(1 << CS22) & ~(1 << CS21) & ~(1 << CS20))
      break;
    }
    case TC_3:
    {
      /*edit the TCCR3B register*/
      TCCR3B &= (~(1 << CS32) & ~(1 << CS31) & ~(1 << CS30))
      break;
    }
    case TC_4:
    {
      /*edit the TCCR4B register*/
      TCCR4B &= (~(1 << CS42) & ~(1 << CS41) & ~(1 << CS40))
      break;
    }
    case TC_5:
    {
      /*edit the TCCR5B register*/
      TCCR5B &= (~(1 << CS52) & ~(1 << CS51) & ~(1 << CS50))
      break;
    }
  }
  return 0;	//How to return -1?
}

/**
* Enables the overflow interrupt on this timer
*
* @param  ISR		A pointer to the ISR that will be called when this interrupt is generated.
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::enable_tov_interrupt(void* ISR(void))
{
   /* Set the TCCRnA and TCCRnB WGMn2:0 bits to 0 for normal operation where the timer/counter
    * counting direction is always incremented from 0x00(00) to 0xFF(FF) (16-bit implementation)
    * and the TOVn flag is set when the counter is reset to 0x00(00).
    *	
    * Set the appropriate registers depedning on which timer/counter implementation
    * is for.
    * 
    * In addition, place the user-provided ISR into the appropriate position of the timer_interrupts
    * ISR
    * 
    * 
    */
  switch(timer_id.number)
  {
    case TC_0:
    {
      /*Edit the TCCR0A and TCCR0B registers*/
      TCCR0A &= (~(1 << WGM01) & ~(1 << WGM00));
      TCCR0B &= ~(1 << WGM02);
      /*edit the TIMSK0 register to enable timer 0 overflow*/
      TIMSK0 |= (1 << TOIE0);
      /*edit the TIFR0 register to clear overflow event (not strictly necessary)*/
      TIFR0 |= (1 << TOV0);
      /*place ISR pointer in timer_interrupts array*/
      timer_interrupts[TIMER0_OVF_int] = ISR;
      break;
    }
    case TC_1:
    {
      /*Edit the TCCR0A and TCCR0B registers*/
      TCCR1A &= (~(1 << WGM11) & ~(1 << WGM10));
      TCCR1B &= ~(1 << WGM12);
      /*edit the TIMSK1 register to enable timer 1 overflow*/
      TIMSK1 |= (1 << TOIE1);
      /*edit the TIFR0 register to clear overflow event (not strictly necessary)*/
      TIFR1 |= (1 << TOV1);
      /*place ISR pointer in timer_interrupts array*/
      timer_interrupts[TIMER1_OVF_int] = ISR;
      break;
    }
    case TC_2:
    {
      /*Edit the TCCR0A and TCCR0B registers*/
      TCCR2A &= (~(1 << WGM21) & ~(1 << WGM20));
      TCCR2B &= ~(1 << WGM22);
      /*edit the TIMSK2 register to enable timer 2 overflow*/
      TIMSK2 |= (1 << TOIE2);
      /*edit the TIFR0 register to clear overflow event (not strictly necessary)*/
      TIFR2 |= (1 << TOV2);
      /*place ISR pointer in timer_interrupts array*/
      timer_interrupts[TIMER2_OVF_int] = ISR;
      break;
    }
    case TC_3:
    {
      /*Edit the TCCR0A and TCCR0B registers*/
      TCCR3A &= (~(1 << WGM31) & ~(1 << WGM30));
      TCCR3B &= ~(1 << WGM32);
      /*edit the TIMSK3 register to enable timer 3 overflow*/
      TIMSK3 |= (1 << TOIE3);
      /*edit the TIFR0 register to clear overflow event (not strictly necessary)*/
      TIFR3 |= (1 << TOV3);
      /*place ISR pointer in timer_interrupts array*/
      timer_interrupts[TIMER3_OVF_int] = ISR;
      break;
    }
    case TC_4:
    {
      /*Edit the TCCR0A and TCCR0B registers*/
      TCCR4A &= (~(1 << WGM41) & ~(1 << WGM40));
      TCCR4B &= ~(1 << WGM42);
      /*edit the TIMSK4 register to enable timer 4 overflow*/
      TIMSK4 |= (1 << TOIE4);
      /*edit the TIFR0 register to clear overflow event (not strictly necessary)*/
      TIFR4 |= (1 << TOV4);
      /*place ISR pointer in timer_interrupts array*/
      timer_interrupts[TIMER4_OVF_int] = ISR;
      break;
    }
    case TC_5:
    {
      /*Edit the TCCR0A and TCCR0B registers*/
      TCCR5A &= (~(1 << WGM51) & ~(1 << WGM50));
      TCCR5B &= ~(1 << WGM52);
      /*edit the TIMSK5 register to enable timer 5 overflow*/
      TIMSK5 |= (1 << TOIE5);
      /*edit the TIFR0 register to clear overflow event (not strictly necessary)*/
      TIFR5 |= (1 << TOV5);
      /*place ISR pointer in timer_interrupts array*/
      timer_interrupts[TIMER5_OVF_int] = ISR;
      break;
    }
  }
  
  return 0;	/* How to detect error states? TODO*/
}

/**
* Disables the overflow interrupt on this timer
*
* @param  Nothing.
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::disable_tov_interrupt(void)
{
  /*
   * To disable the timer overflow interrupt
   * clear the TOIEn bit in the TIMSKn register
   */
  switch(timer_id.number)
    {
      case TC_0:
      {
	TIMSK0 &= ~(1 << TOIE0);
	/*replace ISR pointer in timer_interrupts array with NULL to prevent an ISR firing (just in case)*/
	timer_interrupts[TIMER0_OVF_int] = NULL;
	break;
      }
      case TC_1:
      {
	TIMSK1 &= ~(1 << TOIE1);
	/*replace ISR pointer in timer_interrupts array with NULL to prevent an ISR firing (just in case)*/
	timer_interrupts[TIMER1_OVF_int] = NULL;
	break;
      }
      case TC_2:
      {
	TIMSK2 &= ~(1 << TOIE2);
	/*replace ISR pointer in timer_interrupts array with NULL to prevent an ISR firing (just in case)*/
	timer_interrupts[TIMER2_OVF_int] = NULL;
	break;
      }
      case TC_3:
      {
	TIMSK3 &= ~(1 << TOIE3);
	/*replace ISR pointer in timer_interrupts array with NULL to prevent an ISR firing (just in case)*/
	timer_interrupts[TIMER3_OVF_int] = NULL;
	break;
      }
      case TC_4:
      {
	TIMSK4 &= ~(1 << TOIE4);
	/*replace ISR pointer in timer_interrupts array with NULL to prevent an ISR firing (just in case)*/
	timer_interrupts[TIMER4_OVF_int] = NULL;
	break;
      }
      case TC_5:
      {
	TIMSK5 &= ~(1 << TOIE5);
	/*replace ISR pointer in timer_interrupts array with NULL to prevent an ISR firing (just in case)*/
	timer_interrupts[TIMER5_OVF_int] = NULL;
	break;
      }
    }
    
    return 0;	/* How to detect error states? TODO*/
}

/**
* Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disable OC mode
* operation for the specified channel.
*
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t timer_imp::enable_oc(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare mode depending on which timer is used for
   * implementation
   */
  switch(timer_id.number)
  {
    case TC_0:
    {
      return (enable_oc_timer0(channel, mode));
      break;
    }
    case TC_1:
    {
      return (enable_oc_timer1(channel, mode));
      break;
    }
    case TC_2:
    {
      return (enable_oc_timer2(channel, mode));
      break;
    }
    case TC_3:
    {
      return (enable_oc_timer3(channel, mode));
      break;
    }
    case TC_4:
    {
      return (enable_oc_timer4(channel, mode));
      break;
    }
    case TC_5:
    {
      return (enable_oc_timer5(channel, mode));
      break;
    }
  }
  return 0;	
}

/**
* Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
* enable OC mode itself.
*
* @param  channel		Which channel register to interrupt on.
* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::enable_oc_interrupt(tc_oc_channel channel, void* ISR(void))
{
  /* Switch the process of enabling output compare interrupts depending on which timer is used for
   * implementation
   */
  switch(timer_id.number)
  {
    case TC_0:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK0 |= (1 << OCIE0A);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER0_COMPA_int] = ISR;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK0 |= (1 << OCIE0B);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER0_COMPB_int] = ISR;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_1:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK1 |= (1 << OCIE1A);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER1_COMPA_int] = ISR;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK1 |= (1 << OCIE1B);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER1_COMPB_int] = ISR;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK1 |= (1 << OCIE1C);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER1_COMPC_int] = ISR;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_2:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK2 |= (1 << OCIE2A);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER2_COMPA_int] = ISR;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK2 |= (1 << OCIE2B);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER2_COMPB_int] = ISR;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_3:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK3 |= (1 << OCIE3A);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER3_COMPA_int] = ISR;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK3 |= (1 << OCIE3B);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER3_COMPB_int] = ISR;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK3 |= (1 << OCIE3C);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER3_COMPC_int] = ISR;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_4:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK4 |= (1 << OCIE4A);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER4_COMPA_int] = ISR;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK4 |= (1 << OCIE4B);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER4_COMPB_int] = ISR;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK4 |= (1 << OCIE4C);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER4_COMPC_int] = ISR;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_5:
    {
       /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK5 |= (1 << OCIE5A);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER5_COMPA_int] = ISR;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK5 |= (1 << OCIE5B);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER5_COMPB_int] = ISR;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Enable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK5 |= (1 << OCIE5C);
	 /* Store the ISR function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER5_COMPC_int] = ISR;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
  }
  return 0;
}

/**
* Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
* OC mode operation itself.
*
* @param channel		Which channel register to disable the interrupt on.
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::disable_oc_interrupt(tc_oc_channel channel)
{
 /* Switch the process of disabling output compare interrupts depending on which timer is used for
   * implementation
   */
  switch(timer_id.number)
  {
    case TC_0:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK0 &= ~(1 << OCIE0A);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER0_COMPA_int] = NULL;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK0 &= ~(1 << OCIE0B);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER0_COMPB_int] = NULL;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_1:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK1 &= ~(1 << OCIE1A);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER1_COMPA_int] = NULL;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK1 &= ~(1 << OCIE1B);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER1_COMPB_int] = NULL;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK1 &= ~(1 << OCIE1C);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER1_COMPC_int] = NULL;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_2:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK2 &= ~(1 << OCIE2A);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER2_COMPA_int] = NULL;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK2 &= ~(1 << OCIE2B);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER2_COMPB_int] = NULL;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_3:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK3 &= ~(1 << OCIE3A);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER3_COMPA_int] = NULL;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK3 &= ~(1 << OCIE3B);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER3_COMPB_int] = NULL;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK3 &= ~(1 << OCIE3C);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER3_COMPC_int] = NULL;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_4:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK4 &= ~(1 << OCIE4A);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER4_COMPA_int] = NULL;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK4 &= ~(1 << OCIE4B);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER4_COMPB_int] = NULL;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK4 &= ~(1 << OCIE4C);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER4_COMPC_int] = NULL;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_5:
    {
       /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK5 &= ~(1 << OCIE5A);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER5_COMPA_int] = NULL;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK5 &= ~(1 << OCIE5B);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER5_COMPB_int] = NULL;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Disable the OCIEnX bit in the TIMSKn register to allow output compare interrupts */
	 TIMSK5 &= ~(1 << OCIE5C);
	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
	 timer_interrupts[TIMER5_COMPC_int] = NULL;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
  }
  return 0; 
}

/**
* Sets the channel value for output compare.
*
* @param channel	Which channel to set the OC value for.
* @param value		The value where when the timer reaches it, something will happen.
* @return 0 for success, -1 for error.
*/
template <typename T>
uint8_t timer_imp::set_ocR(tc_oc_channel channel, T value)
{
  /* Switch the process of disabling output compare interrupts depending on which timer is used for
   * implementation
   */
  switch(timer_id.number)
  {
    case TC_0:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR0A = value;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR0B = value;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_1:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	/* Write to the OCRnX register to set the output compare value */
	 OCR1A = value;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR1B = value;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR1C = value;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_2:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR2A = value;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR2B = value;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_3:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR3A = value;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR3B = value;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR3C = value;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_4:
    {
     /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR4A = value;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR4B = value;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR4C = value;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
    case TC_5:
    {
       /* Switch which channel is modified based on the channel provided
      */
     switch(channel)
     {
       case TC_OC_A:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR5A = value;
	 
	 break;
       }
       case TC_OC_B:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR5B = value;
	 
	 break;
       }
       case TC_OC_C:
       {
	 /* Write to the OCRnX register to set the output compare value */
	 OCR5C = value;
	 
	 break;
       }
       default:		/* Not a valid channel for this timer */
	 return -1;
     }	 
      break;
    }
  }
  return 0;   
}

/**
* Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
*/
int8_t timer_imp::enable_ic(tc_ic_channel channel, tc_ic_mode mode)
{
  /* Switch depending on which timer is saved in the implementation */
  switch (timer_id.number)
  {
    case TC_1:
    {
      return(enable_ic_timer1(channel, mode));
      break;
    }
    case TC_3:
    {
      return(enable_ic_timer3(channel, mode));
      break;
    }
    case TC_4:
    {
      return(enable_ic_timer4(channel, mode));
      break;
    }
    case TC_5:
    {
      return(enable_ic_timer5(channel, mode));
      break;
    }
    default:	/* Invalid timer number supplied */
      return -1;      
  }
  return 0;    
}

/**
* Enables the input compare interrupt on this timer
*
* @param  channel		Which channel register to interrupt on.
* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.  
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::enable_ic_interrupt(uint8_t channel, void* ISR(void))
{
  /* Switch depending on which timer is saved in the implementation */
  switch (timer_id.number)
  {
    case TC_1:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK1 |= (1 << ICIE1);
	  /* Place the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER1_CAPT_int] = ISR;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    case TC_3:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK3 |= (1 << ICIE3);
	  /* Place the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER3_CAPT_int] = ISR;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    case TC_4:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK4 |= (1 << ICIE4);
	  /* Place the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER4_CAPT_int] = ISR;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    case TC_5:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK5 |= (1 << ICIE5);
	  /* Place the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER5_CAPT_int] = ISR;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    default:	/* invalid timer number! */
      return -1;
  }	  
  return 0;    
}

/**
* Disables the input compare interrupt on this timer
*
* @param channel		Which channel register to disable the interrupt on.
* @return 0 for success, -1 for error.
*/
int8_t timer_imp::disable_ic_interrupt(uint8_t channel)
{
  /* Switch depending on which timer is saved in the implementation */
  switch (timer_id.number)
  {
    case TC_1:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK1 &= ~(1 << ICIE1);
	  /* Replace the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER1_CAPT_int] = NULL;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    case TC_3:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK3 &= ~(3 << ICIE1);
	  /* Replace the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER3_CAPT_int] = NULL;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    case TC_4:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK4 &= ~(1 << ICIE4);
	  /* Replace the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER4_CAPT_int] = NULL;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    case TC_5:
    {
      /* Switch depending on which channel is supplied */
      switch (channel)
      {
	case TC_IC_A:
	{
	  /* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
	  TIMSK5 &= ~(1 << ICIE1);
	  /* Replace the user ISR pointer in the appropriate element within the ISR pointer array */
	  timer_interrupts[TIMER5_CAPT_int] = NULL;
	  
	  break;
	}
	/* TODO: more channels go here if needed */
      }
      break;
    }
    default:	/* invalid timer number! */
      return -1;
  }
  return 0;
}

/**
* Reads the current input capture register value for the specified channel.
*
* @param channel	Which channel to read the IC value from.
* @return The IC register value.
*/
template <typename T>
T timer_imp::get_ocR(tc_oc_channel channel)
{
  /* Switch which register to read depending on ther timer number saved in the implementation */
  switch (timer_id.number)
  {
    case TC_1:
    {
      /* Switch which channel to read */
      switch (channel)
      {
	case TC_IC_A:
	{
	  return (ICR1);
	}
      }
      /*TODO: more channels could be placed here as required */
      break;
    }
    case TC_3:
    {
      /* Switch which channel to read */
      switch (channel)
      {
	case TC_IC_A:
	{
	  return (ICR3);
	}
      }
      /*TODO: more channels could be placed here as required */
      break;
    }
    case TC_4:
    {
      /* Switch which channel to read */
      switch (channel)
      {
	case TC_IC_A:
	{
	  return (ICR4);
	}
      }
      /*TODO: more channels could be placed here as required */
      break;
    }
    case TC_5:
    {
      /* Switch which channel to read */
      switch (channel)
      {
	case TC_IC_A:
	{
	  return (ICR5);
	}
      }
      /*TODO: more channels could be placed here as required */
      break;
    }
    default:	/* Not a valid timer number provided */
      return -1;
  }     
 return 0;	/* Should never reach this point */
}

/** 
* Allows access to the timer to be relinquished and assumed elsewhere.
*
* @param  Nothing.
* @return Nothing.
*/
void timer_imp::vacate(void)
{

}

/**
* Starts Timer 0 by manipulating the TCCR0A & TCCR0B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer0(timer_rate rate)
{
  /*Edit the registers according to whether an internal/external clock is selected
   * and which prescaler is chosen*/
  switch(rate.src)
  {
    case INT:	//internal clock
    {
      switch(rate.pre)
      {
	case TC_PRE_1:	//Prescalar = 1
	{
	  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
	  break;
	}
	case TC_PRE_8:	//Prescalar = 8
	{
	  TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
	  break;
	}
	case TC_PRE_64:	//Prescalar = 64
	{
	  TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
	  break;
	}
	case TC_PRE_256:	//Prescalar = 256
	{
	  TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	  break;
	}
	case TC_PRE_1024:	//Prescalar = 1024
	{
	  TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
	  break;
	}
	default: /*Not a valid prescalar*/
	  return -1;
      }
      break;
    }
    /* TODO: If external clocks are ever an option add it here*/
  }
  return 0;	/*Valid clock and prescalar*/
}

/**
* Starts Timer 1 by manipulating the TCCR1A & TCCR1B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer1(timer_rate rate)
{
  /*Edit the registers according to whether an internal/external clock is selected
   * and which prescaler is chosen*/
  switch(rate.src)
  {
    case INT:	//internal clock
    {
      switch(rate.pre)
      {
	case TC_PRE_1:	//Prescalar = 1
	{
	  TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
	  break;
	}
	case TC_PRE_8:	//Prescalar = 8
	{
	  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
	  break;
	}
	case TC_PRE_64:	//Prescalar = 64
	{
	  TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
	  break;
	}
	case TC_PRE_256:	//Prescalar = 256
	{
	  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
	  break;
	}
	case TC_PRE_1024:	//Prescalar = 256
	{
	  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
	  break;
	}
      default: /*Not a valid prescalar*/
	  return -1;
      }
      break;
    }
    /* TODO: If external clocks are ever an option add it here*/
  }
  return 0;	/*Valid clock and prescalar*/
}

/**
* Starts Timer 2 by manipulating the TCCR2A & TCCR2B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer2(timer_rate rate)
{
  /*Edit the registers according to whether an internal/external clock is selected
   * and which prescaler is chosen*/
  switch(rate.src)
  {
    case INT:	//internal clock
    {
      switch(rate.pre)
      {
	case TC_PRE_1:	//Prescalar = 1
	{
	  TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
	  break;
	}
	case TC_PRE_8:	//Prescalar = 8
	{
	  TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);
	  break;
	}
	case TC_PRE_32:	//Prescalar = 32
	{
	  TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20);
	  break;
	}
	case TC_PRE_64:	//Prescalar = 64
	{
	  TCCR2B |= (1 << CS22) | (0 << CS21) | (0 << CS20);
	  break;
	}
	case TC_PRE_128:	//Prescalar = 128
	{
	  TCCR2B |= (1 << CS22) | (0 << CS21) | (1 << CS20);
	  break;
	}
	case TC_PRE_256:	//Prescalar = 256
	{
	  TCCR2B |= (1 << CS22) | (1 << CS21) | (0 << CS20);
	  break;
	}
	case TC_PRE_1024:	//Prescalar = 1024
	{
	  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
	  break;
	}
      default: /*Not a valid prescalar*/
	  return -1;
      }
      break;
    }
    /* TODO: If external clocks are ever an option add it here*/
  }
  return 0;	/*Valid clock and prescalar*/
}

/**
* Starts Timer 3 by manipulating the TCCR3A & TCCR3B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer3(timer_rate rate)
{
  /*Edit the registers according to whether an internal/external clock is selected
   * and which prescaler is chosen*/
  switch(rate.src)
  {
    case INT:	//internal clock
    {
      switch(rate.pre)
      {
	case TC_PRE_1:	//Prescalar = 1
	{
	  TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30);
	  break;
	}
	case TC_PRE_8:	//Prescalar = 8
	{
	  TCCR3B |= (0 << CS32) | (1 << CS31) | (0 << CS30);
	  break;
	}
	case TC_PRE_64:	//Prescalar = 64
	{
	  TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);
	  break;
	}
	case TC_PRE_256:	//Prescalar = 256
	{
	  TCCR3B |= (1 << CS32) | (0 << CS31) | (0 << CS30);
	  break;
	}
	case TC_PRE_1024:	//Prescalar = 256
	{
	  TCCR3B |= (1 << CS32) | (0 << CS31) | (1 << CS30);
	  break;
	}
      default: /*Not a valid prescalar*/
	  return -1;
      }
      break;
    }
    /* TODO: If external clocks are ever an option add it here*/
  }
  return 0;	/*Valid clock and prescalar*/
}

/**
* Starts Timer 4 by manipulating the TCCR4A & TCCR4B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer4(timer_rate rate)
{
  /*Edit the registers according to whether an internal/external clock is selected
   * and which prescaler is chosen*/
  switch(rate.src)
  {
    case INT:	//internal clock
    {
      switch(rate.pre)
      {
	case TC_PRE_1:	//Prescalar = 1
	{
	  TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
	  break;
	}
	case TC_PRE_8:	//Prescalar = 8
	{
	  TCCR4B |= (0 << CS42) | (1 << CS41) | (0 << CS40);
	  break;
	}
	case TC_PRE_64:	//Prescalar = 64
	{
	  TCCR4B |= (0 << CS42) | (1 << CS41) | (1 << CS40);
	  break;
	}
	case TC_PRE_256:	//Prescalar = 256
	{
	  TCCR4B |= (1 << CS42) | (0 << CS41) | (0 << CS40);
	  break;
	}
	case TC_PRE_1024:	//Prescalar = 256
	{
	  TCCR4B |= (1 << CS42) | (0 << CS41) | (1 << CS40);
	  break;
	}
      default: /*Not a valid prescalar*/
	  return -1;
      }
      break;
    }
    /* TODO: If external clocks are ever an option add it here*/
  }
  return 0;	/*Valid clock and prescalar*/
}

/**
* Starts Timer 5 by manipulating the TCCR3A & TCCR3B registers
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 if valid prescalar and clock are supplied, otherwise -1
*/
int8_t start_timer5(timer_rate rate)
{
  /*Edit the registers according to whether an internal/external clock is selected
   * and which prescaler is chosen*/
  switch(rate.src)
  {
    case INT:	//internal clock
    {
      switch(rate.pre)
      {
	case TC_PRE_1:	//Prescalar = 1
	{
	  TCCR5B |= (0 << CS52) | (0 << CS51) | (1 << CS50);
	  break;
	}
	case TC_PRE_8:	//Prescalar = 8
	{
	  TCCR5B |= (0 << CS52) | (1 << CS51) | (0 << CS50);
	  break;
	}
	case TC_PRE_64:	//Prescalar = 64
	{
	  TCCR5B |= (0 << CS52) | (1 << CS51) | (1 << CS50);
	  break;
	}
	case TC_PRE_256:	//Prescalar = 256
	{
	  TCCR5B |= (1 << CS52) | (0 << CS51) | (0 << CS50);
	  break;
	}
	case TC_PRE_1024:	//Prescalar = 256
	{
	  TCCR5B |= (1 << CS52) | (0 << CS51) | (1 << CS50);
	  break;
	}
      default: /*Not a valid prescalar*/
	  return -1;
      }
      break;
    }
    /* TODO: If external clocks are ever an option add it here*/
  }
  return 0;	/*Valid clock and prescalar*/
}

/**
* Enables Output Compare operation on Timer Counter 0.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer0(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare depending on which tc_oc_channel is selected */
  switch(channel)
  {
    case TC_OC_A:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK0 &= ~(1 << OCIE0A);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR0A &= (~(1 << COM0A1) & ~(1 << COM0A0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn2:0 bits to 0x02 for CTC mode */
	    TCCR0A &= ~(1 << WGM00);
	    TCCR0A |= (1 << WGM01);
	    TCCR0B &= ~(1 << WGM02);
	    
	    /* Configure COMnX1:0 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR0A |= (1 << COM0A0);
	    TCCR0A &= ~(1 << COM0A1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK0 |= (1 << OCIE0A);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR0A |= ((1 << WGM01) | (1 << WGM00));
	    TCCR0B |= (1 << WGM02);
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR0A |= (1 << COM0A1);
	    TCCR0A &= ~(1 << COM0A0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR0A |= ((1 << WGM01) | (1 << WGM00));
	    TCCR0B |= (1 << WGM02);
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR0A |= ((1 << COM0A1) | (1 << COM0A0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_B:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK0 &= ~(1 << OCIE0B);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR0A &= (~(1 << COM0B1) & ~(1 << COM0B0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn2:0 bits to 0x02 for CTC mode */
	    TCCR0A &= ~(1 << WGM00);
	    TCCR0A |= (1 << WGM01);
	    TCCR0B &= ~(1 << WGM02);
	    
	    /* Configure COMnX1:0 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR0A |= (1 << COM0B0);
	    TCCR0A &= ~(1 << COM0B1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK0 |= (1 << OCIE0B);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR0A |= ((1 << WGM01) | (1 << WGM00));
	    TCCR0B |= (1 << WGM02);
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR0A |= (1 << COM0B1);
	    TCCR0A &= ~(1 << COM0B0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR0A |= ((1 << WGM01) | (1 << WGM00));
	    TCCR0B |= (1 << WGM02);
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR0A |= ((1 << COM0B1) | (1 << COM0B0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    default:	/* No more channels available, return an error. */
      return -1;
    }
    
    return 0;
}

/**
* Enables Output Compare operation on Timer Counter 1.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer1(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare depending on which tc_oc_channel is selected */
  switch(channel)
  {
    case TC_OC_A:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK1 &= ~(1 << OCIE1A);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR1A &= (~(1 << COM1A1) & ~(1 << COM1A0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR1A &= (~(1 << WGM11) & ~(1 << WGM10));
	    TCCR1B &= ~(1 << WGM13);
	    TCCR1B |= (1 << WGM12);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR1A |= (1 << COM1A0);
	    TCCR1A &= ~(1 << COM1A1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK1 |= (1 << OCIE1A);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR1A |= ((1 << WGM11) | (1 << WGM10));
	    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR1A |= (1 << COM1A1);
	    TCCR1A &= ~(1 << COM1A0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR1A |= ((1 << WGM11) | (1 << WGM10));
	    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR1A |= ((1 << COM1A1) | (1 << COM1A0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_B:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK1 &= ~(1 << OCIE1B);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR1A &= (~(1 << COM1B1) & ~(1 << COM1B0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR1A &= (~(1 << WGM11) & ~(1 << WGM10));
	    TCCR1B &= ~(1 << WGM13);
	    TCCR1B |= (1 << WGM12);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR1A |= (1 << COM1B0);
	    TCCR1A &= ~(1 << COM1B1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK1 |= (1 << OCIE1B);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR1A |= ((1 << WGM11) | (1 << WGM10));
	    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR1A |= (1 << COM1B1);
	    TCCR1A &= ~(1 << COM1B0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR1A |= ((1 << WGM11) | (1 << WGM10));
	    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR1A |= ((1 << COM1B1) | (1 << COM1B0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_C:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK1 &= ~(1 << OCIE1C);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR1A &= (~(1 << COM1C1) & ~(1 << COM1C0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR1A &= (~(1 << WGM11) & ~(1 << WGM10));
	    TCCR1B &= ~(1 << WGM13);
	    TCCR1B |= (1 << WGM12);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR1A |= (1 << COM1C0);
	    TCCR1A &= ~(1 << COM1C1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK1 |= (1 << OCIE1C);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR1A |= ((1 << WGM11) | (1 << WGM10));
	    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR1A |= (1 << COM1C1);
	    TCCR1A &= ~(1 << COM1C0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR1A |= ((1 << WGM11) | (1 << WGM10));
	    TCCR1B |= ((1 << WGM13) | (1 << WGM12));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR1A |= ((1 << COM1C1) | (1 << COM1C0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    default:	/* No more channels available, return an error. */
      return -1;
    }
    
    return 0;
}

/**
* Enables Output Compare operation on Timer Counter 2.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer2(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare depending on which tc_oc_channel is selected */
  switch(channel)
  {
    case TC_OC_A:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK2 &= ~(1 << OCIE2A);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR2A &= (~(1 << COM2A1) & ~(1 << COM2A0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn2:0 bits to 0x02 for CTC mode */
	    TCCR2A &= ~(1 << WGM20);
	    TCCR2A |= (1 << WGM21);
	    TCCR2B &= ~(1 << WGM22);
	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR2A |= (1 << COM2A0);
	    TCCR2A &= ~(1 << COM2A1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK2 |= (1 << OCIE2A);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR2A |= ((1 << WGM21) | (1 << WGM20));
	    TCCR2B |= (1 << WGM22);
	    
	    /* Configure COMnX1:0 bits to 0x12 for non-inverted PWM */
	    TCCR2A |= (1 << COM2A1);
	    TCCR2A &= ~(1 << COM2A0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR2A |= ((1 << WGM21) | (1 << WGM20));
	    TCCR2B |= (1 << WGM22);
	    
	    /* Configure COMnX1:0 bits to 0x03 for non-inverted PWM */
	    TCCR2A |= ((1 << COM2A1) | (1 << COM2A0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_B:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK2 &= ~(1 << OCIE2B);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR2A &= (~(1 << COM2B1) & ~(1 << COM2B0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn2:0 bits to 0x02 for CTC mode */
	    TCCR2A &= ~(1 << WGM20);
	    TCCR2A |= (1 << WGM21);
	    TCCR2B &= ~(1 << WGM22);
	    
	    /* Configure COMnX1:0 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR2A |= (1 << COM2B0);
	    TCCR2A &= ~(1 << COM2B1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK2 |= (1 << OCIE2B);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR2A |= ((1 << WGM21) | (1 << WGM20));
	    TCCR2B |= (1 << WGM22);
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR2A |= (1 << COM2B1);
	    TCCR2A &= ~(1 << COM2B0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0x07 for Fast PWM mode where TOP = OCRnX */
	    TCCR2A |= ((1 << WGM21) | (1 << WGM20));
	    TCCR2B |= (1 << WGM22);
	    
	    /* Configure COMnX1:0 bits to 0x03 for non-inverted PWM */
	    TCCR2A |= ((1 << COM2B1) | (1 << COM2B0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    default:	/* No more channels available, return an error. */
      return -1;
    }
    
    return 0;
}

/**
* Enables Output Compare operation on Timer Counter 3.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer3(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare depending on which tc_oc_channel is selected */
  switch(channel)
  {
    case TC_OC_A:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK3 &= ~(1 << OCIE3A);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR3A &= (~(1 << COM3A1) & ~(1 << COM3A0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR3A &= (~(1 << WGM31) & ~(1 << WGM30));
	    TCCR3B &= ~(1 << WGM33);
	    TCCR3B |= (1 << WGM32);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR3A |= (1 << COM3A0);
	    TCCR3A &= ~(1 << COM3A1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK3 |= (1 << OCIE3A);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR3A |= ((1 << WGM31) | (1 << WGM30));
	    TCCR3B |= ((1 << WGM33) | (1 << WGM32));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR3A |= (1 << COM3A1);
	    TCCR3A &= ~(1 << COM3A0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR3A |= ((1 << WGM31) | (1 << WGM30));
	    TCCR3B |= ((1 << WGM33) | (1 << WGM32));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR3A |= ((1 << COM3A1) | (1 << COM3A0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_B:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK3 &= ~(1 << OCIE3B);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR3A &= (~(1 << COM3B1) & ~(1 << COM3B0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR3A &= (~(1 << WGM31) & ~(1 << WGM30));
	    TCCR3B &= ~(1 << WGM33);
	    TCCR3B |= (1 << WGM32);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR3A |= (1 << COM3B0);
	    TCCR3A &= ~(1 << COM3B1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK3 |= (1 << OCIE3B);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR3A |= ((1 << WGM31) | (1 << WGM30));
	    TCCR3B |= ((1 << WGM33) | (1 << WGM32));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR3A |= (1 << COM3B1);
	    TCCR3A &= ~(1 << COM3B0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR3A |= ((1 << WGM31) | (1 << WGM30));
	    TCCR3B |= ((1 << WGM33) | (1 << WGM32));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR3A |= ((1 << COM3B1) | (1 << COM3B0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_C:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK3 &= ~(1 << OCIE3C);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR3A &= (~(1 << COM3C1) & ~(1 << COM3C0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR3A &= (~(1 << WGM31) & ~(1 << WGM30));
	    TCCR3B &= ~(1 << WGM33);
	    TCCR3B |= (1 << WGM32);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR3A |= (1 << COM3C0);
	    TCCR3A &= ~(1 << COM3C1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK3 |= (1 << OCIE3C);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR3A |= ((1 << WGM31) | (1 << WGM30));
	    TCCR3B |= ((1 << WGM33) | (1 << WGM32));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR3A |= (1 << COM3C1);
	    TCCR3A &= ~(1 << COM3C0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR3A |= ((1 << WGM31) | (1 << WGM30));
	    TCCR3B |= ((1 << WGM33) | (1 << WGM32));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR3A |= ((1 << COM3C1) | (1 << COM3C0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    default:	/* No more channels available, return an error. */
      return -1;
    }
    
    return 0;
}

/**
* Enables Output Compare operation on Timer Counter 4.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer4(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare depending on which tc_oc_channel is selected */
  switch(channel)
  {
    case TC_OC_A:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK4 &= ~(1 << OCIE4A);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR4A &= (~(1 << COM4A1) & ~(1 << COM4A0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR4A &= (~(1 << WGM41) & ~(1 << WGM40));
	    TCCR4B &= ~(1 << WGM43);
	    TCCR4B |= (1 << WGM42);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR4A |= (1 << COM4A0);
	    TCCR4A &= ~(1 << COM4A1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK4 |= (1 << OCIE4A);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR4A |= ((1 << WGM41) | (1 << WGM40));
	    TCCR4B |= ((1 << WGM43) | (1 << WGM42));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR4A |= (1 << COM4A1);
	    TCCR4A &= ~(1 << COM4A0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR4A |= ((1 << WGM41) | (1 << WGM40));
	    TCCR4B |= ((1 << WGM43) | (1 << WGM42));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR4A |= ((1 << COM4A1) | (1 << COM4A0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_B:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK4 &= ~(1 << OCIE4B);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR4A &= (~(1 << COM4B1) & ~(1 << COM4B0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR4A &= (~(1 << WGM41) & ~(1 << WGM40));
	    TCCR4B &= ~(1 << WGM43);
	    TCCR4B |= (1 << WGM42);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR4A |= (1 << COM4B0);
	    TCCR4A &= ~(1 << COM4B1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK4 |= (1 << OCIE4B);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR4A |= ((1 << WGM41) | (1 << WGM40));
	    TCCR4B |= ((1 << WGM43) | (1 << WGM42));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR4A |= (1 << COM4B1);
	    TCCR4A &= ~(1 << COM4B0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR4A |= ((1 << WGM41) | (1 << WGM40));
	    TCCR4B |= ((1 << WGM43) | (1 << WGM42));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR4A |= ((1 << COM4B1) | (1 << COM4B0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_C:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK4 &= ~(1 << OCIE4C);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR4A &= (~(1 << COM4C1) & ~(1 << COM4C0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR4A &= (~(1 << WGM41) & ~(1 << WGM40));
	    TCCR4B &= ~(1 << WGM43);
	    TCCR4B |= (1 << WGM42);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR4A |= (1 << COM4C0);
	    TCCR4A &= ~(1 << COM4C1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK4 |= (1 << OCIE4C);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR4A |= ((1 << WGM41) | (1 << WGM40));
	    TCCR4B |= ((1 << WGM43) | (1 << WGM42));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR4A |= (1 << COM4C1);
	    TCCR4A &= ~(1 << COM4C0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR4A |= ((1 << WGM41) | (1 << WGM40));
	    TCCR4B |= ((1 << WGM43) | (1 << WGM42));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR4A |= ((1 << COM4C1) | (1 << COM4C0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    default:	/* No more channels available, return an error. */
      return -1;
    }
    
    return 0;
}

/**
* Enables Output Compare operation on Timer Counter 5.
* 
* @param channel		Which OC channel should be enabled.
* @param mode			Which mode the OC channel should be set to.
* @return 0 if successful, -1 otherwise.
*/
int8_t enable_oc_timer5(tc_oc_channel channel, tc_oc_mode mode)
{
  /* Switch the process of enabling output compare depending on which tc_oc_channel is selected */
  switch(channel)
  {
    case TC_OC_A:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK5 &= ~(1 << OCIE5A);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR5A &= (~(1 << COM5A1) & ~(1 << COM5A0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR5A &= (~(1 << WGM51) & ~(1 << WGM50));
	    TCCR5B &= ~(1 << WGM53);
	    TCCR5B |= (1 << WGM52);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR5A |= (1 << COM5A0);
	    TCCR5A &= ~(1 << COM5A1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK5 |= (1 << OCIE5A);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR5A |= ((1 << WGM51) | (1 << WGM50));
	    TCCR5B |= ((1 << WGM53) | (1 << WGM52));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR5A |= (1 << COM5A1);
	    TCCR5A &= ~(1 << COM5A0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR5A |= ((1 << WGM51) | (1 << WGM50));
	    TCCR5B |= ((1 << WGM53) | (1 << WGM52));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR5A |= ((1 << COM5A1) | (1 << COM5A0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_B:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK5 &= ~(1 << OCIE5B);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR5A &= (~(1 << COM5B1) & ~(1 << COM5B0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR5A &= (~(1 << WGM51) & ~(1 << WGM50));
	    TCCR5B &= ~(1 << WGM53);
	    TCCR5B |= (1 << WGM52);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR5A |= (1 << COM5B0);
	    TCCR5A &= ~(1 << COM5B1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK5 |= (1 << OCIE5B);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR5A |= ((1 << WGM51) | (1 << WGM50));
	    TCCR5B |= ((1 << WGM53) | (1 << WGM52));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR5A |= (1 << COM5B1);
	    TCCR5A &= ~(1 << COM5B0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR5A |= ((1 << WGM51) | (1 << WGM50));
	    TCCR5B |= ((1 << WGM53) | (1 << WGM52));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR5A |= ((1 << COM5B1) | (1 << COM5B0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    case TC_OC_C:
    {
      /* Switch the process of enabling output compare mode depending on which mode is chosen and
	* provided to function.
	*/
	switch(mode)
	{
	  case OC_NONE:
	  {
	    /* Disable the output compare operation */
	    TIMSK5 &= ~(1 << OCIE5C);
	    /* Disconnect the output pin to allow for normal operation */
	    TCCR5A &= (~(1 << COM5C1) & ~(1 << COM5C0));
	    break;
	  }
	  case OC_MODE_1:	/* Clear timer on Compare (CTC) mode. Toggles OCnX pin on compare-match interrupt if pin is set to output*/
	  {
	    /* Set WGMn3:0 bits to 0x04 for CTC mode */
	    TCCR5A &= (~(1 << WGM51) & ~(1 << WGM50));
	    TCCR5B &= ~(1 << WGM53);
	    TCCR5B |= (1 << WGM52);
	    	    
	    /* Configure COMnX1:1 bits to 0x01 for toggling OCnX pin on compare match. */
	    TCCR5A |= (1 << COM5C0);
	    TCCR5A &= ~(1 << COM5C1);
	    
	    /* Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
	    TIMSK5 |= (1 << OCIE5C);
	    
	    break;
	  }
	  case OC_MODE_2:	/* Fast PWM, non-inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR5A |= ((1 << WGM51) | (1 << WGM50));
	    TCCR5B |= ((1 << WGM53) | (1 << WGM52));
	    
	    /* Configure COMnX1:0 bits to 0x02 for non-inverted PWM */
	    TCCR5A |= (1 << COM5C1);
	    TCCR5A &= ~(1 << COM5C0);
	    
	    break;
	  }
	  case OC_MODE_3;	/* Fast PWM, inverted */
	  {
	    /* Set WGMn2:0 bits to 0xF0 for Fast PWM mode where TOP = OCRnX */
	    TCCR5A |= ((1 << WGM51) | (1 << WGM50));
	    TCCR5B |= ((1 << WGM53) | (1 << WGM52));
	    
	    /* Configure COMnX1:0 bits to 0x03 for inverted PWM */
	    TCCR5A |= ((1 << COM5C1) | (1 << COM5C0));
		    
	    break;
	  }
	  /* TODO: More modes in here if necessary */
	}
    }
    default:	/* No more channels available, return an error. */
      return -1;
    }
    
    return 0;
}

/**
* Enables input capture mode for Timer Counter 1.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
* @return 0 for success, -1 for error.
*/
int8_t enable_ic_timer1(tc_ic_channel channel, tc_ic_mode mode)
{
  /* Manipulate the necessary registers depending on which channel is supplied to function */
  switch(channel)
  {
    case TC_IC_A:
    {
      /* Switch depending on which mode is supplied */
      switch(mode)
      {
	case IC_NONE:
	{
	  /* TODO: Any disabling code for IC goes here */
	  break;
	}
	case IC_MODE_1:	/* Rising edge and input noise cancellation enabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & the ICNCn bit in the same register for noise cancellation */
	  TCCR1B |= ((1 << ICES1) | (1 << ICNC1));
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR1B |= (1 << ICES1) 
	  TCCR1B &= ~(1 << ICNC1);
	  break;
	}
	case IC_MODE_3:	/* Falling edge and input noise cancellation enabled */
	{
	  /* Clear the ICESn bit in TCCRnB for falling edge detection & set the ICNCn bit in the same register for noise cancellation */
	  TCCR1B |= (1 << ICNC1);
	  TCCR1B &= ~(1 << ICES1);
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Clear the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR1B &= (~(1 << ICNC1) & ~(1 << ICES1));
	  break;
	}
	default:	/* Invalid mode for timer */
	  return -1;
      }
      /*TODO: any more IC channels go here*/
    }
  }
  return 0;  
}

/**
* Enables input capture mode for Timer Counter 3.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
* @return 0 for success, -1 for error.
*/
int8_t enable_ic_timer3(tc_ic_channel channel, tc_ic_mode mode)
{
  /* Manipulate the necessary registers depending on which channel is supplied to function */
  switch(channel)
  {
    case TC_IC_A:
    {
      /* Switch depending on which mode is supplied */
      switch(mode)
      {
	case IC_NONE:
	{
	  /* TODO: Any disabling code for IC goes here */
	  break;
	}
	case IC_MODE_1:	/* Rising edge and input noise cancellation enabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & the ICNCn bit in the same register for noise cancellation */
	  TCCR3B |= ((1 << ICES3) | (1 << ICNC3));
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR3B |= (1 << ICES3) 
	  TCCR3B &= ~(1 << ICNC3);
	  break;
	}
	case IC_MODE_3:	/* Falling edge and input noise cancellation enabled */
	{
	  /* Clear the ICESn bit in TCCRnB for falling edge detection & set the ICNCn bit in the same register for noise cancellation */
	  TCCR3B |= (1 << ICNC3);
	  TCCR3B &= ~(1 << ICES3);
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Clear the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR3B &= (~(1 << ICNC3) & ~(1 << ICES3));
	  break;
	}
	default:	/* Invalid mode for timer */
	  return -1;
      }
      /*TODO: any more IC channels go here*/
    }
  }
  return 0;  
}

/**
* Enables input capture mode for Timer Counter 4.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
* @return 0 for success, -1 for error.
*/
int8_t enable_ic_timer4(tc_ic_channel channel, tc_ic_mode mode)
{
  /* Manipulate the necessary registers depending on which channel is supplied to function */
  switch(channel)
  {
    case TC_IC_A:
    {
      /* Switch depending on which mode is supplied */
      switch(mode)
      {
	case IC_NONE:
	{
	  /* TODO: Any disabling code for IC goes here */
	  break;
	}
	case IC_MODE_1:	/* Rising edge and input noise cancellation enabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & the ICNCn bit in the same register for noise cancellation */
	  TCCR4B |= ((1 << ICES4) | (1 << ICNC4));
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR4B |= (1 << ICES4) 
	  TCCR4B &= ~(1 << ICNC4);
	  break;
	}
	case IC_MODE_3:	/* Falling edge and input noise cancellation enabled */
	{
	  /* Clear the ICESn bit in TCCRnB for falling edge detection & set the ICNCn bit in the same register for noise cancellation */
	  TCCR4B |= (1 << ICNC4);
	  TCCR4B &= ~(1 << ICES4);
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Clear the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR4B &= (~(1 << ICNC4) & ~(1 << ICES4));
	  break;
	}
	default:	/* Invalid mode for timer */
	  return -1;
      }
      /*TODO: any more IC channels go here*/
    }
  }
  return 0;  
}

/**
* Enables input capture mode for Timer Counter 5.  If mode to set to 'IC_NONE', then disable IC mode
* operation for the specified channel.
*
* @param channel		Which IC channel should be enabled.
* @param mode			Which mode the IC channel should be set to.
* @return 0 for success, -1 for error.
*/
int8_t enable_ic_timer5(tc_ic_channel channel, tc_ic_mode mode)
{
  /* Manipulate the necessary registers depending on which channel is supplied to function */
  switch(channel)
  {
    case TC_IC_A:
    {
      /* Switch depending on which mode is supplied */
      switch(mode)
      {
	case IC_NONE:
	{
	  /* TODO: Any disabling code for IC goes here */
	  break;
	}
	case IC_MODE_1:	/* Rising edge and input noise cancellation enabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & the ICNCn bit in the same register for noise cancellation */
	  TCCR5B |= ((1 << ICES5) | (1 << ICNC5));
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Set the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR5B |= (1 << ICES5) 
	  TCCR5B &= ~(1 << ICNC5);
	  break;
	}
	case IC_MODE_3:	/* Falling edge and input noise cancellation enabled */
	{
	  /* Clear the ICESn bit in TCCRnB for falling edge detection & set the ICNCn bit in the same register for noise cancellation */
	  TCCR5B |= (1 << ICNC5);
	  TCCR5B &= ~(1 << ICES5);
	  break;
	}
	case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
	{
	  /* Clear the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
	  TCCR5B &= (~(1 << ICNC5) & ~(1 << ICES5));
	  break;
	}
	default:	/* Invalid mode for timer */
	  return -1;
      }
      /*TODO: any more IC channels go here*/
    }
  }
  return 0;  
}

/* Declare the ISRs
 * 
 * Each timer interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs by way of the function pointer array timer_interrupts[]. Here the
 * ISRs are declared and the user ISR is called if the appropriate element of the function
 * pointer array is non NULL.
 */

ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER0_COMPA_int])
    timer_interrupts[TIMER0_COMPA_int]();
}

ISR(TIMER0_COMPB_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER0_COMPB_int])
    timer_interrupts[TIMER0_COMPB_int]();
}

ISR(TIMER0_OVF_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER0_OVF_int])
    timer_interrupts[TIMER0_OVF_int]();
}

ISR(TIMER1_CAPT_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER1_CAPT_int])
    timer_interrupts[TIMER1_CAPT_int]();
}

ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER1_COMPA_int])
    timer_interrupts[TIMER1_COMPA_int]();
}

ISR(TIMER1_COMPB_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER1_COMPB_int])
    timer_interrupts[TIMER1_COMPB_int]();
}

ISR(TIMER1_OVF_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER1_OVF_int])
    timer_interrupts[TIMER1_OVF_int]();
}

ISR(TIMER2_COMPA_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER2_COMPA_int])
    timer_interrupts[TIMER2_COMPA_int]();
}

ISR(TIMER2_COMPB_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER2_COMPB_int])
    timer_interrupts[TIMER2_COMPB_int]();
}

ISR(TIMER2_OVF_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER2_OVF_int])
    timer_interrupts[TIMER2_OVF_int]();
}

ISR(TIMER3_CAPT_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER3_CAPT_int])
    timer_interrupts[TIMER3_CAPT_int]();
}

ISR(TIMER3_COMPA_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER3_COMPA_int])
    timer_interrupts[TIMER3_COMPA_int]();
}

ISR(TIMER3_COMPB_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER3_COMPB_int])
    timer_interrupts[TIMER3_COMPB_int]();
}

ISR(TIMER3_COMPC_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER3_COMPC_int])
    timer_interrupts[TIMER3_COMPC_int]();
}

ISR(TIMER3_OVF_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER3_OVF_int])
    timer_interrupts[TIMER3_OVF_int]();
}

ISR(TIMER4_CAPT_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER4_CAPT_int])
    timer_interrupts[TIMER4_CAPT_int]();
}

ISR(TIMER4_COMPA_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER4_COMPA_int])
    timer_interrupts[TIMER4_COMPA_int]();
}

ISR(TIMER4_COMPB_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER4_COMPB_int])
    timer_interrupts[TIMER4_COMPB_int]();
}

ISR(TIMER4_COMPC_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER4_COMPC_int])
    timer_interrupts[TIMER4_COMPC_int]();
}

ISR(TIMER4_OVF_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER4_OVF_int])
    timer_interrupts[TIMER4_OVF_int]();
}

ISR(TIMER5_CAPT_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER5_CAPT_int])
    timer_interrupts[TIMER5_CAPT_int]();
}

ISR(TIMER5_COMPA_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER5_COMPA_int])
    timer_interrupts[TIMER5_COMPA_int]();
}

ISR(TIMER5_COMPB_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER5_COMPB_int])
    timer_interrupts[TIMER5_COMPB_int]();
}

ISR(TIMER5_COMPC_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER5_COMPC_int])
    timer_interrupts[TIMER5_COMPC_int]();
}

ISR(TIMER5_OVF_vect, ISR_BLOCK)
{
  if (timer_interrupts[TIMER5_OVF_int])
    timer_interrupts[TIMER5_OVF_int]();
}

// ALL DONE.
