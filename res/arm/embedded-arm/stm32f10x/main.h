//Oh my god. CAN WE PLEASE STOP HAVING SHITTY DESIGNS

//This is a god awful hack. The stm32cube generates all it's unclude that are designed to include the main file !?
//Heirachy guys.

#ifndef __main_H
#define __main_H
#ifdef __cplusplus
 extern "C" {
#endif
//As we do not use main.h, this is soly included to provide the required includes.
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_rcc.h"
//#include "stm32f1xx_hal_conf.h"

#ifdef USE_FULL_LL_DRIVER
    #include "stm32f1xx_ll_gpio.h"
    #include "stm32f1xx_ll_bus.h"
#endif

void SystemClock_Config(void);
void Error_Handler(void);

#ifdef __cplusplus
}
#endif
#endif /*__ main_H */
