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

/// @brief  Possible STM32 system reset causes
typedef enum reset_cause_e
{
    RESET_CAUSE_UNKNOWN = 0,
    RESET_CAUSE_LOW_POWER_RESET,
    RESET_CAUSE_WINDOW_WATCHDOG_RESET,
    RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET,
    RESET_CAUSE_SOFTWARE_RESET,
    RESET_CAUSE_POWER_ON_POWER_DOWN_RESET,
    RESET_CAUSE_EXTERNAL_RESET_PIN_RESET,
    RESET_CAUSE_BROWNOUT_RESET,
} reset_cause_t;

void SystemClock_Config(void);
void Error_Handler(void);
reset_cause_t reset_cause_get(void);
const char * reset_cause_get_name(reset_cause_t reset_cause);


#ifdef __cplusplus
}
#endif
#endif /*__ main_H */
