/**
 *
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		gpio.h
 *  A header file for the GPIO module of the HAL. Contains functionality for writing to and reading from individual pins.
 *  Uses semaphores to prevent resource conflict. The implementation of the functions provided should be in a gpio.cpp
 *  file in the res/ARCHITECTURETYPE/hal folder.
 * 
 *  @brief 
 *  A class that handles GPIO. User grabs control of a GPIO pin which is an instance of this class,
 *  and uses it to manipulate the pin.
 * 
 *  @author 		Edwin Hayes
 *
 *  @date		7-12-2011
 * 
 *  @section 		Licence
 * 
 *  LICENCE GOES HERE
 * 
 *  
 * 
 *  @section Description
 *
 * This is the header file which matches gpio.cpp.  
 * This class implements functions for general i/o. 
 * As many pins have multiple uses, semaphores are used to make sure that pins are only being used by one peripheral at once. 
 * In order to use a GPIO pin, one must call the static gpio_pin_grab function, which, if the pin is free, will
 * return a pointer to a gpio_pin_imp implementation of the GPIO. If this is a valid pointer, the program now has control 
 * of that pin until it relinquishes control using the vacate function. 
 * An instance of this class cannot be instantiated using a constructor, but must be created using the gpio_pin_grab function.
 * 
 * @section Example
 * @code
 * gpio_pin_address my_pin_address;
 * my_pin_address.port = PORT_B;
 * my_pin_address.pin = PIN_5;
 * gpio_pin my_pin = gpio_pin::grab(my_pin_address);
 * if (my_pin.is_valid())
 * {
 * 	my_pin.set_mode(OUTPUT);
 * 	my_pin.write(HIGH);
 * 	my_pin.set_mode(INPUT);
 * 	if (my_pin.read() == HIGH)
 * 	{
 * 		my_pin.enable_interrupt(RISING_EDGE,&myISR);
 * 	}
 * }
 * 
 * void myISR()
 * {
 * 	do_something();
 * }
 * @endcode
 */

// Only include this header file once.
#ifndef __GPIO_H__
#define __GPIO_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the semaphore library that someone is gonna create.
#include "semaphore.h"

// Include the hal library.
#include "hal/hal.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

typedef void (*voidFuncPtr)(void);

enum gpio_mode {INPUT, OUTPUT};

enum gpio_output_state {O_LOW, O_HIGH, O_TOGGLE, O_ERROR=-1};

enum gpio_input_state {I_LOW, I_HIGH, I_ERROR=-1};

enum inter_return_t {GP_SUCCESS, GP_ALREADY_DONE, GP_ALREADY_TAKEN=-1, GP_OUT_OF_RANGE=-2};

enum interrupt_mode {INT_LOW_LEVEL, INT_ANY_EDGE, INT_FALLING_EDGE, INT_RISING_EDGE};

// FORWARD DEFINE PRIVATE PROTOTYPES.

class gpio_pin_imp;

/**
 * @class
 * This class implements functions for general i/o. 
 * As many pins have multiple uses, semaphores are used to make sure that pins are only being used by one peripheral at once. 
 * In order to use a GPIO pin, one must call the static gpio_pin_grab function, which, if the pin is free, will
 * return a pointer to a gpio_pin_imp implementation of the GPIO. If this is a valid pointer, the program now has control 
 * of that pin until it relinquishes control using the vacate function. 
 * An instance of this class cannot be instantiated using a constructor, but must be created using the gpio_pin_grab function.
 * 
 */
// DEFINE PUBLIC CLASSES.
class gpio_pin
{
	public:
		// Functions.

		/**
		 * Gets run whenever the instance of class gpio_pin goes out of scope.
		 * Vacates the semaphore, allowing the pin to be allocated elsewhere.
		 * This is useful for vacating a pin automatically, without using the vacate function. However,
		 * users are recommended to use the vacate function for consistency and safety.
		 * @param Nothing
		 * @return Nothing
		 */
		 ~gpio_pin(void);
		
		/**
		 * Sets the pin to an input or output. Does not have any other options (such as Pull-up, Pull-Push, Open Drain), kept simple.
		 * If you want to use these functions, circumvent the HAL.
		 * @subsection	Example
		 * @code
		 * set_mode(INPUT); 
		 * @endcode
		 * @param  mode	Set to INPUT or OUTPUT.
		 * @return 0 for success, -1 for error. Errors occur mostly when the pin is out of scope for this Target.
		 * 
		 */
		int8_t set_mode(gpio_mode mode);
				
		/**
		 * Reads the value of the gpio pin and returns it. To compare, use the specified types (LOW, HIGH).
		 * 
		 * @subsection Example 
		 * @code
		 * if (my_pin.read() == HIGH)
		 * {
		 * 	my_pin.write(LOW);
		 * }
		 * @endcode
		 * @return LOW (0), HIGH (1), or ERROR (-1).
		 * 
		 * @param Nothing
		 * @return Nothing
		 */
		gpio_input_state read(void);
		
		/**
		 * Writes the value provided to the pin. A value of TOGGLE will simply change it to what it currently isn't,
		 * i.e if it is currently HIGH it will be set LOW and vice versa.
		 * 
		 * @subsection Example
		 * @code
		 * if (my_pin.read() == HIGH)
		 * {
		 * 	my_pin.write(LOW);
		 * } 
		 * @endcode
		 * @param  value	HIGH(1), LOW(0) or TOGGLE(2).
		 * @return Nothing
		 */
		int8_t write(gpio_output_state value);
		
		/** 
		 * Initialise an interrupt for the associated pin in the specified mode
		 * and attach the ISR function pointer provided to the interrupt.
		 * To use this, create a function that you will use as your ISR. Pass the
		 * pointer to your ISR into this function.
		 * 
		 * @subsection Example
		 * @code
		 * if (my_pin.enable_interrupt(RISING_EDGE, &myISR) == GP_SUCCESS)
		 * {
		 * 	runMyThings();
		 * }
		 * else
		 * {
		 * 	giveUp();
		 * }
		 * @endcode
		 * @param  mode		Any number of interrupt types (RISING_EDGE, FALLING_EDGE, BLOCKING, NON_BLOCKING).
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return 		Whether it was successful. Shouldn't really need to be used.
		 * @return inter_return_t 	(GP_SUCCESS, GP_ALREADY_DONE, GP_ALREADY_TAKEN=-1, GP_OUT_OF_RANGE=-2)
		 */
		inter_return_t enable_interrupt(interrupt_mode mode, void (*func_pt)(void));
		
		/**
		 *
		 * Disable an interrupt for the associated pin. The interrupt is still set up, but is simply masked at this stage.
		 *
		 * @param  Nothing.
		 * @return inter_return_t 	(GP_SUCCESS, GP_ALREADY_DONE, GP_ALREADY_TAKEN=-1, GP_OUT_OF_RANGE=-2)
		 */
		inter_return_t disable_interrupt(void);
		
		/**
		 * Checks to see whether or not the GPIO pin implementation pointer is null or not. Use this after
		 * using gpio_pin_grab to see if your pin grab was successful or not. If the pin grab was
		 * unsuccessful then probably the pin was already being used by another peripheral.
		 * 
		 * @subsection Example
		 * @code
		 * gpio_pin my_pin = gpio_pin::grab(my_pin_address);
		 * if (my_pin.is_valid())
		 * {
		 * 	my_pin.write(HIGH);
		 * }
		 * @endcode
		 * 
		 * @param Nothing
		 * @return True if the implementation pointer is not NULL, false otherwise.
		 */
		bool is_valid(void);
		
		/** 
		 * Allows access to the GPIO pin to be relinquished and assumed elsewhere. Use this
		 * when are process has finished with a pin and no longer needs control over it. This 
		 * lets another process grab control of that pin.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request access to a gpio pin and manages the semaphore
		 * indicating whether access has been granted or not.
		 * THIS IS THE ONLY WAY (using the hal) TO GET AN INSTANCE OF A GPIO PIN.
		 * @subsection Example
		 * @code
		 * gpio_pin_address my_pin_address;
		 * my_pin_address.port = PORT_B;
		 * my_pin_address.pin = PIN_5;
		 * gpio_pin my_pin = gpio_pin::grab(my_pin_address);
		 * if (my_pin.is_valid())
		 * {
		 * 	my_pin.write(HIGH);
		 * }
		 * @endcode
		 *
		 * @param  gpio_pin_address	Address of the GPIO pin requested.
		 * @return A gpio_pin instance.
		 */
		static gpio_pin grab(gpio_pin_address);

	private:
		// Functions.
		
		gpio_pin(void);	// Poisoned.

		gpio_pin(gpio_pin_imp*);

		gpio_pin operator =(gpio_pin const&);	// Poisoned.

		// Fields.

		/*
		* Pointer to the machine specific implementation of the GPIO pin.
		*/
		gpio_pin_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__GPIO_H__*/

// ALL DONE.
