//Oh my god. CAN WE PLEASE STOP HAVING SHITTY DESIGNS

//This is a god awful hack. The stm32cube generates all it's unclude that are designed to include the main file !?
//Heirachy guys.

//As we do not use main.h, this is soly included to provide the required includes.
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_rcc.h"

void SystemClock_Config(void);
