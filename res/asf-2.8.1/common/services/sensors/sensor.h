/**
 * \file
 *
 * \brief Atmel AVR and 32-bit AVR Common Sensor API.
 *
 * The sensor device service provides high-level interfaces and binary driver
 * libraries for sensor devices on systems built around UC3 and XMEGA
 * microcontrollers.
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */


#ifndef _sensor_h_
#define _sensor_h_


// Sensor API Definitions

#include    "physics/physics.h"
#include    "sensor_bus.h"
#include    "sensor_nvram.h"
#include    "sensor_wait.h"


#ifdef __cplusplus
extern "C" {
#endif


// Atmel Software Framework (ASF) Interfaces

#include    <gpio.h>


//! \brief Generic Sensor API Descriptor

typedef struct sensor_desc sensor_t;


//! \brief Sensor Hardware Abstraction Descriptor

typedef struct sensor_hal sensor_hal_t;


//! \brief Sensor Type Constants

typedef enum {

	SENSOR_TYPE_UNKNOWN,            //!< unknown or unspecified sensor
	SENSOR_TYPE_ACCELEROMETER,      //!< single- or multi-axis accelerometer
	SENSOR_TYPE_BAROMETER,          //!< atmospheric air pressure
	SENSOR_TYPE_COMPASS,            //!< single - or multi-axis compass
	SENSOR_TYPE_GYROSCOPE,          //!< single- or multi-axies gyroscope
	SENSOR_TYPE_HUMIDITY,           //!< moisture or humidity sensor
	SENSOR_TYPE_LIGHT,              //!< ambient light sensor
	SENSOR_TYPE_MAGNETIC,           //!< magnetic sensor
	SENSOR_TYPE_PRESSURE,           //!< pressure sensor
	SENSOR_TYPE_PROXIMITY,          //!< proximity sensor
	SENSOR_TYPE_TEMPERATURE,        //!< single-function temperature
	SENSOR_TYPE_VOLTAGE             //!< single-function voltage

	} sensor_type_t;


//! \brief Sensor Feature Constants

typedef enum {

	SENSOR_CAPS_UNKNOWN         = 0x0000,
	SENSOR_CAPS_1_AXIS          = 0x0001,
	SENSOR_CAPS_2_AXIS          = 0x0002,
	SENSOR_CAPS_3_AXIS          = 0x0004,
	SENSOR_CAPS_SELFTEST        = 0x0008,
	SENSOR_CAPS_AUX_TEMP        = 0x0010,
	SENSOR_CAPS_HI_G_EVENT      = 0x0020,
	SENSOR_CAPS_LO_G_EVENT      = 0x0040,
	SENSOR_CAPS_TAP_EVENT       = 0x0080,
	SENSOR_CAPS_TILT_EVENT      = 0x0100,
	SENSOR_CAPS_DROP_EVENT      = 0x0200,
	SENSOR_CAPS_AUTO_CAL        = 0x0400,
	SENSOR_CAPS_AUX_ACCEL       = 0x0800

	} sensor_feature_t;


//! \brief Sensor Vendor Constants

typedef enum {

	SENSOR_VENDOR_UNKNOWN,          //!< unknown sensor vendor
	SENSOR_VENDOR_ADI,              //!< Analog Devices, Inc.
	SENSOR_VENDOR_AKM,              //!< Asahi Kasei Microdevices
	SENSOR_VENDOR_AVAGO,            //!< Avago Technologies
	SENSOR_VENDOR_BOSCH,            //!< Bosch Sensortec GmbH
	SENSOR_VENDOR_HONEYWELL,        //!< Honeywell International, Inc.
	SENSOR_VENDOR_INTERSIL,         //!< Intersil Corporation
	SENSOR_VENDOR_INVENSENSE,       //!< InvenSense
	SENSOR_VENDOR_KIONIX,           //!< Kionix, Inc. (ROHM)
	SENSOR_VENDOR_OSRAM,            //!< OSRAM Opto Semiconductors
	SENSOR_VENDOR_STM,              //!< STMicroelectronics
	SENSOR_VENDOR_TAOS,             //!< Texas Advanced Optoelectronic Solutions
	SENSOR_VENDOR_FREESCALE         //!< Freescale Semiconductor

	} sensor_vendor_t;


//! \brief Sensor Data Descriptor

typedef struct {

	union {
				
		int32_t           value [3];    //!< generic data name

		struct {                        // linear axis data
			int32_t       x;            //!< x-axis value
			int32_t       y;            //!< y-axis value
			int32_t       z;            //!< z-axis value
			} axis;

		struct {                        // rotational axis data
			int32_t       pitch;        //!< pitch-axis value
			int32_t       roll;         //!< roll-axis value
			int32_t       yaw;          //!< yaw-axis value
			} angle;

		struct {                        // magnetic heading data
			int32_t       direction;    //!< heading relative to magnetic north
			int32_t       inclination;  //!< inclination above/below horizontal
			int32_t       strength;     //!< net magnetic field intensity
			} heading;

		struct {                        // tap detection data
			int32_t       count;        //!< tap count
			int32_t       axis;         //!< tap detection axis (X,Y,Z)
			int32_t       direction;    //!< tap direction
			} tap;

		struct {                         // pressure data
			 int32_t       value;        //!< pressure value
			 int32_t       unused[2];    //!< unused (spare) fields
			} pressure;

		struct {                        // temperature data
			int32_t       value;        //!< temperature value
			int32_t       unused[2];    //!< unused (spare) fields
			} temperature;

		struct {                        // light data
			int32_t       value;        //!< light value
			int32_t       unused[2];    //!< unused (spare) fields
			} light;

		struct {                        // proximity data
			int32_t       value[3];       //!< proximity values (3)
			} proximity;

		struct {
			uint32_t      id;           //!< device ID
			uint32_t      version;      //!< version
			uint32_t      unused;       //!< unused (spare) field
			} device;
		};

	uint32_t          timestamp;    //!< data sample timestamp
	bool              scaled;       //!< data sample format (true => scaled)

	} sensor_data_t;



//! \brief Sensor Data Read Operations

typedef enum {

	SENSOR_READ_ACCELERATION,       //!< read acceleration data
	SENSOR_READ_FIELD,              //!< read field strength data
	SENSOR_READ_HEADING,            //!< read heading data
	SENSOR_READ_ID,                 //!< read sensor device ID
	SENSOR_READ_INTENSITY,          //!< read intensity data
	SENSOR_READ_LIGHT,              //!< read light level data
	SENSOR_READ_PRESSURE,           //!< read pressure data
	SENSOR_READ_PROXIMITY,          //!< read proximity data
	SENSOR_READ_ROTATION,           //!< read rotation data
	SENSOR_READ_TEMPERATURE,        //!< read temperature data

	SENSOR_READ_SCALAR,             //!< read generic single-value data
	SENSOR_READ_VECTOR              //!< read generic 3-axis vector data

	} sensor_read_t;


//! \brief Sensor Command Constants - used for sensor ioctl operations

typedef enum {

	// Get operational states

	SENSOR_INFO_QUERY,              //!< sensor information query

	SENSOR_STATUS_RUNNING,          //!< test for a running sensor
	SENSOR_STATUS_SLEEPING,         //!< test for a sleeping sensor
	SENSOR_STATUS_SUSPENDED,        //!< test for a suspended sensor

	// Set operational states

	SENSOR_EXEC_SLEEP,              //!< execute sensor sleep state
	SENSOR_EXEC_WAKE,               //!< execute sensor wake state
	SENSOR_EXEC_SUSPEND,            //!< execute sensor suspend state
	SENSOR_EXEC_RESET,              //!< execute sensor soft-reset function
	SENSOR_EXEC_SELFTEST,           //!< execute sensor self-test function

	// Get operational parameters

	SENSOR_GET_RANGE,               //!< get device-specific operational range
	SENSOR_GET_BANDWIDTH,           //!< get bandwidth (Hertz)
	SENSOR_GET_POWER,               //!< get power requirement (milliamps)
	SENSOR_GET_RESOLUTION,          //!< get sample resolution (bits)
	SENSOR_GET_SAMPLE_RATE,         //!< get device-specific sample rate
	SENSOR_GET_THRESHOLD,           //!< get sensor threshold value

	// Set operational parameters

	SENSOR_SET_STATE,               //!< set device operational state/mode
	SENSOR_SET_RANGE,               //!< set device-specific operational range
	SENSOR_SET_BANDWIDTH,           //!< set bandwidth (Hertz)
	SENSOR_SET_POWER,               //!< set power requirement (milliamps)
	SENSOR_SET_RESOLUTION,          //!< set sample resolution (bits)
	SENSOR_SET_SAMPLE_RATE,         //!< set device-specific sample rate
	SENSOR_SET_THRESHOLD,           //!< set sensor threshold value
	SENSOR_SET_TAP,                 //!< set sensor tap detection values

	// Sensor event control

	SENSOR_ENABLE_EVENT,            //!< enable sensor event
	SENSOR_DISABLE_EVENT            //!< disable sensor event

	} sensor_command_t;



//! \brief Sensor Driver and API Error Constants

typedef enum {

	SENSOR_ERR_NONE             = 0x0000,
	SENSOR_ERR_CALDATA          = 0x0001,
	SENSOR_ERR_RAWDATA          = 0x0002,
	SENSOR_ERR_COMPDATA         = 0x0004,
	SENSOR_ERR_HARDWARE         = 0x0008,
	SENSOR_ERR_SOFTWARE         = 0x0010,
	SENSOR_ERR_PARAMS           = 0x0020,
	SENSOR_ERR_CONFIG           = 0x0040,
	SENSOR_ERR_SELFTEST         = 0x0080,
	SENSOR_ERR_IO               = 0x0100,
	SENSOR_ERR_DRIVER           = 0x0200,
	SENSOR_ERR_UNSUPPORTED      = 0x8000,
	SENSOR_ERR_FUNCTION         = 0X8200,
	SENSOR_ERR_IOCTL            = 0x8210

	} sensor_error_t;


//! \brief Sensor Self-Test Error Constants

typedef enum {

	SENSOR_TEST_ERR_NONE        = 0x0000,
	SENSOR_TEST_ERR_FUNCTION    = 0x0001,       //!< no such self-test function
	SENSOR_TEST_ERR_READ        = 0x0002,       //!< read error
	SENSOR_TEST_ERR_WRITE       = 0x0003,       //!< write error
	SENSOR_TEST_ERR_RANGE       = 0x0004        //!< results out of range

	} sensor_testerr_t;


//! \name Sensor Physical Axis Definitions
// @{

//! \brief Sensor Axis Name Constants

typedef enum {

	SENSOR_AXIS_X               =  0,           // valid indeces are 0, 1, 2
	SENSOR_AXIS_Y               =  1,
	SENSOR_AXIS_Z               =  2,
	SENSOR_AXIS_NONE            = -1

	} sensor_axis_t;

//! \brief Sensor Axis Sign Constants

typedef enum {

	SENSOR_SIGN_POS             =  1,
	SENSOR_SIGN_NEG             = -1,
	SENSOR_SIGN_NONE            =  0

	} sensor_sign_t;

//! \brief Sensor Axis Descriptor

typedef struct {

	sensor_axis_t   axis;
	sensor_sign_t   sign;

	} sensor_axis_vec_t;

//! \brief Sensor Orientation Descriptor

typedef struct {

	sensor_axis_vec_t   x;
	sensor_axis_vec_t   y;
	sensor_axis_vec_t   z;

	} sensor_orient_t;

#define AXIS_X_POS  {SENSOR_AXIS_X, SENSOR_SIGN_POS}
#define AXIS_X_NEG  {SENSOR_AXIS_X, SENSOR_SIGN_NEG}
#define AXIS_Y_POS  {SENSOR_AXIS_Y, SENSOR_SIGN_POS}
#define AXIS_Y_NEG  {SENSOR_AXIS_Y, SENSOR_SIGN_NEG}
#define AXIS_Z_POS  {SENSOR_AXIS_Z, SENSOR_SIGN_POS}
#define AXIS_Z_NEG  {SENSOR_AXIS_Z, SENSOR_SIGN_NEG}
#define AXIS_NONE   {SENSOR_AXIS_NONE, SENSOR_SIGN_NONE}

// @}


//! \brief Sensor Calibration Type Constants

typedef enum {

	HARD_IRON_CALIBRATE,            //!< hard-iron calibration
	SOFT_IRON_CALIBRATE,            //!< soft-iron calibration
	FIELD_CALIBRATE,                //!< field calibration
	AUTO_CALIBRATE,                 //!< auto-calibration
	MANUAL_CALIBRATE                //!< manual calibration

	} sensor_calibration_t;



//! \name Sensor Event Interface
// @{

/*! \interface sensor_event_callback
 *
 * \brief
 * Sensor Event Handler Callback Type
 */
typedef void(*sensor_event_callback)(volatile void *);

/*! \interface sensor_enum_callback
 *
 * \brief
 * Sensor Enumeration Handler Callback Type
 */
typedef bool(*sensor_enum_callback)(const sensor_hal_t *, void *);

//! \brief Sensor Event Types

typedef enum {

	SENSOR_EVENT_UNKNOWN        = 0x0000,       //!< unknown sensor event
	SENSOR_EVENT_NEW_DATA       = 0x0001,       //!< new data available
	SENSOR_EVENT_MOTION         = 0x0002,       //!< motion detected
	SENSOR_EVENT_LOW_G          = 0x0004,       //!< inertial low-G detected
	SENSOR_EVENT_HIGH_G         = 0x0008,       //!< inertial high-G detected
	SENSOR_EVENT_TILT           = 0x0010,       //!< inertial tilt detected
	SENSOR_EVENT_TAP            = 0x0020,       //!< tap detected
	SENSOR_EVENT_DROP           = 0x0040,       //!< drop detected
	SENSOR_EVENT_LOW_PROXIMITY  = 0x0080,       //!< far proximity detected
	SENSOR_EVENT_HIGH_PROXIMITY = 0x0080,       //!< close proximity detected
	SENSOR_EVENT_LOW_LIGHT      = 0x0100,       //!< low light level detected
	SENSOR_EVENT_HIGH_LIGHT     = 0x0200,       //!< high light level detected

	} sensor_event_t;

//! \brief Sensor Event Descriptor

typedef struct {

	sensor_t *              sensor;             //!< event sensor descriptor
	sensor_event_t          event;              //!< sensor event type
	sensor_data_t           data;               //!< sensor event data
	sensor_event_callback   handler;            //!< user-defined event callback
	volatile void *         arg;                //!< optional callback parameter
	bool                    enabled;            //!< initial enabled state

	} sensor_event_desc_t;

//! \brief Sensor Tap Event

typedef enum {

	SENSOR_TAP_AXIS_UNKNOWN     = 0x0000,       //!< unknown tap detect axis
	SENSOR_TAP_AXIS_X           = 0x0001,       //!< tap detected on X axis
	SENSOR_TAP_AXIS_Y           = 0x0002,       //!< tap detected on Y axis
	SENSOR_TAP_AXIS_Z           = 0x0004,       //!< tap detected on Z axis
	
	} sensor_tap_axis_t;

//! \brief Sensor Tap Event (event direction)

typedef enum {

	SENSOR_TAP_DIRECTION_UNKNOWN = 0x0000,       //!< unknown tap direction
	SENSOR_TAP_DIRECTION_POS     = 0x0001,       //!< tap in positive direction
	SENSOR_TAP_DIRECTION_NEG     = 0x0002,       //!< tap in negative direction
	
	} sensor_tap_direction_t;

//! \brief Sensor Tap Event Parameters

typedef struct {

	size_t          count;           //!< max number of taps to detect
	uint16_t        axes;            //!< axes (X,Y,Z) to detect tap events
	size_t          threshold_min;   //!< minimum signal change for tap
	size_t          threshold_max;   //!< maximum signal change for tap
	uint16_t        total_time;      //!< total time for tap detection window
	uint16_t        tap_time_min;    //!< minimum duration of a tap
	uint16_t        tap_time_max;    //!< maximum duration of a tap
	uint16_t        between_time;    //!< minimum time between taps
	uint16_t        ignore_time;     //!< latency period after a tap

	} sensor_tap_params_t;

// @}


//! \brief Sensor Operational State Type Constants

typedef enum {

	SENSOR_STATE_UNKNOWN,           //!< unknown state
	SENSOR_STATE_NORMAL,            //!< normal state
	SENSOR_STATE_SLEEP,             //!< sleep state
	SENSOR_STATE_LOWEST_POWER,      //!< lowest power state
	SENSOR_STATE_LOW_POWER,         //!< low-power state
	SENSOR_STATE_HIGH_POWER,        //!< high-power state
	SENSOR_STATE_HIGHEST_POWER,     //!< highest power state
	SENSOR_STATE_X_AXIS_STANDBY,    //!< x-axis low power standby
	SENSOR_STATE_Y_AXIS_STANDBY,    //!< y-axis low power standby
	SENSOR_STATE_Z_AXIS_STANDBY,    //!< z-axis low power standby
	SENSOR_STATE_RESET,             //!< reset state (run soft-reset)
	SENSOR_STATE_POWER_DOWN         //!< power-down state

	} sensor_state_t;


//! \brief Sensor Self Test Types

typedef enum {

	SENSOR_TEST_DEFAULT,            //!< default test type for device
	SENSOR_TEST_BIAS_POS,           //!< positive bias test
	SENSOR_TEST_BIAS_NEG,           //!< negative bias test
	SENSOR_TEST_DEFLECTION,         //!< deflection test (e.g. accelerometer)
	SENSOR_TEST_INTERRUPT           //!< interrupt test

	} sensor_test_t;


//! \brief Sensor Threshold Type Constants

typedef enum {

	SENSOR_THRESHOLD_MOTION,         //!< inertial motion threshold
	SENSOR_THRESHOLD_LOW_G,          //!< inertial low-G threshold
	SENSOR_THRESHOLD_HIGH_G,         //!< inertial high-G threshold
	SENSOR_THRESHOLD_TAP,            //!< inertial tap threshold
	SENSOR_THRESHOLD_TILT,           //!< inertial tilt threshold
	SENSOR_THRESHOLD_DURATION,       //!< event duration
	SENSOR_THRESHOLD_LOW_LIGHT,      //!< low light level threshold
	SENSOR_THRESHOLD_HIGH_LIGHT,     //!< high light level threshold
	SENSOR_THRESHOLD_LOW_PROXIMITY,  //!< low proximity (far) threshold
	SENSOR_THRESHOLD_HIGH_PROXIMITY, //!< high proximity (close) threshold

	} sensor_threshold_t;


//! \brief Sensor Threshold Descriptor

typedef struct {

	sensor_threshold_t  type;
	int16_t             value;

	} sensor_threshold_desc_t;


//! \name Sensor Sample Commands and Data Formats
// @{

//! \brief Sensor Sample Data Format

typedef enum {

	SAMPLE_FORMAT_COUNTS,           //!< unscaled raw sample counts
	SAMPLE_FORMAT_SCALED            //!< scaled engineering units

	} sample_format_t;


//! \brief Sensor Sample Units

typedef enum {

	SENSOR_UNITS_NONE,              //!< unscaled data (raw counts)
	SENSOR_UNITS_g0,                //!< standard gravity (g0)
	SENSOR_UNITS_gauss,             //!< gauss (G)
	SENSOR_UNITS_lux,               //!< lux (lx)
	SENSOR_UNITS_lumen,             //!< lumen (lm)
	SENSOR_UNITS_pascal,            //!< pascal (Pa)
	SENSOR_UNITS_deg_per_sec,       //!< degrees-per-second (dps)
	SENSOR_UNITS_deg_Celcius,       //!< degrees-Celcius
	SENSOR_UNITS_tesla,             //!< tesla (T)
	SENSOR_UNITS_volt_DC,           //!< Volts DC
	SENSOR_UNITS_volt_AC            //!< Volts AC

	} sensor_units_t;


//! \brief Sensor Sample Unit Scale

typedef enum {

	SENSOR_SCALE_micro  = -6,       //!< log 0.000001
	SENSOR_SCALE_milli  = -3,       //!< log 0.001
	SENSOR_SCALE_centi  = -2,       //!< log 0.01
	SENSOR_SCALE_deci   = -1,       //!< log 0.1
	SENSOR_SCALE_one    =  0,       //!< log 1
	SENSOR_SCALE_deca   =  1,       //!< log 10
	SENSOR_SCALE_hecto  =  2,       //!< log 100
	SENSOR_SCALE_kilo   =  3        //!< log 1000

	} sensor_scale_t;


//! \brief Sensor Operational Capabilities Descriptors
// @{

typedef struct {

	union {
	int16_t                 bandwidth_Hz; //!< engineering unit value (Hz.)
	int16_t                 range_units;  //!< engineering unit value (varies)
	};
	uint8_t                 reserved_val; //!< driver-specific reserved value

	} sensor_map_t;


typedef sensor_map_t        sensor_range_t;
typedef sensor_map_t        sensor_band_t;

//! \brief Sensor Capabilities

typedef struct {

	sensor_feature_t        feature;      //!< API-specific sensor features
	sensor_vendor_t         vendor;       //!< API-specific vendor designation
	size_t                  range_count;  //!< device-specific range count
	size_t                  band_count;   //!< device-specific bandwidth count
	const sensor_map_t      *range_table;  //!< device-specific range table
	const sensor_map_t      *band_table;   //!< device-specific bandwidth table
	sensor_units_t          units;        //!< data sample base engineering units
	sensor_scale_t          scale;        //!< data sample engineering unit scale
	const char              *name;        //!< human readable description

	} sensor_caps_t;

// @}


//! \name Sensor Device Descriptors
// @{

//! \brief Sensor Platform Hardware Abstraction Descriptor

struct sensor_hal {
	bus_desc_t      bus;            //!< Platform Bus Descriptor
	uint8_t         burst_addr;     //!< Sensor Burst Read Address
	uint32_t        mcu_sigint;     //!< I/O input to MCU from sensor
	uint32_t        mcu_sigout;     //!< I/O output from MCU to sensor
	sensor_type_t   dev_type;       //!< Sensor Device Type

	// Sensor Physical/Logical Orientation
	sensor_orient_t orientation;    //!< Sensor axis/sign used as X,Y,Z

	// Sensor Operational Parameters

	int16_t         range;          //!< Sensor range (engineering units)
	int16_t         bandwidth;      //!< Sensor bandwidth (Hz)
	int16_t         sample_rate;    //!< Sensor sample rate (Hz)
	int16_t         resolution;     //!< Sensor sample resolution (bits)

	// Sensor Device Initialization Method

	bool (*sensor_init)(sensor_t *, int);
};


//! \brief Sensor Driver Entry Point Table

typedef struct {

	bool (*read)             (sensor_t *, sensor_read_t, sensor_data_t *);
	bool (*ioctl)            (sensor_t *, sensor_command_t, void *);
	bool (*event_callback)   (sensor_t *, sensor_event_desc_t *);
	bool (*calibrate)        (sensor_t *, sensor_calibration_t, int, void *);
	bool (*selftest)         (sensor_t *, int *, void *);

} sensor_funcs_t;


//! \brief Sensor Device Driver Specific Descriptor

typedef struct {

	sensor_funcs_t          func;   //!< driver functions
	sensor_caps_t           caps;   //!< driver capabilities

} sensor_device_t;


//! \brief Generic Sensor API Descriptor

struct sensor_desc {

	sensor_hal_t            *hal;    //!< platform interface
	const sensor_device_t   *drv;    //!< driver functions & capabilities
	sensor_state_t          mod;    //!< runtime state
	sensor_error_t          err;    //!< runtime errors
	void                    *aux;    //!< API extensions
};

// @}


//! \name Sensor API Convenience Macros and Functions
// @{

#define ARRAYSIZE(a)                    (sizeof (a) / sizeof (a[0]))

#define sensor_get_x(sensor, data)      (sensor_get_axis(sensor, data, 0))
#define sensor_get_y(sensor, data)      (sensor_get_axis(sensor, data, 1))
#define sensor_get_z(sensor, data)      (sensor_get_axis(sensor, data, 2))

#define sensor_get_pitch(sensor, data)  (sensor_get_angle(sensor, data, 0))
#define sensor_get_roll(sensor, data)   (sensor_get_angle(sensor, data, 1))
#define sensor_get_yaw(sensor, data)    (sensor_get_angle(sensor, data, 2))


/*! \brief Convert raw sensor data to scaled engineering units.
 *
 * This routine converts a sensor sample, \c counts, to a linearly scaled
 * integer value in engineering units using device-specific range in
 * standard engineering units and full scale resolution parameters in
 * \c hal.
 *
 * \param hal       An initialized hardware interface descriptor.
 * \param counts    An unscaled raw sensor sample value.
 *
 * \return Scaled signed sensor data in standard engineering units.
 */
static inline int32_t raw_to_scaled(sensor_hal_t *hal, int32_t counts)
{
	/* The unit increment per count is peak-to-peak range divided
	 * by full-scale resolution.
	 */
	return (counts * (2 * (int32_t)(hal->range))) >> hal->resolution;
}

/*! \brief Convert scaled sensor data to raw counts
 *
 * This routine converts a linearly scaled integer value in engineering
 * units to the corresponding "raw" reading value for the device,
 * using the device-specific range in standard engineering units and full 
 * scale resolution parameters in "opts".
 *
 * \param hal       An initialized hardware interface descriptor.
 * \param value     A scaled sensor sample value.
 *
 * \return Scaled signed sensor data in standard engineering units.
 */
static inline int32_t scaled_to_raw(sensor_hal_t *hal, int32_t value)
{
	/* The unit increment per count is peak-to-peak range divided
	 * by full-scale resolution.
	 */
	return (value << hal->resolution) / (2 * (int32_t)(hal->range));
}

/**
 * \brief Delay in milliseconds.
 *
 * \param msecs Delay in milliseconds
 */
extern void mdelay(unsigned long msecs);

/**
 * \brief Delay in microseconds.
 *
 * \param usecs Delay in microseconds
 */
extern void udelay(unsigned long usecs);

// @}


//! \name Sensor Bus I/O Wrapper Routines
// @{
#define sensor_bus_init              bus_init
#define sensor_bus_read(hal,...)     bus_read(&(hal)->bus,         __VA_ARGS__)
#define sensor_bus_write(hal,...)    bus_write(&(hal)->bus,        __VA_ARGS__)
#define sensor_bus_probe(hal,...)    bus_probe(&(hal)->bus,        __VA_ARGS__)
#define sensor_bus_get(hal,...)      bus_get(&(hal)->bus,          __VA_ARGS__)
#define sensor_bus_put(hal,...)      bus_put(&(hal)->bus,          __VA_ARGS__)
#define sensor_reg_bitclear(hal,...) bus_reg_bitclear(&(hal)->bus, __VA_ARGS__)
#define sensor_reg_bitset(hal,...)   bus_reg_bitset(&(hal)->bus,   __VA_ARGS__)
// @}


//! \defgroup mems_sensor_api Common Sensor API
// @{

//! \name Platform Interfaces
// @{
/*! \brief AVR Software Framework Common Sensor API version
 *
 * This routine Gets the Sensor API version number and release date.
 *
 * \return The address of a null-terminated read-only version string.
 */
extern const char *sensor_api_version(void);

/*! \brief Find a sensor hardware descriptor
 *
 * This routine returns the address of a sensor hardware descriptor, based on
 * the sensor type specified in the \c type parameter.  The first hardware
 * entry with the correct type will be used.
 *
 * This utility is currently used to abstract the details of the device list
 * implementation from the rest of the API.  However, it will not be retained in
 * future versions of the API.  As a result applications and library code should
 * not use this routine.  If list iteration is required in API clients, use the
 * sensor_device_enum() function.
 *
 * \param   type   The type of sensor to find in hardware descriptor list
 *
 * \return  The address of the sensor hardware descriptor, or NULL if not found
 */
extern sensor_hal_t *sensor_find(sensor_type_t type);

/*! \brief Install a sensor device interrupt handler
 *
 * This routine will enable interrupts on the pin specified by the \c intr_pin
 * parameter and call a user-defined callback \c handler when an interrupt is
 * detected.  The \c arg parameter is used to pass the address of user-defined
 * input and output storage for the callback handler.  Calling the routine with
 * the \c handler parameter set to 0 (the NULL pointer) will cause interrupts to
 * be disabled for the specified GPIO pin.
 *
 * \param   intr_pin    Board-specific interrupt / GPIO pin interface to the MCU.
 * \param   handler     The address of a user-defined interrupt handler.
 * \param   arg         An optional address passed to the interrupt handler.
 *
 * \return  bool        \c true if the call succeeds, else \c false.
 */
extern bool sensor_irq_connect(uint32_t intr_pin, 
	void (*handler)(volatile void *), void *arg);

/*! \brief Fetch the sensor hardware descriptor list
 *
 * This routine returns the system address of a table of sensor hardware
 * descriptors along with the number of descriptors in the \c dev_count
 * parameter.  This utility is currently used to abstract the details of the
 * device list implementation from the rest of the API.  However, it will not
 * be retained in future versions of the API.  As a result applications and
 * library code should not use this routine.  If list iteration is required
 * in API clients, use the sensor_device_enum() function.
 *
 * \param   dev_count   The list descriptor count is returned here.
 *
 * \return  The address of the sensor hardware descriptor list.
 */
extern sensor_hal_t *sensor_list(size_t *dev_count);

/*! \brief Initialize the Sensor Platform Hardware
 *
 * This function initializes the Atmel \c Xplained platform hardware and
 * must be called once from the client application before any of the Sensors
 * Xplained API routines can be used.
 *
 * After the platform board initialization (i.e. board_init()) configures
 * GPIO pins, interrupts, etc., this routine initializes the AVR and 32-bit AVR
 * hardware abstraction layer (HAL) for the Xplained Sensor API.
 *
 * \note
 * Sensor device availability varies by development board.  Even in cases where
 * the underlying platform has a supported sensor device, the required support
 * code for the sensor service may not have been implemented.  Consult the
 * development board documentation to determine whether the sensor API is
 * supported.
 *
 * @sa atavrsb_config
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_platform_init(void);

/*! \brief This function returns the current timestamp counter value.
 *
 * The timestamp facility is implemented in terms of the XMEGA or UC3
 * timer and clock function APIs.
 *
 * \return The current counter value (microseconds).
 */
extern uint32_t sensor_timestamp(void);

// @}

/*! \brief Attach a specified sensor descriptor to a sensor device.
 *
 * Applications invoke this routine to attach a \c sensor_t instance to an
 * existing sensor device of a specified \c type.  Assuming the attach call
 * is successful, the \c sensor_t instance can then be used with other sensor
 * API functions to perform operations on the device.
 *
 * \param   sensor  Specifies a descriptor to attach to the sensor device.
 * \param   type    Specifies the sensor type to attach.
 * \param   num     Driver instance number; currently ignored.
 * \param   aux     API Reserved value; should always be set to zero.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_attach(sensor_t *sensor, sensor_type_t type, int num, 
	void *aux);

/*! \brief Get sensor hardware device ID.
 *
 * This routine returns device-specific sensor hardware identification
 * and, optionally, version values.  Unimplemented values will be set
 * to zero.  For example, devices supporting a dedicated ID register, but
 * not a version register, will set "id" to the ID value and "ver" to zero.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   id      An address where the device ID is returned.
 * \param   ver     An address where the device version is returned.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_device_id(sensor_t *sensor, uint32_t *id, uint8_t *ver);

/*! \brief Enumerate sensor devices.
 *
 * This routine is a sensor device enumeration function that will call a
 * user-defined callback \c func for each sensor of a specified \c type
 * configured into the system.  The user-callback function will be passed the
 * address of a \a sensor_hal_t \c HAL descriptor corresponding to the sensor
 * type along with a user-specified address \c arg storing any additional
 * function arguments.
 *
 * If the specified sensor \c type is \c SENSOR_TYPE_UNKNOWN, then the user
 * \c func will be called for every sensor device in the system.
 *
 * Once called, the user-callback function must return a boolean \a true
 * value to continue iterating the list, else \a false to cease device list
 * iteration.  This routine returns when there are not more sensors of the
 * requested \c type in the device list, or when the user function returns
 * zero (false).
 *
 * Note that this function will not be included in the API by default.  Build
 * a sensor system with \c INCLUDE_SENSOR_ENUM defined to include this routine.
 *
 * \param   type    Specifies the sensor type to enumerate.
 * \param   func    Specifies the address of a user callback function.
 * \param   arg     Specifies the address of a callback function argument.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_device_enum(sensor_type_t type, sensor_enum_callback func, 
	void *arg);


/*! \brief Read sensor data
 *
 *  This is a generic routine that will call a specified sensor function
 *  returning \c vector sensor data.  It is used primarily by API routines
 *  but may be called by special-case application or library code where
 *  needed to extend the API semantics.
 *
 *  As an example, consider a multiple-axis gyroscope driver implementing
 *  the sensor_funcs_t.get_rotation() interface.  An application will usually
 *  call the sensor_get_rotation() routine in this case, but the angular
 *  rate might be obtained from the device as follows:
 *
 *  \code
 *
 *  sensor_t      gyroscope;
 *  sensor_data_t omega;
 *  ...
 *
 *  sensor_read(&gyroscope, SENSOR_READ_ROTATION, &omega);
 *  ...
 *
 *  \endcode
 *
 * In the event of a false return from this routine, the contents stored
 * at the location specified by "data" are undefined.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   type    Type of read operation to perform.
 * \param   data    Specifies an address where sensor data is stored.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_read(sensor_t *sensor, sensor_read_t type, 
	sensor_data_t *data);

/*! \brief Enumerate sensor bandwidth settings.
 *
 * This routine returns the address of a table, if any, holding device-specific
 * sensor bandwidth settings.  The use and context of the settings are specific
 * to the device and typically documented in the manufacturer's data sheets for
 * the device.
 *
 * \param   sensor  The address of a sensor descriptor.
 * \param   table   Location where the table address is returned.
 * \param   count   Location where the number of table elements is returned.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */

extern bool sensor_enum_bandwidth(sensor_t *sensor, const sensor_band_t **table,
	size_t* count);

/*! \brief Enumerate sensor range settings
 *
 * This routine returns the address of a table, if any, holding device-specific
 * sensor range settings.  The units of the settings are specific to the
 * device and typically documented in the manufacturer's data sheets for
 * the device.
 *
 * \param   sensor  The address of a sensor descriptor.
 * \param   table   Location where the table address is returned.
 * \param   count   Location where the number of table elements is returned.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_enum_range(sensor_t *sensor, const sensor_range_t **table, 
	size_t *count);

/*! \brief Calibrate a sensor device.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   caltype The type of calibration to perform.
 * \param   code    Device-specific calibration code or step parameter.
 * \param   info    Unimplemented (ignored) parameter.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_calibrate(sensor_t *sensor, sensor_calibration_t caltype, 
	int code, void *info);

/*! \brief Initiate a sensor device software reset.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   arg     Device-specific argument options.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_reset(sensor_t *sensor, int arg);

/*! \brief Set a sensor device to low-power or standby mode.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   arg     Device-specific argument options.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_sleep(sensor_t *sensor, int arg);

/*! \brief Set a sensor operational threshold.
 *
 * \param   sensor      The address of an initialized sensor descriptor.
 * \param   threshold   A specified sensor operational threshold.
 * \param   value       The value of the specified threshold.
 *
 * \return  bool     true if the call succeeds, else false is returned.
 */
extern bool sensor_set_threshold(sensor_t *sensor, sensor_threshold_t threshold,
	int16_t value);

/*! \brief Get a sensor operational threshold.
 *
 * \param   sensor      The address of an initialized sensor descriptor.
 * \param   threshold   A specified sensor operational threshold.
 * \param   value       Address of location to return threshold value
 *
 * \return  bool     true if the call succeeds, else false is returned.
 */
extern bool sensor_get_threshold(sensor_t *sensor, sensor_threshold_t threshold,
	int16_t *value);

/*! \brief Execute a sensor device control function.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   cmd     Specifies the IOCTL command.
 * \param   arg     Specifies command paramters (varies by command).
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_ioctl(sensor_t *sensor, sensor_command_t cmd, void *arg);

/*! \brief Set tap event parameters
 *
 * \param sensor    Address of an initialized sensor device descriptor.
 * \param params    Address of a tap paramter structure.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_set_tap(sensor_t *sensor, sensor_tap_params_t *params);

/*! \brief Activate a sensor self-test function.
 *
 * \param sensor    Address of an initialized sensor device descriptor.
 * \param test_code Address of a device-specific numeric test code.
 * \param arg       Device-specific self-test argument options.
 *
 * \return  bool    true if the test succeeds, else false is returned.
 */
extern bool sensor_selftest(sensor_t *sensor, int * test_code, void *arg);

/*! \brief Install a sensor event handler.
 *
 * This routine installs a sensor event handler that will be called when
 * the specified sensor event(s) occurs.  The \c event_desc parameter points
 * to a \c sensor_event_desc_t structure that describes the event, including
 * the specific sensor event to be reported, the address of the handler
 * function to be called, the parameter that will be passed (typically
 * a \c sensor_data_t structure to be filled in with measurement data),
 * and whether the event handler should initially be enabled or disabled.
 *
 * The event handler can subsequently be enabled and disabled using the
 * sensor_event_enable() and sensor_event_disable() routines.
 *
 * \param   event_desc  A specified sensor event descriptor.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_add_event(sensor_event_desc_t *event_desc);


/*! \brief Enable a sensor event handler.
 *
 * This routine enables the handler for a sensor event.  The event handler
 * must have already been defined using sensor_add_event().  To disable
 * the event, see sensor_disable_event().
 *
 * \param   event_desc  A specified sensor event descriptor.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
static inline bool sensor_enable_event(sensor_event_desc_t *event_desc) 
{
	return sensor_ioctl(event_desc->sensor, SENSOR_ENABLE_EVENT, event_desc);
}

/*! \brief Disable a sensor event handler.
 *
 * This routine disables the handler for a sensor event.  The event handler
 * must have already been defined using sensor_add_event().  To enable
 * the event, see sensor_enable_event().
 *
 * \param   event_desc  A specified sensor event descriptor.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
static inline bool sensor_disable_event(sensor_event_desc_t *event_desc) 
{
	return sensor_ioctl(event_desc->sensor, SENSOR_DISABLE_EVENT, event_desc);
}

/*! \brief Set a sensor mode.
 *
 * This routine sets a specified sensor execution state to one of the
 * following values:
 *
 *      - SENSOR_STATE_NORMAL
 *      - SENSOR_STATE_SLEEP
 *      - SENSOR_STATE_SUSPEND
 *      - SENSOR_STATE_LOWEST_POWER
 *      - SENSOR_STATE_LOW_POWER
 *      - SENSOR_STATE_HIGH_POWER
 *      - SENSOR_STATE_HIGHEST_POWER
 *      - SENSOR_STATE_RESET
 *
 * These execution states are not supported in all devices.  The function
 * return value will indicate whether or not the request could be processed.
 * The result of the request, when supported, is device dependent.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   mode    A specified sensor operational mode.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_set_state(sensor_t *sensor, sensor_state_t mode);

/*! \brief Get a sensor mode.
 *
 * This routine gets the current sensor execution state which may be one
 * of the following values:
 *
 *      - SENSOR_STATE_NORMAL
 *      - SENSOR_STATE_SLEEP
 *      - SENSOR_STATE_SUSPEND
 *      - SENSOR_STATE_LOWEST_POWER
 *      - SENSOR_STATE_LOW_POWER
 *      - SENSOR_STATE_HIGH_POWER
 *      - SENSOR_STATE_HIGHEST_POWER
 *      - SENSOR_STATE_RESET
 *
 * These execution states are not supported in all devices.  The function
 * return value will indicate whether or not the request could be processed.
 * The result of the request, when supported, is device dependent.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   mode    The current sensor mode is returned to this location.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
extern bool sensor_get_state(sensor_t *sensor, sensor_state_t *mode);

/*! \brief Set the sensor operational range.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   range   The new sensor operational range.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
static inline bool sensor_set_range(sensor_t *sensor, int16_t range)
{
	return sensor_ioctl(sensor, SENSOR_SET_RANGE, &range);
}

/*! \brief Get the sensor operational range.
 *
 * \param   sensor  The address of an initialized sensor descriptor.
 * \param   range   The current sensor operational range.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_range(sensor_t *sensor, int16_t *range)
{
	return sensor_ioctl(sensor, SENSOR_GET_RANGE, range);
}

/*! \brief Set the sensor operational bandwidth.
 *
 * \param   sensor       The address of an initialized sensor descriptor.
 * \param   bandwidth_Hz The new sensor operational bandwidth in Hertz.
 *
 * \return  bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_set_bandwidth (sensor_t *sensor, int16_t bandwidth_Hz)
{
	return sensor_ioctl(sensor, SENSOR_SET_BANDWIDTH, &bandwidth_Hz);
}

/*! \brief Get the sensor operational bandwidth.
 *
 * \param   sensor       The address of an initialized sensor descriptor.
 * \param   bandwidth_Hz The current sensor operational bandwidth in Hertz.
 *
 * \return  bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_bandwidth (sensor_t *sensor, 
	int16_t *bandwidth_Hz)
{
	return sensor_ioctl(sensor, SENSOR_GET_BANDWIDTH, bandwidth_Hz);
}

/*! \brief Set the sensor operational sample rate.
 *
 * \param   sensor       The address of an initialized sensor descriptor.
 * \param   sample_Hz    The new sensor operational sample rate in Hertz.
 *
 * \return  bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_set_sample_rate (sensor_t *sensor, int16_t sample_Hz)
{
	return sensor_ioctl(sensor, SENSOR_SET_SAMPLE_RATE, &sample_Hz);
}

/*! \brief Get the sensor operational sample rate.
 *
 * \param   sensor       The address of an initialized sensor descriptor.
 * \param   sample_Hz    The current sensor sample rate in Hertz.
 *
 * \return  bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_sample_rate (sensor_t *sensor, int16_t *sample_Hz)
{
	return sensor_ioctl(sensor, SENSOR_GET_SAMPLE_RATE, sample_Hz);
}


/*! \brief Read angular rate sensor data
 *
 * This routine returns a data sample for an \c angle of a specified
 * angular rate \c sensor device such as a gyroscope.
 *
 * In the event of a false return from this routine, the contents stored
 * at the location specified by \c data are undefined.
 *
 * \note This routine is only supported for drivers implementing the
 * \b get_rotation driver interface.
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 * \param  angle    Specifies the angle (pitch = 0, roll = 1, yaw = 2)
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_angle (sensor_t *sensor, sensor_data_t *data, 
	int angle)
{

	// assert ((0 <= angle) && (angle <= 2));

	sensor_data_t vec;

	bool const result = sensor_read(sensor, SENSOR_READ_ROTATION, &vec);

	data->value[0] = vec.value [angle];

	return result;
}

/*! \brief Get vector sensor data
 *
 * In the event of a false return from this routine, the contents stored
 * at the location specified by "data" are undefined.
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_vector(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_VECTOR, data);
}

/*! \brief Get acceleration sensor data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_acceleration(sensor_t *sensor, 
	sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_ACCELERATION, data);
}

/*! \brief Get rotation sensor data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_rotation(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_ROTATION, data);
}

/*! \brief Get pressure sensor data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_pressure(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_PRESSURE, data);
}

/*! \brief Get temperature sensor data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_temperature(sensor_t *sensor, 
	sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_TEMPERATURE, data);
}

/*! \brief Get sensor heading data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_heading(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_HEADING, data);
}

/*! \brief Get sensor field strength data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_field (sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_FIELD, data);
}

/*! \brief Get sensor proximity data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_proximity(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_PROXIMITY, data);
}

/*! \brief Get sensor light level data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_light(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_LIGHT, data);
}
/*! \brief Get sensor intensity data
 *
 * \param  sensor   The address of an initialized sensor descriptor.
 * \param  data     Specifies an address where sensor data is stored.
 *
 * \return bool     true if the call succeeds, else false is returned.
 */
static inline bool sensor_get_intensity(sensor_t *sensor, sensor_data_t *data)
{
	return sensor_read(sensor, SENSOR_READ_INTENSITY, data);
}
// @}


#ifdef __cplusplus
}
#endif

#endif /* _sensor_h_ */
