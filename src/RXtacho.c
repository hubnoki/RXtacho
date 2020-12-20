/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  RXtacho                                */
/*      FILE         :  RXtacho.c                              */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RX200                                  */
/*      CPU TYPE     :  RX220                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                                
                                                                           
                                                                           
/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


#include "iodefine.h"
#include "hardware_lib.h"

#include "uart.h"
#include "timer_soft.h"
#include "lcdc_ST7735S.h"
#include "sdc.h"
#include "ADXL345.h"
#include "commandline.h"

#include "errno.h"

#include "ff11/src/ff.h"

#include "fix_math.h"
#include "fft4g_fix.h"

#include "work_area.h"

#include "han_window.h"

#ifdef CPPAPP
//Initialize global constructors
extern "C" void __main()
{
  static int initialized;
  if (! initialized)
    {
      typedef void (*pfunc) ();
      extern pfunc __ctors[];
      extern pfunc __ctors_end[];
      pfunc *p;

      initialized = 1;
      for (p = __ctors_end; p > __ctors; )
    (*--p) ();

    }
}
#endif 


#define PRINTF printf

//-------------------------------------------------------------------------------------------
// Local variables

#define DISP_INT_INTVL 0

#define RX_BUF_N 100
static char rx_buf[RX_BUF_N];

const char commandline_header[] = "RX UART > ";


#define MODE_LOGGING	0
#define MODE_FFT		1
#define MODE_METER		2
#define MODE_SETTING	3

#define PSW_READY			0
#define PSW_WAIT_RELEASE	1
#define PSW_SHORT_PUSHED	2

#define AXIS_X			0
#define AXIS_Y			1
#define AXIS_Z			2

#define N_GBUF			512
#define N_IP			32		// >= 2+sqrt(N_GBUF/2)
#define N_W				640		// = N_GBUF * 5 / 4

#define SEL_A			0
#define SEL_B			1

#define SHORT_PUSH_TH_MS		1000

#define LOG_FMT_BIN		0
#define LOG_FMT_CSV		1

#define STG_ST_STG		0
#define STG_ST_VAL		1

//---------------------

typedef struct{
	char *name;
	unsigned int val;
} ST_VALUE_UNIT;


static const ST_VALUE_UNIT value_list_axis[] = {
	{"X"	, AXIS_X}
	, {"Y"	, AXIS_Y}
	, {"Z"	, AXIS_Z}
};

static const ST_VALUE_UNIT value_list_log_fmt[] = {
	{"BIN", LOG_FMT_BIN}
	, {"CSV", LOG_FMT_CSV}
};

static const ST_VALUE_UNIT value_list_rate[] = {
	{"3200" 	, ADXL345_RATE_3200}
	, {"1600" 	, ADXL345_RATE_1600}
	, {"800" 	, ADXL345_RATE_800}
	, {"400" 	, ADXL345_RATE_400}
	, {"200" 	, ADXL345_RATE_200}
	, {"100" 	, ADXL345_RATE_100}
	, {"50" 	, ADXL345_RATE_50}
	, {"25" 	, ADXL345_RATE_25}
	, {"12R5" 	, ADXL345_RATE_12R5}
	, {"6R5" 	, ADXL345_RATE_6R5}
	, {"3R13" 	, ADXL345_RATE_3R13}
	, {"1R56" 	, ADXL345_RATE_1R56}
	, {"0R78" 	, ADXL345_RATE_0R78}
	, {"0R39" 	, ADXL345_RATE_0R39}
	, {"0R20" 	, ADXL345_RATE_0R20}
	, {"0R10" 	, ADXL345_RATE_0R10}
};

static const ST_VALUE_UNIT value_list_range[] = {
	{"2G"		, ADXL345_RANGE_2G}
	, {"4G"		, ADXL345_RANGE_4G}
	, {"8G"		, ADXL345_RANGE_8G}
	, {"16G"	, ADXL345_RANGE_16G}
};

static const ST_VALUE_UNIT value_list_fft_scale[] = {
	{"0", 0}
	, {"9", 9}
	, {"8", 8}
	, {"7", 7}
	, {"6", 6}
	, {"5", 5}
	, {"4", 4}
	, {"3", 3}
	, {"2", 2}
	, {"1", 1}
};


typedef struct{
	char *name;
	uint8_t nval;
	const ST_VALUE_UNIT *list;
} ST_SETTING_UNIT;

static enum {
	STG_AXIS,
	STG_LOGFMT,
	STG_RATE,
	STG_RANGE,
	STG_FFTSCALE,
	STG_EXIT
} STG_ENUM;

static const ST_SETTING_UNIT setting_list[] = {
	{"axis"			, sizeof(value_list_axis) / sizeof(ST_VALUE_UNIT)		, value_list_axis}
	, {"log_fmt"	, sizeof(value_list_log_fmt) / sizeof(ST_VALUE_UNIT)	, value_list_log_fmt}
	, {"rate"		, sizeof(value_list_rate) / sizeof(ST_VALUE_UNIT)		, value_list_rate}
	, {"range"		, sizeof(value_list_range) / sizeof(ST_VALUE_UNIT)		, value_list_range}
	, {"fft_scale"	, sizeof(value_list_fft_scale) / sizeof(ST_VALUE_UNIT)	, value_list_fft_scale}
	, {"exit"		, 1, NULL}
};

//---------------------

// Flags of log data
// 	flags.bit0    overrun - Overrun occurred, overwriting data which are not read
//  flags.bit1    measureIntCnt - Data contains measurement interval count
typedef union{
	struct{
		uint8_t overrun : 1;
		uint8_t measureIntCnt : 1;
	};
	uint16_t wd;
} LOG_FLAGS;

typedef struct{
	signed short d;
	LOG_FLAGS flags;
} LOG_UNIT;

#define N_LOGBUF (2*sizeof(FIX_T)*N_GBUF / sizeof(LOG_UNIT))

static struct{
	uint8_t 		mode;
	uint8_t			mode_init;
	ADXL345_CONF 	adxl345_cfg;
	uint8_t 		axis_sel;

	uint8_t			psw_state;
	unsigned long	psw_tm;

	union{
		LOG_UNIT g_buf[N_LOGBUF];
		struct{
			FIX_T g_buf_a[N_GBUF];
			FIX_T g_buf_b[N_GBUF];
		};
	};

	uint8_t 		g_buf_sel; // Buffer side to save G sensor data
	uint16_t 		g_buf_wp_a;
	uint16_t 		g_buf_wp_b;
	uint16_t		g_buf_wcnt_a; // For logging mode
	uint16_t 		g_buf_rp;
	uint16_t		g_buf_rcnt; // For logging mode
	uint8_t 		g_overrun;
	uint8_t			g_buf_filled; // All elements of the buffer are filled with valid data

	uint16_t		g_int_intvl;
	uint16_t		g_int_cnt_last;
	uint8_t			g_int_update;

	uint8_t 		logging;
	int				log_sqno; // Sequential number for log file
	int				log_format;

	int 			fft_disp_scale;
	int				fft_disp_scale_auto;

	int				setting_state;
	int				cur_setting_idx;
	uint8_t			cur_value_idx[sizeof(setting_list)/sizeof(ST_SETTING_UNIT)];

	int 			fft_ip[N_IP];
	FIX_T			fft_w[N_W];

}vars;



//-------------------------------------------------------------------------------------------
// Interrupt routines

void adxl345_int_routine()
{
	signed short d[3];
	FIX_T f;
	LOG_UNIT log_d;
	uint16_t int_cnt = ADXL345_INT_CNTR;

	// if(vars.g_int_update == 0){
	// 	vars.g_int_intvl = int_cnt - vars.g_int_cnt_last;
	// 	vars.g_int_update = 1;
	// }
	// vars.g_int_cnt_last = int_cnt;

	ADXL345_get(d);

	// Put data into buffer
	if(vars.logging){

		if(vars.g_buf_wp_a == 0){
			// Measure the interval to fill the buffer
			vars.g_int_intvl = int_cnt - vars.g_int_cnt_last;
			vars.g_int_cnt_last = int_cnt;
		}

		log_d.d = d[vars.axis_sel];
		log_d.flags.wd = 0;
		log_d.flags.overrun = (vars.g_overrun = (vars.g_buf_wcnt_a - vars.g_buf_rcnt) >= N_LOGBUF-1);

		vars.g_buf[vars.g_buf_wp_a] = log_d;

		if(++vars.g_buf_wp_a >= N_LOGBUF){
			vars.g_buf_wp_a = 0;
			vars.g_buf_filled = 1;
		}
		vars.g_buf_wcnt_a++;
	}
	else{
		if(vars.g_buf_sel == SEL_A){
			if(vars.g_buf_wp_a < N_GBUF){
				vars.g_buf_a[vars.g_buf_wp_a] = fix_int2fix((int)d[vars.axis_sel]);
				vars.g_buf_wp_a++;
				if(vars.g_buf_wp_a == N_GBUF-1){
					// Measure the interval to fill the buffer
					vars.g_int_intvl = int_cnt - vars.g_int_cnt_last;
					vars.g_int_cnt_last = int_cnt;
				}
			}
			else{
				// Update last counter value while waiting for buffer read
				vars.g_int_cnt_last = int_cnt;
			}
		}
		else{
			if(vars.g_buf_wp_b < N_GBUF){
				vars.g_buf_b[vars.g_buf_wp_b] = fix_int2fix((int)d[vars.axis_sel]);;
				vars.g_buf_wp_b++;
				if(vars.g_buf_wp_b == N_GBUF-1){
					// Measure the interval to fill the buffer
					vars.g_int_intvl = int_cnt - vars.g_int_cnt_last;
					vars.g_int_cnt_last = int_cnt;
				}
			}
			else{
				// Update last counter value while waiting for buffer read
				vars.g_int_cnt_last = int_cnt;
			}
		}
	}
}

void psw_routine(void)
{
	if(vars.psw_state == PSW_READY){
		if(PSW_PIN == 0){
			timer_soft_reset(&(vars.psw_tm));
			vars.psw_state = PSW_WAIT_RELEASE;
		}
	}
	else if(vars.psw_state == PSW_WAIT_RELEASE){
		if(PSW_PIN == 1){
			if(timer_soft_count(&(vars.psw_tm)) < SHORT_PUSH_TH_MS)
				vars.psw_state = PSW_SHORT_PUSHED;
		}
	}
}

//-------------------------------------------------------------------------------------------

static void adxl345_start()
{
	signed short d[3];

	ADXL345_get(d); // clear data buffer
	adxl345int1_int_enable();
	ADXL345_int_enable(ADXL345_INT_BIT_DATA_READY);
	ADXL345_start();
}

static void adxl345_stop()
{
	signed short d[3];

	adxl345int1_int_disable();
	ADXL345_int_enable(0x0); // disable all interrupts
	ADXL345_stop();
	ADXL345_get(d); // clear data buffer
}

static inline FRESULT mount_SD(FATFS * fs)
{
	return f_mount(fs
			, "SD1" // physical drive number :
			, 1 // option : 1 -> do mount action
			);
}

static inline FRESULT umount_SD()
{
	return f_mount(0, "SD1", 1);
}

/**
 * @brief 	Get the sequential number for the next file
 * 			Sequential number is expected to exist before ".[extention]" in the file name
 * 
 * @param f_hdr		File name header, and '*' should be added last
 * 					e.g.	"adxl345_log_000.csv", "adxl345_log_001.csv", ... -> "adxl345_log_*"
 * @param sqno 		Sequential number for next file		
 * @return int		Result (0 -> Success, 1 -> Error)
 */
static int get_file_sqno(char f_hdr[], int *sqno)
{
	int i;
	FRESULT res;
	char *sqno_top;
	int sqno_len;
	char s_sqno[11];
	int sqno_tmp;

	wk.fno.lfname = wk.fname;
	wk.fno.lfsize = WK_N_FNAME;

	res = mount_SD(&(wk.fatfs));
	if(res != FR_OK){
		PRINTF("SD open failed\r\n");
		return 1;
	}

	*sqno = 0;
	res = f_findfirst(&(wk.dj), &(wk.fno), "", f_hdr);
	while ((res == FR_OK) && wk.fno.fname[0]) {
		// printf("%s\r\n", wk.fno.lfname);

		// strlen(f_hdr) = actual length + 1 (+1 for '*' character)
		if(strlen(f_hdr) > strlen(wk.fno.lfname)) // File name with only f_hdr
			continue;
		sqno_top = &(wk.fno.lfname[strlen(f_hdr)-1]);
		sqno_len = strcspn(wk.fno.lfname, ".") - (strlen(f_hdr) - 1);
		// printf("sqno_len : %d\r\n", sqno_len);

		strncpy(s_sqno, sqno_top, sqno_len);
		s_sqno[sqno_len] = '\0';
		for(i = 0; i < sqno_len; i++){
			if(!isdigit(s_sqno[i])) break; // Not valid as a number
		}

		sqno_tmp = atoi(s_sqno);
		// printf("sqno_tmp : %d\r\n", sqno_tmp);
		if(sqno_tmp >= *sqno)
			*sqno = sqno_tmp + 1;

		res = f_findnext(&(wk.dj), &(wk.fno));
	}

	umount_SD();	

	return 0;
}

// f[0] : Real part
// f[1] : Imaginary part
static double fix_cabs(FIX_T *f)
{
	int i1;
	double d1, d2;

	i1 = fix_fix2int(f[0]); // Re
	d1 = i1 * i1;// Re^2
	d2 = d1;

	i1 = fix_fix2int(f[1]); // Im
	d1 = i1 * i1; // Im^2
	d2 += d1;

	return sqrt(d2);
}

static _SWORD FFT_curve(_UWORD x, FIX_T *buf)
{
	double d3;

	d3 = fix_cabs(&(buf[x*4]));
	d3 += fix_cabs(&(buf[x*4+2]));

	return (d3 < (double)INT16_MAX) ? (_SWORD)d3 : INT16_MAX;
}

static _SWORD FFT_curve_a(_UWORD x)
{
	_SWORD rtn;
	if(vars.fft_disp_scale == 0){
		if(vars.fft_disp_scale_auto != 0)
			rtn = FFT_curve(x, vars.g_buf_a) / vars.fft_disp_scale_auto;
		else
			rtn = FFT_curve(x, vars.g_buf_a);
	}
	else
		rtn = FFT_curve(x, vars.g_buf_a) >> vars.fft_disp_scale;

	return rtn;
}

static _SWORD FFT_curve_b(_UWORD x)
{
	_SWORD rtn;
	if(vars.fft_disp_scale == 0){
		if(vars.fft_disp_scale_auto != 0)
			rtn = FFT_curve(x, vars.g_buf_b) / vars.fft_disp_scale_auto;
		else
			rtn = FFT_curve(x, vars.g_buf_b);
	}
	else
		rtn = FFT_curve(x, vars.g_buf_b) >> vars.fft_disp_scale;

	return rtn;
}

static void FFT_set_scale(FIX_T *buf)
{
	_SWORD tmp1, tmp2;
	_UWORD i;
	FIX_T *p_buf;

	tmp1 = 0;
	for(i = 1; i < 128; i++){ // Ignore DC level
		tmp2 = FFT_curve(i, buf);
		if(tmp2 > tmp1) tmp1 = tmp2;
	}
	vars.fft_disp_scale_auto = tmp1 / 100;
	if(vars.fft_disp_scale_auto == 0)
		vars.fft_disp_scale_auto = 1;
}


// return : 0 -> Success, 1 -> Error
static int FFT_log()
{
	FRESULT res;
	int sqno, i;
	int prres = 0;
	int rtn = 0;

	if(get_file_sqno("adxl345_FFT_*", &sqno)){
		return 1;
	}

	res = mount_SD(&(wk.fatfs));
	if(res != FR_OK){
		PRINTF("SD open failed\r\n");
		return 1;
	}

	sprintf(wk.fname, "adxl345_FFT_%03d.csv", sqno);
//	PRINTF("File name : %s\r\n", wk.fname);
	res = f_open(&(wk.fl), wk.fname, FA_WRITE | FA_CREATE_NEW);
	if(res){
		PRINTF("File open failed, res=%d\r\n", res);
		rtn = 1;
	}
	else{
		for(i = 0; i < N_GBUF/2; i++){
			if(vars.g_buf_sel == SEL_A){
				prres = f_printf(&(wk.fl), "%d,%d\r\n", vars.g_buf_b[i*2], vars.g_buf_b[i*2+1]);
			}
			else{
				prres = f_printf(&(wk.fl), "%d,%d\r\n", vars.g_buf_a[i*2], vars.g_buf_a[i*2+1]);
			}

			if(prres == EOF){
				rtn = 1;
				break;
			}
		}
		prres = f_printf(&(wk.fl), "\r\n");
		if(prres == EOF){
			rtn |= 1;
		}

		for(i = 0; i < 128; i++){
			if(vars.g_buf_sel == SEL_A){
				prres = f_printf(&(wk.fl), "%d\r\n", FFT_curve_b((unsigned short)i));
			}
			else{
				prres = f_printf(&(wk.fl), "%d\r\n", FFT_curve_a((unsigned short)i));
			}

			if(prres == EOF){
				rtn |= 1;
				break;
			}
		}
		f_close(&(wk.fl));
	}

	f_mount(0, "SD1", 1); //unmount

	return rtn;
}


//-------------------------------------------------------------------------------------------

static void proc_logging(uint8_t spush, uint8_t lpush);
static void proc_FFT(uint8_t spush, uint8_t lpush);
static void proc_meter(uint8_t spush, uint8_t lpush);
static void proc_setting(uint8_t spush, uint8_t lpush);


int main(void)
{
	char s[50];
	int i;
	unsigned long psw_cnt;
	uint8_t psw_spush, psw_lpush;

//---------------------------------------------------------
	vars.mode = MODE_LOGGING;
	vars.mode_init = 1;
	vars.psw_state = PSW_READY;
	vars.g_buf_sel = SEL_A;
	vars.g_buf_wp_a = 0;
	vars.g_buf_wp_b = 0;
	vars.g_buf_rp = 0;
	vars.g_overrun = 0;
	vars.g_buf_filled = 0;
	vars.logging = 0;

	vars.g_int_update = 0;

	vars.fft_disp_scale_auto = 0;

	vars.setting_state = STG_ST_STG;
	vars.cur_setting_idx = 0;

	vars.cur_value_idx[STG_AXIS] = 2;
	vars.axis_sel = AXIS_Z;
	vars.cur_value_idx[STG_LOGFMT] = 0;
	vars.log_format = LOG_FMT_BIN;
	vars.cur_value_idx[STG_RATE] = 0;
	vars.cur_value_idx[STG_RANGE] = 0;
	vars.cur_value_idx[STG_FFTSCALE] = 0;
	vars.fft_disp_scale = 0;
	vars.cur_value_idx[STG_EXIT] = 0;

	vars.fft_ip[0] = 0;

	psw_cnt = 0;
	psw_spush = 0;
	psw_lpush = 0;

//---------------------------------------------------------
	uart_set(rx_buf, RX_BUF_N);
	sci1_uart_tx_enable();
	sci1_uart_rx_enable();

//---------------------------------------------------------
	LCD_NPWR = 0;
	lcdc_init();
	LCD_LED = 1;
	lcdc_fill(LCDC_BLACK);

//---------------------------------------------------------
	adxl345_stop();
	adxl345int1_int_set_callback(adxl345_int_routine);

	ADXL345_get_default_config(&(vars.adxl345_cfg));
	vars.adxl345_cfg.int_map = 0;
	vars.adxl345_cfg.int_invert = 1;
	vars.adxl345_cfg.rate = (uint8_t)(setting_list[STG_RATE].list[vars.cur_value_idx[STG_RATE]].val);
	vars.adxl345_cfg.range = (uint8_t)(setting_list[STG_RANGE].list[vars.cur_value_idx[STG_RANGE]].val);
	ADXL345_config(&(vars.adxl345_cfg));


//---------------------------------------------------------
	psw_int_disable();
	psw_int_set_callback(psw_routine);
	psw_int_enable();

//---------------------------------------------------------
	PRINTF("\r\n\r\n");
	PRINTF("**** program start ****\r\n");
	PRINTF("Built on e2studio version 6.2.0\r\n");

	//---------------------------------------------------------
	PRINTF(commandline_header);
	
    while (1) {

		// Display ADXL345 interrupt interval
		if(vars.g_int_update == 1){
			PRINTF("%8d\r\n", vars.g_int_intvl);
			vars.g_int_update = 0;
		}

		//// Serial commands ////
		if(uart_kbhit_s()){
    		uart_gets(s);

    		if(!commandline_input(s))
    			PRINTF("illegal command\r\n");

    		uart_puts("\r\n");
    		PRINTF(commandline_header);
    	}

		//// Check for PSW ////
		psw_spush = 0;
		psw_lpush = 0;
		psw_cnt = timer_soft_count(&(vars.psw_tm));
		if(vars.psw_state == PSW_SHORT_PUSHED)
			psw_spush = 1;
		else if(vars.psw_state == PSW_WAIT_RELEASE){
			if(psw_cnt >= SHORT_PUSH_TH_MS)
				psw_lpush = 1;
		}

		//// Process for each mode ////
		//---------
		if(vars.mode == MODE_LOGGING){
			proc_logging(psw_spush, psw_lpush);
		}
		//---------
		else if(vars.mode == MODE_FFT){
			proc_FFT(psw_spush, psw_lpush);
		}
		//---------
		else if(vars.mode == MODE_METER){
			proc_meter(psw_spush, psw_lpush);
		}
		//---------
		else if(vars.mode == MODE_SETTING){
			proc_setting(psw_spush, psw_lpush);
		}

		//// Clear flags for PSW ////
		if((psw_spush == 1) || (psw_lpush == 1))
			vars.psw_state = PSW_READY;

    }

    return 0;
}



//-------------------------------------------------------------------------------------------
// Process for logging mode 
//-------------------------------------------------------------------------------------------
static unsigned long tm, tmax; // For measuring process time

#include "iodefine.h"

static FRESULT write_log_header_bin(FIL *f)
{
	FRESULT fres = 0;
	unsigned int tmp;
	unsigned int btw;

	// Header identifier
	tmp = 'LOGH';
	fres |= f_write(f, &tmp, sizeof(int), &btw);
	// Header version
	tmp = 2;
	fres |= f_write(f, &tmp, sizeof(int), &btw);
	// Header contents size (in bytes)
	tmp = 12;
	fres |= f_write(f, &tmp, sizeof(int), &btw);
	//// Header contents ////
	// Rate setting
	tmp = value_list_rate[vars.cur_value_idx[STG_RATE]].val;
	fres |= f_write(f, &tmp, sizeof(int), &btw);
	// Range setting
	tmp = value_list_range[vars.cur_value_idx[STG_RANGE]].val;
	fres |= f_write(f, &tmp, sizeof(int), &btw);
	// Time measurement interval
	tmp = (N_LOGBUF & 0xFFFF) | (CMT1.CMCR.BIT.CKS << 16);
	fres |= f_write(f, &tmp, sizeof(int), &btw);

	return fres;
}

static void proc_logging(uint8_t spush, uint8_t lpush)
{
	int fres = 0;
	unsigned int btw;
	unsigned long td;

	if(vars.mode_init){
		lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 0, LCDC_COL-1);
		lcdc_puts("Logging mode", LCDC_WHITE, 0, 0);
		lcdc_puts("Short push to start", LCDC_WHITE, 0, 10);
		vars.mode_init = 0;
	}

	if(vars.logging == 0){
		// Start logging
		if(spush){
			fres = 0;

			fres |= get_file_sqno("adxl345_log_*", &(vars.log_sqno));
			fres |= (mount_SD(&(wk.fatfs)) != FR_OK);

			if(vars.log_format == LOG_FMT_CSV)
				sprintf(wk.fname, "adxl345_log_%03d.csv", vars.log_sqno);
			else
				sprintf(wk.fname, "adxl345_log_%03d.bin", vars.log_sqno);
			fres |= (f_open(&(wk.fl), wk.fname, FA_WRITE | FA_CREATE_NEW) != FR_OK);

			lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 0, LCDC_COL-1);
			if(fres){
				lcdc_puts("File open failed", LCDC_WHITE, 0, 0);
				lcdc_puts("Short push to start", LCDC_WHITE, 0, 10);
			}
			else{
				sprintf(wk.fname, "Logging ... (%d)", vars.log_sqno);
				lcdc_puts(wk.fname, LCDC_WHITE, 0, 0);
				lcdc_puts("Short Push to stop ", LCDC_WHITE, 0, 10);

				// Log file header
				if(vars.log_format == LOG_FMT_CSV){
					fres = (
						f_printf(&(wk.fl), "rate:%d, range:%d\r\n"
							, value_list_rate[vars.cur_value_idx[STG_RATE]].val
							, value_list_range[vars.cur_value_idx[STG_RANGE]].val
						)
					== EOF);
				}
				else{
					fres = write_log_header_bin(&(wk.fl));
				}
				vars.logging = 1;
				vars.g_buf_wp_a = 0;
				vars.g_buf_wcnt_a = 0;
				vars.g_buf_rp = 0;
				vars.g_buf_rcnt = 0;
				vars.g_buf_filled = 0;
				adxl345_start();
			}

			timer_soft_reset(&tm);
			tmax = 0;
		}
		else if(lpush){
			// Mode change
			vars.mode = MODE_FFT;
			vars.mode_init = 1;
		}
	}
	else{
		// Stop logging
		if(spush){
			adxl345_stop();
			vars.logging = 0;
			f_close(&(wk.fl));
			umount_SD();

			PRINTF("Max process interval : %d\r\n", tmax);

			vars.mode_init = 1; // Return to the initial step
		}
		// Continue logging
		else{
			td = timer_soft_count(&tm);
			timer_soft_reset(&tm);
			if(td > tmax)
				tmax = td;

			if(vars.g_buf_wcnt_a != vars.g_buf_rcnt){ // There remains unread data
				unsigned int tmp = 0;
				LOG_UNIT logData = vars.g_buf[vars.g_buf_rp];
				unsigned int ovrn = vars.g_overrun;

				if(vars.log_format == LOG_FMT_CSV){
					fres = (
							f_printf(&(wk.fl), "%d,%d\r\n"
							, logData.d, logData.flags.wd)
						== EOF);
				}
				else if(vars.log_format == LOG_FMT_BIN){
					fres |= f_write(&(wk.fl), &logData, sizeof(LOG_UNIT), &btw);

					// Write measure interval count after g data
					if((vars.g_buf_rp == 0) && vars.g_buf_filled){
						logData.d = vars.g_int_intvl;
						logData.flags.measureIntCnt = 1;
						fres |= f_write(&(wk.fl), &logData, sizeof(unsigned int), &btw);
					}

				}

				if(ovrn == 1){
					vars.g_buf_rp = vars.g_buf_wp_a;
					vars.g_buf_rcnt = vars.g_buf_wcnt_a;
					vars.g_overrun = 0;
				}
				else{
					if(++vars.g_buf_rp >= N_LOGBUF) vars.g_buf_rp = 0;
					vars.g_buf_rcnt++;
				}

				if(fres){ // f_write() or f_printf() failed
					adxl345_stop();
					vars.logging = 0;
					f_close(&(wk.fl));
					umount_SD();
//					lcdc_puts("File write failed", LCDC_WHITE, 0, 0);
					sprintf(wk.fname, "File write failed:%d", fres);
					lcdc_puts(wk.fname, LCDC_WHITE, 0, 0);
					lcdc_puts("Short push to start", LCDC_WHITE, 0, 10);

				}
			}
		}
	}

}

//-------------------------------------------------------------------------------------------
// Process for FFT mode 
//-------------------------------------------------------------------------------------------
static void proc_FFT(uint8_t spush, uint8_t lpush)
{
	int i;

	if(vars.mode_init){
		adxl345_stop();
		lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 0, LCDC_COL-1);
		lcdc_puts("FFT mode", LCDC_WHITE, 0, 0);
		vars.g_buf_sel = SEL_A;
		vars.g_buf_wp_a = 0;
		vars.g_buf_wp_b = 0;
		vars.g_int_cnt_last = ADXL345_INT_CNTR;
		adxl345_start();
		vars.mode_init = 0;
	}

	if(vars.g_buf_sel == SEL_A){
		if(vars.g_buf_wp_a == N_GBUF){
			vars.g_buf_sel = SEL_B;
			for(i = 0; i < 512; i++)
				vars.g_buf_a[i] = fix_mul(vars.g_buf_a[i], han_window_fix16_512[i]); // Window function
			rdft_fix(N_GBUF, -1, vars.g_buf_a, vars.fft_ip, vars.fft_w);
			if(vars.fft_disp_scale == 0)
				FFT_set_scale(vars.g_buf_a);
			lcdc_fill_area(LCDC_BLACK, 0, 127, 8, 119);
			lcdc_fill_area(0x8410, 0,127,120,120); // Zero level line
			lcdc_draw_curve(FFT_curve_a, 120, 1, LCDC_GREEN
				, 0, 127, 9, 120);
			vars.g_buf_wp_a = 0;
		}
	}
	else{
		if(vars.g_buf_wp_b == N_GBUF){
			vars.g_buf_sel = SEL_A;
			for(i = 0; i < 512; i++)
				vars.g_buf_b[i] = fix_mul(vars.g_buf_b[i], han_window_fix16_512[i]); // Window function
			rdft_fix(N_GBUF, -1, vars.g_buf_b, vars.fft_ip, vars.fft_w);
			if(vars.fft_disp_scale == 0)
				FFT_set_scale(vars.g_buf_b);
			lcdc_fill_area(LCDC_BLACK, 0, 127, 8, 119);
			lcdc_fill_area(0x8410, 0,127,120,120); // Zero level line
			lcdc_draw_curve(FFT_curve_b, 120, 1, LCDC_GREEN
				, 0, 127, 9, 120);
			vars.g_buf_wp_b = 0;
		}
	}

	if(spush){
		lcdc_puts("Saving ...", LCDC_WHITE, 0, 0);
		FFT_log();
		lcdc_puts("FFT mode  ", LCDC_WHITE, 0, 0);
	}
	else if(lpush){
		// Mode change
		adxl345_stop();
		vars.mode = MODE_METER;
		vars.mode_init = 1;
	}

}

//-------------------------------------------------------------------------------------------
// Process for meter mode 
//-------------------------------------------------------------------------------------------


const double tbl_spectrum_ratio[] = 
{
	0.33333
	, 0.37931
	, 0.42857
	, 0.48148
	, 0.53846
	, 0.60000
	, 0.66667
	, 0.73913
	, 0.81818
	, 0.90476
	, 1.00000
	, 1.10526
	, 1.22222
	, 1.35294
	, 1.50000
	, 1.66667
	, 1.85714
	, 2.07692
	, 2.33333
	, 2.63636
	, 3.00000
};

#define N_SPECTRUM_RATIO (sizeof(tbl_spectrum_ratio)/sizeof(double))
#define SPECTRUM_FRAC_UNIT ((double)1.0/N_SPECTRUM_RATIO)
#define MAX_FREQ_IDX 64

static int calc_rpm(FIX_T *fft_result, double df)
{
	int i;
	FIX_T *p = fft_result + 2;
	double amp;
	double amp_max = 0;
	int idx_max = 0;
	double amp_max_m1, amp_max_p1;
	double amp_mean = 0;
	bool updated_max = false;
	double amp_ratio;
	double frac;
	int rtn;

	// Find the index with maximum amplitude (Except DC level)
	for(i = 1; i < MAX_FREQ_IDX; i++){

		amp = fix_cabs(p);
		p += 2;
		amp_mean += amp;

		if(updated_max){
			amp_max_p1 = amp;
		}

		if(amp > amp_max){
			amp_max_m1 = amp_max;
			amp_max = amp;
			idx_max = i;
			updated_max = true;
		}
		else{
			updated_max = false;
		}
	}
	amp_mean /= (MAX_FREQ_IDX-1);

//	PRINTF("%f, %d, %f, %f, %f\r\n", amp_max, idx_max, amp_max_m1, amp_max_p1, amp_mean);

	// Find the fractional value of the actual frequency
	// Calculate rpm
	frac = -1.0;
	if((amp_max_p1 > amp_mean) && (amp_max_m1 > amp_mean)){
		amp_ratio = amp_max_p1 / amp_max_m1;
		for(i = 0; i < N_SPECTRUM_RATIO; i++){
			if(amp_ratio < tbl_spectrum_ratio[i]){
				rtn = (int)((idx_max + frac) * df * 60);
				// PRINTF("%d, %f\r\n", i, amp_ratio);
				break;
			}
			frac += SPECTRUM_FRAC_UNIT;
			if(i == N_SPECTRUM_RATIO-1)
				rtn = (int)(idx_max * df * 60);
		}
	}
	else{
		rtn = (int)(idx_max * df * 60);
	}

	return rtn;

}

static void proc_meter(uint8_t spush, uint8_t lpush)
{
	int i;
	int rpm;
	char s[10];
	unsigned int tm, tm_d;

	if(vars.mode_init){
		adxl345_stop();
		lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 0, LCDC_COL-1);
		lcdc_puts("METER mode", LCDC_WHITE, 0, 0);
		lcdc_puts_x4("rpm", LCDC_GREEN, 88, 48);
		vars.g_buf_sel = SEL_A;
		vars.g_buf_wp_a = 0;
		vars.g_buf_wp_b = 0;
		vars.g_int_cnt_last = ADXL345_INT_CNTR;
		adxl345_start();
		vars.mode_init = 0;
	}

	if(vars.g_buf_sel == SEL_A){
		if(vars.g_buf_wp_a == N_GBUF){
//t			timer_soft_reset(&tm);
			vars.g_buf_sel = SEL_B;
			// for(i = 0; i < 512; i++)
			// 	vars.g_buf_a[i] = fix_mul(vars.g_buf_a[i], han_window_fix16_512[i]); // Window function
			rdft_fix(N_GBUF, -1, vars.g_buf_a, vars.fft_ip, vars.fft_w);

			//// Calculate and display rotation frequency
			rpm = calc_rpm(vars.g_buf_a, (1.0 / 25.6e-6) / (double)(vars.g_int_intvl));
			if(rpm > 10000) rpm = 9999;
			sprintf(s, "%4d", rpm/10*10);
			lcdc_puts_x4(s, LCDC_GREEN, 0, 48);

//t			tm_d = timer_soft_count(&tm);
//t			PRINTF("Elapsed : %d\r\n", tm_d);

			vars.g_buf_wp_a = 0;
		}
	}
	else{
		if(vars.g_buf_wp_b == N_GBUF){
//t			timer_soft_reset(&tm);
			vars.g_buf_sel = SEL_A;
			// for(i = 0; i < 512; i++)
			// 	vars.g_buf_b[i] = fix_mul(vars.g_buf_b[i], han_window_fix16_512[i]); // Window function
			rdft_fix(N_GBUF, -1, vars.g_buf_b, vars.fft_ip, vars.fft_w);

			//// Calculate and display rotation frequency
			rpm = calc_rpm(vars.g_buf_b, (1.0 / 25.6e-6) / (double)(vars.g_int_intvl));
			if(rpm > 10000) rpm = 9999;
			sprintf(s, "%4d", rpm/10*10);
			lcdc_puts_x4(s, LCDC_GREEN, 0, 48);

//t			tm_d = timer_soft_count(&tm);
//t			PRINTF("Elapsed : %d\r\n", tm_d);

			vars.g_buf_wp_b = 0;
		}
	}

	if(lpush){
		// Mode change
		adxl345_stop();
		vars.mode = MODE_SETTING;
		vars.mode_init = 1;
	}

}

//-------------------------------------------------------------------------------------------
// Process for setting mode 
//-------------------------------------------------------------------------------------------
static void proc_setting(uint8_t spush, uint8_t lpush)
{
	int i;
	uint8_t u8_tmp;
	uint8_t *u8_tmp_p;
	unsigned int tmp;

	if(vars.mode_init || (lpush && (vars.setting_state == STG_ST_VAL))){
		/*
		 * Just have entered into setting mode
		 * , or long push to return from value setting state to item selection state.
		 */

		// Show mode name
		if(vars.mode_init){
			lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 0, 8);
			lcdc_puts("SETTING mode", LCDC_WHITE, 0, 0);
			vars.mode_init = 0;
		}
		// Show setting list
		lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 9, LCDC_COL-1);
		for(i = 0; i < (sizeof(setting_list)/sizeof(ST_SETTING_UNIT)); i++){
			lcdc_puts(setting_list[i].name, LCDC_WHITE, 6, (i+1)*9); // Add one character space on top for selection mark
		}
		// Selection mark
		lcdc_putchar('*', LCDC_WHITE, 0, (vars.cur_setting_idx+1)*9);
		vars.setting_state = STG_ST_STG;
	}
	else if(lpush && (vars.setting_state == STG_ST_STG)){
		/*
		 * Long push to go into value setting state
		 */

		// "exit" menu -> Apply setting values and go to next mode
		if(strcmp(setting_list[vars.cur_setting_idx].name, "exit") == 0){
			u8_tmp = (uint8_t)(setting_list[STG_AXIS].list[vars.cur_value_idx[STG_AXIS]].val);
			vars.axis_sel = u8_tmp;
			vars.log_format = setting_list[STG_LOGFMT].list[vars.cur_value_idx[STG_LOGFMT]].val;
			u8_tmp = (uint8_t)(setting_list[STG_RATE].list[vars.cur_value_idx[STG_RATE]].val);
			ADXL345_set_rate(u8_tmp);
			u8_tmp = (uint8_t)(setting_list[STG_RANGE].list[vars.cur_value_idx[STG_RANGE]].val);
			ADXL345_set_range(u8_tmp);
			tmp = setting_list[STG_FFTSCALE].list[vars.cur_value_idx[STG_FFTSCALE]].val;
			vars.fft_disp_scale = tmp;

			vars.cur_setting_idx = STG_AXIS;
			vars.mode = MODE_LOGGING;
			vars.mode_init = 1;
		}
		// Other menu -> Show value list
		else{
			lcdc_fill_area(LCDC_BLACK, 0, LCDC_ROW-1, 9, LCDC_COL-1);
			for(i = 0; i < setting_list[vars.cur_setting_idx].nval; i++){
				lcdc_puts(setting_list[vars.cur_setting_idx].list[i].name, LCDC_WHITE, 6, (i+1)*9); // Add one character space on top for selection mark
			}
			// Selection mark
			lcdc_putchar('*', LCDC_WHITE, 0, (vars.cur_value_idx[vars.cur_setting_idx]+1)*9);
			vars.setting_state = STG_ST_VAL;
		}

	}

	if(spush){
		if(vars.setting_state == STG_ST_STG){
			// Increment setting index
			lcdc_putchar(' ', LCDC_WHITE, 0, (vars.cur_setting_idx+1)*9);
			if(++(vars.cur_setting_idx) >= sizeof(setting_list) / sizeof(ST_SETTING_UNIT))
				vars.cur_setting_idx = 0;
			lcdc_putchar('*', LCDC_WHITE, 0, (vars.cur_setting_idx+1)*9);
		}
		else{
			// Increment value index
			u8_tmp_p = &(vars.cur_value_idx[vars.cur_setting_idx]);
			lcdc_putchar(' ', LCDC_WHITE, 0, (*u8_tmp_p+1)*9);
			if(++(*u8_tmp_p) >= setting_list[vars.cur_setting_idx].nval)
				*u8_tmp_p = 0;
			lcdc_putchar('*', LCDC_WHITE, 0, (*u8_tmp_p+1)*9);
		}
	}

}


