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

// DEFINE PRIVATE MACROS.

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
	* @param  timer_rate	Settings for clock source and prescaler.
	* @return 0 for success, -1 for error.
	*/
	int8_t set_rate(timer_rate rate)
	{
// 	  /*Switch which registers are edited based on the timer number*/
// 	  switch(timer_id.number)
// 	  {
// 	    case TC_0:
// 	    {
// 	      /*edit the TCCR0A and TCCR0B registers*/
// 	      set_timer0(rate);
// 	      break;
// 	    }
// 	    case TC_1:
// 	    {
// 	      /*edit the TCCR1A and TCCR1B registers*/
// 	      set_timer1(rate);
// 	      break;
// 	    }
// 	    case TC_2:
// 	    {
// 	      /*edit the TCCR2A and TCCR2B registers*/
// 	      set_timer2(rate);
// 	      break;
// 	    }
// 	    case TC_3:
// 	    {
// 	      /*edit the TCCR3A and TCCR3B registers*/
// 	      set_timer3(rate);
// 	      break;
// 	    }
// 	    case TC_4:
// 	    {
// 	      /*edit the TCCR4A and TCCR4B registers*/
// 	      set_timer4(rate);
// 	      break;
// 	    }
// 	    case TC_5:
// 	    {
// 	      /*edit the TCCR5A and TCCR5B registers*/
// 	      set_timer5(rate);
// 	      break;
// 	    }
// 	  }
	  return 0;	//How to return -1 in case of an error?
	}

	/**
	* Loads the timer with a value.
	*
	* @param value		The value the timer register will have.
 	* @param number		number of the timer counter
	* @return 0 for success, -1 for error.
	*/
	template <typename T>
	int8_t load_timer_value(T value, tc_number number)
	{
	  /*Switch which TCNTn registers are edited based on the timer number*/
	  switch(number)
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
	* @param number	Number of the timer counter
	* @return T 	The timer value
	*/
	template <typename T>
	T get_timer_value(tc_number number)
	{
	  /*Switch which TCNTn registers are read based on the timer number*/
	  switch(number)
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
	* @param rate	clock source and prescalar value to apply to timer
	* @param number	Number of timer counter to start
	* @return 0 for success, -1 for error.
	*/
	int8_t start(timer_rate rate, tc_number number)
	{
	 /*Switch which registers are edited based on the timer number*/
	  switch(number)
	  {
	    case TC_0:
	    {
	      /*edit the TCCR0A and TCCR0B registers*/
	      start_timer0(rate);
	      break;
	    }
	    case TC_1:
	    {
	      /*edit the TCCR1A and TCCR1B registers*/
	      start_timer1(rate);
	      break;
	    }
	    case TC_2:
	    {
	      /*edit the TCCR2A and TCCR2B registers*/
	      start_timer2(rate);
	      break;
	    }
	    case TC_3:
	    {
	      /*edit the TCCR3A and TCCR3B registers*/
	      start_timer3(rate);
	      break;
	    }
	    case TC_4:
	    {
	      /*edit the TCCR4A and TCCR4B registers*/
	      start_timer4(rate);
	      break;
	    }
	    case TC_5:
	    {
	      /*edit the TCCR5A and TCCR5B registers*/
	      start_timer5(rate);
	      break;
	    }
	  }
	  return 0;	//How to return -1 in case of an error?
	}

	/**
	* Stops the timer.
	*
	* @param number	Number of the timer counter
	* @return 0 for success, -1 for error.
	*/
	int8_t stop(tc_number number)
	{
	  /*Switch which TCNTn registers are edited based on the timer number*/
	  switch(number)
	  {
	    case TC_0:
	    {
	      /*edit the TCCR0B register*/
	      TCCR0B &= (0 << CS02) | (0 << CS01) | (0 << CS00)
	      break;
	    }
	    case TC_1:
	    {
	      /*edit the TCCR1B register*/
	      TCCR1B &= (0 << CS02) | (0 << CS01) | (0 << CS00)
	      break;
	    }
	    case TC_2:
	    {
	      /*edit the TCCR2B register*/
	      TCCR2B &= (0 << CS02) | (0 << CS01) | (0 << CS00)
	      break;
	    }
	    case TC_3:
	    {
	      /*edit the TCCR3B register*/
	      TCCR3B &= (0 << CS02) | (0 << CS01) | (0 << CS00)
	      break;
	    }
	    case TC_4:
	    {
	      /*edit the TCCR4B register*/
	      TCCR4B &= (0 << CS02) | (0 << CS01) | (0 << CS00)
	      break;
	    }
	    case TC_5:
	    {
	      /*edit the TCCR5B register*/
	      TCCR5B &= (0 << CS02) | (0 << CS01) | (0 << CS00)
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
	int8_t enable_tov_interrupt(void* ISR(void))
	{

	}

	/**
	* Disables the overflow interrupt on this timer
	*
	* @param  Nothing.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_tov_interrupt(void)
	{

	}

	/**
	* Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disable OC mode
	* operation for the specified channel.
	*
	* @param channel		Which OC channel should be enabled.
	* @param mode			Which mode the OC channel should be set to.
	*/
	int8_t enable_oc(tc_oc_channel channel, tc_oc_mode mode)
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
	int8_t enable_oc_interrupt(tc_oc_channel channel, void* ISR(void))
	{

	}

	/**
	* Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
	* OC mode operation itself.
	*
	* @param channel		Which channel register to disable the interrupt on.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_oc_interrupt(tc_oc_channel channel)
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
	uint8_t set_ocR(tc_oc_channel channel, T value)
	{

	}

	/**
	* Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
	* operation for the specified channel.
	*
	* @param channel		Which IC channel should be enabled.
	* @param mode			Which mode the IC channel should be set to.
	*/
	int8_t enable_ic(tc_ic_channel channel, tc_ic_mode mode)
	{

	}

	/**
	* Enables the input compare interrupt on this timer
	*
	* @param  channel		Which channel register to interrupt on.
	* @param  ISR			A pointer to the ISR that is called when this interrupt is generated.  
	* @return 0 for success, -1 for error.
	*/
	int8_t enable_ic_interrupt(uint8_t channel, void* ISR(void))
	{

	}

	/**
	* Disables the input compare interrupt on this timer
	*
	* @param channel		Which channel register to disable the interrupt on.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_ic_interrupt(uint8_t channel)
	{

	}

	/**
	* Reads the current input capture register value for the specified channel.
	*
	* @param channel	Which channel to read the IC value from.
	* @return The IC register value.
	*/
	template <typename T>
	T get_ocR(tc_oc_channel channel)
	{

	}

	/**
	* Gets run whenever the instance of class timer goes out of scope.
	* Vacates the semaphore, allowing the timer to be allocated elsewhere.
	*
	* @param  Nothing.
	* @return Nothing.
	*/
	~timer_imp(void)
	{

	}

	/** 
	* Allows access to the timer to be relinquished and assumed elsewhere.
	*
	* @param  Nothing.
	* @return Nothing.
	*/
	void vacate(void)
	{

	}
	
	//Private functions
	
	//Fields
	
}

// DECLARE PRIVATE GLOBAL VARIABLES.

/*Create an array of timer implementation*/
timer_imp timer_imps[NUM_TIMERS];	/*TODO Possibly make into a two-dimensional array of some sort to provide semaphores on each channel of each timer*/

// IMPLEMENT PUBLIC FUNCTIONS.

/**
* Sets the timer rate by selecting the clk src and prescaler.
* 
* @param  timer_rate	Settings for clock source and prescaler.
* @return 0 for success, -1 for error.
*/
int8_t timer::set_rate(timer_rate rate)
{
  if (imp->set_rate(rate))
  {
    /*Preserve the prescalar and clock source now*/
    preserved_rate = rate;
    return 0;
  }
  else
  {
    return -1;
  }
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
  return(imp->get_timer_value(timer_id.number));
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

// ALL DONE.
