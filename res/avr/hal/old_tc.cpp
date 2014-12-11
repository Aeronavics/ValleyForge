// /* Array of user ISRs for timer interrupts. */
// void (*timerInterrupts[NUM_TIMER_INTERRUPTS])(void) = {NULL};

// /* Create an array of timer implementation. */
// timer_imp timer_imps[NUM_TIMERS];

// /* Variable to indicate whether timer_imps[] has been initialised yet */
// bool initialised_timers;

// /*Enumerated list of timer interrupts for use in accessing the appropriate function pointer from the function pointer array*/
// enum timer_interrupts {TIMER0_COMPA_int, TIMER0_COMPB_int, TIMER0_OVF_int, TIMER1_CAPT_int, TIMER1_COMPA_int, TIMER1_COMPB_int, TIMER1_COMPC_int, TIMER1_OVF_int, TIMER2_COMPA_int, TIMER2_COMPB_int, TIMER2_OVF_int, TIMER3_CAPT_int, TIMER3_COMPA_int, TIMER3_COMPB_int, TIMER3_COMPC_int, TIMER3_OVF_int, TIMER4_CAPT_int, TIMER4_COMPA_int, TIMER4_COMPB_int, TIMER4_COMPC_int, TIMER4_OVF_int, TIMER5_CAPT_int, TIMER5_COMPA_int, TIMER5_COMPB_int, TIMER5_COMPC_int, TIMER5_OVF_int};



// /**
// * Allows a process to request access to a timer and manages the semaphore
// * indicating whether access has been granted or not.
// *
// * @param  timerNumber	Which timer is required.
// * @return A timer instance.
// */
// timer timer::grab(tc_number timerNumber)
// {
//   /* TODO add possible semaphore functionality in here*/
  
//   /* Check to make sure the timers have been initialised */
//   if  (!initialised_timers)
//   {
//     /* Go and initialise them */
//     for (uint8_t i = 0; i < NUM_TIMERS; i++)
//     {
//       timer_imps[i].timer_id = (tc_number)i;
//     }
    
//     /* Assign the implementation semaphore pointers to their associated peripheral pins */
//     /* Timer/Counter 0 */ /* TODO: break out into a seperate initialisation function */
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_A].address.port = TC0_OC_A_PORT;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_A].address.pin = TC0_OC_A_PIN;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_A].s = &semaphores[(int8_t)TC0_OC_A_PORT][(int8_t)TC0_OC_A_PIN];
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_B].address.port = TC0_OC_B_PORT;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_B].address.pin = TC0_OC_B_PIN;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_B].s = &semaphores[(int8_t)TC0_OC_B_PORT][(int8_t)TC0_OC_B_PIN];
    
//     /* Timer/Counter 1 */
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_A].address.port = TC1_OC_A_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_A].address.pin = TC1_OC_A_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_A].s = &semaphores[(int8_t)TC1_OC_A_PORT][(int8_t)TC1_OC_A_PIN];
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_B].address.port = TC1_OC_B_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_B].address.pin = TC1_OC_B_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_B].s = &semaphores[(int8_t)TC1_OC_B_PORT][(int8_t)TC1_OC_B_PIN];
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_C].address.port = TC1_OC_C_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_C].address.pin = TC1_OC_C_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC1_OC_C_PORT][(int8_t)TC1_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_1].timer_pins[TC_IC_CHANNEL_A].address.port = TC1_IC_A_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_IC_CHANNEL_A].address.pin = TC1_IC_A_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC1_IC_A_PORT][(int8_t)TC1_IC_A_PIN];
    
//     /* Timer/Counter 2 */
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_A].address.port = TC2_OC_A_PORT;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_A].address.pin = TC2_OC_A_PIN;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_A].s = &semaphores[(int8_t)TC2_OC_A_PORT][(int8_t)TC2_OC_A_PIN];
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_B].address.port = TC2_OC_B_PORT;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_B].address.pin = TC2_OC_B_PIN;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_B].s = &semaphores[(int8_t)TC2_OC_B_PORT][(int8_t)TC2_OC_B_PIN];
    
//      /* Timer/Counter 3 */
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_A].address.port = TC3_OC_A_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_A].address.pin = TC3_OC_A_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_A].s = &semaphores[(int8_t)TC3_OC_A_PORT][(int8_t)TC3_OC_A_PIN];
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_B].address.port = TC3_OC_B_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_B].address.pin = TC3_OC_B_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_B].s = &semaphores[(int8_t)TC3_OC_B_PORT][(int8_t)TC3_OC_B_PIN];
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_C].address.port = TC3_OC_C_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_C].address.pin = TC3_OC_C_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC3_OC_C_PORT][(int8_t)TC3_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_3].timer_pins[TC_IC_CHANNEL_A].address.port = TC3_IC_A_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_IC_CHANNEL_A].address.pin = TC3_IC_A_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC3_IC_A_PORT][(int8_t)TC3_IC_A_PIN];
    
//     /* Timer/Counter 4 */
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_A].address.port = TC4_OC_A_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_A].address.pin = TC4_OC_A_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_A].s = &semaphores[(int8_t)TC4_OC_A_PORT][(int8_t)TC4_OC_A_PIN];
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_B].address.port = TC4_OC_B_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_B].address.pin = TC4_OC_B_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_B].s = &semaphores[(int8_t)TC4_OC_B_PORT][(int8_t)TC4_OC_B_PIN];
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_C].address.port = TC4_OC_C_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_C].address.pin = TC4_OC_C_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC4_OC_C_PORT][(int8_t)TC4_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_4].timer_pins[TC_IC_CHANNEL_A].address.port = TC4_IC_A_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_IC_CHANNEL_A].address.pin = TC4_IC_A_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC4_IC_A_PORT][(int8_t)TC4_IC_A_PIN];
    
//     /* Timer/Counter 5 */
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_A].address.port = TC5_OC_A_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_A].address.pin = TC5_OC_A_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_A].s = &semaphores[(int8_t)TC5_OC_A_PORT][(int8_t)TC5_OC_A_PIN];
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_B].address.port = TC5_OC_B_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_B].address.pin = TC5_OC_B_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_B].s = &semaphores[(int8_t)TC5_OC_B_PORT][(int8_t)TC5_OC_B_PIN];
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_C].address.port = TC5_OC_C_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_C].address.pin = TC5_OC_C_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC5_OC_C_PORT][(int8_t)TC5_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_5].timer_pins[TC_IC_CHANNEL_A].address.port = TC5_IC_A_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_IC_CHANNEL_A].address.pin = TC5_IC_A_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC5_IC_A_PORT][(int8_t)TC5_IC_A_PIN];    
    
//     initialised_timers = true;
//   }
  
//   /* Set the local field 'imp' pointer to point to the specific
//    * implementation of timer_imp */
//   return timer(&timer_imps[timerNumber]);
// }

// // IMPLEMENT PRIVATE FUNCTIONS.

// timer::timer(timer_imp* implementation)
// {
//   /*attach the timer implementation*/
//   imp = implementation;
// }

// /**
// * Sets the timer rate by selecting the clk src and prescaler.
// * 
// * Store the timer number, prescalar and clock settings into fields
// * within the implementation.
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::set_rate(timer_rate rate)
// {
//   /* Check the rate (i.e prescalar) is compatible with the timer chosen */
//   switch (timer_id)
//   {
//     case TC_0:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK0_ADDRESS;
//       registerTable.TCCRB_address = TCCR0B_ADDRESS;
//       registerTable.TCCRA_address = TCCR0A_ADDRESS;
//       registerTable.OCRB_address = OCR0B_ADDRESS;
//       registerTable.OCRA_address = OCR0A_ADDRESS;
//       registerTable.TCNT_address = TCNT0_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_8_BIT;

//       break;
//     }
//     case TC_1:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK1_ADDRESS;
//       registerTable.TCCRB_address = TCCR1B_ADDRESS;
//       registerTable.TCCRA_address = TCCR1A_ADDRESS;
//       registerTable.OCRC_address = OCR1C_ADDRESS;
//       registerTable.OCRB_address = OCR1B_ADDRESS;
//       registerTable.OCRA_address = OCR1A_ADDRESS;
//       registerTable.ICR_address = ICR1_ADDRESS;
//       registerTable.TCNT_address = TCNT1_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//     case TC_2:
//     {
//       /* No invalid settings */
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK2_ADDRESS;
//       registerTable.TCCRB_address = TCCR2B_ADDRESS;
//       registerTable.TCCRA_address = TCCR2A_ADDRESS;
//       registerTable.OCRB_address = OCR2B_ADDRESS;
//       registerTable.OCRA_address = OCR2A_ADDRESS;
//       registerTable.TCNT_address = TCNT2_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_8_BIT;

//       break;
//     }
//     case TC_3:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK3_ADDRESS;
//       registerTable.TCCRB_address = TCCR3B_ADDRESS;
//       registerTable.TCCRA_address = TCCR3A_ADDRESS;
//       registerTable.OCRC_address = OCR3C_ADDRESS;
//       registerTable.OCRB_address = OCR3B_ADDRESS;
//       registerTable.OCRA_address = OCR3A_ADDRESS;
//       registerTable.ICR_address = ICR3_ADDRESS;
//       registerTable.TCNT_address = TCNT3_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//     case TC_4:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK4_ADDRESS;
//       registerTable.TCCRB_address = TCCR4B_ADDRESS;
//       registerTable.TCCRA_address = TCCR4A_ADDRESS;
//       registerTable.OCRC_address = OCR4C_ADDRESS;
//       registerTable.OCRB_address = OCR4B_ADDRESS;
//       registerTable.OCRA_address = OCR4A_ADDRESS;
//       registerTable.ICR_address = ICR4_ADDRESS;
//       registerTable.TCNT_address = TCNT4_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//     case TC_5:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK5_ADDRESS;
//       registerTable.TCCRB_address = TCCR5B_ADDRESS;
//       registerTable.TCCRA_address = TCCR5A_ADDRESS;
//       registerTable.OCRC_address = OCR5C_ADDRESS;
//       registerTable.OCRB_address = OCR5B_ADDRESS;
//       registerTable.OCRA_address = OCR5A_ADDRESS;
//       registerTable.ICR_address = ICR5_ADDRESS;
//       registerTable.TCNT_address = TCNT5_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//   }
//   /*Preserve the clock and prescalar settings within the implementation fields if code makes it this far*/
//   preserved_rate = rate;
    
//   return 0;	/* Exit success	*/
// }

// /**
// * Loads the timer with a value.
// *
// * @param value		The value the timer register will have.
// * @return 0 for success, -1 for error.
// */
// template <typename T>
// int8_t timer_imp::load_timer_value(T value)
// {
//   if (timerType == TIMER_16_BIT)
//   {
//     _SFR_MEM16(registerTable.TCNT_address) = value;
//   }
//   else if (registerTable.TCNT_address > 0x60)
//   {
//     _SFR_MEM8(registerTable.TCNT_address) = value;
//   }
//   else
//   {
//     _SFR_IO8(registerTable.TCNT_address) = value;
//   }
  
//  return 0;
// }

// /**
// * Gets the value of the timer register.
// *
// * @return T 	The timer value
// */
// template <typename T>
// T timer_imp::get_timer_value(void)
// {
//   if (timerType == TIMER_16_BIT)
//   {
//     return(_SFR_MEM16(registerTable.TCNT_address));
//   }
//   else if (registerTable.TCNT_address > 0x60)
//   {
//     return(_SFR_MEM8(registerTable.TCNT_address));
//   }
//   else
//   {
//     return(_SFR_IO8(registerTable.TCNT_address));
//   }
// }

// /**
// * Starts the timer.
// *
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::start(void)
// {
//   /*Switch which registers are edited based on the timer number*/
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//       /*edit the TCCR0A and TCCR0B registers*/
//       start_timer0(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_1:
//     {
//       /*edit the TCCR1A and TCCR1B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_2:
//     {
//       /*edit the TCCR2A and TCCR2B registers*/
//       start_timer2(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_3:
//     {
//       /*edit the TCCR3A and TCCR3B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_4:
//     {
//       /*edit the TCCR4A and TCCR4B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_5:
//     {
//       /*edit the TCCR5A and TCCR5B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//   }
//   return 0;	//How to return -1 in case of an error?
// }

// /**
// * Stops the timer.
// *
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::stop(void)
// {
//   if (registerTable.TCNT_address > 0x60)
//   {
//     _SFR_MEM8(registerTable.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
//   }
//   else
//   {
//     _SFR_IO8(registerTable.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
//   }
  
//   return 0;
// }

// /**
// * Enables the overflow interrupt on this timer
// *
// * @param  ISRptr		A pointer to the ISR that will be called when this interrupt is generated.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_tov_interrupt(void (*ISRptr)(void))
// {
//     /* Set the TCCRnA and TCCRnB WGMn2:0 bits to 0 for normal operation where the timer/counter
//     * counting direction is always incremented from 0x00(00) to 0xFF(FF) (16-bit implementation)
//     * and the TOVn flag is set when the counter is reset to 0x00(00).
//     *	
//     * Set the appropriate registers depending on which timer/counter implementation
//     * is for.
//     * 
//     * In addition, place the user-provided ISR into the appropriate position of the timerInterrupts
//     * ISR
//     * 
//     * 
//     */
  
//   if (registerTable.TCCRA_address > 0x60)
//   {
//     _SFR_IO8(registerTable.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_IO8(registerTable.TCCRB_address) &= ~(1 << WGM2_BIT);
//   }
//   else
//   {
//     _SFR_MEM8(registerTable.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(registerTable.TCCRB_address) &= ~(1 << WGM2_BIT);
//   }
//   _SFR_MEM8(registerTable.TIMSK_address) |= (1 << TOIE_BIT);
  
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//       timerInterrupts[TIMER0_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_1:
//     {
//       timerInterrupts[TIMER1_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_2:
//     {
//       timerInterrupts[TIMER2_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_3:
//     {
//       timerInterrupts[TIMER3_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_4:
//     {
//       timerInterrupts[TIMER4_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_5:
//     {
//       timerInterrupts[TIMER5_OVF_int] = ISRptr;
//       break;
//     }
//   }  
//   return 0;
// }

// /**
// * Disables the overflow interrupt on this timer
// *
// * @param  Nothing.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::disable_tov_interrupt(void)
// {
//   /*
//    * To disable the timer overflow interrupt
//    * clear the TOIEn bit in the TIMSKn register
//    */
//   _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << TOIE_BIT);
  
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER0_OVF_int] = NULL;
//       break;
//     }
//     case TC_1:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER1_OVF_int] = NULL;
//       break;
//     }
//     case TC_2:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER2_OVF_int] = NULL;
//       break;
//     }
//     case TC_3:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER3_OVF_int] = NULL;
//       break;
//     }
//     case TC_4:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER4_OVF_int] = NULL;
//       break;
//     }
//     case TC_5:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER5_OVF_int] = NULL;
//       break;
//     }
//   }    
//   return 0;
// }

// /**
// * Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode
// * operation for Timer/Counter implemented.
// *
// * @param mode			Which mode the OC channel should be set to.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_oc(tc_oc_mode mode)
// {
//   /* Switch the process of enabling output compare interrupts depending on which timer
//    * has been initialised.
//    */
//   switch(timer_id)
//   {
//     case TC_0:
//     { 
//       enable_oc_8bit(mode, &registerTable);
//       break;
//     }
//     case TC_1:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     case TC_2:
//     {
//       enable_oc_8bit(mode, &registerTable);
//       break;
//     }
//     case TC_3:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     case TC_4:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     case TC_5:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     default:	/* No more timers available, return an error. */
//     {
//       return -1;
//     }
//   } 
//   return 0;	/*Should never get here*/
// }

// /**
// * Enables output channel attached to each Timer/Counter for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode
// * operation for Timer/Counter implemented.
// *
// * @param mode			Which mode the OC channel should be set to.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_oc_channel(tc_oc_channel channel, tc_oc_channel_mode mode)
// {
//   /*
//    * Switch action to be peformed on register depending on which mode is provided
//    * for function.
//    * 
//    * Note: Process of setting and clearing bits is as follows. Register TCCRnA is structured as below
//    * 	7	  6	   5	    4	     3		2
//    * ------------------------------------------------------------
//    * | COMnA1 | COMnA0 | COMnB1 | COMnB0 | COMnC1* | COMnC0* | etc.
//    * ------------------------------------------------------------ 
//    * (* - Only relevant on 16-bit timers)
//    * 
//    * Thus, to generalise the setting and clearing of bits; COMnA1 or COMnA0 are used in conjunction
//    * with a 'COM_BIT_OFFSET' (2 in this case) and the tc_oc_channel value as a multiplier to set the exact
//    * bit(s) required.
//    */

// if (mode == OC_CHANNEL_MODE_0)	/* COMnX1:0 bits set to 0x00 */
// {
//   if (registerTable.TCCRA_address > 0x60)
//   {
//     _SFR_MEM8(registerTable.TCCRA_address) &= (~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) & ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
//   }
//   else
//   {
//     _SFR_IO8(registerTable.TCCRA_address) &= (~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) & ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
//   }
  
//   /* Vacate the associated GPIO semaphore */
//   timer_pins[(int8_t)channel].s.vacate();
// }
// /* Attempt to procure the semaphore for the GPIO pin required prior to setting the output bits */
// else if (timer_pins[(int8_t)channel].s.procure())
// {
//   switch (mode)
//   {
//     case OC_CHANNEL_MODE_1:	/* COMnX1:0 bits set to 0x01 */
//     {
//       if (registerTable.TCCRA_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.TCCRA_address) &= ~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_MEM8(registerTable.TCCRA_address) |= (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.TCCRA_address) &= ~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_IO8(registerTable.TCCRA_address) |= (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
//       }
      
//       break;
//     }
//     case OC_CHANNEL_MODE_2:	/* COMnX1:0 bits set to 0x02 */
//     {
//       if (registerTable.TCCRA_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.TCCRA_address) |= (1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_MEM8(registerTable.TCCRA_address) &= ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));

//       }
//       else
//       {
// 	_SFR_IO8(registerTable.TCCRA_address) |= (1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_IO8(registerTable.TCCRA_address) &= ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
//       }
      
//       break;
//     }
//     case OC_CHANNEL_MODE_3:	/* COMnX1:0 bits set to 0x03 */
//     {
//       if (timer_pins[(int8_t)channel].s.procure())
//       {
// 	if (registerTable.TCCRA_address > 0x60)
// 	{
// 	  _SFR_MEM8(registerTable.TCCRA_address) |= ((1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) | (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
// 	}
// 	else
// 	{
// 	  _SFR_IO8(registerTable.TCCRA_address) |= ((1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) | (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
// 	}
//       }
      
//       break;
//     }
//     default:
//       return -1;
//   }    
//   /* 
//    * Set the acquired GPIO pin as an OUTPUT 
//    */
//   if (timer_pins[(int8_t)channel].address.port < PORT_H)
//   {
//     _SFR_IO8(timer_pins[(int8_t)channel].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) |= (1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//   }
//   else
//   {
//     _SFR_MEM8(timer_pins[(int8_t)channel].address.port * PORT_REGISTER_MULTIPLIER + HIGHER_REGISTER_PORT_OFFSET) |= (1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//   }

// }
// else
// {
//   return -1;
// }
	
// return 0;
// }

// /**
// * Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
// * enable OC mode itself.
// *
// * @param  channel		Which channel register to interrupt on.
// * @param  ISRptr			A pointer to the ISR that is called when this interrupt is generated.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_oc_interrupt(tc_oc_channel channel, void (*ISRptr)(void))
// {
//   /*
//    * Save the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */
//   switch (timer_id)
//   {
//     case TC_0:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER0_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER0_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	default:
// 	{
// 	  return -1;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_1:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER1_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER1_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER1_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_2:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER2_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER2_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	default:
// 	{
// 	  return -1;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_3:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER3_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER3_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER3_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_4:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER4_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER4_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER4_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_5:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER5_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER5_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER5_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//   }  
  
//   /* 
//    * Switch which output compare interrupt to enable based on which channel is provided
//    */
//   switch (channel)
//   {
//     case TC_OC_A:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << OCIEA_BIT);
//       break;
//     }
//     case TC_OC_B:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << OCIEB_BIT);
//       break;
//     }
//     case TC_OC_C:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << OCIEC_BIT);
//       break;
//     }
//   }
  
//   return 0;
// }

// /**
// * Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
// * OC mode operation itself.
// *
// * @param channel		Which channel register to disable the interrupt on.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::disable_oc_interrupt(tc_oc_channel channel)
// {
//   /*
//    * Clear the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */ 
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER0_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER0_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_1:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER1_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER1_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_2:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER2_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER2_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_3:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER3_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER3_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_C:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER3_COMPC_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_4:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER4_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER4_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_C:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER4_COMPC_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_5:
//     {
//        /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER5_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER5_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_C:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER5_COMPC_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//   }
  
//   /* Switch the process of disabling output compare interrupts depending on which timer is used for
//    * implementation
//    */
//   switch (channel)
//   {
//     case TC_OC_A:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << OCIEA_BIT);
//       break;
//     }
//     case TC_OC_B:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << OCIEB_BIT);
//       break;
//     }
//     case TC_OC_C:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << OCIEC_BIT);
//       break;
//     }
//   }
  
//   return 0; 
// }

// /**
// * Sets the channel value for output compare.
// *
// * @param channel	Which channel to set the OC value for.
// * @param value		The value where when the timer reaches it, something will happen.
// * @return 0 for success, -1 for error.
// */
// template <typename T>
// int8_t timer_imp::set_ocR(tc_oc_channel channel, T value)
// {
//   switch(channel)
//   {
//     case TC_OC_A:
//     {
//       /* Write to the OCRnX register to set the output compare value */
//       if (timerType == TIMER_16_BIT)
//       {
// 	_SFR_MEM16(registerTable.OCRA_address) = value;
//       }
//       else if (registerTable.OCRA_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.OCRA_address) = value;
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.OCRA_address) = value;
//       }
      
//       break;
//     }
//     case TC_OC_B:
//     {
//       /* Write to the OCRnX register to set the output compare value */
//       if (timerType == TIMER_16_BIT)
//       {
// 	_SFR_MEM16(registerTable.OCRB_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM16(registerTable.OCRA_address) == 0x0000)
// // 	{
// // 	  _SFR_MEM16(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else if (registerTable.OCRB_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.OCRB_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_MEM8(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.OCRB_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_IO8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_IO8(registerTable.OCRA_address) = value;
// // 	}
//       }
      
//       break;
//     }
//     case TC_OC_C:	/* TODO: Prevent user from writing to TC_OC_C if using a counter that only has two channels. */
//     {
//       /* Write to the OCRnX register to set the output compare value */
//       if (timerType == TIMER_16_BIT)
//       {
// // 	_SFR_MEM16(registerTable.OCRC_address) = value;
// // 	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM16(registerTable.OCRA_address) == 0x0000)
// // 	{
// // 	  _SFR_MEM16(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else if (registerTable.OCRC_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.OCRC_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_MEM8(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.OCRC_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_IO8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_IO8(registerTable.OCRA_address) = value;
// // 	}
//       }
      
//       break;
//     }
//     default:		/* Not a valid channel for this timer */
//       return -1;
//   }

//   return 0;   
// }

// /**
// * Sets the channel value for output compare when TOP is equal to the ICRn register.
// *
// * @param channel	Which channel to set the OC value for.
// * @param value		The value where when the timer reaches it, something will happen.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::set_icR(tc_oc_channel channel, uint16_t value)
// {
//   _SFR_MEM16(registerTable.ICR_address) = value;
  
//   return 0;
// }

// /**
// * Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
// * operation for the specified channel.
// *
// * @param channel		Which IC channel should be enabled.
// * @param mode			Which mode the IC channel should be set to.
// */
// int8_t timer_imp::enable_ic(tc_ic_channel channel, tc_ic_mode mode)
// {
//   /*
//    * Switch which mode is enabled on the input capture unit by the value
//    * given to the function
//    */
//   /* Attempt to procure the required GPIO semaphore first */
//   if (timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].s.procure())
//   {
//     switch(channel)
//     {
//       case TC_IC_A:
//       {
// 	/* Switch depending on which mode is supplied */
// 	switch(mode)
// 	{
// 	  case IC_NONE:
// 	  {
// 	    /* Any disabling code for IC goes here */
// 	    break;
// 	  }
// 	  case IC_MODE_1:	/* Rising edge and input noise cancellation enabled */
// 	  {
// 	    /* Set the ICESn bit in TCCRnB for rising edge detection & the ICNCn bit in the same register for noise cancellation */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_MEM8(registerTable.TCCRB_address) |= ((1 << ICES_BIT) | (1 << ICNC_BIT));
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) |= ((1 << ICES_BIT) | (1 << ICNC_BIT));
// 	    }
	    
// 	    break;
// 	  }
// 	  case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
// 	  {
// 	    /* Set the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_MEM8(registerTable.TCCRB_address) |= (1 << ICES_BIT); 
// 	      _SFR_MEM8(registerTable.TCCRB_address) &= ~(1 << ICNC_BIT);		  
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) |= (1 << ICES_BIT); 
// 	      _SFR_IO8(registerTable.TCCRB_address) &= ~(1 << ICNC_BIT);	  
// 	    }
	    
// 	    break;
// 	  }
// 	  case IC_MODE_3:	/* Falling edge and input noise cancellation enabled */
// 	  {
// 	    /* Clear the ICESn bit in TCCRnB for falling edge detection & set the ICNCn bit in the same register for noise cancellation */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_MEM8(registerTable.TCCRB_address) |= (1 << ICNC_BIT);
// 	      _SFR_MEM8(registerTable.TCCRB_address) &= ~(1 << ICES_BIT);	  
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) |= (1 << ICNC_BIT);
// 	      _SFR_IO8(registerTable.TCCRB_address) &= ~(1 << ICES_BIT);
// 	    }
	  
// 	    break;
// 	  }
// 	  case IC_MODE_4:	/* Falling edge and input noise cancellation disabled */
// 	  {
// 	    /* Clear the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));	  
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));	  
// 	    }r
	    
// 	    break;
// 	  }
// 	  default:	/* Invalid mode for timer */
// 	    return -1;
// 	}
// 	break;
//       }
//       /* Any more IC channels go here*/
//     }  
    
//     /* 
//      * Set the acquired GPIO pin as an INPUT 
//      */
//     if (timer_pins[(int8_t)channel].address.port < PORT_H)
//     {
//       _SFR_IO8(timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//     }
//     else
//     {
//       _SFR_MEM8(timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + HIGHER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//     }
  
//     return 0;
//   }
//   else
//     return -1;
// }

// /**
// * Enables the input compare interrupt on this timer
// *
// * @param  channel		Which channel register to interrupt on.
// * @param  ISRptr			A pointer to the ISR that is called when this interrupt is generated.  
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_ic_interrupt(tc_ic_channel channel, void (*ISRptr)(void))
// {
//   /*
//    * Save the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */
//   switch (timer_id)
//   {
//     case TC_1:
//     {
//       timerInterrupts[TIMER1_CAPT_int] = ISRptr;
//       break;
//     }
//     case TC_3:
//     {
//       timerInterrupts[TIMER3_CAPT_int] = ISRptr;
//       break;
//     }
//     case TC_4:
//     {
//       timerInterrupts[TIMER4_CAPT_int] = ISRptr;
//       break;
//     }
//     case TC_5:
//     {
//       timerInterrupts[TIMER5_CAPT_int] = ISRptr;
//       break;
//     }
//     default:
//     {
//       return -1;
//       break;
//     }
//   }
 
//   /* 
//    *Switch depending on which channel is supplied 
//    */
//   switch (channel)
//   {
//     case TC_IC_A:
//     {
//       /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << ICIE_BIT);
         
//       break;
//     }
//     /* TODO: more channels go here if needed */
//   }
  
//   return 0;    
// }

// /**
// * Disables the input compare interrupt on this timer
// *
// * @param channel		Which channel register to disable the interrupt on.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::disable_ic_interrupt(tc_ic_channel channel)
// {
//   /*
//    * Clear the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */
//   switch (timer_id)
//   {
//     case TC_1:
//     {
//       timerInterrupts[TIMER1_CAPT_int] = NULL;
//       break;
//     }
//     case TC_3:
//     {
//       timerInterrupts[TIMER3_CAPT_int] = NULL;
//       break;
//     }
//     case TC_4:
//     {
//       timerInterrupts[TIMER4_CAPT_int] = NULL;
//       break;
//     }
//     case TC_5:
//     {
//       timerInterrupts[TIMER5_CAPT_int] = NULL;
//       break;
//     }
//     default:
//     {
//       return -1;
//       break;
//     }
//   }
  
//   /* 
//    * Switch depending on which channel is supplied 
//    */
//   switch (channel)
//   {
//     case TC_IC_A:
//     {
//       /* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << ICIE_BIT);
         
//       break;
//     }
//     /* TODO: more channels go here if needed */
//   }
  
//   /*
//    * Vacate the GPIO semaphore gathered
//    */
//   timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].s.vacate();
  
//  return 0;  
// }

// /**
// * Reads the current input capture register value for the specified channel.
// *
// * @param channel	Which channel to read the IC value from.
// * @return The IC register value.
// */
// template <typename T>
// T timer_imp::get_icR(tc_ic_channel channel)
// {
//   /* Switch which channel to read */
//   switch (channel)
//   {
//     case TC_IC_A:
//     {
//       return (_SFR_MEM16(registerTable.ICR_address));
//       break;
//     }
//   }
    
//  return 0;
// }

// /** 
// * Obtains the peripheral pin which the Timer/Counter requires.
// *
// * @param  address	The address of the GPIO pin required.
// * @return Pointer to a GPIO pin implementation.
// */
// // gpio_pin* timer_imp::grabPeripheralPin(gpio_pin_address address)
// // {
// //   return (&(gpio_pin::grab(address)));
// // }

// /**
// * Starts Timer 0 by manipulating the TCCR0A & TCCR0B registers
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @param  table		Table register addresses for particular Timer/Counter.
// * @return 0 if valid prescalar and clock are supplied, otherwise -1
// */
// int8_t start_timer0(timer_rate rate, Register_address_table *table)
// {
//   /*Edit the registers according to whether an internal/external clock is selected
//    * and which prescaler is chosen*/
//   switch(rate.src)
//   {
//     case INT:	//internal clock
//     {
//       switch(rate.pre)
//       {
// 	case TC_PRE_1:	//Prescalar = 1
// 	{
// 	  _SFR_IO8(table.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
// 	  _SFR_IO8(table.TCCRB_address) |= (1 << CS0_BIT);	  
// 	  break;
// 	}
// 	case TC_PRE_8:	//Prescalar = 8
// 	{
// 	  _SFR_IO8(table.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_IO8(table.TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_64:	//Prescalar = 64
// 	{
//   	  _SFR_IO8(table.TCCRB_address) &= ~(1 << CS2_BIT);
// 	  _SFR_IO8(table.TCCRB_address) |= ((1 << CS1_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	case TC_PRE_256:	//Prescalar = 256
// 	{
//   	  _SFR_IO8(table.TCCRB_address) &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_IO8(table.TCCRB_address) |= ((1 << CS2_BIT));
// 	  break;
// 	}
// 	case TC_PRE_1024:	//Prescalar = 1024
// 	{
//   	  _SFR_IO8(table.TCCRB_address) &= ~(1 << CS1_BIT);
// 	  _SFR_IO8(table.TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	default: /*Not a valid prescalar*/
// 	  return -1;
//       }
//       break;
//     }
//     /* If external clocks are ever an option add it here*/
//   }
//   return 0;	/*Valid clock and prescalar*/
// }

// /**
// * Starts the 16-bit Timer/Counters by manipulating the TCCR0B registers
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @param  table		Table register addresses for particular Timer/Counter.
// * @return 0 if valid prescalar and clock are supplied, otherwise -1
// */
// int8_t start_16bit_timer(timer_rate rate, Register_address_table *table)
// {
//   /*Edit the registers according to whether an internal/external clock is selected
//    * and which prescaler is chosen*/
//   switch(rate.src)
//   {
//     case INT:	//internal clock
//     {
//       switch(rate.pre)
//       {
// 	case TC_PRE_1:	//Prescalar = 1
// 	{
//  	  _SFR_MEM8(table.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
// 	  _SFR_MEM8(table.TCCRB_address) |= (1 << CS0_BIT);
// 	  break;
// 	}
// 	case TC_PRE_8:	//Prescalar = 8
// 	{
//  	  _SFR_MEM8(table.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table.TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_64:	//Prescalar = 64
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= ~(1 << CS2_BIT);
// 	  _SFR_MEM8(table.TCCRB_address) |= ((1 << CS1_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	case TC_PRE_256:	//Prescalar = 256
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table.TCCRB_address) |= ((1 << CS2_BIT));
// 	  break;
// 	}
// 	case TC_PRE_1024:	//Prescalar = 1024
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= ~(1 << CS1_BIT);
// 	  _SFR_MEM8(table.TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
//       default: /*Not a valid prescalar*/
// 	  return -1;
//       }
//       break;
//     }
//     /* TODO: If external clocks are ever an option add it here*/
//   }
//   return 0;	/*Valid clock and prescalar*/
// }

// /**
// * Starts Timer 0 by manipulating the TCCR0A & TCCR0B registers
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @param  table		Table register addresses for particular Timer/Counter.
// * @return 0 if valid prescalar and clock are supplied, otherwise -1
// */
// int8_t start_timer2(timer_rate rate, Register_address_table *table)
// {
//   /*Edit the registers according to whether an internal/external clock is selected
//    * and which prescaler is chosen*/
//   switch(rate.src)
//   {
//     case INT:	//internal clock
//     {
//       switch(rate.pre)
//       {
// 	case TC_PRE_1:	//Prescalar = 1
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
// 	  _SFR_MEM8(table.TCCRB_address) |= (1 << CS0_BIT);
// 	  break;
// 	}
// 	case TC_PRE_8:	//Prescalar = 8
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table.TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_32:	//Prescalar = 32
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= ~(1 << CS2_BIT);
// 	  _SFR_MEM8(table.TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_64:	//Prescalar = 64
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table.TCCRB_address) |= (1 << CS2_BIT);
// 	  break;
// 	}
// 	case TC_PRE_128:	//Prescalar = 128
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= ~(1 << CS1_BIT);
// 	  _SFR_MEM8(table.TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	case TC_PRE_256:	//Prescalar = 256
// 	{
//   	  _SFR_MEM8(table.TCCRB_address) &= ~(1 << CS0_BIT);
// 	  _SFR_MEM8(table.TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS1_BIT));
// 	  break;
// 	}
// 	case TC_PRE_1024:	//Prescalar = 1024
// 	{
//  	  _SFR_MEM8(table.TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS1_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
//       default: /*Not a valid prescalar*/
// 	  return -1;
//       }
//       break;
//     }
//     /* If external clocks are ever an option add it here*/
//   }
//   return 0;	/*Valid clock and prescalar*/
// }

// /**
// * Enables Output Compare operation on 8-bit Timer/Counters.
// * 
// * @param mode			Which mode the OC channel should be set to.
// * @param table			Table of addresses for the particular Timer/Counter registers
// * @return 0 if successful, -1 otherwise.
// */
// int8_t enable_oc_8bit(tc_oc_mode mode, Register_address_table *table)
// {
//   switch(mode)
//   {
//     case OC_NONE:	/* Reset the Timer/Counter to NORMAL mode */
//     {
//       if (table.TCCRA_address > 0x60)
//       {
// 	/* Set the WGMn2:0 bits to 0x00 for NORMAL mode */
// 	_SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
// 	_SFR_MEM8(table.TCCRB_address) &= (~(1 << WGM2_BIT));
//       }
//       else
//       {
// 	/* Set the WGMn2:0 bits to 0x00 for NORMAL mode */
// 	_SFR_IO8(table.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
// 	_SFR_IO8(table.TCCRB_address) &= (~(1 << WGM2_BIT));
//       }
//        /* Disable the output compare interrupt */
//       _SFR_MEM8(table.TIMSK_address) &= ~(1 << OCIEA_BIT);
      
//       break;
//     }	  	  
//     case OC_MODE_1:	/* PWM Phase Correct, where TOP = 0xFF */
//     {
//       if (table.TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x01 for PWM Phase Correct mode, where TOP = 0xFF */
// 	_SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_MEM8(table.TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);	
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x01 for PWM Phase Correct mode, where TOP = 0xFF */
// 	_SFR_IO8(table.TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_IO8(table.TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_IO8(table.TCCRB_address) &= ~(1 << WGM2_BIT);	
//       }
      
//       break;
//     }
//     case OC_MODE_2:	/* Clear timer on compare (CTC) mode, where TOP = OCRnA */
//     {
//       if (table.TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x02 for Clear timer on compare (CTC) mode, where TOP = OCRnA */
// 	_SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM0_BIT);
// 	_SFR_MEM8(table.TCCRA_address) |= (1 << WGM1_BIT);
// 	_SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);	
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x02 for Clear timer on compare (CTC) mode, where TOP = OCRnA */
// 	_SFR_IO8(table.TCCRA_address) &= ~(1 << WGM0_BIT);
// 	_SFR_IO8(table.TCCRA_address) |= (1 << WGM1_BIT);
// 	_SFR_IO8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
//       }
      
//       break;
//     }
//     case OC_MODE_3:	/* Fast PWM mode, where TOP = 0xFF */
//     {
//       if (table.TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x03 for Fast PWM mode, where TOP = 0xFF */
// 	_SFR_MEM8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x03 for Fast PWM mode, where TOP = 0xFF */
// 	_SFR_IO8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_IO8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
//       }
	      
//       break;
//     }
//     /* Mode 4 reserved */
//     case OC_MODE_5:	/* PWM Phase Correct mode, where TOP = OCRnA */
//     {
//       if (table.TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x05 for PWM Phase Correct mode, where TOP = OCRnA */
// 	_SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_MEM8(table.TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_MEM8(table.TCCRB_address) |= (1 << WGM2_BIT);
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x05 for PWM Phase Correct mode, where TOP = OCRnA */
// 	_SFR_IO8(table.TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_IO8(table.TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_IO8(table.TCCRB_address) |= (1 << WGM2_BIT);
//       }
	      
//       break;
//     }
//     /* Mode 6 reserved */
//     case OC_MODE_7:	/* Fast PWM mode, where TOP = OCRnA */
//     {
//       if (table.TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x07 for Fast PWM mode, where TOP = OCRnA */
// 	_SFR_MEM8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_MEM8(table.TCCRB_address) |= (1 << WGM2_BIT);
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x07 for Fast PWM mode, where TOP = OCRnA */
// 	_SFR_IO8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_IO8(table.TCCRB_address) |= (1 << WGM2_BIT);
//       }
	      
//       break;
//     }
//     default:	/* To handle all other modes not included in the 8-bit timers */
//       return -1;
//       break;
    
//     /* More modes in here if necessary */
//   }

// return 0;

// }

// /**
// * Enables Output Compare operation on 8-bit Timer/Counters.
// * 
// * @param mode			Which mode the OC channel should be set to.
// * @param table			Table of addresses for the particular Timer/Counter registers
// * @return 0 if successful, -1 otherwise.
// */
// int8_t enable_oc_16bit(tc_oc_mode mode, Register_address_table *table)
// {  
//   /* Switch the process of enabling output compare mode depending on which mode is chosen and
//   * provided to function.
//   */
//   switch(mode)
//   {
//   case OC_NONE:
//   {
//     /* Reset the timer counter mode back to NORMAL */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(table.TCCRB_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
//     /* Disable the output compare operation */
//     _SFR_MEM8(table.TIMSK_address) &= ~(1 << OCIEA_BIT);
//     /* Disconnect the output pin to allow for normal operation */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << COMA1_BIT) & ~(1 << COMA0_BIT));
//     break;
//   }
//   case OC_MODE_1:	/* PWM, Phase Correct, 8-bit */
//   {
//     /* Set WGMn3:0 bits to 0x01 for Phase Correct mode with TOP = 0x00FF (8-bit) */
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM0_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT) & ~(1 << WGM1_BIT));
    	    
//     break;
//   }
//   case OC_MODE_2:	/* PWM, Phase Correct, 9-bit */
//   {
//     /* Set WGMn3:0 bits to 0x02 for Phase Correct mode with TOP = 0x01FF (9-bit) */
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM1_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT) & ~(1 << WGM0_BIT));
    	    
//     break;
//   }
//   case OC_MODE_3:	/* PWM, Phase Correct, 10-bit */
//   {
//     /* Set WGMn3:0 bits to 0x03 for Phase Correct mode with TOP = 0x03FF (10-bit) */
//     _SFR_MEM8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
    	    
//     break;
//   }
//   case OC_MODE_4:	/* Clear timer on Compare (CTC) mode where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x04 for CTC mode where TOP = OCRnA */
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     /* TODO: Move this to the enable_oc_interrupt()! Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
//     _SFR_MEM8(table.TIMSK_address) |= (1 << OCIEA_BIT);
	    
//     break;
//   }
//   case OC_MODE_5:	/* Fast PWM, 8-bit */
//   {
//     /* Set WGMn3:0 bits to 0x05 for Fast PWM mode where TOP = 0x00FF (8-bit) */
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM0_BIT);
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM1_BIT);
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     break;
//   }
//   case OC_MODE_6:	/* Fast PWM, 9-bit */
//   {
//     /* Set WGMn3:0 bits to 0x06 for Fast PWM mode where TOP = 0x01FF (9-bit) */
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM1_BIT);
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM0_BIT);
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     break;
//   }
//   case OC_MODE_7:	/* Fast PWM, 10-bit */
//   {
//     /* Set WGMn3:0 bits to 0x07 for Fast PWM mode where TOP = 0x03FF (10-bit) */
//     _SFR_MEM8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     break;
//   }
//   case OC_MODE_8:	/* PWM, Phase & Frequency Correct where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x08 for PWM, Phase & Frequency Correct mode where TOP = ICRn */
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM3_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_9:	/* PWM, Phase & Frequency Correct where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x09 for PWM, Phase & Frequency Correct mode where TOP = OCRnA */
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM3_BIT);
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM0_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM1_BIT);
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_10:	/* PWM, Phase Correct where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x10 for PWM, Phase Correct mode where TOP = ICRn */
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM3_BIT);
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM1_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= ~(1 << WGM0_BIT);
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_11:	/* PWM, Phase Correct where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x11 for PWM, Phase Correct mode where TOP = OCRnA */
//     _SFR_MEM8(table.TCCRB_address) |= (1 << WGM3_BIT);
//     _SFR_MEM8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_12:	/* Clear timer on Compare (CTC) mode where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x12 for CTC mode where TOP = ICRn */
//     _SFR_MEM8(table.TCCRB_address) |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
    
//     break;
//   }
//   case OC_MODE_13:	/* Reserved */
//   {
//     /* Reserved */
    
//     break;
//   }
//   case OC_MODE_14:	/* Fast PWM mode, where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x14 for Fast PWM mode, where TOP = ICRn */
//     _SFR_MEM8(table.TCCRB_address) |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
//     _SFR_MEM8(table.TCCRA_address) |= (1 << WGM1_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table.TCCRA_address) &= (1 << WGM0_BIT);
    
//     break;
//   }
//   case OC_MODE_15:	/* Fast PWM mode, where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x15 for Fast PWM mode, where TOP = OCRnA */
//     _SFR_MEM8(table.TCCRB_address) |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
//     _SFR_MEM8(table.TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
    
//     break;
//   }
//   /* More modes in here if necessary */	
//   }
  
//   return 0;
// }


// /** Declare the ISRptrs
//  * 
//  * Each timer interrupt type is tied to a relevant interrupt vector. These are associated
//  * with the user ISRs by way of the function pointer array timerInterrupts[]. Here the
//  * ISRs are declared and the user ISR is called if the appropriate element of the function
//  * pointer array is non NULL.
//  */

// ISR(TIMER0_COMPA_vect)
// {
//   if (timerInterrupts[TIMER0_COMPA_int])
//     timerInterrupts[TIMER0_COMPA_int]();
// }

// ISR(TIMER0_COMPB_vect)
// {
//   if (timerInterrupts[TIMER0_COMPB_int])
//     timerInterrupts[TIMER0_COMPB_int]();
// }

// ISR(TIMER0_OVF_vect)
// {
//   if (timerInterrupts[TIMER0_OVF_int])
//     timerInterrupts[TIMER0_OVF_int]();
// }

// ISR(TIMER1_CAPT_vect)
// {
//   if (timerInterrupts[TIMER1_CAPT_int])
//     timerInterrupts[TIMER1_CAPT_int]();
// }

// ISR(TIMER1_COMPA_vect)
// {
//   if (timerInterrupts[TIMER1_COMPA_int])
//     timerInterrupts[TIMER1_COMPA_int]();
// }

// ISR(TIMER1_COMPB_vect)
// {
//   if (timerInterrupts[TIMER1_COMPB_int])
//     timerInterrupts[TIMER1_COMPB_int]();
// }

// ISR(TIMER1_COMPC_vect)
// {
//   if (timerInterrupts[TIMER1_COMPC_int])
//     timerInterrupts[TIMER1_COMPC_int]();
// }

// ISR(TIMER1_OVF_vect)
// {
//   if (timerInterrupts[TIMER1_OVF_int])
//     timerInterrupts[TIMER1_OVF_int]();
// }

// /*
//  * To prevent TIMER2_COMPA_vect being referenced by Free RTOS too; exclude the 
//  * reference here if FREE_RTOS is defined
//  */
// #ifndef FREE_RTOS_INC
// ISR(TIMER2_COMPA_vect)
// {
//   if (timerInterrupts[TIMER2_COMPA_int])
//     timerInterrupts[TIMER2_COMPA_int]();
// }
// #endif

// ISR(TIMER2_COMPB_vect)
// {
//   if (timerInterrupts[TIMER2_COMPB_int])
//     timerInterrupts[TIMER2_COMPB_int]();
// }

// ISR(TIMER2_OVF_vect)
// {
//   if (timerInterrupts[TIMER2_OVF_int])
//     timerInterrupts[TIMER2_OVF_int]();
// }

// ISR(TIMER3_CAPT_vect)
// {
//   if (timerInterrupts[TIMER3_CAPT_int])
//     timerInterrupts[TIMER3_CAPT_int]();
// }

// ISR(TIMER3_COMPA_vect)
// {
//   if (timerInterrupts[TIMER3_COMPA_int])
//     timerInterrupts[TIMER3_COMPA_int]();
// }

// ISR(TIMER3_COMPB_vect)
// {
//   if (timerInterrupts[TIMER3_COMPB_int])
//     timerInterrupts[TIMER3_COMPB_int]();
// }

// ISR(TIMER3_COMPC_vect)
// {
//   if (timerInterrupts[TIMER3_COMPC_int])
//     timerInterrupts[TIMER3_COMPC_int]();
// }

// ISR(TIMER3_OVF_vect)
// {
//   if (timerInterrupts[TIMER3_OVF_int])
//     timerInterrupts[TIMER3_OVF_int]();
// }

// ISR(TIMER4_CAPT_vect)
// {
//   if (timerInterrupts[TIMER4_CAPT_int])
//     timerInterrupts[TIMER4_CAPT_int]();
// }

// ISR(TIMER4_COMPA_vect)
// {
//   if (timerInterrupts[TIMER4_COMPA_int])
//     timerInterrupts[TIMER4_COMPA_int]();
// }

// ISR(TIMER4_COMPB_vect)
// {
//   if (timerInterrupts[TIMER4_COMPB_int])
//     timerInterrupts[TIMER4_COMPB_int]();
// }

// ISR(TIMER4_COMPC_vect)
// {
//   if (timerInterrupts[TIMER4_COMPC_int])
//     timerInterrupts[TIMER4_COMPC_int]();
// }

// ISR(TIMER4_OVF_vect)
// {
//   if (timerInterrupts[TIMER4_OVF_int])
//     timerInterrupts[TIMER4_OVF_int]();
// }

// ISR(TIMER5_CAPT_vect)
// {
//   if (timerInterrupts[TIMER5_CAPT_int])
//     timerInterrupts[TIMER5_CAPT_int]();
// }

// ISR(TIMER5_COMPA_vect)
// {
//   if (timerInterrupts[TIMER5_COMPA_int])
//     timerInterrupts[TIMER5_COMPA_int]();
// }

// ISR(TIMER5_COMPB_vect)
// {
//   if (timerInterrupts[TIMER5_COMPB_int])
//     timerInterrupts[TIMER5_COMPB_int]();
// }

// ISR(TIMER5_COMPC_vect)
// {
//   if (timerInterrupts[TIMER5_COMPC_int])
//     timerInterrupts[TIMER5_COMPC_int]();
// }

// ISR(TIMER5_OVF_vect)
// {
//   if (timerInterrupts[TIMER5_OVF_int])
//     timerInterrupts[TIMER5_OVF_int]();
// }

// // ALL DONE.
