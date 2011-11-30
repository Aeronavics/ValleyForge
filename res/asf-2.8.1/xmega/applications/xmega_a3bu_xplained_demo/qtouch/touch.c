#include <compiler.h>
#include <parts.h>
#include <board.h>
#include <ioport.h>
#include "touch_api.h"


#ifdef _DEBUG_INTERFACE_
/* Include files for QTouch Studio integration */
#include "QDebug.h"
#include "QDebugTransport.h"
#endif

/* Stuff that is passed to the compiler
 * _QTOUCH_
 * SNS=F
 * SNSK=F
 * _SNS1_SNSK1_SAME_PORT_
 * QT_DELAY_CYCLES=1 (at 2MHz CPU freq this is 0.5us)
 * QT_NUM_CHANNELS=4
 * QTOUCH_STUDIO_MASKS=1
 * NUMBER_OF_PORTS=1
 */

#define GET_SENSOR_STATE(SENSOR_NUMBER) qt_measure_data.qt_touch_status.sensor_states[(SENSOR_NUMBER/8)] & (1 << (SENSOR_NUMBER % 8))

/* Timer period in msec. */
uint16_t qt_measurement_period_msec = 25;


/* This configuration data structure parameters if needs to be changed will be
   changed in the qt_set_parameters function */
extern qt_touch_lib_config_data_t qt_config_data;
/* touch output - measurement data */
extern qt_touch_lib_measure_data_t qt_measure_data;
/* Get sensor delta values */
extern int16_t qt_get_sensor_delta( uint8_t sensor);
#ifdef QTOUCH_STUDIO_MASKS
extern TOUCH_DATA_T SNS_array[2][2];
extern TOUCH_DATA_T SNSK_array[2][2];
#endif
/* Output can be observed in the watch window using this pointer */
qt_touch_lib_measure_data_t *pqt_measure_data = &qt_measure_data;

/* flag set by timer ISR when it's time to measure touch */
static volatile bool time_to_measure_touch = false;

/* current time, set by timer ISR */
static volatile uint16_t current_time_ms_touch = 0;


/** \brief Passes default parameters from config file to touch library
 */
static void qt_set_parameters( void )
{
    qt_config_data.qt_di              = DEF_QT_DI;
    qt_config_data.qt_neg_drift_rate  = DEF_QT_NEG_DRIFT_RATE;
    qt_config_data.qt_pos_drift_rate  = DEF_QT_POS_DRIFT_RATE;
    qt_config_data.qt_max_on_duration = DEF_QT_MAX_ON_DURATION;
    qt_config_data.qt_drift_hold_time = DEF_QT_DRIFT_HOLD_TIME;
    qt_config_data.qt_recal_threshold = DEF_QT_RECAL_THRESHOLD;
    qt_config_data.qt_pos_recal_delay = DEF_QT_POS_RECAL_DELAY;
}

static void config_sensor(void)
{
	/* The sensor is wired up with SNS=PF6 and SNSK=PF7
	 * When using "pin configurability" this will result in channel 0
	 * because it is the first and only channel that is used.
	 * For the standard qtouch library setup we would need to use
	 * channel 3 since we are using the last two pins on the port.
	 */
	 qt_enable_key(CHANNEL_0, NO_AKS_GROUP, 10, HYST_6_25);
}

static void init_timer_isr( void )
{
	PR.PRPC &= ~(0x02);
	/* We divide the peripheral 2MHz clock by 2 to get 1MHz*/
	TCC1.CTRLA = 2;
	/* 1000 counts is 1ms at 1MHz input clock */
	TCC1.PER = 1000 * qt_measurement_period_msec;
	/*  Set Compare A interrupt to low level   */
	TCC1.INTCTRLB = 1;
}

ISR(TCC1_CCA_vect)
{
    time_to_measure_touch = true;
    current_time_ms_touch += qt_measurement_period_msec;
}

/** \brief Configures touch library and measurement setup
 *
 * @pre Interrupts must be enabled in order to trigger regular measurements
 * The touch configuration requires a fixed CPU speed to work properly in this
 * case we need 2 MHz.
 */
void touch_init(void)
{

#ifdef QTOUCH_STUDIO_MASKS
	SNS_array[0][0]= 0x40;
	SNS_array[0][1]= 0x0;
	SNS_array[1][0]= 0x0;
	SNS_array[1][1]= 0x0;

	SNSK_array[0][0]= 0x80;
	SNSK_array[0][1]= 0x0;
	SNSK_array[1][0]= 0x0;
	SNSK_array[1][1]= 0x0;
#endif

	config_sensor();
	qt_init_sensing();
	qt_set_parameters();
	init_timer_isr();

	/* Set up callback function. This function is called after the library
	 * has made capacitive measurements, but before it has processed them.
	 * The user can use this hook to apply filter functions to the measured
	 * signal values.(Possibly to fix sensor layout faults)
	 */
	qt_filter_callback = 0;

#ifdef _DEBUG_INTERFACE_
    QDebug_Init();
#endif
}

bool check_touch_key_pressed(void)
{
    uint16_t status_flag;
    uint16_t burst_flag;    
 
#ifdef _DEBUG_INTERFACE_ 
    /* Process commands from PC */
    QDebug_ProcessCommands();    
#endif

	if (time_to_measure_touch)
	{
		time_to_measure_touch = false;

		do {
			status_flag = qt_measure_sensors( current_time_ms_touch );
			burst_flag = status_flag & QTLIB_BURST_AGAIN;

#ifdef _DEBUG_INTERFACE_                 
			QDebug_SendData(status_flag);
#endif
		/* Time-critical host application code should be placed here since
		 * a full burst cycle may delay critical task in the main application
		 */

		}while (burst_flag) ;

#ifdef _DEBUG_INTERFACE_             
		/* Process commands from PC */
		QDebug_ProcessCommands(); 
#endif            
	}
	if(GET_SENSOR_STATE(0))
		return 0;
	else
		return 1;
}
