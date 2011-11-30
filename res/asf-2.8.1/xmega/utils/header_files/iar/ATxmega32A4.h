


/*
 --------------------------------------------------------------------------
 --             - ATxmega32A4.h -
 --
 --     This file declares the internal register addresses for ATxmega32A4.
 --
 --     Used with IAR System's iccAVR and aAVR.
 --
 --     Copyright Atmel Corporation 2008. All rights reserved.
 --
 --------------------------------------------------------------------------
*/

#include <Atmel/iomacro_xmega.h>

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#pragma language=save
#pragma language=extended
#endif


#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr whith processor option -v3
#endif /* TID_GUARD(3) */



#if !defined(__ATxmega32A4_H) && defined(__IAR_SYSTEMS_ICC__)

/*
 ---------------------------------------------------------------------------
 ----------------------------------------------------------------------------
 --
 -- Device signature                           
 --
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
*/

#define SIGNATURE_000 0x1E
#define SIGNATURE_001 0x95
#define SIGNATURE_002 0x41


/*
 ---------------------------------------------------------------------------
 ----------------------------------------------------------------------------
 --
 -- IO module structures.                           
 --
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
*/


/** @addtogroup xocd On-Chip Debug System
 *  @{
 */
	
/// On-Chip Debug System
typedef struct OCD_struct {
	register8_t OCDR0; ///< OCD Register 0
	register8_t OCDR1; ///< OCD Register 1
} OCD_t;
	
/** @} */
	
/** @addtogroup clk Clock System
 *  @{
 */
	
/// Clock System
typedef struct CLK_struct {
	register8_t CTRL; ///< Control Register
	register8_t PSCTRL; ///< Prescaler Control Register
	register8_t LOCK; ///< Lock register
	register8_t RTCCTRL; ///< RTC Control Register
} CLK_t;
	
/// Power Reduction
typedef struct PR_struct {
	register8_t PRGEN; ///< General Power Reduction
	register8_t PRPA; ///< Power Reduction Port A
	register8_t PRPB; ///< Power Reduction Port B
	register8_t PRPC; ///< Power Reduction Port C
	register8_t PRPD; ///< Power Reduction Port D
	register8_t PRPE; ///< Power Reduction Port E
	register8_t PRPF; ///< Power Reduction Port F
} PR_t;
	
/** @} */
	
/** @addtogroup sleep Sleep Controller
 *  @{
 */
	
/// Sleep Controller
typedef struct SLEEP_struct {
	register8_t CTRL; ///< Control Register
} SLEEP_t;
	
/** @} */
	
/** @addtogroup osc Oscillator
 *  @{
 */
	
/// Oscillator
typedef struct OSC_struct {
	register8_t CTRL; ///< Control Register
	register8_t STATUS; ///< Status Register
	register8_t XOSCCTRL; ///< External Oscillator Control Register
	register8_t XOSCFAIL; ///< External Oscillator Failure Detection Register
	register8_t RC32KCAL; ///< 32kHz Internal Oscillator Calibration Register
	register8_t PLLCTRL; ///< PLL Control REgister
	register8_t DFLLCTRL; ///< DFLL Control Register
} OSC_t;
	
/** @} */
	
/** @addtogroup dfll DFLL
 *  @{
 */
	
/// DFLL
typedef struct DFLL_struct {
	register8_t CTRL; ///< Control Register
	register8_t reserved_0x01; ///< reserved
	register8_t CALA; ///< Calibration Register A
	register8_t CALB; ///< Calibration Register B
	register8_t COMP0; ///< Oscillator Compare Register 0
	register8_t COMP1; ///< Oscillator Compare Register 1
	register8_t COMP2; ///< Oscillator Compare Register 2
	register8_t reserved_0x07; ///< reserved
} DFLL_t;
	
/** @} */
	
/** @addtogroup rst Reset
 *  @{
 */
	
/// Reset
typedef struct RST_struct {
	register8_t STATUS; ///< Status Register
	register8_t CTRL; ///< Control Register
} RST_t;
	
/** @} */
	
/** @addtogroup wdt Watch-Dog Timer
 *  @{
 */
	
/// Watch-Dog Timer
typedef struct WDT_struct {
	register8_t CTRL; ///< Control
	register8_t WINCTRL; ///< Windowed Mode Control
	register8_t STATUS; ///< Status
} WDT_t;
	
/** @} */
	
/** @addtogroup mcu MCU Control
 *  @{
 */
	
/// MCU Control
typedef struct MCU_struct {
	register8_t DEVID0; ///< Device ID byte 0
	register8_t DEVID1; ///< Device ID byte 1
	register8_t DEVID2; ///< Device ID byte 2
	register8_t REVID; ///< Revision ID
	register8_t JTAGUID; ///< JTAG User ID
	register8_t reserved_0x05; ///< reserved
	register8_t MCUCR; ///< MCU Control
	register8_t reserved_0x07; ///< reserved
	register8_t EVSYSLOCK; ///< Event System Lock
	register8_t AWEXLOCK; ///< AWEX Lock
	register8_t reserved_0x0A; ///< reserved
	register8_t reserved_0x0B; ///< reserved
} MCU_t;
	
/** @} */
	
/** @addtogroup pmic Programmable Multi-level Interrupt Controller
 *  @{
 */
	
/// Programmable Multi-level Interrupt Controller
typedef struct PMIC_struct {
	register8_t STATUS; ///< Status Register
	register8_t INTPRI; ///< Interrupt Priority
	register8_t CTRL; ///< Control Register
} PMIC_t;
	
/** @} */
	
/** @addtogroup dma DMA Controller
 *  @{
 */
	
/// DMA Channel
typedef struct DMA_CH_struct {
	register8_t CTRLA; ///< Channel Control
	register8_t CTRLB; ///< Channel Control
	register8_t ADDRCTRL; ///< Address Control
	register8_t TRIGSRC; ///< Channel Trigger Source
	WORDREGISTER(TRFCNT); ///< Channel Block Transfer Count
	register8_t REPCNT; ///< Channel Repeat Count
	register8_t reserved_0x07; ///< reserved
	register8_t SRCADDR0; ///< Channel Source Address 0
	register8_t SRCADDR1; ///< Channel Source Address 1
	register8_t SRCADDR2; ///< Channel Source Address 2
	register8_t reserved_0x0B; ///< reserved
	register8_t DESTADDR0; ///< Channel Destination Address 0
	register8_t DESTADDR1; ///< Channel Destination Address 1
	register8_t DESTADDR2; ///< Channel Destination Address 2
	register8_t reserved_0x0F; ///< reserved
} DMA_CH_t;
	
/// DMA Controller
typedef struct DMA_struct {
	register8_t CTRL; ///< Control
	register8_t reserved_0x01; ///< reserved
	register8_t reserved_0x02; ///< reserved
	register8_t INTFLAGS; ///< Transfer Interrupt Status
	register8_t STATUS; ///< Status
	register8_t reserved_0x05; ///< reserved
	WORDREGISTER(TEMP); ///< Temporary Register For 16/24-bit Access
	register8_t reserved_0x08; ///< reserved
	register8_t reserved_0x09; ///< reserved
	register8_t reserved_0x0A; ///< reserved
	register8_t reserved_0x0B; ///< reserved
	register8_t reserved_0x0C; ///< reserved
	register8_t reserved_0x0D; ///< reserved
	register8_t reserved_0x0E; ///< reserved
	register8_t reserved_0x0F; ///< reserved
	DMA_CH_t CH0; ///< DMA Channel 0
	DMA_CH_t CH1; ///< DMA Channel 1
	DMA_CH_t CH2; ///< DMA Channel 2
	DMA_CH_t CH3; ///< DMA Channel 3
} DMA_t;
	
/** @} */
	
/** @addtogroup evsys Event System
 *  @{
 */
	
/// Event System
typedef struct EVSYS_struct {
	register8_t CH0MUX; ///< Event Channel 0 Multiplexer
	register8_t CH1MUX; ///< Event Channel 1 Multiplexer
	register8_t CH2MUX; ///< Event Channel 2 Multiplexer
	register8_t CH3MUX; ///< Event Channel 3 Multiplexer
	register8_t CH4MUX; ///< Event Channel 4 Multiplexer
	register8_t CH5MUX; ///< Event Channel 5 Multiplexer
	register8_t CH6MUX; ///< Event Channel 6 Multiplexer
	register8_t CH7MUX; ///< Event Channel 7 Multiplexer
	register8_t CH0CTRL; ///< Channel 0 Control Register
	register8_t CH1CTRL; ///< Channel 1 Control Register
	register8_t CH2CTRL; ///< Channel 2 Control Register
	register8_t CH3CTRL; ///< Channel 3 Control Register
	register8_t CH4CTRL; ///< Channel 4 Control Register
	register8_t CH5CTRL; ///< Channel 5 Control Register
	register8_t CH6CTRL; ///< Channel 6 Control Register
	register8_t CH7CTRL; ///< Channel 7 Control Register
	register8_t STROBE; ///< Event Strobe
	register8_t DATA; ///< Event Data
} EVSYS_t;
	
/** @} */
	
/** @addtogroup nvm Non Volatile Memory Controller
 *  @{
 */
	
/// Non-volatile Memory Controller
typedef struct NVM_struct {
	register8_t ADDR0; ///< Address Register 0
	register8_t ADDR1; ///< Address Register 1
	register8_t ADDR2; ///< Address Register 2
	register8_t reserved_0x03; ///< reserved
	register8_t DATA0; ///< Data Register 0
	register8_t DATA1; ///< Data Register 1
	register8_t DATA2; ///< Data Register 2
	register8_t reserved_0x07; ///< reserved
	register8_t reserved_0x08; ///< reserved
	register8_t reserved_0x09; ///< reserved
	register8_t CMD; ///< Command
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t INTCTRL; ///< Interrupt Control
	register8_t reserved_0x0E; ///< reserved
	register8_t STATUS; ///< Status
	register8_t LOCKBITS; ///< Lock Bits
} NVM_t;
	
/// Lock Bits
typedef struct NVM_LOCKBITS_struct {
	register8_t LOCKBITS; ///< Lock Bits
} NVM_LOCKBITS_t;
	
/// Fuses
typedef struct NVM_FUSES_struct {
	register8_t FUSEBYTE0; ///< User ID
	register8_t FUSEBYTE1; ///< Watchdog Configuration
	register8_t FUSEBYTE2; ///< Reset Configuration
	register8_t reserved_0x03; ///< reserved
	register8_t FUSEBYTE4; ///< Start-up Configuration
	register8_t FUSEBYTE5; ///< EESAVE and BOD Level
} NVM_FUSES_t;
	
/// Production Signatures
typedef struct NVM_PROD_SIGNATURES_struct {
	register8_t RCOSC2M; ///< RCOSC 2MHz Calibration Value
	register8_t reserved_0x01; ///< reserved
	register8_t RCOSC32K; ///< RCOSC 32kHz Calibration Value
	register8_t RCOSC32M; ///< RCOSC 32MHz Calibration Value
	register8_t reserved_0x04; ///< reserved
	register8_t reserved_0x05; ///< reserved
	register8_t reserved_0x06; ///< reserved
	register8_t reserved_0x07; ///< reserved
	register8_t LOTNUM0; ///< Lot Number Byte 0, ASCII
	register8_t LOTNUM1; ///< Lot Number Byte 1, ASCII
	register8_t LOTNUM2; ///< Lot Number Byte 2, ASCII
	register8_t LOTNUM3; ///< Lot Number Byte 3, ASCII
	register8_t LOTNUM4; ///< Lot Number Byte 4, ASCII
	register8_t LOTNUM5; ///< Lot Number Byte 5, ASCII
	register8_t reserved_0x0E; ///< reserved
	register8_t reserved_0x0F; ///< reserved
	register8_t WAFNUM; ///< Wafer Number
	register8_t reserved_0x11; ///< reserved
	register8_t COORDX0; ///< Wafer Coordinate X Byte 0
	register8_t COORDX1; ///< Wafer Coordinate X Byte 1
	register8_t COORDY0; ///< Wafer Coordinate Y Byte 0
	register8_t COORDY1; ///< Wafer Coordinate Y Byte 1
	register8_t reserved_0x16; ///< reserved
	register8_t reserved_0x17; ///< reserved
	register8_t reserved_0x18; ///< reserved
	register8_t reserved_0x19; ///< reserved
	register8_t reserved_0x1A; ///< reserved
	register8_t reserved_0x1B; ///< reserved
	register8_t reserved_0x1C; ///< reserved
	register8_t reserved_0x1D; ///< reserved
	register8_t reserved_0x1E; ///< reserved
	register8_t reserved_0x1F; ///< reserved
	register8_t ADCACAL0; ///< ADCA Calibration Byte 0
	register8_t ADCACAL1; ///< ADCA Calibration Byte 1
	register8_t reserved_0x22; ///< reserved
	register8_t reserved_0x23; ///< reserved
	register8_t ADCBCAL0; ///< ADCB Calibration Byte 0
	register8_t ADCBCAL1; ///< ADCB Calibration Byte 1
	register8_t reserved_0x26; ///< reserved
	register8_t reserved_0x27; ///< reserved
	register8_t reserved_0x28; ///< reserved
	register8_t reserved_0x29; ///< reserved
	register8_t reserved_0x2A; ///< reserved
	register8_t reserved_0x2B; ///< reserved
	register8_t reserved_0x2C; ///< reserved
	register8_t reserved_0x2D; ///< reserved
	register8_t TEMPSENSE0; ///< Temperature Sensor Calibration Byte 0
	register8_t TEMPSENSE1; ///< Temperature Sensor Calibration Byte 0
	register8_t reserved_0x30; ///< reserved
	register8_t reserved_0x31; ///< reserved
	register8_t reserved_0x32; ///< reserved
	register8_t reserved_0x33; ///< reserved
	register8_t reserved_0x34; ///< reserved
	register8_t reserved_0x35; ///< reserved
	register8_t reserved_0x36; ///< reserved
	register8_t reserved_0x37; ///< reserved
	register8_t reserved_0x38; ///< reserved
	register8_t reserved_0x39; ///< reserved
	register8_t reserved_0x3A; ///< reserved
	register8_t reserved_0x3B; ///< reserved
	register8_t reserved_0x3C; ///< reserved
	register8_t reserved_0x3D; ///< reserved
	register8_t reserved_0x3E; ///< reserved
} NVM_PROD_SIGNATURES_t;
	
/** @} */
	
/** @addtogroup ac Analog Comparator
 *  @{
 */
	
/// Analog Comparator
typedef struct AC_struct {
	register8_t AC0CTRL; ///< Comparator 0 Control
	register8_t AC1CTRL; ///< Comparator 1 Control
	register8_t AC0MUXCTRL; ///< Comparator 0 MUX Control
	register8_t AC1MUXCTRL; ///< Comparator 1 MUX Control
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t WINCTRL; ///< Window Mode Control
	register8_t STATUS; ///< Status
} AC_t;
	
/** @} */
	
/** @addtogroup adc Analog/Digital Converter
 *  @{
 */
	
/// ADC Channel
typedef struct ADC_CH_struct {
	register8_t CTRL; ///< Control Register
	register8_t MUXCTRL; ///< MUX Control
	register8_t INTCTRL; ///< Channel Interrupt Control
	register8_t INTFLAGS; ///< Interrupt Flags
	WORDREGISTER(RES); ///< Channel Result
	register8_t reserved_0x6; ///< reserved
	register8_t reserved_0x7; ///< reserved
} ADC_CH_t;
	
/// Analog-to-Digital Converter
typedef struct ADC_struct {
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t REFCTRL; ///< Reference Control
	register8_t EVCTRL; ///< Event Control
	register8_t PRESCALER; ///< Clock Prescaler
	register8_t reserved_0x05; ///< reserved
	register8_t INTFLAGS; ///< Interrupt Flags
	register8_t TEMP; ///< Temporary register
	register8_t reserved_0x08; ///< reserved
	register8_t reserved_0x09; ///< reserved
	register8_t reserved_0x0A; ///< reserved
	register8_t reserved_0x0B; ///< reserved
	WORDREGISTER(CAL); ///< Calibration Value
	register8_t reserved_0x0E; ///< reserved
	register8_t reserved_0x0F; ///< reserved
	WORDREGISTER(CH0RES); ///< Channel 0 Result
	WORDREGISTER(CH1RES); ///< Channel 1 Result
	WORDREGISTER(CH2RES); ///< Channel 2 Result
	WORDREGISTER(CH3RES); ///< Channel 3 Result
	WORDREGISTER(CMP); ///< Compare Value
	register8_t reserved_0x1A; ///< reserved
	register8_t reserved_0x1B; ///< reserved
	register8_t reserved_0x1C; ///< reserved
	register8_t reserved_0x1D; ///< reserved
	register8_t reserved_0x1E; ///< reserved
	register8_t reserved_0x1F; ///< reserved
	ADC_CH_t CH0; ///< ADC Channel 0
	ADC_CH_t CH1; ///< ADC Channel 1
	ADC_CH_t CH2; ///< ADC Channel 2
	ADC_CH_t CH3; ///< ADC Channel 3
} ADC_t;
	
/** @} */
	
/** @addtogroup dac Digital/Analog Converter
 *  @{
 */
	
/// Digital-to-Analog Converter
typedef struct DAC_struct {
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t CTRLC; ///< Control Register C
	register8_t EVCTRL; ///< Event Input Control
	register8_t TIMCTRL; ///< Timing Control
	register8_t STATUS; ///< Status
	register8_t reserved_0x06; ///< reserved
	register8_t reserved_0x07; ///< reserved
	register8_t GAINCAL; ///< Gain Calibration
	register8_t OFFSETCAL; ///< Offset Calibration
	register8_t reserved_0x0A; ///< reserved
	register8_t reserved_0x0B; ///< reserved
	register8_t reserved_0x0C; ///< reserved
	register8_t reserved_0x0D; ///< reserved
	register8_t reserved_0x0E; ///< reserved
	register8_t reserved_0x0F; ///< reserved
	register8_t reserved_0x10; ///< reserved
	register8_t reserved_0x11; ///< reserved
	register8_t reserved_0x12; ///< reserved
	register8_t reserved_0x13; ///< reserved
	register8_t reserved_0x14; ///< reserved
	register8_t reserved_0x15; ///< reserved
	register8_t reserved_0x16; ///< reserved
	register8_t reserved_0x17; ///< reserved
	WORDREGISTER(CH0DATA); ///< Channel 0 Data
	WORDREGISTER(CH1DATA); ///< Channel 1 Data
} DAC_t;
	
/** @} */
	
/** @addtogroup rtc Real-Time Clounter
 *  @{
 */
	
/// Real-Time Counter
typedef struct RTC_struct {
	register8_t CTRL; ///< Control Register
	register8_t STATUS; ///< Status Register
	register8_t INTCTRL; ///< Interrupt Control Register
	register8_t INTFLAGS; ///< Interrupt Flags
	register8_t TEMP; ///< Temporary register
	register8_t reserved_0x05; ///< reserved
	register8_t reserved_0x06; ///< reserved
	register8_t reserved_0x07; ///< reserved
	WORDREGISTER(CNT); ///< Count Register
	WORDREGISTER(PER); ///< Period Register
	WORDREGISTER(COMP); ///< Compare Register
} RTC_t;
	
/** @} */
	
/** @addtogroup ebi External Bus Interface
 *  @{
 */
	
/// EBI Chip Select Module
typedef struct EBI_CS_struct {
	register8_t CTRLA; ///< Chip Select Control Register A
	register8_t CTRLB; ///< Chip Select Control Register B
	WORDREGISTER(BASEADDR); ///< Chip Select Base Address
} EBI_CS_t;
	
/// External Bus Interface
typedef struct EBI_struct {
	register8_t CTRL; ///< Control
	register8_t SDRAMCTRLA; ///< SDRAM Control Register A
	register8_t reserved_0x02; ///< reserved
	register8_t reserved_0x03; ///< reserved
	WORDREGISTER(REFRESH); ///< SDRAM Refresh Period
	WORDREGISTER(INITDLY); ///< SDRAM Initialization Delay
	register8_t SDRAMCTRLB; ///< SDRAM Control Register B
	register8_t SDRAMCTRLC; ///< SDRAM Control Register C
	register8_t reserved_0x0A; ///< reserved
	register8_t reserved_0x0B; ///< reserved
	register8_t reserved_0x0C; ///< reserved
	register8_t reserved_0x0D; ///< reserved
	register8_t reserved_0x0E; ///< reserved
	register8_t reserved_0x0F; ///< reserved
	EBI_CS_t CS0; ///< Chip Select 0
	EBI_CS_t CS1; ///< Chip Select 1
	EBI_CS_t CS2; ///< Chip Select 2
	EBI_CS_t CS3; ///< Chip Select 3
} EBI_t;
	
/** @} */
	
/** @addtogroup twi Two-Wire Interface
 *  @{
 */
	
/// -- no doc!
typedef struct TWI_MASTER_struct {
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t CTRLC; ///< Control Register C
	register8_t STATUS; ///< Status Register
	register8_t BAUD; ///< Baurd Rate Control Register
	register8_t ADDR; ///< Address Register
	register8_t DATA; ///< Data Register
} TWI_MASTER_t;
	
/// -- no doc!
typedef struct TWI_SLAVE_struct {
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t STATUS; ///< Status Register
	register8_t ADDR; ///< Address Register
	register8_t DATA; ///< Data Register
	register8_t ADDRMASK; ///< Address Mask Register
} TWI_SLAVE_t;
	
/// Two-Wire Interface
typedef struct TWI_struct {
	register8_t CTRL; ///< TWI Common Control Register
	TWI_MASTER_t MASTER; ///< TWI master module
	TWI_SLAVE_t SLAVE; ///< TWI slave module
} TWI_t;
	
/** @} */
	
/** @addtogroup port Port Configuration
 *  @{
 */
	
/// I/O port Configuration
typedef struct PORTCFG_struct {
	register8_t MPCMASK; ///< Multi-pin Configuration Mask
	register8_t reserved_0x01; ///< reserved
	register8_t VPCTRLA; ///< Virtual Port Control Register A
	register8_t VPCTRLB; ///< Virtual Port Control Register B
	register8_t CLKEVOUT; ///< Clock and Event Out Register
} PORTCFG_t;
	
/// Virtual Port
typedef struct VPORT_struct {
	register8_t DIR; ///< I/O Port Data Direction
	register8_t OUT; ///< I/O Port Output
	register8_t IN; ///< I/O Port Input
	register8_t INTFLAGS; ///< Interrupt Flag Register
} VPORT_t;
	
/// I/O Ports
typedef struct PORT_struct {
	register8_t DIR; ///< I/O Port Data Direction
	register8_t DIRSET; ///< I/O Port Data Direction Set
	register8_t DIRCLR; ///< I/O Port Data Direction Clear
	register8_t DIRTGL; ///< I/O Port Data Direction Toggle
	register8_t OUT; ///< I/O Port Output
	register8_t OUTSET; ///< I/O Port Output Set
	register8_t OUTCLR; ///< I/O Port Output Clear
	register8_t OUTTGL; ///< I/O Port Output Toggle
	register8_t IN; ///< I/O port Input
	register8_t INTCTRL; ///< Interrupt Control Register
	register8_t INT0MASK; ///< Port Interrupt 0 Mask
	register8_t INT1MASK; ///< Port Interrupt 1 Mask
	register8_t INTFLAGS; ///< Interrupt Flag Register
	register8_t reserved_0x0D; ///< reserved
	register8_t reserved_0x0E; ///< reserved
	register8_t reserved_0x0F; ///< reserved
	register8_t PIN0CTRL; ///< Pin 0 Control Register
	register8_t PIN1CTRL; ///< Pin 1 Control Register
	register8_t PIN2CTRL; ///< Pin 2 Control Register
	register8_t PIN3CTRL; ///< Pin 3 Control Register
	register8_t PIN4CTRL; ///< Pin 4 Control Register
	register8_t PIN5CTRL; ///< Pin 5 Control Register
	register8_t PIN6CTRL; ///< Pin 6 Control Register
	register8_t PIN7CTRL; ///< Pin 7 Control Register
} PORT_t;
	
/** @} */
	
/** @addtogroup tc 16-bit Timer/Counter With PWM
 *  @{
 */
	
/// 16-bit Timer/Counter 0
typedef struct TC0_struct {
	register8_t CTRLA; ///< Control  Register A
	register8_t CTRLB; ///< Control Register B
	register8_t CTRLC; ///< Control register C
	register8_t CTRLD; ///< Control Register D
	register8_t CTRLE; ///< Control Register E
	register8_t reserved_0x05; ///< reserved
	register8_t INTCTRLA; ///< Interrupt Control Register A
	register8_t INTCTRLB; ///< Interrupt Control Register B
	register8_t CTRLFCLR; ///< Control Register F Clear
	register8_t CTRLFSET; ///< Control Register F Set
	register8_t CTRLGCLR; ///< Control Register G Clear
	register8_t CTRLGSET; ///< Control Register G Set
	register8_t INTFLAGS; ///< Interrupt Flag Register
	register8_t reserved_0x0D; ///< reserved
	register8_t reserved_0x0E; ///< reserved
	register8_t TEMP; ///< Temporary Register For 16-bit Access
	register8_t reserved_0x10; ///< reserved
	register8_t reserved_0x11; ///< reserved
	register8_t reserved_0x12; ///< reserved
	register8_t reserved_0x13; ///< reserved
	register8_t reserved_0x14; ///< reserved
	register8_t reserved_0x15; ///< reserved
	register8_t reserved_0x16; ///< reserved
	register8_t reserved_0x17; ///< reserved
	register8_t reserved_0x18; ///< reserved
	register8_t reserved_0x19; ///< reserved
	register8_t reserved_0x1A; ///< reserved
	register8_t reserved_0x1B; ///< reserved
	register8_t reserved_0x1C; ///< reserved
	register8_t reserved_0x1D; ///< reserved
	register8_t reserved_0x1E; ///< reserved
	register8_t reserved_0x1F; ///< reserved
	WORDREGISTER(CNT); ///< Count
	register8_t reserved_0x22; ///< reserved
	register8_t reserved_0x23; ///< reserved
	register8_t reserved_0x24; ///< reserved
	register8_t reserved_0x25; ///< reserved
	WORDREGISTER(PER); ///< Period
	WORDREGISTER(CCA); ///< Compare or Capture A
	WORDREGISTER(CCB); ///< Compare or Capture B
	WORDREGISTER(CCC); ///< Compare or Capture C
	WORDREGISTER(CCD); ///< Compare or Capture D
	register8_t reserved_0x30; ///< reserved
	register8_t reserved_0x31; ///< reserved
	register8_t reserved_0x32; ///< reserved
	register8_t reserved_0x33; ///< reserved
	register8_t reserved_0x34; ///< reserved
	register8_t reserved_0x35; ///< reserved
	WORDREGISTER(PERBUF); ///< Period Buffer
	WORDREGISTER(CCABUF); ///< Compare Or Capture A Buffer
	WORDREGISTER(CCBBUF); ///< Compare Or Capture B Buffer
	WORDREGISTER(CCCBUF); ///< Compare Or Capture C Buffer
	WORDREGISTER(CCDBUF); ///< Compare Or Capture D Buffer
} TC0_t;
	
/// 16-bit Timer/Counter 1
typedef struct TC1_struct {
	register8_t CTRLA; ///< Control  Register A
	register8_t CTRLB; ///< Control Register B
	register8_t CTRLC; ///< Control register C
	register8_t CTRLD; ///< Control Register D
	register8_t CTRLE; ///< Control Register E
	register8_t reserved_0x05; ///< reserved
	register8_t INTCTRLA; ///< Interrupt Control Register A
	register8_t INTCTRLB; ///< Interrupt Control Register B
	register8_t CTRLFCLR; ///< Control Register F Clear
	register8_t CTRLFSET; ///< Control Register F Set
	register8_t CTRLGCLR; ///< Control Register G Clear
	register8_t CTRLGSET; ///< Control Register G Set
	register8_t INTFLAGS; ///< Interrupt Flag Register
	register8_t reserved_0x0D; ///< reserved
	register8_t reserved_0x0E; ///< reserved
	register8_t TEMP; ///< Temporary Register For 16-bit Access
	register8_t reserved_0x10; ///< reserved
	register8_t reserved_0x11; ///< reserved
	register8_t reserved_0x12; ///< reserved
	register8_t reserved_0x13; ///< reserved
	register8_t reserved_0x14; ///< reserved
	register8_t reserved_0x15; ///< reserved
	register8_t reserved_0x16; ///< reserved
	register8_t reserved_0x17; ///< reserved
	register8_t reserved_0x18; ///< reserved
	register8_t reserved_0x19; ///< reserved
	register8_t reserved_0x1A; ///< reserved
	register8_t reserved_0x1B; ///< reserved
	register8_t reserved_0x1C; ///< reserved
	register8_t reserved_0x1D; ///< reserved
	register8_t reserved_0x1E; ///< reserved
	register8_t reserved_0x1F; ///< reserved
	WORDREGISTER(CNT); ///< Count
	register8_t reserved_0x22; ///< reserved
	register8_t reserved_0x23; ///< reserved
	register8_t reserved_0x24; ///< reserved
	register8_t reserved_0x25; ///< reserved
	WORDREGISTER(PER); ///< Period
	WORDREGISTER(CCA); ///< Compare or Capture A
	WORDREGISTER(CCB); ///< Compare or Capture B
	register8_t reserved_0x2C; ///< reserved
	register8_t reserved_0x2D; ///< reserved
	register8_t reserved_0x2E; ///< reserved
	register8_t reserved_0x2F; ///< reserved
	register8_t reserved_0x30; ///< reserved
	register8_t reserved_0x31; ///< reserved
	register8_t reserved_0x32; ///< reserved
	register8_t reserved_0x33; ///< reserved
	register8_t reserved_0x34; ///< reserved
	register8_t reserved_0x35; ///< reserved
	WORDREGISTER(PERBUF); ///< Period Buffer
	WORDREGISTER(CCABUF); ///< Compare Or Capture A Buffer
	WORDREGISTER(CCBBUF); ///< Compare Or Capture B Buffer
} TC1_t;
	
/// Advanced Waveform Extension
typedef struct AWEX_struct {
	register8_t CTRL; ///< Control Register
	register8_t reserved_0x01; ///< reserved
	register8_t FDEMASK; ///< Fault Detection Event Mask
	register8_t FDCTRL; ///< Fault Detection Control Register
	register8_t STATUS; ///< Status Register
	register8_t reserved_0x05; ///< reserved
	register8_t DTBOTH; ///< Dead Time Both Sides
	register8_t DTBOTHBUF; ///< Dead Time Both Sides Buffer
	register8_t DTLS; ///< Dead Time Low Side
	register8_t DTHS; ///< Dead Time High Side
	register8_t DTLSBUF; ///< Dead Time Low Side Buffer
	register8_t DTHSBUF; ///< Dead Time High Side Buffer
	register8_t OUTOVEN; ///< Output Override Enable
} AWEX_t;
	
/// High-Resolution Extension
typedef struct HIRES_struct {
	register8_t CTRLA; ///< Control Register
} HIRES_t;
	
/** @} */
	
/** @addtogroup usart Universal Asynchronous Receiver-Transmitter
 *  @{
 */
	
/// Universal Synchronous/Asynchronous Receiver/Transmitter
typedef struct USART_struct {
	register8_t DATA; ///< Data Register
	register8_t STATUS; ///< Status Register
	register8_t reserved_0x02; ///< reserved
	register8_t CTRLA; ///< Control Register A
	register8_t CTRLB; ///< Control Register B
	register8_t CTRLC; ///< Control Register C
	register8_t BAUDCTRLA; ///< Baud Rate Control Register A
	register8_t BAUDCTRLB; ///< Baud Rate Control Register B
} USART_t;
	
/** @} */
	
/** @addtogroup spi Serial Peripheral Interface
 *  @{
 */
	
/// Serial Peripheral Interface
typedef struct SPI_struct {
	register8_t CTRL; ///< Control Register
	register8_t INTCTRL; ///< Interrupt Control Register
	register8_t STATUS; ///< Status Register
	register8_t DATA; ///< Data Register
} SPI_t;
	
/** @} */
	
/** @addtogroup ircom IR Communication Module
 *  @{
 */
	
/// IR Communication Module
typedef struct IRCOM_struct {
	register8_t CTRL; ///< Control Register
	register8_t TXPLCTRL; ///< IrDA Transmitter Pulse Length Control Register
	register8_t RXPLCTRL; ///< IrDA Receiver Pulse Length Control Register
} IRCOM_t;
	
/** @} */
	
/** @addtogroup aes AES Module
 *  @{
 */
	
/// AES Module
typedef struct AES_struct {
	register8_t CTRL; ///< AES Control Register
	register8_t STATUS; ///< AES Status Register
	register8_t STATE; ///< AES State Register
	register8_t KEY; ///< AES Key Register
	register8_t INTCTRL; ///< AES Interrupt Control Register
} AES_t;
	
/** @} */
	

#endif // !defined(__ATxmega32A4_H) && defined(__IAR_SYSTEMS_ICC__)



/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */

#if !defined(__ATxmega32A4_H) || defined(__IAR_SYSTEMS_ASM__)

#pragma language=extended


/*
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
 --
 -- IO register group instances.
 -- Here we define the IO module instances and map
 -- them to their respective locations in memory.
 --
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
*/

#if !defined(__IAR_SYSTEMS_ASM__)

/** @addtogroup modules_base Module Base Pointers
 *  @{
 */

#define GPIO0		(*(register8_t *) 0x00)		///< General Purpose IO Register 0
#define GPIO1		(*(register8_t *) 0x01)		///< General Purpose IO Register 1
#define GPIO2		(*(register8_t *) 0x02)		///< General Purpose IO Register 2
#define GPIO3		(*(register8_t *) 0x03)		///< General Purpose IO Register 3
#define GPIO4		(*(register8_t *) 0x04)		///< General Purpose IO Register 4
#define GPIO5		(*(register8_t *) 0x05)		///< General Purpose IO Register 5
#define GPIO6		(*(register8_t *) 0x06)		///< General Purpose IO Register 6
#define GPIO7		(*(register8_t *) 0x07)		///< General Purpose IO Register 7
#define GPIO8		(*(register8_t *) 0x08)		///< General Purpose IO Register 8
#define GPIO9		(*(register8_t *) 0x09)		///< General Purpose IO Register 9
#define GPIOA		(*(register8_t *) 0x0A)		///< General Purpose IO Register 10
#define GPIOB		(*(register8_t *) 0x0B)		///< General Purpose IO Register 11
#define GPIOC		(*(register8_t *) 0x0C)		///< General Purpose IO Register 12
#define GPIOD		(*(register8_t *) 0x0D)		///< General Purpose IO Register 13
#define GPIOE		(*(register8_t *) 0x0E)		///< General Purpose IO Register 14
#define GPIOF		(*(register8_t *) 0x0F)		///< General Purpose IO Register 15

#define CCP   		(*(register8_t *) 0x34)		///< Configuration Change Protection
#define RAMPD		(*(register8_t *) 0x38)		///< Ramp D
#define RAMPX		(*(register8_t *) 0x39)		///< Ramp X
#define RAMPY		(*(register8_t *) 0x3A)		///< Ramp Y
#define RAMPZ		(*(register8_t *) 0x3B)		///< Ramp Z
#define EIND 		(*(register8_t *) 0x3C)		///< Extended Indirect Jump
#define SPL  		(*(register8_t *) 0x3D)		///< Stack Pointer Low
#define SPH  		(*(register8_t *) 0x3E)		///< Stack Pointer High
#define SREG 		(*(register8_t *) 0x3F)		///< Status Register


#define OCD		(*(OCD_t *) 0x002E)		///< On-Chip Debug System
#define CLK		(*(CLK_t *) 0x0040)		///< Clock System
#define SLEEP		(*(SLEEP_t *) 0x0048)		///< Sleep Controller
#define OSC		(*(OSC_t *) 0x0050)		///< Oscillator Control
#define DFLLRC32M		(*(DFLL_t *) 0x0060)		///< DFLL for 32MHz RC Oscillator
#define DFLLRC2M		(*(DFLL_t *) 0x0068)		///< DFLL for 2MHz RC Oscillator
#define PR		(*(PR_t *) 0x0070)		///< Power Reduction
#define RST		(*(RST_t *) 0x0078)		///< Reset Controller
#define WDT		(*(WDT_t *) 0x0080)		///< Watch-Dog Timer
#define MCU		(*(MCU_t *) 0x0090)		///< MCU Control
#define PMIC		(*(PMIC_t *) 0x00A0)		///< Programmable Interrupt Controller
#define DMA		(*(DMA_t *) 0x0100)		///< DMA Controller
#define EVSYS		(*(EVSYS_t *) 0x0180)		///< Event System
#define NVM		(*(NVM_t *) 0x01C0)		///< Non Volatile Memory Controller
#define ACA		(*(AC_t *) 0x0380)		///< Analog Comparator A
#define ADCA		(*(ADC_t *) 0x0200)		///< Analog to Digital Converter A
#define DACB		(*(DAC_t *) 0x0320)		///< Digital to Analog Converter B
#define RTC		(*(RTC_t *) 0x0400)		///< Real-Time Counter
#define TWIC		(*(TWI_t *) 0x480)		///< Two-Wire Interface C
#define TWIE		(*(TWI_t *) 0x4A0)		///< Two-Wire Interface E
#define PORTCFG		(*(PORTCFG_t *) 0x00B0)		///< Port Configuration
#define VPORT0		(*(VPORT_t *) 0x0010)		///< Virtual Port 0
#define VPORT1		(*(VPORT_t *) 0x0014)		///< Virtual Port 1
#define VPORT2		(*(VPORT_t *) 0x0018)		///< Virtual Port 2
#define VPORT3		(*(VPORT_t *) 0x001C)		///< Virtual Port 3
#define PORTA		(*(PORT_t *) 0x0600)		///< Port A
#define PORTB		(*(PORT_t *) 0x0620)		///< Port B
#define PORTC		(*(PORT_t *) 0x0640)		///< Port C
#define PORTD		(*(PORT_t *) 0x0660)		///< Port D
#define PORTE		(*(PORT_t *) 0x0680)		///< Port E
#define PORTR		(*(PORT_t *) 0x07E0)		///< Port R
#define TCC0		(*(TC0_t *) 0x800)		///< Timer/Counter C0
#define TCC1		(*(TC1_t *) 0x840)		///< Timer/Counter C1
#define AWEXC		(*(AWEX_t *) 0x880)		///< Advanced Waveform Extension C
#define HIRESC		(*(HIRES_t *) 0x890)		///< High-Resolution Extension C
#define USARTC0		(*(USART_t *) 0x8A0)		///< Universal Asynchronous Receiver-Transmitter C0
#define USARTC1		(*(USART_t *) 0x8B0)		///< Universal Asynchronous Receiver-Transmitter C1
#define SPIC		(*(SPI_t *) 0x8C0)		///< Serial Peripheral Interface C
#define TCD0		(*(TC0_t *) 0x900)		///< Timer/Counter D0
#define TCD1		(*(TC1_t *) 0x940)		///< Timer/Counter D1
#define HIRESD		(*(HIRES_t *) 0x990)		///< High-Resolution Extension D
#define USARTD0		(*(USART_t *) 0x9A0)		///< Universal Asynchronous Receiver-Transmitter D0
#define USARTD1		(*(USART_t *) 0x9B0)		///< Universal Asynchronous Receiver-Transmitter D1
#define SPID		(*(SPI_t *) 0x9C0)		///< Serial Peripheral Interface D
#define TCE0		(*(TC0_t *) 0xA00)		///< Timer/Counter E0
#define HIRESE		(*(HIRES_t *) 0xA90)		///< High-Resolution Extension E
#define USARTE0		(*(USART_t *) 0xAA0)		///< Universal Asynchronous Receiver-Transmitter E0
#define IRCOM		(*(IRCOM_t *) 0x8F8)		///< IR Communication Module
#define AES		(*(AES_t *) 0x0C0)		///< AES Crypto Module

/** @} */

#endif // !defined(__IAR_SYSTEMS_ASM__)

#if defined(__IAR_SYSTEMS_ASM__)


/*
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
 --
 -- Fully qualified IO register names for use with the assembler
 --
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
*/

/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */


/*
 --------------------------------------------------------------------------
 -- GPIO - General Purpose IO Registers
 --------------------------------------------------------------------------
*/
	
sfrb GPIO0 = 0x0000		///< General Purpose IO Register 0
sfrb GPIO1 = 0x0001		///< General Purpose IO Register 1
sfrb GPIO2 = 0x0002		///< General Purpose IO Register 2
sfrb GPIO3 = 0x0003		///< General Purpose IO Register 3
sfrb GPIO4 = 0x0004		///< General Purpose IO Register 4
sfrb GPIO5 = 0x0005		///< General Purpose IO Register 5
sfrb GPIO6 = 0x0006		///< General Purpose IO Register 6
sfrb GPIO7 = 0x0007		///< General Purpose IO Register 7
sfrb GPIO8 = 0x0008		///< General Purpose IO Register 8
sfrb GPIO9 = 0x0009		///< General Purpose IO Register 9
sfrb GPIOA = 0x000A		///< General Purpose IO Register 10
sfrb GPIOB = 0x000B		///< General Purpose IO Register 11
sfrb GPIOC = 0x000C		///< General Purpose IO Register 12
sfrb GPIOD = 0x000D		///< General Purpose IO Register 13
sfrb GPIOE = 0x000E		///< General Purpose IO Register 14
sfrb GPIOF = 0x000F		///< General Purpose IO Register 15

/*
 ---------------------------------------------------------------------------
 -- CPU - CPU Registers
 ---------------------------------------------------------------------------
*/
	
sfrb CCP = 0x0034		///< Configuration Change Protection
sfrb RAMPD = 0x0038		///< Ramp D
sfrb RAMPX = 0x0039		///< Ramp X
sfrb RAMPY = 0x003A		///< Ramp Y
sfrb RAMPZ = 0x003B		///< Ramp Z
sfrb EIND = 0x003C		///< Extended Indirect Jump
sfrb SPL = 0x003D		///< Stack Pointer Low
sfrb SPH = 0x003E		///< Stack Pointer High
sfrb SREG = 0x003F		///< Status Register



/*
 --------------------------------------------------------------------------
 -- OCD - On-Chip Debug System
 --------------------------------------------------------------------------
*/
	
sfrb OCD_OCDR0 = 0x002E		///< OCD Register 0
sfrb OCD_OCDR1 = 0x002F		///< OCD Register 1

/*
 --------------------------------------------------------------------------
 -- CLK - Clock System
 --------------------------------------------------------------------------
*/
	
sfrb CLK_CTRL = 0x0040		///< Control Register
sfrb CLK_PSCTRL = 0x0041		///< Prescaler Control Register
sfrb CLK_LOCK = 0x0042		///< Lock register
sfrb CLK_RTCCTRL = 0x0043		///< RTC Control Register

/*
 --------------------------------------------------------------------------
 -- SLEEP - Sleep Controller
 --------------------------------------------------------------------------
*/
	
sfrb SLEEP_CTRL = 0x0048		///< Control Register

/*
 --------------------------------------------------------------------------
 -- OSC - Oscillator Control
 --------------------------------------------------------------------------
*/
	
sfrb OSC_CTRL = 0x0050		///< Control Register
sfrb OSC_STATUS = 0x0051		///< Status Register
sfrb OSC_XOSCCTRL = 0x0052		///< External Oscillator Control Register
sfrb OSC_XOSCFAIL = 0x0053		///< External Oscillator Failure Detection Register
sfrb OSC_RC32KCAL = 0x0054		///< 32kHz Internal Oscillator Calibration Register
sfrb OSC_PLLCTRL = 0x0055		///< PLL Control REgister
sfrb OSC_DFLLCTRL = 0x0056		///< DFLL Control Register

/*
 --------------------------------------------------------------------------
 -- DFLLRC32M - DFLL for 32MHz RC Oscillator
 --------------------------------------------------------------------------
*/
	
sfrb DFLLRC32M_CTRL = 0x0060		///< Control Register
sfrb DFLLRC32M_CALA = 0x0062		///< Calibration Register A
sfrb DFLLRC32M_CALB = 0x0063		///< Calibration Register B
sfrb DFLLRC32M_COMP0 = 0x0064		///< Oscillator Compare Register 0
sfrb DFLLRC32M_COMP1 = 0x0065		///< Oscillator Compare Register 1
sfrb DFLLRC32M_COMP2 = 0x0066		///< Oscillator Compare Register 2

/*
 --------------------------------------------------------------------------
 -- DFLLRC2M - DFLL for 2MHz RC Oscillator
 --------------------------------------------------------------------------
*/
	
sfrb DFLLRC2M_CTRL = 0x0068		///< Control Register
sfrb DFLLRC2M_CALA = 0x006A		///< Calibration Register A
sfrb DFLLRC2M_CALB = 0x006B		///< Calibration Register B
sfrb DFLLRC2M_COMP0 = 0x006C		///< Oscillator Compare Register 0
sfrb DFLLRC2M_COMP1 = 0x006D		///< Oscillator Compare Register 1
sfrb DFLLRC2M_COMP2 = 0x006E		///< Oscillator Compare Register 2

/*
 --------------------------------------------------------------------------
 -- PR - Power Reduction
 --------------------------------------------------------------------------
*/
	
sfrb PR_PRGEN = 0x0070		///< General Power Reduction
sfrb PR_PRPA = 0x0071		///< Power Reduction Port A
sfrb PR_PRPB = 0x0072		///< Power Reduction Port B
sfrb PR_PRPC = 0x0073		///< Power Reduction Port C
sfrb PR_PRPD = 0x0074		///< Power Reduction Port D
sfrb PR_PRPE = 0x0075		///< Power Reduction Port E
sfrb PR_PRPF = 0x0076		///< Power Reduction Port F

/*
 --------------------------------------------------------------------------
 -- RST - Reset Controller
 --------------------------------------------------------------------------
*/
	
sfrb RST_STATUS = 0x0078		///< Status Register
sfrb RST_CTRL = 0x0079		///< Control Register

/*
 --------------------------------------------------------------------------
 -- WDT - Watch-Dog Timer
 --------------------------------------------------------------------------
*/
	
sfrb WDT_CTRL = 0x0080		///< Control
sfrb WDT_WINCTRL = 0x0081		///< Windowed Mode Control
sfrb WDT_STATUS = 0x0082		///< Status

/*
 --------------------------------------------------------------------------
 -- MCU - MCU Control
 --------------------------------------------------------------------------
*/
	
sfrb MCU_DEVID0 = 0x0090		///< Device ID byte 0
sfrb MCU_DEVID1 = 0x0091		///< Device ID byte 1
sfrb MCU_DEVID2 = 0x0092		///< Device ID byte 2
sfrb MCU_REVID = 0x0093		///< Revision ID
sfrb MCU_JTAGUID = 0x0094		///< JTAG User ID
sfrb MCU_MCUCR = 0x0096		///< MCU Control
sfrb MCU_EVSYSLOCK = 0x0098		///< Event System Lock
sfrb MCU_AWEXLOCK = 0x0099		///< AWEX Lock

/*
 --------------------------------------------------------------------------
 -- PMIC - Programmable Interrupt Controller
 --------------------------------------------------------------------------
*/
	
sfrb PMIC_STATUS = 0x00A0		///< Status Register
sfrb PMIC_INTPRI = 0x00A1		///< Interrupt Priority
sfrb PMIC_CTRL = 0x00A2		///< Control Register

/*
 --------------------------------------------------------------------------
 -- DMA - DMA Controller
 --------------------------------------------------------------------------
*/
	
sfrb DMA_CTRL = 0x0100		///< Control
sfrb DMA_INTFLAGS = 0x0103		///< Transfer Interrupt Status
sfrb DMA_STATUS = 0x0104		///< Status
sfrb DMA_TEMPL = 0x0106		///< Temporary Register For 16/24-bit Access
sfrb DMA_TEMPH = (0x0106+1)	///< Temporary Register For 16/24-bit Access
sfrb DMA_CH0_CTRLA = 0x0110		///< Channel Control
sfrb DMA_CH0_CTRLB = 0x0111		///< Channel Control
sfrb DMA_CH0_ADDRCTRL = 0x0112		///< Address Control
sfrb DMA_CH0_TRIGSRC = 0x0113		///< Channel Trigger Source
sfrb DMA_CH0_TRFCNTL = 0x0114		///< Channel Block Transfer Count
sfrb DMA_CH0_TRFCNTH = (0x0114+1)	///< Channel Block Transfer Count
sfrb DMA_CH0_REPCNT = 0x0116		///< Channel Repeat Count
sfrb DMA_CH0_SRCADDR0 = 0x0118		///< Channel Source Address 0
sfrb DMA_CH0_SRCADDR1 = 0x0119		///< Channel Source Address 1
sfrb DMA_CH0_SRCADDR2 = 0x011A		///< Channel Source Address 2
sfrb DMA_CH0_DESTADDR0 = 0x011C		///< Channel Destination Address 0
sfrb DMA_CH0_DESTADDR1 = 0x011D		///< Channel Destination Address 1
sfrb DMA_CH0_DESTADDR2 = 0x011E		///< Channel Destination Address 2
sfrb DMA_CH1_CTRLA = 0x0120		///< Channel Control
sfrb DMA_CH1_CTRLB = 0x0121		///< Channel Control
sfrb DMA_CH1_ADDRCTRL = 0x0122		///< Address Control
sfrb DMA_CH1_TRIGSRC = 0x0123		///< Channel Trigger Source
sfrb DMA_CH1_TRFCNTL = 0x0124		///< Channel Block Transfer Count
sfrb DMA_CH1_TRFCNTH = (0x0124+1)	///< Channel Block Transfer Count
sfrb DMA_CH1_REPCNT = 0x0126		///< Channel Repeat Count
sfrb DMA_CH1_SRCADDR0 = 0x0128		///< Channel Source Address 0
sfrb DMA_CH1_SRCADDR1 = 0x0129		///< Channel Source Address 1
sfrb DMA_CH1_SRCADDR2 = 0x012A		///< Channel Source Address 2
sfrb DMA_CH1_DESTADDR0 = 0x012C		///< Channel Destination Address 0
sfrb DMA_CH1_DESTADDR1 = 0x012D		///< Channel Destination Address 1
sfrb DMA_CH1_DESTADDR2 = 0x012E		///< Channel Destination Address 2
sfrb DMA_CH2_CTRLA = 0x0130		///< Channel Control
sfrb DMA_CH2_CTRLB = 0x0131		///< Channel Control
sfrb DMA_CH2_ADDRCTRL = 0x0132		///< Address Control
sfrb DMA_CH2_TRIGSRC = 0x0133		///< Channel Trigger Source
sfrb DMA_CH2_TRFCNTL = 0x0134		///< Channel Block Transfer Count
sfrb DMA_CH2_TRFCNTH = (0x0134+1)	///< Channel Block Transfer Count
sfrb DMA_CH2_REPCNT = 0x0136		///< Channel Repeat Count
sfrb DMA_CH2_SRCADDR0 = 0x0138		///< Channel Source Address 0
sfrb DMA_CH2_SRCADDR1 = 0x0139		///< Channel Source Address 1
sfrb DMA_CH2_SRCADDR2 = 0x013A		///< Channel Source Address 2
sfrb DMA_CH2_DESTADDR0 = 0x013C		///< Channel Destination Address 0
sfrb DMA_CH2_DESTADDR1 = 0x013D		///< Channel Destination Address 1
sfrb DMA_CH2_DESTADDR2 = 0x013E		///< Channel Destination Address 2
sfrb DMA_CH3_CTRLA = 0x0140		///< Channel Control
sfrb DMA_CH3_CTRLB = 0x0141		///< Channel Control
sfrb DMA_CH3_ADDRCTRL = 0x0142		///< Address Control
sfrb DMA_CH3_TRIGSRC = 0x0143		///< Channel Trigger Source
sfrb DMA_CH3_TRFCNTL = 0x0144		///< Channel Block Transfer Count
sfrb DMA_CH3_TRFCNTH = (0x0144+1)	///< Channel Block Transfer Count
sfrb DMA_CH3_REPCNT = 0x0146		///< Channel Repeat Count
sfrb DMA_CH3_SRCADDR0 = 0x0148		///< Channel Source Address 0
sfrb DMA_CH3_SRCADDR1 = 0x0149		///< Channel Source Address 1
sfrb DMA_CH3_SRCADDR2 = 0x014A		///< Channel Source Address 2
sfrb DMA_CH3_DESTADDR0 = 0x014C		///< Channel Destination Address 0
sfrb DMA_CH3_DESTADDR1 = 0x014D		///< Channel Destination Address 1
sfrb DMA_CH3_DESTADDR2 = 0x014E		///< Channel Destination Address 2

/*
 --------------------------------------------------------------------------
 -- EVSYS - Event System
 --------------------------------------------------------------------------
*/
	
sfrb EVSYS_CH0MUX = 0x0180		///< Event Channel 0 Multiplexer
sfrb EVSYS_CH1MUX = 0x0181		///< Event Channel 1 Multiplexer
sfrb EVSYS_CH2MUX = 0x0182		///< Event Channel 2 Multiplexer
sfrb EVSYS_CH3MUX = 0x0183		///< Event Channel 3 Multiplexer
sfrb EVSYS_CH4MUX = 0x0184		///< Event Channel 4 Multiplexer
sfrb EVSYS_CH5MUX = 0x0185		///< Event Channel 5 Multiplexer
sfrb EVSYS_CH6MUX = 0x0186		///< Event Channel 6 Multiplexer
sfrb EVSYS_CH7MUX = 0x0187		///< Event Channel 7 Multiplexer
sfrb EVSYS_CH0CTRL = 0x0188		///< Channel 0 Control Register
sfrb EVSYS_CH1CTRL = 0x0189		///< Channel 1 Control Register
sfrb EVSYS_CH2CTRL = 0x018A		///< Channel 2 Control Register
sfrb EVSYS_CH3CTRL = 0x018B		///< Channel 3 Control Register
sfrb EVSYS_CH4CTRL = 0x018C		///< Channel 4 Control Register
sfrb EVSYS_CH5CTRL = 0x018D		///< Channel 5 Control Register
sfrb EVSYS_CH6CTRL = 0x018E		///< Channel 6 Control Register
sfrb EVSYS_CH7CTRL = 0x018F		///< Channel 7 Control Register
sfrb EVSYS_STROBE = 0x0190		///< Event Strobe
sfrb EVSYS_DATA = 0x0191		///< Event Data

/*
 --------------------------------------------------------------------------
 -- NVM - Non Volatile Memory
 --------------------------------------------------------------------------
*/
	
sfrb NVM_ADDR0 = 0x01C0		///< Address Register 0
sfrb NVM_ADDR1 = 0x01C1		///< Address Register 1
sfrb NVM_ADDR2 = 0x01C2		///< Address Register 2
sfrb NVM_DATA0 = 0x01C4		///< Data Register 0
sfrb NVM_DATA1 = 0x01C5		///< Data Register 1
sfrb NVM_DATA2 = 0x01C6		///< Data Register 2
sfrb NVM_CMD = 0x01CA		///< Command
sfrb NVM_CTRLA = 0x01CB		///< Control Register A
sfrb NVM_CTRLB = 0x01CC		///< Control Register B
sfrb NVM_INTCTRL = 0x01CD		///< Interrupt Control
sfrb NVM_STATUS = 0x01CF		///< Status
sfrb NVM_LOCKBITS = 0x01D0		///< Lock Bits

/*
 --------------------------------------------------------------------------
 -- ACA - Analog Comparator A
 --------------------------------------------------------------------------
*/
	
sfrb ACA_AC0CTRL = 0x0380		///< Comparator 0 Control
sfrb ACA_AC1CTRL = 0x0381		///< Comparator 1 Control
sfrb ACA_AC0MUXCTRL = 0x0382		///< Comparator 0 MUX Control
sfrb ACA_AC1MUXCTRL = 0x0383		///< Comparator 1 MUX Control
sfrb ACA_CTRLA = 0x0384		///< Control Register A
sfrb ACA_CTRLB = 0x0385		///< Control Register B
sfrb ACA_WINCTRL = 0x0386		///< Window Mode Control
sfrb ACA_STATUS = 0x0387		///< Status

/*
 --------------------------------------------------------------------------
 -- ADCA - Analog to Digital Converter A
 --------------------------------------------------------------------------
*/
	
sfrb ADCA_CTRLA = 0x0200		///< Control Register A
sfrb ADCA_CTRLB = 0x0201		///< Control Register B
sfrb ADCA_REFCTRL = 0x0202		///< Reference Control
sfrb ADCA_EVCTRL = 0x0203		///< Event Control
sfrb ADCA_PRESCALER = 0x0204		///< Clock Prescaler
sfrb ADCA_INTFLAGS = 0x0206		///< Interrupt Flags
sfrb ADCA_TEMP = 0x0207		///< Temporary register
sfrb ADCA_CALL = 0x020C		///< Calibration Value
sfrb ADCA_CALH = (0x020C+1)	///< Calibration Value
sfrb ADCA_CH0RESL = 0x0210		///< Channel 0 Result
sfrb ADCA_CH0RESH = (0x0210+1)	///< Channel 0 Result
sfrb ADCA_CH1RESL = 0x0212		///< Channel 1 Result
sfrb ADCA_CH1RESH = (0x0212+1)	///< Channel 1 Result
sfrb ADCA_CH2RESL = 0x0214		///< Channel 2 Result
sfrb ADCA_CH2RESH = (0x0214+1)	///< Channel 2 Result
sfrb ADCA_CH3RESL = 0x0216		///< Channel 3 Result
sfrb ADCA_CH3RESH = (0x0216+1)	///< Channel 3 Result
sfrb ADCA_CMPL = 0x0218		///< Compare Value
sfrb ADCA_CMPH = (0x0218+1)	///< Compare Value
sfrb ADCA_CH0_CTRL = 0x0220		///< Control Register
sfrb ADCA_CH0_MUXCTRL = 0x0221		///< MUX Control
sfrb ADCA_CH0_INTCTRL = 0x0222		///< Channel Interrupt Control
sfrb ADCA_CH0_INTFLAGS = 0x0223		///< Interrupt Flags
sfrb ADCA_CH0_RESL = 0x0224		///< Channel Result
sfrb ADCA_CH0_RESH = (0x0224+1)	///< Channel Result
sfrb ADCA_CH1_CTRL = 0x0228		///< Control Register
sfrb ADCA_CH1_MUXCTRL = 0x0229		///< MUX Control
sfrb ADCA_CH1_INTCTRL = 0x022A		///< Channel Interrupt Control
sfrb ADCA_CH1_INTFLAGS = 0x022B		///< Interrupt Flags
sfrb ADCA_CH1_RESL = 0x022C		///< Channel Result
sfrb ADCA_CH1_RESH = (0x022C+1)	///< Channel Result
sfrb ADCA_CH2_CTRL = 0x0230		///< Control Register
sfrb ADCA_CH2_MUXCTRL = 0x0231		///< MUX Control
sfrb ADCA_CH2_INTCTRL = 0x0232		///< Channel Interrupt Control
sfrb ADCA_CH2_INTFLAGS = 0x0233		///< Interrupt Flags
sfrb ADCA_CH2_RESL = 0x0234		///< Channel Result
sfrb ADCA_CH2_RESH = (0x0234+1)	///< Channel Result
sfrb ADCA_CH3_CTRL = 0x0238		///< Control Register
sfrb ADCA_CH3_MUXCTRL = 0x0239		///< MUX Control
sfrb ADCA_CH3_INTCTRL = 0x023A		///< Channel Interrupt Control
sfrb ADCA_CH3_INTFLAGS = 0x023B		///< Interrupt Flags
sfrb ADCA_CH3_RESL = 0x023C		///< Channel Result
sfrb ADCA_CH3_RESH = (0x023C+1)	///< Channel Result

/*
 --------------------------------------------------------------------------
 -- DACB - Digital to Analog Converter B
 --------------------------------------------------------------------------
*/
	
sfrb DACB_CTRLA = 0x0320		///< Control Register A
sfrb DACB_CTRLB = 0x0321		///< Control Register B
sfrb DACB_CTRLC = 0x0322		///< Control Register C
sfrb DACB_EVCTRL = 0x0323		///< Event Input Control
sfrb DACB_TIMCTRL = 0x0324		///< Timing Control
sfrb DACB_STATUS = 0x0325		///< Status
sfrb DACB_GAINCAL = 0x0328		///< Gain Calibration
sfrb DACB_OFFSETCAL = 0x0329		///< Offset Calibration
sfrb DACB_CH0DATAL = 0x0338		///< Channel 0 Data
sfrb DACB_CH0DATAH = (0x0338+1)	///< Channel 0 Data
sfrb DACB_CH1DATAL = 0x033A		///< Channel 1 Data
sfrb DACB_CH1DATAH = (0x033A+1)	///< Channel 1 Data

/*
 --------------------------------------------------------------------------
 -- RTC - Real-Time Counter
 --------------------------------------------------------------------------
*/
	
sfrb RTC_CTRL = 0x0400		///< Control Register
sfrb RTC_STATUS = 0x0401		///< Status Register
sfrb RTC_INTCTRL = 0x0402		///< Interrupt Control Register
sfrb RTC_INTFLAGS = 0x0403		///< Interrupt Flags
sfrb RTC_TEMP = 0x0404		///< Temporary register
sfrb RTC_CNTL = 0x0408		///< Count Register
sfrb RTC_CNTH = (0x0408+1)	///< Count Register
sfrb RTC_PERL = 0x040A		///< Period Register
sfrb RTC_PERH = (0x040A+1)	///< Period Register
sfrb RTC_COMPL = 0x040C		///< Compare Register
sfrb RTC_COMPH = (0x040C+1)	///< Compare Register

/*
 --------------------------------------------------------------------------
 -- TWIC - Two-Wire Interface C
 --------------------------------------------------------------------------
*/
	
sfrb TWIC_CTRL = 0x0480		///< TWI Common Control Register
sfrb TWIC_MASTER_CTRLA = 0x0481		///< Control Register A
sfrb TWIC_MASTER_CTRLB = 0x0482		///< Control Register B
sfrb TWIC_MASTER_CTRLC = 0x0483		///< Control Register C
sfrb TWIC_MASTER_STATUS = 0x0484		///< Status Register
sfrb TWIC_MASTER_BAUD = 0x0485		///< Baurd Rate Control Register
sfrb TWIC_MASTER_ADDR = 0x0486		///< Address Register
sfrb TWIC_MASTER_DATA = 0x0487		///< Data Register
sfrb TWIC_SLAVE_CTRLA = 0x0488		///< Control Register A
sfrb TWIC_SLAVE_CTRLB = 0x0489		///< Control Register B
sfrb TWIC_SLAVE_STATUS = 0x048A		///< Status Register
sfrb TWIC_SLAVE_ADDR = 0x048B		///< Address Register
sfrb TWIC_SLAVE_DATA = 0x048C		///< Data Register
sfrb TWIC_SLAVE_ADDRMASK = 0x048D		///< Address Mask Register

/*
 --------------------------------------------------------------------------
 -- TWIE - Two-Wire Interface E
 --------------------------------------------------------------------------
*/
	
sfrb TWIE_CTRL = 0x04A0		///< TWI Common Control Register
sfrb TWIE_MASTER_CTRLA = 0x04A1		///< Control Register A
sfrb TWIE_MASTER_CTRLB = 0x04A2		///< Control Register B
sfrb TWIE_MASTER_CTRLC = 0x04A3		///< Control Register C
sfrb TWIE_MASTER_STATUS = 0x04A4		///< Status Register
sfrb TWIE_MASTER_BAUD = 0x04A5		///< Baurd Rate Control Register
sfrb TWIE_MASTER_ADDR = 0x04A6		///< Address Register
sfrb TWIE_MASTER_DATA = 0x04A7		///< Data Register
sfrb TWIE_SLAVE_CTRLA = 0x04A8		///< Control Register A
sfrb TWIE_SLAVE_CTRLB = 0x04A9		///< Control Register B
sfrb TWIE_SLAVE_STATUS = 0x04AA		///< Status Register
sfrb TWIE_SLAVE_ADDR = 0x04AB		///< Address Register
sfrb TWIE_SLAVE_DATA = 0x04AC		///< Data Register
sfrb TWIE_SLAVE_ADDRMASK = 0x04AD		///< Address Mask Register

/*
 --------------------------------------------------------------------------
 -- PORT_CFG - Port Configuration
 --------------------------------------------------------------------------
*/
	
sfrb PORTCFG_MPCMASK = 0x00B0		///< Multi-pin Configuration Mask
sfrb PORTCFG_VPCTRLA = 0x00B2		///< Virtual Port Control Register A
sfrb PORTCFG_VPCTRLB = 0x00B3		///< Virtual Port Control Register B
sfrb PORTCFG_CLKEVOUT = 0x00B4		///< Clock and Event Out Register

/*
 --------------------------------------------------------------------------
 -- VPORT0 - Virtual Port 0
 --------------------------------------------------------------------------
*/
	
sfrb VPORT0_DIR = 0x0010		///< I/O Port Data Direction
sfrb VPORT0_OUT = 0x0011		///< I/O Port Output
sfrb VPORT0_IN = 0x0012		///< I/O Port Input
sfrb VPORT0_INTFLAGS = 0x0013		///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- VPORT1 - Virtual Port 1
 --------------------------------------------------------------------------
*/
	
sfrb VPORT1_DIR = 0x0014		///< I/O Port Data Direction
sfrb VPORT1_OUT = 0x0015		///< I/O Port Output
sfrb VPORT1_IN = 0x0016		///< I/O Port Input
sfrb VPORT1_INTFLAGS = 0x0017		///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- VPORT2 - Virtual Port 2
 --------------------------------------------------------------------------
*/
	
sfrb VPORT2_DIR = 0x0018		///< I/O Port Data Direction
sfrb VPORT2_OUT = 0x0019		///< I/O Port Output
sfrb VPORT2_IN = 0x001A		///< I/O Port Input
sfrb VPORT2_INTFLAGS = 0x001B		///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- VPORT3 - Virtual Port 3
 --------------------------------------------------------------------------
*/
	
sfrb VPORT3_DIR = 0x001C		///< I/O Port Data Direction
sfrb VPORT3_OUT = 0x001D		///< I/O Port Output
sfrb VPORT3_IN = 0x001E		///< I/O Port Input
sfrb VPORT3_INTFLAGS = 0x001F		///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- PORTA - Port A
 --------------------------------------------------------------------------
*/
	
sfrb PORTA_DIR = 0x0600		///< I/O Port Data Direction
sfrb PORTA_DIRSET = 0x0601		///< I/O Port Data Direction Set
sfrb PORTA_DIRCLR = 0x0602		///< I/O Port Data Direction Clear
sfrb PORTA_DIRTGL = 0x0603		///< I/O Port Data Direction Toggle
sfrb PORTA_OUT = 0x0604		///< I/O Port Output
sfrb PORTA_OUTSET = 0x0605		///< I/O Port Output Set
sfrb PORTA_OUTCLR = 0x0606		///< I/O Port Output Clear
sfrb PORTA_OUTTGL = 0x0607		///< I/O Port Output Toggle
sfrb PORTA_IN = 0x0608		///< I/O port Input
sfrb PORTA_INTCTRL = 0x0609		///< Interrupt Control Register
sfrb PORTA_INT0MASK = 0x060A		///< Port Interrupt 0 Mask
sfrb PORTA_INT1MASK = 0x060B		///< Port Interrupt 1 Mask
sfrb PORTA_INTFLAGS = 0x060C		///< Interrupt Flag Register
sfrb PORTA_PIN0CTRL = 0x0610		///< Pin 0 Control Register
sfrb PORTA_PIN1CTRL = 0x0611		///< Pin 1 Control Register
sfrb PORTA_PIN2CTRL = 0x0612		///< Pin 2 Control Register
sfrb PORTA_PIN3CTRL = 0x0613		///< Pin 3 Control Register
sfrb PORTA_PIN4CTRL = 0x0614		///< Pin 4 Control Register
sfrb PORTA_PIN5CTRL = 0x0615		///< Pin 5 Control Register
sfrb PORTA_PIN6CTRL = 0x0616		///< Pin 6 Control Register
sfrb PORTA_PIN7CTRL = 0x0617		///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTB - Port B
 --------------------------------------------------------------------------
*/
	
sfrb PORTB_DIR = 0x0620		///< I/O Port Data Direction
sfrb PORTB_DIRSET = 0x0621		///< I/O Port Data Direction Set
sfrb PORTB_DIRCLR = 0x0622		///< I/O Port Data Direction Clear
sfrb PORTB_DIRTGL = 0x0623		///< I/O Port Data Direction Toggle
sfrb PORTB_OUT = 0x0624		///< I/O Port Output
sfrb PORTB_OUTSET = 0x0625		///< I/O Port Output Set
sfrb PORTB_OUTCLR = 0x0626		///< I/O Port Output Clear
sfrb PORTB_OUTTGL = 0x0627		///< I/O Port Output Toggle
sfrb PORTB_IN = 0x0628		///< I/O port Input
sfrb PORTB_INTCTRL = 0x0629		///< Interrupt Control Register
sfrb PORTB_INT0MASK = 0x062A		///< Port Interrupt 0 Mask
sfrb PORTB_INT1MASK = 0x062B		///< Port Interrupt 1 Mask
sfrb PORTB_INTFLAGS = 0x062C		///< Interrupt Flag Register
sfrb PORTB_PIN0CTRL = 0x0630		///< Pin 0 Control Register
sfrb PORTB_PIN1CTRL = 0x0631		///< Pin 1 Control Register
sfrb PORTB_PIN2CTRL = 0x0632		///< Pin 2 Control Register
sfrb PORTB_PIN3CTRL = 0x0633		///< Pin 3 Control Register
sfrb PORTB_PIN4CTRL = 0x0634		///< Pin 4 Control Register
sfrb PORTB_PIN5CTRL = 0x0635		///< Pin 5 Control Register
sfrb PORTB_PIN6CTRL = 0x0636		///< Pin 6 Control Register
sfrb PORTB_PIN7CTRL = 0x0637		///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTC - Port C
 --------------------------------------------------------------------------
*/
	
sfrb PORTC_DIR = 0x0640		///< I/O Port Data Direction
sfrb PORTC_DIRSET = 0x0641		///< I/O Port Data Direction Set
sfrb PORTC_DIRCLR = 0x0642		///< I/O Port Data Direction Clear
sfrb PORTC_DIRTGL = 0x0643		///< I/O Port Data Direction Toggle
sfrb PORTC_OUT = 0x0644		///< I/O Port Output
sfrb PORTC_OUTSET = 0x0645		///< I/O Port Output Set
sfrb PORTC_OUTCLR = 0x0646		///< I/O Port Output Clear
sfrb PORTC_OUTTGL = 0x0647		///< I/O Port Output Toggle
sfrb PORTC_IN = 0x0648		///< I/O port Input
sfrb PORTC_INTCTRL = 0x0649		///< Interrupt Control Register
sfrb PORTC_INT0MASK = 0x064A		///< Port Interrupt 0 Mask
sfrb PORTC_INT1MASK = 0x064B		///< Port Interrupt 1 Mask
sfrb PORTC_INTFLAGS = 0x064C		///< Interrupt Flag Register
sfrb PORTC_PIN0CTRL = 0x0650		///< Pin 0 Control Register
sfrb PORTC_PIN1CTRL = 0x0651		///< Pin 1 Control Register
sfrb PORTC_PIN2CTRL = 0x0652		///< Pin 2 Control Register
sfrb PORTC_PIN3CTRL = 0x0653		///< Pin 3 Control Register
sfrb PORTC_PIN4CTRL = 0x0654		///< Pin 4 Control Register
sfrb PORTC_PIN5CTRL = 0x0655		///< Pin 5 Control Register
sfrb PORTC_PIN6CTRL = 0x0656		///< Pin 6 Control Register
sfrb PORTC_PIN7CTRL = 0x0657		///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTD - Port D
 --------------------------------------------------------------------------
*/
	
sfrb PORTD_DIR = 0x0660		///< I/O Port Data Direction
sfrb PORTD_DIRSET = 0x0661		///< I/O Port Data Direction Set
sfrb PORTD_DIRCLR = 0x0662		///< I/O Port Data Direction Clear
sfrb PORTD_DIRTGL = 0x0663		///< I/O Port Data Direction Toggle
sfrb PORTD_OUT = 0x0664		///< I/O Port Output
sfrb PORTD_OUTSET = 0x0665		///< I/O Port Output Set
sfrb PORTD_OUTCLR = 0x0666		///< I/O Port Output Clear
sfrb PORTD_OUTTGL = 0x0667		///< I/O Port Output Toggle
sfrb PORTD_IN = 0x0668		///< I/O port Input
sfrb PORTD_INTCTRL = 0x0669		///< Interrupt Control Register
sfrb PORTD_INT0MASK = 0x066A		///< Port Interrupt 0 Mask
sfrb PORTD_INT1MASK = 0x066B		///< Port Interrupt 1 Mask
sfrb PORTD_INTFLAGS = 0x066C		///< Interrupt Flag Register
sfrb PORTD_PIN0CTRL = 0x0670		///< Pin 0 Control Register
sfrb PORTD_PIN1CTRL = 0x0671		///< Pin 1 Control Register
sfrb PORTD_PIN2CTRL = 0x0672		///< Pin 2 Control Register
sfrb PORTD_PIN3CTRL = 0x0673		///< Pin 3 Control Register
sfrb PORTD_PIN4CTRL = 0x0674		///< Pin 4 Control Register
sfrb PORTD_PIN5CTRL = 0x0675		///< Pin 5 Control Register
sfrb PORTD_PIN6CTRL = 0x0676		///< Pin 6 Control Register
sfrb PORTD_PIN7CTRL = 0x0677		///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTE - Port E
 --------------------------------------------------------------------------
*/
	
sfrb PORTE_DIR = 0x0680		///< I/O Port Data Direction
sfrb PORTE_DIRSET = 0x0681		///< I/O Port Data Direction Set
sfrb PORTE_DIRCLR = 0x0682		///< I/O Port Data Direction Clear
sfrb PORTE_DIRTGL = 0x0683		///< I/O Port Data Direction Toggle
sfrb PORTE_OUT = 0x0684		///< I/O Port Output
sfrb PORTE_OUTSET = 0x0685		///< I/O Port Output Set
sfrb PORTE_OUTCLR = 0x0686		///< I/O Port Output Clear
sfrb PORTE_OUTTGL = 0x0687		///< I/O Port Output Toggle
sfrb PORTE_IN = 0x0688		///< I/O port Input
sfrb PORTE_INTCTRL = 0x0689		///< Interrupt Control Register
sfrb PORTE_INT0MASK = 0x068A		///< Port Interrupt 0 Mask
sfrb PORTE_INT1MASK = 0x068B		///< Port Interrupt 1 Mask
sfrb PORTE_INTFLAGS = 0x068C		///< Interrupt Flag Register
sfrb PORTE_PIN0CTRL = 0x0690		///< Pin 0 Control Register
sfrb PORTE_PIN1CTRL = 0x0691		///< Pin 1 Control Register
sfrb PORTE_PIN2CTRL = 0x0692		///< Pin 2 Control Register
sfrb PORTE_PIN3CTRL = 0x0693		///< Pin 3 Control Register
sfrb PORTE_PIN4CTRL = 0x0694		///< Pin 4 Control Register
sfrb PORTE_PIN5CTRL = 0x0695		///< Pin 5 Control Register
sfrb PORTE_PIN6CTRL = 0x0696		///< Pin 6 Control Register
sfrb PORTE_PIN7CTRL = 0x0697		///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTR - Port R
 --------------------------------------------------------------------------
*/
	
sfrb PORTR_DIR = 0x07E0		///< I/O Port Data Direction
sfrb PORTR_DIRSET = 0x07E1		///< I/O Port Data Direction Set
sfrb PORTR_DIRCLR = 0x07E2		///< I/O Port Data Direction Clear
sfrb PORTR_DIRTGL = 0x07E3		///< I/O Port Data Direction Toggle
sfrb PORTR_OUT = 0x07E4		///< I/O Port Output
sfrb PORTR_OUTSET = 0x07E5		///< I/O Port Output Set
sfrb PORTR_OUTCLR = 0x07E6		///< I/O Port Output Clear
sfrb PORTR_OUTTGL = 0x07E7		///< I/O Port Output Toggle
sfrb PORTR_IN = 0x07E8		///< I/O port Input
sfrb PORTR_INTCTRL = 0x07E9		///< Interrupt Control Register
sfrb PORTR_INT0MASK = 0x07EA		///< Port Interrupt 0 Mask
sfrb PORTR_INT1MASK = 0x07EB		///< Port Interrupt 1 Mask
sfrb PORTR_INTFLAGS = 0x07EC		///< Interrupt Flag Register
sfrb PORTR_PIN0CTRL = 0x07F0		///< Pin 0 Control Register
sfrb PORTR_PIN1CTRL = 0x07F1		///< Pin 1 Control Register
sfrb PORTR_PIN2CTRL = 0x07F2		///< Pin 2 Control Register
sfrb PORTR_PIN3CTRL = 0x07F3		///< Pin 3 Control Register
sfrb PORTR_PIN4CTRL = 0x07F4		///< Pin 4 Control Register
sfrb PORTR_PIN5CTRL = 0x07F5		///< Pin 5 Control Register
sfrb PORTR_PIN6CTRL = 0x07F6		///< Pin 6 Control Register
sfrb PORTR_PIN7CTRL = 0x07F7		///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- TCC0 - Timer/Counter C0
 --------------------------------------------------------------------------
*/
	
sfrb TCC0_CTRLA = 0x0800		///< Control  Register A
sfrb TCC0_CTRLB = 0x0801		///< Control Register B
sfrb TCC0_CTRLC = 0x0802		///< Control register C
sfrb TCC0_CTRLD = 0x0803		///< Control Register D
sfrb TCC0_CTRLE = 0x0804		///< Control Register E
sfrb TCC0_INTCTRLA = 0x0806		///< Interrupt Control Register A
sfrb TCC0_INTCTRLB = 0x0807		///< Interrupt Control Register B
sfrb TCC0_CTRLFCLR = 0x0808		///< Control Register F Clear
sfrb TCC0_CTRLFSET = 0x0809		///< Control Register F Set
sfrb TCC0_CTRLGCLR = 0x080A		///< Control Register G Clear
sfrb TCC0_CTRLGSET = 0x080B		///< Control Register G Set
sfrb TCC0_INTFLAGS = 0x080C		///< Interrupt Flag Register
sfrb TCC0_TEMP = 0x080F		///< Temporary Register For 16-bit Access
sfrb TCC0_CNTL = 0x0820		///< Count
sfrb TCC0_CNTH = (0x0820+1)	///< Count
sfrb TCC0_PERL = 0x0826		///< Period
sfrb TCC0_PERH = (0x0826+1)	///< Period
sfrb TCC0_CCAL = 0x0828		///< Compare or Capture A
sfrb TCC0_CCAH = (0x0828+1)	///< Compare or Capture A
sfrb TCC0_CCBL = 0x082A		///< Compare or Capture B
sfrb TCC0_CCBH = (0x082A+1)	///< Compare or Capture B
sfrb TCC0_CCCL = 0x082C		///< Compare or Capture C
sfrb TCC0_CCCH = (0x082C+1)	///< Compare or Capture C
sfrb TCC0_CCDL = 0x082E		///< Compare or Capture D
sfrb TCC0_CCDH = (0x082E+1)	///< Compare or Capture D
sfrb TCC0_PERBUFL = 0x0836		///< Period Buffer
sfrb TCC0_PERBUFH = (0x0836+1)	///< Period Buffer
sfrb TCC0_CCABUFL = 0x0838		///< Compare Or Capture A Buffer
sfrb TCC0_CCABUFH = (0x0838+1)	///< Compare Or Capture A Buffer
sfrb TCC0_CCBBUFL = 0x083A		///< Compare Or Capture B Buffer
sfrb TCC0_CCBBUFH = (0x083A+1)	///< Compare Or Capture B Buffer
sfrb TCC0_CCCBUFL = 0x083C		///< Compare Or Capture C Buffer
sfrb TCC0_CCCBUFH = (0x083C+1)	///< Compare Or Capture C Buffer
sfrb TCC0_CCDBUFL = 0x083E		///< Compare Or Capture D Buffer
sfrb TCC0_CCDBUFH = (0x083E+1)	///< Compare Or Capture D Buffer

/*
 --------------------------------------------------------------------------
 -- TCC1 - Timer/Counter C1
 --------------------------------------------------------------------------
*/
	
sfrb TCC1_CTRLA = 0x0840		///< Control  Register A
sfrb TCC1_CTRLB = 0x0841		///< Control Register B
sfrb TCC1_CTRLC = 0x0842		///< Control register C
sfrb TCC1_CTRLD = 0x0843		///< Control Register D
sfrb TCC1_CTRLE = 0x0844		///< Control Register E
sfrb TCC1_INTCTRLA = 0x0846		///< Interrupt Control Register A
sfrb TCC1_INTCTRLB = 0x0847		///< Interrupt Control Register B
sfrb TCC1_CTRLFCLR = 0x0848		///< Control Register F Clear
sfrb TCC1_CTRLFSET = 0x0849		///< Control Register F Set
sfrb TCC1_CTRLGCLR = 0x084A		///< Control Register G Clear
sfrb TCC1_CTRLGSET = 0x084B		///< Control Register G Set
sfrb TCC1_INTFLAGS = 0x084C		///< Interrupt Flag Register
sfrb TCC1_TEMP = 0x084F		///< Temporary Register For 16-bit Access
sfrb TCC1_CNTL = 0x0860		///< Count
sfrb TCC1_CNTH = (0x0860+1)	///< Count
sfrb TCC1_PERL = 0x0866		///< Period
sfrb TCC1_PERH = (0x0866+1)	///< Period
sfrb TCC1_CCAL = 0x0868		///< Compare or Capture A
sfrb TCC1_CCAH = (0x0868+1)	///< Compare or Capture A
sfrb TCC1_CCBL = 0x086A		///< Compare or Capture B
sfrb TCC1_CCBH = (0x086A+1)	///< Compare or Capture B
sfrb TCC1_PERBUFL = 0x0876		///< Period Buffer
sfrb TCC1_PERBUFH = (0x0876+1)	///< Period Buffer
sfrb TCC1_CCABUFL = 0x0878		///< Compare Or Capture A Buffer
sfrb TCC1_CCABUFH = (0x0878+1)	///< Compare Or Capture A Buffer
sfrb TCC1_CCBBUFL = 0x087A		///< Compare Or Capture B Buffer
sfrb TCC1_CCBBUFH = (0x087A+1)	///< Compare Or Capture B Buffer

/*
 --------------------------------------------------------------------------
 -- AWEXC - Advanced Waveform Extension C
 --------------------------------------------------------------------------
*/
	
sfrb AWEXC_CTRL = 0x0880		///< Control Register
sfrb AWEXC_FDEMASK = 0x0882		///< Fault Detection Event Mask
sfrb AWEXC_FDCTRL = 0x0883		///< Fault Detection Control Register
sfrb AWEXC_STATUS = 0x0884		///< Status Register
sfrb AWEXC_DTBOTH = 0x0886		///< Dead Time Both Sides
sfrb AWEXC_DTBOTHBUF = 0x0887		///< Dead Time Both Sides Buffer
sfrb AWEXC_DTLS = 0x0888		///< Dead Time Low Side
sfrb AWEXC_DTHS = 0x0889		///< Dead Time High Side
sfrb AWEXC_DTLSBUF = 0x088A		///< Dead Time Low Side Buffer
sfrb AWEXC_DTHSBUF = 0x088B		///< Dead Time High Side Buffer
sfrb AWEXC_OUTOVEN = 0x088C		///< Output Override Enable

/*
 --------------------------------------------------------------------------
 -- HIRESC - High-Resolution Extension C
 --------------------------------------------------------------------------
*/
	
sfrb HIRESC_CTRLA = 0x0890		///< Control Register

/*
 --------------------------------------------------------------------------
 -- USARTC0 - Universal Asynchronous Receiver-Transmitter C0
 --------------------------------------------------------------------------
*/
	
sfrb USARTC0_DATA = 0x08A0		///< Data Register
sfrb USARTC0_STATUS = 0x08A1		///< Status Register
sfrb USARTC0_CTRLA = 0x08A3		///< Control Register A
sfrb USARTC0_CTRLB = 0x08A4		///< Control Register B
sfrb USARTC0_CTRLC = 0x08A5		///< Control Register C
sfrb USARTC0_BAUDCTRLA = 0x08A6		///< Baud Rate Control Register A
sfrb USARTC0_BAUDCTRLB = 0x08A7		///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- USARTC1 - Universal Asynchronous Receiver-Transmitter C1
 --------------------------------------------------------------------------
*/
	
sfrb USARTC1_DATA = 0x08B0		///< Data Register
sfrb USARTC1_STATUS = 0x08B1		///< Status Register
sfrb USARTC1_CTRLA = 0x08B3		///< Control Register A
sfrb USARTC1_CTRLB = 0x08B4		///< Control Register B
sfrb USARTC1_CTRLC = 0x08B5		///< Control Register C
sfrb USARTC1_BAUDCTRLA = 0x08B6		///< Baud Rate Control Register A
sfrb USARTC1_BAUDCTRLB = 0x08B7		///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- SPIC - Serial Peripheral Interface C
 --------------------------------------------------------------------------
*/
	
sfrb SPIC_CTRL = 0x08C0		///< Control Register
sfrb SPIC_INTCTRL = 0x08C1		///< Interrupt Control Register
sfrb SPIC_STATUS = 0x08C2		///< Status Register
sfrb SPIC_DATA = 0x08C3		///< Data Register

/*
 --------------------------------------------------------------------------
 -- TCD0 - Timer/Counter D0
 --------------------------------------------------------------------------
*/
	
sfrb TCD0_CTRLA = 0x0900		///< Control  Register A
sfrb TCD0_CTRLB = 0x0901		///< Control Register B
sfrb TCD0_CTRLC = 0x0902		///< Control register C
sfrb TCD0_CTRLD = 0x0903		///< Control Register D
sfrb TCD0_CTRLE = 0x0904		///< Control Register E
sfrb TCD0_INTCTRLA = 0x0906		///< Interrupt Control Register A
sfrb TCD0_INTCTRLB = 0x0907		///< Interrupt Control Register B
sfrb TCD0_CTRLFCLR = 0x0908		///< Control Register F Clear
sfrb TCD0_CTRLFSET = 0x0909		///< Control Register F Set
sfrb TCD0_CTRLGCLR = 0x090A		///< Control Register G Clear
sfrb TCD0_CTRLGSET = 0x090B		///< Control Register G Set
sfrb TCD0_INTFLAGS = 0x090C		///< Interrupt Flag Register
sfrb TCD0_TEMP = 0x090F		///< Temporary Register For 16-bit Access
sfrb TCD0_CNTL = 0x0920		///< Count
sfrb TCD0_CNTH = (0x0920+1)	///< Count
sfrb TCD0_PERL = 0x0926		///< Period
sfrb TCD0_PERH = (0x0926+1)	///< Period
sfrb TCD0_CCAL = 0x0928		///< Compare or Capture A
sfrb TCD0_CCAH = (0x0928+1)	///< Compare or Capture A
sfrb TCD0_CCBL = 0x092A		///< Compare or Capture B
sfrb TCD0_CCBH = (0x092A+1)	///< Compare or Capture B
sfrb TCD0_CCCL = 0x092C		///< Compare or Capture C
sfrb TCD0_CCCH = (0x092C+1)	///< Compare or Capture C
sfrb TCD0_CCDL = 0x092E		///< Compare or Capture D
sfrb TCD0_CCDH = (0x092E+1)	///< Compare or Capture D
sfrb TCD0_PERBUFL = 0x0936		///< Period Buffer
sfrb TCD0_PERBUFH = (0x0936+1)	///< Period Buffer
sfrb TCD0_CCABUFL = 0x0938		///< Compare Or Capture A Buffer
sfrb TCD0_CCABUFH = (0x0938+1)	///< Compare Or Capture A Buffer
sfrb TCD0_CCBBUFL = 0x093A		///< Compare Or Capture B Buffer
sfrb TCD0_CCBBUFH = (0x093A+1)	///< Compare Or Capture B Buffer
sfrb TCD0_CCCBUFL = 0x093C		///< Compare Or Capture C Buffer
sfrb TCD0_CCCBUFH = (0x093C+1)	///< Compare Or Capture C Buffer
sfrb TCD0_CCDBUFL = 0x093E		///< Compare Or Capture D Buffer
sfrb TCD0_CCDBUFH = (0x093E+1)	///< Compare Or Capture D Buffer

/*
 --------------------------------------------------------------------------
 -- TCD1 - Timer/Counter D1
 --------------------------------------------------------------------------
*/
	
sfrb TCD1_CTRLA = 0x0940		///< Control  Register A
sfrb TCD1_CTRLB = 0x0941		///< Control Register B
sfrb TCD1_CTRLC = 0x0942		///< Control register C
sfrb TCD1_CTRLD = 0x0943		///< Control Register D
sfrb TCD1_CTRLE = 0x0944		///< Control Register E
sfrb TCD1_INTCTRLA = 0x0946		///< Interrupt Control Register A
sfrb TCD1_INTCTRLB = 0x0947		///< Interrupt Control Register B
sfrb TCD1_CTRLFCLR = 0x0948		///< Control Register F Clear
sfrb TCD1_CTRLFSET = 0x0949		///< Control Register F Set
sfrb TCD1_CTRLGCLR = 0x094A		///< Control Register G Clear
sfrb TCD1_CTRLGSET = 0x094B		///< Control Register G Set
sfrb TCD1_INTFLAGS = 0x094C		///< Interrupt Flag Register
sfrb TCD1_TEMP = 0x094F		///< Temporary Register For 16-bit Access
sfrb TCD1_CNTL = 0x0960		///< Count
sfrb TCD1_CNTH = (0x0960+1)	///< Count
sfrb TCD1_PERL = 0x0966		///< Period
sfrb TCD1_PERH = (0x0966+1)	///< Period
sfrb TCD1_CCAL = 0x0968		///< Compare or Capture A
sfrb TCD1_CCAH = (0x0968+1)	///< Compare or Capture A
sfrb TCD1_CCBL = 0x096A		///< Compare or Capture B
sfrb TCD1_CCBH = (0x096A+1)	///< Compare or Capture B
sfrb TCD1_PERBUFL = 0x0976		///< Period Buffer
sfrb TCD1_PERBUFH = (0x0976+1)	///< Period Buffer
sfrb TCD1_CCABUFL = 0x0978		///< Compare Or Capture A Buffer
sfrb TCD1_CCABUFH = (0x0978+1)	///< Compare Or Capture A Buffer
sfrb TCD1_CCBBUFL = 0x097A		///< Compare Or Capture B Buffer
sfrb TCD1_CCBBUFH = (0x097A+1)	///< Compare Or Capture B Buffer

/*
 --------------------------------------------------------------------------
 -- HIRESD - High-Resolution Extension D
 --------------------------------------------------------------------------
*/
	
sfrb HIRESD_CTRLA = 0x0990		///< Control Register

/*
 --------------------------------------------------------------------------
 -- USARTD0 - Universal Asynchronous Receiver-Transmitter D0
 --------------------------------------------------------------------------
*/
	
sfrb USARTD0_DATA = 0x09A0		///< Data Register
sfrb USARTD0_STATUS = 0x09A1		///< Status Register
sfrb USARTD0_CTRLA = 0x09A3		///< Control Register A
sfrb USARTD0_CTRLB = 0x09A4		///< Control Register B
sfrb USARTD0_CTRLC = 0x09A5		///< Control Register C
sfrb USARTD0_BAUDCTRLA = 0x09A6		///< Baud Rate Control Register A
sfrb USARTD0_BAUDCTRLB = 0x09A7		///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- USARTD1 - Universal Asynchronous Receiver-Transmitter D1
 --------------------------------------------------------------------------
*/
	
sfrb USARTD1_DATA = 0x09B0		///< Data Register
sfrb USARTD1_STATUS = 0x09B1		///< Status Register
sfrb USARTD1_CTRLA = 0x09B3		///< Control Register A
sfrb USARTD1_CTRLB = 0x09B4		///< Control Register B
sfrb USARTD1_CTRLC = 0x09B5		///< Control Register C
sfrb USARTD1_BAUDCTRLA = 0x09B6		///< Baud Rate Control Register A
sfrb USARTD1_BAUDCTRLB = 0x09B7		///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- SPID - Serial Peripheral Interface D
 --------------------------------------------------------------------------
*/
	
sfrb SPID_CTRL = 0x09C0		///< Control Register
sfrb SPID_INTCTRL = 0x09C1		///< Interrupt Control Register
sfrb SPID_STATUS = 0x09C2		///< Status Register
sfrb SPID_DATA = 0x09C3		///< Data Register

/*
 --------------------------------------------------------------------------
 -- TCE0 - Timer/Counter E0
 --------------------------------------------------------------------------
*/
	
sfrb TCE0_CTRLA = 0x0A00		///< Control  Register A
sfrb TCE0_CTRLB = 0x0A01		///< Control Register B
sfrb TCE0_CTRLC = 0x0A02		///< Control register C
sfrb TCE0_CTRLD = 0x0A03		///< Control Register D
sfrb TCE0_CTRLE = 0x0A04		///< Control Register E
sfrb TCE0_INTCTRLA = 0x0A06		///< Interrupt Control Register A
sfrb TCE0_INTCTRLB = 0x0A07		///< Interrupt Control Register B
sfrb TCE0_CTRLFCLR = 0x0A08		///< Control Register F Clear
sfrb TCE0_CTRLFSET = 0x0A09		///< Control Register F Set
sfrb TCE0_CTRLGCLR = 0x0A0A		///< Control Register G Clear
sfrb TCE0_CTRLGSET = 0x0A0B		///< Control Register G Set
sfrb TCE0_INTFLAGS = 0x0A0C		///< Interrupt Flag Register
sfrb TCE0_TEMP = 0x0A0F		///< Temporary Register For 16-bit Access
sfrb TCE0_CNTL = 0x0A20		///< Count
sfrb TCE0_CNTH = (0x0A20+1)	///< Count
sfrb TCE0_PERL = 0x0A26		///< Period
sfrb TCE0_PERH = (0x0A26+1)	///< Period
sfrb TCE0_CCAL = 0x0A28		///< Compare or Capture A
sfrb TCE0_CCAH = (0x0A28+1)	///< Compare or Capture A
sfrb TCE0_CCBL = 0x0A2A		///< Compare or Capture B
sfrb TCE0_CCBH = (0x0A2A+1)	///< Compare or Capture B
sfrb TCE0_CCCL = 0x0A2C		///< Compare or Capture C
sfrb TCE0_CCCH = (0x0A2C+1)	///< Compare or Capture C
sfrb TCE0_CCDL = 0x0A2E		///< Compare or Capture D
sfrb TCE0_CCDH = (0x0A2E+1)	///< Compare or Capture D
sfrb TCE0_PERBUFL = 0x0A36		///< Period Buffer
sfrb TCE0_PERBUFH = (0x0A36+1)	///< Period Buffer
sfrb TCE0_CCABUFL = 0x0A38		///< Compare Or Capture A Buffer
sfrb TCE0_CCABUFH = (0x0A38+1)	///< Compare Or Capture A Buffer
sfrb TCE0_CCBBUFL = 0x0A3A		///< Compare Or Capture B Buffer
sfrb TCE0_CCBBUFH = (0x0A3A+1)	///< Compare Or Capture B Buffer
sfrb TCE0_CCCBUFL = 0x0A3C		///< Compare Or Capture C Buffer
sfrb TCE0_CCCBUFH = (0x0A3C+1)	///< Compare Or Capture C Buffer
sfrb TCE0_CCDBUFL = 0x0A3E		///< Compare Or Capture D Buffer
sfrb TCE0_CCDBUFH = (0x0A3E+1)	///< Compare Or Capture D Buffer

/*
 --------------------------------------------------------------------------
 -- HIRESE - High-Resolution Extension E
 --------------------------------------------------------------------------
*/
	
sfrb HIRESE_CTRLA = 0x0A90		///< Control Register

/*
 --------------------------------------------------------------------------
 -- USARTE0 - Universal Asynchronous Receiver-Transmitter E0
 --------------------------------------------------------------------------
*/
	
sfrb USARTE0_DATA = 0x0AA0		///< Data Register
sfrb USARTE0_STATUS = 0x0AA1		///< Status Register
sfrb USARTE0_CTRLA = 0x0AA3		///< Control Register A
sfrb USARTE0_CTRLB = 0x0AA4		///< Control Register B
sfrb USARTE0_CTRLC = 0x0AA5		///< Control Register C
sfrb USARTE0_BAUDCTRLA = 0x0AA6		///< Baud Rate Control Register A
sfrb USARTE0_BAUDCTRLB = 0x0AA7		///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- IRCOM - IR Communication Module
 --------------------------------------------------------------------------
*/
	
sfrb IRCOM_CTRL = 0x08F8		///< Control Register
sfrb IRCOM_TXPLCTRL = 0x08F9		///< IrDA Transmitter Pulse Length Control Register
sfrb IRCOM_RXPLCTRL = 0x08FA		///< IrDA Receiver Pulse Length Control Register

/*
 --------------------------------------------------------------------------
 -- AES - AES Crypto Module
 --------------------------------------------------------------------------
*/
	
sfrb AES_CTRL = 0x00C0		///< AES Control Register
sfrb AES_STATUS = 0x00C1		///< AES Status Register
sfrb AES_STATE = 0x00C2		///< AES State Register
sfrb AES_KEY = 0x00C3		///< AES Key Register
sfrb AES_INTCTRL = 0x00C4		///< AES Interrupt Control Register


#endif // defined(__IAR_SYSTEMS_ASM__)



#if defined(__IAR_SYSTEMS_ICC__)

/*
 ---------------------------------------------------------------------------
 ---------------------------------------------------------------------------
 --
 -- Fully qualified IO register names for use with the compiler
 --
 ----------------------------------------------------------------------------
 ----------------------------------------------------------------------------
*/



/*
 --------------------------------------------------------------------------
 -- OCD - On-Chip Debug System
 --------------------------------------------------------------------------
*/
	
#define OCD_OCDR0	OCD.OCDR0	///< OCD Register 0
#define OCD_OCDR1	OCD.OCDR1	///< OCD Register 1

/*
 --------------------------------------------------------------------------
 -- CLK - Clock System
 --------------------------------------------------------------------------
*/
	
#define CLK_CTRL	CLK.CTRL	///< Control Register
#define CLK_PSCTRL	CLK.PSCTRL	///< Prescaler Control Register
#define CLK_LOCK	CLK.LOCK	///< Lock register
#define CLK_RTCCTRL	CLK.RTCCTRL	///< RTC Control Register

/*
 --------------------------------------------------------------------------
 -- SLEEP - Sleep Controller
 --------------------------------------------------------------------------
*/
	
#define SLEEP_CTRL	SLEEP.CTRL	///< Control Register

/*
 --------------------------------------------------------------------------
 -- OSC - Oscillator Control
 --------------------------------------------------------------------------
*/
	
#define OSC_CTRL	OSC.CTRL	///< Control Register
#define OSC_STATUS	OSC.STATUS	///< Status Register
#define OSC_XOSCCTRL	OSC.XOSCCTRL	///< External Oscillator Control Register
#define OSC_XOSCFAIL	OSC.XOSCFAIL	///< External Oscillator Failure Detection Register
#define OSC_RC32KCAL	OSC.RC32KCAL	///< 32kHz Internal Oscillator Calibration Register
#define OSC_PLLCTRL	OSC.PLLCTRL	///< PLL Control REgister
#define OSC_DFLLCTRL	OSC.DFLLCTRL	///< DFLL Control Register

/*
 --------------------------------------------------------------------------
 -- DFLLRC32M - DFLL for 32MHz RC Oscillator
 --------------------------------------------------------------------------
*/
	
#define DFLLRC32M_CTRL	DFLLRC32M.CTRL	///< Control Register
#define DFLLRC32M_CALA	DFLLRC32M.CALA	///< Calibration Register A
#define DFLLRC32M_CALB	DFLLRC32M.CALB	///< Calibration Register B
#define DFLLRC32M_COMP0	DFLLRC32M.COMP0	///< Oscillator Compare Register 0
#define DFLLRC32M_COMP1	DFLLRC32M.COMP1	///< Oscillator Compare Register 1
#define DFLLRC32M_COMP2	DFLLRC32M.COMP2	///< Oscillator Compare Register 2

/*
 --------------------------------------------------------------------------
 -- DFLLRC2M - DFLL for 2MHz RC Oscillator
 --------------------------------------------------------------------------
*/
	
#define DFLLRC2M_CTRL	DFLLRC2M.CTRL	///< Control Register
#define DFLLRC2M_CALA	DFLLRC2M.CALA	///< Calibration Register A
#define DFLLRC2M_CALB	DFLLRC2M.CALB	///< Calibration Register B
#define DFLLRC2M_COMP0	DFLLRC2M.COMP0	///< Oscillator Compare Register 0
#define DFLLRC2M_COMP1	DFLLRC2M.COMP1	///< Oscillator Compare Register 1
#define DFLLRC2M_COMP2	DFLLRC2M.COMP2	///< Oscillator Compare Register 2

/*
 --------------------------------------------------------------------------
 -- PR - Power Reduction
 --------------------------------------------------------------------------
*/
	
#define PR_PRGEN	PR.PRGEN	///< General Power Reduction
#define PR_PRPA	PR.PRPA	///< Power Reduction Port A
#define PR_PRPB	PR.PRPB	///< Power Reduction Port B
#define PR_PRPC	PR.PRPC	///< Power Reduction Port C
#define PR_PRPD	PR.PRPD	///< Power Reduction Port D
#define PR_PRPE	PR.PRPE	///< Power Reduction Port E
#define PR_PRPF	PR.PRPF	///< Power Reduction Port F

/*
 --------------------------------------------------------------------------
 -- RST - Reset Controller
 --------------------------------------------------------------------------
*/
	
#define RST_STATUS	RST.STATUS	///< Status Register
#define RST_CTRL	RST.CTRL	///< Control Register

/*
 --------------------------------------------------------------------------
 -- WDT - Watch-Dog Timer
 --------------------------------------------------------------------------
*/
	
#define WDT_CTRL	WDT.CTRL	///< Control
#define WDT_WINCTRL	WDT.WINCTRL	///< Windowed Mode Control
#define WDT_STATUS	WDT.STATUS	///< Status

/*
 --------------------------------------------------------------------------
 -- MCU - MCU Control
 --------------------------------------------------------------------------
*/
	
#define MCU_DEVID0	MCU.DEVID0	///< Device ID byte 0
#define MCU_DEVID1	MCU.DEVID1	///< Device ID byte 1
#define MCU_DEVID2	MCU.DEVID2	///< Device ID byte 2
#define MCU_REVID	MCU.REVID	///< Revision ID
#define MCU_JTAGUID	MCU.JTAGUID	///< JTAG User ID
#define MCU_MCUCR	MCU.MCUCR	///< MCU Control
#define MCU_EVSYSLOCK	MCU.EVSYSLOCK	///< Event System Lock
#define MCU_AWEXLOCK	MCU.AWEXLOCK	///< AWEX Lock

/*
 --------------------------------------------------------------------------
 -- PMIC - Programmable Interrupt Controller
 --------------------------------------------------------------------------
*/
	
#define PMIC_STATUS	PMIC.STATUS	///< Status Register
#define PMIC_INTPRI	PMIC.INTPRI	///< Interrupt Priority
#define PMIC_CTRL	PMIC.CTRL	///< Control Register

/*
 --------------------------------------------------------------------------
 -- DMA - DMA Controller
 --------------------------------------------------------------------------
*/
	
#define DMA_CTRL	DMA.CTRL	///< Control
#define DMA_INTFLAGS	DMA.INTFLAGS	///< Transfer Interrupt Status
#define DMA_STATUS	DMA.STATUS	///< Status
#define DMA_TEMP	DMA.TEMP	///< Temporary Register For 16/24-bit Access
#define DMA_CH0_CTRLA	DMA.CH0.CTRLA	///< Channel Control
#define DMA_CH0_CTRLB	DMA.CH0.CTRLB	///< Channel Control
#define DMA_CH0_ADDRCTRL	DMA.CH0.ADDRCTRL	///< Address Control
#define DMA_CH0_TRIGSRC	DMA.CH0.TRIGSRC	///< Channel Trigger Source
#define DMA_CH0_TRFCNT	DMA.CH0.TRFCNT	///< Channel Block Transfer Count
#define DMA_CH0_REPCNT	DMA.CH0.REPCNT	///< Channel Repeat Count
#define DMA_CH0_SRCADDR0	DMA.CH0.SRCADDR0	///< Channel Source Address 0
#define DMA_CH0_SRCADDR1	DMA.CH0.SRCADDR1	///< Channel Source Address 1
#define DMA_CH0_SRCADDR2	DMA.CH0.SRCADDR2	///< Channel Source Address 2
#define DMA_CH0_DESTADDR0	DMA.CH0.DESTADDR0	///< Channel Destination Address 0
#define DMA_CH0_DESTADDR1	DMA.CH0.DESTADDR1	///< Channel Destination Address 1
#define DMA_CH0_DESTADDR2	DMA.CH0.DESTADDR2	///< Channel Destination Address 2
#define DMA_CH1_CTRLA	DMA.CH1.CTRLA	///< Channel Control
#define DMA_CH1_CTRLB	DMA.CH1.CTRLB	///< Channel Control
#define DMA_CH1_ADDRCTRL	DMA.CH1.ADDRCTRL	///< Address Control
#define DMA_CH1_TRIGSRC	DMA.CH1.TRIGSRC	///< Channel Trigger Source
#define DMA_CH1_TRFCNT	DMA.CH1.TRFCNT	///< Channel Block Transfer Count
#define DMA_CH1_REPCNT	DMA.CH1.REPCNT	///< Channel Repeat Count
#define DMA_CH1_SRCADDR0	DMA.CH1.SRCADDR0	///< Channel Source Address 0
#define DMA_CH1_SRCADDR1	DMA.CH1.SRCADDR1	///< Channel Source Address 1
#define DMA_CH1_SRCADDR2	DMA.CH1.SRCADDR2	///< Channel Source Address 2
#define DMA_CH1_DESTADDR0	DMA.CH1.DESTADDR0	///< Channel Destination Address 0
#define DMA_CH1_DESTADDR1	DMA.CH1.DESTADDR1	///< Channel Destination Address 1
#define DMA_CH1_DESTADDR2	DMA.CH1.DESTADDR2	///< Channel Destination Address 2
#define DMA_CH2_CTRLA	DMA.CH2.CTRLA	///< Channel Control
#define DMA_CH2_CTRLB	DMA.CH2.CTRLB	///< Channel Control
#define DMA_CH2_ADDRCTRL	DMA.CH2.ADDRCTRL	///< Address Control
#define DMA_CH2_TRIGSRC	DMA.CH2.TRIGSRC	///< Channel Trigger Source
#define DMA_CH2_TRFCNT	DMA.CH2.TRFCNT	///< Channel Block Transfer Count
#define DMA_CH2_REPCNT	DMA.CH2.REPCNT	///< Channel Repeat Count
#define DMA_CH2_SRCADDR0	DMA.CH2.SRCADDR0	///< Channel Source Address 0
#define DMA_CH2_SRCADDR1	DMA.CH2.SRCADDR1	///< Channel Source Address 1
#define DMA_CH2_SRCADDR2	DMA.CH2.SRCADDR2	///< Channel Source Address 2
#define DMA_CH2_DESTADDR0	DMA.CH2.DESTADDR0	///< Channel Destination Address 0
#define DMA_CH2_DESTADDR1	DMA.CH2.DESTADDR1	///< Channel Destination Address 1
#define DMA_CH2_DESTADDR2	DMA.CH2.DESTADDR2	///< Channel Destination Address 2
#define DMA_CH3_CTRLA	DMA.CH3.CTRLA	///< Channel Control
#define DMA_CH3_CTRLB	DMA.CH3.CTRLB	///< Channel Control
#define DMA_CH3_ADDRCTRL	DMA.CH3.ADDRCTRL	///< Address Control
#define DMA_CH3_TRIGSRC	DMA.CH3.TRIGSRC	///< Channel Trigger Source
#define DMA_CH3_TRFCNT	DMA.CH3.TRFCNT	///< Channel Block Transfer Count
#define DMA_CH3_REPCNT	DMA.CH3.REPCNT	///< Channel Repeat Count
#define DMA_CH3_SRCADDR0	DMA.CH3.SRCADDR0	///< Channel Source Address 0
#define DMA_CH3_SRCADDR1	DMA.CH3.SRCADDR1	///< Channel Source Address 1
#define DMA_CH3_SRCADDR2	DMA.CH3.SRCADDR2	///< Channel Source Address 2
#define DMA_CH3_DESTADDR0	DMA.CH3.DESTADDR0	///< Channel Destination Address 0
#define DMA_CH3_DESTADDR1	DMA.CH3.DESTADDR1	///< Channel Destination Address 1
#define DMA_CH3_DESTADDR2	DMA.CH3.DESTADDR2	///< Channel Destination Address 2

/*
 --------------------------------------------------------------------------
 -- EVSYS - Event System
 --------------------------------------------------------------------------
*/
	
#define EVSYS_CH0MUX	EVSYS.CH0MUX	///< Event Channel 0 Multiplexer
#define EVSYS_CH1MUX	EVSYS.CH1MUX	///< Event Channel 1 Multiplexer
#define EVSYS_CH2MUX	EVSYS.CH2MUX	///< Event Channel 2 Multiplexer
#define EVSYS_CH3MUX	EVSYS.CH3MUX	///< Event Channel 3 Multiplexer
#define EVSYS_CH4MUX	EVSYS.CH4MUX	///< Event Channel 4 Multiplexer
#define EVSYS_CH5MUX	EVSYS.CH5MUX	///< Event Channel 5 Multiplexer
#define EVSYS_CH6MUX	EVSYS.CH6MUX	///< Event Channel 6 Multiplexer
#define EVSYS_CH7MUX	EVSYS.CH7MUX	///< Event Channel 7 Multiplexer
#define EVSYS_CH0CTRL	EVSYS.CH0CTRL	///< Channel 0 Control Register
#define EVSYS_CH1CTRL	EVSYS.CH1CTRL	///< Channel 1 Control Register
#define EVSYS_CH2CTRL	EVSYS.CH2CTRL	///< Channel 2 Control Register
#define EVSYS_CH3CTRL	EVSYS.CH3CTRL	///< Channel 3 Control Register
#define EVSYS_CH4CTRL	EVSYS.CH4CTRL	///< Channel 4 Control Register
#define EVSYS_CH5CTRL	EVSYS.CH5CTRL	///< Channel 5 Control Register
#define EVSYS_CH6CTRL	EVSYS.CH6CTRL	///< Channel 6 Control Register
#define EVSYS_CH7CTRL	EVSYS.CH7CTRL	///< Channel 7 Control Register
#define EVSYS_STROBE	EVSYS.STROBE	///< Event Strobe
#define EVSYS_DATA	EVSYS.DATA	///< Event Data

/*
 --------------------------------------------------------------------------
 -- NVM - Non Volatile Memory
 --------------------------------------------------------------------------
*/
	
#define NVM_ADDR0	NVM.ADDR0	///< Address Register 0
#define NVM_ADDR1	NVM.ADDR1	///< Address Register 1
#define NVM_ADDR2	NVM.ADDR2	///< Address Register 2
#define NVM_DATA0	NVM.DATA0	///< Data Register 0
#define NVM_DATA1	NVM.DATA1	///< Data Register 1
#define NVM_DATA2	NVM.DATA2	///< Data Register 2
#define NVM_CMD	NVM.CMD	///< Command
#define NVM_CTRLA	NVM.CTRLA	///< Control Register A
#define NVM_CTRLB	NVM.CTRLB	///< Control Register B
#define NVM_INTCTRL	NVM.INTCTRL	///< Interrupt Control
#define NVM_STATUS	NVM.STATUS	///< Status
#define NVM_LOCKBITS	NVM.LOCKBITS	///< Lock Bits

/*
 --------------------------------------------------------------------------
 -- ACA - Analog Comparator A
 --------------------------------------------------------------------------
*/
	
#define ACA_AC0CTRL	ACA.AC0CTRL	///< Comparator 0 Control
#define ACA_AC1CTRL	ACA.AC1CTRL	///< Comparator 1 Control
#define ACA_AC0MUXCTRL	ACA.AC0MUXCTRL	///< Comparator 0 MUX Control
#define ACA_AC1MUXCTRL	ACA.AC1MUXCTRL	///< Comparator 1 MUX Control
#define ACA_CTRLA	ACA.CTRLA	///< Control Register A
#define ACA_CTRLB	ACA.CTRLB	///< Control Register B
#define ACA_WINCTRL	ACA.WINCTRL	///< Window Mode Control
#define ACA_STATUS	ACA.STATUS	///< Status

/*
 --------------------------------------------------------------------------
 -- ADCA - Analog to Digital Converter A
 --------------------------------------------------------------------------
*/
	
#define ADCA_CTRLA	ADCA.CTRLA	///< Control Register A
#define ADCA_CTRLB	ADCA.CTRLB	///< Control Register B
#define ADCA_REFCTRL	ADCA.REFCTRL	///< Reference Control
#define ADCA_EVCTRL	ADCA.EVCTRL	///< Event Control
#define ADCA_PRESCALER	ADCA.PRESCALER	///< Clock Prescaler
#define ADCA_INTFLAGS	ADCA.INTFLAGS	///< Interrupt Flags
#define ADCA_TEMP	ADCA.TEMP	///< Temporary register
#define ADCA_CAL	ADCA.CAL	///< Calibration Value
#define ADCA_CH0RES	ADCA.CH0RES	///< Channel 0 Result
#define ADCA_CH1RES	ADCA.CH1RES	///< Channel 1 Result
#define ADCA_CH2RES	ADCA.CH2RES	///< Channel 2 Result
#define ADCA_CH3RES	ADCA.CH3RES	///< Channel 3 Result
#define ADCA_CMP	ADCA.CMP	///< Compare Value
#define ADCA_CH0_CTRL	ADCA.CH0.CTRL	///< Control Register
#define ADCA_CH0_MUXCTRL	ADCA.CH0.MUXCTRL	///< MUX Control
#define ADCA_CH0_INTCTRL	ADCA.CH0.INTCTRL	///< Channel Interrupt Control
#define ADCA_CH0_INTFLAGS	ADCA.CH0.INTFLAGS	///< Interrupt Flags
#define ADCA_CH0_RES	ADCA.CH0.RES	///< Channel Result
#define ADCA_CH1_CTRL	ADCA.CH1.CTRL	///< Control Register
#define ADCA_CH1_MUXCTRL	ADCA.CH1.MUXCTRL	///< MUX Control
#define ADCA_CH1_INTCTRL	ADCA.CH1.INTCTRL	///< Channel Interrupt Control
#define ADCA_CH1_INTFLAGS	ADCA.CH1.INTFLAGS	///< Interrupt Flags
#define ADCA_CH1_RES	ADCA.CH1.RES	///< Channel Result
#define ADCA_CH2_CTRL	ADCA.CH2.CTRL	///< Control Register
#define ADCA_CH2_MUXCTRL	ADCA.CH2.MUXCTRL	///< MUX Control
#define ADCA_CH2_INTCTRL	ADCA.CH2.INTCTRL	///< Channel Interrupt Control
#define ADCA_CH2_INTFLAGS	ADCA.CH2.INTFLAGS	///< Interrupt Flags
#define ADCA_CH2_RES	ADCA.CH2.RES	///< Channel Result
#define ADCA_CH3_CTRL	ADCA.CH3.CTRL	///< Control Register
#define ADCA_CH3_MUXCTRL	ADCA.CH3.MUXCTRL	///< MUX Control
#define ADCA_CH3_INTCTRL	ADCA.CH3.INTCTRL	///< Channel Interrupt Control
#define ADCA_CH3_INTFLAGS	ADCA.CH3.INTFLAGS	///< Interrupt Flags
#define ADCA_CH3_RES	ADCA.CH3.RES	///< Channel Result

/*
 --------------------------------------------------------------------------
 -- DACB - Digital to Analog Converter B
 --------------------------------------------------------------------------
*/
	
#define DACB_CTRLA	DACB.CTRLA	///< Control Register A
#define DACB_CTRLB	DACB.CTRLB	///< Control Register B
#define DACB_CTRLC	DACB.CTRLC	///< Control Register C
#define DACB_EVCTRL	DACB.EVCTRL	///< Event Input Control
#define DACB_TIMCTRL	DACB.TIMCTRL	///< Timing Control
#define DACB_STATUS	DACB.STATUS	///< Status
#define DACB_GAINCAL	DACB.GAINCAL	///< Gain Calibration
#define DACB_OFFSETCAL	DACB.OFFSETCAL	///< Offset Calibration
#define DACB_CH0DATA	DACB.CH0DATA	///< Channel 0 Data
#define DACB_CH1DATA	DACB.CH1DATA	///< Channel 1 Data

/*
 --------------------------------------------------------------------------
 -- RTC - Real-Time Counter
 --------------------------------------------------------------------------
*/
	
#define RTC_CTRL	RTC.CTRL	///< Control Register
#define RTC_STATUS	RTC.STATUS	///< Status Register
#define RTC_INTCTRL	RTC.INTCTRL	///< Interrupt Control Register
#define RTC_INTFLAGS	RTC.INTFLAGS	///< Interrupt Flags
#define RTC_TEMP	RTC.TEMP	///< Temporary register
#define RTC_CNT	RTC.CNT	///< Count Register
#define RTC_PER	RTC.PER	///< Period Register
#define RTC_COMP	RTC.COMP	///< Compare Register

/*
 --------------------------------------------------------------------------
 -- TWIC - Two-Wire Interface C
 --------------------------------------------------------------------------
*/
	
#define TWIC_CTRL	TWIC.CTRL	///< TWI Common Control Register
#define TWIC_MASTER_CTRLA	TWIC.MASTER.CTRLA	///< Control Register A
#define TWIC_MASTER_CTRLB	TWIC.MASTER.CTRLB	///< Control Register B
#define TWIC_MASTER_CTRLC	TWIC.MASTER.CTRLC	///< Control Register C
#define TWIC_MASTER_STATUS	TWIC.MASTER.STATUS	///< Status Register
#define TWIC_MASTER_BAUD	TWIC.MASTER.BAUD	///< Baurd Rate Control Register
#define TWIC_MASTER_ADDR	TWIC.MASTER.ADDR	///< Address Register
#define TWIC_MASTER_DATA	TWIC.MASTER.DATA	///< Data Register
#define TWIC_SLAVE_CTRLA	TWIC.SLAVE.CTRLA	///< Control Register A
#define TWIC_SLAVE_CTRLB	TWIC.SLAVE.CTRLB	///< Control Register B
#define TWIC_SLAVE_STATUS	TWIC.SLAVE.STATUS	///< Status Register
#define TWIC_SLAVE_ADDR	TWIC.SLAVE.ADDR	///< Address Register
#define TWIC_SLAVE_DATA	TWIC.SLAVE.DATA	///< Data Register
#define TWIC_SLAVE_ADDRMASK	TWIC.SLAVE.ADDRMASK	///< Address Mask Register

/*
 --------------------------------------------------------------------------
 -- TWIE - Two-Wire Interface E
 --------------------------------------------------------------------------
*/
	
#define TWIE_CTRL	TWIE.CTRL	///< TWI Common Control Register
#define TWIE_MASTER_CTRLA	TWIE.MASTER.CTRLA	///< Control Register A
#define TWIE_MASTER_CTRLB	TWIE.MASTER.CTRLB	///< Control Register B
#define TWIE_MASTER_CTRLC	TWIE.MASTER.CTRLC	///< Control Register C
#define TWIE_MASTER_STATUS	TWIE.MASTER.STATUS	///< Status Register
#define TWIE_MASTER_BAUD	TWIE.MASTER.BAUD	///< Baurd Rate Control Register
#define TWIE_MASTER_ADDR	TWIE.MASTER.ADDR	///< Address Register
#define TWIE_MASTER_DATA	TWIE.MASTER.DATA	///< Data Register
#define TWIE_SLAVE_CTRLA	TWIE.SLAVE.CTRLA	///< Control Register A
#define TWIE_SLAVE_CTRLB	TWIE.SLAVE.CTRLB	///< Control Register B
#define TWIE_SLAVE_STATUS	TWIE.SLAVE.STATUS	///< Status Register
#define TWIE_SLAVE_ADDR	TWIE.SLAVE.ADDR	///< Address Register
#define TWIE_SLAVE_DATA	TWIE.SLAVE.DATA	///< Data Register
#define TWIE_SLAVE_ADDRMASK	TWIE.SLAVE.ADDRMASK	///< Address Mask Register

/*
 --------------------------------------------------------------------------
 -- PORT_CFG - Port Configuration
 --------------------------------------------------------------------------
*/
	
#define PORTCFG_MPCMASK	PORTCFG.MPCMASK	///< Multi-pin Configuration Mask
#define PORTCFG_VPCTRLA	PORTCFG.VPCTRLA	///< Virtual Port Control Register A
#define PORTCFG_VPCTRLB	PORTCFG.VPCTRLB	///< Virtual Port Control Register B
#define PORTCFG_CLKEVOUT	PORTCFG.CLKEVOUT	///< Clock and Event Out Register

/*
 --------------------------------------------------------------------------
 -- VPORT0 - Virtual Port 0
 --------------------------------------------------------------------------
*/
	
#define VPORT0_DIR	VPORT0.DIR	///< I/O Port Data Direction
#define VPORT0_OUT	VPORT0.OUT	///< I/O Port Output
#define VPORT0_IN	VPORT0.IN	///< I/O Port Input
#define VPORT0_INTFLAGS	VPORT0.INTFLAGS	///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- VPORT1 - Virtual Port 1
 --------------------------------------------------------------------------
*/
	
#define VPORT1_DIR	VPORT1.DIR	///< I/O Port Data Direction
#define VPORT1_OUT	VPORT1.OUT	///< I/O Port Output
#define VPORT1_IN	VPORT1.IN	///< I/O Port Input
#define VPORT1_INTFLAGS	VPORT1.INTFLAGS	///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- VPORT2 - Virtual Port 2
 --------------------------------------------------------------------------
*/
	
#define VPORT2_DIR	VPORT2.DIR	///< I/O Port Data Direction
#define VPORT2_OUT	VPORT2.OUT	///< I/O Port Output
#define VPORT2_IN	VPORT2.IN	///< I/O Port Input
#define VPORT2_INTFLAGS	VPORT2.INTFLAGS	///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- VPORT3 - Virtual Port 3
 --------------------------------------------------------------------------
*/
	
#define VPORT3_DIR	VPORT3.DIR	///< I/O Port Data Direction
#define VPORT3_OUT	VPORT3.OUT	///< I/O Port Output
#define VPORT3_IN	VPORT3.IN	///< I/O Port Input
#define VPORT3_INTFLAGS	VPORT3.INTFLAGS	///< Interrupt Flag Register

/*
 --------------------------------------------------------------------------
 -- PORTA - Port A
 --------------------------------------------------------------------------
*/
	
#define PORTA_DIR	PORTA.DIR	///< I/O Port Data Direction
#define PORTA_DIRSET	PORTA.DIRSET	///< I/O Port Data Direction Set
#define PORTA_DIRCLR	PORTA.DIRCLR	///< I/O Port Data Direction Clear
#define PORTA_DIRTGL	PORTA.DIRTGL	///< I/O Port Data Direction Toggle
#define PORTA_OUT	PORTA.OUT	///< I/O Port Output
#define PORTA_OUTSET	PORTA.OUTSET	///< I/O Port Output Set
#define PORTA_OUTCLR	PORTA.OUTCLR	///< I/O Port Output Clear
#define PORTA_OUTTGL	PORTA.OUTTGL	///< I/O Port Output Toggle
#define PORTA_IN	PORTA.IN	///< I/O port Input
#define PORTA_INTCTRL	PORTA.INTCTRL	///< Interrupt Control Register
#define PORTA_INT0MASK	PORTA.INT0MASK	///< Port Interrupt 0 Mask
#define PORTA_INT1MASK	PORTA.INT1MASK	///< Port Interrupt 1 Mask
#define PORTA_INTFLAGS	PORTA.INTFLAGS	///< Interrupt Flag Register
#define PORTA_PIN0CTRL	PORTA.PIN0CTRL	///< Pin 0 Control Register
#define PORTA_PIN1CTRL	PORTA.PIN1CTRL	///< Pin 1 Control Register
#define PORTA_PIN2CTRL	PORTA.PIN2CTRL	///< Pin 2 Control Register
#define PORTA_PIN3CTRL	PORTA.PIN3CTRL	///< Pin 3 Control Register
#define PORTA_PIN4CTRL	PORTA.PIN4CTRL	///< Pin 4 Control Register
#define PORTA_PIN5CTRL	PORTA.PIN5CTRL	///< Pin 5 Control Register
#define PORTA_PIN6CTRL	PORTA.PIN6CTRL	///< Pin 6 Control Register
#define PORTA_PIN7CTRL	PORTA.PIN7CTRL	///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTB - Port B
 --------------------------------------------------------------------------
*/
	
#define PORTB_DIR	PORTB.DIR	///< I/O Port Data Direction
#define PORTB_DIRSET	PORTB.DIRSET	///< I/O Port Data Direction Set
#define PORTB_DIRCLR	PORTB.DIRCLR	///< I/O Port Data Direction Clear
#define PORTB_DIRTGL	PORTB.DIRTGL	///< I/O Port Data Direction Toggle
#define PORTB_OUT	PORTB.OUT	///< I/O Port Output
#define PORTB_OUTSET	PORTB.OUTSET	///< I/O Port Output Set
#define PORTB_OUTCLR	PORTB.OUTCLR	///< I/O Port Output Clear
#define PORTB_OUTTGL	PORTB.OUTTGL	///< I/O Port Output Toggle
#define PORTB_IN	PORTB.IN	///< I/O port Input
#define PORTB_INTCTRL	PORTB.INTCTRL	///< Interrupt Control Register
#define PORTB_INT0MASK	PORTB.INT0MASK	///< Port Interrupt 0 Mask
#define PORTB_INT1MASK	PORTB.INT1MASK	///< Port Interrupt 1 Mask
#define PORTB_INTFLAGS	PORTB.INTFLAGS	///< Interrupt Flag Register
#define PORTB_PIN0CTRL	PORTB.PIN0CTRL	///< Pin 0 Control Register
#define PORTB_PIN1CTRL	PORTB.PIN1CTRL	///< Pin 1 Control Register
#define PORTB_PIN2CTRL	PORTB.PIN2CTRL	///< Pin 2 Control Register
#define PORTB_PIN3CTRL	PORTB.PIN3CTRL	///< Pin 3 Control Register
#define PORTB_PIN4CTRL	PORTB.PIN4CTRL	///< Pin 4 Control Register
#define PORTB_PIN5CTRL	PORTB.PIN5CTRL	///< Pin 5 Control Register
#define PORTB_PIN6CTRL	PORTB.PIN6CTRL	///< Pin 6 Control Register
#define PORTB_PIN7CTRL	PORTB.PIN7CTRL	///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTC - Port C
 --------------------------------------------------------------------------
*/
	
#define PORTC_DIR	PORTC.DIR	///< I/O Port Data Direction
#define PORTC_DIRSET	PORTC.DIRSET	///< I/O Port Data Direction Set
#define PORTC_DIRCLR	PORTC.DIRCLR	///< I/O Port Data Direction Clear
#define PORTC_DIRTGL	PORTC.DIRTGL	///< I/O Port Data Direction Toggle
#define PORTC_OUT	PORTC.OUT	///< I/O Port Output
#define PORTC_OUTSET	PORTC.OUTSET	///< I/O Port Output Set
#define PORTC_OUTCLR	PORTC.OUTCLR	///< I/O Port Output Clear
#define PORTC_OUTTGL	PORTC.OUTTGL	///< I/O Port Output Toggle
#define PORTC_IN	PORTC.IN	///< I/O port Input
#define PORTC_INTCTRL	PORTC.INTCTRL	///< Interrupt Control Register
#define PORTC_INT0MASK	PORTC.INT0MASK	///< Port Interrupt 0 Mask
#define PORTC_INT1MASK	PORTC.INT1MASK	///< Port Interrupt 1 Mask
#define PORTC_INTFLAGS	PORTC.INTFLAGS	///< Interrupt Flag Register
#define PORTC_PIN0CTRL	PORTC.PIN0CTRL	///< Pin 0 Control Register
#define PORTC_PIN1CTRL	PORTC.PIN1CTRL	///< Pin 1 Control Register
#define PORTC_PIN2CTRL	PORTC.PIN2CTRL	///< Pin 2 Control Register
#define PORTC_PIN3CTRL	PORTC.PIN3CTRL	///< Pin 3 Control Register
#define PORTC_PIN4CTRL	PORTC.PIN4CTRL	///< Pin 4 Control Register
#define PORTC_PIN5CTRL	PORTC.PIN5CTRL	///< Pin 5 Control Register
#define PORTC_PIN6CTRL	PORTC.PIN6CTRL	///< Pin 6 Control Register
#define PORTC_PIN7CTRL	PORTC.PIN7CTRL	///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTD - Port D
 --------------------------------------------------------------------------
*/
	
#define PORTD_DIR	PORTD.DIR	///< I/O Port Data Direction
#define PORTD_DIRSET	PORTD.DIRSET	///< I/O Port Data Direction Set
#define PORTD_DIRCLR	PORTD.DIRCLR	///< I/O Port Data Direction Clear
#define PORTD_DIRTGL	PORTD.DIRTGL	///< I/O Port Data Direction Toggle
#define PORTD_OUT	PORTD.OUT	///< I/O Port Output
#define PORTD_OUTSET	PORTD.OUTSET	///< I/O Port Output Set
#define PORTD_OUTCLR	PORTD.OUTCLR	///< I/O Port Output Clear
#define PORTD_OUTTGL	PORTD.OUTTGL	///< I/O Port Output Toggle
#define PORTD_IN	PORTD.IN	///< I/O port Input
#define PORTD_INTCTRL	PORTD.INTCTRL	///< Interrupt Control Register
#define PORTD_INT0MASK	PORTD.INT0MASK	///< Port Interrupt 0 Mask
#define PORTD_INT1MASK	PORTD.INT1MASK	///< Port Interrupt 1 Mask
#define PORTD_INTFLAGS	PORTD.INTFLAGS	///< Interrupt Flag Register
#define PORTD_PIN0CTRL	PORTD.PIN0CTRL	///< Pin 0 Control Register
#define PORTD_PIN1CTRL	PORTD.PIN1CTRL	///< Pin 1 Control Register
#define PORTD_PIN2CTRL	PORTD.PIN2CTRL	///< Pin 2 Control Register
#define PORTD_PIN3CTRL	PORTD.PIN3CTRL	///< Pin 3 Control Register
#define PORTD_PIN4CTRL	PORTD.PIN4CTRL	///< Pin 4 Control Register
#define PORTD_PIN5CTRL	PORTD.PIN5CTRL	///< Pin 5 Control Register
#define PORTD_PIN6CTRL	PORTD.PIN6CTRL	///< Pin 6 Control Register
#define PORTD_PIN7CTRL	PORTD.PIN7CTRL	///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTE - Port E
 --------------------------------------------------------------------------
*/
	
#define PORTE_DIR	PORTE.DIR	///< I/O Port Data Direction
#define PORTE_DIRSET	PORTE.DIRSET	///< I/O Port Data Direction Set
#define PORTE_DIRCLR	PORTE.DIRCLR	///< I/O Port Data Direction Clear
#define PORTE_DIRTGL	PORTE.DIRTGL	///< I/O Port Data Direction Toggle
#define PORTE_OUT	PORTE.OUT	///< I/O Port Output
#define PORTE_OUTSET	PORTE.OUTSET	///< I/O Port Output Set
#define PORTE_OUTCLR	PORTE.OUTCLR	///< I/O Port Output Clear
#define PORTE_OUTTGL	PORTE.OUTTGL	///< I/O Port Output Toggle
#define PORTE_IN	PORTE.IN	///< I/O port Input
#define PORTE_INTCTRL	PORTE.INTCTRL	///< Interrupt Control Register
#define PORTE_INT0MASK	PORTE.INT0MASK	///< Port Interrupt 0 Mask
#define PORTE_INT1MASK	PORTE.INT1MASK	///< Port Interrupt 1 Mask
#define PORTE_INTFLAGS	PORTE.INTFLAGS	///< Interrupt Flag Register
#define PORTE_PIN0CTRL	PORTE.PIN0CTRL	///< Pin 0 Control Register
#define PORTE_PIN1CTRL	PORTE.PIN1CTRL	///< Pin 1 Control Register
#define PORTE_PIN2CTRL	PORTE.PIN2CTRL	///< Pin 2 Control Register
#define PORTE_PIN3CTRL	PORTE.PIN3CTRL	///< Pin 3 Control Register
#define PORTE_PIN4CTRL	PORTE.PIN4CTRL	///< Pin 4 Control Register
#define PORTE_PIN5CTRL	PORTE.PIN5CTRL	///< Pin 5 Control Register
#define PORTE_PIN6CTRL	PORTE.PIN6CTRL	///< Pin 6 Control Register
#define PORTE_PIN7CTRL	PORTE.PIN7CTRL	///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- PORTR - Port R
 --------------------------------------------------------------------------
*/
	
#define PORTR_DIR	PORTR.DIR	///< I/O Port Data Direction
#define PORTR_DIRSET	PORTR.DIRSET	///< I/O Port Data Direction Set
#define PORTR_DIRCLR	PORTR.DIRCLR	///< I/O Port Data Direction Clear
#define PORTR_DIRTGL	PORTR.DIRTGL	///< I/O Port Data Direction Toggle
#define PORTR_OUT	PORTR.OUT	///< I/O Port Output
#define PORTR_OUTSET	PORTR.OUTSET	///< I/O Port Output Set
#define PORTR_OUTCLR	PORTR.OUTCLR	///< I/O Port Output Clear
#define PORTR_OUTTGL	PORTR.OUTTGL	///< I/O Port Output Toggle
#define PORTR_IN	PORTR.IN	///< I/O port Input
#define PORTR_INTCTRL	PORTR.INTCTRL	///< Interrupt Control Register
#define PORTR_INT0MASK	PORTR.INT0MASK	///< Port Interrupt 0 Mask
#define PORTR_INT1MASK	PORTR.INT1MASK	///< Port Interrupt 1 Mask
#define PORTR_INTFLAGS	PORTR.INTFLAGS	///< Interrupt Flag Register
#define PORTR_PIN0CTRL	PORTR.PIN0CTRL	///< Pin 0 Control Register
#define PORTR_PIN1CTRL	PORTR.PIN1CTRL	///< Pin 1 Control Register
#define PORTR_PIN2CTRL	PORTR.PIN2CTRL	///< Pin 2 Control Register
#define PORTR_PIN3CTRL	PORTR.PIN3CTRL	///< Pin 3 Control Register
#define PORTR_PIN4CTRL	PORTR.PIN4CTRL	///< Pin 4 Control Register
#define PORTR_PIN5CTRL	PORTR.PIN5CTRL	///< Pin 5 Control Register
#define PORTR_PIN6CTRL	PORTR.PIN6CTRL	///< Pin 6 Control Register
#define PORTR_PIN7CTRL	PORTR.PIN7CTRL	///< Pin 7 Control Register

/*
 --------------------------------------------------------------------------
 -- TCC0 - Timer/Counter C0
 --------------------------------------------------------------------------
*/
	
#define TCC0_CTRLA	TCC0.CTRLA	///< Control  Register A
#define TCC0_CTRLB	TCC0.CTRLB	///< Control Register B
#define TCC0_CTRLC	TCC0.CTRLC	///< Control register C
#define TCC0_CTRLD	TCC0.CTRLD	///< Control Register D
#define TCC0_CTRLE	TCC0.CTRLE	///< Control Register E
#define TCC0_INTCTRLA	TCC0.INTCTRLA	///< Interrupt Control Register A
#define TCC0_INTCTRLB	TCC0.INTCTRLB	///< Interrupt Control Register B
#define TCC0_CTRLFCLR	TCC0.CTRLFCLR	///< Control Register F Clear
#define TCC0_CTRLFSET	TCC0.CTRLFSET	///< Control Register F Set
#define TCC0_CTRLGCLR	TCC0.CTRLGCLR	///< Control Register G Clear
#define TCC0_CTRLGSET	TCC0.CTRLGSET	///< Control Register G Set
#define TCC0_INTFLAGS	TCC0.INTFLAGS	///< Interrupt Flag Register
#define TCC0_TEMP	TCC0.TEMP	///< Temporary Register For 16-bit Access
#define TCC0_CNT	TCC0.CNT	///< Count
#define TCC0_PER	TCC0.PER	///< Period
#define TCC0_CCA	TCC0.CCA	///< Compare or Capture A
#define TCC0_CCB	TCC0.CCB	///< Compare or Capture B
#define TCC0_CCC	TCC0.CCC	///< Compare or Capture C
#define TCC0_CCD	TCC0.CCD	///< Compare or Capture D
#define TCC0_PERBUF	TCC0.PERBUF	///< Period Buffer
#define TCC0_CCABUF	TCC0.CCABUF	///< Compare Or Capture A Buffer
#define TCC0_CCBBUF	TCC0.CCBBUF	///< Compare Or Capture B Buffer
#define TCC0_CCCBUF	TCC0.CCCBUF	///< Compare Or Capture C Buffer
#define TCC0_CCDBUF	TCC0.CCDBUF	///< Compare Or Capture D Buffer

/*
 --------------------------------------------------------------------------
 -- TCC1 - Timer/Counter C1
 --------------------------------------------------------------------------
*/
	
#define TCC1_CTRLA	TCC1.CTRLA	///< Control  Register A
#define TCC1_CTRLB	TCC1.CTRLB	///< Control Register B
#define TCC1_CTRLC	TCC1.CTRLC	///< Control register C
#define TCC1_CTRLD	TCC1.CTRLD	///< Control Register D
#define TCC1_CTRLE	TCC1.CTRLE	///< Control Register E
#define TCC1_INTCTRLA	TCC1.INTCTRLA	///< Interrupt Control Register A
#define TCC1_INTCTRLB	TCC1.INTCTRLB	///< Interrupt Control Register B
#define TCC1_CTRLFCLR	TCC1.CTRLFCLR	///< Control Register F Clear
#define TCC1_CTRLFSET	TCC1.CTRLFSET	///< Control Register F Set
#define TCC1_CTRLGCLR	TCC1.CTRLGCLR	///< Control Register G Clear
#define TCC1_CTRLGSET	TCC1.CTRLGSET	///< Control Register G Set
#define TCC1_INTFLAGS	TCC1.INTFLAGS	///< Interrupt Flag Register
#define TCC1_TEMP	TCC1.TEMP	///< Temporary Register For 16-bit Access
#define TCC1_CNT	TCC1.CNT	///< Count
#define TCC1_PER	TCC1.PER	///< Period
#define TCC1_CCA	TCC1.CCA	///< Compare or Capture A
#define TCC1_CCB	TCC1.CCB	///< Compare or Capture B
#define TCC1_PERBUF	TCC1.PERBUF	///< Period Buffer
#define TCC1_CCABUF	TCC1.CCABUF	///< Compare Or Capture A Buffer
#define TCC1_CCBBUF	TCC1.CCBBUF	///< Compare Or Capture B Buffer

/*
 --------------------------------------------------------------------------
 -- AWEXC - Advanced Waveform Extension C
 --------------------------------------------------------------------------
*/
	
#define AWEXC_CTRL	AWEXC.CTRL	///< Control Register
#define AWEXC_FDEMASK	AWEXC.FDEMASK	///< Fault Detection Event Mask
#define AWEXC_FDCTRL	AWEXC.FDCTRL	///< Fault Detection Control Register
#define AWEXC_STATUS	AWEXC.STATUS	///< Status Register
#define AWEXC_DTBOTH	AWEXC.DTBOTH	///< Dead Time Both Sides
#define AWEXC_DTBOTHBUF	AWEXC.DTBOTHBUF	///< Dead Time Both Sides Buffer
#define AWEXC_DTLS	AWEXC.DTLS	///< Dead Time Low Side
#define AWEXC_DTHS	AWEXC.DTHS	///< Dead Time High Side
#define AWEXC_DTLSBUF	AWEXC.DTLSBUF	///< Dead Time Low Side Buffer
#define AWEXC_DTHSBUF	AWEXC.DTHSBUF	///< Dead Time High Side Buffer
#define AWEXC_OUTOVEN	AWEXC.OUTOVEN	///< Output Override Enable

/*
 --------------------------------------------------------------------------
 -- HIRESC - High-Resolution Extension C
 --------------------------------------------------------------------------
*/
	
#define HIRESC_CTRLA	HIRESC.CTRLA	///< Control Register

/*
 --------------------------------------------------------------------------
 -- USARTC0 - Universal Asynchronous Receiver-Transmitter C0
 --------------------------------------------------------------------------
*/
	
#define USARTC0_DATA	USARTC0.DATA	///< Data Register
#define USARTC0_STATUS	USARTC0.STATUS	///< Status Register
#define USARTC0_CTRLA	USARTC0.CTRLA	///< Control Register A
#define USARTC0_CTRLB	USARTC0.CTRLB	///< Control Register B
#define USARTC0_CTRLC	USARTC0.CTRLC	///< Control Register C
#define USARTC0_BAUDCTRLA	USARTC0.BAUDCTRLA	///< Baud Rate Control Register A
#define USARTC0_BAUDCTRLB	USARTC0.BAUDCTRLB	///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- USARTC1 - Universal Asynchronous Receiver-Transmitter C1
 --------------------------------------------------------------------------
*/
	
#define USARTC1_DATA	USARTC1.DATA	///< Data Register
#define USARTC1_STATUS	USARTC1.STATUS	///< Status Register
#define USARTC1_CTRLA	USARTC1.CTRLA	///< Control Register A
#define USARTC1_CTRLB	USARTC1.CTRLB	///< Control Register B
#define USARTC1_CTRLC	USARTC1.CTRLC	///< Control Register C
#define USARTC1_BAUDCTRLA	USARTC1.BAUDCTRLA	///< Baud Rate Control Register A
#define USARTC1_BAUDCTRLB	USARTC1.BAUDCTRLB	///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- SPIC - Serial Peripheral Interface C
 --------------------------------------------------------------------------
*/
	
#define SPIC_CTRL	SPIC.CTRL	///< Control Register
#define SPIC_INTCTRL	SPIC.INTCTRL	///< Interrupt Control Register
#define SPIC_STATUS	SPIC.STATUS	///< Status Register
#define SPIC_DATA	SPIC.DATA	///< Data Register

/*
 --------------------------------------------------------------------------
 -- TCD0 - Timer/Counter D0
 --------------------------------------------------------------------------
*/
	
#define TCD0_CTRLA	TCD0.CTRLA	///< Control  Register A
#define TCD0_CTRLB	TCD0.CTRLB	///< Control Register B
#define TCD0_CTRLC	TCD0.CTRLC	///< Control register C
#define TCD0_CTRLD	TCD0.CTRLD	///< Control Register D
#define TCD0_CTRLE	TCD0.CTRLE	///< Control Register E
#define TCD0_INTCTRLA	TCD0.INTCTRLA	///< Interrupt Control Register A
#define TCD0_INTCTRLB	TCD0.INTCTRLB	///< Interrupt Control Register B
#define TCD0_CTRLFCLR	TCD0.CTRLFCLR	///< Control Register F Clear
#define TCD0_CTRLFSET	TCD0.CTRLFSET	///< Control Register F Set
#define TCD0_CTRLGCLR	TCD0.CTRLGCLR	///< Control Register G Clear
#define TCD0_CTRLGSET	TCD0.CTRLGSET	///< Control Register G Set
#define TCD0_INTFLAGS	TCD0.INTFLAGS	///< Interrupt Flag Register
#define TCD0_TEMP	TCD0.TEMP	///< Temporary Register For 16-bit Access
#define TCD0_CNT	TCD0.CNT	///< Count
#define TCD0_PER	TCD0.PER	///< Period
#define TCD0_CCA	TCD0.CCA	///< Compare or Capture A
#define TCD0_CCB	TCD0.CCB	///< Compare or Capture B
#define TCD0_CCC	TCD0.CCC	///< Compare or Capture C
#define TCD0_CCD	TCD0.CCD	///< Compare or Capture D
#define TCD0_PERBUF	TCD0.PERBUF	///< Period Buffer
#define TCD0_CCABUF	TCD0.CCABUF	///< Compare Or Capture A Buffer
#define TCD0_CCBBUF	TCD0.CCBBUF	///< Compare Or Capture B Buffer
#define TCD0_CCCBUF	TCD0.CCCBUF	///< Compare Or Capture C Buffer
#define TCD0_CCDBUF	TCD0.CCDBUF	///< Compare Or Capture D Buffer

/*
 --------------------------------------------------------------------------
 -- TCD1 - Timer/Counter D1
 --------------------------------------------------------------------------
*/
	
#define TCD1_CTRLA	TCD1.CTRLA	///< Control  Register A
#define TCD1_CTRLB	TCD1.CTRLB	///< Control Register B
#define TCD1_CTRLC	TCD1.CTRLC	///< Control register C
#define TCD1_CTRLD	TCD1.CTRLD	///< Control Register D
#define TCD1_CTRLE	TCD1.CTRLE	///< Control Register E
#define TCD1_INTCTRLA	TCD1.INTCTRLA	///< Interrupt Control Register A
#define TCD1_INTCTRLB	TCD1.INTCTRLB	///< Interrupt Control Register B
#define TCD1_CTRLFCLR	TCD1.CTRLFCLR	///< Control Register F Clear
#define TCD1_CTRLFSET	TCD1.CTRLFSET	///< Control Register F Set
#define TCD1_CTRLGCLR	TCD1.CTRLGCLR	///< Control Register G Clear
#define TCD1_CTRLGSET	TCD1.CTRLGSET	///< Control Register G Set
#define TCD1_INTFLAGS	TCD1.INTFLAGS	///< Interrupt Flag Register
#define TCD1_TEMP	TCD1.TEMP	///< Temporary Register For 16-bit Access
#define TCD1_CNT	TCD1.CNT	///< Count
#define TCD1_PER	TCD1.PER	///< Period
#define TCD1_CCA	TCD1.CCA	///< Compare or Capture A
#define TCD1_CCB	TCD1.CCB	///< Compare or Capture B
#define TCD1_PERBUF	TCD1.PERBUF	///< Period Buffer
#define TCD1_CCABUF	TCD1.CCABUF	///< Compare Or Capture A Buffer
#define TCD1_CCBBUF	TCD1.CCBBUF	///< Compare Or Capture B Buffer

/*
 --------------------------------------------------------------------------
 -- HIRESD - High-Resolution Extension D
 --------------------------------------------------------------------------
*/
	
#define HIRESD_CTRLA	HIRESD.CTRLA	///< Control Register

/*
 --------------------------------------------------------------------------
 -- USARTD0 - Universal Asynchronous Receiver-Transmitter D0
 --------------------------------------------------------------------------
*/
	
#define USARTD0_DATA	USARTD0.DATA	///< Data Register
#define USARTD0_STATUS	USARTD0.STATUS	///< Status Register
#define USARTD0_CTRLA	USARTD0.CTRLA	///< Control Register A
#define USARTD0_CTRLB	USARTD0.CTRLB	///< Control Register B
#define USARTD0_CTRLC	USARTD0.CTRLC	///< Control Register C
#define USARTD0_BAUDCTRLA	USARTD0.BAUDCTRLA	///< Baud Rate Control Register A
#define USARTD0_BAUDCTRLB	USARTD0.BAUDCTRLB	///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- USARTD1 - Universal Asynchronous Receiver-Transmitter D1
 --------------------------------------------------------------------------
*/
	
#define USARTD1_DATA	USARTD1.DATA	///< Data Register
#define USARTD1_STATUS	USARTD1.STATUS	///< Status Register
#define USARTD1_CTRLA	USARTD1.CTRLA	///< Control Register A
#define USARTD1_CTRLB	USARTD1.CTRLB	///< Control Register B
#define USARTD1_CTRLC	USARTD1.CTRLC	///< Control Register C
#define USARTD1_BAUDCTRLA	USARTD1.BAUDCTRLA	///< Baud Rate Control Register A
#define USARTD1_BAUDCTRLB	USARTD1.BAUDCTRLB	///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- SPID - Serial Peripheral Interface D
 --------------------------------------------------------------------------
*/
	
#define SPID_CTRL	SPID.CTRL	///< Control Register
#define SPID_INTCTRL	SPID.INTCTRL	///< Interrupt Control Register
#define SPID_STATUS	SPID.STATUS	///< Status Register
#define SPID_DATA	SPID.DATA	///< Data Register

/*
 --------------------------------------------------------------------------
 -- TCE0 - Timer/Counter E0
 --------------------------------------------------------------------------
*/
	
#define TCE0_CTRLA	TCE0.CTRLA	///< Control  Register A
#define TCE0_CTRLB	TCE0.CTRLB	///< Control Register B
#define TCE0_CTRLC	TCE0.CTRLC	///< Control register C
#define TCE0_CTRLD	TCE0.CTRLD	///< Control Register D
#define TCE0_CTRLE	TCE0.CTRLE	///< Control Register E
#define TCE0_INTCTRLA	TCE0.INTCTRLA	///< Interrupt Control Register A
#define TCE0_INTCTRLB	TCE0.INTCTRLB	///< Interrupt Control Register B
#define TCE0_CTRLFCLR	TCE0.CTRLFCLR	///< Control Register F Clear
#define TCE0_CTRLFSET	TCE0.CTRLFSET	///< Control Register F Set
#define TCE0_CTRLGCLR	TCE0.CTRLGCLR	///< Control Register G Clear
#define TCE0_CTRLGSET	TCE0.CTRLGSET	///< Control Register G Set
#define TCE0_INTFLAGS	TCE0.INTFLAGS	///< Interrupt Flag Register
#define TCE0_TEMP	TCE0.TEMP	///< Temporary Register For 16-bit Access
#define TCE0_CNT	TCE0.CNT	///< Count
#define TCE0_PER	TCE0.PER	///< Period
#define TCE0_CCA	TCE0.CCA	///< Compare or Capture A
#define TCE0_CCB	TCE0.CCB	///< Compare or Capture B
#define TCE0_CCC	TCE0.CCC	///< Compare or Capture C
#define TCE0_CCD	TCE0.CCD	///< Compare or Capture D
#define TCE0_PERBUF	TCE0.PERBUF	///< Period Buffer
#define TCE0_CCABUF	TCE0.CCABUF	///< Compare Or Capture A Buffer
#define TCE0_CCBBUF	TCE0.CCBBUF	///< Compare Or Capture B Buffer
#define TCE0_CCCBUF	TCE0.CCCBUF	///< Compare Or Capture C Buffer
#define TCE0_CCDBUF	TCE0.CCDBUF	///< Compare Or Capture D Buffer

/*
 --------------------------------------------------------------------------
 -- HIRESE - High-Resolution Extension E
 --------------------------------------------------------------------------
*/
	
#define HIRESE_CTRLA	HIRESE.CTRLA	///< Control Register

/*
 --------------------------------------------------------------------------
 -- USARTE0 - Universal Asynchronous Receiver-Transmitter E0
 --------------------------------------------------------------------------
*/
	
#define USARTE0_DATA	USARTE0.DATA	///< Data Register
#define USARTE0_STATUS	USARTE0.STATUS	///< Status Register
#define USARTE0_CTRLA	USARTE0.CTRLA	///< Control Register A
#define USARTE0_CTRLB	USARTE0.CTRLB	///< Control Register B
#define USARTE0_CTRLC	USARTE0.CTRLC	///< Control Register C
#define USARTE0_BAUDCTRLA	USARTE0.BAUDCTRLA	///< Baud Rate Control Register A
#define USARTE0_BAUDCTRLB	USARTE0.BAUDCTRLB	///< Baud Rate Control Register B

/*
 --------------------------------------------------------------------------
 -- IRCOM - IR Communication Module
 --------------------------------------------------------------------------
*/
	
#define IRCOM_CTRL	IRCOM.CTRL	///< Control Register
#define IRCOM_TXPLCTRL	IRCOM.TXPLCTRL	///< IrDA Transmitter Pulse Length Control Register
#define IRCOM_RXPLCTRL	IRCOM.RXPLCTRL	///< IrDA Receiver Pulse Length Control Register

/*
 --------------------------------------------------------------------------
 -- AES - AES Crypto Module
 --------------------------------------------------------------------------
*/
	
#define AES_CTRL	AES.CTRL	///< AES Control Register
#define AES_STATUS	AES.STATUS	///< AES Status Register
#define AES_STATE	AES.STATE	///< AES State Register
#define AES_KEY	AES.KEY	///< AES Key Register
#define AES_INTCTRL	AES.INTCTRL	///< AES Interrupt Control Register


#endif // defined(__IAR_SYSTEMS_ICC__)



#ifndef __ATxmega32A4_H
#define __ATxmega32A4_H


/*
 ---------------------------------------------------------------------------
 ---------------------------------------------------------------------------
 --
 -- Interrupt Vector Definitions
 --
 ----------------------------------------------------------------------------
 ---------------------------------------------------------------------------
*/

/* NB! vectors are specified as byte addresses */

/// Reset vector
#define RESET_vect 0


/// OSC interrupt vectors
#define OSC_XOSCF_vect 0x0004 ///< External Oscillator Failure Interrupt (NMI)

/// PORTC interrupt vectors
#define PORTC_INT0_vect 0x0008 ///< External Interrupt 0
#define PORTC_INT1_vect 0x000C ///< External Interrupt 1

/// PORTR interrupt vectors
#define PORTR_INT0_vect 0x0010 ///< External Interrupt 0
#define PORTR_INT1_vect 0x0014 ///< External Interrupt 1

/// DMA interrupt vectors
#define DMA_CH0_vect 0x0018 ///< Channel 0 Interrupt
#define DMA_CH1_vect 0x001C ///< Channel 1 Interrupt
#define DMA_CH2_vect 0x0020 ///< Channel 2 Interrupt
#define DMA_CH3_vect 0x0024 ///< Channel 3 Interrupt

/// RTC interrupt vectors
#define RTC_OVF_vect 0x0028 ///< Overflow Interrupt
#define RTC_COMP_vect 0x002C ///< Compare Interrupt

/// TWIC interrupt vectors
#define TWIC_TWIS_vect 0x0030 ///< TWI Slave Interrupt
#define TWIC_TWIM_vect 0x0034 ///< TWI Master Interrupt

/// TCC0 interrupt vectors
#define TCC0_OVF_vect 0x0038 ///< Overflow Interrupt
#define TCC0_ERR_vect 0x003C ///< Error Interrupt
#define TCC0_CCA_vect 0x0040 ///< Compare or Capture A Interrupt
#define TCC0_CCB_vect 0x0044 ///< Compare or Capture B Interrupt
#define TCC0_CCC_vect 0x0048 ///< Compare or Capture C Interrupt
#define TCC0_CCD_vect 0x004C ///< Compare or Capture D Interrupt

/// TCC1 interrupt vectors
#define TCC1_OVF_vect 0x0050 ///< Overflow Interrupt
#define TCC1_ERR_vect 0x0054 ///< Error Interrupt
#define TCC1_CCA_vect 0x0058 ///< Compare or Capture A Interrupt
#define TCC1_CCB_vect 0x005C ///< Compare or Capture B Interrupt

/// SPIC interrupt vectors
#define SPIC_INT_vect 0x0060 ///< SPI Interrupt

/// USARTC0 interrupt vectors
#define USARTC0_RXC_vect 0x0064 ///< Reception Complete Interrupt
#define USARTC0_DRE_vect 0x0068 ///< Data Register Empty Interrupt
#define USARTC0_TXC_vect 0x006C ///< Transmission Complete Interrupt

/// USARTC1 interrupt vectors
#define USARTC1_RXC_vect 0x0070 ///< Reception Complete Interrupt
#define USARTC1_DRE_vect 0x0074 ///< Data Register Empty Interrupt
#define USARTC1_TXC_vect 0x0078 ///< Transmission Complete Interrupt

/// AES interrupt vectors
#define AES_INT_vect 0x007C ///< AES Interrupt

/// NVM interrupt vectors
#define NVM_EE_vect 0x0080 ///< EE Interrupt
#define NVM_SPM_vect 0x0084 ///< SPM Interrupt

/// PORTB interrupt vectors
#define PORTB_INT0_vect 0x0088 ///< External Interrupt 0
#define PORTB_INT1_vect 0x008C ///< External Interrupt 1

/// PORTE interrupt vectors
#define PORTE_INT0_vect 0x00AC ///< External Interrupt 0
#define PORTE_INT1_vect 0x00B0 ///< External Interrupt 1

/// TWIE interrupt vectors
#define TWIE_TWIS_vect 0x00B4 ///< TWI Slave Interrupt
#define TWIE_TWIM_vect 0x00B8 ///< TWI Master Interrupt

/// TCE0 interrupt vectors
#define TCE0_OVF_vect 0x00BC ///< Overflow Interrupt
#define TCE0_ERR_vect 0x00C0 ///< Error Interrupt
#define TCE0_CCA_vect 0x00C4 ///< Compare or Capture A Interrupt
#define TCE0_CCB_vect 0x00C8 ///< Compare or Capture B Interrupt
#define TCE0_CCC_vect 0x00CC ///< Compare or Capture C Interrupt
#define TCE0_CCD_vect 0x00D0 ///< Compare or Capture D Interrupt

/// TCE1 interrupt vectors

/// USARTE0 interrupt vectors
#define USARTE0_RXC_vect 0x00E8 ///< Reception Complete Interrupt
#define USARTE0_DRE_vect 0x00EC ///< Data Register Empty Interrupt
#define USARTE0_TXC_vect 0x00F0 ///< Transmission Complete Interrupt

/// PORTD interrupt vectors
#define PORTD_INT0_vect 0x0100 ///< External Interrupt 0
#define PORTD_INT1_vect 0x0104 ///< External Interrupt 1

/// PORTA interrupt vectors
#define PORTA_INT0_vect 0x0108 ///< External Interrupt 0
#define PORTA_INT1_vect 0x010C ///< External Interrupt 1

/// ACA interrupt vectors
#define ACA_ACW_vect 0x0118 ///< ACW Window Mode Interrupt
#define ACA_AC1_vect 0x0114 ///< AC1 Interrupt
#define ACA_AC0_vect 0x0110 ///< AC0 Interrupt

/// ADCA interrupt vectors
#define ADCA_CH0_vect 0x011C ///< Interrupt 0
#define ADCA_CH1_vect 0x0120 ///< Interrupt 1
#define ADCA_CH2_vect 0x0124 ///< Interrupt 2
#define ADCA_CH3_vect 0x0128 ///< Interrupt 3

/// TCD0 interrupt vectors
#define TCD0_OVF_vect 0x0134 ///< Overflow Interrupt
#define TCD0_ERR_vect 0x0138 ///< Error Interrupt
#define TCD0_CCA_vect 0x013C ///< Compare or Capture A Interrupt
#define TCD0_CCB_vect 0x0140 ///< Compare or Capture B Interrupt
#define TCD0_CCC_vect 0x0144 ///< Compare or Capture C Interrupt
#define TCD0_CCD_vect 0x0148 ///< Compare or Capture D Interrupt

/// TCD1 interrupt vectors
#define TCD1_OVF_vect 0x014C ///< Overflow Interrupt
#define TCD1_ERR_vect 0x0150 ///< Error Interrupt
#define TCD1_CCA_vect 0x0154 ///< Compare or Capture A Interrupt
#define TCD1_CCB_vect 0x0158 ///< Compare or Capture B Interrupt

/// SPID interrupt vectors
#define SPID_INT_vect 0x015C ///< SPI Interrupt

/// USARTD0 interrupt vectors
#define USARTD0_RXC_vect 0x0160 ///< Reception Complete Interrupt
#define USARTD0_DRE_vect 0x0164 ///< Data Register Empty Interrupt
#define USARTD0_TXC_vect 0x0168 ///< Transmission Complete Interrupt

/// USARTD1 interrupt vectors
#define USARTD1_RXC_vect 0x016C ///< Reception Complete Interrupt
#define USARTD1_DRE_vect 0x0170 ///< Data Register Empty Interrupt
#define USARTD1_TXC_vect 0x0174 ///< Transmission Complete Interrupt





#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif // ENABLE_BIT_DEFINITIONS
#endif // __IAR_SYSTEMS_ASM__

#ifdef ENABLE_BIT_DEFINITIONS

/*
 ---------------------------------------------------------------------------
 ---------------------------------------------------------------------------
 --
 -- Bitfield definitions
 --
 ---------------------------------------------------------------------------
 ---------------------------------------------------------------------------
*/


/*
  ---------------------------------------------------------------------------
  -- CPU - CPU IO registers
  ---------------------------------------------------------------------------
*/

// CPU.SREG bit masks and bit positions
#define I_bm 0x80 ///< Global Interrupt Enable Flag bit mask
#define I_bp 7 ///< Global Interrupt Enable Flag bit position
#define T_bm 0x40 ///< Transfer Bit bit mask
#define T_bp 6 ///< Transfer Bit bit position
#define H_bm 0x20 ///< Half Carry Flag bit mask
#define H_bp 5 ///< Half Carry Flag bit position
#define S_bm 0x10 ///< N Exclusive Or V Flag bit mask
#define S_bp 4 ///< N Exclusive Or V Flag bit position
#define V_bm 0x08 ///< Two's Complement Overflow Flag bit mask
#define V_bp 3 ///< Two's Complement Overflow Flag bit position
#define N_bm 0x04 ///< Negative Flag bit mask
#define N_bp 2 ///< Negative Flag bit position
#define Z_bm 0x02 ///< Zero Flag bit mask
#define Z_bp 1 ///< Zero Flag bit position
#define C_bm 0x01 ///< Carry Flag bit mask
#define C_bp 0 ///< Carry Flag bit position




#if defined(__IAR_SYSTEMS_ICC__)
 	
#endif // defined(__IAR_SYSTEMS_ICC__)


#if defined(__IAR_SYSTEMS_ASM__)
	
#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup xocd On-Chip Debug System
 *  @{
 */
	
/** @name OCD.OCDR1
  * @{
  */
#define OCD_OCDRD_bm 0x01 ///< OCDR Dirty bit mask
#define OCD_OCDRD_bp 0 ///< OCDR Dirty bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
#endif //defined(__IAR_SYSTEMS_ASM__)



#if defined(__IAR_SYSTEMS_ICC__)
 	
/// CCP signatures

typedef enum CCP_enum {
	CCP_SPM_gc = (0x9D<<0),	///< SPM Instruction Protection
	CCP_IOREG_gc = (0xD8<<0),	///< IO Register Protection
} CCP_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)


#if defined(__IAR_SYSTEMS_ASM__)
	
/// CCP signatures
#define CCP_SPM_gc (0x9D<<0)	///< SPM Instruction Protection
#define CCP_IOREG_gc (0xD8<<0)	///< IO Register Protection

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup clk Clock System
 *  @{
 */
	
/** @name CLK.CTRL
  * @see CLK_SCLKSEL_enum
  * @{
  */
#define CLK_SCLKSEL_gm 0x07 ///< System Clock Selection group mask
#define CLK_SCLKSEL_gp 0 ///< System Clock Selection group position
#define CLK_SCLKSEL0_bm (1<<0) ///< System Clock Selection bit 0 mask
#define CLK_SCLKSEL0_bp 0 ///< System Clock Selection bit 0 position
#define CLK_SCLKSEL1_bm (1<<1) ///< System Clock Selection bit 1 mask
#define CLK_SCLKSEL1_bp 1 ///< System Clock Selection bit 1 position
#define CLK_SCLKSEL2_bm (1<<2) ///< System Clock Selection bit 2 mask
#define CLK_SCLKSEL2_bp 2 ///< System Clock Selection bit 2 position
/** @} */
	
/** @name CLK.PSCTRL
  * @see CLK_PSADIV_enum
  * @see CLK_PSBCDIV_enum
  * @{
  */
#define CLK_PSADIV_gm 0x7C ///< Prescaler A Division Factor group mask
#define CLK_PSADIV_gp 2 ///< Prescaler A Division Factor group position
#define CLK_PSADIV0_bm (1<<2) ///< Prescaler A Division Factor bit 0 mask
#define CLK_PSADIV0_bp 2 ///< Prescaler A Division Factor bit 0 position
#define CLK_PSADIV1_bm (1<<3) ///< Prescaler A Division Factor bit 1 mask
#define CLK_PSADIV1_bp 3 ///< Prescaler A Division Factor bit 1 position
#define CLK_PSADIV2_bm (1<<4) ///< Prescaler A Division Factor bit 2 mask
#define CLK_PSADIV2_bp 4 ///< Prescaler A Division Factor bit 2 position
#define CLK_PSADIV3_bm (1<<5) ///< Prescaler A Division Factor bit 3 mask
#define CLK_PSADIV3_bp 5 ///< Prescaler A Division Factor bit 3 position
#define CLK_PSADIV4_bm (1<<6) ///< Prescaler A Division Factor bit 4 mask
#define CLK_PSADIV4_bp 6 ///< Prescaler A Division Factor bit 4 position
#define CLK_PSBCDIV_gm 0x03 ///< Prescaler B and C Division factor group mask
#define CLK_PSBCDIV_gp 0 ///< Prescaler B and C Division factor group position
#define CLK_PSBCDIV0_bm (1<<0) ///< Prescaler B and C Division factor bit 0 mask
#define CLK_PSBCDIV0_bp 0 ///< Prescaler B and C Division factor bit 0 position
#define CLK_PSBCDIV1_bm (1<<1) ///< Prescaler B and C Division factor bit 1 mask
#define CLK_PSBCDIV1_bp 1 ///< Prescaler B and C Division factor bit 1 position
/** @} */
	
/** @name CLK.LOCK
  * @{
  */
#define CLK_LOCK_bm 0x01 ///< Clock System Lock bit mask
#define CLK_LOCK_bp 0 ///< Clock System Lock bit position
/** @} */
	
/** @name CLK.RTCCTRL
  * @see CLK_RTCSRC_enum
  * @{
  */
#define CLK_RTCSRC_gm 0x0E ///< RTC Clock Source group mask
#define CLK_RTCSRC_gp 1 ///< RTC Clock Source group position
#define CLK_RTCSRC0_bm (1<<1) ///< RTC Clock Source bit 0 mask
#define CLK_RTCSRC0_bp 1 ///< RTC Clock Source bit 0 position
#define CLK_RTCSRC1_bm (1<<2) ///< RTC Clock Source bit 1 mask
#define CLK_RTCSRC1_bp 2 ///< RTC Clock Source bit 1 position
#define CLK_RTCSRC2_bm (1<<3) ///< RTC Clock Source bit 2 mask
#define CLK_RTCSRC2_bp 3 ///< RTC Clock Source bit 2 position
#define CLK_RTCEN_bm 0x01 ///< RTC Clock Source Enable bit mask
#define CLK_RTCEN_bp 0 ///< RTC Clock Source Enable bit position
/** @} */
	
/** @name PR.PRGEN
  * @{
  */
#define PR_AES_bm 0x10 ///< AES bit mask
#define PR_AES_bp 4 ///< AES bit position
#define PR_EBI_bm 0x08 ///< External Bus Interface bit mask
#define PR_EBI_bp 3 ///< External Bus Interface bit position
#define PR_RTC_bm 0x04 ///< Real-time Counter bit mask
#define PR_RTC_bp 2 ///< Real-time Counter bit position
#define PR_EVSYS_bm 0x02 ///< Event System bit mask
#define PR_EVSYS_bp 1 ///< Event System bit position
#define PR_DMA_bm 0x01 ///< DMA-Controller bit mask
#define PR_DMA_bp 0 ///< DMA-Controller bit position
/** @} */
	
/** @name PR.PRPA
  * @{
  */
#define PR_DAC_bm 0x04 ///< Port A DAC bit mask
#define PR_DAC_bp 2 ///< Port A DAC bit position
#define PR_ADC_bm 0x02 ///< Port A ADC bit mask
#define PR_ADC_bp 1 ///< Port A ADC bit position
#define PR_AC_bm 0x01 ///< Port A Analog Comparator bit mask
#define PR_AC_bp 0 ///< Port A Analog Comparator bit position
/** @} */
	
/** @name PR.PRPB
  * @{
  */
// Masks for DAC aready defined
// Masks for ADC aready defined
// Masks for AC aready defined
/** @} */
	
/** @name PR.PRPC
  * @{
  */
#define PR_TWI_bm 0x40 ///< Port C Two-wire Interface bit mask
#define PR_TWI_bp 6 ///< Port C Two-wire Interface bit position
#define PR_USART1_bm 0x20 ///< Port C USART1 bit mask
#define PR_USART1_bp 5 ///< Port C USART1 bit position
#define PR_USART0_bm 0x10 ///< Port C USART0 bit mask
#define PR_USART0_bp 4 ///< Port C USART0 bit position
#define PR_SPI_bm 0x08 ///< Port C SPI bit mask
#define PR_SPI_bp 3 ///< Port C SPI bit position
#define PR_HIRES_bm 0x04 ///< Port C AWEX bit mask
#define PR_HIRES_bp 2 ///< Port C AWEX bit position
#define PR_TC1_bm 0x02 ///< Port C Timer/Counter1 bit mask
#define PR_TC1_bp 1 ///< Port C Timer/Counter1 bit position
#define PR_TC0_bm 0x01 ///< Port C Timer/Counter0 bit mask
#define PR_TC0_bp 0 ///< Port C Timer/Counter0 bit position
/** @} */
	
/** @name PR.PRPD
  * @{
  */
// Masks for TWI aready defined
// Masks for USART1 aready defined
// Masks for USART0 aready defined
// Masks for SPI aready defined
// Masks for HIRES aready defined
// Masks for TC1 aready defined
// Masks for TC0 aready defined
/** @} */
	
/** @name PR.PRPE
  * @{
  */
// Masks for TWI aready defined
// Masks for USART1 aready defined
// Masks for USART0 aready defined
// Masks for SPI aready defined
// Masks for HIRES aready defined
// Masks for TC1 aready defined
// Masks for TC0 aready defined
/** @} */
	
/** @name PR.PRPF
  * @{
  */
// Masks for TWI aready defined
// Masks for USART1 aready defined
// Masks for USART0 aready defined
// Masks for SPI aready defined
// Masks for HIRES aready defined
// Masks for TC1 aready defined
// Masks for TC0 aready defined
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// System Clock Selection

typedef enum CLK_SCLKSEL_enum {
	CLK_SCLKSEL_RC2M_gc = (0x00<<0),	///< Internal 2MHz RC Oscillator
	CLK_SCLKSEL_RC32M_gc = (0x01<<0),	///< Internal 32MHz RC Oscillator
	CLK_SCLKSEL_RC32K_gc = (0x02<<0),	///< Internal 32kHz RC Oscillator
	CLK_SCLKSEL_XOSC_gc = (0x03<<0),	///< External Crystal Oscillator or Clock
	CLK_SCLKSEL_PLL_gc = (0x04<<0),	///< Phase Locked Loop
} CLK_SCLKSEL_t;
	
/// Prescaler A Division Factor

typedef enum CLK_PSADIV_enum {
	CLK_PSADIV_1_gc = (0x00<<2),	///< Divide by 1
	CLK_PSADIV_2_gc = (0x01<<2),	///< Divide by 2
	CLK_PSADIV_4_gc = (0x03<<2),	///< Divide by 4
	CLK_PSADIV_8_gc = (0x05<<2),	///< Divide by 8
	CLK_PSADIV_16_gc = (0x07<<2),	///< Divide by 16
	CLK_PSADIV_32_gc = (0x09<<2),	///< Divide by 32
	CLK_PSADIV_64_gc = (0x0B<<2),	///< Divide by 64
	CLK_PSADIV_128_gc = (0x0D<<2),	///< Divide by 128
	CLK_PSADIV_256_gc = (0x0F<<2),	///< Divide by 256
	CLK_PSADIV_512_gc = (0x11<<2),	///< Divide by 512
} CLK_PSADIV_t;
	
/// Prescaler B and C Division Factor

typedef enum CLK_PSBCDIV_enum {
	CLK_PSBCDIV_1_1_gc = (0x00<<0),	///< Divide B by 1 and C by 1
	CLK_PSBCDIV_1_2_gc = (0x01<<0),	///< Divide B by 1 and C by 2
	CLK_PSBCDIV_4_1_gc = (0x02<<0),	///< Divide B by 4 and C by 1
	CLK_PSBCDIV_2_2_gc = (0x03<<0),	///< Divide B by 2 and C by 2
} CLK_PSBCDIV_t;
	
/// RTC Clock Source

typedef enum CLK_RTCSRC_enum {
	CLK_RTCSRC_ULP_gc = (0x00<<1),	///< 1kHz from internal 32kHz ULP
	CLK_RTCSRC_TOSC_gc = (0x01<<1),	///< 1kHz from 32kHz crystal oscillator on TOSC
	CLK_RTCSRC_RCOSC_gc = (0x02<<1),	///< 1kHz from internal 32kHz RC oscillator
	CLK_RTCSRC_TOSC32_gc = (0x05<<1),	///< 32kHz from 32kHz crystal oscillator on TOSC
} CLK_RTCSRC_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// System Clock Selection
#define CLK_SCLKSEL_RC2M_gc (0x00<<0)	///< Internal 2MHz RC Oscillator
#define CLK_SCLKSEL_RC32M_gc (0x01<<0)	///< Internal 32MHz RC Oscillator
#define CLK_SCLKSEL_RC32K_gc (0x02<<0)	///< Internal 32kHz RC Oscillator
#define CLK_SCLKSEL_XOSC_gc (0x03<<0)	///< External Crystal Oscillator or Clock
#define CLK_SCLKSEL_PLL_gc (0x04<<0)	///< Phase Locked Loop

/// Prescaler A Division Factor
#define CLK_PSADIV_1_gc (0x00<<2)	///< Divide by 1
#define CLK_PSADIV_2_gc (0x01<<2)	///< Divide by 2
#define CLK_PSADIV_4_gc (0x03<<2)	///< Divide by 4
#define CLK_PSADIV_8_gc (0x05<<2)	///< Divide by 8
#define CLK_PSADIV_16_gc (0x07<<2)	///< Divide by 16
#define CLK_PSADIV_32_gc (0x09<<2)	///< Divide by 32
#define CLK_PSADIV_64_gc (0x0B<<2)	///< Divide by 64
#define CLK_PSADIV_128_gc (0x0D<<2)	///< Divide by 128
#define CLK_PSADIV_256_gc (0x0F<<2)	///< Divide by 256
#define CLK_PSADIV_512_gc (0x11<<2)	///< Divide by 512

/// Prescaler B and C Division Factor
#define CLK_PSBCDIV_1_1_gc (0x00<<0)	///< Divide B by 1 and C by 1
#define CLK_PSBCDIV_1_2_gc (0x01<<0)	///< Divide B by 1 and C by 2
#define CLK_PSBCDIV_4_1_gc (0x02<<0)	///< Divide B by 4 and C by 1
#define CLK_PSBCDIV_2_2_gc (0x03<<0)	///< Divide B by 2 and C by 2

/// RTC Clock Source
#define CLK_RTCSRC_ULP_gc (0x00<<1)	///< 1kHz from internal 32kHz ULP
#define CLK_RTCSRC_TOSC_gc (0x01<<1)	///< 1kHz from 32kHz crystal oscillator on TOSC
#define CLK_RTCSRC_RCOSC_gc (0x02<<1)	///< 1kHz from internal 32kHz RC oscillator
#define CLK_RTCSRC_TOSC32_gc (0x05<<1)	///< 32kHz from 32kHz crystal oscillator on TOSC

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup sleep Sleep Controller
 *  @{
 */
	
/** @name SLEEP.CTRL
  * @see SLEEP_SMODE_enum
  * @{
  */
#define SLEEP_SMODE_gm 0x0E ///< Sleep Mode group mask
#define SLEEP_SMODE_gp 1 ///< Sleep Mode group position
#define SLEEP_SMODE0_bm (1<<1) ///< Sleep Mode bit 0 mask
#define SLEEP_SMODE0_bp 1 ///< Sleep Mode bit 0 position
#define SLEEP_SMODE1_bm (1<<2) ///< Sleep Mode bit 1 mask
#define SLEEP_SMODE1_bp 2 ///< Sleep Mode bit 1 position
#define SLEEP_SMODE2_bm (1<<3) ///< Sleep Mode bit 2 mask
#define SLEEP_SMODE2_bp 3 ///< Sleep Mode bit 2 position
#define SLEEP_SEN_bm 0x01 ///< Sleep Enable bit mask
#define SLEEP_SEN_bp 0 ///< Sleep Enable bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Sleep Mode

typedef enum SLEEP_SMODE_enum {
	SLEEP_SMODE_IDLE_gc = (0x00<<1),	///< Idle mode
	SLEEP_SMODE_PDOWN_gc = (0x02<<1),	///< Power-down Mode
	SLEEP_SMODE_PSAVE_gc = (0x03<<1),	///< Power-save Mode
	SLEEP_SMODE_STDBY_gc = (0x06<<1),	///< Standby Mode
	SLEEP_SMODE_ESTDBY_gc = (0x07<<1),	///< Extended Standby Mode
} SLEEP_SMODE_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Sleep Mode
#define SLEEP_SMODE_IDLE_gc (0x00<<1)	///< Idle mode
#define SLEEP_SMODE_PDOWN_gc (0x02<<1)	///< Power-down Mode
#define SLEEP_SMODE_PSAVE_gc (0x03<<1)	///< Power-save Mode
#define SLEEP_SMODE_STDBY_gc (0x06<<1)	///< Standby Mode
#define SLEEP_SMODE_ESTDBY_gc (0x07<<1)	///< Extended Standby Mode

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup osc Oscillator
 *  @{
 */
	
/** @name OSC.CTRL
  * @{
  */
#define OSC_PLLEN_bm 0x10 ///< PLL Enable bit mask
#define OSC_PLLEN_bp 4 ///< PLL Enable bit position
#define OSC_XOSCEN_bm 0x08 ///< External Oscillator Enable bit mask
#define OSC_XOSCEN_bp 3 ///< External Oscillator Enable bit position
#define OSC_RC32KEN_bm 0x04 ///< Internal 32kHz RC Oscillator Enable bit mask
#define OSC_RC32KEN_bp 2 ///< Internal 32kHz RC Oscillator Enable bit position
#define OSC_RC32MEN_bm 0x02 ///< Internal 32MHz RC Oscillator Enable bit mask
#define OSC_RC32MEN_bp 1 ///< Internal 32MHz RC Oscillator Enable bit position
#define OSC_RC2MEN_bm 0x01 ///< Internal 2MHz RC Oscillator Enable bit mask
#define OSC_RC2MEN_bp 0 ///< Internal 2MHz RC Oscillator Enable bit position
/** @} */
	
/** @name OSC.STATUS
  * @{
  */
#define OSC_PLLRDY_bm 0x10 ///< PLL Ready bit mask
#define OSC_PLLRDY_bp 4 ///< PLL Ready bit position
#define OSC_XOSCRDY_bm 0x08 ///< External Oscillator Ready bit mask
#define OSC_XOSCRDY_bp 3 ///< External Oscillator Ready bit position
#define OSC_RC32KRDY_bm 0x04 ///< Internal 32kHz RC Oscillator Ready bit mask
#define OSC_RC32KRDY_bp 2 ///< Internal 32kHz RC Oscillator Ready bit position
#define OSC_RC32MRDY_bm 0x02 ///< Internal 32MHz RC Oscillator Ready bit mask
#define OSC_RC32MRDY_bp 1 ///< Internal 32MHz RC Oscillator Ready bit position
#define OSC_RC2MRDY_bm 0x01 ///< Internal 2MHz RC Oscillator Ready bit mask
#define OSC_RC2MRDY_bp 0 ///< Internal 2MHz RC Oscillator Ready bit position
/** @} */
	
/** @name OSC.XOSCCTRL
  * @see OSC_FRQRANGE_enum
  * @see OSC_XOSCSEL_enum
  * @{
  */
#define OSC_FRQRANGE_gm 0xC0 ///< Frequency Range group mask
#define OSC_FRQRANGE_gp 6 ///< Frequency Range group position
#define OSC_FRQRANGE0_bm (1<<6) ///< Frequency Range bit 0 mask
#define OSC_FRQRANGE0_bp 6 ///< Frequency Range bit 0 position
#define OSC_FRQRANGE1_bm (1<<7) ///< Frequency Range bit 1 mask
#define OSC_FRQRANGE1_bp 7 ///< Frequency Range bit 1 position
#define OSC_X32KLPM_bm 0x20 ///< 32kHz XTAL OSC Low-power Mode bit mask
#define OSC_X32KLPM_bp 5 ///< 32kHz XTAL OSC Low-power Mode bit position
#define OSC_XOSCSEL_gm 0x0F ///< External Oscillator Selection and Startup Time group mask
#define OSC_XOSCSEL_gp 0 ///< External Oscillator Selection and Startup Time group position
#define OSC_XOSCSEL0_bm (1<<0) ///< External Oscillator Selection and Startup Time bit 0 mask
#define OSC_XOSCSEL0_bp 0 ///< External Oscillator Selection and Startup Time bit 0 position
#define OSC_XOSCSEL1_bm (1<<1) ///< External Oscillator Selection and Startup Time bit 1 mask
#define OSC_XOSCSEL1_bp 1 ///< External Oscillator Selection and Startup Time bit 1 position
#define OSC_XOSCSEL2_bm (1<<2) ///< External Oscillator Selection and Startup Time bit 2 mask
#define OSC_XOSCSEL2_bp 2 ///< External Oscillator Selection and Startup Time bit 2 position
#define OSC_XOSCSEL3_bm (1<<3) ///< External Oscillator Selection and Startup Time bit 3 mask
#define OSC_XOSCSEL3_bp 3 ///< External Oscillator Selection and Startup Time bit 3 position
/** @} */
	
/** @name OSC.XOSCFAIL
  * @{
  */
#define OSC_XOSCFDIF_bm 0x02 ///< Failure Detection Interrupt Flag bit mask
#define OSC_XOSCFDIF_bp 1 ///< Failure Detection Interrupt Flag bit position
#define OSC_XOSCFDEN_bm 0x01 ///< Failure Detection Enable bit mask
#define OSC_XOSCFDEN_bp 0 ///< Failure Detection Enable bit position
/** @} */
	
/** @name OSC.PLLCTRL
  * @see OSC_PLLSRC_enum
  * @{
  */
#define OSC_PLLSRC_gm 0xC0 ///< Clock Source group mask
#define OSC_PLLSRC_gp 6 ///< Clock Source group position
#define OSC_PLLSRC0_bm (1<<6) ///< Clock Source bit 0 mask
#define OSC_PLLSRC0_bp 6 ///< Clock Source bit 0 position
#define OSC_PLLSRC1_bm (1<<7) ///< Clock Source bit 1 mask
#define OSC_PLLSRC1_bp 7 ///< Clock Source bit 1 position
#define OSC_PLLFAC_gm 0x1F ///< Multiplication Factor group mask
#define OSC_PLLFAC_gp 0 ///< Multiplication Factor group position
#define OSC_PLLFAC0_bm (1<<0) ///< Multiplication Factor bit 0 mask
#define OSC_PLLFAC0_bp 0 ///< Multiplication Factor bit 0 position
#define OSC_PLLFAC1_bm (1<<1) ///< Multiplication Factor bit 1 mask
#define OSC_PLLFAC1_bp 1 ///< Multiplication Factor bit 1 position
#define OSC_PLLFAC2_bm (1<<2) ///< Multiplication Factor bit 2 mask
#define OSC_PLLFAC2_bp 2 ///< Multiplication Factor bit 2 position
#define OSC_PLLFAC3_bm (1<<3) ///< Multiplication Factor bit 3 mask
#define OSC_PLLFAC3_bp 3 ///< Multiplication Factor bit 3 position
#define OSC_PLLFAC4_bm (1<<4) ///< Multiplication Factor bit 4 mask
#define OSC_PLLFAC4_bp 4 ///< Multiplication Factor bit 4 position
/** @} */
	
/** @name OSC.DFLLCTRL
  * @{
  */
#define OSC_RC32MCREF_bm 0x02 ///< 32MHz Calibration Reference bit mask
#define OSC_RC32MCREF_bp 1 ///< 32MHz Calibration Reference bit position
#define OSC_RC2MCREF_bm 0x01 ///< 2MHz Calibration Reference bit mask
#define OSC_RC2MCREF_bp 0 ///< 2MHz Calibration Reference bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Oscillator Frequency Range

typedef enum OSC_FRQRANGE_enum {
	OSC_FRQRANGE_04TO2_gc = (0x00<<6),	///< 0.4 - 2 MHz
	OSC_FRQRANGE_2TO9_gc = (0x01<<6),	///< 2 - 9 MHz
	OSC_FRQRANGE_9TO12_gc = (0x02<<6),	///< 9 - 12 MHz
	OSC_FRQRANGE_12TO16_gc = (0x03<<6),	///< 12 - 16 MHz
} OSC_FRQRANGE_t;
	
/// External Oscillator Selection and Startup Time

typedef enum OSC_XOSCSEL_enum {
	OSC_XOSCSEL_EXTCLK_gc = (0x00<<0),	///< External Clock - 6 CLK
	OSC_XOSCSEL_32KHz_gc = (0x02<<0),	///< 32kHz TOSC - 32K CLK
	OSC_XOSCSEL_XTAL_256CLK_gc = (0x03<<0),	///< 0.4-16MHz XTAL - 256 CLK
	OSC_XOSCSEL_XTAL_1KCLK_gc = (0x07<<0),	///< 0.4-16MHz XTAL - 1K CLK
	OSC_XOSCSEL_XTAL_16KCLK_gc = (0x0B<<0),	///< 0.4-16MHz XTAL - 16K CLK
} OSC_XOSCSEL_t;
	
/// PLL Clock Source

typedef enum OSC_PLLSRC_enum {
	OSC_PLLSRC_RC2M_gc = (0x00<<6),	///< Internal 2MHz RC Oscillator
	OSC_PLLSRC_RC32M_gc = (0x02<<6),	///< Internal 32MHz RC Oscillator
	OSC_PLLSRC_XOSC_gc = (0x03<<6),	///< External Oscillator
} OSC_PLLSRC_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Oscillator Frequency Range
#define OSC_FRQRANGE_04TO2_gc (0x00<<6)	///< 0.4 - 2 MHz
#define OSC_FRQRANGE_2TO9_gc (0x01<<6)	///< 2 - 9 MHz
#define OSC_FRQRANGE_9TO12_gc (0x02<<6)	///< 9 - 12 MHz
#define OSC_FRQRANGE_12TO16_gc (0x03<<6)	///< 12 - 16 MHz

/// External Oscillator Selection and Startup Time
#define OSC_XOSCSEL_EXTCLK_gc (0x00<<0)	///< External Clock - 6 CLK
#define OSC_XOSCSEL_32KHz_gc (0x02<<0)	///< 32kHz TOSC - 32K CLK
#define OSC_XOSCSEL_XTAL_256CLK_gc (0x03<<0)	///< 0.4-16MHz XTAL - 256 CLK
#define OSC_XOSCSEL_XTAL_1KCLK_gc (0x07<<0)	///< 0.4-16MHz XTAL - 1K CLK
#define OSC_XOSCSEL_XTAL_16KCLK_gc (0x0B<<0)	///< 0.4-16MHz XTAL - 16K CLK

/// PLL Clock Source
#define OSC_PLLSRC_RC2M_gc (0x00<<6)	///< Internal 2MHz RC Oscillator
#define OSC_PLLSRC_RC32M_gc (0x02<<6)	///< Internal 32MHz RC Oscillator
#define OSC_PLLSRC_XOSC_gc (0x03<<6)	///< External Oscillator

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup dfll DFLL
 *  @{
 */
	
/** @name DFLL.CTRL
  * @{
  */
#define DFLL_ENABLE_bm 0x01 ///< DFLL Enable bit mask
#define DFLL_ENABLE_bp 0 ///< DFLL Enable bit position
/** @} */
	
/** @name DFLL.CALA
  * @{
  */
#define DFLL_CALL_gm 0x7F ///< DFLL Calibration bits [6:0] group mask
#define DFLL_CALL_gp 0 ///< DFLL Calibration bits [6:0] group position
#define DFLL_CALL0_bm (1<<0) ///< DFLL Calibration bits [6:0] bit 0 mask
#define DFLL_CALL0_bp 0 ///< DFLL Calibration bits [6:0] bit 0 position
#define DFLL_CALL1_bm (1<<1) ///< DFLL Calibration bits [6:0] bit 1 mask
#define DFLL_CALL1_bp 1 ///< DFLL Calibration bits [6:0] bit 1 position
#define DFLL_CALL2_bm (1<<2) ///< DFLL Calibration bits [6:0] bit 2 mask
#define DFLL_CALL2_bp 2 ///< DFLL Calibration bits [6:0] bit 2 position
#define DFLL_CALL3_bm (1<<3) ///< DFLL Calibration bits [6:0] bit 3 mask
#define DFLL_CALL3_bp 3 ///< DFLL Calibration bits [6:0] bit 3 position
#define DFLL_CALL4_bm (1<<4) ///< DFLL Calibration bits [6:0] bit 4 mask
#define DFLL_CALL4_bp 4 ///< DFLL Calibration bits [6:0] bit 4 position
#define DFLL_CALL5_bm (1<<5) ///< DFLL Calibration bits [6:0] bit 5 mask
#define DFLL_CALL5_bp 5 ///< DFLL Calibration bits [6:0] bit 5 position
#define DFLL_CALL6_bm (1<<6) ///< DFLL Calibration bits [6:0] bit 6 mask
#define DFLL_CALL6_bp 6 ///< DFLL Calibration bits [6:0] bit 6 position
/** @} */
	
/** @name DFLL.CALB
  * @{
  */
#define DFLL_CALH_gm 0x3F ///< DFLL Calibration bits [12:7] group mask
#define DFLL_CALH_gp 0 ///< DFLL Calibration bits [12:7] group position
#define DFLL_CALH0_bm (1<<0) ///< DFLL Calibration bits [12:7] bit 0 mask
#define DFLL_CALH0_bp 0 ///< DFLL Calibration bits [12:7] bit 0 position
#define DFLL_CALH1_bm (1<<1) ///< DFLL Calibration bits [12:7] bit 1 mask
#define DFLL_CALH1_bp 1 ///< DFLL Calibration bits [12:7] bit 1 position
#define DFLL_CALH2_bm (1<<2) ///< DFLL Calibration bits [12:7] bit 2 mask
#define DFLL_CALH2_bp 2 ///< DFLL Calibration bits [12:7] bit 2 position
#define DFLL_CALH3_bm (1<<3) ///< DFLL Calibration bits [12:7] bit 3 mask
#define DFLL_CALH3_bp 3 ///< DFLL Calibration bits [12:7] bit 3 position
#define DFLL_CALH4_bm (1<<4) ///< DFLL Calibration bits [12:7] bit 4 mask
#define DFLL_CALH4_bp 4 ///< DFLL Calibration bits [12:7] bit 4 position
#define DFLL_CALH5_bm (1<<5) ///< DFLL Calibration bits [12:7] bit 5 mask
#define DFLL_CALH5_bp 5 ///< DFLL Calibration bits [12:7] bit 5 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup rst Reset
 *  @{
 */
	
/** @name RST.STATUS
  * @{
  */
#define RST_SDRF_bm 0x40 ///< Spike Detection Reset Flag bit mask
#define RST_SDRF_bp 6 ///< Spike Detection Reset Flag bit position
#define RST_SRF_bm 0x20 ///< Software Reset Flag bit mask
#define RST_SRF_bp 5 ///< Software Reset Flag bit position
#define RST_PDIRF_bm 0x10 ///< Programming and Debug Interface Interface Reset Flag bit mask
#define RST_PDIRF_bp 4 ///< Programming and Debug Interface Interface Reset Flag bit position
#define RST_WDRF_bm 0x08 ///< Watchdog Reset Flag bit mask
#define RST_WDRF_bp 3 ///< Watchdog Reset Flag bit position
#define RST_BORF_bm 0x04 ///< Brown-out Reset Flag bit mask
#define RST_BORF_bp 2 ///< Brown-out Reset Flag bit position
#define RST_EXTRF_bm 0x02 ///< External Reset Flag bit mask
#define RST_EXTRF_bp 1 ///< External Reset Flag bit position
#define RST_PORF_bm 0x01 ///< Power-on Reset Flag bit mask
#define RST_PORF_bp 0 ///< Power-on Reset Flag bit position
/** @} */
	
/** @name RST.CTRL
  * @{
  */
#define RST_SWRST_bm 0x01 ///< Software Reset bit mask
#define RST_SWRST_bp 0 ///< Software Reset bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup wdt Watch-Dog Timer
 *  @{
 */
	
/** @name WDT.CTRL
  * @see WDT_PER_enum
  * @{
  */
#define WDT_PER_gm 0x3C ///< Period group mask
#define WDT_PER_gp 2 ///< Period group position
#define WDT_PER0_bm (1<<2) ///< Period bit 0 mask
#define WDT_PER0_bp 2 ///< Period bit 0 position
#define WDT_PER1_bm (1<<3) ///< Period bit 1 mask
#define WDT_PER1_bp 3 ///< Period bit 1 position
#define WDT_PER2_bm (1<<4) ///< Period bit 2 mask
#define WDT_PER2_bp 4 ///< Period bit 2 position
#define WDT_PER3_bm (1<<5) ///< Period bit 3 mask
#define WDT_PER3_bp 5 ///< Period bit 3 position
#define WDT_ENABLE_bm 0x02 ///< Enable bit mask
#define WDT_ENABLE_bp 1 ///< Enable bit position
#define WDT_CEN_bm 0x01 ///< Change Enable bit mask
#define WDT_CEN_bp 0 ///< Change Enable bit position
/** @} */
	
/** @name WDT.WINCTRL
  * @see WDT_WPER_enum
  * @{
  */
#define WDT_WPER_gm 0x3C ///< Windowed Mode Period group mask
#define WDT_WPER_gp 2 ///< Windowed Mode Period group position
#define WDT_WPER0_bm (1<<2) ///< Windowed Mode Period bit 0 mask
#define WDT_WPER0_bp 2 ///< Windowed Mode Period bit 0 position
#define WDT_WPER1_bm (1<<3) ///< Windowed Mode Period bit 1 mask
#define WDT_WPER1_bp 3 ///< Windowed Mode Period bit 1 position
#define WDT_WPER2_bm (1<<4) ///< Windowed Mode Period bit 2 mask
#define WDT_WPER2_bp 4 ///< Windowed Mode Period bit 2 position
#define WDT_WPER3_bm (1<<5) ///< Windowed Mode Period bit 3 mask
#define WDT_WPER3_bp 5 ///< Windowed Mode Period bit 3 position
#define WDT_WEN_bm 0x02 ///< Windowed Mode Enable bit mask
#define WDT_WEN_bp 1 ///< Windowed Mode Enable bit position
#define WDT_WCEN_bm 0x01 ///< Windowed Mode Change Enable bit mask
#define WDT_WCEN_bp 0 ///< Windowed Mode Change Enable bit position
/** @} */
	
/** @name WDT.STATUS
  * @{
  */
#define WDT_SYNCBUSY_bm 0x01 ///< Syncronization busy bit mask
#define WDT_SYNCBUSY_bp 0 ///< Syncronization busy bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Period setting

typedef enum WDT_PER_enum {
	WDT_PER_8CLK_gc = (0x00<<2),	///< 8 cycles (8ms @ 3.3V)
	WDT_PER_16CLK_gc = (0x01<<2),	///< 16 cycles (16ms @ 3.3V)
	WDT_PER_32CLK_gc = (0x02<<2),	///< 32 cycles (32ms @ 3.3V)
	WDT_PER_64CLK_gc = (0x03<<2),	///< 64 cycles (64ms @ 3.3V)
	WDT_PER_125CLK_gc = (0x04<<2),	///< 125 cycles (0.125s @ 3.3V)
	WDT_PER_250CLK_gc = (0x05<<2),	///< 250 cycles (0.25s @ 3.3V)
	WDT_PER_500CLK_gc = (0x06<<2),	///< 500 cycles (0.5s @ 3.3V)
	WDT_PER_1KCLK_gc = (0x07<<2),	///< 1K cycles (1s @ 3.3V)
	WDT_PER_2KCLK_gc = (0x08<<2),	///< 2K cycles (2s @ 3.3V)
	WDT_PER_4KCLK_gc = (0x09<<2),	///< 4K cycles (4s @ 3.3V)
	WDT_PER_8KCLK_gc = (0x0A<<2),	///< 8K cycles (8s @ 3.3V)
} WDT_PER_t;
	
/// Closed window period

typedef enum WDT_WPER_enum {
	WDT_WPER_8CLK_gc = (0x00<<2),	///< 8 cycles (8ms @ 3.3V)
	WDT_WPER_16CLK_gc = (0x01<<2),	///< 16 cycles (16ms @ 3.3V)
	WDT_WPER_32CLK_gc = (0x02<<2),	///< 32 cycles (32ms @ 3.3V)
	WDT_WPER_64CLK_gc = (0x03<<2),	///< 64 cycles (64ms @ 3.3V)
	WDT_WPER_125CLK_gc = (0x04<<2),	///< 125 cycles (0.125s @ 3.3V)
	WDT_WPER_250CLK_gc = (0x05<<2),	///< 250 cycles (0.25s @ 3.3V)
	WDT_WPER_500CLK_gc = (0x06<<2),	///< 500 cycles (0.5s @ 3.3V)
	WDT_WPER_1KCLK_gc = (0x07<<2),	///< 1K cycles (1s @ 3.3V)
	WDT_WPER_2KCLK_gc = (0x08<<2),	///< 2K cycles (2s @ 3.3V)
	WDT_WPER_4KCLK_gc = (0x09<<2),	///< 4K cycles (4s @ 3.3V)
	WDT_WPER_8KCLK_gc = (0x0A<<2),	///< 8K cycles (8s @ 3.3V)
} WDT_WPER_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Period setting
#define WDT_PER_8CLK_gc (0x00<<2)	///< 8 cycles (8ms @ 3.3V)
#define WDT_PER_16CLK_gc (0x01<<2)	///< 16 cycles (16ms @ 3.3V)
#define WDT_PER_32CLK_gc (0x02<<2)	///< 32 cycles (32ms @ 3.3V)
#define WDT_PER_64CLK_gc (0x03<<2)	///< 64 cycles (64ms @ 3.3V)
#define WDT_PER_125CLK_gc (0x04<<2)	///< 125 cycles (0.125s @ 3.3V)
#define WDT_PER_250CLK_gc (0x05<<2)	///< 250 cycles (0.25s @ 3.3V)
#define WDT_PER_500CLK_gc (0x06<<2)	///< 500 cycles (0.5s @ 3.3V)
#define WDT_PER_1KCLK_gc (0x07<<2)	///< 1K cycles (1s @ 3.3V)
#define WDT_PER_2KCLK_gc (0x08<<2)	///< 2K cycles (2s @ 3.3V)
#define WDT_PER_4KCLK_gc (0x09<<2)	///< 4K cycles (4s @ 3.3V)
#define WDT_PER_8KCLK_gc (0x0A<<2)	///< 8K cycles (8s @ 3.3V)

/// Closed window period
#define WDT_WPER_8CLK_gc (0x00<<2)	///< 8 cycles (8ms @ 3.3V)
#define WDT_WPER_16CLK_gc (0x01<<2)	///< 16 cycles (16ms @ 3.3V)
#define WDT_WPER_32CLK_gc (0x02<<2)	///< 32 cycles (32ms @ 3.3V)
#define WDT_WPER_64CLK_gc (0x03<<2)	///< 64 cycles (64ms @ 3.3V)
#define WDT_WPER_125CLK_gc (0x04<<2)	///< 125 cycles (0.125s @ 3.3V)
#define WDT_WPER_250CLK_gc (0x05<<2)	///< 250 cycles (0.25s @ 3.3V)
#define WDT_WPER_500CLK_gc (0x06<<2)	///< 500 cycles (0.5s @ 3.3V)
#define WDT_WPER_1KCLK_gc (0x07<<2)	///< 1K cycles (1s @ 3.3V)
#define WDT_WPER_2KCLK_gc (0x08<<2)	///< 2K cycles (2s @ 3.3V)
#define WDT_WPER_4KCLK_gc (0x09<<2)	///< 4K cycles (4s @ 3.3V)
#define WDT_WPER_8KCLK_gc (0x0A<<2)	///< 8K cycles (8s @ 3.3V)

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup mcu MCU Control
 *  @{
 */
	
/** @name MCU.MCUCR
  * @{
  */
#define MCU_JTAGD_bm 0x01 ///< JTAG Disable bit mask
#define MCU_JTAGD_bp 0 ///< JTAG Disable bit position
/** @} */
	
/** @name MCU.EVSYSLOCK
  * @{
  */
#define MCU_EVSYS1LOCK_bm 0x10 ///< Event Channel 4-7 Lock bit mask
#define MCU_EVSYS1LOCK_bp 4 ///< Event Channel 4-7 Lock bit position
#define MCU_EVSYS0LOCK_bm 0x01 ///< Event Channel 0-3 Lock bit mask
#define MCU_EVSYS0LOCK_bp 0 ///< Event Channel 0-3 Lock bit position
/** @} */
	
/** @name MCU.AWEXLOCK
  * @{
  */
#define MCU_AWEXELOCK_bm 0x04 ///< AWeX on T/C E0 Lock bit mask
#define MCU_AWEXELOCK_bp 2 ///< AWeX on T/C E0 Lock bit position
#define MCU_AWEXCLOCK_bm 0x01 ///< AWeX on T/C C0 Lock bit mask
#define MCU_AWEXCLOCK_bp 0 ///< AWeX on T/C C0 Lock bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup pmic Programmable Multi-level Interrupt Controller
 *  @{
 */
	
/** @name PMIC.STATUS
  * @{
  */
#define PMIC_NMIEX_bm 0x80 ///< Non-maskable Interrupt Executing bit mask
#define PMIC_NMIEX_bp 7 ///< Non-maskable Interrupt Executing bit position
#define PMIC_HILVLEX_bm 0x04 ///< High Level Interrupt Executing bit mask
#define PMIC_HILVLEX_bp 2 ///< High Level Interrupt Executing bit position
#define PMIC_MEDLVLEX_bm 0x02 ///< Medium Level Interrupt Executing bit mask
#define PMIC_MEDLVLEX_bp 1 ///< Medium Level Interrupt Executing bit position
#define PMIC_LOLVLEX_bm 0x01 ///< Low Level Interrupt Executing bit mask
#define PMIC_LOLVLEX_bp 0 ///< Low Level Interrupt Executing bit position
/** @} */
	
/** @name PMIC.CTRL
  * @{
  */
#define PMIC_RREN_bm 0x80 ///< Round-Robin Priority Enable bit mask
#define PMIC_RREN_bp 7 ///< Round-Robin Priority Enable bit position
#define PMIC_IVSEL_bm 0x40 ///< Interrupt Vector Select bit mask
#define PMIC_IVSEL_bp 6 ///< Interrupt Vector Select bit position
#define PMIC_HILVLEN_bm 0x04 ///< High Level Enable bit mask
#define PMIC_HILVLEN_bp 2 ///< High Level Enable bit position
#define PMIC_MEDLVLEN_bm 0x02 ///< Medium Level Enable bit mask
#define PMIC_MEDLVLEN_bp 1 ///< Medium Level Enable bit position
#define PMIC_LOLVLEN_bm 0x01 ///< Low Level Enable bit mask
#define PMIC_LOLVLEN_bp 0 ///< Low Level Enable bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup dma DMA Controller
 *  @{
 */
	
/** @name DMA_CH.CTRLA
  * @see DMA_CH_BURSTLEN_enum
  * @{
  */
#define DMA_CH_ENABLE_bm 0x80 ///< Channel Enable bit mask
#define DMA_CH_ENABLE_bp 7 ///< Channel Enable bit position
#define DMA_CH_RESET_bm 0x40 ///< Channel Software Reset bit mask
#define DMA_CH_RESET_bp 6 ///< Channel Software Reset bit position
#define DMA_CH_REPEAT_bm 0x20 ///< Channel Repeat Mode bit mask
#define DMA_CH_REPEAT_bp 5 ///< Channel Repeat Mode bit position
#define DMA_CH_TRFREQ_bm 0x10 ///< Channel Transfer Request bit mask
#define DMA_CH_TRFREQ_bp 4 ///< Channel Transfer Request bit position
#define DMA_CH_SINGLE_bm 0x04 ///< Channel Single Shot Data Transfer bit mask
#define DMA_CH_SINGLE_bp 2 ///< Channel Single Shot Data Transfer bit position
#define DMA_CH_BURSTLEN_gm 0x03 ///< Channel Transfer Mode group mask
#define DMA_CH_BURSTLEN_gp 0 ///< Channel Transfer Mode group position
#define DMA_CH_BURSTLEN0_bm (1<<0) ///< Channel Transfer Mode bit 0 mask
#define DMA_CH_BURSTLEN0_bp 0 ///< Channel Transfer Mode bit 0 position
#define DMA_CH_BURSTLEN1_bm (1<<1) ///< Channel Transfer Mode bit 1 mask
#define DMA_CH_BURSTLEN1_bp 1 ///< Channel Transfer Mode bit 1 position
/** @} */
	
/** @name DMA_CH.CTRLB
  * @see DMA_CH_ERRINTLVL_enum
  * @see DMA_CH_TRNINTLVL_enum
  * @{
  */
#define DMA_CH_CHBUSY_bm 0x80 ///< Block Transfer Busy bit mask
#define DMA_CH_CHBUSY_bp 7 ///< Block Transfer Busy bit position
#define DMA_CH_CHPEND_bm 0x40 ///< Block Transfer Pending bit mask
#define DMA_CH_CHPEND_bp 6 ///< Block Transfer Pending bit position
#define DMA_CH_ERRIF_bm 0x20 ///< Block Transfer Error Interrupt Flag bit mask
#define DMA_CH_ERRIF_bp 5 ///< Block Transfer Error Interrupt Flag bit position
#define DMA_CH_TRNIF_bm 0x10 ///< Transaction Complete Interrup Flag bit mask
#define DMA_CH_TRNIF_bp 4 ///< Transaction Complete Interrup Flag bit position
#define DMA_CH_ERRINTLVL_gm 0x0C ///< Transfer Error Interrupt Level group mask
#define DMA_CH_ERRINTLVL_gp 2 ///< Transfer Error Interrupt Level group position
#define DMA_CH_ERRINTLVL0_bm (1<<2) ///< Transfer Error Interrupt Level bit 0 mask
#define DMA_CH_ERRINTLVL0_bp 2 ///< Transfer Error Interrupt Level bit 0 position
#define DMA_CH_ERRINTLVL1_bm (1<<3) ///< Transfer Error Interrupt Level bit 1 mask
#define DMA_CH_ERRINTLVL1_bp 3 ///< Transfer Error Interrupt Level bit 1 position
#define DMA_CH_TRNINTLVL_gm 0x03 ///< Transaction Complete Interrupt Level group mask
#define DMA_CH_TRNINTLVL_gp 0 ///< Transaction Complete Interrupt Level group position
#define DMA_CH_TRNINTLVL0_bm (1<<0) ///< Transaction Complete Interrupt Level bit 0 mask
#define DMA_CH_TRNINTLVL0_bp 0 ///< Transaction Complete Interrupt Level bit 0 position
#define DMA_CH_TRNINTLVL1_bm (1<<1) ///< Transaction Complete Interrupt Level bit 1 mask
#define DMA_CH_TRNINTLVL1_bp 1 ///< Transaction Complete Interrupt Level bit 1 position
/** @} */
	
/** @name DMA_CH.ADDRCTRL
  * @see DMA_CH_SRCRELOAD_enum
  * @see DMA_CH_SRCDIR_enum
  * @see DMA_CH_DESTRELOAD_enum
  * @see DMA_CH_DESTDIR_enum
  * @{
  */
#define DMA_CH_SRCRELOAD_gm 0xC0 ///< Channel Source Address Reload group mask
#define DMA_CH_SRCRELOAD_gp 6 ///< Channel Source Address Reload group position
#define DMA_CH_SRCRELOAD0_bm (1<<6) ///< Channel Source Address Reload bit 0 mask
#define DMA_CH_SRCRELOAD0_bp 6 ///< Channel Source Address Reload bit 0 position
#define DMA_CH_SRCRELOAD1_bm (1<<7) ///< Channel Source Address Reload bit 1 mask
#define DMA_CH_SRCRELOAD1_bp 7 ///< Channel Source Address Reload bit 1 position
#define DMA_CH_SRCDIR_gm 0x30 ///< Channel Source Address Mode group mask
#define DMA_CH_SRCDIR_gp 4 ///< Channel Source Address Mode group position
#define DMA_CH_SRCDIR0_bm (1<<4) ///< Channel Source Address Mode bit 0 mask
#define DMA_CH_SRCDIR0_bp 4 ///< Channel Source Address Mode bit 0 position
#define DMA_CH_SRCDIR1_bm (1<<5) ///< Channel Source Address Mode bit 1 mask
#define DMA_CH_SRCDIR1_bp 5 ///< Channel Source Address Mode bit 1 position
#define DMA_CH_DESTRELOAD_gm 0x0C ///< Channel Destination Address Reload group mask
#define DMA_CH_DESTRELOAD_gp 2 ///< Channel Destination Address Reload group position
#define DMA_CH_DESTRELOAD0_bm (1<<2) ///< Channel Destination Address Reload bit 0 mask
#define DMA_CH_DESTRELOAD0_bp 2 ///< Channel Destination Address Reload bit 0 position
#define DMA_CH_DESTRELOAD1_bm (1<<3) ///< Channel Destination Address Reload bit 1 mask
#define DMA_CH_DESTRELOAD1_bp 3 ///< Channel Destination Address Reload bit 1 position
#define DMA_CH_DESTDIR_gm 0x03 ///< Channel Destination Address Mode group mask
#define DMA_CH_DESTDIR_gp 0 ///< Channel Destination Address Mode group position
#define DMA_CH_DESTDIR0_bm (1<<0) ///< Channel Destination Address Mode bit 0 mask
#define DMA_CH_DESTDIR0_bp 0 ///< Channel Destination Address Mode bit 0 position
#define DMA_CH_DESTDIR1_bm (1<<1) ///< Channel Destination Address Mode bit 1 mask
#define DMA_CH_DESTDIR1_bp 1 ///< Channel Destination Address Mode bit 1 position
/** @} */
	
/** @name DMA_CH.TRIGSRC
  * @see DMA_CH_TRIGSRC_enum
  * @{
  */
#define DMA_CH_TRIGSRC_gm 0xFF ///< Channel Trigger Source group mask
#define DMA_CH_TRIGSRC_gp 0 ///< Channel Trigger Source group position
#define DMA_CH_TRIGSRC0_bm (1<<0) ///< Channel Trigger Source bit 0 mask
#define DMA_CH_TRIGSRC0_bp 0 ///< Channel Trigger Source bit 0 position
#define DMA_CH_TRIGSRC1_bm (1<<1) ///< Channel Trigger Source bit 1 mask
#define DMA_CH_TRIGSRC1_bp 1 ///< Channel Trigger Source bit 1 position
#define DMA_CH_TRIGSRC2_bm (1<<2) ///< Channel Trigger Source bit 2 mask
#define DMA_CH_TRIGSRC2_bp 2 ///< Channel Trigger Source bit 2 position
#define DMA_CH_TRIGSRC3_bm (1<<3) ///< Channel Trigger Source bit 3 mask
#define DMA_CH_TRIGSRC3_bp 3 ///< Channel Trigger Source bit 3 position
#define DMA_CH_TRIGSRC4_bm (1<<4) ///< Channel Trigger Source bit 4 mask
#define DMA_CH_TRIGSRC4_bp 4 ///< Channel Trigger Source bit 4 position
#define DMA_CH_TRIGSRC5_bm (1<<5) ///< Channel Trigger Source bit 5 mask
#define DMA_CH_TRIGSRC5_bp 5 ///< Channel Trigger Source bit 5 position
#define DMA_CH_TRIGSRC6_bm (1<<6) ///< Channel Trigger Source bit 6 mask
#define DMA_CH_TRIGSRC6_bp 6 ///< Channel Trigger Source bit 6 position
#define DMA_CH_TRIGSRC7_bm (1<<7) ///< Channel Trigger Source bit 7 mask
#define DMA_CH_TRIGSRC7_bp 7 ///< Channel Trigger Source bit 7 position
/** @} */
	
/** @name DMA.CTRL
  * @see DMA_DBUFMODE_enum
  * @see DMA_PRIMODE_enum
  * @{
  */
#define DMA_ENABLE_bm 0x80 ///< Enable bit mask
#define DMA_ENABLE_bp 7 ///< Enable bit position
#define DMA_RESET_bm 0x40 ///< Software Reset bit mask
#define DMA_RESET_bp 6 ///< Software Reset bit position
#define DMA_DBUFMODE_gm 0x0C ///< Double Buffering Mode group mask
#define DMA_DBUFMODE_gp 2 ///< Double Buffering Mode group position
#define DMA_DBUFMODE0_bm (1<<2) ///< Double Buffering Mode bit 0 mask
#define DMA_DBUFMODE0_bp 2 ///< Double Buffering Mode bit 0 position
#define DMA_DBUFMODE1_bm (1<<3) ///< Double Buffering Mode bit 1 mask
#define DMA_DBUFMODE1_bp 3 ///< Double Buffering Mode bit 1 position
#define DMA_PRIMODE_gm 0x03 ///< Channel Priority Mode group mask
#define DMA_PRIMODE_gp 0 ///< Channel Priority Mode group position
#define DMA_PRIMODE0_bm (1<<0) ///< Channel Priority Mode bit 0 mask
#define DMA_PRIMODE0_bp 0 ///< Channel Priority Mode bit 0 position
#define DMA_PRIMODE1_bm (1<<1) ///< Channel Priority Mode bit 1 mask
#define DMA_PRIMODE1_bp 1 ///< Channel Priority Mode bit 1 position
/** @} */
	
/** @name DMA.INTFLAGS
  * @{
  */
#define DMA_CH3ERRIF_bm 0x80 ///< Channel 3 Block Transfer Error Interrupt Flag bit mask
#define DMA_CH3ERRIF_bp 7 ///< Channel 3 Block Transfer Error Interrupt Flag bit position
#define DMA_CH2ERRIF_bm 0x40 ///< Channel 2 Block Transfer Error Interrupt Flag bit mask
#define DMA_CH2ERRIF_bp 6 ///< Channel 2 Block Transfer Error Interrupt Flag bit position
#define DMA_CH1ERRIF_bm 0x20 ///< Channel 1 Block Transfer Error Interrupt Flag bit mask
#define DMA_CH1ERRIF_bp 5 ///< Channel 1 Block Transfer Error Interrupt Flag bit position
#define DMA_CH0ERRIF_bm 0x10 ///< Channel 0 Block Transfer Error Interrupt Flag bit mask
#define DMA_CH0ERRIF_bp 4 ///< Channel 0 Block Transfer Error Interrupt Flag bit position
#define DMA_CH3TRNIF_bm 0x08 ///< Channel 3 Transaction Complete Interrupt Flag bit mask
#define DMA_CH3TRNIF_bp 3 ///< Channel 3 Transaction Complete Interrupt Flag bit position
#define DMA_CH2TRNIF_bm 0x04 ///< Channel 2 Transaction Complete Interrupt Flag bit mask
#define DMA_CH2TRNIF_bp 2 ///< Channel 2 Transaction Complete Interrupt Flag bit position
#define DMA_CH1TRNIF_bm 0x02 ///< Channel 1 Transaction Complete Interrupt Flag bit mask
#define DMA_CH1TRNIF_bp 1 ///< Channel 1 Transaction Complete Interrupt Flag bit position
#define DMA_CH0TRNIF_bm 0x01 ///< Channel 0 Transaction Complete Interrupt Flag bit mask
#define DMA_CH0TRNIF_bp 0 ///< Channel 0 Transaction Complete Interrupt Flag bit position
/** @} */
	
/** @name DMA.STATUS
  * @{
  */
#define DMA_CH3BUSY_bm 0x80 ///< Channel 3 Block Transfer Busy bit mask
#define DMA_CH3BUSY_bp 7 ///< Channel 3 Block Transfer Busy bit position
#define DMA_CH2BUSY_bm 0x40 ///< Channel 2 Block Transfer Busy bit mask
#define DMA_CH2BUSY_bp 6 ///< Channel 2 Block Transfer Busy bit position
#define DMA_CH1BUSY_bm 0x20 ///< Channel 1 Block Transfer Busy bit mask
#define DMA_CH1BUSY_bp 5 ///< Channel 1 Block Transfer Busy bit position
#define DMA_CH0BUSY_bm 0x10 ///< Channel 0 Block Transfer Busy bit mask
#define DMA_CH0BUSY_bp 4 ///< Channel 0 Block Transfer Busy bit position
#define DMA_CH3PEND_bm 0x08 ///< Channel 3 Block Transfer Pending bit mask
#define DMA_CH3PEND_bp 3 ///< Channel 3 Block Transfer Pending bit position
#define DMA_CH2PEND_bm 0x04 ///< Channel 2 Block Transfer Pending bit mask
#define DMA_CH2PEND_bp 2 ///< Channel 2 Block Transfer Pending bit position
#define DMA_CH1PEND_bm 0x02 ///< Channel 1 Block Transfer Pending bit mask
#define DMA_CH1PEND_bp 1 ///< Channel 1 Block Transfer Pending bit position
#define DMA_CH0PEND_bm 0x01 ///< Channel 0 Block Transfer Pending bit mask
#define DMA_CH0PEND_bp 0 ///< Channel 0 Block Transfer Pending bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Burst mode

typedef enum DMA_CH_BURSTLEN_enum {
	DMA_CH_BURSTLEN_1BYTE_gc = (0x00<<0),	///< 1-byte burst mode
	DMA_CH_BURSTLEN_2BYTE_gc = (0x01<<0),	///< 2-byte burst mode
	DMA_CH_BURSTLEN_4BYTE_gc = (0x02<<0),	///< 4-byte burst mode
	DMA_CH_BURSTLEN_8BYTE_gc = (0x03<<0),	///< 8-byte burst mode
} DMA_CH_BURSTLEN_t;
	
/// Source address reload mode

typedef enum DMA_CH_SRCRELOAD_enum {
	DMA_CH_SRCRELOAD_NONE_gc = (0x00<<6),	///< No reload
	DMA_CH_SRCRELOAD_BLOCK_gc = (0x01<<6),	///< Reload at end of block
	DMA_CH_SRCRELOAD_BURST_gc = (0x02<<6),	///< Reload at end of burst
	DMA_CH_SRCRELOAD_TRANSACTION_gc = (0x03<<6),	///< Reload at end of transaction
} DMA_CH_SRCRELOAD_t;
	
/// Source addressing mode

typedef enum DMA_CH_SRCDIR_enum {
	DMA_CH_SRCDIR_FIXED_gc = (0x00<<4),	///< Fixed
	DMA_CH_SRCDIR_INC_gc = (0x01<<4),	///< Increment
	DMA_CH_SRCDIR_DEC_gc = (0x02<<4),	///< Decrement
} DMA_CH_SRCDIR_t;
	
/// Destination adress reload mode

typedef enum DMA_CH_DESTRELOAD_enum {
	DMA_CH_DESTRELOAD_NONE_gc = (0x00<<2),	///< No reload
	DMA_CH_DESTRELOAD_BLOCK_gc = (0x01<<2),	///< Reload at end of block
	DMA_CH_DESTRELOAD_BURST_gc = (0x02<<2),	///< Reload at end of burst
	DMA_CH_DESTRELOAD_TRANSACTION_gc = (0x03<<2),	///< Reload at end of transaction
} DMA_CH_DESTRELOAD_t;
	
/// Destination adressing mode

typedef enum DMA_CH_DESTDIR_enum {
	DMA_CH_DESTDIR_FIXED_gc = (0x00<<0),	///< Fixed
	DMA_CH_DESTDIR_INC_gc = (0x01<<0),	///< Increment
	DMA_CH_DESTDIR_DEC_gc = (0x02<<0),	///< Decrement
} DMA_CH_DESTDIR_t;
	
/// Transfer trigger source

typedef enum DMA_CH_TRIGSRC_enum {
	DMA_CH_TRIGSRC_OFF_gc = (0x00<<0),	///< Off software triggers only
	DMA_CH_TRIGSRC_EVSYS_CH0_gc = (0x01<<0),	///< Event System Channel 0
	DMA_CH_TRIGSRC_EVSYS_CH1_gc = (0x02<<0),	///< Event System Channel 1
	DMA_CH_TRIGSRC_EVSYS_CH2_gc = (0x03<<0),	///< Event System Channel 2
	DMA_CH_TRIGSRC_ADCA_CH0_gc = (0x10<<0),	///< ADCA Channel 0
	DMA_CH_TRIGSRC_ADCA_CH1_gc = (0x11<<0),	///< ADCA Channel 1
	DMA_CH_TRIGSRC_ADCA_CH2_gc = (0x12<<0),	///< ADCA Channel 2
	DMA_CH_TRIGSRC_ADCA_CH3_gc = (0x13<<0),	///< ADCA Channel 3
	DMA_CH_TRIGSRC_ADCA_CH4_gc = (0x14<<0),	///< ADCA Channel 0,1,2,3 combined
	DMA_CH_TRIGSRC_DACA_CH0_gc = (0x15<<0),	///< DACA Channel 0
	DMA_CH_TRIGSRC_DACA_CH1_gc = (0x16<<0),	///< DACA Channel 1
	DMA_CH_TRIGSRC_ADCB_CH0_gc = (0x20<<0),	///< ADCB Channel 0
	DMA_CH_TRIGSRC_ADCB_CH1_gc = (0x21<<0),	///< ADCB Channel 1
	DMA_CH_TRIGSRC_ADCB_CH2_gc = (0x22<<0),	///< ADCB Channel 2
	DMA_CH_TRIGSRC_ADCB_CH3_gc = (0x23<<0),	///< ADCB Channel 3
	DMA_CH_TRIGSRC_ADCB_CH4_gc = (0x24<<0),	///< ADCB Channel 0,1,2,3 combined
	DMA_CH_TRIGSRC_DACB_CH0_gc = (0x25<<0),	///< DACB Channel 0
	DMA_CH_TRIGSRC_DACB_CH1_gc = (0x26<<0),	///< DACB Channel 1
	DMA_CH_TRIGSRC_TCC0_OVF_gc = (0x40<<0),	///< Timer/Counter C0 Overflow
	DMA_CH_TRIGSRC_TCC0_ERR_gc = (0x41<<0),	///< Timer/Counter C0 Error
	DMA_CH_TRIGSRC_TCC0_CCA_gc = (0x42<<0),	///< Timer/Counter C0 Compare or Capture A
	DMA_CH_TRIGSRC_TCC0_CCB_gc = (0x43<<0),	///< Timer/Counter C0 Compare or Capture B
	DMA_CH_TRIGSRC_TCC0_CCC_gc = (0x44<<0),	///< Timer/Counter C0 Compare or Capture C
	DMA_CH_TRIGSRC_TCC0_CCD_gc = (0x45<<0),	///< Timer/Counter C0 Compare or Capture D
	DMA_CH_TRIGSRC_TCC1_OVF_gc = (0x46<<0),	///< Timer/Counter C1 Overflow
	DMA_CH_TRIGSRC_TCC1_ERR_gc = (0x47<<0),	///< Timer/Counter C1 Error
	DMA_CH_TRIGSRC_TCC1_CCA_gc = (0x48<<0),	///< Timer/Counter C1 Compare or Capture A
	DMA_CH_TRIGSRC_TCC1_CCB_gc = (0x49<<0),	///< Timer/Counter C1 Compare or Capture B
	DMA_CH_TRIGSRC_SPIC_gc = (0x4A<<0),	///< SPI C Transfer Complete
	DMA_CH_TRIGSRC_USARTC0_RXC_gc = (0x4B<<0),	///< USART C0 Receive Complete
	DMA_CH_TRIGSRC_USARTC0_DRE_gc = (0x4C<<0),	///< USART C0 Data Register Empty
	DMA_CH_TRIGSRC_USARTC1_RXC_gc = (0x4E<<0),	///< USART C1 Receive Complete
	DMA_CH_TRIGSRC_USARTC1_DRE_gc = (0x4F<<0),	///< USART C1 Data Register Empty
	DMA_CH_TRIGSRC_TCD0_OVF_gc = (0x60<<0),	///< Timer/Counter D0 Overflow
	DMA_CH_TRIGSRC_TCD0_ERR_gc = (0x61<<0),	///< Timer/Counter D0 Error
	DMA_CH_TRIGSRC_TCD0_CCA_gc = (0x62<<0),	///< Timer/Counter D0 Compare or Capture A
	DMA_CH_TRIGSRC_TCD0_CCB_gc = (0x63<<0),	///< Timer/Counter D0 Compare or Capture B
	DMA_CH_TRIGSRC_TCD0_CCC_gc = (0x64<<0),	///< Timer/Counter D0 Compare or Capture C
	DMA_CH_TRIGSRC_TCD0_CCD_gc = (0x65<<0),	///< Timer/Counter D0 Compare or Capture D
	DMA_CH_TRIGSRC_TCD1_OVF_gc = (0x66<<0),	///< Timer/Counter D1 Overflow
	DMA_CH_TRIGSRC_TCD1_ERR_gc = (0x67<<0),	///< Timer/Counter D1 Error
	DMA_CH_TRIGSRC_TCD1_CCA_gc = (0x68<<0),	///< Timer/Counter D1 Compare or Capture A
	DMA_CH_TRIGSRC_TCD1_CCB_gc = (0x69<<0),	///< Timer/Counter D1 Compare or Capture B
	DMA_CH_TRIGSRC_SPID_gc = (0x6A<<0),	///< SPI D Transfer Complete
	DMA_CH_TRIGSRC_USARTD0_RXC_gc = (0x6B<<0),	///< USART D0 Receive Complete
	DMA_CH_TRIGSRC_USARTD0_DRE_gc = (0x6C<<0),	///< USART D0 Data Register Empty
	DMA_CH_TRIGSRC_USARTD1_RXC_gc = (0x6E<<0),	///< USART D1 Receive Complete
	DMA_CH_TRIGSRC_USARTD1_DRE_gc = (0x6F<<0),	///< USART D1 Data Register Empty
	DMA_CH_TRIGSRC_TCE0_OVF_gc = (0x80<<0),	///< Timer/Counter E0 Overflow
	DMA_CH_TRIGSRC_TCE0_ERR_gc = (0x81<<0),	///< Timer/Counter E0 Error
	DMA_CH_TRIGSRC_TCE0_CCA_gc = (0x82<<0),	///< Timer/Counter E0 Compare or Capture A
	DMA_CH_TRIGSRC_TCE0_CCB_gc = (0x83<<0),	///< Timer/Counter E0 Compare or Capture B
	DMA_CH_TRIGSRC_TCE0_CCC_gc = (0x84<<0),	///< Timer/Counter E0 Compare or Capture C
	DMA_CH_TRIGSRC_TCE0_CCD_gc = (0x85<<0),	///< Timer/Counter E0 Compare or Capture D
	DMA_CH_TRIGSRC_TCE1_OVF_gc = (0x86<<0),	///< Timer/Counter E1 Overflow
	DMA_CH_TRIGSRC_TCE1_ERR_gc = (0x87<<0),	///< Timer/Counter E1 Error
	DMA_CH_TRIGSRC_TCE1_CCA_gc = (0x88<<0),	///< Timer/Counter E1 Compare or Capture A
	DMA_CH_TRIGSRC_TCE1_CCB_gc = (0x89<<0),	///< Timer/Counter E1 Compare or Capture B
	DMA_CH_TRIGSRC_SPIE_gc = (0x8A<<0),	///< SPI E Transfer Complete
	DMA_CH_TRIGSRC_USARTE0_RXC_gc = (0x8B<<0),	///< USART E0 Receive Complete
	DMA_CH_TRIGSRC_USARTE0_DRE_gc = (0x8C<<0),	///< USART E0 Data Register Empty
	DMA_CH_TRIGSRC_USARTE1_RXC_gc = (0x8E<<0),	///< USART E1 Receive Complete
	DMA_CH_TRIGSRC_USARTE1_DRE_gc = (0x8F<<0),	///< USART E1 Data Register Empty
	DMA_CH_TRIGSRC_TCF0_OVF_gc = (0xA0<<0),	///< Timer/Counter F0 Overflow
	DMA_CH_TRIGSRC_TCF0_ERR_gc = (0xA1<<0),	///< Timer/Counter F0 Error
	DMA_CH_TRIGSRC_TCF0_CCA_gc = (0xA2<<0),	///< Timer/Counter F0 Compare or Capture A
	DMA_CH_TRIGSRC_TCF0_CCB_gc = (0xA3<<0),	///< Timer/Counter F0 Compare or Capture B
	DMA_CH_TRIGSRC_TCF0_CCC_gc = (0xA4<<0),	///< Timer/Counter F0 Compare or Capture C
	DMA_CH_TRIGSRC_TCF0_CCD_gc = (0xA5<<0),	///< Timer/Counter F0 Compare or Capture D
	DMA_CH_TRIGSRC_TCF1_OVF_gc = (0xA6<<0),	///< Timer/Counter F1 Overflow
	DMA_CH_TRIGSRC_TCF1_ERR_gc = (0xA7<<0),	///< Timer/Counter F1 Error
	DMA_CH_TRIGSRC_TCF1_CCA_gc = (0xA8<<0),	///< Timer/Counter F1 Compare or Capture A
	DMA_CH_TRIGSRC_TCF1_CCB_gc = (0xA9<<0),	///< Timer/Counter F1 Compare or Capture B
	DMA_CH_TRIGSRC_SPIF_gc = (0xAA<<0),	///< SPI F Transfer Complete
	DMA_CH_TRIGSRC_USARTF0_RXC_gc = (0xAB<<0),	///< USART F0 Receive Complete
	DMA_CH_TRIGSRC_USARTF0_DRE_gc = (0xAC<<0),	///< USART F0 Data Register Empty
	DMA_CH_TRIGSRC_USARTF1_RXC_gc = (0xAE<<0),	///< USART F1 Receive Complete
	DMA_CH_TRIGSRC_USARTF1_DRE_gc = (0xAF<<0),	///< USART F1 Data Register Empty
} DMA_CH_TRIGSRC_t;
	
/// Double buffering mode

typedef enum DMA_DBUFMODE_enum {
	DMA_DBUFMODE_DISABLED_gc = (0x00<<2),	///< Double buffering disabled
	DMA_DBUFMODE_CH01_gc = (0x01<<2),	///< Double buffering enabled on channel 0/1
	DMA_DBUFMODE_CH23_gc = (0x02<<2),	///< Double buffering enabled on channel 2/3
	DMA_DBUFMODE_CH01CH23_gc = (0x03<<2),	///< Double buffering enabled on ch. 0/1 and ch. 2/3
} DMA_DBUFMODE_t;
	
/// Priority mode

typedef enum DMA_PRIMODE_enum {
	DMA_PRIMODE_RR0123_gc = (0x00<<0),	///< Round Robin
	DMA_PRIMODE_CH0RR123_gc = (0x01<<0),	///< Channel 0 > Round Robin on channel 1/2/3
	DMA_PRIMODE_CH01RR23_gc = (0x02<<0),	///< Channel 0 > channel 1 > Round Robin on channel 2/3
	DMA_PRIMODE_CH0123_gc = (0x03<<0),	///< Channel 0 > channel 1 > channel 2 > channel 3
} DMA_PRIMODE_t;
	
/// Interrupt level

typedef enum DMA_CH_ERRINTLVL_enum {
	DMA_CH_ERRINTLVL_OFF_gc = (0x00<<2),	///< Interrupt disabled
	DMA_CH_ERRINTLVL_LO_gc = (0x01<<2),	///< Low level
	DMA_CH_ERRINTLVL_MED_gc = (0x02<<2),	///< Medium level
	DMA_CH_ERRINTLVL_HI_gc = (0x03<<2),	///< High level
} DMA_CH_ERRINTLVL_t;
	
/// Interrupt level

typedef enum DMA_CH_TRNINTLVL_enum {
	DMA_CH_TRNINTLVL_OFF_gc = (0x00<<0),	///< Interrupt disabled
	DMA_CH_TRNINTLVL_LO_gc = (0x01<<0),	///< Low level
	DMA_CH_TRNINTLVL_MED_gc = (0x02<<0),	///< Medium level
	DMA_CH_TRNINTLVL_HI_gc = (0x03<<0),	///< High level
} DMA_CH_TRNINTLVL_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Burst mode
#define DMA_CH_BURSTLEN_1BYTE_gc (0x00<<0)	///< 1-byte burst mode
#define DMA_CH_BURSTLEN_2BYTE_gc (0x01<<0)	///< 2-byte burst mode
#define DMA_CH_BURSTLEN_4BYTE_gc (0x02<<0)	///< 4-byte burst mode
#define DMA_CH_BURSTLEN_8BYTE_gc (0x03<<0)	///< 8-byte burst mode

/// Source address reload mode
#define DMA_CH_SRCRELOAD_NONE_gc (0x00<<6)	///< No reload
#define DMA_CH_SRCRELOAD_BLOCK_gc (0x01<<6)	///< Reload at end of block
#define DMA_CH_SRCRELOAD_BURST_gc (0x02<<6)	///< Reload at end of burst
#define DMA_CH_SRCRELOAD_TRANSACTION_gc (0x03<<6)	///< Reload at end of transaction

/// Source addressing mode
#define DMA_CH_SRCDIR_FIXED_gc (0x00<<4)	///< Fixed
#define DMA_CH_SRCDIR_INC_gc (0x01<<4)	///< Increment
#define DMA_CH_SRCDIR_DEC_gc (0x02<<4)	///< Decrement

/// Destination adress reload mode
#define DMA_CH_DESTRELOAD_NONE_gc (0x00<<2)	///< No reload
#define DMA_CH_DESTRELOAD_BLOCK_gc (0x01<<2)	///< Reload at end of block
#define DMA_CH_DESTRELOAD_BURST_gc (0x02<<2)	///< Reload at end of burst
#define DMA_CH_DESTRELOAD_TRANSACTION_gc (0x03<<2)	///< Reload at end of transaction

/// Destination adressing mode
#define DMA_CH_DESTDIR_FIXED_gc (0x00<<0)	///< Fixed
#define DMA_CH_DESTDIR_INC_gc (0x01<<0)	///< Increment
#define DMA_CH_DESTDIR_DEC_gc (0x02<<0)	///< Decrement

/// Transfer trigger source
#define DMA_CH_TRIGSRC_OFF_gc (0x00<<0)	///< Off software triggers only
#define DMA_CH_TRIGSRC_EVSYS_CH0_gc (0x01<<0)	///< Event System Channel 0
#define DMA_CH_TRIGSRC_EVSYS_CH1_gc (0x02<<0)	///< Event System Channel 1
#define DMA_CH_TRIGSRC_EVSYS_CH2_gc (0x03<<0)	///< Event System Channel 2
#define DMA_CH_TRIGSRC_ADCA_CH0_gc (0x10<<0)	///< ADCA Channel 0
#define DMA_CH_TRIGSRC_ADCA_CH1_gc (0x11<<0)	///< ADCA Channel 1
#define DMA_CH_TRIGSRC_ADCA_CH2_gc (0x12<<0)	///< ADCA Channel 2
#define DMA_CH_TRIGSRC_ADCA_CH3_gc (0x13<<0)	///< ADCA Channel 3
#define DMA_CH_TRIGSRC_ADCA_CH4_gc (0x14<<0)	///< ADCA Channel 0,1,2,3 combined
#define DMA_CH_TRIGSRC_DACA_CH0_gc (0x15<<0)	///< DACA Channel 0
#define DMA_CH_TRIGSRC_DACA_CH1_gc (0x16<<0)	///< DACA Channel 1
#define DMA_CH_TRIGSRC_ADCB_CH0_gc (0x20<<0)	///< ADCB Channel 0
#define DMA_CH_TRIGSRC_ADCB_CH1_gc (0x21<<0)	///< ADCB Channel 1
#define DMA_CH_TRIGSRC_ADCB_CH2_gc (0x22<<0)	///< ADCB Channel 2
#define DMA_CH_TRIGSRC_ADCB_CH3_gc (0x23<<0)	///< ADCB Channel 3
#define DMA_CH_TRIGSRC_ADCB_CH4_gc (0x24<<0)	///< ADCB Channel 0,1,2,3 combined
#define DMA_CH_TRIGSRC_DACB_CH0_gc (0x25<<0)	///< DACB Channel 0
#define DMA_CH_TRIGSRC_DACB_CH1_gc (0x26<<0)	///< DACB Channel 1
#define DMA_CH_TRIGSRC_TCC0_OVF_gc (0x40<<0)	///< Timer/Counter C0 Overflow
#define DMA_CH_TRIGSRC_TCC0_ERR_gc (0x41<<0)	///< Timer/Counter C0 Error
#define DMA_CH_TRIGSRC_TCC0_CCA_gc (0x42<<0)	///< Timer/Counter C0 Compare or Capture A
#define DMA_CH_TRIGSRC_TCC0_CCB_gc (0x43<<0)	///< Timer/Counter C0 Compare or Capture B
#define DMA_CH_TRIGSRC_TCC0_CCC_gc (0x44<<0)	///< Timer/Counter C0 Compare or Capture C
#define DMA_CH_TRIGSRC_TCC0_CCD_gc (0x45<<0)	///< Timer/Counter C0 Compare or Capture D
#define DMA_CH_TRIGSRC_TCC1_OVF_gc (0x46<<0)	///< Timer/Counter C1 Overflow
#define DMA_CH_TRIGSRC_TCC1_ERR_gc (0x47<<0)	///< Timer/Counter C1 Error
#define DMA_CH_TRIGSRC_TCC1_CCA_gc (0x48<<0)	///< Timer/Counter C1 Compare or Capture A
#define DMA_CH_TRIGSRC_TCC1_CCB_gc (0x49<<0)	///< Timer/Counter C1 Compare or Capture B
#define DMA_CH_TRIGSRC_SPIC_gc (0x4A<<0)	///< SPI C Transfer Complete
#define DMA_CH_TRIGSRC_USARTC0_RXC_gc (0x4B<<0)	///< USART C0 Receive Complete
#define DMA_CH_TRIGSRC_USARTC0_DRE_gc (0x4C<<0)	///< USART C0 Data Register Empty
#define DMA_CH_TRIGSRC_USARTC1_RXC_gc (0x4E<<0)	///< USART C1 Receive Complete
#define DMA_CH_TRIGSRC_USARTC1_DRE_gc (0x4F<<0)	///< USART C1 Data Register Empty
#define DMA_CH_TRIGSRC_TCD0_OVF_gc (0x60<<0)	///< Timer/Counter D0 Overflow
#define DMA_CH_TRIGSRC_TCD0_ERR_gc (0x61<<0)	///< Timer/Counter D0 Error
#define DMA_CH_TRIGSRC_TCD0_CCA_gc (0x62<<0)	///< Timer/Counter D0 Compare or Capture A
#define DMA_CH_TRIGSRC_TCD0_CCB_gc (0x63<<0)	///< Timer/Counter D0 Compare or Capture B
#define DMA_CH_TRIGSRC_TCD0_CCC_gc (0x64<<0)	///< Timer/Counter D0 Compare or Capture C
#define DMA_CH_TRIGSRC_TCD0_CCD_gc (0x65<<0)	///< Timer/Counter D0 Compare or Capture D
#define DMA_CH_TRIGSRC_TCD1_OVF_gc (0x66<<0)	///< Timer/Counter D1 Overflow
#define DMA_CH_TRIGSRC_TCD1_ERR_gc (0x67<<0)	///< Timer/Counter D1 Error
#define DMA_CH_TRIGSRC_TCD1_CCA_gc (0x68<<0)	///< Timer/Counter D1 Compare or Capture A
#define DMA_CH_TRIGSRC_TCD1_CCB_gc (0x69<<0)	///< Timer/Counter D1 Compare or Capture B
#define DMA_CH_TRIGSRC_SPID_gc (0x6A<<0)	///< SPI D Transfer Complete
#define DMA_CH_TRIGSRC_USARTD0_RXC_gc (0x6B<<0)	///< USART D0 Receive Complete
#define DMA_CH_TRIGSRC_USARTD0_DRE_gc (0x6C<<0)	///< USART D0 Data Register Empty
#define DMA_CH_TRIGSRC_USARTD1_RXC_gc (0x6E<<0)	///< USART D1 Receive Complete
#define DMA_CH_TRIGSRC_USARTD1_DRE_gc (0x6F<<0)	///< USART D1 Data Register Empty
#define DMA_CH_TRIGSRC_TCE0_OVF_gc (0x80<<0)	///< Timer/Counter E0 Overflow
#define DMA_CH_TRIGSRC_TCE0_ERR_gc (0x81<<0)	///< Timer/Counter E0 Error
#define DMA_CH_TRIGSRC_TCE0_CCA_gc (0x82<<0)	///< Timer/Counter E0 Compare or Capture A
#define DMA_CH_TRIGSRC_TCE0_CCB_gc (0x83<<0)	///< Timer/Counter E0 Compare or Capture B
#define DMA_CH_TRIGSRC_TCE0_CCC_gc (0x84<<0)	///< Timer/Counter E0 Compare or Capture C
#define DMA_CH_TRIGSRC_TCE0_CCD_gc (0x85<<0)	///< Timer/Counter E0 Compare or Capture D
#define DMA_CH_TRIGSRC_TCE1_OVF_gc (0x86<<0)	///< Timer/Counter E1 Overflow
#define DMA_CH_TRIGSRC_TCE1_ERR_gc (0x87<<0)	///< Timer/Counter E1 Error
#define DMA_CH_TRIGSRC_TCE1_CCA_gc (0x88<<0)	///< Timer/Counter E1 Compare or Capture A
#define DMA_CH_TRIGSRC_TCE1_CCB_gc (0x89<<0)	///< Timer/Counter E1 Compare or Capture B
#define DMA_CH_TRIGSRC_SPIE_gc (0x8A<<0)	///< SPI E Transfer Complete
#define DMA_CH_TRIGSRC_USARTE0_RXC_gc (0x8B<<0)	///< USART E0 Receive Complete
#define DMA_CH_TRIGSRC_USARTE0_DRE_gc (0x8C<<0)	///< USART E0 Data Register Empty
#define DMA_CH_TRIGSRC_USARTE1_RXC_gc (0x8E<<0)	///< USART E1 Receive Complete
#define DMA_CH_TRIGSRC_USARTE1_DRE_gc (0x8F<<0)	///< USART E1 Data Register Empty
#define DMA_CH_TRIGSRC_TCF0_OVF_gc (0xA0<<0)	///< Timer/Counter F0 Overflow
#define DMA_CH_TRIGSRC_TCF0_ERR_gc (0xA1<<0)	///< Timer/Counter F0 Error
#define DMA_CH_TRIGSRC_TCF0_CCA_gc (0xA2<<0)	///< Timer/Counter F0 Compare or Capture A
#define DMA_CH_TRIGSRC_TCF0_CCB_gc (0xA3<<0)	///< Timer/Counter F0 Compare or Capture B
#define DMA_CH_TRIGSRC_TCF0_CCC_gc (0xA4<<0)	///< Timer/Counter F0 Compare or Capture C
#define DMA_CH_TRIGSRC_TCF0_CCD_gc (0xA5<<0)	///< Timer/Counter F0 Compare or Capture D
#define DMA_CH_TRIGSRC_TCF1_OVF_gc (0xA6<<0)	///< Timer/Counter F1 Overflow
#define DMA_CH_TRIGSRC_TCF1_ERR_gc (0xA7<<0)	///< Timer/Counter F1 Error
#define DMA_CH_TRIGSRC_TCF1_CCA_gc (0xA8<<0)	///< Timer/Counter F1 Compare or Capture A
#define DMA_CH_TRIGSRC_TCF1_CCB_gc (0xA9<<0)	///< Timer/Counter F1 Compare or Capture B
#define DMA_CH_TRIGSRC_SPIF_gc (0xAA<<0)	///< SPI F Transfer Complete
#define DMA_CH_TRIGSRC_USARTF0_RXC_gc (0xAB<<0)	///< USART F0 Receive Complete
#define DMA_CH_TRIGSRC_USARTF0_DRE_gc (0xAC<<0)	///< USART F0 Data Register Empty
#define DMA_CH_TRIGSRC_USARTF1_RXC_gc (0xAE<<0)	///< USART F1 Receive Complete
#define DMA_CH_TRIGSRC_USARTF1_DRE_gc (0xAF<<0)	///< USART F1 Data Register Empty

/// Double buffering mode
#define DMA_DBUFMODE_DISABLED_gc (0x00<<2)	///< Double buffering disabled
#define DMA_DBUFMODE_CH01_gc (0x01<<2)	///< Double buffering enabled on channel 0/1
#define DMA_DBUFMODE_CH23_gc (0x02<<2)	///< Double buffering enabled on channel 2/3
#define DMA_DBUFMODE_CH01CH23_gc (0x03<<2)	///< Double buffering enabled on ch. 0/1 and ch. 2/3

/// Priority mode
#define DMA_PRIMODE_RR0123_gc (0x00<<0)	///< Round Robin
#define DMA_PRIMODE_CH0RR123_gc (0x01<<0)	///< Channel 0 > Round Robin on channel 1/2/3
#define DMA_PRIMODE_CH01RR23_gc (0x02<<0)	///< Channel 0 > channel 1 > Round Robin on channel 2/3
#define DMA_PRIMODE_CH0123_gc (0x03<<0)	///< Channel 0 > channel 1 > channel 2 > channel 3

/// Interrupt level
#define DMA_CH_ERRINTLVL_OFF_gc (0x00<<2)	///< Interrupt disabled
#define DMA_CH_ERRINTLVL_LO_gc (0x01<<2)	///< Low level
#define DMA_CH_ERRINTLVL_MED_gc (0x02<<2)	///< Medium level
#define DMA_CH_ERRINTLVL_HI_gc (0x03<<2)	///< High level

/// Interrupt level
#define DMA_CH_TRNINTLVL_OFF_gc (0x00<<0)	///< Interrupt disabled
#define DMA_CH_TRNINTLVL_LO_gc (0x01<<0)	///< Low level
#define DMA_CH_TRNINTLVL_MED_gc (0x02<<0)	///< Medium level
#define DMA_CH_TRNINTLVL_HI_gc (0x03<<0)	///< High level

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup evsys Event System
 *  @{
 */
	
/** @name EVSYS.CH0MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
#define EVSYS_CHMUX_gm 0xFF ///< Event Channel 0 Multiplexer group mask
#define EVSYS_CHMUX_gp 0 ///< Event Channel 0 Multiplexer group position
#define EVSYS_CHMUX0_bm (1<<0) ///< Event Channel 0 Multiplexer bit 0 mask
#define EVSYS_CHMUX0_bp 0 ///< Event Channel 0 Multiplexer bit 0 position
#define EVSYS_CHMUX1_bm (1<<1) ///< Event Channel 0 Multiplexer bit 1 mask
#define EVSYS_CHMUX1_bp 1 ///< Event Channel 0 Multiplexer bit 1 position
#define EVSYS_CHMUX2_bm (1<<2) ///< Event Channel 0 Multiplexer bit 2 mask
#define EVSYS_CHMUX2_bp 2 ///< Event Channel 0 Multiplexer bit 2 position
#define EVSYS_CHMUX3_bm (1<<3) ///< Event Channel 0 Multiplexer bit 3 mask
#define EVSYS_CHMUX3_bp 3 ///< Event Channel 0 Multiplexer bit 3 position
#define EVSYS_CHMUX4_bm (1<<4) ///< Event Channel 0 Multiplexer bit 4 mask
#define EVSYS_CHMUX4_bp 4 ///< Event Channel 0 Multiplexer bit 4 position
#define EVSYS_CHMUX5_bm (1<<5) ///< Event Channel 0 Multiplexer bit 5 mask
#define EVSYS_CHMUX5_bp 5 ///< Event Channel 0 Multiplexer bit 5 position
#define EVSYS_CHMUX6_bm (1<<6) ///< Event Channel 0 Multiplexer bit 6 mask
#define EVSYS_CHMUX6_bp 6 ///< Event Channel 0 Multiplexer bit 6 position
#define EVSYS_CHMUX7_bm (1<<7) ///< Event Channel 0 Multiplexer bit 7 mask
#define EVSYS_CHMUX7_bp 7 ///< Event Channel 0 Multiplexer bit 7 position
/** @} */
	
/** @name EVSYS.CH1MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH2MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH3MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH4MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH5MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH6MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH7MUX
  * @see EVSYS_CHMUX_enum
  * @{
  */
// Masks for CHMUX aready defined
/** @} */
	
/** @name EVSYS.CH0CTRL
  * @see EVSYS_DIGFILT_enum
  * @{
  */
#define EVSYS_QDIRM_gm 0x60 ///< Quadrature Decoder Index Recognition Mode group mask
#define EVSYS_QDIRM_gp 5 ///< Quadrature Decoder Index Recognition Mode group position
#define EVSYS_QDIRM0_bm (1<<5) ///< Quadrature Decoder Index Recognition Mode bit 0 mask
#define EVSYS_QDIRM0_bp 5 ///< Quadrature Decoder Index Recognition Mode bit 0 position
#define EVSYS_QDIRM1_bm (1<<6) ///< Quadrature Decoder Index Recognition Mode bit 1 mask
#define EVSYS_QDIRM1_bp 6 ///< Quadrature Decoder Index Recognition Mode bit 1 position
#define EVSYS_QDIEN_bm 0x10 ///< Quadrature Decoder Index Enable bit mask
#define EVSYS_QDIEN_bp 4 ///< Quadrature Decoder Index Enable bit position
#define EVSYS_QDEN_bm 0x08 ///< Quadrature Decoder Enable bit mask
#define EVSYS_QDEN_bp 3 ///< Quadrature Decoder Enable bit position
#define EVSYS_DIGFILT_gm 0x07 ///< Digital Filter group mask
#define EVSYS_DIGFILT_gp 0 ///< Digital Filter group position
#define EVSYS_DIGFILT0_bm (1<<0) ///< Digital Filter bit 0 mask
#define EVSYS_DIGFILT0_bp 0 ///< Digital Filter bit 0 position
#define EVSYS_DIGFILT1_bm (1<<1) ///< Digital Filter bit 1 mask
#define EVSYS_DIGFILT1_bp 1 ///< Digital Filter bit 1 position
#define EVSYS_DIGFILT2_bm (1<<2) ///< Digital Filter bit 2 mask
#define EVSYS_DIGFILT2_bp 2 ///< Digital Filter bit 2 position
/** @} */
	
/** @name EVSYS.CH1CTRL
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for DIGFILT aready defined
/** @} */
	
/** @name EVSYS.CH2CTRL
  * @see EVSYS_QDIRM_enum
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for QDIRM aready defined
// Masks for QDIEN aready defined
// Masks for QDEN aready defined
// Masks for DIGFILT aready defined
/** @} */
	
/** @name EVSYS.CH3CTRL
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for DIGFILT aready defined
/** @} */
	
/** @name EVSYS.CH4CTRL
  * @see EVSYS_QDIRM_enum
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for QDIRM aready defined
// Masks for QDIEN aready defined
// Masks for QDEN aready defined
// Masks for DIGFILT aready defined
/** @} */
	
/** @name EVSYS.CH5CTRL
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for DIGFILT aready defined
/** @} */
	
/** @name EVSYS.CH6CTRL
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for DIGFILT aready defined
/** @} */
	
/** @name EVSYS.CH7CTRL
  * @see EVSYS_DIGFILT_enum
  * @{
  */
// Masks for DIGFILT aready defined
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Quadrature Decoder Index Recognition Mode

typedef enum EVSYS_QDIRM_enum {
	EVSYS_QDIRM_00_gc = (0x00<<5),	///< QDPH0 = 0, QDPH90 = 0
	EVSYS_QDIRM_01_gc = (0x01<<5),	///< QDPH0 = 0, QDPH90 = 1
	EVSYS_QDIRM_10_gc = (0x02<<5),	///< QDPH0 = 1, QDPH90 = 0
	EVSYS_QDIRM_11_gc = (0x03<<5),	///< QDPH0 = 1, QDPH90 = 1
} EVSYS_QDIRM_t;
	
/// Digital filter coefficient

typedef enum EVSYS_DIGFILT_enum {
	EVSYS_DIGFILT_1SAMPLE_gc = (0x00<<0),	///< 1 SAMPLE
	EVSYS_DIGFILT_2SAMPLES_gc = (0x01<<0),	///< 2 SAMPLES
	EVSYS_DIGFILT_3SAMPLES_gc = (0x02<<0),	///< 3 SAMPLES
	EVSYS_DIGFILT_4SAMPLES_gc = (0x03<<0),	///< 4 SAMPLES
	EVSYS_DIGFILT_5SAMPLES_gc = (0x04<<0),	///< 5 SAMPLES
	EVSYS_DIGFILT_6SAMPLES_gc = (0x05<<0),	///< 6 SAMPLES
	EVSYS_DIGFILT_7SAMPLES_gc = (0x06<<0),	///< 7 SAMPLES
	EVSYS_DIGFILT_8SAMPLES_gc = (0x07<<0),	///< 8 SAMPLES
} EVSYS_DIGFILT_t;
	
/// Event Channel multiplexer input selection

typedef enum EVSYS_CHMUX_enum {
	EVSYS_CHMUX_OFF_gc = (0x00<<0),	///< Off
	EVSYS_CHMUX_RTC_OVF_gc = (0x08<<0),	///< RTC Overflow
	EVSYS_CHMUX_RTC_CMP_gc = (0x09<<0),	///< RTC Compare Match
	EVSYS_CHMUX_ACA_CH0_gc = (0x10<<0),	///< Analog Comparator A Channel 0
	EVSYS_CHMUX_ACA_CH1_gc = (0x11<<0),	///< Analog Comparator A Channel 1
	EVSYS_CHMUX_ACA_WIN_gc = (0x12<<0),	///< Analog Comparator A Window
	EVSYS_CHMUX_ACB_CH0_gc = (0x13<<0),	///< Analog Comparator B Channel 0
	EVSYS_CHMUX_ACB_CH1_gc = (0x14<<0),	///< Analog Comparator B Channel 1
	EVSYS_CHMUX_ACB_WIN_gc = (0x15<<0),	///< Analog Comparator B Window
	EVSYS_CHMUX_ADCA_CH0_gc = (0x20<<0),	///< ADC A Channel 0
	EVSYS_CHMUX_ADCA_CH1_gc = (0x21<<0),	///< ADC A Channel 1
	EVSYS_CHMUX_ADCA_CH2_gc = (0x22<<0),	///< ADC A Channel 2
	EVSYS_CHMUX_ADCA_CH3_gc = (0x23<<0),	///< ADC A Channel 3
	EVSYS_CHMUX_ADCB_CH0_gc = (0x24<<0),	///< ADC B Channel 0
	EVSYS_CHMUX_ADCB_CH1_gc = (0x25<<0),	///< ADC B Channel 1
	EVSYS_CHMUX_ADCB_CH2_gc = (0x26<<0),	///< ADC B Channel 2
	EVSYS_CHMUX_ADCB_CH3_gc = (0x27<<0),	///< ADC B Channel 3
	EVSYS_CHMUX_PORTA_PIN0_gc = (0x50<<0),	///< Port A, Pin0
	EVSYS_CHMUX_PORTA_PIN1_gc = (0x51<<0),	///< Port A, Pin1
	EVSYS_CHMUX_PORTA_PIN2_gc = (0x52<<0),	///< Port A, Pin2
	EVSYS_CHMUX_PORTA_PIN3_gc = (0x53<<0),	///< Port A, Pin3
	EVSYS_CHMUX_PORTA_PIN4_gc = (0x54<<0),	///< Port A, Pin4
	EVSYS_CHMUX_PORTA_PIN5_gc = (0x55<<0),	///< Port A, Pin5
	EVSYS_CHMUX_PORTA_PIN6_gc = (0x56<<0),	///< Port A, Pin6
	EVSYS_CHMUX_PORTA_PIN7_gc = (0x57<<0),	///< Port A, Pin7
	EVSYS_CHMUX_PORTB_PIN0_gc = (0x58<<0),	///< Port B, Pin0
	EVSYS_CHMUX_PORTB_PIN1_gc = (0x59<<0),	///< Port B, Pin1
	EVSYS_CHMUX_PORTB_PIN2_gc = (0x5A<<0),	///< Port B, Pin2
	EVSYS_CHMUX_PORTB_PIN3_gc = (0x5B<<0),	///< Port B, Pin3
	EVSYS_CHMUX_PORTB_PIN4_gc = (0x5C<<0),	///< Port B, Pin4
	EVSYS_CHMUX_PORTB_PIN5_gc = (0x5D<<0),	///< Port B, Pin5
	EVSYS_CHMUX_PORTB_PIN6_gc = (0x5E<<0),	///< Port B, Pin6
	EVSYS_CHMUX_PORTB_PIN7_gc = (0x5F<<0),	///< Port B, Pin7
	EVSYS_CHMUX_PORTC_PIN0_gc = (0x60<<0),	///< Port C, Pin0
	EVSYS_CHMUX_PORTC_PIN1_gc = (0x61<<0),	///< Port C, Pin1
	EVSYS_CHMUX_PORTC_PIN2_gc = (0x62<<0),	///< Port C, Pin2
	EVSYS_CHMUX_PORTC_PIN3_gc = (0x63<<0),	///< Port C, Pin3
	EVSYS_CHMUX_PORTC_PIN4_gc = (0x64<<0),	///< Port C, Pin4
	EVSYS_CHMUX_PORTC_PIN5_gc = (0x65<<0),	///< Port C, Pin5
	EVSYS_CHMUX_PORTC_PIN6_gc = (0x66<<0),	///< Port C, Pin6
	EVSYS_CHMUX_PORTC_PIN7_gc = (0x67<<0),	///< Port C, Pin7
	EVSYS_CHMUX_PORTD_PIN0_gc = (0x68<<0),	///< Port D, Pin0
	EVSYS_CHMUX_PORTD_PIN1_gc = (0x69<<0),	///< Port D, Pin1
	EVSYS_CHMUX_PORTD_PIN2_gc = (0x6A<<0),	///< Port D, Pin2
	EVSYS_CHMUX_PORTD_PIN3_gc = (0x6B<<0),	///< Port D, Pin3
	EVSYS_CHMUX_PORTD_PIN4_gc = (0x6C<<0),	///< Port D, Pin4
	EVSYS_CHMUX_PORTD_PIN5_gc = (0x6D<<0),	///< Port D, Pin5
	EVSYS_CHMUX_PORTD_PIN6_gc = (0x6E<<0),	///< Port D, Pin6
	EVSYS_CHMUX_PORTD_PIN7_gc = (0x6F<<0),	///< Port D, Pin7
	EVSYS_CHMUX_PORTE_PIN0_gc = (0x70<<0),	///< Port E, Pin0
	EVSYS_CHMUX_PORTE_PIN1_gc = (0x71<<0),	///< Port E, Pin1
	EVSYS_CHMUX_PORTE_PIN2_gc = (0x72<<0),	///< Port E, Pin2
	EVSYS_CHMUX_PORTE_PIN3_gc = (0x73<<0),	///< Port E, Pin3
	EVSYS_CHMUX_PORTE_PIN4_gc = (0x74<<0),	///< Port E, Pin4
	EVSYS_CHMUX_PORTE_PIN5_gc = (0x75<<0),	///< Port E, Pin5
	EVSYS_CHMUX_PORTE_PIN6_gc = (0x76<<0),	///< Port E, Pin6
	EVSYS_CHMUX_PORTE_PIN7_gc = (0x77<<0),	///< Port E, Pin7
	EVSYS_CHMUX_PORTF_PIN0_gc = (0x78<<0),	///< Port F, Pin0
	EVSYS_CHMUX_PORTF_PIN1_gc = (0x79<<0),	///< Port F, Pin1
	EVSYS_CHMUX_PORTF_PIN2_gc = (0x7A<<0),	///< Port F, Pin2
	EVSYS_CHMUX_PORTF_PIN3_gc = (0x7B<<0),	///< Port F, Pin3
	EVSYS_CHMUX_PORTF_PIN4_gc = (0x7C<<0),	///< Port F, Pin4
	EVSYS_CHMUX_PORTF_PIN5_gc = (0x7D<<0),	///< Port F, Pin5
	EVSYS_CHMUX_PORTF_PIN6_gc = (0x7E<<0),	///< Port F, Pin6
	EVSYS_CHMUX_PORTF_PIN7_gc = (0x7F<<0),	///< Port F, Pin7
	EVSYS_CHMUX_PRESCALER_1_gc = (0x80<<0),	///< Prescaler, divide by 1
	EVSYS_CHMUX_PRESCALER_2_gc = (0x81<<0),	///< Prescaler, divide by 2
	EVSYS_CHMUX_PRESCALER_4_gc = (0x82<<0),	///< Prescaler, divide by 4
	EVSYS_CHMUX_PRESCALER_8_gc = (0x83<<0),	///< Prescaler, divide by 8
	EVSYS_CHMUX_PRESCALER_16_gc = (0x84<<0),	///< Prescaler, divide by 16
	EVSYS_CHMUX_PRESCALER_32_gc = (0x85<<0),	///< Prescaler, divide by 32
	EVSYS_CHMUX_PRESCALER_64_gc = (0x86<<0),	///< Prescaler, divide by 64
	EVSYS_CHMUX_PRESCALER_128_gc = (0x87<<0),	///< Prescaler, divide by 128
	EVSYS_CHMUX_PRESCALER_256_gc = (0x88<<0),	///< Prescaler, divide by 256
	EVSYS_CHMUX_PRESCALER_512_gc = (0x89<<0),	///< Prescaler, divide by 512
	EVSYS_CHMUX_PRESCALER_1024_gc = (0x8A<<0),	///< Prescaler, divide by 1024
	EVSYS_CHMUX_PRESCALER_2048_gc = (0x8B<<0),	///< Prescaler, divide by 2048
	EVSYS_CHMUX_PRESCALER_4096_gc = (0x8C<<0),	///< Prescaler, divide by 4096
	EVSYS_CHMUX_PRESCALER_8192_gc = (0x8D<<0),	///< Prescaler, divide by 8192
	EVSYS_CHMUX_PRESCALER_16384_gc = (0x8E<<0),	///< Prescaler, divide by 16384
	EVSYS_CHMUX_PRESCALER_32768_gc = (0x8F<<0),	///< Prescaler, divide by 32768
	EVSYS_CHMUX_TCC0_OVF_gc = (0xC0<<0),	///< Timer/Counter C0 Overflow
	EVSYS_CHMUX_TCC0_ERR_gc = (0xC1<<0),	///< Timer/Counter C0 Error
	EVSYS_CHMUX_TCC0_CCA_gc = (0xC4<<0),	///< Timer/Counter C0 Compare or Capture A
	EVSYS_CHMUX_TCC0_CCB_gc = (0xC5<<0),	///< Timer/Counter C0 Compare or Capture B
	EVSYS_CHMUX_TCC0_CCC_gc = (0xC6<<0),	///< Timer/Counter C0 Compare or Capture C
	EVSYS_CHMUX_TCC0_CCD_gc = (0xC7<<0),	///< Timer/Counter C0 Compare or Capture D
	EVSYS_CHMUX_TCC1_OVF_gc = (0xC8<<0),	///< Timer/Counter C1 Overflow
	EVSYS_CHMUX_TCC1_ERR_gc = (0xC9<<0),	///< Timer/Counter C1 Error
	EVSYS_CHMUX_TCC1_CCA_gc = (0xCC<<0),	///< Timer/Counter C1 Compare or Capture A
	EVSYS_CHMUX_TCC1_CCB_gc = (0xCD<<0),	///< Timer/Counter C1 Compare or Capture B
	EVSYS_CHMUX_TCD0_OVF_gc = (0xD0<<0),	///< Timer/Counter D0 Overflow
	EVSYS_CHMUX_TCD0_ERR_gc = (0xD1<<0),	///< Timer/Counter D0 Error
	EVSYS_CHMUX_TCD0_CCA_gc = (0xD4<<0),	///< Timer/Counter D0 Compare or Capture A
	EVSYS_CHMUX_TCD0_CCB_gc = (0xD5<<0),	///< Timer/Counter D0 Compare or Capture B
	EVSYS_CHMUX_TCD0_CCC_gc = (0xD6<<0),	///< Timer/Counter D0 Compare or Capture C
	EVSYS_CHMUX_TCD0_CCD_gc = (0xD7<<0),	///< Timer/Counter D0 Compare or Capture D
	EVSYS_CHMUX_TCD1_OVF_gc = (0xD8<<0),	///< Timer/Counter D1 Overflow
	EVSYS_CHMUX_TCD1_ERR_gc = (0xD9<<0),	///< Timer/Counter D1 Error
	EVSYS_CHMUX_TCD1_CCA_gc = (0xDC<<0),	///< Timer/Counter D1 Compare or Capture A
	EVSYS_CHMUX_TCD1_CCB_gc = (0xDD<<0),	///< Timer/Counter D1 Compare or Capture B
	EVSYS_CHMUX_TCE0_OVF_gc = (0xE0<<0),	///< Timer/Counter E0 Overflow
	EVSYS_CHMUX_TCE0_ERR_gc = (0xE1<<0),	///< Timer/Counter E0 Error
	EVSYS_CHMUX_TCE0_CCA_gc = (0xE4<<0),	///< Timer/Counter E0 Compare or Capture A
	EVSYS_CHMUX_TCE0_CCB_gc = (0xE5<<0),	///< Timer/Counter E0 Compare or Capture B
	EVSYS_CHMUX_TCE0_CCC_gc = (0xE6<<0),	///< Timer/Counter E0 Compare or Capture C
	EVSYS_CHMUX_TCE0_CCD_gc = (0xE7<<0),	///< Timer/Counter E0 Compare or Capture D
	EVSYS_CHMUX_TCE1_OVF_gc = (0xE8<<0),	///< Timer/Counter E1 Overflow
	EVSYS_CHMUX_TCE1_ERR_gc = (0xE9<<0),	///< Timer/Counter E1 Error
	EVSYS_CHMUX_TCE1_CCA_gc = (0xEC<<0),	///< Timer/Counter E1 Compare or Capture A
	EVSYS_CHMUX_TCE1_CCB_gc = (0xED<<0),	///< Timer/Counter E1 Compare or Capture B
	EVSYS_CHMUX_TCF0_OVF_gc = (0xF0<<0),	///< Timer/Counter F0 Overflow
	EVSYS_CHMUX_TCF0_ERR_gc = (0xF1<<0),	///< Timer/Counter F0 Error
	EVSYS_CHMUX_TCF0_CCA_gc = (0xF4<<0),	///< Timer/Counter F0 Compare or Capture A
	EVSYS_CHMUX_TCF0_CCB_gc = (0xF5<<0),	///< Timer/Counter F0 Compare or Capture B
	EVSYS_CHMUX_TCF0_CCC_gc = (0xF6<<0),	///< Timer/Counter F0 Compare or Capture C
	EVSYS_CHMUX_TCF0_CCD_gc = (0xF7<<0),	///< Timer/Counter F0 Compare or Capture D
	EVSYS_CHMUX_TCF1_OVF_gc = (0xF8<<0),	///< Timer/Counter F1 Overflow
	EVSYS_CHMUX_TCF1_ERR_gc = (0xF9<<0),	///< Timer/Counter F1 Error
	EVSYS_CHMUX_TCF1_CCA_gc = (0xFC<<0),	///< Timer/Counter F1 Compare or Capture A
	EVSYS_CHMUX_TCF1_CCB_gc = (0xFD<<0),	///< Timer/Counter F1 Compare or Capture B
} EVSYS_CHMUX_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Quadrature Decoder Index Recognition Mode
#define EVSYS_QDIRM_00_gc (0x00<<5)	///< QDPH0 = 0, QDPH90 = 0
#define EVSYS_QDIRM_01_gc (0x01<<5)	///< QDPH0 = 0, QDPH90 = 1
#define EVSYS_QDIRM_10_gc (0x02<<5)	///< QDPH0 = 1, QDPH90 = 0
#define EVSYS_QDIRM_11_gc (0x03<<5)	///< QDPH0 = 1, QDPH90 = 1

/// Digital filter coefficient
#define EVSYS_DIGFILT_1SAMPLE_gc (0x00<<0)	///< 1 SAMPLE
#define EVSYS_DIGFILT_2SAMPLES_gc (0x01<<0)	///< 2 SAMPLES
#define EVSYS_DIGFILT_3SAMPLES_gc (0x02<<0)	///< 3 SAMPLES
#define EVSYS_DIGFILT_4SAMPLES_gc (0x03<<0)	///< 4 SAMPLES
#define EVSYS_DIGFILT_5SAMPLES_gc (0x04<<0)	///< 5 SAMPLES
#define EVSYS_DIGFILT_6SAMPLES_gc (0x05<<0)	///< 6 SAMPLES
#define EVSYS_DIGFILT_7SAMPLES_gc (0x06<<0)	///< 7 SAMPLES
#define EVSYS_DIGFILT_8SAMPLES_gc (0x07<<0)	///< 8 SAMPLES

/// Event Channel multiplexer input selection
#define EVSYS_CHMUX_OFF_gc (0x00<<0)	///< Off
#define EVSYS_CHMUX_RTC_OVF_gc (0x08<<0)	///< RTC Overflow
#define EVSYS_CHMUX_RTC_CMP_gc (0x09<<0)	///< RTC Compare Match
#define EVSYS_CHMUX_ACA_CH0_gc (0x10<<0)	///< Analog Comparator A Channel 0
#define EVSYS_CHMUX_ACA_CH1_gc (0x11<<0)	///< Analog Comparator A Channel 1
#define EVSYS_CHMUX_ACA_WIN_gc (0x12<<0)	///< Analog Comparator A Window
#define EVSYS_CHMUX_ACB_CH0_gc (0x13<<0)	///< Analog Comparator B Channel 0
#define EVSYS_CHMUX_ACB_CH1_gc (0x14<<0)	///< Analog Comparator B Channel 1
#define EVSYS_CHMUX_ACB_WIN_gc (0x15<<0)	///< Analog Comparator B Window
#define EVSYS_CHMUX_ADCA_CH0_gc (0x20<<0)	///< ADC A Channel 0
#define EVSYS_CHMUX_ADCA_CH1_gc (0x21<<0)	///< ADC A Channel 1
#define EVSYS_CHMUX_ADCA_CH2_gc (0x22<<0)	///< ADC A Channel 2
#define EVSYS_CHMUX_ADCA_CH3_gc (0x23<<0)	///< ADC A Channel 3
#define EVSYS_CHMUX_ADCB_CH0_gc (0x24<<0)	///< ADC B Channel 0
#define EVSYS_CHMUX_ADCB_CH1_gc (0x25<<0)	///< ADC B Channel 1
#define EVSYS_CHMUX_ADCB_CH2_gc (0x26<<0)	///< ADC B Channel 2
#define EVSYS_CHMUX_ADCB_CH3_gc (0x27<<0)	///< ADC B Channel 3
#define EVSYS_CHMUX_PORTA_PIN0_gc (0x50<<0)	///< Port A, Pin0
#define EVSYS_CHMUX_PORTA_PIN1_gc (0x51<<0)	///< Port A, Pin1
#define EVSYS_CHMUX_PORTA_PIN2_gc (0x52<<0)	///< Port A, Pin2
#define EVSYS_CHMUX_PORTA_PIN3_gc (0x53<<0)	///< Port A, Pin3
#define EVSYS_CHMUX_PORTA_PIN4_gc (0x54<<0)	///< Port A, Pin4
#define EVSYS_CHMUX_PORTA_PIN5_gc (0x55<<0)	///< Port A, Pin5
#define EVSYS_CHMUX_PORTA_PIN6_gc (0x56<<0)	///< Port A, Pin6
#define EVSYS_CHMUX_PORTA_PIN7_gc (0x57<<0)	///< Port A, Pin7
#define EVSYS_CHMUX_PORTB_PIN0_gc (0x58<<0)	///< Port B, Pin0
#define EVSYS_CHMUX_PORTB_PIN1_gc (0x59<<0)	///< Port B, Pin1
#define EVSYS_CHMUX_PORTB_PIN2_gc (0x5A<<0)	///< Port B, Pin2
#define EVSYS_CHMUX_PORTB_PIN3_gc (0x5B<<0)	///< Port B, Pin3
#define EVSYS_CHMUX_PORTB_PIN4_gc (0x5C<<0)	///< Port B, Pin4
#define EVSYS_CHMUX_PORTB_PIN5_gc (0x5D<<0)	///< Port B, Pin5
#define EVSYS_CHMUX_PORTB_PIN6_gc (0x5E<<0)	///< Port B, Pin6
#define EVSYS_CHMUX_PORTB_PIN7_gc (0x5F<<0)	///< Port B, Pin7
#define EVSYS_CHMUX_PORTC_PIN0_gc (0x60<<0)	///< Port C, Pin0
#define EVSYS_CHMUX_PORTC_PIN1_gc (0x61<<0)	///< Port C, Pin1
#define EVSYS_CHMUX_PORTC_PIN2_gc (0x62<<0)	///< Port C, Pin2
#define EVSYS_CHMUX_PORTC_PIN3_gc (0x63<<0)	///< Port C, Pin3
#define EVSYS_CHMUX_PORTC_PIN4_gc (0x64<<0)	///< Port C, Pin4
#define EVSYS_CHMUX_PORTC_PIN5_gc (0x65<<0)	///< Port C, Pin5
#define EVSYS_CHMUX_PORTC_PIN6_gc (0x66<<0)	///< Port C, Pin6
#define EVSYS_CHMUX_PORTC_PIN7_gc (0x67<<0)	///< Port C, Pin7
#define EVSYS_CHMUX_PORTD_PIN0_gc (0x68<<0)	///< Port D, Pin0
#define EVSYS_CHMUX_PORTD_PIN1_gc (0x69<<0)	///< Port D, Pin1
#define EVSYS_CHMUX_PORTD_PIN2_gc (0x6A<<0)	///< Port D, Pin2
#define EVSYS_CHMUX_PORTD_PIN3_gc (0x6B<<0)	///< Port D, Pin3
#define EVSYS_CHMUX_PORTD_PIN4_gc (0x6C<<0)	///< Port D, Pin4
#define EVSYS_CHMUX_PORTD_PIN5_gc (0x6D<<0)	///< Port D, Pin5
#define EVSYS_CHMUX_PORTD_PIN6_gc (0x6E<<0)	///< Port D, Pin6
#define EVSYS_CHMUX_PORTD_PIN7_gc (0x6F<<0)	///< Port D, Pin7
#define EVSYS_CHMUX_PORTE_PIN0_gc (0x70<<0)	///< Port E, Pin0
#define EVSYS_CHMUX_PORTE_PIN1_gc (0x71<<0)	///< Port E, Pin1
#define EVSYS_CHMUX_PORTE_PIN2_gc (0x72<<0)	///< Port E, Pin2
#define EVSYS_CHMUX_PORTE_PIN3_gc (0x73<<0)	///< Port E, Pin3
#define EVSYS_CHMUX_PORTE_PIN4_gc (0x74<<0)	///< Port E, Pin4
#define EVSYS_CHMUX_PORTE_PIN5_gc (0x75<<0)	///< Port E, Pin5
#define EVSYS_CHMUX_PORTE_PIN6_gc (0x76<<0)	///< Port E, Pin6
#define EVSYS_CHMUX_PORTE_PIN7_gc (0x77<<0)	///< Port E, Pin7
#define EVSYS_CHMUX_PORTF_PIN0_gc (0x78<<0)	///< Port F, Pin0
#define EVSYS_CHMUX_PORTF_PIN1_gc (0x79<<0)	///< Port F, Pin1
#define EVSYS_CHMUX_PORTF_PIN2_gc (0x7A<<0)	///< Port F, Pin2
#define EVSYS_CHMUX_PORTF_PIN3_gc (0x7B<<0)	///< Port F, Pin3
#define EVSYS_CHMUX_PORTF_PIN4_gc (0x7C<<0)	///< Port F, Pin4
#define EVSYS_CHMUX_PORTF_PIN5_gc (0x7D<<0)	///< Port F, Pin5
#define EVSYS_CHMUX_PORTF_PIN6_gc (0x7E<<0)	///< Port F, Pin6
#define EVSYS_CHMUX_PORTF_PIN7_gc (0x7F<<0)	///< Port F, Pin7
#define EVSYS_CHMUX_PRESCALER_1_gc (0x80<<0)	///< Prescaler, divide by 1
#define EVSYS_CHMUX_PRESCALER_2_gc (0x81<<0)	///< Prescaler, divide by 2
#define EVSYS_CHMUX_PRESCALER_4_gc (0x82<<0)	///< Prescaler, divide by 4
#define EVSYS_CHMUX_PRESCALER_8_gc (0x83<<0)	///< Prescaler, divide by 8
#define EVSYS_CHMUX_PRESCALER_16_gc (0x84<<0)	///< Prescaler, divide by 16
#define EVSYS_CHMUX_PRESCALER_32_gc (0x85<<0)	///< Prescaler, divide by 32
#define EVSYS_CHMUX_PRESCALER_64_gc (0x86<<0)	///< Prescaler, divide by 64
#define EVSYS_CHMUX_PRESCALER_128_gc (0x87<<0)	///< Prescaler, divide by 128
#define EVSYS_CHMUX_PRESCALER_256_gc (0x88<<0)	///< Prescaler, divide by 256
#define EVSYS_CHMUX_PRESCALER_512_gc (0x89<<0)	///< Prescaler, divide by 512
#define EVSYS_CHMUX_PRESCALER_1024_gc (0x8A<<0)	///< Prescaler, divide by 1024
#define EVSYS_CHMUX_PRESCALER_2048_gc (0x8B<<0)	///< Prescaler, divide by 2048
#define EVSYS_CHMUX_PRESCALER_4096_gc (0x8C<<0)	///< Prescaler, divide by 4096
#define EVSYS_CHMUX_PRESCALER_8192_gc (0x8D<<0)	///< Prescaler, divide by 8192
#define EVSYS_CHMUX_PRESCALER_16384_gc (0x8E<<0)	///< Prescaler, divide by 16384
#define EVSYS_CHMUX_PRESCALER_32768_gc (0x8F<<0)	///< Prescaler, divide by 32768
#define EVSYS_CHMUX_TCC0_OVF_gc (0xC0<<0)	///< Timer/Counter C0 Overflow
#define EVSYS_CHMUX_TCC0_ERR_gc (0xC1<<0)	///< Timer/Counter C0 Error
#define EVSYS_CHMUX_TCC0_CCA_gc (0xC4<<0)	///< Timer/Counter C0 Compare or Capture A
#define EVSYS_CHMUX_TCC0_CCB_gc (0xC5<<0)	///< Timer/Counter C0 Compare or Capture B
#define EVSYS_CHMUX_TCC0_CCC_gc (0xC6<<0)	///< Timer/Counter C0 Compare or Capture C
#define EVSYS_CHMUX_TCC0_CCD_gc (0xC7<<0)	///< Timer/Counter C0 Compare or Capture D
#define EVSYS_CHMUX_TCC1_OVF_gc (0xC8<<0)	///< Timer/Counter C1 Overflow
#define EVSYS_CHMUX_TCC1_ERR_gc (0xC9<<0)	///< Timer/Counter C1 Error
#define EVSYS_CHMUX_TCC1_CCA_gc (0xCC<<0)	///< Timer/Counter C1 Compare or Capture A
#define EVSYS_CHMUX_TCC1_CCB_gc (0xCD<<0)	///< Timer/Counter C1 Compare or Capture B
#define EVSYS_CHMUX_TCD0_OVF_gc (0xD0<<0)	///< Timer/Counter D0 Overflow
#define EVSYS_CHMUX_TCD0_ERR_gc (0xD1<<0)	///< Timer/Counter D0 Error
#define EVSYS_CHMUX_TCD0_CCA_gc (0xD4<<0)	///< Timer/Counter D0 Compare or Capture A
#define EVSYS_CHMUX_TCD0_CCB_gc (0xD5<<0)	///< Timer/Counter D0 Compare or Capture B
#define EVSYS_CHMUX_TCD0_CCC_gc (0xD6<<0)	///< Timer/Counter D0 Compare or Capture C
#define EVSYS_CHMUX_TCD0_CCD_gc (0xD7<<0)	///< Timer/Counter D0 Compare or Capture D
#define EVSYS_CHMUX_TCD1_OVF_gc (0xD8<<0)	///< Timer/Counter D1 Overflow
#define EVSYS_CHMUX_TCD1_ERR_gc (0xD9<<0)	///< Timer/Counter D1 Error
#define EVSYS_CHMUX_TCD1_CCA_gc (0xDC<<0)	///< Timer/Counter D1 Compare or Capture A
#define EVSYS_CHMUX_TCD1_CCB_gc (0xDD<<0)	///< Timer/Counter D1 Compare or Capture B
#define EVSYS_CHMUX_TCE0_OVF_gc (0xE0<<0)	///< Timer/Counter E0 Overflow
#define EVSYS_CHMUX_TCE0_ERR_gc (0xE1<<0)	///< Timer/Counter E0 Error
#define EVSYS_CHMUX_TCE0_CCA_gc (0xE4<<0)	///< Timer/Counter E0 Compare or Capture A
#define EVSYS_CHMUX_TCE0_CCB_gc (0xE5<<0)	///< Timer/Counter E0 Compare or Capture B
#define EVSYS_CHMUX_TCE0_CCC_gc (0xE6<<0)	///< Timer/Counter E0 Compare or Capture C
#define EVSYS_CHMUX_TCE0_CCD_gc (0xE7<<0)	///< Timer/Counter E0 Compare or Capture D
#define EVSYS_CHMUX_TCE1_OVF_gc (0xE8<<0)	///< Timer/Counter E1 Overflow
#define EVSYS_CHMUX_TCE1_ERR_gc (0xE9<<0)	///< Timer/Counter E1 Error
#define EVSYS_CHMUX_TCE1_CCA_gc (0xEC<<0)	///< Timer/Counter E1 Compare or Capture A
#define EVSYS_CHMUX_TCE1_CCB_gc (0xED<<0)	///< Timer/Counter E1 Compare or Capture B
#define EVSYS_CHMUX_TCF0_OVF_gc (0xF0<<0)	///< Timer/Counter F0 Overflow
#define EVSYS_CHMUX_TCF0_ERR_gc (0xF1<<0)	///< Timer/Counter F0 Error
#define EVSYS_CHMUX_TCF0_CCA_gc (0xF4<<0)	///< Timer/Counter F0 Compare or Capture A
#define EVSYS_CHMUX_TCF0_CCB_gc (0xF5<<0)	///< Timer/Counter F0 Compare or Capture B
#define EVSYS_CHMUX_TCF0_CCC_gc (0xF6<<0)	///< Timer/Counter F0 Compare or Capture C
#define EVSYS_CHMUX_TCF0_CCD_gc (0xF7<<0)	///< Timer/Counter F0 Compare or Capture D
#define EVSYS_CHMUX_TCF1_OVF_gc (0xF8<<0)	///< Timer/Counter F1 Overflow
#define EVSYS_CHMUX_TCF1_ERR_gc (0xF9<<0)	///< Timer/Counter F1 Error
#define EVSYS_CHMUX_TCF1_CCA_gc (0xFC<<0)	///< Timer/Counter F1 Compare or Capture A
#define EVSYS_CHMUX_TCF1_CCB_gc (0xFD<<0)	///< Timer/Counter F1 Compare or Capture B

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup nvm Non Volatile Memory Controller
 *  @{
 */
	
/** @name NVM.CMD
  * @see NVM_CMD_enum
  * @{
  */
#define NVM_CMD_gm 0xFF ///< Command group mask
#define NVM_CMD_gp 0 ///< Command group position
#define NVM_CMD0_bm (1<<0) ///< Command bit 0 mask
#define NVM_CMD0_bp 0 ///< Command bit 0 position
#define NVM_CMD1_bm (1<<1) ///< Command bit 1 mask
#define NVM_CMD1_bp 1 ///< Command bit 1 position
#define NVM_CMD2_bm (1<<2) ///< Command bit 2 mask
#define NVM_CMD2_bp 2 ///< Command bit 2 position
#define NVM_CMD3_bm (1<<3) ///< Command bit 3 mask
#define NVM_CMD3_bp 3 ///< Command bit 3 position
#define NVM_CMD4_bm (1<<4) ///< Command bit 4 mask
#define NVM_CMD4_bp 4 ///< Command bit 4 position
#define NVM_CMD5_bm (1<<5) ///< Command bit 5 mask
#define NVM_CMD5_bp 5 ///< Command bit 5 position
#define NVM_CMD6_bm (1<<6) ///< Command bit 6 mask
#define NVM_CMD6_bp 6 ///< Command bit 6 position
#define NVM_CMD7_bm (1<<7) ///< Command bit 7 mask
#define NVM_CMD7_bp 7 ///< Command bit 7 position
/** @} */
	
/** @name NVM.CTRLA
  * @{
  */
#define NVM_CMDEX_bm 0x01 ///< Command Execute bit mask
#define NVM_CMDEX_bp 0 ///< Command Execute bit position
/** @} */
	
/** @name NVM.CTRLB
  * @{
  */
#define NVM_EEMAPEN_bm 0x08 ///< EEPROM Mapping Enable bit mask
#define NVM_EEMAPEN_bp 3 ///< EEPROM Mapping Enable bit position
#define NVM_FPRM_bm 0x04 ///< Flash Power Reduction Enable bit mask
#define NVM_FPRM_bp 2 ///< Flash Power Reduction Enable bit position
#define NVM_EPRM_bm 0x02 ///< EEPROM Power Reduction Enable bit mask
#define NVM_EPRM_bp 1 ///< EEPROM Power Reduction Enable bit position
#define NVM_SPMLOCK_bm 0x01 ///< SPM Lock bit mask
#define NVM_SPMLOCK_bp 0 ///< SPM Lock bit position
/** @} */
	
/** @name NVM.INTCTRL
  * @see NVM_SPMLVL_enum
  * @see NVM_EELVL_enum
  * @{
  */
#define NVM_SPMLVL_gm 0x0C ///< SPM Interrupt Level group mask
#define NVM_SPMLVL_gp 2 ///< SPM Interrupt Level group position
#define NVM_SPMLVL0_bm (1<<2) ///< SPM Interrupt Level bit 0 mask
#define NVM_SPMLVL0_bp 2 ///< SPM Interrupt Level bit 0 position
#define NVM_SPMLVL1_bm (1<<3) ///< SPM Interrupt Level bit 1 mask
#define NVM_SPMLVL1_bp 3 ///< SPM Interrupt Level bit 1 position
#define NVM_EELVL_gm 0x03 ///< EEPROM Interrupt Level group mask
#define NVM_EELVL_gp 0 ///< EEPROM Interrupt Level group position
#define NVM_EELVL0_bm (1<<0) ///< EEPROM Interrupt Level bit 0 mask
#define NVM_EELVL0_bp 0 ///< EEPROM Interrupt Level bit 0 position
#define NVM_EELVL1_bm (1<<1) ///< EEPROM Interrupt Level bit 1 mask
#define NVM_EELVL1_bp 1 ///< EEPROM Interrupt Level bit 1 position
/** @} */
	
/** @name NVM.STATUS
  * @{
  */
#define NVM_NVMBUSY_bm 0x80 ///< Non-volatile Memory Busy bit mask
#define NVM_NVMBUSY_bp 7 ///< Non-volatile Memory Busy bit position
#define NVM_FBUSY_bm 0x40 ///< Flash Memory Busy bit mask
#define NVM_FBUSY_bp 6 ///< Flash Memory Busy bit position
#define NVM_EELOAD_bm 0x02 ///< EEPROM Page Buffer Active Loading bit mask
#define NVM_EELOAD_bp 1 ///< EEPROM Page Buffer Active Loading bit position
#define NVM_FLOAD_bm 0x01 ///< Flash Page Buffer Active Loading bit mask
#define NVM_FLOAD_bp 0 ///< Flash Page Buffer Active Loading bit position
/** @} */
	
/** @name NVM.LOCKBITS
  * @see NVM_BLBB_enum
  * @see NVM_BLBA_enum
  * @see NVM_BLBAT_enum
  * @see NVM_LB_enum
  * @{
  */
#define NVM_BLBB_gm 0xC0 ///< Boot Lock Bits - Boot Section group mask
#define NVM_BLBB_gp 6 ///< Boot Lock Bits - Boot Section group position
#define NVM_BLBB0_bm (1<<6) ///< Boot Lock Bits - Boot Section bit 0 mask
#define NVM_BLBB0_bp 6 ///< Boot Lock Bits - Boot Section bit 0 position
#define NVM_BLBB1_bm (1<<7) ///< Boot Lock Bits - Boot Section bit 1 mask
#define NVM_BLBB1_bp 7 ///< Boot Lock Bits - Boot Section bit 1 position
#define NVM_BLBA_gm 0x30 ///< Boot Lock Bits - Application Section group mask
#define NVM_BLBA_gp 4 ///< Boot Lock Bits - Application Section group position
#define NVM_BLBA0_bm (1<<4) ///< Boot Lock Bits - Application Section bit 0 mask
#define NVM_BLBA0_bp 4 ///< Boot Lock Bits - Application Section bit 0 position
#define NVM_BLBA1_bm (1<<5) ///< Boot Lock Bits - Application Section bit 1 mask
#define NVM_BLBA1_bp 5 ///< Boot Lock Bits - Application Section bit 1 position
#define NVM_BLBAT_gm 0x0C ///< Boot Lock Bits - Application Table group mask
#define NVM_BLBAT_gp 2 ///< Boot Lock Bits - Application Table group position
#define NVM_BLBAT0_bm (1<<2) ///< Boot Lock Bits - Application Table bit 0 mask
#define NVM_BLBAT0_bp 2 ///< Boot Lock Bits - Application Table bit 0 position
#define NVM_BLBAT1_bm (1<<3) ///< Boot Lock Bits - Application Table bit 1 mask
#define NVM_BLBAT1_bp 3 ///< Boot Lock Bits - Application Table bit 1 position
#define NVM_LB_gm 0x03 ///< Lock Bits group mask
#define NVM_LB_gp 0 ///< Lock Bits group position
#define NVM_LB0_bm (1<<0) ///< Lock Bits bit 0 mask
#define NVM_LB0_bp 0 ///< Lock Bits bit 0 position
#define NVM_LB1_bm (1<<1) ///< Lock Bits bit 1 mask
#define NVM_LB1_bp 1 ///< Lock Bits bit 1 position
/** @} */
	
/** @name NVM_LOCKBITS.LOCKBITS
  * @see NVM_BLBB_enum
  * @see NVM_BLBA_enum
  * @see NVM_BLBAT_enum
  * @see NVM_LB_enum
  * @{
  */
#define NVM_LOCKBITS_BLBB_gm 0xC0 ///< Boot Lock Bits - Boot Section group mask
#define NVM_LOCKBITS_BLBB_gp 6 ///< Boot Lock Bits - Boot Section group position
#define NVM_LOCKBITS_BLBB0_bm (1<<6) ///< Boot Lock Bits - Boot Section bit 0 mask
#define NVM_LOCKBITS_BLBB0_bp 6 ///< Boot Lock Bits - Boot Section bit 0 position
#define NVM_LOCKBITS_BLBB1_bm (1<<7) ///< Boot Lock Bits - Boot Section bit 1 mask
#define NVM_LOCKBITS_BLBB1_bp 7 ///< Boot Lock Bits - Boot Section bit 1 position
#define NVM_LOCKBITS_BLBA_gm 0x30 ///< Boot Lock Bits - Application Section group mask
#define NVM_LOCKBITS_BLBA_gp 4 ///< Boot Lock Bits - Application Section group position
#define NVM_LOCKBITS_BLBA0_bm (1<<4) ///< Boot Lock Bits - Application Section bit 0 mask
#define NVM_LOCKBITS_BLBA0_bp 4 ///< Boot Lock Bits - Application Section bit 0 position
#define NVM_LOCKBITS_BLBA1_bm (1<<5) ///< Boot Lock Bits - Application Section bit 1 mask
#define NVM_LOCKBITS_BLBA1_bp 5 ///< Boot Lock Bits - Application Section bit 1 position
#define NVM_LOCKBITS_BLBAT_gm 0x0C ///< Boot Lock Bits - Application Table group mask
#define NVM_LOCKBITS_BLBAT_gp 2 ///< Boot Lock Bits - Application Table group position
#define NVM_LOCKBITS_BLBAT0_bm (1<<2) ///< Boot Lock Bits - Application Table bit 0 mask
#define NVM_LOCKBITS_BLBAT0_bp 2 ///< Boot Lock Bits - Application Table bit 0 position
#define NVM_LOCKBITS_BLBAT1_bm (1<<3) ///< Boot Lock Bits - Application Table bit 1 mask
#define NVM_LOCKBITS_BLBAT1_bp 3 ///< Boot Lock Bits - Application Table bit 1 position
#define NVM_LOCKBITS_LB_gm 0x03 ///< Lock Bits group mask
#define NVM_LOCKBITS_LB_gp 0 ///< Lock Bits group position
#define NVM_LOCKBITS_LB0_bm (1<<0) ///< Lock Bits bit 0 mask
#define NVM_LOCKBITS_LB0_bp 0 ///< Lock Bits bit 0 position
#define NVM_LOCKBITS_LB1_bm (1<<1) ///< Lock Bits bit 1 mask
#define NVM_LOCKBITS_LB1_bp 1 ///< Lock Bits bit 1 position
/** @} */
	
/** @name NVM_FUSES.FUSEBYTE0
  * @{
  */
#define NVM_FUSES_USERID_gm 0xFF ///< User ID group mask
#define NVM_FUSES_USERID_gp 0 ///< User ID group position
#define NVM_FUSES_USERID0_bm (1<<0) ///< User ID bit 0 mask
#define NVM_FUSES_USERID0_bp 0 ///< User ID bit 0 position
#define NVM_FUSES_USERID1_bm (1<<1) ///< User ID bit 1 mask
#define NVM_FUSES_USERID1_bp 1 ///< User ID bit 1 position
#define NVM_FUSES_USERID2_bm (1<<2) ///< User ID bit 2 mask
#define NVM_FUSES_USERID2_bp 2 ///< User ID bit 2 position
#define NVM_FUSES_USERID3_bm (1<<3) ///< User ID bit 3 mask
#define NVM_FUSES_USERID3_bp 3 ///< User ID bit 3 position
#define NVM_FUSES_USERID4_bm (1<<4) ///< User ID bit 4 mask
#define NVM_FUSES_USERID4_bp 4 ///< User ID bit 4 position
#define NVM_FUSES_USERID5_bm (1<<5) ///< User ID bit 5 mask
#define NVM_FUSES_USERID5_bp 5 ///< User ID bit 5 position
#define NVM_FUSES_USERID6_bm (1<<6) ///< User ID bit 6 mask
#define NVM_FUSES_USERID6_bp 6 ///< User ID bit 6 position
#define NVM_FUSES_USERID7_bm (1<<7) ///< User ID bit 7 mask
#define NVM_FUSES_USERID7_bp 7 ///< User ID bit 7 position
/** @} */
	
/** @name NVM_FUSES.FUSEBYTE1
  * @see WD_enum
  * @see WD_enum
  * @{
  */
#define NVM_FUSES_WDWP_gm 0xF0 ///< Watchdog Window Timeout Period group mask
#define NVM_FUSES_WDWP_gp 4 ///< Watchdog Window Timeout Period group position
#define NVM_FUSES_WDWP0_bm (1<<4) ///< Watchdog Window Timeout Period bit 0 mask
#define NVM_FUSES_WDWP0_bp 4 ///< Watchdog Window Timeout Period bit 0 position
#define NVM_FUSES_WDWP1_bm (1<<5) ///< Watchdog Window Timeout Period bit 1 mask
#define NVM_FUSES_WDWP1_bp 5 ///< Watchdog Window Timeout Period bit 1 position
#define NVM_FUSES_WDWP2_bm (1<<6) ///< Watchdog Window Timeout Period bit 2 mask
#define NVM_FUSES_WDWP2_bp 6 ///< Watchdog Window Timeout Period bit 2 position
#define NVM_FUSES_WDWP3_bm (1<<7) ///< Watchdog Window Timeout Period bit 3 mask
#define NVM_FUSES_WDWP3_bp 7 ///< Watchdog Window Timeout Period bit 3 position
#define NVM_FUSES_WDP_gm 0x0F ///< Watchdog Timeout Period group mask
#define NVM_FUSES_WDP_gp 0 ///< Watchdog Timeout Period group position
#define NVM_FUSES_WDP0_bm (1<<0) ///< Watchdog Timeout Period bit 0 mask
#define NVM_FUSES_WDP0_bp 0 ///< Watchdog Timeout Period bit 0 position
#define NVM_FUSES_WDP1_bm (1<<1) ///< Watchdog Timeout Period bit 1 mask
#define NVM_FUSES_WDP1_bp 1 ///< Watchdog Timeout Period bit 1 position
#define NVM_FUSES_WDP2_bm (1<<2) ///< Watchdog Timeout Period bit 2 mask
#define NVM_FUSES_WDP2_bp 2 ///< Watchdog Timeout Period bit 2 position
#define NVM_FUSES_WDP3_bm (1<<3) ///< Watchdog Timeout Period bit 3 mask
#define NVM_FUSES_WDP3_bp 3 ///< Watchdog Timeout Period bit 3 position
/** @} */
	
/** @name NVM_FUSES.FUSEBYTE2
  * @see BOOTRST_enum
  * @see BOD_enum
  * @{
  */
#define NVM_FUSES_DVSDON_bm 0x80 ///< Spike Detector Enable bit mask
#define NVM_FUSES_DVSDON_bp 7 ///< Spike Detector Enable bit position
#define NVM_FUSES_BOOTRST_bm 0x40 ///< Boot Loader Section Reset Vector bit mask
#define NVM_FUSES_BOOTRST_bp 6 ///< Boot Loader Section Reset Vector bit position
#define NVM_FUSES_BODPD_gm 0x03 ///< BOD Operation in Power-Down Mode group mask
#define NVM_FUSES_BODPD_gp 0 ///< BOD Operation in Power-Down Mode group position
#define NVM_FUSES_BODPD0_bm (1<<0) ///< BOD Operation in Power-Down Mode bit 0 mask
#define NVM_FUSES_BODPD0_bp 0 ///< BOD Operation in Power-Down Mode bit 0 position
#define NVM_FUSES_BODPD1_bm (1<<1) ///< BOD Operation in Power-Down Mode bit 1 mask
#define NVM_FUSES_BODPD1_bp 1 ///< BOD Operation in Power-Down Mode bit 1 position
/** @} */
	
/** @name NVM_FUSES.FUSEBYTE4
  * @see SUT_enum
  * @{
  */
#define NVM_FUSES_RSTDISBL_bm 0x10 ///< External Reset Disable bit mask
#define NVM_FUSES_RSTDISBL_bp 4 ///< External Reset Disable bit position
#define NVM_FUSES_SUT_gm 0x0C ///< Start-up Time group mask
#define NVM_FUSES_SUT_gp 2 ///< Start-up Time group position
#define NVM_FUSES_SUT0_bm (1<<2) ///< Start-up Time bit 0 mask
#define NVM_FUSES_SUT0_bp 2 ///< Start-up Time bit 0 position
#define NVM_FUSES_SUT1_bm (1<<3) ///< Start-up Time bit 1 mask
#define NVM_FUSES_SUT1_bp 3 ///< Start-up Time bit 1 position
#define NVM_FUSES_WDLOCK_bm 0x02 ///< Watchdog Timer Lock bit mask
#define NVM_FUSES_WDLOCK_bp 1 ///< Watchdog Timer Lock bit position
/** @} */
	
/** @name NVM_FUSES.FUSEBYTE5
  * @see BOD_enum
  * @see BODLVL_enum
  * @{
  */
#define NVM_FUSES_BODACT_gm 0x30 ///< BOD Operation in Active Mode group mask
#define NVM_FUSES_BODACT_gp 4 ///< BOD Operation in Active Mode group position
#define NVM_FUSES_BODACT0_bm (1<<4) ///< BOD Operation in Active Mode bit 0 mask
#define NVM_FUSES_BODACT0_bp 4 ///< BOD Operation in Active Mode bit 0 position
#define NVM_FUSES_BODACT1_bm (1<<5) ///< BOD Operation in Active Mode bit 1 mask
#define NVM_FUSES_BODACT1_bp 5 ///< BOD Operation in Active Mode bit 1 position
#define NVM_FUSES_EESAVE_bm 0x08 ///< Preserve EEPROM Through Chip Erase bit mask
#define NVM_FUSES_EESAVE_bp 3 ///< Preserve EEPROM Through Chip Erase bit position
#define NVM_FUSES_BODLVL_gm 0x07 ///< Brown Out Detection Voltage Level group mask
#define NVM_FUSES_BODLVL_gp 0 ///< Brown Out Detection Voltage Level group position
#define NVM_FUSES_BODLVL0_bm (1<<0) ///< Brown Out Detection Voltage Level bit 0 mask
#define NVM_FUSES_BODLVL0_bp 0 ///< Brown Out Detection Voltage Level bit 0 position
#define NVM_FUSES_BODLVL1_bm (1<<1) ///< Brown Out Detection Voltage Level bit 1 mask
#define NVM_FUSES_BODLVL1_bp 1 ///< Brown Out Detection Voltage Level bit 1 position
#define NVM_FUSES_BODLVL2_bm (1<<2) ///< Brown Out Detection Voltage Level bit 2 mask
#define NVM_FUSES_BODLVL2_bp 2 ///< Brown Out Detection Voltage Level bit 2 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// NVM Command

typedef enum NVM_CMD_enum {
	NVM_CMD_NO_OPERATION_gc = (0x00<<0),	///< Noop/Ordinary LPM
	NVM_CMD_READ_CALIB_ROW_gc = (0x02<<0),	///< Read calibration row
	NVM_CMD_READ_USER_SIG_ROW_gc = (0x01<<0),	///< Read user signature row
	NVM_CMD_READ_EEPROM_gc = (0x06<<0),	///< Read EEPROM
	NVM_CMD_READ_FUSES_gc = (0x07<<0),	///< Read fuse byte
	NVM_CMD_WRITE_LOCK_BITS_gc = (0x08<<0),	///< Write lock bits
	NVM_CMD_ERASE_USER_SIG_ROW_gc = (0x18<<0),	///< Erase user signature row
	NVM_CMD_WRITE_USER_SIG_ROW_gc = (0x1A<<0),	///< Write user signature row
	NVM_CMD_ERASE_APP_gc = (0x20<<0),	///< Erase Application Section
	NVM_CMD_ERASE_APP_PAGE_gc = (0x22<<0),	///< Erase Application Section page
	NVM_CMD_LOAD_FLASH_BUFFER_gc = (0x23<<0),	///< Load Flash page buffer
	NVM_CMD_WRITE_APP_PAGE_gc = (0x24<<0),	///< Write Application Section page
	NVM_CMD_ERASE_WRITE_APP_PAGE_gc = (0x25<<0),	///< Erase-and-write Application Section page
	NVM_CMD_ERASE_FLASH_BUFFER_gc = (0x26<<0),	///< Erase/flush Flash page buffer
	NVM_CMD_ERASE_BOOT_PAGE_gc = (0x2A<<0),	///< Erase Boot Section page
	NVM_CMD_WRITE_BOOT_PAGE_gc = (0x2C<<0),	///< Write Boot Section page
	NVM_CMD_ERASE_WRITE_BOOT_PAGE_gc = (0x2D<<0),	///< Erase-and-write Boot Section page
	NVM_CMD_ERASE_EEPROM_gc = (0x30<<0),	///< Erase EEPROM
	NVM_CMD_ERASE_EEPROM_PAGE_gc = (0x32<<0),	///< Erase EEPROM page
	NVM_CMD_LOAD_EEPROM_BUFFER_gc = (0x33<<0),	///< Load EEPROM page buffer
	NVM_CMD_WRITE_EEPROM_PAGE_gc = (0x34<<0),	///< Write EEPROM page
	NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc = (0x35<<0),	///< Erase-and-write EEPROM page
	NVM_CMD_ERASE_EEPROM_BUFFER_gc = (0x36<<0),	///< Erase/flush EEPROM page buffer
	NVM_CMD_APP_CRC_gc = (0x38<<0),	///< Generate Application section CRC
	NVM_CMD_BOOT_CRC_gc = (0x39<<0),	///< Generate Boot Section CRC
	NVM_CMD_FLASH_RANGE_CRC_gc = (0x3A<<0),	///< Generate Flash Range CRC
} NVM_CMD_t;
	
/// SPM ready interrupt level

typedef enum NVM_SPMLVL_enum {
	NVM_SPMLVL_OFF_gc = (0x00<<2),	///< Interrupt disabled
	NVM_SPMLVL_LO_gc = (0x01<<2),	///< Low level
	NVM_SPMLVL_MED_gc = (0x02<<2),	///< Medium level
	NVM_SPMLVL_HI_gc = (0x03<<2),	///< High level
} NVM_SPMLVL_t;
	
/// EEPROM ready interrupt level

typedef enum NVM_EELVL_enum {
	NVM_EELVL_OFF_gc = (0x00<<0),	///< Interrupt disabled
	NVM_EELVL_LO_gc = (0x01<<0),	///< Low level
	NVM_EELVL_MED_gc = (0x02<<0),	///< Medium level
	NVM_EELVL_HI_gc = (0x03<<0),	///< High level
} NVM_EELVL_t;
	
/// Boot lock bits - boot setcion

typedef enum NVM_BLBB_enum {
	NVM_BLBB_NOLOCK_gc = (0x03<<6),	///< No locks
	NVM_BLBB_WLOCK_gc = (0x02<<6),	///< Write not allowed
	NVM_BLBB_RLOCK_gc = (0x01<<6),	///< Read not allowed
	NVM_BLBB_RWLOCK_gc = (0x00<<6),	///< Read and write not allowed
} NVM_BLBB_t;
	
/// Boot lock bits - application section

typedef enum NVM_BLBA_enum {
	NVM_BLBA_NOLOCK_gc = (0x03<<4),	///< No locks
	NVM_BLBA_WLOCK_gc = (0x02<<4),	///< Write not allowed
	NVM_BLBA_RLOCK_gc = (0x01<<4),	///< Read not allowed
	NVM_BLBA_RWLOCK_gc = (0x00<<4),	///< Read and write not allowed
} NVM_BLBA_t;
	
/// Boot lock bits - application table section

typedef enum NVM_BLBAT_enum {
	NVM_BLBAT_NOLOCK_gc = (0x03<<2),	///< No locks
	NVM_BLBAT_WLOCK_gc = (0x02<<2),	///< Write not allowed
	NVM_BLBAT_RLOCK_gc = (0x01<<2),	///< Read not allowed
	NVM_BLBAT_RWLOCK_gc = (0x00<<2),	///< Read and write not allowed
} NVM_BLBAT_t;
	
/// Lock bits

typedef enum NVM_LB_enum {
	NVM_LB_NOLOCK_gc = (0x03<<0),	///< No locks
	NVM_LB_WLOCK_gc = (0x02<<0),	///< Write not allowed
	NVM_LB_RWLOCK_gc = (0x00<<0),	///< Read and write not allowed
} NVM_LB_t;
	
/// Boot Loader Section Reset Vector

typedef enum BOOTRST_enum {
	BOOTRST_BOOTLDR_gc = (0x00<<6),	///< Boot Loader Reset
	BOOTRST_APPLICATION_gc = (0x01<<6),	///< Application Reset
} BOOTRST_t;
	
/// BOD operation

typedef enum BOD_enum {
	BOD_INSAMPLEDMODE_gc = (0x01<<0),	///< BOD enabled in sampled mode
	BOD_CONTINOUSLY_gc = (0x02<<0),	///< BOD enabled continuously
	BOD_DISABLED_gc = (0x03<<0),	///< BOD Disabled
} BOD_t;
	
/// Watchdog (Window) Timeout Period

typedef enum WD_enum {
	WD_8CLK_gc = (0x00<<4),	///< 8 cycles (8ms @ 3.3V)
	WD_16CLK_gc = (0x01<<4),	///< 16 cycles (16ms @ 3.3V)
	WD_32CLK_gc = (0x02<<4),	///< 32 cycles (32ms @ 3.3V)
	WD_64CLK_gc = (0x03<<4),	///< 64 cycles (64ms @ 3.3V)
	WD_128CLK_gc = (0x04<<4),	///< 128 cycles (0.125s @ 3.3V)
	WD_256CLK_gc = (0x05<<4),	///< 256 cycles (0.25s @ 3.3V)
	WD_512CLK_gc = (0x06<<4),	///< 512 cycles (0.5s @ 3.3V)
	WD_1KCLK_gc = (0x07<<4),	///< 1K cycles (1s @ 3.3V)
	WD_2KCLK_gc = (0x08<<4),	///< 2K cycles (2s @ 3.3V)
	WD_4KCLK_gc = (0x09<<4),	///< 4K cycles (4s @ 3.3V)
	WD_8KCLK_gc = (0x0A<<4),	///< 8K cycles (8s @ 3.3V)
} WD_t;
	
/// Start-up Time

typedef enum SUT_enum {
	SUT_0MS_gc = (0x03<<2),	///< 0 ms
	SUT_4MS_gc = (0x01<<2),	///< 4 ms
	SUT_64MS_gc = (0x00<<2),	///< 64 ms
} SUT_t;
	
/// Brown Out Detection Voltage Level

typedef enum BODLVL_enum {
	BODLVL_1V6_gc = (0x07<<0),	///< 1.6 V
	BODLVL_1V9_gc = (0x06<<0),	///< 1.9 V
	BODLVL_2V1_gc = (0x05<<0),	///< 2.1 V
	BODLVL_2V4_gc = (0x04<<0),	///< 2.4 V
	BODLVL_2V6_gc = (0x03<<0),	///< 2.6 V
	BODLVL_2V9_gc = (0x02<<0),	///< 2.9 V
	BODLVL_3V2_gc = (0x01<<0),	///< 3.2 V
} BODLVL_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// NVM Command
#define NVM_CMD_NO_OPERATION_gc (0x00<<0)	///< Noop/Ordinary LPM
#define NVM_CMD_READ_CALIB_ROW_gc (0x02<<0)	///< Read calibration row
#define NVM_CMD_READ_USER_SIG_ROW_gc (0x01<<0)	///< Read user signature row
#define NVM_CMD_READ_EEPROM_gc (0x06<<0)	///< Read EEPROM
#define NVM_CMD_READ_FUSES_gc (0x07<<0)	///< Read fuse byte
#define NVM_CMD_WRITE_LOCK_BITS_gc (0x08<<0)	///< Write lock bits
#define NVM_CMD_ERASE_USER_SIG_ROW_gc (0x18<<0)	///< Erase user signature row
#define NVM_CMD_WRITE_USER_SIG_ROW_gc (0x1A<<0)	///< Write user signature row
#define NVM_CMD_ERASE_APP_gc (0x20<<0)	///< Erase Application Section
#define NVM_CMD_ERASE_APP_PAGE_gc (0x22<<0)	///< Erase Application Section page
#define NVM_CMD_LOAD_FLASH_BUFFER_gc (0x23<<0)	///< Load Flash page buffer
#define NVM_CMD_WRITE_APP_PAGE_gc (0x24<<0)	///< Write Application Section page
#define NVM_CMD_ERASE_WRITE_APP_PAGE_gc (0x25<<0)	///< Erase-and-write Application Section page
#define NVM_CMD_ERASE_FLASH_BUFFER_gc (0x26<<0)	///< Erase/flush Flash page buffer
#define NVM_CMD_ERASE_BOOT_PAGE_gc (0x2A<<0)	///< Erase Boot Section page
#define NVM_CMD_WRITE_BOOT_PAGE_gc (0x2C<<0)	///< Write Boot Section page
#define NVM_CMD_ERASE_WRITE_BOOT_PAGE_gc (0x2D<<0)	///< Erase-and-write Boot Section page
#define NVM_CMD_ERASE_EEPROM_gc (0x30<<0)	///< Erase EEPROM
#define NVM_CMD_ERASE_EEPROM_PAGE_gc (0x32<<0)	///< Erase EEPROM page
#define NVM_CMD_LOAD_EEPROM_BUFFER_gc (0x33<<0)	///< Load EEPROM page buffer
#define NVM_CMD_WRITE_EEPROM_PAGE_gc (0x34<<0)	///< Write EEPROM page
#define NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc (0x35<<0)	///< Erase-and-write EEPROM page
#define NVM_CMD_ERASE_EEPROM_BUFFER_gc (0x36<<0)	///< Erase/flush EEPROM page buffer
#define NVM_CMD_APP_CRC_gc (0x38<<0)	///< Generate Application section CRC
#define NVM_CMD_BOOT_CRC_gc (0x39<<0)	///< Generate Boot Section CRC
#define NVM_CMD_FLASH_RANGE_CRC_gc (0x3A<<0)	///< Generate Flash Range CRC

/// SPM ready interrupt level
#define NVM_SPMLVL_OFF_gc (0x00<<2)	///< Interrupt disabled
#define NVM_SPMLVL_LO_gc (0x01<<2)	///< Low level
#define NVM_SPMLVL_MED_gc (0x02<<2)	///< Medium level
#define NVM_SPMLVL_HI_gc (0x03<<2)	///< High level

/// EEPROM ready interrupt level
#define NVM_EELVL_OFF_gc (0x00<<0)	///< Interrupt disabled
#define NVM_EELVL_LO_gc (0x01<<0)	///< Low level
#define NVM_EELVL_MED_gc (0x02<<0)	///< Medium level
#define NVM_EELVL_HI_gc (0x03<<0)	///< High level

/// Boot lock bits - boot setcion
#define NVM_BLBB_NOLOCK_gc (0x03<<6)	///< No locks
#define NVM_BLBB_WLOCK_gc (0x02<<6)	///< Write not allowed
#define NVM_BLBB_RLOCK_gc (0x01<<6)	///< Read not allowed
#define NVM_BLBB_RWLOCK_gc (0x00<<6)	///< Read and write not allowed

/// Boot lock bits - application section
#define NVM_BLBA_NOLOCK_gc (0x03<<4)	///< No locks
#define NVM_BLBA_WLOCK_gc (0x02<<4)	///< Write not allowed
#define NVM_BLBA_RLOCK_gc (0x01<<4)	///< Read not allowed
#define NVM_BLBA_RWLOCK_gc (0x00<<4)	///< Read and write not allowed

/// Boot lock bits - application table section
#define NVM_BLBAT_NOLOCK_gc (0x03<<2)	///< No locks
#define NVM_BLBAT_WLOCK_gc (0x02<<2)	///< Write not allowed
#define NVM_BLBAT_RLOCK_gc (0x01<<2)	///< Read not allowed
#define NVM_BLBAT_RWLOCK_gc (0x00<<2)	///< Read and write not allowed

/// Lock bits
#define NVM_LB_NOLOCK_gc (0x03<<0)	///< No locks
#define NVM_LB_WLOCK_gc (0x02<<0)	///< Write not allowed
#define NVM_LB_RWLOCK_gc (0x00<<0)	///< Read and write not allowed

/// Boot Loader Section Reset Vector
#define BOOTRST_BOOTLDR_gc (0x00<<6)	///< Boot Loader Reset
#define BOOTRST_APPLICATION_gc (0x01<<6)	///< Application Reset

/// BOD operation
#define BOD_INSAMPLEDMODE_gc (0x01<<0)	///< BOD enabled in sampled mode
#define BOD_CONTINOUSLY_gc (0x02<<0)	///< BOD enabled continuously
#define BOD_DISABLED_gc (0x03<<0)	///< BOD Disabled

/// Watchdog (Window) Timeout Period
#define WD_8CLK_gc (0x00<<4)	///< 8 cycles (8ms @ 3.3V)
#define WD_16CLK_gc (0x01<<4)	///< 16 cycles (16ms @ 3.3V)
#define WD_32CLK_gc (0x02<<4)	///< 32 cycles (32ms @ 3.3V)
#define WD_64CLK_gc (0x03<<4)	///< 64 cycles (64ms @ 3.3V)
#define WD_128CLK_gc (0x04<<4)	///< 128 cycles (0.125s @ 3.3V)
#define WD_256CLK_gc (0x05<<4)	///< 256 cycles (0.25s @ 3.3V)
#define WD_512CLK_gc (0x06<<4)	///< 512 cycles (0.5s @ 3.3V)
#define WD_1KCLK_gc (0x07<<4)	///< 1K cycles (1s @ 3.3V)
#define WD_2KCLK_gc (0x08<<4)	///< 2K cycles (2s @ 3.3V)
#define WD_4KCLK_gc (0x09<<4)	///< 4K cycles (4s @ 3.3V)
#define WD_8KCLK_gc (0x0A<<4)	///< 8K cycles (8s @ 3.3V)

/// Start-up Time
#define SUT_0MS_gc (0x03<<2)	///< 0 ms
#define SUT_4MS_gc (0x01<<2)	///< 4 ms
#define SUT_64MS_gc (0x00<<2)	///< 64 ms

/// Brown Out Detection Voltage Level
#define BODLVL_1V6_gc (0x07<<0)	///< 1.6 V
#define BODLVL_1V9_gc (0x06<<0)	///< 1.9 V
#define BODLVL_2V1_gc (0x05<<0)	///< 2.1 V
#define BODLVL_2V4_gc (0x04<<0)	///< 2.4 V
#define BODLVL_2V6_gc (0x03<<0)	///< 2.6 V
#define BODLVL_2V9_gc (0x02<<0)	///< 2.9 V
#define BODLVL_3V2_gc (0x01<<0)	///< 3.2 V

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup ac Analog Comparator
 *  @{
 */
	
/** @name AC.AC0CTRL
  * @see AC_INTMODE_enum
  * @see AC_INTLVL_enum
  * @see AC_HYSMODE_enum
  * @{
  */
#define AC_INTMODE_gm 0xC0 ///< Interrupt Mode group mask
#define AC_INTMODE_gp 6 ///< Interrupt Mode group position
#define AC_INTMODE0_bm (1<<6) ///< Interrupt Mode bit 0 mask
#define AC_INTMODE0_bp 6 ///< Interrupt Mode bit 0 position
#define AC_INTMODE1_bm (1<<7) ///< Interrupt Mode bit 1 mask
#define AC_INTMODE1_bp 7 ///< Interrupt Mode bit 1 position
#define AC_INTLVL_gm 0x30 ///< Interrupt Level group mask
#define AC_INTLVL_gp 4 ///< Interrupt Level group position
#define AC_INTLVL0_bm (1<<4) ///< Interrupt Level bit 0 mask
#define AC_INTLVL0_bp 4 ///< Interrupt Level bit 0 position
#define AC_INTLVL1_bm (1<<5) ///< Interrupt Level bit 1 mask
#define AC_INTLVL1_bp 5 ///< Interrupt Level bit 1 position
#define AC_HSMODE_bm 0x08 ///< High-speed Mode bit mask
#define AC_HSMODE_bp 3 ///< High-speed Mode bit position
#define AC_HYSMODE_gm 0x06 ///< Hysteresis Mode group mask
#define AC_HYSMODE_gp 1 ///< Hysteresis Mode group position
#define AC_HYSMODE0_bm (1<<1) ///< Hysteresis Mode bit 0 mask
#define AC_HYSMODE0_bp 1 ///< Hysteresis Mode bit 0 position
#define AC_HYSMODE1_bm (1<<2) ///< Hysteresis Mode bit 1 mask
#define AC_HYSMODE1_bp 2 ///< Hysteresis Mode bit 1 position
#define AC_ENABLE_bm 0x01 ///< Enable bit mask
#define AC_ENABLE_bp 0 ///< Enable bit position
/** @} */
	
/** @name AC.AC1CTRL
  * @see AC_INTMODE_enum
  * @see AC_INTLVL_enum
  * @see AC_HYSMODE_enum
  * @{
  */
// Masks for INTMODE aready defined
// Masks for INTLVL aready defined
// Masks for HSMODE aready defined
// Masks for HYSMODE aready defined
// Masks for ENABLE aready defined
/** @} */
	
/** @name AC.AC0MUXCTRL
  * @see AC_MUXPOS_enum
  * @see AC_MUXNEG_enum
  * @{
  */
#define AC_MUXPOS_gm 0x38 ///< MUX Positive Input group mask
#define AC_MUXPOS_gp 3 ///< MUX Positive Input group position
#define AC_MUXPOS0_bm (1<<3) ///< MUX Positive Input bit 0 mask
#define AC_MUXPOS0_bp 3 ///< MUX Positive Input bit 0 position
#define AC_MUXPOS1_bm (1<<4) ///< MUX Positive Input bit 1 mask
#define AC_MUXPOS1_bp 4 ///< MUX Positive Input bit 1 position
#define AC_MUXPOS2_bm (1<<5) ///< MUX Positive Input bit 2 mask
#define AC_MUXPOS2_bp 5 ///< MUX Positive Input bit 2 position
#define AC_MUXNEG_gm 0x07 ///< MUX Negative Input group mask
#define AC_MUXNEG_gp 0 ///< MUX Negative Input group position
#define AC_MUXNEG0_bm (1<<0) ///< MUX Negative Input bit 0 mask
#define AC_MUXNEG0_bp 0 ///< MUX Negative Input bit 0 position
#define AC_MUXNEG1_bm (1<<1) ///< MUX Negative Input bit 1 mask
#define AC_MUXNEG1_bp 1 ///< MUX Negative Input bit 1 position
#define AC_MUXNEG2_bm (1<<2) ///< MUX Negative Input bit 2 mask
#define AC_MUXNEG2_bp 2 ///< MUX Negative Input bit 2 position
/** @} */
	
/** @name AC.AC1MUXCTRL
  * @see AC_MUXPOS_enum
  * @see AC_MUXNEG_enum
  * @{
  */
// Masks for MUXPOS aready defined
// Masks for MUXNEG aready defined
/** @} */
	
/** @name AC.CTRLA
  * @{
  */
#define AC_AC0OUT_bm 0x01 ///< Comparator 0 Output Enable bit mask
#define AC_AC0OUT_bp 0 ///< Comparator 0 Output Enable bit position
/** @} */
	
/** @name AC.CTRLB
  * @{
  */
#define AC_SCALEFAC_gm 0x3F ///< VCC Voltage Scaler Factor group mask
#define AC_SCALEFAC_gp 0 ///< VCC Voltage Scaler Factor group position
#define AC_SCALEFAC0_bm (1<<0) ///< VCC Voltage Scaler Factor bit 0 mask
#define AC_SCALEFAC0_bp 0 ///< VCC Voltage Scaler Factor bit 0 position
#define AC_SCALEFAC1_bm (1<<1) ///< VCC Voltage Scaler Factor bit 1 mask
#define AC_SCALEFAC1_bp 1 ///< VCC Voltage Scaler Factor bit 1 position
#define AC_SCALEFAC2_bm (1<<2) ///< VCC Voltage Scaler Factor bit 2 mask
#define AC_SCALEFAC2_bp 2 ///< VCC Voltage Scaler Factor bit 2 position
#define AC_SCALEFAC3_bm (1<<3) ///< VCC Voltage Scaler Factor bit 3 mask
#define AC_SCALEFAC3_bp 3 ///< VCC Voltage Scaler Factor bit 3 position
#define AC_SCALEFAC4_bm (1<<4) ///< VCC Voltage Scaler Factor bit 4 mask
#define AC_SCALEFAC4_bp 4 ///< VCC Voltage Scaler Factor bit 4 position
#define AC_SCALEFAC5_bm (1<<5) ///< VCC Voltage Scaler Factor bit 5 mask
#define AC_SCALEFAC5_bp 5 ///< VCC Voltage Scaler Factor bit 5 position
/** @} */
	
/** @name AC.WINCTRL
  * @see AC_WINTMODE_enum
  * @see AC_WINTLVL_enum
  * @{
  */
#define AC_WEN_bm 0x10 ///< Window Mode Enable bit mask
#define AC_WEN_bp 4 ///< Window Mode Enable bit position
#define AC_WINTMODE_gm 0x0C ///< Window Interrupt Mode group mask
#define AC_WINTMODE_gp 2 ///< Window Interrupt Mode group position
#define AC_WINTMODE0_bm (1<<2) ///< Window Interrupt Mode bit 0 mask
#define AC_WINTMODE0_bp 2 ///< Window Interrupt Mode bit 0 position
#define AC_WINTMODE1_bm (1<<3) ///< Window Interrupt Mode bit 1 mask
#define AC_WINTMODE1_bp 3 ///< Window Interrupt Mode bit 1 position
#define AC_WINTLVL_gm 0x03 ///< Window Interrupt Level group mask
#define AC_WINTLVL_gp 0 ///< Window Interrupt Level group position
#define AC_WINTLVL0_bm (1<<0) ///< Window Interrupt Level bit 0 mask
#define AC_WINTLVL0_bp 0 ///< Window Interrupt Level bit 0 position
#define AC_WINTLVL1_bm (1<<1) ///< Window Interrupt Level bit 1 mask
#define AC_WINTLVL1_bp 1 ///< Window Interrupt Level bit 1 position
/** @} */
	
/** @name AC.STATUS
  * @see AC_WSTATE_enum
  * @{
  */
#define AC_WSTATE_gm 0xC0 ///< Window Mode State group mask
#define AC_WSTATE_gp 6 ///< Window Mode State group position
#define AC_WSTATE0_bm (1<<6) ///< Window Mode State bit 0 mask
#define AC_WSTATE0_bp 6 ///< Window Mode State bit 0 position
#define AC_WSTATE1_bm (1<<7) ///< Window Mode State bit 1 mask
#define AC_WSTATE1_bp 7 ///< Window Mode State bit 1 position
#define AC_AC1STATE_bm 0x20 ///< Comparator 1 State bit mask
#define AC_AC1STATE_bp 5 ///< Comparator 1 State bit position
#define AC_AC0STATE_bm 0x10 ///< Comparator 0 State bit mask
#define AC_AC0STATE_bp 4 ///< Comparator 0 State bit position
#define AC_WIF_bm 0x04 ///< Window Mode Interrupt Flag bit mask
#define AC_WIF_bp 2 ///< Window Mode Interrupt Flag bit position
#define AC_AC1IF_bm 0x02 ///< Comparator 1 Interrupt Flag bit mask
#define AC_AC1IF_bp 1 ///< Comparator 1 Interrupt Flag bit position
#define AC_AC0IF_bm 0x01 ///< Comparator 0 Interrupt Flag bit mask
#define AC_AC0IF_bp 0 ///< Comparator 0 Interrupt Flag bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Interrupt mode

typedef enum AC_INTMODE_enum {
	AC_INTMODE_BOTHEDGES_gc = (0x00<<6),	///< Interrupt on both edges
	AC_INTMODE_FALLING_gc = (0x02<<6),	///< Interrupt on falling edge
	AC_INTMODE_RISING_gc = (0x03<<6),	///< Interrupt on rising edge
} AC_INTMODE_t;
	
/// Interrupt level

typedef enum AC_INTLVL_enum {
	AC_INTLVL_OFF_gc = (0x00<<4),	///< Interrupt disabled
	AC_INTLVL_LO_gc = (0x01<<4),	///< Low level
	AC_INTLVL_MED_gc = (0x02<<4),	///< Medium level
	AC_INTLVL_HI_gc = (0x03<<4),	///< High level
} AC_INTLVL_t;
	
/// Hysteresis mode selection

typedef enum AC_HYSMODE_enum {
	AC_HYSMODE_NO_gc = (0x00<<1),	///< No hysteresis
	AC_HYSMODE_SMALL_gc = (0x01<<1),	///< Small hysteresis
	AC_HYSMODE_LARGE_gc = (0x02<<1),	///< Large hysteresis
} AC_HYSMODE_t;
	
/// Positive input multiplexer selection

typedef enum AC_MUXPOS_enum {
	AC_MUXPOS_PIN0_gc = (0x00<<3),	///< Pin 0
	AC_MUXPOS_PIN1_gc = (0x01<<3),	///< Pin 1
	AC_MUXPOS_PIN2_gc = (0x02<<3),	///< Pin 2
	AC_MUXPOS_PIN3_gc = (0x03<<3),	///< Pin 3
	AC_MUXPOS_PIN4_gc = (0x04<<3),	///< Pin 4
	AC_MUXPOS_PIN5_gc = (0x05<<3),	///< Pin 5
	AC_MUXPOS_PIN6_gc = (0x06<<3),	///< Pin 6
	AC_MUXPOS_DAC_gc = (0x07<<3),	///< DAC output
} AC_MUXPOS_t;
	
/// Negative input multiplexer selection

typedef enum AC_MUXNEG_enum {
	AC_MUXNEG_PIN0_gc = (0x00<<0),	///< Pin 0
	AC_MUXNEG_PIN1_gc = (0x01<<0),	///< Pin 1
	AC_MUXNEG_PIN3_gc = (0x02<<0),	///< Pin 3
	AC_MUXNEG_PIN5_gc = (0x03<<0),	///< Pin 5
	AC_MUXNEG_PIN7_gc = (0x04<<0),	///< Pin 7
	AC_MUXNEG_DAC_gc = (0x05<<0),	///< DAC output
	AC_MUXNEG_BANDGAP_gc = (0x06<<0),	///< Bandgap Reference
	AC_MUXNEG_SCALER_gc = (0x07<<0),	///< Internal voltage scaler
} AC_MUXNEG_t;
	
/// Windows interrupt mode

typedef enum AC_WINTMODE_enum {
	AC_WINTMODE_ABOVE_gc = (0x00<<2),	///< Interrupt on above window
	AC_WINTMODE_INSIDE_gc = (0x01<<2),	///< Interrupt on inside window
	AC_WINTMODE_BELOW_gc = (0x02<<2),	///< Interrupt on below window
	AC_WINTMODE_OUTSIDE_gc = (0x03<<2),	///< Interrupt on outside window
} AC_WINTMODE_t;
	
/// Window interrupt level

typedef enum AC_WINTLVL_enum {
	AC_WINTLVL_OFF_gc = (0x00<<0),	///< Interrupt disabled
	AC_WINTLVL_LO_gc = (0x01<<0),	///< Low priority
	AC_WINTLVL_MED_gc = (0x02<<0),	///< Medium priority
	AC_WINTLVL_HI_gc = (0x03<<0),	///< High priority
} AC_WINTLVL_t;
	
/// Window mode state

typedef enum AC_WSTATE_enum {
	AC_WSTATE_ABOVE_gc = (0x00<<6),	///< Signal above window
	AC_WSTATE_INSIDE_gc = (0x01<<6),	///< Signal inside window
	AC_WSTATE_BELOW_gc = (0x02<<6),	///< Signal below window
} AC_WSTATE_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Interrupt mode
#define AC_INTMODE_BOTHEDGES_gc (0x00<<6)	///< Interrupt on both edges
#define AC_INTMODE_FALLING_gc (0x02<<6)	///< Interrupt on falling edge
#define AC_INTMODE_RISING_gc (0x03<<6)	///< Interrupt on rising edge

/// Interrupt level
#define AC_INTLVL_OFF_gc (0x00<<4)	///< Interrupt disabled
#define AC_INTLVL_LO_gc (0x01<<4)	///< Low level
#define AC_INTLVL_MED_gc (0x02<<4)	///< Medium level
#define AC_INTLVL_HI_gc (0x03<<4)	///< High level

/// Hysteresis mode selection
#define AC_HYSMODE_NO_gc (0x00<<1)	///< No hysteresis
#define AC_HYSMODE_SMALL_gc (0x01<<1)	///< Small hysteresis
#define AC_HYSMODE_LARGE_gc (0x02<<1)	///< Large hysteresis

/// Positive input multiplexer selection
#define AC_MUXPOS_PIN0_gc (0x00<<3)	///< Pin 0
#define AC_MUXPOS_PIN1_gc (0x01<<3)	///< Pin 1
#define AC_MUXPOS_PIN2_gc (0x02<<3)	///< Pin 2
#define AC_MUXPOS_PIN3_gc (0x03<<3)	///< Pin 3
#define AC_MUXPOS_PIN4_gc (0x04<<3)	///< Pin 4
#define AC_MUXPOS_PIN5_gc (0x05<<3)	///< Pin 5
#define AC_MUXPOS_PIN6_gc (0x06<<3)	///< Pin 6
#define AC_MUXPOS_DAC_gc (0x07<<3)	///< DAC output

/// Negative input multiplexer selection
#define AC_MUXNEG_PIN0_gc (0x00<<0)	///< Pin 0
#define AC_MUXNEG_PIN1_gc (0x01<<0)	///< Pin 1
#define AC_MUXNEG_PIN3_gc (0x02<<0)	///< Pin 3
#define AC_MUXNEG_PIN5_gc (0x03<<0)	///< Pin 5
#define AC_MUXNEG_PIN7_gc (0x04<<0)	///< Pin 7
#define AC_MUXNEG_DAC_gc (0x05<<0)	///< DAC output
#define AC_MUXNEG_BANDGAP_gc (0x06<<0)	///< Bandgap Reference
#define AC_MUXNEG_SCALER_gc (0x07<<0)	///< Internal voltage scaler

/// Windows interrupt mode
#define AC_WINTMODE_ABOVE_gc (0x00<<2)	///< Interrupt on above window
#define AC_WINTMODE_INSIDE_gc (0x01<<2)	///< Interrupt on inside window
#define AC_WINTMODE_BELOW_gc (0x02<<2)	///< Interrupt on below window
#define AC_WINTMODE_OUTSIDE_gc (0x03<<2)	///< Interrupt on outside window

/// Window interrupt level
#define AC_WINTLVL_OFF_gc (0x00<<0)	///< Interrupt disabled
#define AC_WINTLVL_LO_gc (0x01<<0)	///< Low priority
#define AC_WINTLVL_MED_gc (0x02<<0)	///< Medium priority
#define AC_WINTLVL_HI_gc (0x03<<0)	///< High priority

/// Window mode state
#define AC_WSTATE_ABOVE_gc (0x00<<6)	///< Signal above window
#define AC_WSTATE_INSIDE_gc (0x01<<6)	///< Signal inside window
#define AC_WSTATE_BELOW_gc (0x02<<6)	///< Signal below window

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup adc Analog/Digital Converter
 *  @{
 */
	
/** @name ADC_CH.CTRL
  * @see ADC_CH_GAIN_enum
  * @see ADC_CH_INPUTMODE_enum
  * @{
  */
#define ADC_CH_START_bm 0x80 ///< Channel Start Conversion bit mask
#define ADC_CH_START_bp 7 ///< Channel Start Conversion bit position
#define ADC_CH_GAINFAC_gm 0x1C ///< Gain Factor group mask
#define ADC_CH_GAINFAC_gp 2 ///< Gain Factor group position
#define ADC_CH_GAINFAC0_bm (1<<2) ///< Gain Factor bit 0 mask
#define ADC_CH_GAINFAC0_bp 2 ///< Gain Factor bit 0 position
#define ADC_CH_GAINFAC1_bm (1<<3) ///< Gain Factor bit 1 mask
#define ADC_CH_GAINFAC1_bp 3 ///< Gain Factor bit 1 position
#define ADC_CH_GAINFAC2_bm (1<<4) ///< Gain Factor bit 2 mask
#define ADC_CH_GAINFAC2_bp 4 ///< Gain Factor bit 2 position
#define ADC_CH_INPUTMODE_gm 0x03 ///< Input Mode Select group mask
#define ADC_CH_INPUTMODE_gp 0 ///< Input Mode Select group position
#define ADC_CH_INPUTMODE0_bm (1<<0) ///< Input Mode Select bit 0 mask
#define ADC_CH_INPUTMODE0_bp 0 ///< Input Mode Select bit 0 position
#define ADC_CH_INPUTMODE1_bm (1<<1) ///< Input Mode Select bit 1 mask
#define ADC_CH_INPUTMODE1_bp 1 ///< Input Mode Select bit 1 position
/** @} */
	
/** @name ADC_CH.MUXCTRL
  * @see ADC_CH_MUXPOS_enum
  * @see ADC_CH_MUXINT_enum
  * @see ADC_CH_MUXNEG_enum
  * @{
  */
#define ADC_CH_MUXPOS_gm 0x78 ///< Positive Input Select group mask
#define ADC_CH_MUXPOS_gp 3 ///< Positive Input Select group position
#define ADC_CH_MUXPOS0_bm (1<<3) ///< Positive Input Select bit 0 mask
#define ADC_CH_MUXPOS0_bp 3 ///< Positive Input Select bit 0 position
#define ADC_CH_MUXPOS1_bm (1<<4) ///< Positive Input Select bit 1 mask
#define ADC_CH_MUXPOS1_bp 4 ///< Positive Input Select bit 1 position
#define ADC_CH_MUXPOS2_bm (1<<5) ///< Positive Input Select bit 2 mask
#define ADC_CH_MUXPOS2_bp 5 ///< Positive Input Select bit 2 position
#define ADC_CH_MUXPOS3_bm (1<<6) ///< Positive Input Select bit 3 mask
#define ADC_CH_MUXPOS3_bp 6 ///< Positive Input Select bit 3 position
#define ADC_CH_MUXINT_gm 0x78 ///< Internal Input Select group mask
#define ADC_CH_MUXINT_gp 3 ///< Internal Input Select group position
#define ADC_CH_MUXINT0_bm (1<<3) ///< Internal Input Select bit 0 mask
#define ADC_CH_MUXINT0_bp 3 ///< Internal Input Select bit 0 position
#define ADC_CH_MUXINT1_bm (1<<4) ///< Internal Input Select bit 1 mask
#define ADC_CH_MUXINT1_bp 4 ///< Internal Input Select bit 1 position
#define ADC_CH_MUXINT2_bm (1<<5) ///< Internal Input Select bit 2 mask
#define ADC_CH_MUXINT2_bp 5 ///< Internal Input Select bit 2 position
#define ADC_CH_MUXINT3_bm (1<<6) ///< Internal Input Select bit 3 mask
#define ADC_CH_MUXINT3_bp 6 ///< Internal Input Select bit 3 position
#define ADC_CH_MUXNEG_gm 0x03 ///< Negative Input Select group mask
#define ADC_CH_MUXNEG_gp 0 ///< Negative Input Select group position
#define ADC_CH_MUXNEG0_bm (1<<0) ///< Negative Input Select bit 0 mask
#define ADC_CH_MUXNEG0_bp 0 ///< Negative Input Select bit 0 position
#define ADC_CH_MUXNEG1_bm (1<<1) ///< Negative Input Select bit 1 mask
#define ADC_CH_MUXNEG1_bp 1 ///< Negative Input Select bit 1 position
/** @} */
	
/** @name ADC_CH.INTCTRL
  * @see ADC_CH_INTMODE_enum
  * @see ADC_CH_INTLVL_enum
  * @{
  */
#define ADC_CH_INTMODE_gm 0x0C ///< Interrupt Mode group mask
#define ADC_CH_INTMODE_gp 2 ///< Interrupt Mode group position
#define ADC_CH_INTMODE0_bm (1<<2) ///< Interrupt Mode bit 0 mask
#define ADC_CH_INTMODE0_bp 2 ///< Interrupt Mode bit 0 position
#define ADC_CH_INTMODE1_bm (1<<3) ///< Interrupt Mode bit 1 mask
#define ADC_CH_INTMODE1_bp 3 ///< Interrupt Mode bit 1 position
#define ADC_CH_INTLVL_gm 0x03 ///< Interrupt Level group mask
#define ADC_CH_INTLVL_gp 0 ///< Interrupt Level group position
#define ADC_CH_INTLVL0_bm (1<<0) ///< Interrupt Level bit 0 mask
#define ADC_CH_INTLVL0_bp 0 ///< Interrupt Level bit 0 position
#define ADC_CH_INTLVL1_bm (1<<1) ///< Interrupt Level bit 1 mask
#define ADC_CH_INTLVL1_bp 1 ///< Interrupt Level bit 1 position
/** @} */
	
/** @name ADC_CH.INTFLAGS
  * @{
  */
#define ADC_CH_CHIF_bm 0x01 ///< Channel Interrupt Flag bit mask
#define ADC_CH_CHIF_bp 0 ///< Channel Interrupt Flag bit position
/** @} */
	
/** @name ADC.CTRLA
  * @see ADC_DMASEL_enum
  * @{
  */
#define ADC_DMASEL_gm 0xC0 ///< DMA Selection group mask
#define ADC_DMASEL_gp 6 ///< DMA Selection group position
#define ADC_DMASEL0_bm (1<<6) ///< DMA Selection bit 0 mask
#define ADC_DMASEL0_bp 6 ///< DMA Selection bit 0 position
#define ADC_DMASEL1_bm (1<<7) ///< DMA Selection bit 1 mask
#define ADC_DMASEL1_bp 7 ///< DMA Selection bit 1 position
#define ADC_CH3START_bm 0x20 ///< Channel 3 Start Conversion bit mask
#define ADC_CH3START_bp 5 ///< Channel 3 Start Conversion bit position
#define ADC_CH2START_bm 0x10 ///< Channel 2 Start Conversion bit mask
#define ADC_CH2START_bp 4 ///< Channel 2 Start Conversion bit position
#define ADC_CH1START_bm 0x08 ///< Channel 1 Start Conversion bit mask
#define ADC_CH1START_bp 3 ///< Channel 1 Start Conversion bit position
#define ADC_CH0START_bm 0x04 ///< Channel 0 Start Conversion bit mask
#define ADC_CH0START_bp 2 ///< Channel 0 Start Conversion bit position
#define ADC_FLUSH_bm 0x02 ///< Flush Pipeline bit mask
#define ADC_FLUSH_bp 1 ///< Flush Pipeline bit position
#define ADC_ENABLE_bm 0x01 ///< Enable ADC bit mask
#define ADC_ENABLE_bp 0 ///< Enable ADC bit position
/** @} */
	
/** @name ADC.CTRLB
  * @see ADC_RESOLUTION_enum
  * @{
  */
#define ADC_CONMODE_bm 0x10 ///< Conversion Mode bit mask
#define ADC_CONMODE_bp 4 ///< Conversion Mode bit position
#define ADC_FREERUN_bm 0x08 ///< Free Running Mode Enable bit mask
#define ADC_FREERUN_bp 3 ///< Free Running Mode Enable bit position
#define ADC_RESOLUTION_gm 0x06 ///< Result Resolution group mask
#define ADC_RESOLUTION_gp 1 ///< Result Resolution group position
#define ADC_RESOLUTION0_bm (1<<1) ///< Result Resolution bit 0 mask
#define ADC_RESOLUTION0_bp 1 ///< Result Resolution bit 0 position
#define ADC_RESOLUTION1_bm (1<<2) ///< Result Resolution bit 1 mask
#define ADC_RESOLUTION1_bp 2 ///< Result Resolution bit 1 position
/** @} */
	
/** @name ADC.REFCTRL
  * @see ADC_REFSEL_enum
  * @{
  */
#define ADC_REFSEL_gm 0x30 ///< Reference Selection group mask
#define ADC_REFSEL_gp 4 ///< Reference Selection group position
#define ADC_REFSEL0_bm (1<<4) ///< Reference Selection bit 0 mask
#define ADC_REFSEL0_bp 4 ///< Reference Selection bit 0 position
#define ADC_REFSEL1_bm (1<<5) ///< Reference Selection bit 1 mask
#define ADC_REFSEL1_bp 5 ///< Reference Selection bit 1 position
#define ADC_BANDGAP_bm 0x02 ///< Bandgap enable bit mask
#define ADC_BANDGAP_bp 1 ///< Bandgap enable bit position
#define ADC_TEMPREF_bm 0x01 ///< Temperature Reference Enable bit mask
#define ADC_TEMPREF_bp 0 ///< Temperature Reference Enable bit position
/** @} */
	
/** @name ADC.EVCTRL
  * @see ADC_SWEEP_enum
  * @see ADC_EVSEL_enum
  * @see ADC_EVACT_enum
  * @{
  */
#define ADC_SWEEP_gm 0xC0 ///< Channel Sweep Selection group mask
#define ADC_SWEEP_gp 6 ///< Channel Sweep Selection group position
#define ADC_SWEEP0_bm (1<<6) ///< Channel Sweep Selection bit 0 mask
#define ADC_SWEEP0_bp 6 ///< Channel Sweep Selection bit 0 position
#define ADC_SWEEP1_bm (1<<7) ///< Channel Sweep Selection bit 1 mask
#define ADC_SWEEP1_bp 7 ///< Channel Sweep Selection bit 1 position
#define ADC_EVSEL_gm 0x38 ///< Event Input Select group mask
#define ADC_EVSEL_gp 3 ///< Event Input Select group position
#define ADC_EVSEL0_bm (1<<3) ///< Event Input Select bit 0 mask
#define ADC_EVSEL0_bp 3 ///< Event Input Select bit 0 position
#define ADC_EVSEL1_bm (1<<4) ///< Event Input Select bit 1 mask
#define ADC_EVSEL1_bp 4 ///< Event Input Select bit 1 position
#define ADC_EVSEL2_bm (1<<5) ///< Event Input Select bit 2 mask
#define ADC_EVSEL2_bp 5 ///< Event Input Select bit 2 position
#define ADC_EVACT_gm 0x07 ///< Event Action Select group mask
#define ADC_EVACT_gp 0 ///< Event Action Select group position
#define ADC_EVACT0_bm (1<<0) ///< Event Action Select bit 0 mask
#define ADC_EVACT0_bp 0 ///< Event Action Select bit 0 position
#define ADC_EVACT1_bm (1<<1) ///< Event Action Select bit 1 mask
#define ADC_EVACT1_bp 1 ///< Event Action Select bit 1 position
#define ADC_EVACT2_bm (1<<2) ///< Event Action Select bit 2 mask
#define ADC_EVACT2_bp 2 ///< Event Action Select bit 2 position
/** @} */
	
/** @name ADC.PRESCALER
  * @see ADC_PRESCALER_enum
  * @{
  */
#define ADC_PRESCALER_gm 0x07 ///< Clock Prescaler Selection group mask
#define ADC_PRESCALER_gp 0 ///< Clock Prescaler Selection group position
#define ADC_PRESCALER0_bm (1<<0) ///< Clock Prescaler Selection bit 0 mask
#define ADC_PRESCALER0_bp 0 ///< Clock Prescaler Selection bit 0 position
#define ADC_PRESCALER1_bm (1<<1) ///< Clock Prescaler Selection bit 1 mask
#define ADC_PRESCALER1_bp 1 ///< Clock Prescaler Selection bit 1 position
#define ADC_PRESCALER2_bm (1<<2) ///< Clock Prescaler Selection bit 2 mask
#define ADC_PRESCALER2_bp 2 ///< Clock Prescaler Selection bit 2 position
/** @} */
	
/** @name ADC.INTFLAGS
  * @{
  */
#define ADC_CH3IF_bm 0x08 ///< Channel 3 Interrupt Flag bit mask
#define ADC_CH3IF_bp 3 ///< Channel 3 Interrupt Flag bit position
#define ADC_CH2IF_bm 0x04 ///< Channel 2 Interrupt Flag bit mask
#define ADC_CH2IF_bp 2 ///< Channel 2 Interrupt Flag bit position
#define ADC_CH1IF_bm 0x02 ///< Channel 1 Interrupt Flag bit mask
#define ADC_CH1IF_bp 1 ///< Channel 1 Interrupt Flag bit position
#define ADC_CH0IF_bm 0x01 ///< Channel 0 Interrupt Flag bit mask
#define ADC_CH0IF_bp 0 ///< Channel 0 Interrupt Flag bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Positive input multiplexer selection

typedef enum ADC_CH_MUXPOS_enum {
	ADC_CH_MUXPOS_PIN0_gc = (0x00<<3),	///< Input pin 0
	ADC_CH_MUXPOS_PIN1_gc = (0x01<<3),	///< Input pin 1
	ADC_CH_MUXPOS_PIN2_gc = (0x02<<3),	///< Input pin 2
	ADC_CH_MUXPOS_PIN3_gc = (0x03<<3),	///< Input pin 3
	ADC_CH_MUXPOS_PIN4_gc = (0x04<<3),	///< Input pin 4
	ADC_CH_MUXPOS_PIN5_gc = (0x05<<3),	///< Input pin 5
	ADC_CH_MUXPOS_PIN6_gc = (0x06<<3),	///< Input pin 6
	ADC_CH_MUXPOS_PIN7_gc = (0x07<<3),	///< Input pin 7
} ADC_CH_MUXPOS_t;
	
/// Internal input multiplexer selections

typedef enum ADC_CH_MUXINT_enum {
	ADC_CH_MUXINT_TEMP_gc = (0x00<<3),	///< Temperature Reference
	ADC_CH_MUXINT_BANDGAP_gc = (0x01<<3),	///< Bandgap Reference
	ADC_CH_MUXINT_SCALEDVCC_gc = (0x02<<3),	///< 1/10 scaled VCC
	ADC_CH_MUXINT_DAC_gc = (0x03<<3),	///< DAC output
} ADC_CH_MUXINT_t;
	
/// Negative input multiplexer selection

typedef enum ADC_CH_MUXNEG_enum {
	ADC_CH_MUXNEG_PIN0_gc = (0x00<<0),	///< Input pin 0
	ADC_CH_MUXNEG_PIN1_gc = (0x01<<0),	///< Input pin 1
	ADC_CH_MUXNEG_PIN2_gc = (0x02<<0),	///< Input pin 2
	ADC_CH_MUXNEG_PIN3_gc = (0x03<<0),	///< Input pin 3
	ADC_CH_MUXNEG_PIN4_gc = (0x04<<0),	///< Input pin 4
	ADC_CH_MUXNEG_PIN5_gc = (0x05<<0),	///< Input pin 5
	ADC_CH_MUXNEG_PIN6_gc = (0x06<<0),	///< Input pin 6
	ADC_CH_MUXNEG_PIN7_gc = (0x07<<0),	///< Input pin 7
} ADC_CH_MUXNEG_t;
	
/// Input mode

typedef enum ADC_CH_INPUTMODE_enum {
	ADC_CH_INPUTMODE_INTERNAL_gc = (0x00<<0),	///< Internal inputs, no gain
	ADC_CH_INPUTMODE_SINGLEENDED_gc = (0x01<<0),	///< Single-ended input, no gain
	ADC_CH_INPUTMODE_DIFF_gc = (0x02<<0),	///< Differential input, no gain
	ADC_CH_INPUTMODE_DIFFWGAIN_gc = (0x03<<0),	///< Differential input, with gain
} ADC_CH_INPUTMODE_t;
	
/// Gain factor

typedef enum ADC_CH_GAIN_enum {
	ADC_CH_GAIN_1X_gc = (0x00<<2),	///< 1x gain
	ADC_CH_GAIN_2X_gc = (0x01<<2),	///< 2x gain
	ADC_CH_GAIN_4X_gc = (0x02<<2),	///< 4x gain
	ADC_CH_GAIN_8X_gc = (0x03<<2),	///< 8x gain
	ADC_CH_GAIN_16X_gc = (0x04<<2),	///< 16x gain
	ADC_CH_GAIN_32X_gc = (0x05<<2),	///< 32x gain
	ADC_CH_GAIN_64X_gc = (0x06<<2),	///< 64x gain
} ADC_CH_GAIN_t;
	
/// Conversion result resolution

typedef enum ADC_RESOLUTION_enum {
	ADC_RESOLUTION_12BIT_gc = (0x00<<1),	///< 12-bit right-adjusted result
	ADC_RESOLUTION_8BIT_gc = (0x02<<1),	///< 8-bit right-adjusted result
	ADC_RESOLUTION_LEFT12BIT_gc = (0x03<<1),	///< 12-bit left-adjusted result
} ADC_RESOLUTION_t;
	
/// Voltage reference selection

typedef enum ADC_REFSEL_enum {
	ADC_REFSEL_INT1V_gc = (0x00<<4),	///< Internal 1V
	ADC_REFSEL_VCC_gc = (0x01<<4),	///< Internal VCC / 1.6V
	ADC_REFSEL_AREFA_gc = (0x02<<4),	///< External reference on PORT A
	ADC_REFSEL_AREFB_gc = (0x03<<4),	///< External reference on PORT B
} ADC_REFSEL_t;
	
/// Channel sweep selection

typedef enum ADC_SWEEP_enum {
	ADC_SWEEP_0_gc = (0x00<<6),	///< ADC Channel 0
	ADC_SWEEP_01_gc = (0x01<<6),	///< ADC Channel 0,1
	ADC_SWEEP_012_gc = (0x02<<6),	///< ADC Channel 0,1,2
	ADC_SWEEP_0123_gc = (0x03<<6),	///< ADC Channel 0,1,2,3
} ADC_SWEEP_t;
	
/// Event channel input selection

typedef enum ADC_EVSEL_enum {
	ADC_EVSEL_0123_gc = (0x00<<3),	///< Event Channel 0,1,2,3
	ADC_EVSEL_1234_gc = (0x01<<3),	///< Event Channel 1,2,3,4
	ADC_EVSEL_2345_gc = (0x02<<3),	///< Event Channel 2,3,4,5
	ADC_EVSEL_3456_gc = (0x03<<3),	///< Event Channel 3,4,5,6
	ADC_EVSEL_4567_gc = (0x04<<3),	///< Event Channel 4,5,6,7
	ADC_EVSEL_567_gc = (0x05<<3),	///< Event Channel 5,6,7
	ADC_EVSEL_67_gc = (0x06<<3),	///< Event Channel 6,7
	ADC_EVSEL_7_gc = (0x07<<3),	///< Event Channel 7
} ADC_EVSEL_t;
	
/// Event action selection

typedef enum ADC_EVACT_enum {
	ADC_EVACT_NONE_gc = (0x00<<0),	///< No event action
	ADC_EVACT_CH0_gc = (0x01<<0),	///< First event triggers channel 0
	ADC_EVACT_CH01_gc = (0x02<<0),	///< First two events trigger channel 0,1
	ADC_EVACT_CH012_gc = (0x03<<0),	///< First three events trigger channel 0,1,2
	ADC_EVACT_CH0123_gc = (0x04<<0),	///< Events trigger channel 0,1,2,3
	ADC_EVACT_SWEEP_gc = (0x05<<0),	///< First event triggers sweep
	ADC_EVACT_SYNCHSWEEP_gc = (0x06<<0),	///< First event triggers synchronized sweep
} ADC_EVACT_t;
	
/// Interupt mode

typedef enum ADC_CH_INTMODE_enum {
	ADC_CH_INTMODE_COMPLETE_gc = (0x00<<2),	///< Interrupt on conversion complete
	ADC_CH_INTMODE_BELOW_gc = (0x01<<2),	///< Interrupt on result below compare value
	ADC_CH_INTMODE_ABOVE_gc = (0x03<<2),	///< Interrupt on result above compare value
} ADC_CH_INTMODE_t;
	
/// Interrupt level

typedef enum ADC_CH_INTLVL_enum {
	ADC_CH_INTLVL_OFF_gc = (0x00<<0),	///< Interrupt disabled
	ADC_CH_INTLVL_LO_gc = (0x01<<0),	///< Low level
	ADC_CH_INTLVL_MED_gc = (0x02<<0),	///< Medium level
	ADC_CH_INTLVL_HI_gc = (0x03<<0),	///< High level
} ADC_CH_INTLVL_t;
	
/// DMA request selection

typedef enum ADC_DMASEL_enum {
	ADC_DMASEL_OFF_gc = (0x00<<6),	///< Combined DMA request OFF
	ADC_DMASEL_CH01_gc = (0x01<<6),	///< ADC Channel 0 or 1
	ADC_DMASEL_CH012_gc = (0x02<<6),	///< ADC Channel 0 or 1 or 2
	ADC_DMASEL_CH0123_gc = (0x03<<6),	///< ADC Channel 0 or 1 or 2 or 3
} ADC_DMASEL_t;
	
/// Clock prescaler

typedef enum ADC_PRESCALER_enum {
	ADC_PRESCALER_DIV4_gc = (0x00<<0),	///< Divide clock by 4
	ADC_PRESCALER_DIV8_gc = (0x01<<0),	///< Divide clock by 8
	ADC_PRESCALER_DIV16_gc = (0x02<<0),	///< Divide clock by 16
	ADC_PRESCALER_DIV32_gc = (0x03<<0),	///< Divide clock by 32
	ADC_PRESCALER_DIV64_gc = (0x04<<0),	///< Divide clock by 64
	ADC_PRESCALER_DIV128_gc = (0x05<<0),	///< Divide clock by 128
	ADC_PRESCALER_DIV256_gc = (0x06<<0),	///< Divide clock by 256
	ADC_PRESCALER_DIV512_gc = (0x07<<0),	///< Divide clock by 512
} ADC_PRESCALER_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Positive input multiplexer selection
#define ADC_CH_MUXPOS_PIN0_gc (0x00<<3)	///< Input pin 0
#define ADC_CH_MUXPOS_PIN1_gc (0x01<<3)	///< Input pin 1
#define ADC_CH_MUXPOS_PIN2_gc (0x02<<3)	///< Input pin 2
#define ADC_CH_MUXPOS_PIN3_gc (0x03<<3)	///< Input pin 3
#define ADC_CH_MUXPOS_PIN4_gc (0x04<<3)	///< Input pin 4
#define ADC_CH_MUXPOS_PIN5_gc (0x05<<3)	///< Input pin 5
#define ADC_CH_MUXPOS_PIN6_gc (0x06<<3)	///< Input pin 6
#define ADC_CH_MUXPOS_PIN7_gc (0x07<<3)	///< Input pin 7

/// Internal input multiplexer selections
#define ADC_CH_MUXINT_TEMP_gc (0x00<<3)	///< Temperature Reference
#define ADC_CH_MUXINT_BANDGAP_gc (0x01<<3)	///< Bandgap Reference
#define ADC_CH_MUXINT_SCALEDVCC_gc (0x02<<3)	///< 1/10 scaled VCC
#define ADC_CH_MUXINT_DAC_gc (0x03<<3)	///< DAC output

/// Negative input multiplexer selection
#define ADC_CH_MUXNEG_PIN0_gc (0x00<<0)	///< Input pin 0
#define ADC_CH_MUXNEG_PIN1_gc (0x01<<0)	///< Input pin 1
#define ADC_CH_MUXNEG_PIN2_gc (0x02<<0)	///< Input pin 2
#define ADC_CH_MUXNEG_PIN3_gc (0x03<<0)	///< Input pin 3
#define ADC_CH_MUXNEG_PIN4_gc (0x04<<0)	///< Input pin 4
#define ADC_CH_MUXNEG_PIN5_gc (0x05<<0)	///< Input pin 5
#define ADC_CH_MUXNEG_PIN6_gc (0x06<<0)	///< Input pin 6
#define ADC_CH_MUXNEG_PIN7_gc (0x07<<0)	///< Input pin 7

/// Input mode
#define ADC_CH_INPUTMODE_INTERNAL_gc (0x00<<0)	///< Internal inputs, no gain
#define ADC_CH_INPUTMODE_SINGLEENDED_gc (0x01<<0)	///< Single-ended input, no gain
#define ADC_CH_INPUTMODE_DIFF_gc (0x02<<0)	///< Differential input, no gain
#define ADC_CH_INPUTMODE_DIFFWGAIN_gc (0x03<<0)	///< Differential input, with gain

/// Gain factor
#define ADC_CH_GAIN_1X_gc (0x00<<2)	///< 1x gain
#define ADC_CH_GAIN_2X_gc (0x01<<2)	///< 2x gain
#define ADC_CH_GAIN_4X_gc (0x02<<2)	///< 4x gain
#define ADC_CH_GAIN_8X_gc (0x03<<2)	///< 8x gain
#define ADC_CH_GAIN_16X_gc (0x04<<2)	///< 16x gain
#define ADC_CH_GAIN_32X_gc (0x05<<2)	///< 32x gain
#define ADC_CH_GAIN_64X_gc (0x06<<2)	///< 64x gain

/// Conversion result resolution
#define ADC_RESOLUTION_12BIT_gc (0x00<<1)	///< 12-bit right-adjusted result
#define ADC_RESOLUTION_8BIT_gc (0x02<<1)	///< 8-bit right-adjusted result
#define ADC_RESOLUTION_LEFT12BIT_gc (0x03<<1)	///< 12-bit left-adjusted result

/// Voltage reference selection
#define ADC_REFSEL_INT1V_gc (0x00<<4)	///< Internal 1V
#define ADC_REFSEL_VCC_gc (0x01<<4)	///< Internal VCC / 1.6V
#define ADC_REFSEL_AREFA_gc (0x02<<4)	///< External reference on PORT A
#define ADC_REFSEL_AREFB_gc (0x03<<4)	///< External reference on PORT B

/// Channel sweep selection
#define ADC_SWEEP_0_gc (0x00<<6)	///< ADC Channel 0
#define ADC_SWEEP_01_gc (0x01<<6)	///< ADC Channel 0,1
#define ADC_SWEEP_012_gc (0x02<<6)	///< ADC Channel 0,1,2
#define ADC_SWEEP_0123_gc (0x03<<6)	///< ADC Channel 0,1,2,3

/// Event channel input selection
#define ADC_EVSEL_0123_gc (0x00<<3)	///< Event Channel 0,1,2,3
#define ADC_EVSEL_1234_gc (0x01<<3)	///< Event Channel 1,2,3,4
#define ADC_EVSEL_2345_gc (0x02<<3)	///< Event Channel 2,3,4,5
#define ADC_EVSEL_3456_gc (0x03<<3)	///< Event Channel 3,4,5,6
#define ADC_EVSEL_4567_gc (0x04<<3)	///< Event Channel 4,5,6,7
#define ADC_EVSEL_567_gc (0x05<<3)	///< Event Channel 5,6,7
#define ADC_EVSEL_67_gc (0x06<<3)	///< Event Channel 6,7
#define ADC_EVSEL_7_gc (0x07<<3)	///< Event Channel 7

/// Event action selection
#define ADC_EVACT_NONE_gc (0x00<<0)	///< No event action
#define ADC_EVACT_CH0_gc (0x01<<0)	///< First event triggers channel 0
#define ADC_EVACT_CH01_gc (0x02<<0)	///< First two events trigger channel 0,1
#define ADC_EVACT_CH012_gc (0x03<<0)	///< First three events trigger channel 0,1,2
#define ADC_EVACT_CH0123_gc (0x04<<0)	///< Events trigger channel 0,1,2,3
#define ADC_EVACT_SWEEP_gc (0x05<<0)	///< First event triggers sweep
#define ADC_EVACT_SYNCHSWEEP_gc (0x06<<0)	///< First event triggers synchronized sweep

/// Interupt mode
#define ADC_CH_INTMODE_COMPLETE_gc (0x00<<2)	///< Interrupt on conversion complete
#define ADC_CH_INTMODE_BELOW_gc (0x01<<2)	///< Interrupt on result below compare value
#define ADC_CH_INTMODE_ABOVE_gc (0x03<<2)	///< Interrupt on result above compare value

/// Interrupt level
#define ADC_CH_INTLVL_OFF_gc (0x00<<0)	///< Interrupt disabled
#define ADC_CH_INTLVL_LO_gc (0x01<<0)	///< Low level
#define ADC_CH_INTLVL_MED_gc (0x02<<0)	///< Medium level
#define ADC_CH_INTLVL_HI_gc (0x03<<0)	///< High level

/// DMA request selection
#define ADC_DMASEL_OFF_gc (0x00<<6)	///< Combined DMA request OFF
#define ADC_DMASEL_CH01_gc (0x01<<6)	///< ADC Channel 0 or 1
#define ADC_DMASEL_CH012_gc (0x02<<6)	///< ADC Channel 0 or 1 or 2
#define ADC_DMASEL_CH0123_gc (0x03<<6)	///< ADC Channel 0 or 1 or 2 or 3

/// Clock prescaler
#define ADC_PRESCALER_DIV4_gc (0x00<<0)	///< Divide clock by 4
#define ADC_PRESCALER_DIV8_gc (0x01<<0)	///< Divide clock by 8
#define ADC_PRESCALER_DIV16_gc (0x02<<0)	///< Divide clock by 16
#define ADC_PRESCALER_DIV32_gc (0x03<<0)	///< Divide clock by 32
#define ADC_PRESCALER_DIV64_gc (0x04<<0)	///< Divide clock by 64
#define ADC_PRESCALER_DIV128_gc (0x05<<0)	///< Divide clock by 128
#define ADC_PRESCALER_DIV256_gc (0x06<<0)	///< Divide clock by 256
#define ADC_PRESCALER_DIV512_gc (0x07<<0)	///< Divide clock by 512

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup dac Digital/Analog Converter
 *  @{
 */
	
/** @name DAC.CTRLA
  * @{
  */
#define DAC_IDOEN_bm 0x10 ///< Internal Output Enable bit mask
#define DAC_IDOEN_bp 4 ///< Internal Output Enable bit position
#define DAC_CH1EN_bm 0x08 ///< Channel 1 Output Enable bit mask
#define DAC_CH1EN_bp 3 ///< Channel 1 Output Enable bit position
#define DAC_CH0EN_bm 0x04 ///< Channel 0 Output Enable bit mask
#define DAC_CH0EN_bp 2 ///< Channel 0 Output Enable bit position
#define DAC_LPMODE_bm 0x02 ///< Low Power Mode bit mask
#define DAC_LPMODE_bp 1 ///< Low Power Mode bit position
#define DAC_ENABLE_bm 0x01 ///< Enable bit mask
#define DAC_ENABLE_bp 0 ///< Enable bit position
/** @} */
	
/** @name DAC.CTRLB
  * @see DAC_CHSEL_enum
  * @{
  */
#define DAC_CHSEL_gm 0x60 ///< Channel Select group mask
#define DAC_CHSEL_gp 5 ///< Channel Select group position
#define DAC_CHSEL0_bm (1<<5) ///< Channel Select bit 0 mask
#define DAC_CHSEL0_bp 5 ///< Channel Select bit 0 position
#define DAC_CHSEL1_bm (1<<6) ///< Channel Select bit 1 mask
#define DAC_CHSEL1_bp 6 ///< Channel Select bit 1 position
#define DAC_CH1TRIG_bm 0x02 ///< Channel 1 Event Trig Enable bit mask
#define DAC_CH1TRIG_bp 1 ///< Channel 1 Event Trig Enable bit position
#define DAC_CH0TRIG_bm 0x01 ///< Channel 0 Event Trig Enable bit mask
#define DAC_CH0TRIG_bp 0 ///< Channel 0 Event Trig Enable bit position
/** @} */
	
/** @name DAC.CTRLC
  * @see DAC_REFSEL_enum
  * @{
  */
#define DAC_REFSEL_gm 0x18 ///< Reference Select group mask
#define DAC_REFSEL_gp 3 ///< Reference Select group position
#define DAC_REFSEL0_bm (1<<3) ///< Reference Select bit 0 mask
#define DAC_REFSEL0_bp 3 ///< Reference Select bit 0 position
#define DAC_REFSEL1_bm (1<<4) ///< Reference Select bit 1 mask
#define DAC_REFSEL1_bp 4 ///< Reference Select bit 1 position
#define DAC_LEFTADJ_bm 0x01 ///< Left-adjust Result bit mask
#define DAC_LEFTADJ_bp 0 ///< Left-adjust Result bit position
/** @} */
	
/** @name DAC.EVCTRL
  * @see DAC_EVSEL_enum
  * @{
  */
#define DAC_EVSEL_gm 0x07 ///< Event Input Selection group mask
#define DAC_EVSEL_gp 0 ///< Event Input Selection group position
#define DAC_EVSEL0_bm (1<<0) ///< Event Input Selection bit 0 mask
#define DAC_EVSEL0_bp 0 ///< Event Input Selection bit 0 position
#define DAC_EVSEL1_bm (1<<1) ///< Event Input Selection bit 1 mask
#define DAC_EVSEL1_bp 1 ///< Event Input Selection bit 1 position
#define DAC_EVSEL2_bm (1<<2) ///< Event Input Selection bit 2 mask
#define DAC_EVSEL2_bp 2 ///< Event Input Selection bit 2 position
/** @} */
	
/** @name DAC.TIMCTRL
  * @see DAC_CONINTVAL_enum
  * @see DAC_REFRESH_enum
  * @{
  */
#define DAC_CONINTVAL_gm 0x70 ///< Conversion Intercal group mask
#define DAC_CONINTVAL_gp 4 ///< Conversion Intercal group position
#define DAC_CONINTVAL0_bm (1<<4) ///< Conversion Intercal bit 0 mask
#define DAC_CONINTVAL0_bp 4 ///< Conversion Intercal bit 0 position
#define DAC_CONINTVAL1_bm (1<<5) ///< Conversion Intercal bit 1 mask
#define DAC_CONINTVAL1_bp 5 ///< Conversion Intercal bit 1 position
#define DAC_CONINTVAL2_bm (1<<6) ///< Conversion Intercal bit 2 mask
#define DAC_CONINTVAL2_bp 6 ///< Conversion Intercal bit 2 position
#define DAC_REFRESH_gm 0x0F ///< Refresh Timing Control group mask
#define DAC_REFRESH_gp 0 ///< Refresh Timing Control group position
#define DAC_REFRESH0_bm (1<<0) ///< Refresh Timing Control bit 0 mask
#define DAC_REFRESH0_bp 0 ///< Refresh Timing Control bit 0 position
#define DAC_REFRESH1_bm (1<<1) ///< Refresh Timing Control bit 1 mask
#define DAC_REFRESH1_bp 1 ///< Refresh Timing Control bit 1 position
#define DAC_REFRESH2_bm (1<<2) ///< Refresh Timing Control bit 2 mask
#define DAC_REFRESH2_bp 2 ///< Refresh Timing Control bit 2 position
#define DAC_REFRESH3_bm (1<<3) ///< Refresh Timing Control bit 3 mask
#define DAC_REFRESH3_bp 3 ///< Refresh Timing Control bit 3 position
/** @} */
	
/** @name DAC.STATUS
  * @{
  */
#define DAC_CH1DRE_bm 0x02 ///< Channel 1 Data Register Empty bit mask
#define DAC_CH1DRE_bp 1 ///< Channel 1 Data Register Empty bit position
#define DAC_CH0DRE_bm 0x01 ///< Channel 0 Data Register Empty bit mask
#define DAC_CH0DRE_bp 0 ///< Channel 0 Data Register Empty bit position
/** @} */
	
/** @name DAC.GAINCAL
  * @{
  */
#define DAC_GAINCAL_gm 0x7F ///< Gain Calibration group mask
#define DAC_GAINCAL_gp 0 ///< Gain Calibration group position
#define DAC_GAINCAL0_bm (1<<0) ///< Gain Calibration bit 0 mask
#define DAC_GAINCAL0_bp 0 ///< Gain Calibration bit 0 position
#define DAC_GAINCAL1_bm (1<<1) ///< Gain Calibration bit 1 mask
#define DAC_GAINCAL1_bp 1 ///< Gain Calibration bit 1 position
#define DAC_GAINCAL2_bm (1<<2) ///< Gain Calibration bit 2 mask
#define DAC_GAINCAL2_bp 2 ///< Gain Calibration bit 2 position
#define DAC_GAINCAL3_bm (1<<3) ///< Gain Calibration bit 3 mask
#define DAC_GAINCAL3_bp 3 ///< Gain Calibration bit 3 position
#define DAC_GAINCAL4_bm (1<<4) ///< Gain Calibration bit 4 mask
#define DAC_GAINCAL4_bp 4 ///< Gain Calibration bit 4 position
#define DAC_GAINCAL5_bm (1<<5) ///< Gain Calibration bit 5 mask
#define DAC_GAINCAL5_bp 5 ///< Gain Calibration bit 5 position
#define DAC_GAINCAL6_bm (1<<6) ///< Gain Calibration bit 6 mask
#define DAC_GAINCAL6_bp 6 ///< Gain Calibration bit 6 position
/** @} */
	
/** @name DAC.OFFSETCAL
  * @{
  */
#define DAC_OFFSETCAL_gm 0x7F ///< Offset Calibration group mask
#define DAC_OFFSETCAL_gp 0 ///< Offset Calibration group position
#define DAC_OFFSETCAL0_bm (1<<0) ///< Offset Calibration bit 0 mask
#define DAC_OFFSETCAL0_bp 0 ///< Offset Calibration bit 0 position
#define DAC_OFFSETCAL1_bm (1<<1) ///< Offset Calibration bit 1 mask
#define DAC_OFFSETCAL1_bp 1 ///< Offset Calibration bit 1 position
#define DAC_OFFSETCAL2_bm (1<<2) ///< Offset Calibration bit 2 mask
#define DAC_OFFSETCAL2_bp 2 ///< Offset Calibration bit 2 position
#define DAC_OFFSETCAL3_bm (1<<3) ///< Offset Calibration bit 3 mask
#define DAC_OFFSETCAL3_bp 3 ///< Offset Calibration bit 3 position
#define DAC_OFFSETCAL4_bm (1<<4) ///< Offset Calibration bit 4 mask
#define DAC_OFFSETCAL4_bp 4 ///< Offset Calibration bit 4 position
#define DAC_OFFSETCAL5_bm (1<<5) ///< Offset Calibration bit 5 mask
#define DAC_OFFSETCAL5_bp 5 ///< Offset Calibration bit 5 position
#define DAC_OFFSETCAL6_bm (1<<6) ///< Offset Calibration bit 6 mask
#define DAC_OFFSETCAL6_bp 6 ///< Offset Calibration bit 6 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Output channel selection

typedef enum DAC_CHSEL_enum {
	DAC_CHSEL_SINGLE_gc = (0x00<<5),	///< Single channel operation (Channel A only)
	DAC_CHSEL_DUAL_gc = (0x02<<5),	///< Dual channel operation (S/H on both channels)
} DAC_CHSEL_t;
	
/// Reference voltage selection

typedef enum DAC_REFSEL_enum {
	DAC_REFSEL_INT1V_gc = (0x00<<3),	///< Internal 1V 
	DAC_REFSEL_AVCC_gc = (0x01<<3),	///< Analog supply voltage
	DAC_REFSEL_AREFA_gc = (0x02<<3),	///< External reference on AREF on PORTA
	DAC_REFSEL_AREFB_gc = (0x03<<3),	///< External reference on AREF on PORTB
} DAC_REFSEL_t;
	
/// Event channel selection

typedef enum DAC_EVSEL_enum {
	DAC_EVSEL_0_gc = (0x00<<0),	///< Event Channel 0
	DAC_EVSEL_1_gc = (0x01<<0),	///< Event Channel 1
	DAC_EVSEL_2_gc = (0x02<<0),	///< Event Channel 2
	DAC_EVSEL_3_gc = (0x03<<0),	///< Event Channel 3
	DAC_EVSEL_4_gc = (0x04<<0),	///< Event Channel 4
	DAC_EVSEL_5_gc = (0x05<<0),	///< Event Channel 5
	DAC_EVSEL_6_gc = (0x06<<0),	///< Event Channel 6
	DAC_EVSEL_7_gc = (0x07<<0),	///< Event Channel 7
} DAC_EVSEL_t;
	
/// Conversion interval

typedef enum DAC_CONINTVAL_enum {
	DAC_CONINTVAL_1CLK_gc = (0x00<<4),	///< 1 CLK / 2 CLK in S/H mode
	DAC_CONINTVAL_2CLK_gc = (0x01<<4),	///< 2 CLK / 3 CLK in S/H mode
	DAC_CONINTVAL_4CLK_gc = (0x02<<4),	///< 4 CLK / 6 CLK in S/H mode
	DAC_CONINTVAL_8CLK_gc = (0x03<<4),	///< 8 CLK / 12 CLK in S/H mode
	DAC_CONINTVAL_16CLK_gc = (0x04<<4),	///< 16 CLK / 24 CLK in S/H mode
	DAC_CONINTVAL_32CLK_gc = (0x05<<4),	///< 32 CLK / 48 CLK in S/H mode
	DAC_CONINTVAL_64CLK_gc = (0x06<<4),	///< 64 CLK / 96 CLK in S/H mode
	DAC_CONINTVAL_128CLK_gc = (0x07<<4),	///< 128 CLK / 192 CLK in S/H mode
} DAC_CONINTVAL_t;
	
/// Refresh rate

typedef enum DAC_REFRESH_enum {
	DAC_REFRESH_16CLK_gc = (0x00<<0),	///< 16 CLK
	DAC_REFRESH_32CLK_gc = (0x01<<0),	///< 32 CLK
	DAC_REFRESH_64CLK_gc = (0x02<<0),	///< 64 CLK
	DAC_REFRESH_128CLK_gc = (0x03<<0),	///< 128 CLK
	DAC_REFRESH_256CLK_gc = (0x04<<0),	///< 256 CLK
	DAC_REFRESH_512CLK_gc = (0x05<<0),	///< 512 CLK
	DAC_REFRESH_1024CLK_gc = (0x06<<0),	///< 1024 CLK
	DAC_REFRESH_2048CLK_gc = (0x07<<0),	///< 2048 CLK
	DAC_REFRESH_4096CLK_gc = (0x08<<0),	///< 4096 CLK
	DAC_REFRESH_8192CLK_gc = (0x09<<0),	///< 8192 CLK
	DAC_REFRESH_16384CLK_gc = (0x0A<<0),	///< 16384 CLK
	DAC_REFRESH_32768CLK_gc = (0x0B<<0),	///< 32768 CLK
	DAC_REFRESH_65536CLK_gc = (0x0C<<0),	///< 65536 CLK
	DAC_REFRESH_OFF_gc = (0x0F<<0),	///< Auto refresh OFF
} DAC_REFRESH_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Output channel selection
#define DAC_CHSEL_SINGLE_gc (0x00<<5)	///< Single channel operation (Channel A only)
#define DAC_CHSEL_DUAL_gc (0x02<<5)	///< Dual channel operation (S/H on both channels)

/// Reference voltage selection
#define DAC_REFSEL_INT1V_gc (0x00<<3)	///< Internal 1V 
#define DAC_REFSEL_AVCC_gc (0x01<<3)	///< Analog supply voltage
#define DAC_REFSEL_AREFA_gc (0x02<<3)	///< External reference on AREF on PORTA
#define DAC_REFSEL_AREFB_gc (0x03<<3)	///< External reference on AREF on PORTB

/// Event channel selection
#define DAC_EVSEL_0_gc (0x00<<0)	///< Event Channel 0
#define DAC_EVSEL_1_gc (0x01<<0)	///< Event Channel 1
#define DAC_EVSEL_2_gc (0x02<<0)	///< Event Channel 2
#define DAC_EVSEL_3_gc (0x03<<0)	///< Event Channel 3
#define DAC_EVSEL_4_gc (0x04<<0)	///< Event Channel 4
#define DAC_EVSEL_5_gc (0x05<<0)	///< Event Channel 5
#define DAC_EVSEL_6_gc (0x06<<0)	///< Event Channel 6
#define DAC_EVSEL_7_gc (0x07<<0)	///< Event Channel 7

/// Conversion interval
#define DAC_CONINTVAL_1CLK_gc (0x00<<4)	///< 1 CLK / 2 CLK in S/H mode
#define DAC_CONINTVAL_2CLK_gc (0x01<<4)	///< 2 CLK / 3 CLK in S/H mode
#define DAC_CONINTVAL_4CLK_gc (0x02<<4)	///< 4 CLK / 6 CLK in S/H mode
#define DAC_CONINTVAL_8CLK_gc (0x03<<4)	///< 8 CLK / 12 CLK in S/H mode
#define DAC_CONINTVAL_16CLK_gc (0x04<<4)	///< 16 CLK / 24 CLK in S/H mode
#define DAC_CONINTVAL_32CLK_gc (0x05<<4)	///< 32 CLK / 48 CLK in S/H mode
#define DAC_CONINTVAL_64CLK_gc (0x06<<4)	///< 64 CLK / 96 CLK in S/H mode
#define DAC_CONINTVAL_128CLK_gc (0x07<<4)	///< 128 CLK / 192 CLK in S/H mode

/// Refresh rate
#define DAC_REFRESH_16CLK_gc (0x00<<0)	///< 16 CLK
#define DAC_REFRESH_32CLK_gc (0x01<<0)	///< 32 CLK
#define DAC_REFRESH_64CLK_gc (0x02<<0)	///< 64 CLK
#define DAC_REFRESH_128CLK_gc (0x03<<0)	///< 128 CLK
#define DAC_REFRESH_256CLK_gc (0x04<<0)	///< 256 CLK
#define DAC_REFRESH_512CLK_gc (0x05<<0)	///< 512 CLK
#define DAC_REFRESH_1024CLK_gc (0x06<<0)	///< 1024 CLK
#define DAC_REFRESH_2048CLK_gc (0x07<<0)	///< 2048 CLK
#define DAC_REFRESH_4096CLK_gc (0x08<<0)	///< 4096 CLK
#define DAC_REFRESH_8192CLK_gc (0x09<<0)	///< 8192 CLK
#define DAC_REFRESH_16384CLK_gc (0x0A<<0)	///< 16384 CLK
#define DAC_REFRESH_32768CLK_gc (0x0B<<0)	///< 32768 CLK
#define DAC_REFRESH_65536CLK_gc (0x0C<<0)	///< 65536 CLK
#define DAC_REFRESH_OFF_gc (0x0F<<0)	///< Auto refresh OFF

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup rtc Real-Time Clounter
 *  @{
 */
	
/** @name RTC.CTRL
  * @see RTC_PRESCALER_enum
  * @{
  */
#define RTC_PRESCALER_gm 0x07 ///< Prescaling Factor group mask
#define RTC_PRESCALER_gp 0 ///< Prescaling Factor group position
#define RTC_PRESCALER0_bm (1<<0) ///< Prescaling Factor bit 0 mask
#define RTC_PRESCALER0_bp 0 ///< Prescaling Factor bit 0 position
#define RTC_PRESCALER1_bm (1<<1) ///< Prescaling Factor bit 1 mask
#define RTC_PRESCALER1_bp 1 ///< Prescaling Factor bit 1 position
#define RTC_PRESCALER2_bm (1<<2) ///< Prescaling Factor bit 2 mask
#define RTC_PRESCALER2_bp 2 ///< Prescaling Factor bit 2 position
/** @} */
	
/** @name RTC.STATUS
  * @{
  */
#define RTC_SYNCBUSY_bm 0x01 ///< Synchronization Busy Flag bit mask
#define RTC_SYNCBUSY_bp 0 ///< Synchronization Busy Flag bit position
/** @} */
	
/** @name RTC.INTCTRL
  * @see RTC_COMPINTLVL_enum
  * @see RTC_OVFINTLVL_enum
  * @{
  */
#define RTC_COMPINTLVL_gm 0x0C ///< Compare Match Interrupt Level group mask
#define RTC_COMPINTLVL_gp 2 ///< Compare Match Interrupt Level group position
#define RTC_COMPINTLVL0_bm (1<<2) ///< Compare Match Interrupt Level bit 0 mask
#define RTC_COMPINTLVL0_bp 2 ///< Compare Match Interrupt Level bit 0 position
#define RTC_COMPINTLVL1_bm (1<<3) ///< Compare Match Interrupt Level bit 1 mask
#define RTC_COMPINTLVL1_bp 3 ///< Compare Match Interrupt Level bit 1 position
#define RTC_OVFINTLVL_gm 0x03 ///< Overflow Interrupt Level group mask
#define RTC_OVFINTLVL_gp 0 ///< Overflow Interrupt Level group position
#define RTC_OVFINTLVL0_bm (1<<0) ///< Overflow Interrupt Level bit 0 mask
#define RTC_OVFINTLVL0_bp 0 ///< Overflow Interrupt Level bit 0 position
#define RTC_OVFINTLVL1_bm (1<<1) ///< Overflow Interrupt Level bit 1 mask
#define RTC_OVFINTLVL1_bp 1 ///< Overflow Interrupt Level bit 1 position
/** @} */
	
/** @name RTC.INTFLAGS
  * @{
  */
#define RTC_COMPIF_bm 0x02 ///< Compare Match Interrupt Flag bit mask
#define RTC_COMPIF_bp 1 ///< Compare Match Interrupt Flag bit position
#define RTC_OVFIF_bm 0x01 ///< Overflow Interrupt Flag bit mask
#define RTC_OVFIF_bp 0 ///< Overflow Interrupt Flag bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Prescaler Factor

typedef enum RTC_PRESCALER_enum {
	RTC_PRESCALER_OFF_gc = (0x00<<0),	///< RTC Off
	RTC_PRESCALER_DIV1_gc = (0x01<<0),	///< RTC Clock
	RTC_PRESCALER_DIV2_gc = (0x02<<0),	///< RTC Clock / 2
	RTC_PRESCALER_DIV8_gc = (0x03<<0),	///< RTC Clock / 8
	RTC_PRESCALER_DIV16_gc = (0x04<<0),	///< RTC Clock / 16
	RTC_PRESCALER_DIV64_gc = (0x05<<0),	///< RTC Clock / 64
	RTC_PRESCALER_DIV256_gc = (0x06<<0),	///< RTC Clock / 256
	RTC_PRESCALER_DIV1024_gc = (0x07<<0),	///< RTC Clock / 1024
} RTC_PRESCALER_t;
	
/// Compare Interrupt level

typedef enum RTC_COMPINTLVL_enum {
	RTC_COMPINTLVL_OFF_gc = (0x00<<2),	///< Interrupt Disabled
	RTC_COMPINTLVL_LO_gc = (0x01<<2),	///< Low Level
	RTC_COMPINTLVL_MED_gc = (0x02<<2),	///< Medium Level
	RTC_COMPINTLVL_HI_gc = (0x03<<2),	///< High Level
} RTC_COMPINTLVL_t;
	
/// Overflow Interrupt level

typedef enum RTC_OVFINTLVL_enum {
	RTC_OVFINTLVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	RTC_OVFINTLVL_LO_gc = (0x01<<0),	///< Low Level
	RTC_OVFINTLVL_MED_gc = (0x02<<0),	///< Medium Level
	RTC_OVFINTLVL_HI_gc = (0x03<<0),	///< High Level
} RTC_OVFINTLVL_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Prescaler Factor
#define RTC_PRESCALER_OFF_gc (0x00<<0)	///< RTC Off
#define RTC_PRESCALER_DIV1_gc (0x01<<0)	///< RTC Clock
#define RTC_PRESCALER_DIV2_gc (0x02<<0)	///< RTC Clock / 2
#define RTC_PRESCALER_DIV8_gc (0x03<<0)	///< RTC Clock / 8
#define RTC_PRESCALER_DIV16_gc (0x04<<0)	///< RTC Clock / 16
#define RTC_PRESCALER_DIV64_gc (0x05<<0)	///< RTC Clock / 64
#define RTC_PRESCALER_DIV256_gc (0x06<<0)	///< RTC Clock / 256
#define RTC_PRESCALER_DIV1024_gc (0x07<<0)	///< RTC Clock / 1024

/// Compare Interrupt level
#define RTC_COMPINTLVL_OFF_gc (0x00<<2)	///< Interrupt Disabled
#define RTC_COMPINTLVL_LO_gc (0x01<<2)	///< Low Level
#define RTC_COMPINTLVL_MED_gc (0x02<<2)	///< Medium Level
#define RTC_COMPINTLVL_HI_gc (0x03<<2)	///< High Level

/// Overflow Interrupt level
#define RTC_OVFINTLVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define RTC_OVFINTLVL_LO_gc (0x01<<0)	///< Low Level
#define RTC_OVFINTLVL_MED_gc (0x02<<0)	///< Medium Level
#define RTC_OVFINTLVL_HI_gc (0x03<<0)	///< High Level

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup ebi External Bus Interface
 *  @{
 */
	
/** @name EBI_CS.CTRLA
  * @see EBI_CS_ASIZE_enum
  * @see EBI_CS_MODE_enum
  * @{
  */
#define EBI_CS_ASIZE_gm 0x7C ///< Address Space group mask
#define EBI_CS_ASIZE_gp 2 ///< Address Space group position
#define EBI_CS_ASIZE0_bm (1<<2) ///< Address Space bit 0 mask
#define EBI_CS_ASIZE0_bp 2 ///< Address Space bit 0 position
#define EBI_CS_ASIZE1_bm (1<<3) ///< Address Space bit 1 mask
#define EBI_CS_ASIZE1_bp 3 ///< Address Space bit 1 position
#define EBI_CS_ASIZE2_bm (1<<4) ///< Address Space bit 2 mask
#define EBI_CS_ASIZE2_bp 4 ///< Address Space bit 2 position
#define EBI_CS_ASIZE3_bm (1<<5) ///< Address Space bit 3 mask
#define EBI_CS_ASIZE3_bp 5 ///< Address Space bit 3 position
#define EBI_CS_ASIZE4_bm (1<<6) ///< Address Space bit 4 mask
#define EBI_CS_ASIZE4_bp 6 ///< Address Space bit 4 position
#define EBI_CS_MODE_gm 0x03 ///< Memory Mode group mask
#define EBI_CS_MODE_gp 0 ///< Memory Mode group position
#define EBI_CS_MODE0_bm (1<<0) ///< Memory Mode bit 0 mask
#define EBI_CS_MODE0_bp 0 ///< Memory Mode bit 0 position
#define EBI_CS_MODE1_bm (1<<1) ///< Memory Mode bit 1 mask
#define EBI_CS_MODE1_bp 1 ///< Memory Mode bit 1 position
/** @} */
	
/** @name EBI_CS.CTRLB
  * @see EBI_CS_SRWS_enum
  * @see EBI_CS_SDMODE_enum
  * @{
  */
#define EBI_CS_SRWS_gm 0x07 ///< SRAM Wait State Cycles group mask
#define EBI_CS_SRWS_gp 0 ///< SRAM Wait State Cycles group position
#define EBI_CS_SRWS0_bm (1<<0) ///< SRAM Wait State Cycles bit 0 mask
#define EBI_CS_SRWS0_bp 0 ///< SRAM Wait State Cycles bit 0 position
#define EBI_CS_SRWS1_bm (1<<1) ///< SRAM Wait State Cycles bit 1 mask
#define EBI_CS_SRWS1_bp 1 ///< SRAM Wait State Cycles bit 1 position
#define EBI_CS_SRWS2_bm (1<<2) ///< SRAM Wait State Cycles bit 2 mask
#define EBI_CS_SRWS2_bp 2 ///< SRAM Wait State Cycles bit 2 position
#define EBI_CS_SDINITDONE_bm 0x80 ///< SDRAM Initialization Done bit mask
#define EBI_CS_SDINITDONE_bp 7 ///< SDRAM Initialization Done bit position
#define EBI_CS_SDSREN_bm 0x04 ///< SDRAM Self-refresh Enable bit mask
#define EBI_CS_SDSREN_bp 2 ///< SDRAM Self-refresh Enable bit position
#define EBI_CS_SDMODE_gm 0x03 ///< SDRAM Mode group mask
#define EBI_CS_SDMODE_gp 0 ///< SDRAM Mode group position
#define EBI_CS_SDMODE0_bm (1<<0) ///< SDRAM Mode bit 0 mask
#define EBI_CS_SDMODE0_bp 0 ///< SDRAM Mode bit 0 position
#define EBI_CS_SDMODE1_bm (1<<1) ///< SDRAM Mode bit 1 mask
#define EBI_CS_SDMODE1_bp 1 ///< SDRAM Mode bit 1 position
/** @} */
	
/** @name EBI.CTRL
  * @see EBI_SDDATAW_enum
  * @see EBI_LPCMODE_enum
  * @see EBI_SRMODE_enum
  * @see EBI_IFMODE_enum
  * @{
  */
#define EBI_SDDATAW_gm 0xC0 ///< SDRAM Data Width Setting group mask
#define EBI_SDDATAW_gp 6 ///< SDRAM Data Width Setting group position
#define EBI_SDDATAW0_bm (1<<6) ///< SDRAM Data Width Setting bit 0 mask
#define EBI_SDDATAW0_bp 6 ///< SDRAM Data Width Setting bit 0 position
#define EBI_SDDATAW1_bm (1<<7) ///< SDRAM Data Width Setting bit 1 mask
#define EBI_SDDATAW1_bp 7 ///< SDRAM Data Width Setting bit 1 position
#define EBI_LPCMODE_gm 0x30 ///< SRAM LPC Mode group mask
#define EBI_LPCMODE_gp 4 ///< SRAM LPC Mode group position
#define EBI_LPCMODE0_bm (1<<4) ///< SRAM LPC Mode bit 0 mask
#define EBI_LPCMODE0_bp 4 ///< SRAM LPC Mode bit 0 position
#define EBI_LPCMODE1_bm (1<<5) ///< SRAM LPC Mode bit 1 mask
#define EBI_LPCMODE1_bp 5 ///< SRAM LPC Mode bit 1 position
#define EBI_SRMODE_gm 0x0C ///< SRAM Mode group mask
#define EBI_SRMODE_gp 2 ///< SRAM Mode group position
#define EBI_SRMODE0_bm (1<<2) ///< SRAM Mode bit 0 mask
#define EBI_SRMODE0_bp 2 ///< SRAM Mode bit 0 position
#define EBI_SRMODE1_bm (1<<3) ///< SRAM Mode bit 1 mask
#define EBI_SRMODE1_bp 3 ///< SRAM Mode bit 1 position
#define EBI_IFMODE_gm 0x03 ///< Interface Mode group mask
#define EBI_IFMODE_gp 0 ///< Interface Mode group position
#define EBI_IFMODE0_bm (1<<0) ///< Interface Mode bit 0 mask
#define EBI_IFMODE0_bp 0 ///< Interface Mode bit 0 position
#define EBI_IFMODE1_bm (1<<1) ///< Interface Mode bit 1 mask
#define EBI_IFMODE1_bp 1 ///< Interface Mode bit 1 position
/** @} */
	
/** @name EBI.SDRAMCTRLA
  * @see EBI_SDCOL_enum
  * @{
  */
#define EBI_SDCAS_bm 0x08 ///< SDRAM CAS Latency Setting bit mask
#define EBI_SDCAS_bp 3 ///< SDRAM CAS Latency Setting bit position
#define EBI_SDROW_bm 0x04 ///< SDRAM ROW Bits Setting bit mask
#define EBI_SDROW_bp 2 ///< SDRAM ROW Bits Setting bit position
#define EBI_SDCOL_gm 0x03 ///< SDRAM Column Bits Setting group mask
#define EBI_SDCOL_gp 0 ///< SDRAM Column Bits Setting group position
#define EBI_SDCOL0_bm (1<<0) ///< SDRAM Column Bits Setting bit 0 mask
#define EBI_SDCOL0_bp 0 ///< SDRAM Column Bits Setting bit 0 position
#define EBI_SDCOL1_bm (1<<1) ///< SDRAM Column Bits Setting bit 1 mask
#define EBI_SDCOL1_bp 1 ///< SDRAM Column Bits Setting bit 1 position
/** @} */
	
/** @name EBI.SDRAMCTRLB
  * @see EBI_MRDLY_enum
  * @see EBI_ROWCYCDLY_enum
  * @see EBI_RPDLY_enum
  * @{
  */
#define EBI_MRDLY_gm 0xC0 ///< SDRAM Mode Register Delay group mask
#define EBI_MRDLY_gp 6 ///< SDRAM Mode Register Delay group position
#define EBI_MRDLY0_bm (1<<6) ///< SDRAM Mode Register Delay bit 0 mask
#define EBI_MRDLY0_bp 6 ///< SDRAM Mode Register Delay bit 0 position
#define EBI_MRDLY1_bm (1<<7) ///< SDRAM Mode Register Delay bit 1 mask
#define EBI_MRDLY1_bp 7 ///< SDRAM Mode Register Delay bit 1 position
#define EBI_ROWCYCDLY_gm 0x38 ///< SDRAM Row Cycle Delay group mask
#define EBI_ROWCYCDLY_gp 3 ///< SDRAM Row Cycle Delay group position
#define EBI_ROWCYCDLY0_bm (1<<3) ///< SDRAM Row Cycle Delay bit 0 mask
#define EBI_ROWCYCDLY0_bp 3 ///< SDRAM Row Cycle Delay bit 0 position
#define EBI_ROWCYCDLY1_bm (1<<4) ///< SDRAM Row Cycle Delay bit 1 mask
#define EBI_ROWCYCDLY1_bp 4 ///< SDRAM Row Cycle Delay bit 1 position
#define EBI_ROWCYCDLY2_bm (1<<5) ///< SDRAM Row Cycle Delay bit 2 mask
#define EBI_ROWCYCDLY2_bp 5 ///< SDRAM Row Cycle Delay bit 2 position
#define EBI_RPDLY_gm 0x07 ///< SDRAM Row-to-Precharge Delay group mask
#define EBI_RPDLY_gp 0 ///< SDRAM Row-to-Precharge Delay group position
#define EBI_RPDLY0_bm (1<<0) ///< SDRAM Row-to-Precharge Delay bit 0 mask
#define EBI_RPDLY0_bp 0 ///< SDRAM Row-to-Precharge Delay bit 0 position
#define EBI_RPDLY1_bm (1<<1) ///< SDRAM Row-to-Precharge Delay bit 1 mask
#define EBI_RPDLY1_bp 1 ///< SDRAM Row-to-Precharge Delay bit 1 position
#define EBI_RPDLY2_bm (1<<2) ///< SDRAM Row-to-Precharge Delay bit 2 mask
#define EBI_RPDLY2_bp 2 ///< SDRAM Row-to-Precharge Delay bit 2 position
/** @} */
	
/** @name EBI.SDRAMCTRLC
  * @see EBI_WRDLY_enum
  * @see EBI_ESRDLY_enum
  * @see EBI_ROWCOLDLY_enum
  * @{
  */
#define EBI_WRDLY_gm 0xC0 ///< SDRAM Write Recovery Delay group mask
#define EBI_WRDLY_gp 6 ///< SDRAM Write Recovery Delay group position
#define EBI_WRDLY0_bm (1<<6) ///< SDRAM Write Recovery Delay bit 0 mask
#define EBI_WRDLY0_bp 6 ///< SDRAM Write Recovery Delay bit 0 position
#define EBI_WRDLY1_bm (1<<7) ///< SDRAM Write Recovery Delay bit 1 mask
#define EBI_WRDLY1_bp 7 ///< SDRAM Write Recovery Delay bit 1 position
#define EBI_ESRDLY_gm 0x38 ///< SDRAM Exit-Self-refresh-to-Active Delay group mask
#define EBI_ESRDLY_gp 3 ///< SDRAM Exit-Self-refresh-to-Active Delay group position
#define EBI_ESRDLY0_bm (1<<3) ///< SDRAM Exit-Self-refresh-to-Active Delay bit 0 mask
#define EBI_ESRDLY0_bp 3 ///< SDRAM Exit-Self-refresh-to-Active Delay bit 0 position
#define EBI_ESRDLY1_bm (1<<4) ///< SDRAM Exit-Self-refresh-to-Active Delay bit 1 mask
#define EBI_ESRDLY1_bp 4 ///< SDRAM Exit-Self-refresh-to-Active Delay bit 1 position
#define EBI_ESRDLY2_bm (1<<5) ///< SDRAM Exit-Self-refresh-to-Active Delay bit 2 mask
#define EBI_ESRDLY2_bp 5 ///< SDRAM Exit-Self-refresh-to-Active Delay bit 2 position
#define EBI_ROWCOLDLY_gm 0x07 ///< SDRAM Row-to-Column Delay group mask
#define EBI_ROWCOLDLY_gp 0 ///< SDRAM Row-to-Column Delay group position
#define EBI_ROWCOLDLY0_bm (1<<0) ///< SDRAM Row-to-Column Delay bit 0 mask
#define EBI_ROWCOLDLY0_bp 0 ///< SDRAM Row-to-Column Delay bit 0 position
#define EBI_ROWCOLDLY1_bm (1<<1) ///< SDRAM Row-to-Column Delay bit 1 mask
#define EBI_ROWCOLDLY1_bp 1 ///< SDRAM Row-to-Column Delay bit 1 position
#define EBI_ROWCOLDLY2_bm (1<<2) ///< SDRAM Row-to-Column Delay bit 2 mask
#define EBI_ROWCOLDLY2_bp 2 ///< SDRAM Row-to-Column Delay bit 2 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Chip Select adress space

typedef enum EBI_CS_ASIZE_enum {
	EBI_CS_ASIZE_256B_gc = (0x00<<2),	///< 256 bytes
	EBI_CS_ASIZE_512B_gc = (0x01<<2),	///< 512 bytes
	EBI_CS_ASIZE_1KB_gc = (0x02<<2),	///< 1K bytes
	EBI_CS_ASIZE_2KB_gc = (0x03<<2),	///< 2K bytes
	EBI_CS_ASIZE_4KB_gc = (0x04<<2),	///< 4K bytes
	EBI_CS_ASIZE_8KB_gc = (0x05<<2),	///< 8K bytes
	EBI_CS_ASIZE_16KB_gc = (0x06<<2),	///< 16K bytes
	EBI_CS_ASIZE_32KB_gc = (0x07<<2),	///< 32K bytes
	EBI_CS_ASIZE_64KB_gc = (0x08<<2),	///< 64K bytes
	EBI_CS_ASIZE_128KB_gc = (0x09<<2),	///< 128K bytes
	EBI_CS_ASIZE_256KB_gc = (0x0A<<2),	///< 256K bytes
	EBI_CS_ASIZE_512KB_gc = (0x0B<<2),	///< 512K bytes
	EBI_CS_ASIZE_1MB_gc = (0x0C<<2),	///< 1M bytes
	EBI_CS_ASIZE_2MB_gc = (0x0D<<2),	///< 2M bytes
	EBI_CS_ASIZE_4MB_gc = (0x0E<<2),	///< 4M bytes
	EBI_CS_ASIZE_8MB_gc = (0x0F<<2),	///< 8M bytes
	EBI_CS_ASIZE_16M_gc = (0x10<<2),	///< 16M bytes
} EBI_CS_ASIZE_t;
	
/// -- no doc!

typedef enum EBI_CS_SRWS_enum {
	EBI_CS_SRWS_0CLK_gc = (0x00<<0),	///< 0 cycles
	EBI_CS_SRWS_1CLK_gc = (0x01<<0),	///< 1 cycle
	EBI_CS_SRWS_2CLK_gc = (0x02<<0),	///< 2 cycles
	EBI_CS_SRWS_3CLK_gc = (0x03<<0),	///< 3 cycles
	EBI_CS_SRWS_4CLK_gc = (0x04<<0),	///< 4 cycles
	EBI_CS_SRWS_5CLK_gc = (0x05<<0),	///< 5 cycle
	EBI_CS_SRWS_6CLK_gc = (0x06<<0),	///< 6 cycles
	EBI_CS_SRWS_7CLK_gc = (0x07<<0),	///< 7 cycles
} EBI_CS_SRWS_t;
	
/// Chip Select address mode

typedef enum EBI_CS_MODE_enum {
	EBI_CS_MODE_DISABLED_gc = (0x00<<0),	///< Chip Select Disabled
	EBI_CS_MODE_SRAM_gc = (0x01<<0),	///< Chip Select in SRAM mode
	EBI_CS_MODE_LPC_gc = (0x02<<0),	///< Chip Select in SRAM LPC mode
	EBI_CS_MODE_SDRAM_gc = (0x03<<0),	///< Chip Select in SDRAM mode
} EBI_CS_MODE_t;
	
/// Chip Select SDRAM mode

typedef enum EBI_CS_SDMODE_enum {
	EBI_CS_SDMODE_NORMAL_gc = (0x00<<0),	///< Normal mode
	EBI_CS_SDMODE_LOAD_gc = (0x01<<0),	///< Load Mode Register command mode
} EBI_CS_SDMODE_t;
	
/// -- no doc!

typedef enum EBI_SDDATAW_enum {
	EBI_SDDATAW_4BIT_gc = (0x00<<6),	///< 4-bit data bus
	EBI_SDDATAW_8BIT_gc = (0x01<<6),	///< 8-bit data bus
} EBI_SDDATAW_t;
	
/// -- no doc!

typedef enum EBI_LPCMODE_enum {
	EBI_LPCMODE_ALE1_gc = (0x00<<4),	///< Data muxed with addr byte 0
	EBI_LPCMODE_ALE12_gc = (0x02<<4),	///< Data muxed with addr byte 0 and 1
} EBI_LPCMODE_t;
	
/// -- no doc!

typedef enum EBI_SRMODE_enum {
	EBI_SRMODE_ALE1_gc = (0x00<<2),	///< Addr byte 0 muxed with 1
	EBI_SRMODE_ALE2_gc = (0x01<<2),	///< Addr byte 0 muxed with 2
	EBI_SRMODE_ALE12_gc = (0x02<<2),	///< Addr byte 0 muxed with 1 and 2
	EBI_SRMODE_NOALE_gc = (0x03<<2),	///< No addr muxing
} EBI_SRMODE_t;
	
/// -- no doc!

typedef enum EBI_IFMODE_enum {
	EBI_IFMODE_DISABLED_gc = (0x00<<0),	///< EBI Disabled
	EBI_IFMODE_3PORT_gc = (0x01<<0),	///< 3-port mode
	EBI_IFMODE_4PORT_gc = (0x02<<0),	///< 4-port mode
	EBI_IFMODE_2PORT_gc = (0x03<<0),	///< 2-port mode
} EBI_IFMODE_t;
	
/// -- no doc!

typedef enum EBI_SDCOL_enum {
	EBI_SDCOL_8BIT_gc = (0x00<<0),	///< 8 column bits
	EBI_SDCOL_9BIT_gc = (0x01<<0),	///< 9 column bits
	EBI_SDCOL_10BIT_gc = (0x02<<0),	///< 10 column bits
	EBI_SDCOL_11BIT_gc = (0x03<<0),	///< 11 column bits
} EBI_SDCOL_t;
	
/// -- no doc!

typedef enum EBI_MRDLY_enum {
	EBI_MRDLY_0CLK_gc = (0x00<<6),	///< 0 cycles
	EBI_MRDLY_1CLK_gc = (0x01<<6),	///< 1 cycle
	EBI_MRDLY_2CLK_gc = (0x02<<6),	///< 2 cycles
	EBI_MRDLY_3CLK_gc = (0x03<<6),	///< 3 cycles
} EBI_MRDLY_t;
	
/// -- no doc!

typedef enum EBI_ROWCYCDLY_enum {
	EBI_ROWCYCDLY_0CLK_gc = (0x00<<3),	///< 0 cycles
	EBI_ROWCYCDLY_1CLK_gc = (0x01<<3),	///< 1 cycle
	EBI_ROWCYCDLY_2CLK_gc = (0x02<<3),	///< 2 cycles
	EBI_ROWCYCDLY_3CLK_gc = (0x03<<3),	///< 3 cycles
	EBI_ROWCYCDLY_4CLK_gc = (0x04<<3),	///< 4 cycles
	EBI_ROWCYCDLY_5CLK_gc = (0x05<<3),	///< 5 cycle
	EBI_ROWCYCDLY_6CLK_gc = (0x06<<3),	///< 6 cycles
	EBI_ROWCYCDLY_7CLK_gc = (0x07<<3),	///< 7 cycles
} EBI_ROWCYCDLY_t;
	
/// -- no doc!

typedef enum EBI_RPDLY_enum {
	EBI_RPDLY_0CLK_gc = (0x00<<0),	///< 0 cycles
	EBI_RPDLY_1CLK_gc = (0x01<<0),	///< 1 cycle
	EBI_RPDLY_2CLK_gc = (0x02<<0),	///< 2 cycles
	EBI_RPDLY_3CLK_gc = (0x03<<0),	///< 3 cycles
	EBI_RPDLY_4CLK_gc = (0x04<<0),	///< 4 cycles
	EBI_RPDLY_5CLK_gc = (0x05<<0),	///< 5 cycle
	EBI_RPDLY_6CLK_gc = (0x06<<0),	///< 6 cycles
	EBI_RPDLY_7CLK_gc = (0x07<<0),	///< 7 cycles
} EBI_RPDLY_t;
	
/// -- no doc!

typedef enum EBI_WRDLY_enum {
	EBI_WRDLY_0CLK_gc = (0x00<<6),	///< 0 cycles
	EBI_WRDLY_1CLK_gc = (0x01<<6),	///< 1 cycle
	EBI_WRDLY_2CLK_gc = (0x02<<6),	///< 2 cycles
	EBI_WRDLY_3CLK_gc = (0x03<<6),	///< 3 cycles
} EBI_WRDLY_t;
	
/// -- no doc!

typedef enum EBI_ESRDLY_enum {
	EBI_ESRDLY_0CLK_gc = (0x00<<3),	///< 0 cycles
	EBI_ESRDLY_1CLK_gc = (0x01<<3),	///< 1 cycle
	EBI_ESRDLY_2CLK_gc = (0x02<<3),	///< 2 cycles
	EBI_ESRDLY_3CLK_gc = (0x03<<3),	///< 3 cycles
	EBI_ESRDLY_4CLK_gc = (0x04<<3),	///< 4 cycles
	EBI_ESRDLY_5CLK_gc = (0x05<<3),	///< 5 cycle
	EBI_ESRDLY_6CLK_gc = (0x06<<3),	///< 6 cycles
	EBI_ESRDLY_7CLK_gc = (0x07<<3),	///< 7 cycles
} EBI_ESRDLY_t;
	
/// -- no doc!

typedef enum EBI_ROWCOLDLY_enum {
	EBI_ROWCOLDLY_0CLK_gc = (0x00<<0),	///< 0 cycles
	EBI_ROWCOLDLY_1CLK_gc = (0x01<<0),	///< 1 cycle
	EBI_ROWCOLDLY_2CLK_gc = (0x02<<0),	///< 2 cycles
	EBI_ROWCOLDLY_3CLK_gc = (0x03<<0),	///< 3 cycles
	EBI_ROWCOLDLY_4CLK_gc = (0x04<<0),	///< 4 cycles
	EBI_ROWCOLDLY_5CLK_gc = (0x05<<0),	///< 5 cycle
	EBI_ROWCOLDLY_6CLK_gc = (0x06<<0),	///< 6 cycles
	EBI_ROWCOLDLY_7CLK_gc = (0x07<<0),	///< 7 cycles
} EBI_ROWCOLDLY_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Chip Select adress space
#define EBI_CS_ASIZE_256B_gc (0x00<<2)	///< 256 bytes
#define EBI_CS_ASIZE_512B_gc (0x01<<2)	///< 512 bytes
#define EBI_CS_ASIZE_1KB_gc (0x02<<2)	///< 1K bytes
#define EBI_CS_ASIZE_2KB_gc (0x03<<2)	///< 2K bytes
#define EBI_CS_ASIZE_4KB_gc (0x04<<2)	///< 4K bytes
#define EBI_CS_ASIZE_8KB_gc (0x05<<2)	///< 8K bytes
#define EBI_CS_ASIZE_16KB_gc (0x06<<2)	///< 16K bytes
#define EBI_CS_ASIZE_32KB_gc (0x07<<2)	///< 32K bytes
#define EBI_CS_ASIZE_64KB_gc (0x08<<2)	///< 64K bytes
#define EBI_CS_ASIZE_128KB_gc (0x09<<2)	///< 128K bytes
#define EBI_CS_ASIZE_256KB_gc (0x0A<<2)	///< 256K bytes
#define EBI_CS_ASIZE_512KB_gc (0x0B<<2)	///< 512K bytes
#define EBI_CS_ASIZE_1MB_gc (0x0C<<2)	///< 1M bytes
#define EBI_CS_ASIZE_2MB_gc (0x0D<<2)	///< 2M bytes
#define EBI_CS_ASIZE_4MB_gc (0x0E<<2)	///< 4M bytes
#define EBI_CS_ASIZE_8MB_gc (0x0F<<2)	///< 8M bytes
#define EBI_CS_ASIZE_16M_gc (0x10<<2)	///< 16M bytes

/// 
#define EBI_CS_SRWS_0CLK_gc (0x00<<0)	///< 0 cycles
#define EBI_CS_SRWS_1CLK_gc (0x01<<0)	///< 1 cycle
#define EBI_CS_SRWS_2CLK_gc (0x02<<0)	///< 2 cycles
#define EBI_CS_SRWS_3CLK_gc (0x03<<0)	///< 3 cycles
#define EBI_CS_SRWS_4CLK_gc (0x04<<0)	///< 4 cycles
#define EBI_CS_SRWS_5CLK_gc (0x05<<0)	///< 5 cycle
#define EBI_CS_SRWS_6CLK_gc (0x06<<0)	///< 6 cycles
#define EBI_CS_SRWS_7CLK_gc (0x07<<0)	///< 7 cycles

/// Chip Select address mode
#define EBI_CS_MODE_DISABLED_gc (0x00<<0)	///< Chip Select Disabled
#define EBI_CS_MODE_SRAM_gc (0x01<<0)	///< Chip Select in SRAM mode
#define EBI_CS_MODE_LPC_gc (0x02<<0)	///< Chip Select in SRAM LPC mode
#define EBI_CS_MODE_SDRAM_gc (0x03<<0)	///< Chip Select in SDRAM mode

/// Chip Select SDRAM mode
#define EBI_CS_SDMODE_NORMAL_gc (0x00<<0)	///< Normal mode
#define EBI_CS_SDMODE_LOAD_gc (0x01<<0)	///< Load Mode Register command mode

/// 
#define EBI_SDDATAW_4BIT_gc (0x00<<6)	///< 4-bit data bus
#define EBI_SDDATAW_8BIT_gc (0x01<<6)	///< 8-bit data bus

/// 
#define EBI_LPCMODE_ALE1_gc (0x00<<4)	///< Data muxed with addr byte 0
#define EBI_LPCMODE_ALE12_gc (0x02<<4)	///< Data muxed with addr byte 0 and 1

/// 
#define EBI_SRMODE_ALE1_gc (0x00<<2)	///< Addr byte 0 muxed with 1
#define EBI_SRMODE_ALE2_gc (0x01<<2)	///< Addr byte 0 muxed with 2
#define EBI_SRMODE_ALE12_gc (0x02<<2)	///< Addr byte 0 muxed with 1 and 2
#define EBI_SRMODE_NOALE_gc (0x03<<2)	///< No addr muxing

/// 
#define EBI_IFMODE_DISABLED_gc (0x00<<0)	///< EBI Disabled
#define EBI_IFMODE_3PORT_gc (0x01<<0)	///< 3-port mode
#define EBI_IFMODE_4PORT_gc (0x02<<0)	///< 4-port mode
#define EBI_IFMODE_2PORT_gc (0x03<<0)	///< 2-port mode

/// 
#define EBI_SDCOL_8BIT_gc (0x00<<0)	///< 8 column bits
#define EBI_SDCOL_9BIT_gc (0x01<<0)	///< 9 column bits
#define EBI_SDCOL_10BIT_gc (0x02<<0)	///< 10 column bits
#define EBI_SDCOL_11BIT_gc (0x03<<0)	///< 11 column bits

/// 
#define EBI_MRDLY_0CLK_gc (0x00<<6)	///< 0 cycles
#define EBI_MRDLY_1CLK_gc (0x01<<6)	///< 1 cycle
#define EBI_MRDLY_2CLK_gc (0x02<<6)	///< 2 cycles
#define EBI_MRDLY_3CLK_gc (0x03<<6)	///< 3 cycles

/// 
#define EBI_ROWCYCDLY_0CLK_gc (0x00<<3)	///< 0 cycles
#define EBI_ROWCYCDLY_1CLK_gc (0x01<<3)	///< 1 cycle
#define EBI_ROWCYCDLY_2CLK_gc (0x02<<3)	///< 2 cycles
#define EBI_ROWCYCDLY_3CLK_gc (0x03<<3)	///< 3 cycles
#define EBI_ROWCYCDLY_4CLK_gc (0x04<<3)	///< 4 cycles
#define EBI_ROWCYCDLY_5CLK_gc (0x05<<3)	///< 5 cycle
#define EBI_ROWCYCDLY_6CLK_gc (0x06<<3)	///< 6 cycles
#define EBI_ROWCYCDLY_7CLK_gc (0x07<<3)	///< 7 cycles

/// 
#define EBI_RPDLY_0CLK_gc (0x00<<0)	///< 0 cycles
#define EBI_RPDLY_1CLK_gc (0x01<<0)	///< 1 cycle
#define EBI_RPDLY_2CLK_gc (0x02<<0)	///< 2 cycles
#define EBI_RPDLY_3CLK_gc (0x03<<0)	///< 3 cycles
#define EBI_RPDLY_4CLK_gc (0x04<<0)	///< 4 cycles
#define EBI_RPDLY_5CLK_gc (0x05<<0)	///< 5 cycle
#define EBI_RPDLY_6CLK_gc (0x06<<0)	///< 6 cycles
#define EBI_RPDLY_7CLK_gc (0x07<<0)	///< 7 cycles

/// 
#define EBI_WRDLY_0CLK_gc (0x00<<6)	///< 0 cycles
#define EBI_WRDLY_1CLK_gc (0x01<<6)	///< 1 cycle
#define EBI_WRDLY_2CLK_gc (0x02<<6)	///< 2 cycles
#define EBI_WRDLY_3CLK_gc (0x03<<6)	///< 3 cycles

/// 
#define EBI_ESRDLY_0CLK_gc (0x00<<3)	///< 0 cycles
#define EBI_ESRDLY_1CLK_gc (0x01<<3)	///< 1 cycle
#define EBI_ESRDLY_2CLK_gc (0x02<<3)	///< 2 cycles
#define EBI_ESRDLY_3CLK_gc (0x03<<3)	///< 3 cycles
#define EBI_ESRDLY_4CLK_gc (0x04<<3)	///< 4 cycles
#define EBI_ESRDLY_5CLK_gc (0x05<<3)	///< 5 cycle
#define EBI_ESRDLY_6CLK_gc (0x06<<3)	///< 6 cycles
#define EBI_ESRDLY_7CLK_gc (0x07<<3)	///< 7 cycles

/// 
#define EBI_ROWCOLDLY_0CLK_gc (0x00<<0)	///< 0 cycles
#define EBI_ROWCOLDLY_1CLK_gc (0x01<<0)	///< 1 cycle
#define EBI_ROWCOLDLY_2CLK_gc (0x02<<0)	///< 2 cycles
#define EBI_ROWCOLDLY_3CLK_gc (0x03<<0)	///< 3 cycles
#define EBI_ROWCOLDLY_4CLK_gc (0x04<<0)	///< 4 cycles
#define EBI_ROWCOLDLY_5CLK_gc (0x05<<0)	///< 5 cycle
#define EBI_ROWCOLDLY_6CLK_gc (0x06<<0)	///< 6 cycles
#define EBI_ROWCOLDLY_7CLK_gc (0x07<<0)	///< 7 cycles

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup twi Two-Wire Interface
 *  @{
 */
	
/** @name TWI_MASTER.CTRLA
  * @see TWI_MASTER_INTLVL_enum
  * @{
  */
#define TWI_MASTER_INTLVL_gm 0xC0 ///< Interrupt Level group mask
#define TWI_MASTER_INTLVL_gp 6 ///< Interrupt Level group position
#define TWI_MASTER_INTLVL0_bm (1<<6) ///< Interrupt Level bit 0 mask
#define TWI_MASTER_INTLVL0_bp 6 ///< Interrupt Level bit 0 position
#define TWI_MASTER_INTLVL1_bm (1<<7) ///< Interrupt Level bit 1 mask
#define TWI_MASTER_INTLVL1_bp 7 ///< Interrupt Level bit 1 position
#define TWI_MASTER_RIEN_bm 0x20 ///< Read Interrupt Enable bit mask
#define TWI_MASTER_RIEN_bp 5 ///< Read Interrupt Enable bit position
#define TWI_MASTER_WIEN_bm 0x10 ///< Write Interrupt Enable bit mask
#define TWI_MASTER_WIEN_bp 4 ///< Write Interrupt Enable bit position
#define TWI_MASTER_ENABLE_bm 0x08 ///< Enable TWI Master bit mask
#define TWI_MASTER_ENABLE_bp 3 ///< Enable TWI Master bit position
/** @} */
	
/** @name TWI_MASTER.CTRLB
  * @see TWI_MASTER_TIMEOUT_enum
  * @{
  */
#define TWI_MASTER_TIMEOUT_gm 0x0C ///< Inactive Bus Timeout group mask
#define TWI_MASTER_TIMEOUT_gp 2 ///< Inactive Bus Timeout group position
#define TWI_MASTER_TIMEOUT0_bm (1<<2) ///< Inactive Bus Timeout bit 0 mask
#define TWI_MASTER_TIMEOUT0_bp 2 ///< Inactive Bus Timeout bit 0 position
#define TWI_MASTER_TIMEOUT1_bm (1<<3) ///< Inactive Bus Timeout bit 1 mask
#define TWI_MASTER_TIMEOUT1_bp 3 ///< Inactive Bus Timeout bit 1 position
#define TWI_MASTER_QCEN_bm 0x02 ///< Quick Command Enable bit mask
#define TWI_MASTER_QCEN_bp 1 ///< Quick Command Enable bit position
#define TWI_MASTER_SMEN_bm 0x01 ///< Smart Mode Enable bit mask
#define TWI_MASTER_SMEN_bp 0 ///< Smart Mode Enable bit position
/** @} */
	
/** @name TWI_MASTER.CTRLC
  * @see TWI_MASTER_CMD_enum
  * @{
  */
#define TWI_MASTER_ACKACT_bm 0x04 ///< Acknowledge Action bit mask
#define TWI_MASTER_ACKACT_bp 2 ///< Acknowledge Action bit position
#define TWI_MASTER_CMD_gm 0x03 ///< Command group mask
#define TWI_MASTER_CMD_gp 0 ///< Command group position
#define TWI_MASTER_CMD0_bm (1<<0) ///< Command bit 0 mask
#define TWI_MASTER_CMD0_bp 0 ///< Command bit 0 position
#define TWI_MASTER_CMD1_bm (1<<1) ///< Command bit 1 mask
#define TWI_MASTER_CMD1_bp 1 ///< Command bit 1 position
/** @} */
	
/** @name TWI_MASTER.STATUS
  * @see TWI_MASTER_BUSSTATE_enum
  * @{
  */
#define TWI_MASTER_RIF_bm 0x80 ///< Read Interrupt Flag bit mask
#define TWI_MASTER_RIF_bp 7 ///< Read Interrupt Flag bit position
#define TWI_MASTER_WIF_bm 0x40 ///< Write Interrupt Flag bit mask
#define TWI_MASTER_WIF_bp 6 ///< Write Interrupt Flag bit position
#define TWI_MASTER_CLKHOLD_bm 0x20 ///< Clock Hold bit mask
#define TWI_MASTER_CLKHOLD_bp 5 ///< Clock Hold bit position
#define TWI_MASTER_RXACK_bm 0x10 ///< Received Acknowledge bit mask
#define TWI_MASTER_RXACK_bp 4 ///< Received Acknowledge bit position
#define TWI_MASTER_ARBLOST_bm 0x08 ///< Arbitration Lost bit mask
#define TWI_MASTER_ARBLOST_bp 3 ///< Arbitration Lost bit position
#define TWI_MASTER_BUSERR_bm 0x04 ///< Bus Error bit mask
#define TWI_MASTER_BUSERR_bp 2 ///< Bus Error bit position
#define TWI_MASTER_BUSSTATE_gm 0x03 ///< Bus State group mask
#define TWI_MASTER_BUSSTATE_gp 0 ///< Bus State group position
#define TWI_MASTER_BUSSTATE0_bm (1<<0) ///< Bus State bit 0 mask
#define TWI_MASTER_BUSSTATE0_bp 0 ///< Bus State bit 0 position
#define TWI_MASTER_BUSSTATE1_bm (1<<1) ///< Bus State bit 1 mask
#define TWI_MASTER_BUSSTATE1_bp 1 ///< Bus State bit 1 position
/** @} */
	
/** @name TWI_SLAVE.CTRLA
  * @see TWI_SLAVE_INTLVL_enum
  * @{
  */
#define TWI_SLAVE_INTLVL_gm 0xC0 ///< Interrupt Level group mask
#define TWI_SLAVE_INTLVL_gp 6 ///< Interrupt Level group position
#define TWI_SLAVE_INTLVL0_bm (1<<6) ///< Interrupt Level bit 0 mask
#define TWI_SLAVE_INTLVL0_bp 6 ///< Interrupt Level bit 0 position
#define TWI_SLAVE_INTLVL1_bm (1<<7) ///< Interrupt Level bit 1 mask
#define TWI_SLAVE_INTLVL1_bp 7 ///< Interrupt Level bit 1 position
#define TWI_SLAVE_DIEN_bm 0x20 ///< Data Interrupt Enable bit mask
#define TWI_SLAVE_DIEN_bp 5 ///< Data Interrupt Enable bit position
#define TWI_SLAVE_APIEN_bm 0x10 ///< Address/Stop Interrupt Enable bit mask
#define TWI_SLAVE_APIEN_bp 4 ///< Address/Stop Interrupt Enable bit position
#define TWI_SLAVE_ENABLE_bm 0x08 ///< Enable TWI Slave bit mask
#define TWI_SLAVE_ENABLE_bp 3 ///< Enable TWI Slave bit position
#define TWI_SLAVE_PIEN_bm 0x04 ///< Stop Interrupt Enable bit mask
#define TWI_SLAVE_PIEN_bp 2 ///< Stop Interrupt Enable bit position
#define TWI_SLAVE_PMEN_bm 0x02 ///< Promiscuous Mode Enable bit mask
#define TWI_SLAVE_PMEN_bp 1 ///< Promiscuous Mode Enable bit position
#define TWI_SLAVE_SMEN_bm 0x01 ///< Smart Mode Enable bit mask
#define TWI_SLAVE_SMEN_bp 0 ///< Smart Mode Enable bit position
/** @} */
	
/** @name TWI_SLAVE.CTRLB
  * @see TWI_SLAVE_CMD_enum
  * @{
  */
#define TWI_SLAVE_ACKACT_bm 0x04 ///< Acknowledge Action bit mask
#define TWI_SLAVE_ACKACT_bp 2 ///< Acknowledge Action bit position
#define TWI_SLAVE_CMD_gm 0x03 ///< Command group mask
#define TWI_SLAVE_CMD_gp 0 ///< Command group position
#define TWI_SLAVE_CMD0_bm (1<<0) ///< Command bit 0 mask
#define TWI_SLAVE_CMD0_bp 0 ///< Command bit 0 position
#define TWI_SLAVE_CMD1_bm (1<<1) ///< Command bit 1 mask
#define TWI_SLAVE_CMD1_bp 1 ///< Command bit 1 position
/** @} */
	
/** @name TWI_SLAVE.STATUS
  * @{
  */
#define TWI_SLAVE_DIF_bm 0x80 ///< Data Interrupt Flag bit mask
#define TWI_SLAVE_DIF_bp 7 ///< Data Interrupt Flag bit position
#define TWI_SLAVE_APIF_bm 0x40 ///< Address/Stop Interrupt Flag bit mask
#define TWI_SLAVE_APIF_bp 6 ///< Address/Stop Interrupt Flag bit position
#define TWI_SLAVE_CLKHOLD_bm 0x20 ///< Clock Hold bit mask
#define TWI_SLAVE_CLKHOLD_bp 5 ///< Clock Hold bit position
#define TWI_SLAVE_RXACK_bm 0x10 ///< Received Acknowledge bit mask
#define TWI_SLAVE_RXACK_bp 4 ///< Received Acknowledge bit position
#define TWI_SLAVE_COLL_bm 0x08 ///< Collision bit mask
#define TWI_SLAVE_COLL_bp 3 ///< Collision bit position
#define TWI_SLAVE_BUSERR_bm 0x04 ///< Bus Error bit mask
#define TWI_SLAVE_BUSERR_bp 2 ///< Bus Error bit position
#define TWI_SLAVE_DIR_bm 0x02 ///< Read/Write Direction bit mask
#define TWI_SLAVE_DIR_bp 1 ///< Read/Write Direction bit position
#define TWI_SLAVE_AP_bm 0x01 ///< Slave Address or Stop bit mask
#define TWI_SLAVE_AP_bp 0 ///< Slave Address or Stop bit position
/** @} */
	
/** @name TWI_SLAVE.ADDRMASK
  * @{
  */
#define TWI_SLAVE_ADDRMASK_gm 0xFE ///< Address Mask group mask
#define TWI_SLAVE_ADDRMASK_gp 1 ///< Address Mask group position
#define TWI_SLAVE_ADDRMASK0_bm (1<<1) ///< Address Mask bit 0 mask
#define TWI_SLAVE_ADDRMASK0_bp 1 ///< Address Mask bit 0 position
#define TWI_SLAVE_ADDRMASK1_bm (1<<2) ///< Address Mask bit 1 mask
#define TWI_SLAVE_ADDRMASK1_bp 2 ///< Address Mask bit 1 position
#define TWI_SLAVE_ADDRMASK2_bm (1<<3) ///< Address Mask bit 2 mask
#define TWI_SLAVE_ADDRMASK2_bp 3 ///< Address Mask bit 2 position
#define TWI_SLAVE_ADDRMASK3_bm (1<<4) ///< Address Mask bit 3 mask
#define TWI_SLAVE_ADDRMASK3_bp 4 ///< Address Mask bit 3 position
#define TWI_SLAVE_ADDRMASK4_bm (1<<5) ///< Address Mask bit 4 mask
#define TWI_SLAVE_ADDRMASK4_bp 5 ///< Address Mask bit 4 position
#define TWI_SLAVE_ADDRMASK5_bm (1<<6) ///< Address Mask bit 5 mask
#define TWI_SLAVE_ADDRMASK5_bp 6 ///< Address Mask bit 5 position
#define TWI_SLAVE_ADDRMASK6_bm (1<<7) ///< Address Mask bit 6 mask
#define TWI_SLAVE_ADDRMASK6_bp 7 ///< Address Mask bit 6 position
#define TWI_SLAVE_ADDREN_bm 0x01 ///< Address Enable bit mask
#define TWI_SLAVE_ADDREN_bp 0 ///< Address Enable bit position
/** @} */
	
/** @name TWI.CTRL
  * @{
  */
#define TWI_SDAHOLD_bm 0x02 ///< SDA Hold Time Enable bit mask
#define TWI_SDAHOLD_bp 1 ///< SDA Hold Time Enable bit position
#define TWI_EDIEN_bm 0x01 ///< External Driver Interface Enable bit mask
#define TWI_EDIEN_bp 0 ///< External Driver Interface Enable bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Master Interrupt Level

typedef enum TWI_MASTER_INTLVL_enum {
	TWI_MASTER_INTLVL_OFF_gc = (0x00<<6),	///< Interrupt Disabled
	TWI_MASTER_INTLVL_LO_gc = (0x01<<6),	///< Low Level
	TWI_MASTER_INTLVL_MED_gc = (0x02<<6),	///< Medium Level
	TWI_MASTER_INTLVL_HI_gc = (0x03<<6),	///< High Level
} TWI_MASTER_INTLVL_t;
	
/// Inactive Timeout

typedef enum TWI_MASTER_TIMEOUT_enum {
	TWI_MASTER_TIMEOUT_DISABLED_gc = (0x00<<2),	///< Bus Timeout Disabled
	TWI_MASTER_TIMEOUT_50US_gc = (0x01<<2),	///< 50 Microseconds
	TWI_MASTER_TIMEOUT_100US_gc = (0x02<<2),	///< 100 Microseconds
	TWI_MASTER_TIMEOUT_200US_gc = (0x03<<2),	///< 200 Microseconds
} TWI_MASTER_TIMEOUT_t;
	
/// Master Command

typedef enum TWI_MASTER_CMD_enum {
	TWI_MASTER_CMD_NOACT_gc = (0x00<<0),	///< No Action
	TWI_MASTER_CMD_REPSTART_gc = (0x01<<0),	///< Issue Repeated Start Condition
	TWI_MASTER_CMD_RECVTRANS_gc = (0x02<<0),	///< Receive or Transmit Data
	TWI_MASTER_CMD_STOP_gc = (0x03<<0),	///< Issue Stop Condition
} TWI_MASTER_CMD_t;
	
/// Master Bus State

typedef enum TWI_MASTER_BUSSTATE_enum {
	TWI_MASTER_BUSSTATE_UNKNOWN_gc = (0x00<<0),	///< Unknown Bus State
	TWI_MASTER_BUSSTATE_IDLE_gc = (0x01<<0),	///< Bus is Idle
	TWI_MASTER_BUSSTATE_OWNER_gc = (0x02<<0),	///< This Module Controls The Bus
	TWI_MASTER_BUSSTATE_BUSY_gc = (0x03<<0),	///< The Bus is Busy
} TWI_MASTER_BUSSTATE_t;
	
/// Slave Interrupt Level

typedef enum TWI_SLAVE_INTLVL_enum {
	TWI_SLAVE_INTLVL_OFF_gc = (0x00<<6),	///< Interrupt Disabled
	TWI_SLAVE_INTLVL_LO_gc = (0x01<<6),	///< Low Level
	TWI_SLAVE_INTLVL_MED_gc = (0x02<<6),	///< Medium Level
	TWI_SLAVE_INTLVL_HI_gc = (0x03<<6),	///< High Level
} TWI_SLAVE_INTLVL_t;
	
/// Slave Command

typedef enum TWI_SLAVE_CMD_enum {
	TWI_SLAVE_CMD_NOACT_gc = (0x00<<0),	///< No Action
	TWI_SLAVE_CMD_COMPTRANS_gc = (0x02<<0),	///< Used To Complete a Transaction
	TWI_SLAVE_CMD_RESPONSE_gc = (0x03<<0),	///< Used in Response to Address/Data Interrupt
} TWI_SLAVE_CMD_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Master Interrupt Level
#define TWI_MASTER_INTLVL_OFF_gc (0x00<<6)	///< Interrupt Disabled
#define TWI_MASTER_INTLVL_LO_gc (0x01<<6)	///< Low Level
#define TWI_MASTER_INTLVL_MED_gc (0x02<<6)	///< Medium Level
#define TWI_MASTER_INTLVL_HI_gc (0x03<<6)	///< High Level

/// Inactive Timeout
#define TWI_MASTER_TIMEOUT_DISABLED_gc (0x00<<2)	///< Bus Timeout Disabled
#define TWI_MASTER_TIMEOUT_50US_gc (0x01<<2)	///< 50 Microseconds
#define TWI_MASTER_TIMEOUT_100US_gc (0x02<<2)	///< 100 Microseconds
#define TWI_MASTER_TIMEOUT_200US_gc (0x03<<2)	///< 200 Microseconds

/// Master Command
#define TWI_MASTER_CMD_NOACT_gc (0x00<<0)	///< No Action
#define TWI_MASTER_CMD_REPSTART_gc (0x01<<0)	///< Issue Repeated Start Condition
#define TWI_MASTER_CMD_RECVTRANS_gc (0x02<<0)	///< Receive or Transmit Data
#define TWI_MASTER_CMD_STOP_gc (0x03<<0)	///< Issue Stop Condition

/// Master Bus State
#define TWI_MASTER_BUSSTATE_UNKNOWN_gc (0x00<<0)	///< Unknown Bus State
#define TWI_MASTER_BUSSTATE_IDLE_gc (0x01<<0)	///< Bus is Idle
#define TWI_MASTER_BUSSTATE_OWNER_gc (0x02<<0)	///< This Module Controls The Bus
#define TWI_MASTER_BUSSTATE_BUSY_gc (0x03<<0)	///< The Bus is Busy

/// Slave Interrupt Level
#define TWI_SLAVE_INTLVL_OFF_gc (0x00<<6)	///< Interrupt Disabled
#define TWI_SLAVE_INTLVL_LO_gc (0x01<<6)	///< Low Level
#define TWI_SLAVE_INTLVL_MED_gc (0x02<<6)	///< Medium Level
#define TWI_SLAVE_INTLVL_HI_gc (0x03<<6)	///< High Level

/// Slave Command
#define TWI_SLAVE_CMD_NOACT_gc (0x00<<0)	///< No Action
#define TWI_SLAVE_CMD_COMPTRANS_gc (0x02<<0)	///< Used To Complete a Transaction
#define TWI_SLAVE_CMD_RESPONSE_gc (0x03<<0)	///< Used in Response to Address/Data Interrupt

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup port Port Configuration
 *  @{
 */
	
/** @name PORTCFG.VPCTRLA
  * @see PORTCFG_VP1MAP_enum
  * @see PORTCFG_VP0MAP_enum
  * @{
  */
#define PORTCFG_VP1MAP_gm 0xF0 ///< Virtual Port 1 Mapping group mask
#define PORTCFG_VP1MAP_gp 4 ///< Virtual Port 1 Mapping group position
#define PORTCFG_VP1MAP0_bm (1<<4) ///< Virtual Port 1 Mapping bit 0 mask
#define PORTCFG_VP1MAP0_bp 4 ///< Virtual Port 1 Mapping bit 0 position
#define PORTCFG_VP1MAP1_bm (1<<5) ///< Virtual Port 1 Mapping bit 1 mask
#define PORTCFG_VP1MAP1_bp 5 ///< Virtual Port 1 Mapping bit 1 position
#define PORTCFG_VP1MAP2_bm (1<<6) ///< Virtual Port 1 Mapping bit 2 mask
#define PORTCFG_VP1MAP2_bp 6 ///< Virtual Port 1 Mapping bit 2 position
#define PORTCFG_VP1MAP3_bm (1<<7) ///< Virtual Port 1 Mapping bit 3 mask
#define PORTCFG_VP1MAP3_bp 7 ///< Virtual Port 1 Mapping bit 3 position
#define PORTCFG_VP0MAP_gm 0x0F ///< Virtual Port 0 Mapping group mask
#define PORTCFG_VP0MAP_gp 0 ///< Virtual Port 0 Mapping group position
#define PORTCFG_VP0MAP0_bm (1<<0) ///< Virtual Port 0 Mapping bit 0 mask
#define PORTCFG_VP0MAP0_bp 0 ///< Virtual Port 0 Mapping bit 0 position
#define PORTCFG_VP0MAP1_bm (1<<1) ///< Virtual Port 0 Mapping bit 1 mask
#define PORTCFG_VP0MAP1_bp 1 ///< Virtual Port 0 Mapping bit 1 position
#define PORTCFG_VP0MAP2_bm (1<<2) ///< Virtual Port 0 Mapping bit 2 mask
#define PORTCFG_VP0MAP2_bp 2 ///< Virtual Port 0 Mapping bit 2 position
#define PORTCFG_VP0MAP3_bm (1<<3) ///< Virtual Port 0 Mapping bit 3 mask
#define PORTCFG_VP0MAP3_bp 3 ///< Virtual Port 0 Mapping bit 3 position
/** @} */
	
/** @name PORTCFG.VPCTRLB
  * @see PORTCFG_VP3MAP_enum
  * @see PORTCFG_VP2MAP_enum
  * @{
  */
#define PORTCFG_VP3MAP_gm 0xF0 ///< Virtual Port 3 Mapping group mask
#define PORTCFG_VP3MAP_gp 4 ///< Virtual Port 3 Mapping group position
#define PORTCFG_VP3MAP0_bm (1<<4) ///< Virtual Port 3 Mapping bit 0 mask
#define PORTCFG_VP3MAP0_bp 4 ///< Virtual Port 3 Mapping bit 0 position
#define PORTCFG_VP3MAP1_bm (1<<5) ///< Virtual Port 3 Mapping bit 1 mask
#define PORTCFG_VP3MAP1_bp 5 ///< Virtual Port 3 Mapping bit 1 position
#define PORTCFG_VP3MAP2_bm (1<<6) ///< Virtual Port 3 Mapping bit 2 mask
#define PORTCFG_VP3MAP2_bp 6 ///< Virtual Port 3 Mapping bit 2 position
#define PORTCFG_VP3MAP3_bm (1<<7) ///< Virtual Port 3 Mapping bit 3 mask
#define PORTCFG_VP3MAP3_bp 7 ///< Virtual Port 3 Mapping bit 3 position
#define PORTCFG_VP2MAP_gm 0x0F ///< Virtual Port 2 Mapping group mask
#define PORTCFG_VP2MAP_gp 0 ///< Virtual Port 2 Mapping group position
#define PORTCFG_VP2MAP0_bm (1<<0) ///< Virtual Port 2 Mapping bit 0 mask
#define PORTCFG_VP2MAP0_bp 0 ///< Virtual Port 2 Mapping bit 0 position
#define PORTCFG_VP2MAP1_bm (1<<1) ///< Virtual Port 2 Mapping bit 1 mask
#define PORTCFG_VP2MAP1_bp 1 ///< Virtual Port 2 Mapping bit 1 position
#define PORTCFG_VP2MAP2_bm (1<<2) ///< Virtual Port 2 Mapping bit 2 mask
#define PORTCFG_VP2MAP2_bp 2 ///< Virtual Port 2 Mapping bit 2 position
#define PORTCFG_VP2MAP3_bm (1<<3) ///< Virtual Port 2 Mapping bit 3 mask
#define PORTCFG_VP2MAP3_bp 3 ///< Virtual Port 2 Mapping bit 3 position
/** @} */
	
/** @name PORTCFG.CLKEVOUT
  * @see PORTCFG_CLKOUT_enum
  * @see PORTCFG_EVOUT_enum
  * @{
  */
#define PORTCFG_CLKOUT_gm 0x03 ///< Clock Output Port group mask
#define PORTCFG_CLKOUT_gp 0 ///< Clock Output Port group position
#define PORTCFG_CLKOUT0_bm (1<<0) ///< Clock Output Port bit 0 mask
#define PORTCFG_CLKOUT0_bp 0 ///< Clock Output Port bit 0 position
#define PORTCFG_CLKOUT1_bm (1<<1) ///< Clock Output Port bit 1 mask
#define PORTCFG_CLKOUT1_bp 1 ///< Clock Output Port bit 1 position
#define PORTCFG_EVOUT_gm 0x30 ///< Event Output Port group mask
#define PORTCFG_EVOUT_gp 4 ///< Event Output Port group position
#define PORTCFG_EVOUT0_bm (1<<4) ///< Event Output Port bit 0 mask
#define PORTCFG_EVOUT0_bp 4 ///< Event Output Port bit 0 position
#define PORTCFG_EVOUT1_bm (1<<5) ///< Event Output Port bit 1 mask
#define PORTCFG_EVOUT1_bp 5 ///< Event Output Port bit 1 position
/** @} */
	
/** @name VPORT.INTFLAGS
  * @{
  */
#define VPORT_INT1IF_bm 0x02 ///< Port Interrupt 1 Flag bit mask
#define VPORT_INT1IF_bp 1 ///< Port Interrupt 1 Flag bit position
#define VPORT_INT0IF_bm 0x01 ///< Port Interrupt 0 Flag bit mask
#define VPORT_INT0IF_bp 0 ///< Port Interrupt 0 Flag bit position
/** @} */
	
/** @name PORT.INTCTRL
  * @see PORT_INT1LVL_enum
  * @see PORT_INT0LVL_enum
  * @{
  */
#define PORT_INT1LVL_gm 0x0C ///< Port Interrupt 1 Level group mask
#define PORT_INT1LVL_gp 2 ///< Port Interrupt 1 Level group position
#define PORT_INT1LVL0_bm (1<<2) ///< Port Interrupt 1 Level bit 0 mask
#define PORT_INT1LVL0_bp 2 ///< Port Interrupt 1 Level bit 0 position
#define PORT_INT1LVL1_bm (1<<3) ///< Port Interrupt 1 Level bit 1 mask
#define PORT_INT1LVL1_bp 3 ///< Port Interrupt 1 Level bit 1 position
#define PORT_INT0LVL_gm 0x03 ///< Port Interrupt 0 Level group mask
#define PORT_INT0LVL_gp 0 ///< Port Interrupt 0 Level group position
#define PORT_INT0LVL0_bm (1<<0) ///< Port Interrupt 0 Level bit 0 mask
#define PORT_INT0LVL0_bp 0 ///< Port Interrupt 0 Level bit 0 position
#define PORT_INT0LVL1_bm (1<<1) ///< Port Interrupt 0 Level bit 1 mask
#define PORT_INT0LVL1_bp 1 ///< Port Interrupt 0 Level bit 1 position
/** @} */
	
/** @name PORT.INTFLAGS
  * @{
  */
#define PORT_INT1IF_bm 0x02 ///< Port Interrupt 1 Flag bit mask
#define PORT_INT1IF_bp 1 ///< Port Interrupt 1 Flag bit position
#define PORT_INT0IF_bm 0x01 ///< Port Interrupt 0 Flag bit mask
#define PORT_INT0IF_bp 0 ///< Port Interrupt 0 Flag bit position
/** @} */
	
/** @name PORT.PIN0CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
#define PORT_SRLEN_bm 0x80 ///< Slew Rate Enable bit mask
#define PORT_SRLEN_bp 7 ///< Slew Rate Enable bit position
#define PORT_INVEN_bm 0x40 ///< Inverted I/O Enable bit mask
#define PORT_INVEN_bp 6 ///< Inverted I/O Enable bit position
#define PORT_OPC_gm 0x38 ///< Output/Pull Configuration group mask
#define PORT_OPC_gp 3 ///< Output/Pull Configuration group position
#define PORT_OPC0_bm (1<<3) ///< Output/Pull Configuration bit 0 mask
#define PORT_OPC0_bp 3 ///< Output/Pull Configuration bit 0 position
#define PORT_OPC1_bm (1<<4) ///< Output/Pull Configuration bit 1 mask
#define PORT_OPC1_bp 4 ///< Output/Pull Configuration bit 1 position
#define PORT_OPC2_bm (1<<5) ///< Output/Pull Configuration bit 2 mask
#define PORT_OPC2_bp 5 ///< Output/Pull Configuration bit 2 position
#define PORT_ISC_gm 0x07 ///< Input/Sense Configuration group mask
#define PORT_ISC_gp 0 ///< Input/Sense Configuration group position
#define PORT_ISC0_bm (1<<0) ///< Input/Sense Configuration bit 0 mask
#define PORT_ISC0_bp 0 ///< Input/Sense Configuration bit 0 position
#define PORT_ISC1_bm (1<<1) ///< Input/Sense Configuration bit 1 mask
#define PORT_ISC1_bp 1 ///< Input/Sense Configuration bit 1 position
#define PORT_ISC2_bm (1<<2) ///< Input/Sense Configuration bit 2 mask
#define PORT_ISC2_bp 2 ///< Input/Sense Configuration bit 2 position
/** @} */
	
/** @name PORT.PIN1CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	
/** @name PORT.PIN2CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	
/** @name PORT.PIN3CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	
/** @name PORT.PIN4CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	
/** @name PORT.PIN5CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	
/** @name PORT.PIN6CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	
/** @name PORT.PIN7CTRL
  * @see PORT_OPC_enum
  * @see PORT_ISC_enum
  * @{
  */
// Masks for SRLEN aready defined
// Masks for INVEN aready defined
// Masks for OPC aready defined
// Masks for ISC aready defined
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Virtual Port 0 Mapping

typedef enum PORTCFG_VP0MAP_enum {
	PORTCFG_VP0MAP_PORTA_gc = (0x00<<0),	///< Mapped To PORTA
	PORTCFG_VP0MAP_PORTB_gc = (0x01<<0),	///< Mapped To PORTB
	PORTCFG_VP0MAP_PORTC_gc = (0x02<<0),	///< Mapped To PORTC
	PORTCFG_VP0MAP_PORTD_gc = (0x03<<0),	///< Mapped To PORTD
	PORTCFG_VP0MAP_PORTE_gc = (0x04<<0),	///< Mapped To PORTE
	PORTCFG_VP0MAP_PORTF_gc = (0x05<<0),	///< Mapped To PORTF
	PORTCFG_VP0MAP_PORTG_gc = (0x06<<0),	///< Mapped To PORTG
	PORTCFG_VP0MAP_PORTH_gc = (0x07<<0),	///< Mapped To PORTH
	PORTCFG_VP0MAP_PORTJ_gc = (0x08<<0),	///< Mapped To PORTJ
	PORTCFG_VP0MAP_PORTK_gc = (0x09<<0),	///< Mapped To PORTK
	PORTCFG_VP0MAP_PORTL_gc = (0x0A<<0),	///< Mapped To PORTL
	PORTCFG_VP0MAP_PORTM_gc = (0x0B<<0),	///< Mapped To PORTM
	PORTCFG_VP0MAP_PORTN_gc = (0x0C<<0),	///< Mapped To PORTN
	PORTCFG_VP0MAP_PORTP_gc = (0x0D<<0),	///< Mapped To PORTP
	PORTCFG_VP0MAP_PORTQ_gc = (0x0E<<0),	///< Mapped To PORTQ
	PORTCFG_VP0MAP_PORTR_gc = (0x0F<<0),	///< Mapped To PORTR
} PORTCFG_VP0MAP_t;
	
/// Virtual Port 1 Mapping

typedef enum PORTCFG_VP1MAP_enum {
	PORTCFG_VP1MAP_PORTA_gc = (0x00<<4),	///< Mapped To PORTA
	PORTCFG_VP1MAP_PORTB_gc = (0x01<<4),	///< Mapped To PORTB
	PORTCFG_VP1MAP_PORTC_gc = (0x02<<4),	///< Mapped To PORTC
	PORTCFG_VP1MAP_PORTD_gc = (0x03<<4),	///< Mapped To PORTD
	PORTCFG_VP1MAP_PORTE_gc = (0x04<<4),	///< Mapped To PORTE
	PORTCFG_VP1MAP_PORTF_gc = (0x05<<4),	///< Mapped To PORTF
	PORTCFG_VP1MAP_PORTG_gc = (0x06<<4),	///< Mapped To PORTG
	PORTCFG_VP1MAP_PORTH_gc = (0x07<<4),	///< Mapped To PORTH
	PORTCFG_VP1MAP_PORTJ_gc = (0x08<<4),	///< Mapped To PORTJ
	PORTCFG_VP1MAP_PORTK_gc = (0x09<<4),	///< Mapped To PORTK
	PORTCFG_VP1MAP_PORTL_gc = (0x0A<<4),	///< Mapped To PORTL
	PORTCFG_VP1MAP_PORTM_gc = (0x0B<<4),	///< Mapped To PORTM
	PORTCFG_VP1MAP_PORTN_gc = (0x0C<<4),	///< Mapped To PORTN
	PORTCFG_VP1MAP_PORTP_gc = (0x0D<<4),	///< Mapped To PORTP
	PORTCFG_VP1MAP_PORTQ_gc = (0x0E<<4),	///< Mapped To PORTQ
	PORTCFG_VP1MAP_PORTR_gc = (0x0F<<4),	///< Mapped To PORTR
} PORTCFG_VP1MAP_t;
	
/// Virtual Port 2 Mapping

typedef enum PORTCFG_VP2MAP_enum {
	PORTCFG_VP2MAP_PORTA_gc = (0x00<<0),	///< Mapped To PORTA
	PORTCFG_VP2MAP_PORTB_gc = (0x01<<0),	///< Mapped To PORTB
	PORTCFG_VP2MAP_PORTC_gc = (0x02<<0),	///< Mapped To PORTC
	PORTCFG_VP2MAP_PORTD_gc = (0x03<<0),	///< Mapped To PORTD
	PORTCFG_VP2MAP_PORTE_gc = (0x04<<0),	///< Mapped To PORTE
	PORTCFG_VP2MAP_PORTF_gc = (0x05<<0),	///< Mapped To PORTF
	PORTCFG_VP2MAP_PORTG_gc = (0x06<<0),	///< Mapped To PORTG
	PORTCFG_VP2MAP_PORTH_gc = (0x07<<0),	///< Mapped To PORTH
	PORTCFG_VP2MAP_PORTJ_gc = (0x08<<0),	///< Mapped To PORTJ
	PORTCFG_VP2MAP_PORTK_gc = (0x09<<0),	///< Mapped To PORTK
	PORTCFG_VP2MAP_PORTL_gc = (0x0A<<0),	///< Mapped To PORTL
	PORTCFG_VP2MAP_PORTM_gc = (0x0B<<0),	///< Mapped To PORTM
	PORTCFG_VP2MAP_PORTN_gc = (0x0C<<0),	///< Mapped To PORTN
	PORTCFG_VP2MAP_PORTP_gc = (0x0D<<0),	///< Mapped To PORTP
	PORTCFG_VP2MAP_PORTQ_gc = (0x0E<<0),	///< Mapped To PORTQ
	PORTCFG_VP2MAP_PORTR_gc = (0x0F<<0),	///< Mapped To PORTR
} PORTCFG_VP2MAP_t;
	
/// Virtual Port 3 Mapping

typedef enum PORTCFG_VP3MAP_enum {
	PORTCFG_VP3MAP_PORTA_gc = (0x00<<4),	///< Mapped To PORTA
	PORTCFG_VP3MAP_PORTB_gc = (0x01<<4),	///< Mapped To PORTB
	PORTCFG_VP3MAP_PORTC_gc = (0x02<<4),	///< Mapped To PORTC
	PORTCFG_VP3MAP_PORTD_gc = (0x03<<4),	///< Mapped To PORTD
	PORTCFG_VP3MAP_PORTE_gc = (0x04<<4),	///< Mapped To PORTE
	PORTCFG_VP3MAP_PORTF_gc = (0x05<<4),	///< Mapped To PORTF
	PORTCFG_VP3MAP_PORTG_gc = (0x06<<4),	///< Mapped To PORTG
	PORTCFG_VP3MAP_PORTH_gc = (0x07<<4),	///< Mapped To PORTH
	PORTCFG_VP3MAP_PORTJ_gc = (0x08<<4),	///< Mapped To PORTJ
	PORTCFG_VP3MAP_PORTK_gc = (0x09<<4),	///< Mapped To PORTK
	PORTCFG_VP3MAP_PORTL_gc = (0x0A<<4),	///< Mapped To PORTL
	PORTCFG_VP3MAP_PORTM_gc = (0x0B<<4),	///< Mapped To PORTM
	PORTCFG_VP3MAP_PORTN_gc = (0x0C<<4),	///< Mapped To PORTN
	PORTCFG_VP3MAP_PORTP_gc = (0x0D<<4),	///< Mapped To PORTP
	PORTCFG_VP3MAP_PORTQ_gc = (0x0E<<4),	///< Mapped To PORTQ
	PORTCFG_VP3MAP_PORTR_gc = (0x0F<<4),	///< Mapped To PORTR
} PORTCFG_VP3MAP_t;
	
/// Clock Output Port

typedef enum PORTCFG_CLKOUT_enum {
	PORTCFG_CLKOUT_OFF_gc = (0x00<<0),	///< Clock Output Disabled
	PORTCFG_CLKOUT_PC7_gc = (0x01<<0),	///< Clock Output on Port C pin 7
	PORTCFG_CLKOUT_PD7_gc = (0x02<<0),	///< Clock Output on Port D pin 7
	PORTCFG_CLKOUT_PE7_gc = (0x03<<0),	///< Clock Output on Port E pin 7
} PORTCFG_CLKOUT_t;
	
/// Event Output Port

typedef enum PORTCFG_EVOUT_enum {
	PORTCFG_EVOUT_OFF_gc = (0x00<<4),	///< Event Output Disabled
	PORTCFG_EVOUT_PC7_gc = (0x01<<4),	///< Event Channel 7 Output on Port C pin 7
	PORTCFG_EVOUT_PD7_gc = (0x02<<4),	///< Event Channel 7 Output on Port D pin 7
	PORTCFG_EVOUT_PE7_gc = (0x03<<4),	///< Event Channel 7 Output on Port E pin 7
} PORTCFG_EVOUT_t;
	
/// Port Interrupt 0 Level

typedef enum PORT_INT0LVL_enum {
	PORT_INT0LVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	PORT_INT0LVL_LO_gc = (0x01<<0),	///< Low Level
	PORT_INT0LVL_MED_gc = (0x02<<0),	///< Medium Level
	PORT_INT0LVL_HI_gc = (0x03<<0),	///< High Level
} PORT_INT0LVL_t;
	
/// Port Interrupt 1 Level

typedef enum PORT_INT1LVL_enum {
	PORT_INT1LVL_OFF_gc = (0x00<<2),	///< Interrupt Disabled
	PORT_INT1LVL_LO_gc = (0x01<<2),	///< Low Level
	PORT_INT1LVL_MED_gc = (0x02<<2),	///< Medium Level
	PORT_INT1LVL_HI_gc = (0x03<<2),	///< High Level
} PORT_INT1LVL_t;
	
/// Output/Pull Configuration

typedef enum PORT_OPC_enum {
	PORT_OPC_TOTEM_gc = (0x00<<3),	///< Totempole
	PORT_OPC_BUSKEEPER_gc = (0x01<<3),	///< Totempole w/ Bus keeper on Input and Output
	PORT_OPC_PULLDOWN_gc = (0x02<<3),	///< Totempole w/ Pull-down on Input
	PORT_OPC_PULLUP_gc = (0x03<<3),	///< Totempole w/ Pull-up on Input
	PORT_OPC_WIREDOR_gc = (0x04<<3),	///< Wired OR
	PORT_OPC_WIREDAND_gc = (0x05<<3),	///< Wired AND
	PORT_OPC_WIREDORPULL_gc = (0x06<<3),	///< Wired OR w/ Pull-down
	PORT_OPC_WIREDANDPULL_gc = (0x07<<3),	///< Wired AND w/ Pull-up
} PORT_OPC_t;
	
/// Input/Sense Configuration

typedef enum PORT_ISC_enum {
	PORT_ISC_BOTHEDGES_gc = (0x00<<0),	///< Sense Both Edges
	PORT_ISC_RISING_gc = (0x01<<0),	///< Sense Rising Edge
	PORT_ISC_FALLING_gc = (0x02<<0),	///< Sense Falling Edge
	PORT_ISC_LEVEL_gc = (0x03<<0),	///< Sense Level (Transparent For Events)
	PORT_ISC_INPUT_DISABLE_gc = (0x07<<0),	///< Disable Digital Input Buffer
} PORT_ISC_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Virtual Port 0 Mapping
#define PORTCFG_VP0MAP_PORTA_gc (0x00<<0)	///< Mapped To PORTA
#define PORTCFG_VP0MAP_PORTB_gc (0x01<<0)	///< Mapped To PORTB
#define PORTCFG_VP0MAP_PORTC_gc (0x02<<0)	///< Mapped To PORTC
#define PORTCFG_VP0MAP_PORTD_gc (0x03<<0)	///< Mapped To PORTD
#define PORTCFG_VP0MAP_PORTE_gc (0x04<<0)	///< Mapped To PORTE
#define PORTCFG_VP0MAP_PORTF_gc (0x05<<0)	///< Mapped To PORTF
#define PORTCFG_VP0MAP_PORTG_gc (0x06<<0)	///< Mapped To PORTG
#define PORTCFG_VP0MAP_PORTH_gc (0x07<<0)	///< Mapped To PORTH
#define PORTCFG_VP0MAP_PORTJ_gc (0x08<<0)	///< Mapped To PORTJ
#define PORTCFG_VP0MAP_PORTK_gc (0x09<<0)	///< Mapped To PORTK
#define PORTCFG_VP0MAP_PORTL_gc (0x0A<<0)	///< Mapped To PORTL
#define PORTCFG_VP0MAP_PORTM_gc (0x0B<<0)	///< Mapped To PORTM
#define PORTCFG_VP0MAP_PORTN_gc (0x0C<<0)	///< Mapped To PORTN
#define PORTCFG_VP0MAP_PORTP_gc (0x0D<<0)	///< Mapped To PORTP
#define PORTCFG_VP0MAP_PORTQ_gc (0x0E<<0)	///< Mapped To PORTQ
#define PORTCFG_VP0MAP_PORTR_gc (0x0F<<0)	///< Mapped To PORTR

/// Virtual Port 1 Mapping
#define PORTCFG_VP1MAP_PORTA_gc (0x00<<4)	///< Mapped To PORTA
#define PORTCFG_VP1MAP_PORTB_gc (0x01<<4)	///< Mapped To PORTB
#define PORTCFG_VP1MAP_PORTC_gc (0x02<<4)	///< Mapped To PORTC
#define PORTCFG_VP1MAP_PORTD_gc (0x03<<4)	///< Mapped To PORTD
#define PORTCFG_VP1MAP_PORTE_gc (0x04<<4)	///< Mapped To PORTE
#define PORTCFG_VP1MAP_PORTF_gc (0x05<<4)	///< Mapped To PORTF
#define PORTCFG_VP1MAP_PORTG_gc (0x06<<4)	///< Mapped To PORTG
#define PORTCFG_VP1MAP_PORTH_gc (0x07<<4)	///< Mapped To PORTH
#define PORTCFG_VP1MAP_PORTJ_gc (0x08<<4)	///< Mapped To PORTJ
#define PORTCFG_VP1MAP_PORTK_gc (0x09<<4)	///< Mapped To PORTK
#define PORTCFG_VP1MAP_PORTL_gc (0x0A<<4)	///< Mapped To PORTL
#define PORTCFG_VP1MAP_PORTM_gc (0x0B<<4)	///< Mapped To PORTM
#define PORTCFG_VP1MAP_PORTN_gc (0x0C<<4)	///< Mapped To PORTN
#define PORTCFG_VP1MAP_PORTP_gc (0x0D<<4)	///< Mapped To PORTP
#define PORTCFG_VP1MAP_PORTQ_gc (0x0E<<4)	///< Mapped To PORTQ
#define PORTCFG_VP1MAP_PORTR_gc (0x0F<<4)	///< Mapped To PORTR

/// Virtual Port 2 Mapping
#define PORTCFG_VP2MAP_PORTA_gc (0x00<<0)	///< Mapped To PORTA
#define PORTCFG_VP2MAP_PORTB_gc (0x01<<0)	///< Mapped To PORTB
#define PORTCFG_VP2MAP_PORTC_gc (0x02<<0)	///< Mapped To PORTC
#define PORTCFG_VP2MAP_PORTD_gc (0x03<<0)	///< Mapped To PORTD
#define PORTCFG_VP2MAP_PORTE_gc (0x04<<0)	///< Mapped To PORTE
#define PORTCFG_VP2MAP_PORTF_gc (0x05<<0)	///< Mapped To PORTF
#define PORTCFG_VP2MAP_PORTG_gc (0x06<<0)	///< Mapped To PORTG
#define PORTCFG_VP2MAP_PORTH_gc (0x07<<0)	///< Mapped To PORTH
#define PORTCFG_VP2MAP_PORTJ_gc (0x08<<0)	///< Mapped To PORTJ
#define PORTCFG_VP2MAP_PORTK_gc (0x09<<0)	///< Mapped To PORTK
#define PORTCFG_VP2MAP_PORTL_gc (0x0A<<0)	///< Mapped To PORTL
#define PORTCFG_VP2MAP_PORTM_gc (0x0B<<0)	///< Mapped To PORTM
#define PORTCFG_VP2MAP_PORTN_gc (0x0C<<0)	///< Mapped To PORTN
#define PORTCFG_VP2MAP_PORTP_gc (0x0D<<0)	///< Mapped To PORTP
#define PORTCFG_VP2MAP_PORTQ_gc (0x0E<<0)	///< Mapped To PORTQ
#define PORTCFG_VP2MAP_PORTR_gc (0x0F<<0)	///< Mapped To PORTR

/// Virtual Port 3 Mapping
#define PORTCFG_VP3MAP_PORTA_gc (0x00<<4)	///< Mapped To PORTA
#define PORTCFG_VP3MAP_PORTB_gc (0x01<<4)	///< Mapped To PORTB
#define PORTCFG_VP3MAP_PORTC_gc (0x02<<4)	///< Mapped To PORTC
#define PORTCFG_VP3MAP_PORTD_gc (0x03<<4)	///< Mapped To PORTD
#define PORTCFG_VP3MAP_PORTE_gc (0x04<<4)	///< Mapped To PORTE
#define PORTCFG_VP3MAP_PORTF_gc (0x05<<4)	///< Mapped To PORTF
#define PORTCFG_VP3MAP_PORTG_gc (0x06<<4)	///< Mapped To PORTG
#define PORTCFG_VP3MAP_PORTH_gc (0x07<<4)	///< Mapped To PORTH
#define PORTCFG_VP3MAP_PORTJ_gc (0x08<<4)	///< Mapped To PORTJ
#define PORTCFG_VP3MAP_PORTK_gc (0x09<<4)	///< Mapped To PORTK
#define PORTCFG_VP3MAP_PORTL_gc (0x0A<<4)	///< Mapped To PORTL
#define PORTCFG_VP3MAP_PORTM_gc (0x0B<<4)	///< Mapped To PORTM
#define PORTCFG_VP3MAP_PORTN_gc (0x0C<<4)	///< Mapped To PORTN
#define PORTCFG_VP3MAP_PORTP_gc (0x0D<<4)	///< Mapped To PORTP
#define PORTCFG_VP3MAP_PORTQ_gc (0x0E<<4)	///< Mapped To PORTQ
#define PORTCFG_VP3MAP_PORTR_gc (0x0F<<4)	///< Mapped To PORTR

/// Clock Output Port
#define PORTCFG_CLKOUT_OFF_gc (0x00<<0)	///< Clock Output Disabled
#define PORTCFG_CLKOUT_PC7_gc (0x01<<0)	///< Clock Output on Port C pin 7
#define PORTCFG_CLKOUT_PD7_gc (0x02<<0)	///< Clock Output on Port D pin 7
#define PORTCFG_CLKOUT_PE7_gc (0x03<<0)	///< Clock Output on Port E pin 7

/// Event Output Port
#define PORTCFG_EVOUT_OFF_gc (0x00<<4)	///< Event Output Disabled
#define PORTCFG_EVOUT_PC7_gc (0x01<<4)	///< Event Channel 7 Output on Port C pin 7
#define PORTCFG_EVOUT_PD7_gc (0x02<<4)	///< Event Channel 7 Output on Port D pin 7
#define PORTCFG_EVOUT_PE7_gc (0x03<<4)	///< Event Channel 7 Output on Port E pin 7

/// Port Interrupt 0 Level
#define PORT_INT0LVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define PORT_INT0LVL_LO_gc (0x01<<0)	///< Low Level
#define PORT_INT0LVL_MED_gc (0x02<<0)	///< Medium Level
#define PORT_INT0LVL_HI_gc (0x03<<0)	///< High Level

/// Port Interrupt 1 Level
#define PORT_INT1LVL_OFF_gc (0x00<<2)	///< Interrupt Disabled
#define PORT_INT1LVL_LO_gc (0x01<<2)	///< Low Level
#define PORT_INT1LVL_MED_gc (0x02<<2)	///< Medium Level
#define PORT_INT1LVL_HI_gc (0x03<<2)	///< High Level

/// Output/Pull Configuration
#define PORT_OPC_TOTEM_gc (0x00<<3)	///< Totempole
#define PORT_OPC_BUSKEEPER_gc (0x01<<3)	///< Totempole w/ Bus keeper on Input and Output
#define PORT_OPC_PULLDOWN_gc (0x02<<3)	///< Totempole w/ Pull-down on Input
#define PORT_OPC_PULLUP_gc (0x03<<3)	///< Totempole w/ Pull-up on Input
#define PORT_OPC_WIREDOR_gc (0x04<<3)	///< Wired OR
#define PORT_OPC_WIREDAND_gc (0x05<<3)	///< Wired AND
#define PORT_OPC_WIREDORPULL_gc (0x06<<3)	///< Wired OR w/ Pull-down
#define PORT_OPC_WIREDANDPULL_gc (0x07<<3)	///< Wired AND w/ Pull-up

/// Input/Sense Configuration
#define PORT_ISC_BOTHEDGES_gc (0x00<<0)	///< Sense Both Edges
#define PORT_ISC_RISING_gc (0x01<<0)	///< Sense Rising Edge
#define PORT_ISC_FALLING_gc (0x02<<0)	///< Sense Falling Edge
#define PORT_ISC_LEVEL_gc (0x03<<0)	///< Sense Level (Transparent For Events)
#define PORT_ISC_INPUT_DISABLE_gc (0x07<<0)	///< Disable Digital Input Buffer

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup tc 16-bit Timer/Counter With PWM
 *  @{
 */
	
/** @name TC0.CTRLA
  * @see TC_CLKSEL_enum
  * @{
  */
#define TC0_CLKSEL_gm 0x0F ///< Clock Selection group mask
#define TC0_CLKSEL_gp 0 ///< Clock Selection group position
#define TC0_CLKSEL0_bm (1<<0) ///< Clock Selection bit 0 mask
#define TC0_CLKSEL0_bp 0 ///< Clock Selection bit 0 position
#define TC0_CLKSEL1_bm (1<<1) ///< Clock Selection bit 1 mask
#define TC0_CLKSEL1_bp 1 ///< Clock Selection bit 1 position
#define TC0_CLKSEL2_bm (1<<2) ///< Clock Selection bit 2 mask
#define TC0_CLKSEL2_bp 2 ///< Clock Selection bit 2 position
#define TC0_CLKSEL3_bm (1<<3) ///< Clock Selection bit 3 mask
#define TC0_CLKSEL3_bp 3 ///< Clock Selection bit 3 position
/** @} */
	
/** @name TC0.CTRLB
  * @see TC_WGMODE_enum
  * @{
  */
#define TC0_CCDEN_bm 0x80 ///< Compare or Capture D Enable bit mask
#define TC0_CCDEN_bp 7 ///< Compare or Capture D Enable bit position
#define TC0_CCCEN_bm 0x40 ///< Compare or Capture C Enable bit mask
#define TC0_CCCEN_bp 6 ///< Compare or Capture C Enable bit position
#define TC0_CCBEN_bm 0x20 ///< Compare or Capture B Enable bit mask
#define TC0_CCBEN_bp 5 ///< Compare or Capture B Enable bit position
#define TC0_CCAEN_bm 0x10 ///< Compare or Capture A Enable bit mask
#define TC0_CCAEN_bp 4 ///< Compare or Capture A Enable bit position
#define TC0_WGMODE_gm 0x07 ///< Waveform generation mode group mask
#define TC0_WGMODE_gp 0 ///< Waveform generation mode group position
#define TC0_WGMODE0_bm (1<<0) ///< Waveform generation mode bit 0 mask
#define TC0_WGMODE0_bp 0 ///< Waveform generation mode bit 0 position
#define TC0_WGMODE1_bm (1<<1) ///< Waveform generation mode bit 1 mask
#define TC0_WGMODE1_bp 1 ///< Waveform generation mode bit 1 position
#define TC0_WGMODE2_bm (1<<2) ///< Waveform generation mode bit 2 mask
#define TC0_WGMODE2_bp 2 ///< Waveform generation mode bit 2 position
/** @} */
	
/** @name TC0.CTRLC
  * @{
  */
#define TC0_CMPD_bm 0x08 ///< Compare D Output Value bit mask
#define TC0_CMPD_bp 3 ///< Compare D Output Value bit position
#define TC0_CMPC_bm 0x04 ///< Compare C Output Value bit mask
#define TC0_CMPC_bp 2 ///< Compare C Output Value bit position
#define TC0_CMPB_bm 0x02 ///< Compare B Output Value bit mask
#define TC0_CMPB_bp 1 ///< Compare B Output Value bit position
#define TC0_CMPA_bm 0x01 ///< Compare A Output Value bit mask
#define TC0_CMPA_bp 0 ///< Compare A Output Value bit position
/** @} */
	
/** @name TC0.CTRLD
  * @see TC_EVACT_enum
  * @see TC_EVSEL_enum
  * @{
  */
#define TC0_EVACT_gm 0xE0 ///< Event Action group mask
#define TC0_EVACT_gp 5 ///< Event Action group position
#define TC0_EVACT0_bm (1<<5) ///< Event Action bit 0 mask
#define TC0_EVACT0_bp 5 ///< Event Action bit 0 position
#define TC0_EVACT1_bm (1<<6) ///< Event Action bit 1 mask
#define TC0_EVACT1_bp 6 ///< Event Action bit 1 position
#define TC0_EVACT2_bm (1<<7) ///< Event Action bit 2 mask
#define TC0_EVACT2_bp 7 ///< Event Action bit 2 position
#define TC0_EVDLY_bm 0x10 ///< Event Delay bit mask
#define TC0_EVDLY_bp 4 ///< Event Delay bit position
#define TC0_EVSEL_gm 0x0F ///< Event Source Select group mask
#define TC0_EVSEL_gp 0 ///< Event Source Select group position
#define TC0_EVSEL0_bm (1<<0) ///< Event Source Select bit 0 mask
#define TC0_EVSEL0_bp 0 ///< Event Source Select bit 0 position
#define TC0_EVSEL1_bm (1<<1) ///< Event Source Select bit 1 mask
#define TC0_EVSEL1_bp 1 ///< Event Source Select bit 1 position
#define TC0_EVSEL2_bm (1<<2) ///< Event Source Select bit 2 mask
#define TC0_EVSEL2_bp 2 ///< Event Source Select bit 2 position
#define TC0_EVSEL3_bm (1<<3) ///< Event Source Select bit 3 mask
#define TC0_EVSEL3_bp 3 ///< Event Source Select bit 3 position
/** @} */
	
/** @name TC0.CTRLE
  * @{
  */
#define TC0_BYTEM_bm 0x01 ///< Byte Mode bit mask
#define TC0_BYTEM_bp 0 ///< Byte Mode bit position
/** @} */
	
/** @name TC0.INTCTRLA
  * @see TC_ERRINTLVL_enum
  * @see TC_OVFINTLVL_enum
  * @{
  */
#define TC0_ERRINTLVL_gm 0x0C ///< Error Interrupt Level group mask
#define TC0_ERRINTLVL_gp 2 ///< Error Interrupt Level group position
#define TC0_ERRINTLVL0_bm (1<<2) ///< Error Interrupt Level bit 0 mask
#define TC0_ERRINTLVL0_bp 2 ///< Error Interrupt Level bit 0 position
#define TC0_ERRINTLVL1_bm (1<<3) ///< Error Interrupt Level bit 1 mask
#define TC0_ERRINTLVL1_bp 3 ///< Error Interrupt Level bit 1 position
#define TC0_OVFINTLVL_gm 0x03 ///< Overflow interrupt level group mask
#define TC0_OVFINTLVL_gp 0 ///< Overflow interrupt level group position
#define TC0_OVFINTLVL0_bm (1<<0) ///< Overflow interrupt level bit 0 mask
#define TC0_OVFINTLVL0_bp 0 ///< Overflow interrupt level bit 0 position
#define TC0_OVFINTLVL1_bm (1<<1) ///< Overflow interrupt level bit 1 mask
#define TC0_OVFINTLVL1_bp 1 ///< Overflow interrupt level bit 1 position
/** @} */
	
/** @name TC0.INTCTRLB
  * @see TC_CCDINTLVL_enum
  * @see TC_CCCINTLVL_enum
  * @see TC_CCBINTLVL_enum
  * @see TC_CCAINTLVL_enum
  * @{
  */
#define TC0_CCDINTLVL_gm 0xC0 ///< Compare or Capture D Interrupt Level group mask
#define TC0_CCDINTLVL_gp 6 ///< Compare or Capture D Interrupt Level group position
#define TC0_CCDINTLVL0_bm (1<<6) ///< Compare or Capture D Interrupt Level bit 0 mask
#define TC0_CCDINTLVL0_bp 6 ///< Compare or Capture D Interrupt Level bit 0 position
#define TC0_CCDINTLVL1_bm (1<<7) ///< Compare or Capture D Interrupt Level bit 1 mask
#define TC0_CCDINTLVL1_bp 7 ///< Compare or Capture D Interrupt Level bit 1 position
#define TC0_CCCINTLVL_gm 0x30 ///< Compare or Capture C Interrupt Level group mask
#define TC0_CCCINTLVL_gp 4 ///< Compare or Capture C Interrupt Level group position
#define TC0_CCCINTLVL0_bm (1<<4) ///< Compare or Capture C Interrupt Level bit 0 mask
#define TC0_CCCINTLVL0_bp 4 ///< Compare or Capture C Interrupt Level bit 0 position
#define TC0_CCCINTLVL1_bm (1<<5) ///< Compare or Capture C Interrupt Level bit 1 mask
#define TC0_CCCINTLVL1_bp 5 ///< Compare or Capture C Interrupt Level bit 1 position
#define TC0_CCBINTLVL_gm 0x0C ///< Compare or Capture B Interrupt Level group mask
#define TC0_CCBINTLVL_gp 2 ///< Compare or Capture B Interrupt Level group position
#define TC0_CCBINTLVL0_bm (1<<2) ///< Compare or Capture B Interrupt Level bit 0 mask
#define TC0_CCBINTLVL0_bp 2 ///< Compare or Capture B Interrupt Level bit 0 position
#define TC0_CCBINTLVL1_bm (1<<3) ///< Compare or Capture B Interrupt Level bit 1 mask
#define TC0_CCBINTLVL1_bp 3 ///< Compare or Capture B Interrupt Level bit 1 position
#define TC0_CCAINTLVL_gm 0x03 ///< Compare or Capture A Interrupt Level group mask
#define TC0_CCAINTLVL_gp 0 ///< Compare or Capture A Interrupt Level group position
#define TC0_CCAINTLVL0_bm (1<<0) ///< Compare or Capture A Interrupt Level bit 0 mask
#define TC0_CCAINTLVL0_bp 0 ///< Compare or Capture A Interrupt Level bit 0 position
#define TC0_CCAINTLVL1_bm (1<<1) ///< Compare or Capture A Interrupt Level bit 1 mask
#define TC0_CCAINTLVL1_bp 1 ///< Compare or Capture A Interrupt Level bit 1 position
/** @} */
	
/** @name TC0.CTRLFCLR
  * @{
  */
#define TC0_CMD_gm 0x0C ///< Command group mask
#define TC0_CMD_gp 2 ///< Command group position
#define TC0_CMD0_bm (1<<2) ///< Command bit 0 mask
#define TC0_CMD0_bp 2 ///< Command bit 0 position
#define TC0_CMD1_bm (1<<3) ///< Command bit 1 mask
#define TC0_CMD1_bp 3 ///< Command bit 1 position
#define TC0_LUPD_bm 0x02 ///< Lock Update bit mask
#define TC0_LUPD_bp 1 ///< Lock Update bit position
#define TC0_DIR_bm 0x01 ///< Direction bit mask
#define TC0_DIR_bp 0 ///< Direction bit position
/** @} */
	
/** @name TC0.CTRLFSET
  * @see TC_CMD_enum
  * @{
  */
// Masks for CMD aready defined
// Masks for LUPD aready defined
// Masks for DIR aready defined
/** @} */
	
/** @name TC0.CTRLGCLR
  * @{
  */
#define TC0_CCDBV_bm 0x10 ///< Compare or Capture D Buffer Valid bit mask
#define TC0_CCDBV_bp 4 ///< Compare or Capture D Buffer Valid bit position
#define TC0_CCCBV_bm 0x08 ///< Compare or Capture C Buffer Valid bit mask
#define TC0_CCCBV_bp 3 ///< Compare or Capture C Buffer Valid bit position
#define TC0_CCBBV_bm 0x04 ///< Compare or Capture B Buffer Valid bit mask
#define TC0_CCBBV_bp 2 ///< Compare or Capture B Buffer Valid bit position
#define TC0_CCABV_bm 0x02 ///< Compare or Capture A Buffer Valid bit mask
#define TC0_CCABV_bp 1 ///< Compare or Capture A Buffer Valid bit position
#define TC0_PERBV_bm 0x01 ///< Period Buffer Valid bit mask
#define TC0_PERBV_bp 0 ///< Period Buffer Valid bit position
/** @} */
	
/** @name TC0.CTRLGSET
  * @{
  */
// Masks for CCDBV aready defined
// Masks for CCCBV aready defined
// Masks for CCBBV aready defined
// Masks for CCABV aready defined
// Masks for PERBV aready defined
/** @} */
	
/** @name TC0.INTFLAGS
  * @{
  */
#define TC0_CCDIF_bm 0x80 ///< Compare or Capture D Interrupt Flag bit mask
#define TC0_CCDIF_bp 7 ///< Compare or Capture D Interrupt Flag bit position
#define TC0_CCCIF_bm 0x40 ///< Compare or Capture C Interrupt Flag bit mask
#define TC0_CCCIF_bp 6 ///< Compare or Capture C Interrupt Flag bit position
#define TC0_CCBIF_bm 0x20 ///< Compare or Capture B Interrupt Flag bit mask
#define TC0_CCBIF_bp 5 ///< Compare or Capture B Interrupt Flag bit position
#define TC0_CCAIF_bm 0x10 ///< Compare or Capture A Interrupt Flag bit mask
#define TC0_CCAIF_bp 4 ///< Compare or Capture A Interrupt Flag bit position
#define TC0_ERRIF_bm 0x02 ///< Error Interrupt Flag bit mask
#define TC0_ERRIF_bp 1 ///< Error Interrupt Flag bit position
#define TC0_OVFIF_bm 0x01 ///< Overflow Interrupt Flag bit mask
#define TC0_OVFIF_bp 0 ///< Overflow Interrupt Flag bit position
/** @} */
	
/** @name TC1.CTRLA
  * @see TC_CLKSEL_enum
  * @{
  */
#define TC1_CLKSEL_gm 0x0F ///< Clock Selection group mask
#define TC1_CLKSEL_gp 0 ///< Clock Selection group position
#define TC1_CLKSEL0_bm (1<<0) ///< Clock Selection bit 0 mask
#define TC1_CLKSEL0_bp 0 ///< Clock Selection bit 0 position
#define TC1_CLKSEL1_bm (1<<1) ///< Clock Selection bit 1 mask
#define TC1_CLKSEL1_bp 1 ///< Clock Selection bit 1 position
#define TC1_CLKSEL2_bm (1<<2) ///< Clock Selection bit 2 mask
#define TC1_CLKSEL2_bp 2 ///< Clock Selection bit 2 position
#define TC1_CLKSEL3_bm (1<<3) ///< Clock Selection bit 3 mask
#define TC1_CLKSEL3_bp 3 ///< Clock Selection bit 3 position
/** @} */
	
/** @name TC1.CTRLB
  * @see TC_WGMODE_enum
  * @{
  */
#define TC1_CCBEN_bm 0x20 ///< Compare or Capture B Enable bit mask
#define TC1_CCBEN_bp 5 ///< Compare or Capture B Enable bit position
#define TC1_CCAEN_bm 0x10 ///< Compare or Capture A Enable bit mask
#define TC1_CCAEN_bp 4 ///< Compare or Capture A Enable bit position
#define TC1_WGMODE_gm 0x07 ///< Waveform generation mode group mask
#define TC1_WGMODE_gp 0 ///< Waveform generation mode group position
#define TC1_WGMODE0_bm (1<<0) ///< Waveform generation mode bit 0 mask
#define TC1_WGMODE0_bp 0 ///< Waveform generation mode bit 0 position
#define TC1_WGMODE1_bm (1<<1) ///< Waveform generation mode bit 1 mask
#define TC1_WGMODE1_bp 1 ///< Waveform generation mode bit 1 position
#define TC1_WGMODE2_bm (1<<2) ///< Waveform generation mode bit 2 mask
#define TC1_WGMODE2_bp 2 ///< Waveform generation mode bit 2 position
/** @} */
	
/** @name TC1.CTRLC
  * @{
  */
#define TC1_CMPB_bm 0x02 ///< Compare B Output Value bit mask
#define TC1_CMPB_bp 1 ///< Compare B Output Value bit position
#define TC1_CMPA_bm 0x01 ///< Compare A Output Value bit mask
#define TC1_CMPA_bp 0 ///< Compare A Output Value bit position
/** @} */
	
/** @name TC1.CTRLD
  * @see TC_EVACT_enum
  * @see TC_EVSEL_enum
  * @{
  */
#define TC1_EVACT_gm 0xE0 ///< Event Action group mask
#define TC1_EVACT_gp 5 ///< Event Action group position
#define TC1_EVACT0_bm (1<<5) ///< Event Action bit 0 mask
#define TC1_EVACT0_bp 5 ///< Event Action bit 0 position
#define TC1_EVACT1_bm (1<<6) ///< Event Action bit 1 mask
#define TC1_EVACT1_bp 6 ///< Event Action bit 1 position
#define TC1_EVACT2_bm (1<<7) ///< Event Action bit 2 mask
#define TC1_EVACT2_bp 7 ///< Event Action bit 2 position
#define TC1_EVDLY_bm 0x10 ///< Event Delay bit mask
#define TC1_EVDLY_bp 4 ///< Event Delay bit position
#define TC1_EVSEL_gm 0x0F ///< Event Source Select group mask
#define TC1_EVSEL_gp 0 ///< Event Source Select group position
#define TC1_EVSEL0_bm (1<<0) ///< Event Source Select bit 0 mask
#define TC1_EVSEL0_bp 0 ///< Event Source Select bit 0 position
#define TC1_EVSEL1_bm (1<<1) ///< Event Source Select bit 1 mask
#define TC1_EVSEL1_bp 1 ///< Event Source Select bit 1 position
#define TC1_EVSEL2_bm (1<<2) ///< Event Source Select bit 2 mask
#define TC1_EVSEL2_bp 2 ///< Event Source Select bit 2 position
#define TC1_EVSEL3_bm (1<<3) ///< Event Source Select bit 3 mask
#define TC1_EVSEL3_bp 3 ///< Event Source Select bit 3 position
/** @} */
	
/** @name TC1.CTRLE
  * @{
  */
#define TC1_BYTEM_bm 0x01 ///< Byte Mode bit mask
#define TC1_BYTEM_bp 0 ///< Byte Mode bit position
/** @} */
	
/** @name TC1.INTCTRLA
  * @see TC_ERRINTLVL_enum
  * @see TC_OVFINTLVL_enum
  * @{
  */
#define TC1_ERRINTLVL_gm 0x0C ///< Error Interrupt Level group mask
#define TC1_ERRINTLVL_gp 2 ///< Error Interrupt Level group position
#define TC1_ERRINTLVL0_bm (1<<2) ///< Error Interrupt Level bit 0 mask
#define TC1_ERRINTLVL0_bp 2 ///< Error Interrupt Level bit 0 position
#define TC1_ERRINTLVL1_bm (1<<3) ///< Error Interrupt Level bit 1 mask
#define TC1_ERRINTLVL1_bp 3 ///< Error Interrupt Level bit 1 position
#define TC1_OVFINTLVL_gm 0x03 ///< Overflow interrupt level group mask
#define TC1_OVFINTLVL_gp 0 ///< Overflow interrupt level group position
#define TC1_OVFINTLVL0_bm (1<<0) ///< Overflow interrupt level bit 0 mask
#define TC1_OVFINTLVL0_bp 0 ///< Overflow interrupt level bit 0 position
#define TC1_OVFINTLVL1_bm (1<<1) ///< Overflow interrupt level bit 1 mask
#define TC1_OVFINTLVL1_bp 1 ///< Overflow interrupt level bit 1 position
/** @} */
	
/** @name TC1.INTCTRLB
  * @see TC_CCBINTLVL_enum
  * @see TC_CCAINTLVL_enum
  * @{
  */
#define TC1_CCBINTLVL_gm 0x0C ///< Compare or Capture B Interrupt Level group mask
#define TC1_CCBINTLVL_gp 2 ///< Compare or Capture B Interrupt Level group position
#define TC1_CCBINTLVL0_bm (1<<2) ///< Compare or Capture B Interrupt Level bit 0 mask
#define TC1_CCBINTLVL0_bp 2 ///< Compare or Capture B Interrupt Level bit 0 position
#define TC1_CCBINTLVL1_bm (1<<3) ///< Compare or Capture B Interrupt Level bit 1 mask
#define TC1_CCBINTLVL1_bp 3 ///< Compare or Capture B Interrupt Level bit 1 position
#define TC1_CCAINTLVL_gm 0x03 ///< Compare or Capture A Interrupt Level group mask
#define TC1_CCAINTLVL_gp 0 ///< Compare or Capture A Interrupt Level group position
#define TC1_CCAINTLVL0_bm (1<<0) ///< Compare or Capture A Interrupt Level bit 0 mask
#define TC1_CCAINTLVL0_bp 0 ///< Compare or Capture A Interrupt Level bit 0 position
#define TC1_CCAINTLVL1_bm (1<<1) ///< Compare or Capture A Interrupt Level bit 1 mask
#define TC1_CCAINTLVL1_bp 1 ///< Compare or Capture A Interrupt Level bit 1 position
/** @} */
	
/** @name TC1.CTRLFCLR
  * @{
  */
#define TC1_CMD_gm 0x0C ///< Command group mask
#define TC1_CMD_gp 2 ///< Command group position
#define TC1_CMD0_bm (1<<2) ///< Command bit 0 mask
#define TC1_CMD0_bp 2 ///< Command bit 0 position
#define TC1_CMD1_bm (1<<3) ///< Command bit 1 mask
#define TC1_CMD1_bp 3 ///< Command bit 1 position
#define TC1_LUPD_bm 0x02 ///< Lock Update bit mask
#define TC1_LUPD_bp 1 ///< Lock Update bit position
#define TC1_DIR_bm 0x01 ///< Direction bit mask
#define TC1_DIR_bp 0 ///< Direction bit position
/** @} */
	
/** @name TC1.CTRLFSET
  * @see TC_CMD_enum
  * @{
  */
// Masks for CMD aready defined
// Masks for LUPD aready defined
// Masks for DIR aready defined
/** @} */
	
/** @name TC1.CTRLGCLR
  * @{
  */
#define TC1_CCBBV_bm 0x04 ///< Compare or Capture B Buffer Valid bit mask
#define TC1_CCBBV_bp 2 ///< Compare or Capture B Buffer Valid bit position
#define TC1_CCABV_bm 0x02 ///< Compare or Capture A Buffer Valid bit mask
#define TC1_CCABV_bp 1 ///< Compare or Capture A Buffer Valid bit position
#define TC1_PERBV_bm 0x01 ///< Period Buffer Valid bit mask
#define TC1_PERBV_bp 0 ///< Period Buffer Valid bit position
/** @} */
	
/** @name TC1.CTRLGSET
  * @{
  */
// Masks for CCBBV aready defined
// Masks for CCABV aready defined
// Masks for PERBV aready defined
/** @} */
	
/** @name TC1.INTFLAGS
  * @{
  */
#define TC1_CCBIF_bm 0x20 ///< Compare or Capture B Interrupt Flag bit mask
#define TC1_CCBIF_bp 5 ///< Compare or Capture B Interrupt Flag bit position
#define TC1_CCAIF_bm 0x10 ///< Compare or Capture A Interrupt Flag bit mask
#define TC1_CCAIF_bp 4 ///< Compare or Capture A Interrupt Flag bit position
#define TC1_ERRIF_bm 0x02 ///< Error Interrupt Flag bit mask
#define TC1_ERRIF_bp 1 ///< Error Interrupt Flag bit position
#define TC1_OVFIF_bm 0x01 ///< Overflow Interrupt Flag bit mask
#define TC1_OVFIF_bp 0 ///< Overflow Interrupt Flag bit position
/** @} */
	
/** @name AWEX.CTRL
  * @{
  */
#define AWEX_PGM_bm 0x20 ///< Pattern Generation Mode bit mask
#define AWEX_PGM_bp 5 ///< Pattern Generation Mode bit position
#define AWEX_CWCM_bm 0x10 ///< Common Waveform Channel Mode bit mask
#define AWEX_CWCM_bp 4 ///< Common Waveform Channel Mode bit position
#define AWEX_DTICCDEN_bm 0x08 ///< Dead Time Insertion Compare Channel D Enable bit mask
#define AWEX_DTICCDEN_bp 3 ///< Dead Time Insertion Compare Channel D Enable bit position
#define AWEX_DTICCCEN_bm 0x04 ///< Dead Time Insertion Compare Channel C Enable bit mask
#define AWEX_DTICCCEN_bp 2 ///< Dead Time Insertion Compare Channel C Enable bit position
#define AWEX_DTICCBEN_bm 0x02 ///< Dead Time Insertion Compare Channel B Enable bit mask
#define AWEX_DTICCBEN_bp 1 ///< Dead Time Insertion Compare Channel B Enable bit position
#define AWEX_DTICCAEN_bm 0x01 ///< Dead Time Insertion Compare Channel A Enable bit mask
#define AWEX_DTICCAEN_bp 0 ///< Dead Time Insertion Compare Channel A Enable bit position
/** @} */
	
/** @name AWEX.FDCTRL
  * @see AWEX_FDACT_enum
  * @{
  */
#define AWEX_FDDBD_bm 0x10 ///< Fault Detect on Disable Break Disable bit mask
#define AWEX_FDDBD_bp 4 ///< Fault Detect on Disable Break Disable bit position
#define AWEX_FDMODE_bm 0x04 ///< Fault Detect Mode bit mask
#define AWEX_FDMODE_bp 2 ///< Fault Detect Mode bit position
#define AWEX_FDACT_gm 0x03 ///< Fault Detect Action group mask
#define AWEX_FDACT_gp 0 ///< Fault Detect Action group position
#define AWEX_FDACT0_bm (1<<0) ///< Fault Detect Action bit 0 mask
#define AWEX_FDACT0_bp 0 ///< Fault Detect Action bit 0 position
#define AWEX_FDACT1_bm (1<<1) ///< Fault Detect Action bit 1 mask
#define AWEX_FDACT1_bp 1 ///< Fault Detect Action bit 1 position
/** @} */
	
/** @name AWEX.STATUS
  * @{
  */
#define AWEX_FDF_bm 0x04 ///< Fault Detect Flag bit mask
#define AWEX_FDF_bp 2 ///< Fault Detect Flag bit position
#define AWEX_DTHSBUFV_bm 0x02 ///< Dead Time High Side Buffer Valid bit mask
#define AWEX_DTHSBUFV_bp 1 ///< Dead Time High Side Buffer Valid bit position
#define AWEX_DTLSBUFV_bm 0x01 ///< Dead Time Low Side Buffer Valid bit mask
#define AWEX_DTLSBUFV_bp 0 ///< Dead Time Low Side Buffer Valid bit position
/** @} */
	
/** @name HIRES.CTRLA
  * @see HIRES_HREN_enum
  * @{
  */
#define HIRES_HREN_gm 0x03 ///< High Resolution Enable group mask
#define HIRES_HREN_gp 0 ///< High Resolution Enable group position
#define HIRES_HREN0_bm (1<<0) ///< High Resolution Enable bit 0 mask
#define HIRES_HREN0_bp 0 ///< High Resolution Enable bit 0 position
#define HIRES_HREN1_bm (1<<1) ///< High Resolution Enable bit 1 mask
#define HIRES_HREN1_bp 1 ///< High Resolution Enable bit 1 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Clock Selection

typedef enum TC_CLKSEL_enum {
	TC_CLKSEL_OFF_gc = (0x00<<0),	///< Timer Off
	TC_CLKSEL_DIV1_gc = (0x01<<0),	///< System Clock
	TC_CLKSEL_DIV2_gc = (0x02<<0),	///< System Clock / 2
	TC_CLKSEL_DIV4_gc = (0x03<<0),	///< System Clock / 4
	TC_CLKSEL_DIV8_gc = (0x04<<0),	///< System Clock / 8
	TC_CLKSEL_DIV64_gc = (0x05<<0),	///< System Clock / 64
	TC_CLKSEL_DIV256_gc = (0x06<<0),	///< System Clock / 256
	TC_CLKSEL_DIV1024_gc = (0x07<<0),	///< System Clock / 1024
	TC_CLKSEL_EVCH0_gc = (0x08<<0),	///< Event Channel 0
	TC_CLKSEL_EVCH1_gc = (0x09<<0),	///< Event Channel 1
	TC_CLKSEL_EVCH2_gc = (0x0A<<0),	///< Event Channel 2
	TC_CLKSEL_EVCH3_gc = (0x0B<<0),	///< Event Channel 3
	TC_CLKSEL_EVCH4_gc = (0x0C<<0),	///< Event Channel 4
	TC_CLKSEL_EVCH5_gc = (0x0D<<0),	///< Event Channel 5
	TC_CLKSEL_EVCH6_gc = (0x0E<<0),	///< Event Channel 6
	TC_CLKSEL_EVCH7_gc = (0x0F<<0),	///< Event Channel 7
} TC_CLKSEL_t;
	
/// Waveform Generation Mode

typedef enum TC_WGMODE_enum {
	TC_WGMODE_NORMAL_gc = (0x00<<0),	///< Normal Mode
	TC_WGMODE_FRQ_gc = (0x01<<0),	///< Frequency Generation Mode
	TC_WGMODE_SS_gc = (0x03<<0),	///< Single Slope
	TC_WGMODE_DS_T_gc = (0x05<<0),	///< Dual Slope, Update on TOP
	TC_WGMODE_DS_TB_gc = (0x06<<0),	///< Dual Slope, Update on TOP and BOTTOM
	TC_WGMODE_DS_B_gc = (0x07<<0),	///< Dual Slope, Update on BOTTOM
} TC_WGMODE_t;
	
/// Event Action

typedef enum TC_EVACT_enum {
	TC_EVACT_OFF_gc = (0x00<<5),	///< No Event Action
	TC_EVACT_CAPT_gc = (0x01<<5),	///< Input Capture
	TC_EVACT_UPDOWN_gc = (0x02<<5),	///< Externally Controlled Up/Down Count
	TC_EVACT_QDEC_gc = (0x03<<5),	///< Quadrature Decode
	TC_EVACT_RESTART_gc = (0x04<<5),	///< Restart
	TC_EVACT_FRQ_gc = (0x05<<5),	///< Frequency Capture
	TC_EVACT_PW_gc = (0x06<<5),	///< Pulse-width Capture
} TC_EVACT_t;
	
/// Event Selection

typedef enum TC_EVSEL_enum {
	TC_EVSEL_OFF_gc = (0x00<<0),	///< No Event Source
	TC_EVSEL_CH0_gc = (0x08<<0),	///< Event Channel 0
	TC_EVSEL_CH1_gc = (0x09<<0),	///< Event Channel 1
	TC_EVSEL_CH2_gc = (0x0A<<0),	///< Event Channel 2
	TC_EVSEL_CH3_gc = (0x0B<<0),	///< Event Channel 3
	TC_EVSEL_CH4_gc = (0x0C<<0),	///< Event Channel 4
	TC_EVSEL_CH5_gc = (0x0D<<0),	///< Event Channel 5
	TC_EVSEL_CH6_gc = (0x0E<<0),	///< Event Channel 6
	TC_EVSEL_CH7_gc = (0x0F<<0),	///< Event Channel 7
} TC_EVSEL_t;
	
/// Error Interrupt Level

typedef enum TC_ERRINTLVL_enum {
	TC_ERRINTLVL_OFF_gc = (0x00<<2),	///< Interrupt Disabled
	TC_ERRINTLVL_LO_gc = (0x01<<2),	///< Low Level
	TC_ERRINTLVL_MED_gc = (0x02<<2),	///< Medium Level
	TC_ERRINTLVL_HI_gc = (0x03<<2),	///< High Level
} TC_ERRINTLVL_t;
	
/// Overflow Interrupt Level

typedef enum TC_OVFINTLVL_enum {
	TC_OVFINTLVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	TC_OVFINTLVL_LO_gc = (0x01<<0),	///< Low Level
	TC_OVFINTLVL_MED_gc = (0x02<<0),	///< Medium Level
	TC_OVFINTLVL_HI_gc = (0x03<<0),	///< High Level
} TC_OVFINTLVL_t;
	
/// Compare or Capture D Interrupt Level

typedef enum TC_CCDINTLVL_enum {
	TC_CCDINTLVL_OFF_gc = (0x00<<6),	///< Interrupt Disabled
	TC_CCDINTLVL_LO_gc = (0x01<<6),	///< Low Level
	TC_CCDINTLVL_MED_gc = (0x02<<6),	///< Medium Level
	TC_CCDINTLVL_HI_gc = (0x03<<6),	///< High Level
} TC_CCDINTLVL_t;
	
/// Compare or Capture C Interrupt Level

typedef enum TC_CCCINTLVL_enum {
	TC_CCCINTLVL_OFF_gc = (0x00<<4),	///< Interrupt Disabled
	TC_CCCINTLVL_LO_gc = (0x01<<4),	///< Low Level
	TC_CCCINTLVL_MED_gc = (0x02<<4),	///< Medium Level
	TC_CCCINTLVL_HI_gc = (0x03<<4),	///< High Level
} TC_CCCINTLVL_t;
	
/// Compare or Capture B Interrupt Level

typedef enum TC_CCBINTLVL_enum {
	TC_CCBINTLVL_OFF_gc = (0x00<<2),	///< Interrupt Disabled
	TC_CCBINTLVL_LO_gc = (0x01<<2),	///< Low Level
	TC_CCBINTLVL_MED_gc = (0x02<<2),	///< Medium Level
	TC_CCBINTLVL_HI_gc = (0x03<<2),	///< High Level
} TC_CCBINTLVL_t;
	
/// Compare or Capture A Interrupt Level

typedef enum TC_CCAINTLVL_enum {
	TC_CCAINTLVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	TC_CCAINTLVL_LO_gc = (0x01<<0),	///< Low Level
	TC_CCAINTLVL_MED_gc = (0x02<<0),	///< Medium Level
	TC_CCAINTLVL_HI_gc = (0x03<<0),	///< High Level
} TC_CCAINTLVL_t;
	
/// Timer/Counter Command

typedef enum TC_CMD_enum {
	TC_CMD_NONE_gc = (0x00<<2),	///< No Command
	TC_CMD_UPDATE_gc = (0x01<<2),	///< Force Update
	TC_CMD_RESTART_gc = (0x02<<2),	///< Force Restart
	TC_CMD_RESET_gc = (0x03<<2),	///< Force Hard Reset
} TC_CMD_t;
	
/// Fault Detect Action

typedef enum AWEX_FDACT_enum {
	AWEX_FDACT_NONE_gc = (0x00<<0),	///< No Fault Protection
	AWEX_FDACT_CLEAROE_gc = (0x01<<0),	///< Clear Output Enable Bits
	AWEX_FDACT_CLEARDIR_gc = (0x03<<0),	///< Clear I/O Port Direction Bits
} AWEX_FDACT_t;
	
/// High Resolution Enable

typedef enum HIRES_HREN_enum {
	HIRES_HREN_NONE_gc = (0x00<<0),	///< No Fault Protection
	HIRES_HREN_TC0_gc = (0x01<<0),	///< Enable High Resolution on Timer/Counter 0
	HIRES_HREN_TC1_gc = (0x02<<0),	///< Enable High Resolution on Timer/Counter 1
	HIRES_HREN_BOTH_gc = (0x03<<0),	///< Enable High Resolution both Timer/Counters
} HIRES_HREN_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Clock Selection
#define TC_CLKSEL_OFF_gc (0x00<<0)	///< Timer Off
#define TC_CLKSEL_DIV1_gc (0x01<<0)	///< System Clock
#define TC_CLKSEL_DIV2_gc (0x02<<0)	///< System Clock / 2
#define TC_CLKSEL_DIV4_gc (0x03<<0)	///< System Clock / 4
#define TC_CLKSEL_DIV8_gc (0x04<<0)	///< System Clock / 8
#define TC_CLKSEL_DIV64_gc (0x05<<0)	///< System Clock / 64
#define TC_CLKSEL_DIV256_gc (0x06<<0)	///< System Clock / 256
#define TC_CLKSEL_DIV1024_gc (0x07<<0)	///< System Clock / 1024
#define TC_CLKSEL_EVCH0_gc (0x08<<0)	///< Event Channel 0
#define TC_CLKSEL_EVCH1_gc (0x09<<0)	///< Event Channel 1
#define TC_CLKSEL_EVCH2_gc (0x0A<<0)	///< Event Channel 2
#define TC_CLKSEL_EVCH3_gc (0x0B<<0)	///< Event Channel 3
#define TC_CLKSEL_EVCH4_gc (0x0C<<0)	///< Event Channel 4
#define TC_CLKSEL_EVCH5_gc (0x0D<<0)	///< Event Channel 5
#define TC_CLKSEL_EVCH6_gc (0x0E<<0)	///< Event Channel 6
#define TC_CLKSEL_EVCH7_gc (0x0F<<0)	///< Event Channel 7

/// Waveform Generation Mode
#define TC_WGMODE_NORMAL_gc (0x00<<0)	///< Normal Mode
#define TC_WGMODE_FRQ_gc (0x01<<0)	///< Frequency Generation Mode
#define TC_WGMODE_SS_gc (0x03<<0)	///< Single Slope
#define TC_WGMODE_DS_T_gc (0x05<<0)	///< Dual Slope, Update on TOP
#define TC_WGMODE_DS_TB_gc (0x06<<0)	///< Dual Slope, Update on TOP and BOTTOM
#define TC_WGMODE_DS_B_gc (0x07<<0)	///< Dual Slope, Update on BOTTOM

/// Event Action
#define TC_EVACT_OFF_gc (0x00<<5)	///< No Event Action
#define TC_EVACT_CAPT_gc (0x01<<5)	///< Input Capture
#define TC_EVACT_UPDOWN_gc (0x02<<5)	///< Externally Controlled Up/Down Count
#define TC_EVACT_QDEC_gc (0x03<<5)	///< Quadrature Decode
#define TC_EVACT_RESTART_gc (0x04<<5)	///< Restart
#define TC_EVACT_FRQ_gc (0x05<<5)	///< Frequency Capture
#define TC_EVACT_PW_gc (0x06<<5)	///< Pulse-width Capture

/// Event Selection
#define TC_EVSEL_OFF_gc (0x00<<0)	///< No Event Source
#define TC_EVSEL_CH0_gc (0x08<<0)	///< Event Channel 0
#define TC_EVSEL_CH1_gc (0x09<<0)	///< Event Channel 1
#define TC_EVSEL_CH2_gc (0x0A<<0)	///< Event Channel 2
#define TC_EVSEL_CH3_gc (0x0B<<0)	///< Event Channel 3
#define TC_EVSEL_CH4_gc (0x0C<<0)	///< Event Channel 4
#define TC_EVSEL_CH5_gc (0x0D<<0)	///< Event Channel 5
#define TC_EVSEL_CH6_gc (0x0E<<0)	///< Event Channel 6
#define TC_EVSEL_CH7_gc (0x0F<<0)	///< Event Channel 7

/// Error Interrupt Level
#define TC_ERRINTLVL_OFF_gc (0x00<<2)	///< Interrupt Disabled
#define TC_ERRINTLVL_LO_gc (0x01<<2)	///< Low Level
#define TC_ERRINTLVL_MED_gc (0x02<<2)	///< Medium Level
#define TC_ERRINTLVL_HI_gc (0x03<<2)	///< High Level

/// Overflow Interrupt Level
#define TC_OVFINTLVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define TC_OVFINTLVL_LO_gc (0x01<<0)	///< Low Level
#define TC_OVFINTLVL_MED_gc (0x02<<0)	///< Medium Level
#define TC_OVFINTLVL_HI_gc (0x03<<0)	///< High Level

/// Compare or Capture D Interrupt Level
#define TC_CCDINTLVL_OFF_gc (0x00<<6)	///< Interrupt Disabled
#define TC_CCDINTLVL_LO_gc (0x01<<6)	///< Low Level
#define TC_CCDINTLVL_MED_gc (0x02<<6)	///< Medium Level
#define TC_CCDINTLVL_HI_gc (0x03<<6)	///< High Level

/// Compare or Capture C Interrupt Level
#define TC_CCCINTLVL_OFF_gc (0x00<<4)	///< Interrupt Disabled
#define TC_CCCINTLVL_LO_gc (0x01<<4)	///< Low Level
#define TC_CCCINTLVL_MED_gc (0x02<<4)	///< Medium Level
#define TC_CCCINTLVL_HI_gc (0x03<<4)	///< High Level

/// Compare or Capture B Interrupt Level
#define TC_CCBINTLVL_OFF_gc (0x00<<2)	///< Interrupt Disabled
#define TC_CCBINTLVL_LO_gc (0x01<<2)	///< Low Level
#define TC_CCBINTLVL_MED_gc (0x02<<2)	///< Medium Level
#define TC_CCBINTLVL_HI_gc (0x03<<2)	///< High Level

/// Compare or Capture A Interrupt Level
#define TC_CCAINTLVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define TC_CCAINTLVL_LO_gc (0x01<<0)	///< Low Level
#define TC_CCAINTLVL_MED_gc (0x02<<0)	///< Medium Level
#define TC_CCAINTLVL_HI_gc (0x03<<0)	///< High Level

/// Timer/Counter Command
#define TC_CMD_NONE_gc (0x00<<2)	///< No Command
#define TC_CMD_UPDATE_gc (0x01<<2)	///< Force Update
#define TC_CMD_RESTART_gc (0x02<<2)	///< Force Restart
#define TC_CMD_RESET_gc (0x03<<2)	///< Force Hard Reset

/// Fault Detect Action
#define AWEX_FDACT_NONE_gc (0x00<<0)	///< No Fault Protection
#define AWEX_FDACT_CLEAROE_gc (0x01<<0)	///< Clear Output Enable Bits
#define AWEX_FDACT_CLEARDIR_gc (0x03<<0)	///< Clear I/O Port Direction Bits

/// High Resolution Enable
#define HIRES_HREN_NONE_gc (0x00<<0)	///< No Fault Protection
#define HIRES_HREN_TC0_gc (0x01<<0)	///< Enable High Resolution on Timer/Counter 0
#define HIRES_HREN_TC1_gc (0x02<<0)	///< Enable High Resolution on Timer/Counter 1
#define HIRES_HREN_BOTH_gc (0x03<<0)	///< Enable High Resolution both Timer/Counters

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup usart Universal Asynchronous Receiver-Transmitter
 *  @{
 */
	
/** @name USART.STATUS
  * @{
  */
#define USART_RXCIF_bm 0x80 ///< Receive Interrupt Flag bit mask
#define USART_RXCIF_bp 7 ///< Receive Interrupt Flag bit position
#define USART_TXCIF_bm 0x40 ///< Transmit Interrupt Flag bit mask
#define USART_TXCIF_bp 6 ///< Transmit Interrupt Flag bit position
#define USART_DREIF_bm 0x20 ///< Data Register Empty Flag bit mask
#define USART_DREIF_bp 5 ///< Data Register Empty Flag bit position
#define USART_FERR_bm 0x10 ///< Frame Error bit mask
#define USART_FERR_bp 4 ///< Frame Error bit position
#define USART_BUFOVF_bm 0x08 ///< Buffer Overflow bit mask
#define USART_BUFOVF_bp 3 ///< Buffer Overflow bit position
#define USART_PERR_bm 0x04 ///< Parity Error bit mask
#define USART_PERR_bp 2 ///< Parity Error bit position
#define USART_RXB8_bm 0x01 ///< Receive Bit 8 bit mask
#define USART_RXB8_bp 0 ///< Receive Bit 8 bit position
/** @} */
	
/** @name USART.CTRLA
  * @see USART_RXCINTLVL_enum
  * @see USART_TXCINTLVL_enum
  * @see USART_DREINTLVL_enum
  * @{
  */
#define USART_RXCINTLVL_gm 0x30 ///< Receive Interrupt Level group mask
#define USART_RXCINTLVL_gp 4 ///< Receive Interrupt Level group position
#define USART_RXCINTLVL0_bm (1<<4) ///< Receive Interrupt Level bit 0 mask
#define USART_RXCINTLVL0_bp 4 ///< Receive Interrupt Level bit 0 position
#define USART_RXCINTLVL1_bm (1<<5) ///< Receive Interrupt Level bit 1 mask
#define USART_RXCINTLVL1_bp 5 ///< Receive Interrupt Level bit 1 position
#define USART_TXCINTLVL_gm 0x0C ///< Transmit Interrupt Level group mask
#define USART_TXCINTLVL_gp 2 ///< Transmit Interrupt Level group position
#define USART_TXCINTLVL0_bm (1<<2) ///< Transmit Interrupt Level bit 0 mask
#define USART_TXCINTLVL0_bp 2 ///< Transmit Interrupt Level bit 0 position
#define USART_TXCINTLVL1_bm (1<<3) ///< Transmit Interrupt Level bit 1 mask
#define USART_TXCINTLVL1_bp 3 ///< Transmit Interrupt Level bit 1 position
#define USART_DREINTLVL_gm 0x03 ///< Data Register Empty Interrupt Level group mask
#define USART_DREINTLVL_gp 0 ///< Data Register Empty Interrupt Level group position
#define USART_DREINTLVL0_bm (1<<0) ///< Data Register Empty Interrupt Level bit 0 mask
#define USART_DREINTLVL0_bp 0 ///< Data Register Empty Interrupt Level bit 0 position
#define USART_DREINTLVL1_bm (1<<1) ///< Data Register Empty Interrupt Level bit 1 mask
#define USART_DREINTLVL1_bp 1 ///< Data Register Empty Interrupt Level bit 1 position
/** @} */
	
/** @name USART.CTRLB
  * @{
  */
#define USART_RXEN_bm 0x10 ///< Receiver Enable bit mask
#define USART_RXEN_bp 4 ///< Receiver Enable bit position
#define USART_TXEN_bm 0x08 ///< Transmitter Enable bit mask
#define USART_TXEN_bp 3 ///< Transmitter Enable bit position
#define USART_CLK2X_bm 0x04 ///< Double transmission speed bit mask
#define USART_CLK2X_bp 2 ///< Double transmission speed bit position
#define USART_MPCM_bm 0x02 ///< Multi-processor Communication Mode bit mask
#define USART_MPCM_bp 1 ///< Multi-processor Communication Mode bit position
#define USART_TXB8_bm 0x01 ///< Transmit bit 8 bit mask
#define USART_TXB8_bp 0 ///< Transmit bit 8 bit position
/** @} */
	
/** @name USART.CTRLC
  * @see USART_CMODE_enum
  * @see USART_PMODE_enum
  * @see USART_CHSIZE_enum
  * @{
  */
#define USART_CMODE_gm 0xC0 ///< Communication Mode group mask
#define USART_CMODE_gp 6 ///< Communication Mode group position
#define USART_CMODE0_bm (1<<6) ///< Communication Mode bit 0 mask
#define USART_CMODE0_bp 6 ///< Communication Mode bit 0 position
#define USART_CMODE1_bm (1<<7) ///< Communication Mode bit 1 mask
#define USART_CMODE1_bp 7 ///< Communication Mode bit 1 position
#define USART_PMODE_gm 0x30 ///< Parity Mode group mask
#define USART_PMODE_gp 4 ///< Parity Mode group position
#define USART_PMODE0_bm (1<<4) ///< Parity Mode bit 0 mask
#define USART_PMODE0_bp 4 ///< Parity Mode bit 0 position
#define USART_PMODE1_bm (1<<5) ///< Parity Mode bit 1 mask
#define USART_PMODE1_bp 5 ///< Parity Mode bit 1 position
#define USART_SBMODE_bm 0x08 ///< Stop Bit Mode bit mask
#define USART_SBMODE_bp 3 ///< Stop Bit Mode bit position
#define USART_CHSIZE_gm 0x07 ///< Character Size group mask
#define USART_CHSIZE_gp 0 ///< Character Size group position
#define USART_CHSIZE0_bm (1<<0) ///< Character Size bit 0 mask
#define USART_CHSIZE0_bp 0 ///< Character Size bit 0 position
#define USART_CHSIZE1_bm (1<<1) ///< Character Size bit 1 mask
#define USART_CHSIZE1_bp 1 ///< Character Size bit 1 position
#define USART_CHSIZE2_bm (1<<2) ///< Character Size bit 2 mask
#define USART_CHSIZE2_bp 2 ///< Character Size bit 2 position
/** @} */
	
/** @name USART.BAUDCTRLA
  * @{
  */
#define USART_BSEL_gm 0xFF ///< Baud Rate Selection Bits [7:0] group mask
#define USART_BSEL_gp 0 ///< Baud Rate Selection Bits [7:0] group position
#define USART_BSEL0_bm (1<<0) ///< Baud Rate Selection Bits [7:0] bit 0 mask
#define USART_BSEL0_bp 0 ///< Baud Rate Selection Bits [7:0] bit 0 position
#define USART_BSEL1_bm (1<<1) ///< Baud Rate Selection Bits [7:0] bit 1 mask
#define USART_BSEL1_bp 1 ///< Baud Rate Selection Bits [7:0] bit 1 position
#define USART_BSEL2_bm (1<<2) ///< Baud Rate Selection Bits [7:0] bit 2 mask
#define USART_BSEL2_bp 2 ///< Baud Rate Selection Bits [7:0] bit 2 position
#define USART_BSEL3_bm (1<<3) ///< Baud Rate Selection Bits [7:0] bit 3 mask
#define USART_BSEL3_bp 3 ///< Baud Rate Selection Bits [7:0] bit 3 position
#define USART_BSEL4_bm (1<<4) ///< Baud Rate Selection Bits [7:0] bit 4 mask
#define USART_BSEL4_bp 4 ///< Baud Rate Selection Bits [7:0] bit 4 position
#define USART_BSEL5_bm (1<<5) ///< Baud Rate Selection Bits [7:0] bit 5 mask
#define USART_BSEL5_bp 5 ///< Baud Rate Selection Bits [7:0] bit 5 position
#define USART_BSEL6_bm (1<<6) ///< Baud Rate Selection Bits [7:0] bit 6 mask
#define USART_BSEL6_bp 6 ///< Baud Rate Selection Bits [7:0] bit 6 position
#define USART_BSEL7_bm (1<<7) ///< Baud Rate Selection Bits [7:0] bit 7 mask
#define USART_BSEL7_bp 7 ///< Baud Rate Selection Bits [7:0] bit 7 position
/** @} */
	
/** @name USART.BAUDCTRLB
  * @{
  */
#define USART_BSCALE_gm 0xF0 ///< Baud Rate Scale group mask
#define USART_BSCALE_gp 4 ///< Baud Rate Scale group position
#define USART_BSCALE0_bm (1<<4) ///< Baud Rate Scale bit 0 mask
#define USART_BSCALE0_bp 4 ///< Baud Rate Scale bit 0 position
#define USART_BSCALE1_bm (1<<5) ///< Baud Rate Scale bit 1 mask
#define USART_BSCALE1_bp 5 ///< Baud Rate Scale bit 1 position
#define USART_BSCALE2_bm (1<<6) ///< Baud Rate Scale bit 2 mask
#define USART_BSCALE2_bp 6 ///< Baud Rate Scale bit 2 position
#define USART_BSCALE3_bm (1<<7) ///< Baud Rate Scale bit 3 mask
#define USART_BSCALE3_bp 7 ///< Baud Rate Scale bit 3 position
// Masks for BSEL aready defined
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Receive Complete Interrupt level

typedef enum USART_RXCINTLVL_enum {
	USART_RXCINTLVL_OFF_gc = (0x00<<4),	///< Interrupt Disabled
	USART_RXCINTLVL_LO_gc = (0x01<<4),	///< Low Level
	USART_RXCINTLVL_MED_gc = (0x02<<4),	///< Medium Level
	USART_RXCINTLVL_HI_gc = (0x03<<4),	///< High Level
} USART_RXCINTLVL_t;
	
/// Transmit Complete Interrupt level

typedef enum USART_TXCINTLVL_enum {
	USART_TXCINTLVL_OFF_gc = (0x00<<2),	///< Interrupt Disabled
	USART_TXCINTLVL_LO_gc = (0x01<<2),	///< Low Level
	USART_TXCINTLVL_MED_gc = (0x02<<2),	///< Medium Level
	USART_TXCINTLVL_HI_gc = (0x03<<2),	///< High Level
} USART_TXCINTLVL_t;
	
/// Data Register Empty Interrupt level

typedef enum USART_DREINTLVL_enum {
	USART_DREINTLVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	USART_DREINTLVL_LO_gc = (0x01<<0),	///< Low Level
	USART_DREINTLVL_MED_gc = (0x02<<0),	///< Medium Level
	USART_DREINTLVL_HI_gc = (0x03<<0),	///< High Level
} USART_DREINTLVL_t;
	
/// Character Size

typedef enum USART_CHSIZE_enum {
	USART_CHSIZE_5BIT_gc = (0x00<<0),	///< Character size: 5 bit
	USART_CHSIZE_6BIT_gc = (0x01<<0),	///< Character size: 6 bit
	USART_CHSIZE_7BIT_gc = (0x02<<0),	///< Character size: 7 bit
	USART_CHSIZE_8BIT_gc = (0x03<<0),	///< Character size: 8 bit
	USART_CHSIZE_9BIT_gc = (0x07<<0),	///< Character size: 9 bit
} USART_CHSIZE_t;
	
/// Communication Mode

typedef enum USART_CMODE_enum {
	USART_CMODE_ASYNCHRONOUS_gc = (0x00<<6),	///< Asynchronous Mode
	USART_CMODE_SYNCHRONOUS_gc = (0x01<<6),	///< Synchronous Mode
	USART_CMODE_IRDA_gc = (0x02<<6),	///< IrDA Mode
	USART_CMODE_MSPI_gc = (0x03<<6),	///< Master SPI Mode
} USART_CMODE_t;
	
/// Parity Mode

typedef enum USART_PMODE_enum {
	USART_PMODE_DISABLED_gc = (0x00<<4),	///< No Parity
	USART_PMODE_EVEN_gc = (0x02<<4),	///< Even Parity
	USART_PMODE_ODD_gc = (0x03<<4),	///< Odd Parity
} USART_PMODE_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Receive Complete Interrupt level
#define USART_RXCINTLVL_OFF_gc (0x00<<4)	///< Interrupt Disabled
#define USART_RXCINTLVL_LO_gc (0x01<<4)	///< Low Level
#define USART_RXCINTLVL_MED_gc (0x02<<4)	///< Medium Level
#define USART_RXCINTLVL_HI_gc (0x03<<4)	///< High Level

/// Transmit Complete Interrupt level
#define USART_TXCINTLVL_OFF_gc (0x00<<2)	///< Interrupt Disabled
#define USART_TXCINTLVL_LO_gc (0x01<<2)	///< Low Level
#define USART_TXCINTLVL_MED_gc (0x02<<2)	///< Medium Level
#define USART_TXCINTLVL_HI_gc (0x03<<2)	///< High Level

/// Data Register Empty Interrupt level
#define USART_DREINTLVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define USART_DREINTLVL_LO_gc (0x01<<0)	///< Low Level
#define USART_DREINTLVL_MED_gc (0x02<<0)	///< Medium Level
#define USART_DREINTLVL_HI_gc (0x03<<0)	///< High Level

/// Character Size
#define USART_CHSIZE_5BIT_gc (0x00<<0)	///< Character size: 5 bit
#define USART_CHSIZE_6BIT_gc (0x01<<0)	///< Character size: 6 bit
#define USART_CHSIZE_7BIT_gc (0x02<<0)	///< Character size: 7 bit
#define USART_CHSIZE_8BIT_gc (0x03<<0)	///< Character size: 8 bit
#define USART_CHSIZE_9BIT_gc (0x07<<0)	///< Character size: 9 bit

/// Communication Mode
#define USART_CMODE_ASYNCHRONOUS_gc (0x00<<6)	///< Asynchronous Mode
#define USART_CMODE_SYNCHRONOUS_gc (0x01<<6)	///< Synchronous Mode
#define USART_CMODE_IRDA_gc (0x02<<6)	///< IrDA Mode
#define USART_CMODE_MSPI_gc (0x03<<6)	///< Master SPI Mode

/// Parity Mode
#define USART_PMODE_DISABLED_gc (0x00<<4)	///< No Parity
#define USART_PMODE_EVEN_gc (0x02<<4)	///< Even Parity
#define USART_PMODE_ODD_gc (0x03<<4)	///< Odd Parity

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup spi Serial Peripheral Interface
 *  @{
 */
	
/** @name SPI.CTRL
  * @see SPI_MODE_enum
  * @see SPI_PRESCALER_enum
  * @{
  */
#define SPI_CLK2X_bm 0x80 ///< Enable Double Speed bit mask
#define SPI_CLK2X_bp 7 ///< Enable Double Speed bit position
#define SPI_ENABLE_bm 0x40 ///< Enable Module bit mask
#define SPI_ENABLE_bp 6 ///< Enable Module bit position
#define SPI_DORD_bm 0x20 ///< Data Order Setting bit mask
#define SPI_DORD_bp 5 ///< Data Order Setting bit position
#define SPI_MASTER_bm 0x10 ///< Master Operation Enable bit mask
#define SPI_MASTER_bp 4 ///< Master Operation Enable bit position
#define SPI_MODE_gm 0x0C ///< SPI Mode group mask
#define SPI_MODE_gp 2 ///< SPI Mode group position
#define SPI_MODE0_bm (1<<2) ///< SPI Mode bit 0 mask
#define SPI_MODE0_bp 2 ///< SPI Mode bit 0 position
#define SPI_MODE1_bm (1<<3) ///< SPI Mode bit 1 mask
#define SPI_MODE1_bp 3 ///< SPI Mode bit 1 position
#define SPI_PRESCALER_gm 0x03 ///< Prescaler group mask
#define SPI_PRESCALER_gp 0 ///< Prescaler group position
#define SPI_PRESCALER0_bm (1<<0) ///< Prescaler bit 0 mask
#define SPI_PRESCALER0_bp 0 ///< Prescaler bit 0 position
#define SPI_PRESCALER1_bm (1<<1) ///< Prescaler bit 1 mask
#define SPI_PRESCALER1_bp 1 ///< Prescaler bit 1 position
/** @} */
	
/** @name SPI.INTCTRL
  * @see SPI_INTLVL_enum
  * @{
  */
#define SPI_INTLVL_gm 0x03 ///< Interrupt level group mask
#define SPI_INTLVL_gp 0 ///< Interrupt level group position
#define SPI_INTLVL0_bm (1<<0) ///< Interrupt level bit 0 mask
#define SPI_INTLVL0_bp 0 ///< Interrupt level bit 0 position
#define SPI_INTLVL1_bm (1<<1) ///< Interrupt level bit 1 mask
#define SPI_INTLVL1_bp 1 ///< Interrupt level bit 1 position
/** @} */
	
/** @name SPI.STATUS
  * @{
  */
#define SPI_IF_bm 0x80 ///< Interrupt Flag bit mask
#define SPI_IF_bp 7 ///< Interrupt Flag bit position
#define SPI_WRCOL_bm 0x40 ///< Write Collision bit mask
#define SPI_WRCOL_bp 6 ///< Write Collision bit position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// SPI Mode

typedef enum SPI_MODE_enum {
	SPI_MODE_0_gc = (0x00<<2),	///< SPI Mode 0
	SPI_MODE_1_gc = (0x01<<2),	///< SPI Mode 1
	SPI_MODE_2_gc = (0x02<<2),	///< SPI Mode 2
	SPI_MODE_3_gc = (0x03<<2),	///< SPI Mode 3
} SPI_MODE_t;
	
/// Prescaler setting

typedef enum SPI_PRESCALER_enum {
	SPI_PRESCALER_DIV4_gc = (0x00<<0),	///< System Clock / 4
	SPI_PRESCALER_DIV16_gc = (0x01<<0),	///< System Clock / 16
	SPI_PRESCALER_DIV64_gc = (0x02<<0),	///< System Clock / 64
	SPI_PRESCALER_DIV128_gc = (0x03<<0),	///< System Clock / 128
} SPI_PRESCALER_t;
	
/// Interrupt level

typedef enum SPI_INTLVL_enum {
	SPI_INTLVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	SPI_INTLVL_LO_gc = (0x01<<0),	///< Low Level
	SPI_INTLVL_MED_gc = (0x02<<0),	///< Medium Level
	SPI_INTLVL_HI_gc = (0x03<<0),	///< High Level
} SPI_INTLVL_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// SPI Mode
#define SPI_MODE_0_gc (0x00<<2)	///< SPI Mode 0
#define SPI_MODE_1_gc (0x01<<2)	///< SPI Mode 1
#define SPI_MODE_2_gc (0x02<<2)	///< SPI Mode 2
#define SPI_MODE_3_gc (0x03<<2)	///< SPI Mode 3

/// Prescaler setting
#define SPI_PRESCALER_DIV4_gc (0x00<<0)	///< System Clock / 4
#define SPI_PRESCALER_DIV16_gc (0x01<<0)	///< System Clock / 16
#define SPI_PRESCALER_DIV64_gc (0x02<<0)	///< System Clock / 64
#define SPI_PRESCALER_DIV128_gc (0x03<<0)	///< System Clock / 128

/// Interrupt level
#define SPI_INTLVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define SPI_INTLVL_LO_gc (0x01<<0)	///< Low Level
#define SPI_INTLVL_MED_gc (0x02<<0)	///< Medium Level
#define SPI_INTLVL_HI_gc (0x03<<0)	///< High Level

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup ircom IR Communication Module
 *  @{
 */
	
/** @name IRCOM.CTRL
  * @see IRDA_EVSEL_enum
  * @{
  */
#define IRCOM_EVSEL_gm 0x0F ///< Event Channel Select group mask
#define IRCOM_EVSEL_gp 0 ///< Event Channel Select group position
#define IRCOM_EVSEL0_bm (1<<0) ///< Event Channel Select bit 0 mask
#define IRCOM_EVSEL0_bp 0 ///< Event Channel Select bit 0 position
#define IRCOM_EVSEL1_bm (1<<1) ///< Event Channel Select bit 1 mask
#define IRCOM_EVSEL1_bp 1 ///< Event Channel Select bit 1 position
#define IRCOM_EVSEL2_bm (1<<2) ///< Event Channel Select bit 2 mask
#define IRCOM_EVSEL2_bp 2 ///< Event Channel Select bit 2 position
#define IRCOM_EVSEL3_bm (1<<3) ///< Event Channel Select bit 3 mask
#define IRCOM_EVSEL3_bp 3 ///< Event Channel Select bit 3 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Event channel selection

typedef enum IRDA_EVSEL_enum {
	IRDA_EVSEL_OFF_gc = (0x00<<0),	///< No Event Source
	IRDA_EVSEL_0_gc = (0x08<<0),	///< Event Channel 0
	IRDA_EVSEL_1_gc = (0x09<<0),	///< Event Channel 1
	IRDA_EVSEL_2_gc = (0x0A<<0),	///< Event Channel 2
	IRDA_EVSEL_3_gc = (0x0B<<0),	///< Event Channel 3
	IRDA_EVSEL_4_gc = (0x0C<<0),	///< Event Channel 4
	IRDA_EVSEL_5_gc = (0x0D<<0),	///< Event Channel 5
	IRDA_EVSEL_6_gc = (0x0E<<0),	///< Event Channel 6
	IRDA_EVSEL_7_gc = (0x0F<<0),	///< Event Channel 7
} IRDA_EVSEL_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Event channel selection
#define IRDA_EVSEL_OFF_gc (0x00<<0)	///< No Event Source
#define IRDA_EVSEL_0_gc (0x08<<0)	///< Event Channel 0
#define IRDA_EVSEL_1_gc (0x09<<0)	///< Event Channel 1
#define IRDA_EVSEL_2_gc (0x0A<<0)	///< Event Channel 2
#define IRDA_EVSEL_3_gc (0x0B<<0)	///< Event Channel 3
#define IRDA_EVSEL_4_gc (0x0C<<0)	///< Event Channel 4
#define IRDA_EVSEL_5_gc (0x0D<<0)	///< Event Channel 5
#define IRDA_EVSEL_6_gc (0x0E<<0)	///< Event Channel 6
#define IRDA_EVSEL_7_gc (0x0F<<0)	///< Event Channel 7

#endif //defined(__IAR_SYSTEMS_ASM__)


/** @addtogroup aes AES Module
 *  @{
 */
	
/** @name AES.CTRL
  * @{
  */
#define AES_START_bm 0x80 ///< Start/Run bit mask
#define AES_START_bp 7 ///< Start/Run bit position
#define AES_AUTO_bm 0x40 ///< Auto Start Trigger bit mask
#define AES_AUTO_bp 6 ///< Auto Start Trigger bit position
#define AES_RESET_bm 0x20 ///< AES Software Reset bit mask
#define AES_RESET_bp 5 ///< AES Software Reset bit position
#define AES_DECRYPT_bm 0x10 ///< Decryption / Direction bit mask
#define AES_DECRYPT_bp 4 ///< Decryption / Direction bit position
#define AES_XOR_bm 0x04 ///< State XOR Load Enable bit mask
#define AES_XOR_bp 2 ///< State XOR Load Enable bit position
/** @} */
	
/** @name AES.STATUS
  * @{
  */
#define AES_ERROR_bm 0x80 ///< AES Error bit mask
#define AES_ERROR_bp 7 ///< AES Error bit position
#define AES_SRIF_bm 0x01 ///< State Ready Interrupt Flag bit mask
#define AES_SRIF_bp 0 ///< State Ready Interrupt Flag bit position
/** @} */
	
/** @name AES.INTCTRL
  * @see AES_INTLVL_enum
  * @{
  */
#define AES_INTLVL_gm 0x03 ///< Interrupt level group mask
#define AES_INTLVL_gp 0 ///< Interrupt level group position
#define AES_INTLVL0_bm (1<<0) ///< Interrupt level bit 0 mask
#define AES_INTLVL0_bp 0 ///< Interrupt level bit 0 position
#define AES_INTLVL1_bm (1<<1) ///< Interrupt level bit 1 mask
#define AES_INTLVL1_bp 1 ///< Interrupt level bit 1 position
/** @} */
	

#if defined(__IAR_SYSTEMS_ICC__)
 	
/// Interrupt level

typedef enum AES_INTLVL_enum {
	AES_INTLVL_OFF_gc = (0x00<<0),	///< Interrupt Disabled
	AES_INTLVL_LO_gc = (0x01<<0),	///< Low Level
	AES_INTLVL_MED_gc = (0x02<<0),	///< Medium Level
	AES_INTLVL_HI_gc = (0x03<<0),	///< High Level
} AES_INTLVL_t;
	
#endif // defined(__IAR_SYSTEMS_ICC__)

/** @} */


#if defined(__IAR_SYSTEMS_ASM__)
	
/// Interrupt level
#define AES_INTLVL_OFF_gc (0x00<<0)	///< Interrupt Disabled
#define AES_INTLVL_LO_gc (0x01<<0)	///< Low Level
#define AES_INTLVL_MED_gc (0x02<<0)	///< Medium Level
#define AES_INTLVL_HI_gc (0x03<<0)	///< High Level

#endif //defined(__IAR_SYSTEMS_ASM__)



// Port pins

#define PIN0_bm 0x01 
#define PIN0_bp 0
#define PIN1_bm 0x02
#define PIN1_bp 1
#define PIN2_bm 0x04 
#define PIN2_bp 2
#define PIN3_bm 0x08 
#define PIN3_bp 3
#define PIN4_bm 0x10 
#define PIN4_bp 4
#define PIN5_bm 0x20 
#define PIN5_bp 5
#define PIN6_bm 0x40 
#define PIN6_bp 6
#define PIN7_bm 0x80 
#define PIN7_bp 7


/*============================================================*/
/* Other definitions                                          */
/*============================================================*/

/* Pointer definitions */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

#if defined(__IAR_SYSTEMS_ICC__)

/* Offset definitions for Production Signatures */
typedef enum NVM_PROD_SIGNATURES_offsets {
	RCOSC2M_offset = 0x00, ///< RCOSC 2MHz Calibration Value
	RCOSC32K_offset = 0x02, ///< RCOSC 32kHz Calibration Value
	RCOSC32M_offset = 0x03, ///< RCOSC 32MHz Calibration Value
	LOTNUM0_offset = 0x08, ///< Lot Number Byte 0, ASCII
	LOTNUM1_offset = 0x09, ///< Lot Number Byte 1, ASCII
	LOTNUM2_offset = 0x0A, ///< Lot Number Byte 2, ASCII
	LOTNUM3_offset = 0x0B, ///< Lot Number Byte 3, ASCII
	LOTNUM4_offset = 0x0C, ///< Lot Number Byte 4, ASCII
	LOTNUM5_offset = 0x0D, ///< Lot Number Byte 5, ASCII
	WAFNUM_offset = 0x10, ///< Wafer Number
	COORDX0_offset = 0x12, ///< Wafer Coordinate X Byte 0
	COORDX1_offset = 0x13, ///< Wafer Coordinate X Byte 1
	COORDY0_offset = 0x14, ///< Wafer Coordinate Y Byte 0
	COORDY1_offset = 0x15, ///< Wafer Coordinate Y Byte 1
	ADCACAL0_offset = 0x20, ///< ADCA Calibration Byte 0
	ADCACAL1_offset = 0x21, ///< ADCA Calibration Byte 1
	ADCBCAL0_offset = 0x24, ///< ADCB Calibration Byte 0
	ADCBCAL1_offset = 0x25, ///< ADCB Calibration Byte 1
	TEMPSENSE0_offset = 0x2E, ///< Temperature Sensor Calibration Byte 0
	TEMPSENSE1_offset = 0x2F, ///< Temperature Sensor Calibration Byte 0
} NVM_PROD_SIGNATURES_offsets_t;

#endif //defined(__IAR_SYSTEMS_ICC__)


/* Contants */

#define PROGMEM_START 0x0000
#define PROGMEM_SIZE 0x9000
#define PROGMEM_END (0x0000 + 0x9000 - 1)

#define APP_SECTION_START 0x0000
#define APP_SECTION_SIZE 0x8000
#define APP_SECTION_END (0x0000 + 0x8000 - 1)

#define APPTABLE_SECTION_START 0x07000
#define APPTABLE_SECTION_SIZE 0x1000
#define APPTABLE_SECTION_END (0x07000 + 0x1000 - 1)

#define BOOT_SECTION_START 0x8000
#define BOOT_SECTION_SIZE 0x1000
#define BOOT_SECTION_END (0x8000 + 0x1000 - 1)

#define DATAMEM_START 0x0000
#define DATAMEM_SIZE 0x3000
#define DATAMEM_END (0x0000 + 0x3000 - 1)

#define IO_START 0x0000
#define IO_SIZE 0x1000
#define IO_END (0x0000 + 0x1000 - 1)

#define MAPPED_EEPROM_START 0x1000
#define MAPPED_EEPROM_SIZE 0x0400
#define MAPPED_EEPROM_END (0x1000 + 0x0400 - 1)

#define INTERNAL_SRAM_START 0x2000
#define INTERNAL_SRAM_SIZE 0x1000
#define INTERNAL_SRAM_END (0x2000 + 0x1000 - 1)

#define EEPROM_START 0x0000
#define EEPROM_SIZE 0x0400
#define EEPROM_END (0x0000 + 0x0400 - 1)

#define FUSE_START 0x0000
#define FUSE_SIZE 0x0006
#define FUSE_END (0x0000 + 0x0006 - 1)

#define LOCKBIT_START 0x0000
#define LOCKBIT_SIZE 0x0001
#define LOCKBIT_END (0x0000 + 0x0001 - 1)

#define SIGNATURES_START 0x0000
#define SIGNATURES_SIZE 0x0003
#define SIGNATURES_END (0x0000 + 0x0003 - 1)

#define USER_SIGNATURES_START 0x0000
#define USER_SIGNATURES_SIZE 0x0100
#define USER_SIGNATURES_END (0x0000 + 0x0100 - 1)

#define PROD_SIGNATURES_START 0x0000
#define PROD_SIGNATURES_SIZE 0x0034
#define PROD_SIGNATURES_END (0x0000 + 0x0034 - 1)

#define    RAMEND     INTERNAL_SRAM_END
#define    XRAMEND    EXTERNAL_SRAM_END
#define    E2END      EEPROM_END
#define    FLASHEND   PROGMEM_END


#endif /* ENABLE_BIT_DEFINITIONS */ 
#endif /* __ATxmega32A4_H (define part) */
#endif /* __ATxmega32A4_H (SFR part) */

#ifdef __IAR_SYSTEMS_ICC__
#pragma language=restore
#endif
