/*
 * ADXL345.h
 *
 *  Created on: 2016/09/16
 *      Author: akihiro
 *
 *  2016/09/18 kinoshita
 *  	verified by actual device
 *
 * 2016/11/30 kinoshita
 *     added "adxl345_ready()"
 * 2016/12/17 kinoshita
 *     changed "ADXL345_get()" return value bool -> void
 *     added "ADXL345_config()", "ADXL345_get_default_config()"
 *     , "ADXL345_start()", "ADXL345_stop()", "ADXL345_int_enable()"
 *     , "ADXL345_int_state()", "ADXL345_self_test_in()", "ADXL345_self_test_out()"
 *     , "ADXL345_act_status()", "ADXL345_tap_status()"
 *
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include <stdbool.h>

// check if acceleration data is ready
bool ADXL345_ready();

// get acceleration data (16 bit format)
// data[0] : X data, data[1] : Y data, data[2] : Z data
void ADXL345_get(signed short *data);


void ADXL345_set_rate(unsigned char rate);
void ADXL345_set_range(unsigned char range);

#define ADXL345_RATE_3200 0x0F
#define ADXL345_RATE_1600 0x0E
#define ADXL345_RATE_800 0x0D
#define ADXL345_RATE_400 0x0C
#define ADXL345_RATE_200 0x0B
#define ADXL345_RATE_100 0x0A
#define ADXL345_RATE_50 0x09
#define ADXL345_RATE_25 0x08
#define ADXL345_RATE_12R5 0x07
#define ADXL345_RATE_6R5 0x06
#define ADXL345_RATE_3R13 0x05
#define ADXL345_RATE_1R56 0x04
#define ADXL345_RATE_0R78 0x03
#define ADXL345_RATE_0R39 0x02
#define ADXL345_RATE_0R20 0x01
#define ADXL345_RATE_0R10 0x00

#define ADXL345_RANGE_2G 0x0
#define ADXL345_RANGE_4G 0x1
#define ADXL345_RANGE_8G 0x2
#define ADXL345_RANGE_16G 0x3

void ADXL345_single_read(char reg, char *data);
void ADXL345_single_write(char reg, char data);
void ADXL345_multi_read(char reg, char *data, int n);
void ADXL345_multi_write(char reg, char *data, int n);

typedef struct{
	// BW_RATE register
	unsigned char rate; 			// 4bit code
	unsigned char low_power; 	// 1bit

	unsigned char int_map; 		// interrupt source, bit combination, 0 -> assign to INT1, 1 -> to INT2

	signed char x_offset; // 15.6mg/LSB, signed 8bit
	signed char y_offset; // 15.6mg/LSB, signed 8bit
	signed char z_offset; // 15.6mg/LSB, signed 8bit

	unsigned char thresh_tap; 	// 62.5mg/LSB(0xFF->16g), unsigned 8bit
	unsigned char dur_tap; 		// 625us/LSB, unsigned 8bit
	unsigned char latent_tap; 	// 1.25ms/LSB, unsigned 8bit
	unsigned char window_tap; 	// 1.25ms/LSB, unsigned 8bit
	unsigned char thresh_act; 	// 62.5mg/LSB(0xFF->16g), unsigned 8bit
	unsigned char thresh_inact; 	// 62.5mg/LSB(0xFF->16g), unsigned 8bit
	unsigned char time_inact; 	// 1sec/LSB, unsigned 8bit

	// ACT_INACT_CTL
	unsigned char act_acdc; 		// 1bit, 0 -> DC operation, 1 -> AC operation
	unsigned char act_x_enable;
	unsigned char act_y_enable;
	unsigned char act_z_enable;

	unsigned char inact_acdc; 	// 1bit, 0 -> DC operation, 1 -> AC operation
	unsigned char inact_x_enable;
	unsigned char inact_y_enable;
	unsigned char inact_z_enable;

	// TAP_AXES
	unsigned char tap_x_enable;
	unsigned char tap_y_enable;
	unsigned char tap_z_enable;
	unsigned char suppress_tap; 	// 1bit

	unsigned char thresh_ff; 	// 62.5mg/LSB, unsigned 8bit, 300~600mg(0x05~0x09) is recommended
	unsigned char time_ff; 		// 5ms/LSB, unsigned 8bit, 100~350ms(0x14~0x46) is recommended

	// POWER_CTL register
	unsigned char link; 			// 1bit
	unsigned char auto_sleep; 	// 1bit
	unsigned char sleep; 		// 1bit
	unsigned char wakeup; 		// 2bit code

	// DATA_FORMAT register
	unsigned char spi; 			// 1bit, 0 -> 4 line SPI, 1 -> 3 line SPI
	unsigned char int_invert;		// 1bit, 0 -> active high, 1 -> active low
	unsigned char full_res;		// 1bit, 0 -> 10bit mode, 1 -> fixed scale 4mg/LSB
	unsigned char justify;		// 1bit, 0 -> right justified, 1 -> left justified
	unsigned char range;			// 2bit code

	// FIFO_CTL register
	unsigned char fifo_mode;		// 2bit code
	unsigned char trigger;		// 1bit, 0 -> link trigger event to INT1, 1 -> to INT2
	unsigned char samples;		// 5bit

} ADXL345_CONF;

#define ADXL345_SPI_4LINE 0
#define ADXL345_SPI_3LINE 1

#define ADXL345_FIFO_MODE_BYPASS 0x00
#define ADXL345_FIFO_MODE_FIFO 0x01
#define ADXL345_FIFO_MODE_STREAM 0x02
#define ADXL345_FIFO_MODE_TRIGGER 0x03

#define ADXL345_ACT_X 0x40
#define ADXL345_ACT_Y 0x20
#define ADXL345_ACT_Z 0x10
#define ADXL345_INACT_X 0x04
#define ADXL345_INACT_Y 0x02
#define ADXL345_INACT_Z 0x01

#define ADXL345_TAP_X 0x04
#define ADXL345_TAP_Y 0x02
#define ADXL345_TAP_Z 0x01

#define ADXL345_INT_BIT_DATA_READY 	0x80
#define ADXL345_INT_BIT_SINGLE_TAP 	0x40
#define ADXL345_INT_BIT_DOUBLE_TAP 	0x20
#define ADXL345_INT_BIT_ACTIVITY 	0x10
#define ADXL345_INT_BIT_INACTIVITY 	0x08
#define ADXL345_INT_BIT_FREE_FALL 	0x04
#define ADXL345_INT_BIT_WATERMARK 	0x02
#define ADXL345_INT_BIT_OVERRUN 	0x01

#define ADXL345_WAKEUP_8HZ 0x00
#define ADXL345_WAKEUP_4HZ 0x01
#define ADXL345_WAKEUP_2HZ 0x10
#define ADXL345_WAKEUP_1HZ 0x11

void ADXL345_config(ADXL345_CONF *conf);
void ADXL345_get_default_config(ADXL345_CONF *conf);

void ADXL345_start();
void ADXL345_stop();

// int_source : combination of ADXL345_INT_BIT_xxxx
void ADXL345_int_enable(unsigned char int_source);
void ADXL345_int_state(unsigned char *int_source);


void ADXL345_self_test_in();
void ADXL345_self_test_out();

// return : ADXL345_ACT_X, ADXL345_ACT_Y, or ADXL345_ACT_Z
unsigned char ADXL345_act_status();
// return : ADXL345_TAP_X, ADXL345_TAP_Y, or ADXL345_TAP_Z
unsigned char ADXL345_tap_status();

#endif /* ADXL345_H_ */
