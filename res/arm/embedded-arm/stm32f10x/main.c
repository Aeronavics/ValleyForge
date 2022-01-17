//Oh my god. CAN WE PLEASE STOP HAVING SHITTY DESIGNS

//This is a god awful hack. The stm32cube generates all it's unclude that are designed to include the main file !?
//Heirachy guys.

//As we do not use main.h, this is soly included to provide the required includes.
#include "main.h"
/*
 * System Clock Configuration
 */
void SystemClock_Config(void)
{
        RCC_OscInitTypeDef RCC_OscInitStruct = {0};
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
        RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

        /** Initializes the CPU, AHB and APB busses clocks
         */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.LSIState = RCC_LSI_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        {
                Error_Handler();
        }
        /** Initializes the CPU, AHB and APB busses clocks
         */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                      |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        {
                Error_Handler();
        }
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        {
                Error_Handler();
        }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void)
{
        /* USER CODE BEGIN Error_Handler */
        /* User can add his own implementation to report the HAL error return state */
        while (1)
        {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
            HAL_Delay(500);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
            HAL_Delay(100);
        }
        /* USER CODE END Error_Handler */
}



/// @brief      Obtain the STM32 system reset cause
/// @param      None
/// @return     The system reset cause
reset_cause_t reset_cause_get(void)
{
    reset_cause_t reset_cause;

    if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))
    {
        reset_cause = RESET_CAUSE_LOW_POWER_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))
    {
        reset_cause = RESET_CAUSE_WINDOW_WATCHDOG_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
    {
        reset_cause = RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST))
    {
        // This reset is induced by calling the ARM CMSIS 
        // `NVIC_SystemReset()` function!
        reset_cause = RESET_CAUSE_SOFTWARE_RESET; 
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))
    {
        reset_cause = RESET_CAUSE_POWER_ON_POWER_DOWN_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))
    {
        reset_cause = RESET_CAUSE_EXTERNAL_RESET_PIN_RESET;
    }
    // Needs to come *after* checking the `RCC_FLAG_PORRST` flag in order to
    // ensure first that the reset cause is NOT a POR/PDR reset. See note
    // below. 
//     else if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST))
//     {
//         reset_cause = RESET_CAUSE_BROWNOUT_RESET;
//     }
    else
    {
        reset_cause = RESET_CAUSE_UNKNOWN;
    }

    // Clear all the reset flags or else they will remain set during future
    // resets until system power is fully removed.
    __HAL_RCC_CLEAR_RESET_FLAGS();

    return reset_cause; 
}

// Note: any of the STM32 Hardware Abstraction Layer (HAL) Reset and Clock
// Controller (RCC) header files, such as 
// "STM32Cube_FW_F7_V1.12.0/Drivers/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_rcc.h",
// "STM32Cube_FW_F2_V1.7.0/Drivers/STM32F2xx_HAL_Driver/Inc/stm32f2xx_hal_rcc.h",
// etc., indicate that the brownout flag, `RCC_FLAG_BORRST`, will be set in
// the event of a "POR/PDR or BOR reset". This means that a Power-On Reset
// (POR), Power-Down Reset (PDR), OR Brownout Reset (BOR) will trip this flag.
// See the doxygen just above their definition for the 
// `__HAL_RCC_GET_FLAG()` macro to see this:
//      "@arg RCC_FLAG_BORRST: POR/PDR or BOR reset." <== indicates the Brownout
//      Reset flag will *also* be set in the event of a POR/PDR. 
// Therefore, you must check the Brownout Reset flag, `RCC_FLAG_BORRST`, *after*
// first checking the `RCC_FLAG_PORRST` flag in order to ensure first that the
// reset cause is NOT a POR/PDR reset.


/// @brief      Obtain the system reset cause as an ASCII-printable name string 
///             from a reset cause type
/// @param[in]  reset_cause     The previously-obtained system reset cause
/// @return     A null-terminated ASCII name string describing the system 
///             reset cause
const char * reset_cause_get_name(reset_cause_t reset_cause)
{
    const char * reset_cause_name = "TBD";

    switch (reset_cause)
    {
        case RESET_CAUSE_UNKNOWN:
            reset_cause_name = "UNKNOWN";
            break;
        case RESET_CAUSE_LOW_POWER_RESET:
            reset_cause_name = "LOW_POWER_RESET";
            break;
        case RESET_CAUSE_WINDOW_WATCHDOG_RESET:
            reset_cause_name = "WINDOW_WATCHDOG_RESET";
            break;
        case RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET:
            reset_cause_name = "INDEPENDENT_WATCHDOG_RESET";
            break;
        case RESET_CAUSE_SOFTWARE_RESET:
            reset_cause_name = "SOFTWARE_RESET";
            break;
        case RESET_CAUSE_POWER_ON_POWER_DOWN_RESET:
            reset_cause_name = "POWER-ON_RESET (POR) / POWER-DOWN_RESET (PDR)";
            break;
        case RESET_CAUSE_EXTERNAL_RESET_PIN_RESET:
            reset_cause_name = "EXTERNAL_RESET_PIN_RESET";
            break;
        case RESET_CAUSE_BROWNOUT_RESET:
            reset_cause_name = "BROWNOUT_RESET (BOR)";
            break;
    }

    return reset_cause_name;
}

// // void Reset_Handler(void) {}
// // void NMI_Handler(void) {}
// // void HardFault_Handler(void) {}
// // void MemManage_Handler(void) {}
// // void BusFault_Handler(void) {}
// // void UsageFault_Handler(void) {}
// // void SVC_Handler(void) {}
// // void DebugMon_Handler(void) {}
// // void PendSV_Handler(void) {}
// // void SysTick_Handler(void) {}
// void WWDG_IRQHandler(void) {}
// // void PVD_IRQHandler(void) {}
// void TAMPER_IRQHandler(void) {}
// void RTC_IRQHandler(void) {}
// // void FLASH_IRQHandler(void) {}
// // void RCC_IRQHandler(void) {}
// void EXTI0_IRQHandler(void) {}
// void EXTI1_IRQHandler(void) {}
// void EXTI2_IRQHandler(void) {}
// void EXTI3_IRQHandler(void) {}
// void EXTI4_IRQHandler(void) {}
// void DMA1_Channel1_IRQHandler(void) {}
// void DMA1_Channel2_IRQHandler(void) {}
// // void DMA1_Channel3_IRQHandler(void) {}
// // void DMA1_Channel4_IRQHandler(void) {}
// // void DMA1_Channel5_IRQHandler(void) {}
// // void DMA1_Channel6_IRQHandler(void) {}
// // void DMA1_Channel7_IRQHandler(void) {}
// // void ADC1_2_IRQHandler(void) {}
// void USB_HP_CAN1_TX_IRQHandler(void) {}
// void USB_LP_CAN1_RX0_IRQHandler(void) {}
// void CAN1_RX1_IRQHandler(void) {}
// void CAN1_SCE_IRQHandler(void) {}
// void EXTI9_5_IRQHandler(void) {}
// // void TIM1_BRK_IRQHandler(void) {}
// // void TIM1_UP_IRQHandler(void) {}
// // void TIM1_TRG_COM_IRQHandler(void) {}
// // void TIM1_CC_IRQHandler(void) {}
// // void TIM2_IRQHandler(void) {}
// // void TIM3_IRQHandler(void) {}
// void TIM4_IRQHandler(void) {}
// // void I2C1_EV_IRQHandler(void) {}
// // void I2C1_ER_IRQHandler(void) {}
// void I2C2_EV_IRQHandler(void) {}
// void I2C2_ER_IRQHandler(void) {}
// // void SPI1_IRQHandler(void) {}
// void SPI2_IRQHandler(void) {}
// // void USART1_IRQHandler(void) {}
// // void USART2_IRQHandler(void) {}
// void USART3_IRQHandler(void) {}
// void EXTI15_10_IRQHandler(void) {}
// void RTC_Alarm_IRQHandler(void) {}
// void USBWakeUp_IRQHandler(void) {}
// void TIM8_BRK_IRQHandler(void) {}
// void TIM8_UP_IRQHandler(void) {}
// void TIM8_TRG_COM_IRQHandler(void) {}
// void TIM8_CC_IRQHandler(void) {}
// void ADC3_IRQHandler(void) {}
// void FSMC_IRQHandler(void) {}
// void SDIO_IRQHandler(void) {}
// void TIM5_IRQHandler(void) {}
// void SPI3_IRQHandler(void) {}
// // void UART4_IRQHandler(void) {}
// // void UART5_IRQHandler(void) {}
// // void TIM6_IRQHandler(void) {}
// void TIM7_IRQHandler(void) {}
// void DMA2_Channel1_IRQHandler(void) {}
// void DMA2_Channel2_IRQHandler(void) {}
// // void DMA2_Channel3_IRQHandler(void) {}
// // void DMA2_Channel4_5_IRQHandler(void) {}