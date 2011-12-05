/**
 * \file
 *
 * \brief Common Sensor Service Data Visualizer
 *
 * \mainpage
 *
 * \section intro Introduction
 *
 * This application obtains sensor data from the MEMS accelerometer, gyroscope,
 * and electronic compass devices installed on an Atmel development board.
 * The data is then formatted and transferred to a remote host for display
 * using the Atmel Data Visualizer tool.
 *
 * The Atmel Data Visualizer (ADV) tool is a standalone Windows application
 * that provides a graphical display of data sent from a remote target.  It
 * is available as a separate download.  For more information on downloading
 * and installing the ADV tool, visit 
 * <A href="http://www.atmel.com/dyn/products/tools_card.asp?tool_id=5017">Atmel Data Visualizer</A>
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 *
 * \section License
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
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

#include <stdio.h>

#include <board.h>
#include <led.h>

#include <sensors/sensor.h>
#include "data_visualizer.h"


// Sensor interval settings - how often each sensor is measured
//
#define ACCEL_INTERVAL      1       // loops per accel meas/xmit
#define GYRO_INTERVAL       3       // loops per gyro meas/xmit
#define COMPASS_INTERVAL    5       // loops per compass meas/xmit
#define TEMP_INTERVAL       10      // loops per temperature meas/xmit

#define ACCEL_STREAM_NUM    1       // accelerometer data stream number
#define GYRO_STREAM_NUM     2       // gyroscope data stream number
#define COMPASS_STREAM_NUM  3       // compass/magnetometer data stream number
#define TEMP_STREAM_NUM     4       // temperature data stream number

#define NUM_ACCEL_FIELDS    3       // accelerometer data fields in data packet
#define NUM_GYRO_FIELDS     3       // gyroscope data fields in data packet
#define NUM_COMPASS_FIELDS  3       // compass data fields in data packet
#define NUM_TEMP_FIELDS     1       // temperature data fields in data packet

#define TIMESTAMP_RES       1000000 // timestamp resolution (1 per usec)

// Switch and LED definitions
//
#if UC3
#  define SWITCH_PRESSED  (gpio_get_pin_value (GPIO_PUSH_BUTTON_0) ==     \
				           GPIO_PUSH_BUTTON_0_PRESSED)
#elif XMEGA
#  define SWITCH_PRESSED  (ioport_get_value (GPIO_PUSH_BUTTON_0) == false)
#endif

#if (BOARD==UC3_L0_XPLAINED)
#  define NUM_BLINK_LEDS  (LED_COUNT - 1)    // don't blink LED0 (shared gpio)
#  define ALL_LEDS        (LED1 | LED2 | LED3 | LED4)
#  define PROMPT_LED      LED4      // blink while waiting for user input
   static const uint32_t led_array[LED_COUNT - 1] = {LED1, LED2, LED3, LED4};

#elif (BOARD==UC3_A3_XPLAINED)
#  define NUM_BLINK_LEDS  (LED_COUNT)        // blink all LEDs
#  define ALL_LEDS        (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED      LED0      // blink while waiting for user input
   static const uint32_t led_array[LED_COUNT] = {LED0, LED1, LED2, LED3};

#elif (BOARD==XMEGA_A1_XPLAINED) || (BOARD==XMEGA_A3BU_XPLAINED)
#  define NUM_BLINK_LEDS  (4)        // blink 4 LEDs
#  define ALL_LEDS        (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED      LED0      // blink while waiting for user input
   static const uint32_t led_array[LED_COUNT] = {LED0, LED1, LED2, LED3};
#endif

#define BLINK_DELAY     0xF000      // prompt blink delay loop count



// Forward References
//

void  visual_stream_init(void);


/*! \brief Inertial sensor data visualizer demo application entry
 *
 * This application uses a serial connection to transmit sensor data.  The
 * data is formatted for use by the Atmel Data Visualizer application
 * running on a remote host.
 *
 * Upon entry, the hardware (including processor and sensor board) are
 * initialized, and the sensor interfaces are established.  The application
 * then transmits a series of special data stream configuration packets,
 * which tell the remote application the number, type, and labels for
 * data streams that will subsequently be used.
 *
 * After this initialization, the application enters a continuous loop
 * in which it periodically samples the sensors that are defined and
 * sends the obtained data values to the remote host in stream data packets.
 * Each type of sensor measurement uses an interval counter to determine
 * how often the measurement should be performed and transmitted.
 *
 * \return  Nothing.
 */

int main(void)
{
	volatile int    delay;
	int             led_index = 0;
	int             loop_count = 0;
 
	sensor_t        accel_dev;      // acceleromter device
	sensor_t        compass_dev;    // compass/magnetometer device
	sensor_t        gyro_dev;       // gyroscope device

	sensor_data_t   accel_data;     // accelerometer data
	sensor_data_t   compass_data;   // compass data
	sensor_data_t   gyro_data;      // gyroscope data
	sensor_data_t   temp_data;      // temperature data


	// ------------------------------------------------------------------------
	// Initialization
	// ------------------------------------------------------------------------

	// Initialize hardware & sensor interfaces

	sensor_platform_init();

	LED_On(ALL_LEDS);               // turn all LED's on


	// Attach descriptors to the defined sensor devices.

	sensor_attach(&accel_dev,   SENSOR_TYPE_ACCELEROMETER, 0, 0);
	sensor_attach(&gyro_dev,    SENSOR_TYPE_GYROSCOPE,     0, 0);
	sensor_attach(&compass_dev, SENSOR_TYPE_COMPASS,       0, 0);

	// Set sensor data output formats

	accel_data.scaled   = true;
	gyro_data.scaled    = true;
	compass_data.scaled = true;
	temp_data.scaled    = true;


	// Wait for user to push button before continuing

	LED_Off(ALL_LEDS);                 // turn all LED's off

	while ( ! SWITCH_PRESSED) {

		// Just blink LED until button is pushed

		LED_Toggle(PROMPT_LED);
		
		for (delay = 0; delay < BLINK_DELAY; delay++) {
			;    // do nothing
		}
	}

	LED_Off(PROMPT_LED);                // leave LED off 

	while (SWITCH_PRESSED) {
		;    // wait until button is released
	}

		
	// Enable output streams for Atmel Data Visualizer (ADV)

	visual_stream_init();


	// ------------------------------------------------------------------------
	// Main loop
	// ------------------------------------------------------------------------

	while (true) {

		// Change LED display

		LED_Toggle(led_array [led_index++]);
		if (led_index >= NUM_BLINK_LEDS) {
			led_index = 0;
		}


		// Sample sensors and send data packets according to loop counter

		// Accelerometer data

		if ((loop_count % ACCEL_INTERVAL) == 0) {

			sensor_get_acceleration(&accel_dev, &accel_data);

			adv_data_send_3(ACCEL_STREAM_NUM, accel_data.timestamp,
				accel_data.axis.x, accel_data.axis.y, accel_data.axis.z);
		}

		// Gyroscope data

		if ((loop_count % GYRO_INTERVAL) == 0) {

			sensor_get_rotation(&gyro_dev,  &gyro_data);

			adv_data_send_3(GYRO_STREAM_NUM, gyro_data.timestamp,
				gyro_data.axis.x, gyro_data.axis.y, gyro_data.axis.z);
		}


		// Compass/magnetometer data

		if ((loop_count % COMPASS_INTERVAL) == 0) {

			sensor_get_heading(&compass_dev,  &compass_data);

			adv_data_send_3(COMPASS_STREAM_NUM, compass_data.timestamp,
				compass_data.heading.direction, 
				compass_data.heading.inclination, 
				compass_data.heading.strength);
		}

		// Temperature data

		if ((loop_count % TEMP_INTERVAL) == 0) {

			sensor_get_temperature(&gyro_dev, &temp_data);

			adv_data_send_1(TEMP_STREAM_NUM, temp_data.timestamp,
				temp_data.temperature.value);
		}

		// Re-send stream initialization if switch pressed

		if (SWITCH_PRESSED) {

			LED_Off(ALL_LEDS);              // turn all LED's off

			LED_On(PROMPT_LED);             // turn on user prompt LED only

			visual_stream_init();           // resend init info

			while (SWITCH_PRESSED) {
				;    // wait until button is released
			}

			LED_Off(PROMPT_LED);            // turn off LED
			led_index = 0;                  // reset LED for on/off pattern
		}


		loop_count++;                       // increment loop counter
	}

	return 0;
}

/*! \brief  Initialize sensor data output streams for Atmel Data Visualizer
 *
 * This routine initializes the data streams used in this application for the 
 * Atmel Data Visualizer (ADV) tool.  First, a start-of-configuration packet
 * is constructed and sent.  Next, each data stream is described with a
 * stream descriptor packet and either one or three field descriptor packets
 * (depending on how many data fields are used to report a single set of
 * data from that device).  After all streams and data fields have been
 * described, an end-of-configuration packet is sent.
 *
 * \return  Nothing.
 */

void visual_stream_init(void)
{
	adv_config_start_t  start;      // config start packet
	adv_config_stream_t stream;     // stream config packet
	adv_config_field_t  field;      // data field info packet
	adv_config_end_t    end;        // config end packet


	// Configuration start packet

	start.header1     = ADV_PKT_HEADER_1;
	start.header2     = ADV_PKT_HEADER_2;
	start.length      = cpu_to_le16(sizeof(adv_config_start_t));
	start.type        = ADV_PKT_CONFIG_START;
	start.num_streams = 4;
	start.crc         = 0x00;          // not used
	start.mark        = ADV_PKT_END;

	adv_write_buf((uint8_t *) &start, sizeof(start));

	// Common field values for all stream config packets

	stream.header1  = ADV_PKT_HEADER_1;
	stream.header2  = ADV_PKT_HEADER_2;
	stream.type     = ADV_PKT_CONFIG_STREAM;
	stream.tick_res = cpu_to_le32(TIMESTAMP_RES);
	stream.length   = cpu_to_le16(sizeof(adv_config_stream_t));
	stream.mark     = ADV_PKT_END;
	stream.crc      = 0x00;                   // not used

	// Common field values for all data field descriptor config packets

	field.header1      = ADV_PKT_HEADER_1;
	field.header2      = ADV_PKT_HEADER_2;
	field.type         = ADV_PKT_CONFIG_FIELD;
	field.length       = cpu_to_le16(sizeof(adv_config_field_t));
	field.field_length = 4;             // all fields are signed 4-byte integers
	field.format       = FIELD_FORMAT_SIGNED;
	field.mark         = ADV_PKT_END;
	field.crc          = 0x00;                   // not used


	// Accelerometer stream
	// --------------------
	stream.stream_num = ACCEL_STREAM_NUM;
	stream.num_fields = NUM_ACCEL_FIELDS;
	strcpy((void *) &(stream.stream_name), "Acceleration");

	adv_write_buf((uint8_t *) &stream, sizeof(stream));

	// X axis data field
	field.stream_num = ACCEL_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(-2000);
	field.max        = cpu_to_le32(2000);
	strcpy((void *) &(field.units), "Milli-g");
	strcpy((void *) &(field.name), "Accel X");

	adv_write_buf((uint8_t *) &field, sizeof(field));  

	// Y axis data field (re-use previous values except name & field number)
	field.field_num = 2;
	strcpy((void *) &(field.name), "Accel Y");

	adv_write_buf((uint8_t *) &field, sizeof(field));

	// Z axis data field (re-use previous values except name & field number)
	field.field_num = 3;
	strcpy((void *) &(field.name), "Accel Z");

	adv_write_buf((uint8_t *) &field, sizeof(field));


	// Gyroscope stream
	// ----------------
	stream.stream_num = GYRO_STREAM_NUM;
	stream.num_fields = NUM_GYRO_FIELDS;
	strcpy((void *) &(stream.stream_name), "Rotation");

	adv_write_buf((uint8_t *) &stream, sizeof(stream));

	// X axis data field
	field.stream_num = GYRO_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(-2000);
	field.max        = cpu_to_le32(2000);
	strcpy((void *) &(field.units), "Deg per sec");
	strcpy((void *) &(field.name), "Rot X");

	adv_write_buf((uint8_t *) &field, sizeof(field));

	// Y axis data field (re-use previous values except name & field number)
	field.field_num = 2;
	strcpy((void *) &(field.name), "Rot Y");

	adv_write_buf((uint8_t *) &field, sizeof(field));

	// Z axis data field (re-use previous values except name & field number)
	field.field_num = 3;
	strcpy((void *) &(field.name), "Rot Z");

	adv_write_buf((uint8_t *) &field, sizeof(field));


	// Compass/Magnetometer stream
	// ---------------------------
	stream.stream_num = COMPASS_STREAM_NUM;
	stream.num_fields = NUM_COMPASS_FIELDS;
	strcpy((void *) &(stream.stream_name), "Magnetic Heading");

	adv_write_buf((uint8_t *) &stream, sizeof(stream));

	// Heading data field
	field.stream_num = COMPASS_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(0);
	field.max        = cpu_to_le32(360);
	strcpy((void *) &(field.units), "Degrees");
	strcpy((void *) &(field.name), "Direction");

	adv_write_buf((uint8_t *) &field, sizeof(field));

	// Inclination field
	field.stream_num = COMPASS_STREAM_NUM;
	field.field_num  = 2;
	field.min        = cpu_to_le32(-90);
	field.max        = cpu_to_le32(90);
	strcpy((void *) &(field.units), "Degrees");
	strcpy((void *) &(field.name), "Incl"); 

	adv_write_buf((uint8_t *) &field, sizeof(field));

	// Field strength field
	field.stream_num = COMPASS_STREAM_NUM;
	field.field_num  = 3;
	field.min        = cpu_to_le32(0);
	field.max        = cpu_to_le32(200);
	strcpy((void *) &(field.units), "uTesla");
	strcpy((void *) &(field.name), "Field"); 

	adv_write_buf((uint8_t *) &field, sizeof(field));


	// Temperature stream
	// -------------------
	stream.stream_num = TEMP_STREAM_NUM;
	stream.num_fields = NUM_TEMP_FIELDS;
	strcpy((void *) &(stream.stream_name), "Temperature");

	adv_write_buf((uint8_t *) &stream, sizeof(stream));


	// Temperature field
	field.stream_num = TEMP_STREAM_NUM;
	field.field_num  = 1;
	field.min        = cpu_to_le32(-10);
	field.max        = cpu_to_le32(50);
	strcpy((void *) &(field.units), "Deg C");
	strcpy((void *) &(field.name), "Temp");

	adv_write_buf((uint8_t *) &field, sizeof(field)); 


	// Configuration end packet

	end.header1 = ADV_PKT_HEADER_1;
	end.header2 = ADV_PKT_HEADER_2;
	end.length  = cpu_to_le16(sizeof(adv_config_end_t));
	end.type    = ADV_PKT_CONFIG_END;
	end.num_streams = 4;
	end.crc     = 0x00;             // not used
	end.mark    = ADV_PKT_END;

	adv_write_buf((uint8_t *) &end, sizeof(end));

	return;
}

