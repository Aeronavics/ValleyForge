/********************************************************************************************************************************
 *
 *  FILE: 		gpio.c
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Edwin Hayes, Zac Frank
 *
 *  DATE CREATED:	7-12-2011
 *
 *	This is the implementation for gpio for the atmega2560.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

volatile static voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];

// DECLARE IMPORTED GLOBAL VARIABLES.
extern semaphore semaphores[NUM_PORTS][NUM_PINS];
extern semaphore pc_int_sem[NUM_BANKS];

/**
 * A Class that implements the functions for gpio
 * One instance for each pin.
 * Reads, writes, and sets direction of pins
 */
class gpio_pin_imp
{
	public:

		// Functions.
		/**
		 * Sets the direction of the pin
		 * by manipulating the data direction register
		 * 
		 * @param mode	the direction (INPUT=0,OUTPUT=1)
		 * @return gpio_input_state error code
		 */
		int8_t set_mode(gpio_mode mode);

		/**
		 * Writes to the pin attached to the implementation
		 * 
		 * @param value	sets the pin to (O_LOW, O_HIGH, or O_TOGGLE)
		 * @return int8_t error code
		 */
		int8_t write (gpio_output_state value);

		/**
		 * Reads the pin attached to the implementation
		 * 
		 * @param Nothing.
		 * @return int8_t error code
		 */
		gpio_input_state read (void);
		
		/**
		 * Attaches an interrupt to the pin and enables said interrupt.
		 * 
		 * @param address	The gpio pin address in terms of port and pin
		 * @param *userFunc	A pointer to the user's ISR
		 * @param mode		What kind of interrupt (INT_LOW_LEVEL, INT_ANY_EDGE, INT_FALLING_EDGE, INT_RISING_EDGE) (only valid for the EXTINT pins)
		 * @return inter_return_t return code
		 */
		inter_return_t attach_interrupt(void (*userFunc)(void), interrupt_mode mode);
		
		/**
		 * Detaches the interrupt from the pin and disables said interrupt.
		 * 
		 * @param address	The gpio pin address in terms of port and pin
		 * @return inter_return_t return code
		 */
		inter_return_t disable_interrupt(void);
		
	  // Fields.
	  gpio_pin_address address;
	  semaphore* s;	
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// One implementation for each pin.
gpio_pin_imp gpio_pin_imps[NUM_PORTS][NUM_PINS];

// To show whether we have carrried out the initialisation yet.
bool done_init;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

void gpio_init(void);

// IMPLEMENT PUBLIC FUNCTIONS.
// See gpio.h for descriptions of these functions.
gpio_pin::~gpio_pin(void)
{
	// Make sure we have vacated the semaphore before we go out of scope.
	vacate();

	// All done.
	return;
}

gpio_pin::gpio_pin(gpio_pin_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

int8_t gpio_pin::set_mode(gpio_mode mode)
{
	return (imp->set_mode(mode));
}

int8_t gpio_pin::write(gpio_output_state value)
{
	return (imp->write(value));
}

gpio_input_state gpio_pin::read(void)
{
	return (imp->read());
}

bool gpio_pin::is_valid(void)
{
	return (imp != NULL);
}

void gpio_pin::vacate(void)
{
	// Check if we're already vacated, since there shouldn't be an error if you vacate twice.
	if (imp != NULL)
	{		
		// We haven't vacated yet, so vacate the semaphore.
		imp->s->vacate();
	}

	// Break the link to the implementation.
	imp = NULL;

	// The gpio_pin is now useless.
	
	// All done.
	return;
}

gpio_pin gpio_pin::grab(gpio_pin_address address)
{
	// Check if the GPIO stuff has been initialized.
	if (!done_init)
	{
		// Initialize the GPIO stuff.
		gpio_init();
	}

	// Try to procure the semaphore.
	if (gpio_pin_imps[address.port][address.pin].s->procure())
	{
		// We got the semaphore!
		return gpio_pin(&gpio_pin_imps[address.port][address.pin]);
	}
	else
	{
		// Procuring the semaphore failed, so the pin is already in use.
		return NULL;
	}
}


inter_return_t gpio_pin::enable_interrupt(interrupt_mode mode, void (*user_ISR)(void))
{
      return imp->attach_interrupt(user_ISR,mode); 
}

inter_return_t gpio_pin::disable_interrupt(void)
{
      return imp->disable_interrupt();  
}

// IMPLEMENT PRIVATE FUNCTIONS.

void gpio_init(void)
{
	// Attach the gpio pin implementations to the semaphores which control the corresponding pins.
	for (uint8_t i = 0; i < NUM_PORTS; i++)
	{
		for (uint8_t j = 0; j < NUM_PINS; j++)
		{
			// Attach the semaphores to those in the pin implementations.
			gpio_pin_imps[i][j].s = &semaphores[i][j];
			gpio_pin_imps[i][j].address.port = (port_t)i;
			gpio_pin_imps[i][j].address.pin = (pin_t)j;
		}
	}

	// We don't need to do this again.
	done_init = true;

	// All done.
	return;
}


// DECLARE ISRs

// Each ISR calls the user specified function, by invoking the function pointer in the array of function pointers.
// This offset is here because the interrupts are enumerated, not in the same order as the function array. This is because the number of interrupts changes with architecture.
SIGNAL(INT0_vect) {
  if(intFunc[EINT_0 - INT_DIFF_OFFSET]) 
    intFunc[EINT_0 - INT_DIFF_OFFSET]();
}

SIGNAL(INT1_vect) {
  if(intFunc[EINT_1 - INT_DIFF_OFFSET])
    intFunc[EINT_1 - INT_DIFF_OFFSET]();
}

SIGNAL(INT2_vect) {
  if(intFunc[EINT_2 - INT_DIFF_OFFSET])
    intFunc[EINT_2 - INT_DIFF_OFFSET]();
}

SIGNAL(INT3_vect) {
  if(intFunc[EINT_3 - INT_DIFF_OFFSET])
    intFunc[EINT_3 - INT_DIFF_OFFSET]();
}

SIGNAL(INT4_vect) {
  if(intFunc[EINT_4 - INT_DIFF_OFFSET])
    intFunc[EINT_4 - INT_DIFF_OFFSET]();
}

SIGNAL(INT5_vect) {
  if(intFunc[EINT_5 - INT_DIFF_OFFSET])
    intFunc[EINT_5 - INT_DIFF_OFFSET]();
}

SIGNAL(INT6_vect) {
  if(intFunc[EINT_6 - INT_DIFF_OFFSET])
    intFunc[EINT_6 - INT_DIFF_OFFSET]();
}

SIGNAL(INT7_vect) {
  if(intFunc[EINT_7 - INT_DIFF_OFFSET])
    intFunc[EINT_7 - INT_DIFF_OFFSET]();
}

SIGNAL(PCINT0_vect) {
  if(intFunc[PCINT_0])
    intFunc[PCINT_0]();
}

SIGNAL(PCINT1_vect) {
  if(intFunc[PCINT_1])
    intFunc[PCINT_1]();
}

SIGNAL(PCINT2_vect) {
  if(intFunc[PCINT_2])
    intFunc[PCINT_2]();
}


int8_t gpio_pin_imp::set_mode(gpio_mode mode)
		{
				/* Check to see if parameters are right size */
				if (address.port >= NUM_PORTS) 
				{
					/* Parameter is wrong size*/
					return -1;
				}
				
				if ( address.port >= PORT_H )
					_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_MODE) = (_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_MODE) & ~(1 << address.pin) ) | (mode?(1 << address.pin):0);
				else
					/* Set/clear data direction register pin */
					_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) & ~(1 << address.pin) ) | (mode?(1 << address.pin):0);
				
				return 0;
		}

		
int8_t gpio_pin_imp::write (gpio_output_state value)

		{
				if (address.port >= NUM_PORTS)
				{
					/* Parameter is wrong size*/
					return O_ERROR;
				}
//#if defined (__AVR_ATmega2560__)
//				if (address.port == PORT_I) // There is no PORT_I
//				{
//				    return O_ERROR;
//				}
//#endif
				/* Set/clear port register register pin */
				if (value == O_TOGGLE)
				{		
				    if ( address.port >= PORT_H )
					    /*Toggle value*/
					    _SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) = (_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) & ~(1 << address.pin) ) | ~(_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE));
				    else
					    /*Toggle value*/
					    _SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | ~(_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE));
				}
				else
				{
					    if ( address.port >= PORT_H )
						/* Set or Clear pin on port*/
						_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) = (_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) & ~(1 << address.pin) ) | (value?(1 << address.pin):(pin_t)O_LOW);
					    else
						/* Set or Clear pin on port*/
						_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = ( _SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | (value?(1 << address.pin):(pin_t)O_LOW);
				}
				return 0;
		}
		
gpio_input_state gpio_pin_imp::read (void)

		{
			
				if (address.port >= NUM_PORTS) 
				{
					/* Parameter is wrong size*/
					return I_ERROR;
				}
				
				if ( address.port >= PORT_H )
						/* Read and return pin */
						return ((_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_READ) & (1 << address.pin)) ? I_LOW : I_HIGH);
				else
						/* Read and return pin */
						return ((_SFR_IO8((address.port * PORT_MULTIPLIER) + P_READ) & (1 << address.pin)) ? I_LOW : I_HIGH);
		}
		
		
		
		
inter_return_t gpio_pin_imp::attach_interrupt(void (*userFunc)(void), interrupt_mode mode) 
		{
		    // Check to see if pin is a on a pcint bank
		    if( ( PC_INT[address.port][address.pin] >= PCINT_0 )  && ( PC_INT[address.port][address.pin] < NUM_BANKS ) ) 
		    {
			// Check to see if semaphore is free
			if( pc_int_sem[PC_INT[address.port][address.pin]].procure() )
			{
			    // Change the value in the function pointer array to that given by the user.
			    intFunc[PC_INT[address.port][address.pin]] = userFunc;
			    // if semaphore is free, check which pcint bank it is on, and set interrupt accordingly.
			    switch ((uint8_t)PC_INT[address.port][address.pin]) 
			    {
#if defined (__AVR_ATmega2560__)
			      case PCINT_0:
				PCICR |= (1 << PCINT_0);
				PCMSK0 = (1 << address.pin);
				break;
			      case PCINT_1:
				PCICR |= (1 << PCINT_1);
				// Mostly the pins' position on the interrupt bank matches their position on their port, however pins PORTJ(0-6) match mask bits PCIE1(1-7).
				PCMSK1 = (address.port == PORT_J) ? (1 << (address.pin - 1)) : (1 << address.pin);
				break;
			      case PCINT_2:
				PCICR |= (1 << PCINT_2);
				PCMSK0 = (1 << address.pin);
				break;
#else
#error not yet implemented for this cpu
#endif
			    }
			}
			else
			  return GP_ALREADY_TAKEN;
		    }
			  
		  
		    // Check to see if the pin is one of the special EINT pins
		    else if (( PC_INT[address.port][address.pin] >= EINT_0)  && ( PC_INT[address.port][address.pin] < (EINT_0 + EXT_INT_SIZE ) ) )
		    { 
		      // Configure the interrupt mode (trigger on low input, any change, rising
			// edge, or falling edge).  The mode constants were chosen to correspond
			// to the configuration bits in the hardware register, so we simply shift
			// the mode into place.
			  
			// Enable the interrupt.
			intFunc[PC_INT[address.port][address.pin] - INT_DIFF_OFFSET] = userFunc;  
			switch ((uint8_t)PC_INT[address.port][address.pin]) 
			{
#if defined (__AVR_ATmega2560__)
			  case EINT_0:
			    // Set the mode of interrupt.
			    EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
			    // Enable the interrupt.
			    EIMSK |= (1 << INT0);
			    break;
			  case EINT_1:
			    EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
			    EIMSK |= (1 << INT1);
			    break;
			  case EINT_2:
			    EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
			    EIMSK |= (1 << INT2);
			    break;
			  case EINT_3:
			    EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
			    EIMSK |= (1 << INT3);
			    break;
			  case EINT_4:
			    EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
			    EIMSK |= (1 << INT4);
			    break;
			  case EINT_5:
			    EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
			    EIMSK |= (1 << INT5);
			    break;
			  case EINT_6:
			    EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
			    EIMSK |= (1 << INT6);
			    break;
			  case EINT_7:
			    EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
			    EIMSK |= (1 << INT7);
			    break;
#else
#error attachInterrupt not yet implemented for this cpu (case 1)
			/*
			  case 0:
			  #if defined(EICRA) && defined(ISC00) && defined(EIMSK)
			    EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
			    EIMSK |= (1 << INT0);
			  #elif defined(MCUCR) && defined(ISC00) && defined(GICR)
			    MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
			    GICR |= (1 << INT0);
			  #elif defined(MCUCR) && defined(ISC00) && defined(GIMSK)
			    MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
			    GIMSK |= (1 << INT0);
			  #else
			    #error attachInterrupt not finished for this CPU (case 0)
			  #endif
			    break;

			  case 1:
			  #if defined(EICRA) && defined(ISC10) && defined(ISC11) && defined(EIMSK)
			    EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
			    EIMSK |= (1 << INT1);
			  #elif defined(MCUCR) && defined(ISC10) && defined(ISC11) && defined(GICR)
			    MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
			    GICR |= (1 << INT1);
			  #elif defined(MCUCR) && defined(ISC10) && defined(GIMSK) && defined(GIMSK)
			    MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
			    GIMSK |= (1 << INT1);
			  #else
			    #warning attachInterrupt may need some more work for this cpu (case 1)
			  #endif
			    break;
			    */
#endif
		      }
		    
		    
		  }
		  
		  else
		  {
		      // The Given pin does not have an interrupt available to it.
		      return GP_OUT_OF_RANGE;
		  }
		      // All went according to plan, well done, pat on the back, all that sort of thing.
		      return GP_SUCCESS;
		  
		}
		
		
		
		
inter_return_t gpio_pin_imp::disable_interrupt(void) 
		{
		    // If it is a pin change interrupt, then we have to check the semaphore
		    if( ( PC_INT[address.port][address.pin] >= PCINT_0 )  && ( PC_INT[address.port][address.pin] < NUM_BANKS ) ) 
		    {
			// Check to see if semaphore is free
			if( !pc_int_sem[PC_INT[address.port][address.pin]].procure() )
			{
			    // if semaphore is taken
			    switch ((uint8_t)PC_INT[address.port][address.pin]) 
			    {
#if defined (__AVR_ATmega2560__)
			      case PCINT_0:
				// Disable the interrupt.
				PCICR &= ~(1 << PCINT_0);
				// Clear the mask register so that all pins are disabled.
				PCMSK0 = 0;
				break;
			      case PCINT_1:
				PCICR &= ~(1 << PCINT_1);
				PCMSK0 = 0;
				break;
			      case PCINT_2:
				PCICR &= ~(1 << PCINT_2);
				PCMSK0 = 0;
				break;
#else
#error not for this cpu yet
#endif
			    }
			    // Vacate the semaphore
			    pc_int_sem[PC_INT[address.port][address.pin]].vacate();
			}
			else
			{  
			    // The semaphore was never taken. This could be useful for debugging.
			    return GP_ALREADY_DONE;
			}
			
			intFunc[PC_INT[address.port][address.pin]] = 0;
		    }
		    // If it is an external interrupt (i.e specific pin) then we can disable it easily.
		    else if (( PC_INT[address.port][address.pin] >= EINT_0)  && ( PC_INT[address.port][address.pin] < (EINT_0 + EXT_INT_SIZE ) ) )
		    {
			switch ((uint8_t)PC_INT[address.port][address.pin]) 
			{
#if defined (__AVR_ATmega2560__)
			      case EINT_0:
				// Mask the interrupt so it doesn't fire anymore, i.e put a zero in the mask register.
				EIMSK &= ~(1 << INT0);
				break;
			      case EINT_1:
				EIMSK &= ~(1 << INT1);
				break;
			      case EINT_2:
				EIMSK &= ~(1 << INT2);
				break;
			      case EINT_3:
				EIMSK &= ~(1 << INT3);
				break;
			      case EINT_4:
				EIMSK &= ~(1 << INT4);
				break;
			      case EINT_5:
				EIMSK &= ~(1 << INT5);
				break;
			      case EINT_6:
				EIMSK &= ~(1 << INT6);
				break;
			      case EINT_7:
				EIMSK &= ~(1 << INT7);
				break;
#else
#error not implemented for this cpu
				/*
			      case 0:
			      #if defined(EIMSK) && defined(INT0)
				EIMSK &= ~(1 << INT0);
			      #elif defined(GICR) && defined(ISC00)
				GICR &= ~(1 << INT0); // atmega32
			      #elif defined(GIMSK) && defined(INT0)
				GIMSK &= ~(1 << INT0);
			      #else
				#error detachInterrupt not finished for this cpu
			      #endif
				break;

			      case 1:
			      #if defined(EIMSK) && defined(INT1)
				EIMSK &= ~(1 << INT1);
			      #elif defined(GICR) && defined(INT1)
				GICR &= ~(1 << INT1); // atmega32
			      #elif defined(GIMSK) && defined(INT1)
				GIMSK &= ~(1 << INT1);
			      #else
				#warning detachInterrupt may need some more work for this cpu (case 1)
			      #endif
				break;
				*/
#endif
			  }
		    // detach user's ISR from actual ISR
		    intFunc[PC_INT[address.port][address.pin] - INT_DIFF_OFFSET] = 0;
	      }
	      else
	      {
		  return GP_OUT_OF_RANGE;
	      }
	      return GP_SUCCESS;
	  }
