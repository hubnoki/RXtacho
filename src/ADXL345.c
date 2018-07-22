/*
 * ADXL345.c
 *
 *  Created on: 2016/09/17
 *      Author: akihiro
 *
 *  2016/09/18 kinoshita
 *  	verified by actual device
 * 2016/11/30 kinoshita
 *     added "ADXL345_ready()"
 * 2016/12/17 kinoshita
 *     changed "ADXL345_get()" return value bool -> void
 *     added "ADXL345_config()", "ADXL345_get_default_config()"
 *     , "ADXL345_start()", "ADXL345_stop()", "ADXL345_int_enable()"
 *     , "ADXL345_int_state()", "ADXL345_self_test_in()", "ADXL345_self_test_out()"
 *     , "ADXL345_act_status()", "ADXL345_tap_status()"
 * 2017/01/02 kinoshita
 *     separated device dependent functions
 *
 */

#include "ADXL345.h"
#include "hardware_lib.h"


//// Hardware dependent functions ////

#pragma inline(DEVICE_SPI_TRANSCEIVE)
static char DEVICE_SPI_TRANSCEIVE(char d)
{
	return sci6_ADXL345_transceive(d);
}

#pragma inline(DEVICE_CS_CLEAR)
static void DEVICE_CS_CLEAR(void){SCI6_ADXL345_CS = 0;}
#pragma inline(DEVICE_CS_SET)
static void DEVICE_CS_SET(void){SCI6_ADXL345_CS = 1;}


// ADXL345 register map
#define ADXL345_REG_DEVID 0x00
#define ADXL345_REG_THRESH_TAP 0x1D
#define ADXL345_REG_OFSX 0x1E
#define ADXL345_REG_OFSY 0x1F
#define ADXL345_REG_OFSZ 0x20
#define ADXL345_REG_DUR 0x21
#define ADXL345_REG_LATENT 0x22
#define ADXL345_REG_WINDOW 0x23
#define ADXL345_REG_THRESH_ACT 0x24
#define ADXL345_REG_THRESH_INACT 0x25
#define ADXL345_REG_TIME_INACT 0x26
#define ADXL345_REG_ACT_INACT_CTL 0x27
#define ADXL345_REG_THRESH_FF 0x28
#define ADXL345_REG_TIME_FF 0x29
#define ADXL345_REG_TAP_AXES 0x2A
#define ADXL345_REG_ACT_TAP_STATUS 0x2B
#define ADXL345_REG_BW_RATE 0x2C
#define ADXL345_REG_POWER_CTL 0x2D
#define ADXL345_REG_INT_ENABLE 0x2E
#define ADXL345_REG_INT_MAP 0x2F
#define ADXL345_REG_INT_SOURCE 0x30
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_DATAX0 0x32
#define ADXL345_REG_DATAX1 0x33
#define ADXL345_REG_DATAY0 0x34
#define ADXL345_REG_DATAY1 0x35
#define ADXL345_REG_DATAZ0 0x36
#define ADXL345_REG_DATAZ1 0x37
#define ADXL345_REG_FIFO_CTL 0x38
#define ADXL345_REG_FIFO_STATUS 0x39

// register bit field definitions
// LSB comes first
typedef union{

	struct{
		unsigned char inact_z_enable :1;
		unsigned char inact_y_enable :1;
		unsigned char inact_x_enable :1;
		unsigned char inact_acdc :1;
		unsigned char act_z_enable :1;
		unsigned char act_y_enable :1;
		unsigned char act_x_enable :1;
		unsigned char act_acdc :1;
	} act_inact_ctl;

	struct{
		unsigned char tap_z_enable :1;
		unsigned char tap_y_enable :1;
		unsigned char tap_x_enable :1;
		unsigned char suppress :1;
		unsigned char :4;
	} tap_axes;

	struct{
		unsigned char tap_z_source :1;
		unsigned char tap_y_source :1;
		unsigned char tap_x_source :1;
		unsigned char asleep :1;
		unsigned char act_z_source :1;
		unsigned char act_y_source :1;
		unsigned char act_x_source :1;
		unsigned char :1;
	} act_tap_status;

	struct{
		unsigned char rate :4;
		unsigned char low_power :1;
		unsigned char :3;
	} bw_rate;

	struct{
		unsigned char wakeup :2;
		unsigned char sleep :1;
		unsigned char measure :1;
		unsigned char auto_sleep :1;
		unsigned char link :1;
		unsigned char :2;
	} power_ctl;

	struct{
		unsigned char overrun :1;
		unsigned char watermark :1;
		unsigned char free_fall :1;
		unsigned char inactivity :1;
		unsigned char activity :1;
		unsigned char double_tap :1;
		unsigned char single_tap :1;
		unsigned char data_ready :1;
	} int_map;

	struct{
		unsigned char range :2;
		unsigned char justfy :1;
		unsigned char full_res :1;
		unsigned char :1;
		unsigned char int_invert :1;
		unsigned char spi :1;
		unsigned char self_test :1;
	} data_format;

	struct{
		unsigned char samples :5;
		unsigned char trigger :1;
		unsigned char fifo_mode :2;
	} fifo_ctl;

	struct{
		unsigned char entries :6;
		unsigned char :1;
		unsigned char fifo_trig :1;
	} fifo_status;

	unsigned char byte;

} ADXL345_REG_FIELDS;



// Basic transactions //

void ADXL345_single_read(char reg, char *data)
{
	DEVICE_CS_CLEAR();
	DEVICE_SPI_TRANSCEIVE(reg | 0x80);
	*data = sci6_ADXL345_transceive(0xFF);
	DEVICE_CS_SET();
}

void ADXL345_single_write(char reg, char data)
{
	DEVICE_CS_CLEAR();
	DEVICE_SPI_TRANSCEIVE(reg);
	DEVICE_SPI_TRANSCEIVE(data);
	DEVICE_CS_SET();
}

void ADXL345_multi_read(char reg, char *data, int n)
{
	int i;
	char *p;

	DEVICE_CS_CLEAR();
	DEVICE_SPI_TRANSCEIVE(reg | 0x80 | 0x40);

	p = data;
	for(i = 0; i < n; i++){
		*p = DEVICE_SPI_TRANSCEIVE(0xff);
		p++;
	}
	DEVICE_CS_SET();
}

void ADXL345_multi_write(char reg, char *data, int n)
{
	int i;
	char *p;

	DEVICE_CS_CLEAR();
	DEVICE_SPI_TRANSCEIVE(reg | 0x40);

	p = data;
	for(i = 0; i < n; i++){
		DEVICE_SPI_TRANSCEIVE(*p);
		p++;
	}
	DEVICE_CS_SET();
}


// check if acceleration data is ready
bool ADXL345_ready()
{
	ADXL345_REG_FIELDS reg;
	char int_source;

	ADXL345_single_read(ADXL345_REG_INT_SOURCE, &(reg.byte));

	if(reg.int_map.data_ready == 1)
		return true;
	else
		return false;
}


// get acceleration data (16 bit format)
// data[0] : X data, data[1] : Y data, data[2] : Z data
void ADXL345_get(signed short *data)
{
	ADXL345_multi_read(ADXL345_REG_DATAX0, (char *)data, 6);
}


void ADXL345_set_rate(unsigned char rate)
{
	ADXL345_REG_FIELDS reg;

	ADXL345_single_read(ADXL345_REG_BW_RATE, &(reg.byte));
	reg.bw_rate.rate = rate;
	ADXL345_single_write(ADXL345_REG_BW_RATE, reg.byte);
}

void ADXL345_set_range(unsigned char range)
{
	char tmp;
	ADXL345_REG_FIELDS reg;

	ADXL345_single_read(ADXL345_REG_DATA_FORMAT, &(reg.byte) );
	reg.data_format.range = range;
	ADXL345_single_write(ADXL345_REG_DATA_FORMAT, reg.byte );
}


void ADXL345_config(ADXL345_CONF *conf)
{
	char data;
	ADXL345_REG_FIELDS reg;

	ADXL345_single_write(ADXL345_REG_INT_MAP, conf->int_map);

	ADXL345_single_write(ADXL345_REG_OFSX, conf->x_offset);
	ADXL345_single_write(ADXL345_REG_OFSY, conf->y_offset);
	ADXL345_single_write(ADXL345_REG_OFSZ, conf->z_offset);

	ADXL345_single_write(ADXL345_REG_THRESH_TAP, conf->thresh_tap);
	ADXL345_single_write(ADXL345_REG_DUR, conf->dur_tap);
	ADXL345_single_write(ADXL345_REG_LATENT, conf->latent_tap);
	ADXL345_single_write(ADXL345_REG_WINDOW, conf->window_tap);
	ADXL345_single_write(ADXL345_REG_THRESH_ACT, conf->thresh_act);
	ADXL345_single_write(ADXL345_REG_THRESH_INACT, conf->thresh_inact);
	ADXL345_single_write(ADXL345_REG_TIME_INACT, conf->time_inact);

	reg.act_inact_ctl.act_acdc = conf->act_acdc;
	reg.act_inact_ctl.act_x_enable = conf->act_x_enable;
	reg.act_inact_ctl.act_y_enable = conf->act_y_enable;
	reg.act_inact_ctl.act_z_enable = conf->act_z_enable;
	reg.act_inact_ctl.inact_acdc = conf->inact_acdc;
	reg.act_inact_ctl.inact_x_enable = conf->inact_x_enable;
	reg.act_inact_ctl.inact_y_enable = conf->inact_y_enable;
	reg.act_inact_ctl.inact_z_enable = conf->inact_z_enable;
	ADXL345_single_write(ADXL345_REG_ACT_INACT_CTL, reg.byte);

	reg.tap_axes.suppress = conf->suppress_tap;
	reg.tap_axes.tap_x_enable = conf->tap_x_enable;
	reg.tap_axes.tap_y_enable = conf->tap_y_enable;
	reg.tap_axes.tap_z_enable = conf->tap_z_enable;
	ADXL345_single_write(ADXL345_REG_TAP_AXES, reg.byte);

	reg.bw_rate.low_power = conf->low_power;
	reg.bw_rate.rate = conf->rate;
	ADXL345_single_write(ADXL345_REG_BW_RATE, reg.byte);

	ADXL345_single_read(ADXL345_REG_POWER_CTL, &(reg.byte) ); // get measure bit value
	reg.power_ctl.link = conf->link;
	reg.power_ctl.auto_sleep = conf->auto_sleep;
	reg.power_ctl.sleep = conf->sleep;
	reg.power_ctl.wakeup = conf->wakeup;
	ADXL345_single_write(ADXL345_REG_POWER_CTL, reg.byte);

	ADXL345_single_read(ADXL345_REG_DATA_FORMAT, &(reg.byte));
	reg.data_format.full_res = conf->full_res;
	reg.data_format.int_invert = conf->int_invert;
	reg.data_format.justfy = conf->justify;
	reg.data_format.range = conf->range;
	reg.data_format.spi = conf->spi;
	ADXL345_single_write(ADXL345_REG_DATA_FORMAT, reg.byte);


}

void ADXL345_get_default_config(ADXL345_CONF *conf)
{
	conf->rate = ADXL345_RATE_100;
	conf->low_power = 0;

	conf->int_map = 0x0;

	conf->x_offset = 0;
	conf->y_offset = 0;
	conf->z_offset = 0;

	conf->thresh_tap = 0;
	conf->dur_tap = 0;
	conf->latent_tap = 0;
	conf->window_tap = 0;
	conf->thresh_act = 0;
	conf->thresh_inact = 0;
	conf->time_inact = 0;

	// ACT_INACT_CTL
	conf->act_acdc = 0; 		// 1bit, 0 -> DC operation, 1 -> AC operation
	conf->act_x_enable = 0;
	conf->act_y_enable = 0;
	conf->act_z_enable = 0;

	conf->inact_acdc = 0; 	// 1bit, 0 -> DC operation, 1 -> AC operation
	conf->inact_x_enable = 0;
	conf->inact_y_enable = 0;
	conf->inact_z_enable = 0;

	// TAP_AXES
	conf->tap_x_enable = 0;
	conf->tap_y_enable = 0;
	conf->tap_z_enable = 0;
	conf->suppress_tap = 0; 	// 1bit

	conf->thresh_ff = 0; 	// 62.5mg/LSB, unsigned 8bit, 300~600mg(0x05~0x09) is recommended
	conf->time_ff = 0; 		// 5ms/LSB, unsigned 8bit, 100~350ms(0x14~0x46) is recommended

	// POWER_CTL register
	conf->link = 0; 			// 1bit
	conf->auto_sleep = 0; 	// 1bit
	conf->sleep = 0; 		// 1bit
	conf->wakeup = ADXL345_WAKEUP_8HZ; 		// 2bit code

	// DATA_FORMAT register
	conf->spi = 0; 			// 1bit, 0 -> 4 line SPI, 1 -> 3 line SPI
	conf->int_invert = 0;		// 1bit, 0 -> active high, 1 -> active low
	conf->full_res = 0;		// 1bit, 0 -> 10bit mode, 1 -> fixed scale 4mg/LSB
	conf->justify = 0;		// 1bit, 0 -> right justified, 1 -> left justified
	conf->range = ADXL345_RANGE_2G;			// 2bit code

	// FIFO_CTL register
	conf->fifo_mode = ADXL345_FIFO_MODE_BYPASS;		// 2bit code
	conf->trigger = 0;		// 1bit, 0 -> link trigger event to INT1, 1 -> to INT2
	conf->samples = 0;		// 5bit

}

void ADXL345_start()
{
	ADXL345_REG_FIELDS reg;
	// set Measure bit of POWER_CTL register
	ADXL345_single_read(ADXL345_REG_POWER_CTL, &(reg.byte) );
	reg.power_ctl.measure = 1;
	ADXL345_single_write(ADXL345_REG_POWER_CTL, reg.byte );
}

void ADXL345_stop()
{
	ADXL345_REG_FIELDS reg;
	// clear Measure bit of POWER_CTL register
	ADXL345_single_read(ADXL345_REG_POWER_CTL, &(reg.byte) );
	reg.power_ctl.measure = 0;
	ADXL345_single_write(ADXL345_REG_POWER_CTL, reg.byte );
}

// int_source : combination of ADXL345_INT_BIT_xxxx
void ADXL345_int_enable(unsigned char int_source)
{
	ADXL345_single_write(ADXL345_REG_INT_ENABLE, int_source);
}
void ADXL345_int_state(unsigned char *int_source)
{
	ADXL345_single_read(ADXL345_REG_INT_SOURCE, int_source);
}

void ADXL345_self_test_in()
{
	ADXL345_REG_FIELDS reg;

	ADXL345_single_read(ADXL345_REG_DATA_FORMAT, &(reg.byte) );
	reg.data_format.self_test = 1;
	ADXL345_single_write(ADXL345_REG_DATA_FORMAT, reg.byte );
}

void ADXL345_self_test_out()
{
	ADXL345_REG_FIELDS reg;

	ADXL345_single_read(ADXL345_REG_DATA_FORMAT, &(reg.byte) );
	reg.data_format.self_test = 0;
	ADXL345_single_write(ADXL345_REG_DATA_FORMAT, reg.byte );
}


// return : ADXL345_ACT_X, ADXL345_ACT_Y, or ADXL345_ACT_Z
unsigned char ADXL345_act_status()
{
	unsigned char rtn;

	ADXL345_single_read(ADXL345_REG_ACT_TAP_STATUS, &rtn);
	return (rtn & (~ADXL345_TAP_X) & (~ADXL345_TAP_Y) & (~ADXL345_TAP_Z));
}
// return : ADXL345_TAP_X, ADXL345_TAP_Y, or ADXL345_TAP_Z
unsigned char ADXL345_tap_status()
{
	unsigned char rtn;

	ADXL345_single_read(ADXL345_REG_ACT_TAP_STATUS, &rtn);
	return (rtn & (~ADXL345_ACT_X) & (~ADXL345_ACT_Y) & (~ADXL345_ACT_Z));
}

