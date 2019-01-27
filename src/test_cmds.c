/*
 * test_cmds.c
 *
 *  Created on: 2018/12/30
 *      Author: akicl
 */

//-------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "commandline.h"
#include "iodefine.h"
#include "hardware_lib.h"

#include "uart.h"
#include "timer_soft.h"

#include "lcdc_ST7735S.h"
#include "sdc.h"
#include "ADXL345.h"
#include "ff11/src/ff.h"
#include "fix_math.h"

#include "work_area.h"

//-------------------------------------------------------------------------------------------

#define N_TEST_BUF 1024
static uint8_t test_buf[N_TEST_BUF];

#define FNAME_LEN 256
static TCHAR ff_fname[FNAME_LEN];



//-------------------------------------------------------------------------------------------

// backspace is invalid in gets()
// use gets_pol() to validate backspace
char *gets_pol(char *s)
{
	while(!uart_kbhit_s())
			;
	return gets(s);
}

// wait for string input, fixed by Enter key
// If 'q' is pressed, abort and returns false
static bool gets_q(char *s, int n)
{
	char *p, *p_last;
	bool rtn;

	p = s;
	p_last = s + n - 1;

	while(p < p_last){

		*p = uart_getc();
		if(*p == 'q'){
			rtn = false;
			break;
		}
		else if( (*p == '\r') || (*p == '\n') ){
			rtn = true;
			*p = '\0'; // null termination
			break;
		}

		p++;
	}

	if(p == p_last)
		*p = '\0';

	return rtn;

}

//-------------------------------------------------------------------------------------------


//// Debug commands through serial interface ////

// Switch for each debug command groups

//#define DEBUG_SD
#define DEBUG_FS
#define DEBUG_GSENS
#define DEBUG_LCD


//---- Debug commands -----------------------

//---- List all valid commands ----//
void test_command_list();

//---- SD card test functions ----//
#ifdef DEBUG_SD

void test_cs();
void test_tx();
void test_txmulti();

void test_init();
void test_sread();
void test_swrite();
void test_mread();
void test_mwrite();
void test_blocksize();
void test_sectorcount();

#endif // DEBUG_SD

//---- File system functions ----//
#ifdef DEBUG_FS

void test_f_mount();
void test_f_umount();
void test_f_open(); // create new file
void test_f_write();
void test_f_stat();

void test_pwd();
void test_cd();
void test_ls();
void test_find();
void test_cat();
void test_mkdir();
void test_rm();

#endif // DEBUG_FS

//---- ADXL345 debug commands ----//
#ifdef DEBUG_GSENS

void test_adxl345_cs();
void test_adxl345_tx();
void test_adxl345_reg();
void test_adxl345_mon();
void test_adxl345_log();
void test_adxl345_logf();

#endif // DEBUG_GSENS

//---- LCD debug commands ----//
#ifdef DEBUG_LCD

void test_lcd_init();
void test_lcd_cs();
void test_lcd_rs();
void test_lcd_tx();
void test_lcd_fill();

void test_lcd_clk();
void test_lcd_rx();

void test_lcd_area();
void test_lcd_putc();
void test_lcd_puts();

void test_lcd_rinv();
void test_lcd_cinv();
void test_lcd_ainv();

#ifdef ST7735S_REG_ACCESS

void test_lcd_reg();
void test_lcd_open();
void test_lcd_write();
void test_lcd_read();
void test_lcd_close();

#endif // ST7735S_REG_ACCESS

#endif // DEBUG_LCD

//---- Miscellaneous tests ----//
void test_misc();

//-------------------------------------------

void print_bytes_matrix(uint8_t *buf, int count, int n_col, bool ascii);
unsigned char test_gpio(bool last, char opt);

//-------------------------------------------

COMMANDLINE_SET commandline_sets[] = {
		{"command", 	test_command_list}
#ifdef DEBUG_SD
		, {"cs", 		test_cs}
		, {"tx", 		test_tx}
		, {"txmulti", 	test_txmulti}
		, {"init", 		test_init}
		, {"sread", 	test_sread}
		, {"swrite", 	test_swrite}
		, {"mread", 	test_mread}
		, {"mwrite",	test_mwrite}
		, {"blocksize", test_blocksize}
		, {"sectorcount", test_sectorcount}
#endif // DEBUG_SD
#ifdef DEBUG_FS
		, {"f_mount", 	test_f_mount}
		, {"f_umount", 	test_f_umount}
		, {"f_open", 	test_f_open}
		, {"f_write", 	test_f_write}
		, {"f_stat", 	test_f_stat}
		, {"pwd", 		test_pwd}
		, {"cd", 		test_cd}
		, {"ls", 		test_ls}
		, {"find",		test_find}
		, {"cat", 		test_cat}
		, {"mkdir", 	test_mkdir}
		, {"rm",		test_rm}
#endif // DEBUG_FS
#ifdef DEBUG_GSENS
		, {"adxl345_cs", test_adxl345_cs}
		, {"adxl345_tx", test_adxl345_tx}
		, {"adxl345_reg", test_adxl345_reg}
		, {"adxl345_mon", test_adxl345_mon}
		, {"adxl345_log", test_adxl345_log}
		, {"adxl345_logf", test_adxl345_logf}
#endif // DEBUG_GSENS
#ifdef DEBUG_LCD
		, {"lcd_init", 	test_lcd_init}
		, {"lcd_cs", 	test_lcd_cs}
		, {"lcd_rs", 	test_lcd_rs}
		, {"lcd_tx", 	test_lcd_tx}
		, {"lcd_clk", 	test_lcd_clk}
		, {"lcd_rx", 	test_lcd_rx}
		, {"lcd_area",	test_lcd_area}
		, {"lcd_fill", 	test_lcd_fill}
		, {"lcd_putc",	test_lcd_putc}
		, {"lcd_puts",	test_lcd_puts}
		, {"lcd_rinv",	test_lcd_rinv}
		, {"lcd_cinv",	test_lcd_cinv}
		, {"lcd_ainv",	test_lcd_ainv}
#ifdef ST7735S_REG_ACCESS
		, {"lcd_reg", 	test_lcd_reg}
		, {"lcd_open",	test_lcd_open}
		, {"lcd_write",	test_lcd_write}
		, {"lcd_read",	test_lcd_read}
		, {"lcd_close",	test_lcd_close}
#endif // ST7735S_REG_ACCESS
#endif // DEBUG_LCD
		, {"misc",		test_misc}

};

const int n_commandline = (sizeof(commandline_sets) / sizeof(COMMANDLINE_SET));


//-------------------------------------------
// Function implementations
//-------------------------------------------

// command format : command
// (no argument)
// list all commands
void test_command_list()
{
	int i;

	printf("%s", commandline_sets[0].name);
	for(i = 1; i < n_commandline; i++)
		printf(", %s", commandline_sets[i].name);

	printf("\r\n");
}



//---- SD card test functions ----//
#ifdef DEBUG_SD

#define N_BLOCK_SD (N_TEST_BUF / 512)

// command format : cs [a]
// a : 0, l, or L -> set sd_cs pin LOW
//     1, h, or H -> set sd_cs pin HIGH
//     other or not specified -> alternate sd_cs pin state
void test_cs()
{
	char s[20];
	static bool last;

	commandline_get_arg(1, s, 20);
	SD_CS = ( last = test_gpio(last, s[0]) );
}

// command format : tx [a]
// a : data to send to SD card in hexadecimal (00 ~ ff)
//     up to 19 data are accepted (separated by space)
void test_tx()
{
	int i, n_bytes;
	uint8_t tx_bytes[19], rx_bytes[19];
	char s[20];

	n_bytes = commandline_narg() - 1;

	for(i = 0; i < n_bytes; i++){
		commandline_get_arg(i+1, s, 20);
		tx_bytes[i] = (uint8_t)strtoul(s, NULL, 16);
	}


	printf("input : ");
	for(i = 0; i < n_bytes; i++)
		printf("%#02x ", tx_bytes[i]);
	printf("\r\n");

	for(i = 0; i < n_bytes; i++)
		rx_bytes[i] = sci5_sd_transceive(tx_bytes[i]);

	printf("response : ");
	for(i = 0; i < n_bytes; i++)
		printf("%#02x ", rx_bytes[i]);
	printf("\r\n");

}

// command format : txmulti [a] [b]
// a : data to send to SD card in hexadecimal (00 ~ ff)
// b : count to send data (send data [a] for [b] times)
void test_txmulti()
{
	uint8_t data, rx_buf;
	int count, i;
	char s[20];

	if(!commandline_get_arg(1, s, 20)){
		printf("argument error\r\n");
		return;
	}
	data = (uint8_t)strtoul(s, NULL, 16);

	if(!commandline_get_arg(2, s, 20)){
		printf("argument error\r\n");
		return;
	}
	count = (int)strtoul(s, NULL, 10);

	printf("data : %02x, count %d\r\n", data, count);

	printf("received data : \r\n");
	for(i = 0; i < count; i++){
		rx_buf = sci5_sd_transceive(data);
		printf("%02x ", rx_buf);
		if( (i % 16) == 15 ) printf("\r\n");
	}
	printf("\r\n");

}

// command format : init
// (no argument)
// initialize SD card
void test_init()
{
	SDC_INIT_RESULT res;

	res = sdc_init();
	if(res.result == 0)
		printf("initialize succeeded\r\n");
	else
		printf("initialize failed, result : %#02x\r\n", res.result);
}

// command format : sread  [a] [b]
// a : read address by sector in hexadecimal
// b : "ascii" -> print the data to be translated by ascii code
//     else or not specified : print the data by hexadecimal (00 ~ ff)
void test_sread()
{
	unsigned long addr;
	SDC_RW_RESULT result;
	char s[20];

	bool ascii = false;


	if(commandline_get_arg(1, s, 20))
		addr = strtoul(s, NULL, 16);
	else{
		printf("no address\r\n");
		return;
	}

	if(commandline_get_arg(2, s, 20)){
		if(strcmp(s, "ascii") == 0)
			ascii = true;
	}

	result = sdc_SingleBlockRead(test_buf, addr);

	printf("result : %#02x %#02x %#02x %#02x\r\n",
			result.cmd_resp,
			result.err_token,
			result.cmd12_resp,
			result.prv);

	if(result.result)
		printf("single read failed\r\n");
	else{
		printf("data : \r\n");
		print_bytes_matrix(test_buf, 512, 16, ascii);
	}
}

// command format : swrite [a] [b]
// a : write address by sector in hexadecimal
// b : "ascii" -> write data are specified by ascii characters
//     else or not specified -> write data are specified by array of hexadecimal data
void test_swrite()
{
	unsigned long addr;
	SDC_RW_RESULT res;

	bool ascii = false;

	char s[100];

	int p_block;
	char *token;


	if(commandline_get_arg(1, s, 20))
		addr = strtoul(s, NULL, 16);
	else{
		printf("no address\r\n");
		return;
	}

	if(commandline_get_arg(2, s, 20)){
		if(strcmp(s, "ascii") == 0)
			ascii = true;
	}


	res = sdc_SingleBlockRead(test_buf, addr);
	if(res.result != 0)
		printf("data preload failed\r\n");
	else
		printf("data preloaded\r\n");

	printf("start byte : ");
	gets_pol(s);

	p_block = (uint8_t)strtoul(s, NULL, 16);

	printf("data to write : ");
	gets_pol(s);


	//// put data to write into the buffer ////
	if(ascii)
		strncpy((char *)test_buf, s, 512);
	else{
		token = strtok(s, " ");
		while(token != NULL){
			if(p_block >= 512)
				break;
			else{
				test_buf[p_block] = strtoul(token, NULL, 16);
				p_block++;
				token = strtok(NULL, " ");
			}
		}
	}

	printf("data block to write : \r\n");
	print_bytes_matrix(test_buf, 512, 16, ascii);

	printf("proceed to write data ? (y/n) : ");
	gets_pol(s);

	if( (s[0] == 'Y') || (s[0] == 'y') ){
		printf("start writing\r\n");

		res = sdc_SingleBlockWrite(test_buf, addr);

		printf("result : %#02x %#02x %#02x %#02x\r\n",
				res.cmd_resp,
				res.dat_resp,
				res.cmd12_resp,
				res.prv);
	}
	else
		printf("aborted\r\n");


}

// command format : mread  [a] [b]
// a : read address by sector in hexadecimal
// b : "ascii" -> print the data to be translated by ascii code
//     else or not specified : print the data by hexadecimal (00 ~ ff)
void test_mread()
{
	unsigned long addr;
	unsigned int count, i;
	char s[100];
	SDC_RW_RESULT result;

	bool ascii = false;


	if(commandline_get_arg(1, s, 20))
		addr = strtoul(s, NULL, 16);
	else{
		printf("no address\r\n");
		return;
	}

	if(commandline_get_arg(2, s, 20)){
		if(strcmp(s, "ascii") == 0)
			ascii = true;
	}

	printf("block count (0~%d) : ", N_BLOCK_SD);
	gets_pol(s);
	count = (unsigned int)strtoul(s, NULL, 10);
	if(count > N_BLOCK_SD)
		count = N_BLOCK_SD;

	result = sdc_MultiBlockRead(test_buf, addr, count);

	printf("result : %#02x %#02x %#02x %#02x\r\n",
			result.cmd_resp,
			result.err_token,
			result.cmd12_resp,
			result.prv);

	if(result.result)
		printf("multi block read failed\r\n");
	else{
		printf("data : \r\n");
		for(i = 0; i < count ; i++)
			print_bytes_matrix(test_buf+i*512, 512, 16, ascii);
	}
}

// command format : mwrite [a]
// a : write address by sector in hexadecimal
void test_mwrite()
{
	unsigned long addr;
	unsigned int count, i;
	char s[100];
	uint8_t fill_data;
	SDC_RW_RESULT result;


	if(commandline_get_arg(1, s, 20))
		addr = strtoul(s, NULL, 16);
	else{
		printf("no address\r\n");
		return;
	}

	printf("block count (0~%d) : ", N_BLOCK_SD);
	gets_pol(s);
	count = (unsigned int)strtoul(s, NULL, 10);
	if(count > N_BLOCK_SD)
		count = N_BLOCK_SD;

	printf("fill data byte : ");
	gets_pol(s);
	fill_data = (uint8_t)strtoul(s, NULL, 16);

	for(i = 0; i < count * 512; i++)
		test_buf[i] = fill_data;

	result = sdc_MultiBlockWrite(test_buf, addr, count);

	printf("result : %#02x %#02x %#02x %#02x\r\n",
			result.cmd_resp,
			result.dat_resp,
			result.cmd12_resp,
			result.prv);

}

// command format : blocksize
// (no argument)
// get erase block count of SD card
void test_blocksize()
{
	unsigned long res;

	res = sdc_EraseBlockSize();
	printf("erase block count : %d\r\n", res);

}

// command format : blocksize
// (no argument)
// get sector count of SD card
void test_sectorcount()
{
	unsigned long res;

	res = sdc_SectorCount();
	printf("sector count : %d\r\n", res);
	printf("capacity : %d [MB]\r\n", res >> 11);
}

#endif // DEBUG_SD


//---- File system functions ----//
#ifdef DEBUG_FS

// command format : f_mount
// media initialization is done in this function
void test_f_mount()
{
	FRESULT res;

	res = f_mount(&(wk.fatfs)
			, "SD1" // physical drive number :
			, 1 // option : 1 -> do mount action
			);

	printf("f_mount result : %d\r\n", res);
}

// command format : f_umount
void test_f_umount()
{
	FRESULT res;
	res = f_mount(NULL, "SD1", 1);
	printf("f_mount result : %d\r\n", res);
}

// command format : pwd
// (no argument)
void test_pwd()
{
	FRESULT res;

	res = f_getcwd(ff_fname, 256);
	printf("f_getcwd result : %d\r\n", res);

	if(res == FR_OK)
		printf("current directory : %s\r\n", ff_fname);
}


// command format : cd [a]
// a : directory name
void test_cd()
{
	FRESULT res;

	if(!commandline_get_arg(1, ff_fname, 256)){
		printf("no directory specified\r\n");
		return;
	}

	res = f_chdir(ff_fname);
	printf("f_chdir result : %d\r\n", res);

	if(res == FR_OK)
		printf("cd succeeded\r\n");
	else
		printf("cd failed\r\n");
}


// command format : ls
// (no argument)
void test_ls()
{
	FRESULT res;
	TCHAR *fn;
	int i;

	res = f_getcwd(ff_fname, 256);
	if(res != FR_OK){
		printf("f_getcwd failed : %d\r\n", res);
		return;
	}
	else
		printf("current directory : %s\r\n", ff_fname);

	res = f_opendir(&(wk.dj), ff_fname);
	if(res != FR_OK){
		printf("f_opendir failed : %d\r\n", res);
		return;
	}
	else
		printf("current directory opened\r\n");

	(wk.fno).lfname = ff_fname;
	(wk.fno).lfsize = FNAME_LEN;

	for(i = 0; i < 1000; i++){
		res = f_readdir(&(wk.dj), &(wk.fno));
		if(res != FR_OK){
			printf("f_readdir failed : %d\r\n", res);
			break;
		}

		if((wk.fno).fname[0] == '\0') // no more content
			break;

		if((wk.fno).lfname[0] == '\0')
			fn = (wk.fno).fname;
		else
			fn = (wk.fno).lfname;

		printf(" %3d ", i);

		if ((wk.fno).fattrib & AM_DIR)
            printf("DIR  : ");
        else
        	printf("FILE : ");

        printf("%s\r\n", fn);

	}
	f_closedir(&(wk.dj));

}

// command format : find [a]
// a : file or directory name matching pattern
void test_find()
{
	FRESULT res;
	char s[40];
	TCHAR *fn;

	if(!commandline_get_arg(1, s, 40)){
		s[0] = '*';
		s[1] = '\0';
	}

	(wk.fno).lfname = ff_fname;
	(wk.fno).lfsize = 256;
	res = f_findfirst(&(wk.dj), &(wk.fno), "", s);

	while ((res == FR_OK) && ((wk.fno).fname[0] != '\0')) {

		if((wk.fno).lfname[0] == '\0')
			fn = (wk.fno).fname;
		else
			fn = (wk.fno).lfname;

		if ((wk.fno).fattrib & AM_DIR)
            printf("DIR  : ");
        else
        	printf("FILE : ");
		printf("%s\r\n", fn);

		res = f_findnext(&(wk.dj), &(wk.fno));
	}
}

// command format : cat [a]
// a : file name
void test_cat()
{
	FRESULT res;
	unsigned int n_read;

	if(!commandline_get_arg(1, ff_fname, FNAME_LEN)){
		printf("no file specified\r\n");
		return;
	}

	res = f_open(&(wk.fl), ff_fname, FA_READ);

	if(res == FR_OK){
		do{
			res = f_read(&(wk.fl), (void *)test_buf, N_TEST_BUF, &n_read);
			if(res == FR_OK){
				printf("%s\r\n next? y -> next, else -> end", test_buf);
				if(uart_getc() == 'y')
					printf("\r\n");
				else
					break;
			}
			else{
				printf("f_read failed\r\n");
				break;
			}
		}while(n_read == N_TEST_BUF);
		printf("\r\n");
		f_close(&(wk.fl));
	}
	else if(res == FR_NO_FILE)
		printf("file does not exist\r\n");
	else
		printf("f_open failed\r\n");

}


// command format : f_open [a]
// a : file name
// create new file
void test_f_open()
{
	FRESULT res;

	if(!commandline_get_arg(1, ff_fname, FNAME_LEN)){
		printf("no file specified\r\n");
		return;
	}

	res = f_open(&(wk.fl), ff_fname, FA_READ | FA_CREATE_NEW);

	if(res == FR_OK){
		printf("f_open succeeded\r\n");
		f_close(&(wk.fl));
	}
	else if(res == FR_EXIST)
		printf("specified file already exists\r\n");
	else
		printf("f_open failed\r\n");

}

// command format : f_write [a] [b] [c]
// a : file name
// b : "ascii" -> input data are specified by ascii characters
//     else or not specified -> write data are specified by array of hexadecimal data
// c : "append" -> append to the end of the file
//     else or not specified -> overwrite
void test_f_write()
{
	FRESULT res;
	bool ascii = false, append = false;
	char s[100], *token;
	int n_data, i;
	unsigned int n_data_ret;

	if(!commandline_get_arg(1, ff_fname, FNAME_LEN)){
		printf("no file specified\r\n");
		return;
	}

	res = f_open(&(wk.fl), ff_fname, FA_WRITE);

	i = 2;
	while(commandline_get_arg(i, s, 100)){
		if(strcmp(s, "ascii") == 0)
			ascii = true;
		else if(strcmp(s, "append") == 0)
			append = true;

		i++;
	}

	if(res == FR_NO_FILE)
		printf("file does not exist\r\n");
	else if(res != FR_OK)
		printf("file open error\r\n");
	else{
		if(append){
			res = f_lseek(&(wk.fl), f_size(&(wk.fl)));
		}
		else{
			res = f_truncate(&(wk.fl));
		}

		printf("data to write : \r\n");
		gets_pol(s);

		//// put data to write into the buffer ////
		if(ascii){
			strncpy((char *)test_buf, s, N_TEST_BUF);
			n_data = strlen(test_buf);
		}
		else{
			n_data = 0;
			token = strtok(s, " ");
			while(token != NULL){
				if(n_data >= N_TEST_BUF)
					break;
				else{
					test_buf[n_data] = strtoul(token, NULL, 16);
					n_data++;
					token = strtok(NULL, " ");
				}
			}
		}

		printf("write data : \r\n %s\r\n", test_buf);
		printf("n_data : %d\r\n", n_data);
		printf("OK to write ? (y / n) : ");
		while(!uart_kbhit())
			;
		uart_putc('\r'); uart_putc('\n');
		if(uart_getc() != 'y'){
			printf("Aborted\r\n");
			f_close(&(wk.fl));
			return;
		}

		if(ascii){
			res = f_printf(&(wk.fl), "%s\r\n", (char *)test_buf);
			res = (res != 0) ? FR_OK : 1;
		}
		else
			res = f_write(&(wk.fl), test_buf, n_data, &n_data_ret);

		if(res == FR_OK)
			printf("f_write succeeded\r\n");
		else
			printf("f_write failed\r\n");

		f_close(&(wk.fl));
	}

}

void test_mkdir()
{
	FRESULT res;

	if(!commandline_get_arg(1, ff_fname, FNAME_LEN)){
		printf("no directory name specified\r\n");
		return;
	}

	res = f_mkdir(ff_fname);
	if(res == FR_OK)
		printf("f_mkdir succeeded\r\n");
	else
		printf("f_mkdir failed\r\n");

}

void test_f_stat()
{
    FRESULT fr;

	if(!commandline_get_arg(1, ff_fname, FNAME_LEN)){
		printf("no file or directory name specified\r\n");
		return;
	}

#if _USE_LFN
	wk.fno.lfname = 0;
#endif
    fr = f_stat(ff_fname, &(wk.fno));
    switch (fr) {

    case FR_OK:
        printf("Size: %u\r\n", wk.fno.fsize);
        printf("Timestamp: %u/%02u/%02u, %02u:%02u\r\n",
               (wk.fno.fdate >> 9) + 1980, wk.fno.fdate >> 5 & 15, wk.fno.fdate & 31,
               wk.fno.ftime >> 11, wk.fno.ftime >> 5 & 63);
        printf("Attributes: %c%c%c%c%c\r\n",
               (wk.fno.fattrib & AM_DIR) ? 'D' : '-',
               (wk.fno.fattrib & AM_RDO) ? 'R' : '-',
               (wk.fno.fattrib & AM_HID) ? 'H' : '-',
               (wk.fno.fattrib & AM_SYS) ? 'S' : '-',
               (wk.fno.fattrib & AM_ARC) ? 'A' : '-');
        break;

    case FR_NO_FILE:
        printf("File does not exist.\r\n");
        break;

    default:
        printf("An error occured. (%d)\r\n", fr);
    }
}


// command format : rm [a]
// a : file name
void test_rm()
{
	FRESULT res;

	if(!commandline_get_arg(1, ff_fname, FNAME_LEN)){
		printf("no file or directory name specified\r\n");
		return;
	}

	printf("OK to remove %s ? y/n\r\n", ff_fname);
	if(uart_getc() != 'y'){
		printf("Aborted\r\n");
		return;
	}

	res = f_unlink(ff_fname);
	if(res == FR_OK)
		printf("Succeeded\r\n");
	else
		printf("Failed, result = %d\r\n", res);
}


#endif // DEBUG_FS


//---- ADXL345 debug commands ----//
#ifdef DEBUG_GSENS

#define ADXL345_LOG_DEPTH (N_TEST_BUF / 6)


// command format : adxl345_cs [a]
// a : 0, l, or L -> set sd_cs pin LOW
//     1, h, or H -> set sd_cs pin HIGH
//     other or not specified -> alternate sd_cs pin state
void test_adxl345_cs()
{
	char s[20];
	static bool last;

	commandline_get_arg(1, s, 20);
	SCI6_ADXL345_CS = ( last = test_gpio(last, s[0]) );
}

// command format : adxl345_tx [a]
// a : data to send to SD card in hexadecimal (00 ~ ff)
//     up to 19 data are accepted (separated by space)
void test_adxl345_tx()
{
	int i, n_bytes;
	uint8_t tx_bytes[19], rx_bytes[19];
	char s[20];

	n_bytes = commandline_narg() - 1;

	for(i = 0; i < n_bytes; i++){
		commandline_get_arg(i+1, s, 20);
		tx_bytes[i] = (uint8_t)strtoul(s, NULL, 16);
	}

	printf("input : ");
	for(i = 0; i < n_bytes; i++)
		printf("%#02x ", tx_bytes[i]);
	printf("\r\n");

	for(i = 0; i < n_bytes; i++)
		rx_bytes[i] = sci6_ADXL345_transceive(tx_bytes[i]);


	printf("response : ");
	for(i = 0; i < n_bytes; i++)
		printf("%#02x ", rx_bytes[i]);
	printf("\r\n");

}

// command format : adxl345_reg [a] [b] [c]
// a : "W" or "w" -> write operation,
//     "R" or "r" -> read operation
// b : register address in hexadecimal
// c : number of multi access in decimal (optional)
void test_adxl345_reg()
{
	char s[20];
	char addr, wdata[20];
	bool r_w;
	int n_transfer, i;


	while(uart_kbhit()) uart_getc(); // clear UART buffer

	if(commandline_get_arg(1, s, 20)){
		if( (s[0] == 'W') || (s[0] == 'w') )
			r_w = false;
		else if( (s[0] == 'R') || (s[0] == 'r') )
			r_w = true;
		else{
			printf("R or W must be specified\r\n");
			return;
		}

	}
	else{
		printf("R or W must be specified\r\n");
		return;
	}

	if(!commandline_get_arg(2, s, 20)){
		printf("address must be specified\r\n");
		return;
	}
	else
		addr = strtoul(s, NULL, 16);

	if(commandline_get_arg(4, s, 20)){
		n_transfer = strtoul(s, NULL, 10);
		if(n_transfer > 20)
				n_transfer = 20;
	}
	else
		n_transfer = 1;

	if(r_w){
		if(n_transfer > 1)
			ADXL345_multi_read(addr, s, n_transfer);
		else
			ADXL345_single_read(addr, s);

		printf("read data : \r\n");
		printf("%x", s[0]);
		for(i = 1; i < n_transfer; i++){
			printf(", %x", s[i]);
		}
		printf("\r\n");
	}
	else{
		printf("data to write : \r\n");
		for(i = 0; i < n_transfer; i++){
			gets_pol(s);
			wdata[i] = strtoul(s, NULL, 16);
		}

		if(n_transfer > 1)
			ADXL345_multi_write(addr, wdata, n_transfer);
		else
			ADXL345_single_write(addr, wdata[0]);
	}


}


void test_adxl345_mon()
{
	signed short data[3], data_last[3];
	signed short xs, xe, ys, ye;

	printf("\r\nADXL345 monitoring\r\npress any key to quit\r\n");
	printf("    X,    Y,    Z\r\n");

	xs = 0; xe = 159; ys = 0; ye = 127;
	lcdc_set_area(xs, xe, ys, ye);

	ADXL345_start();
	ADXL345_int_enable(ADXL345_INT_BIT_DATA_READY);

	while(!uart_kbhit()){
		while(!ADXL345_ready()) ;
		ADXL345_get(data);
		printf("%5d,%5d,%5d\r", data[0], data[1], data[2]);

		lcdc_fill(LCDC_BLACK);
		lcdc_fill_area(0x8410, 80,80,0,127);
		lcdc_fill_area(0x8410, 0,159,64,64);
		lcdc_fill_area(LCDC_BLUE
				, (- data[1] >> 3) + 80 - 1
				, (- data[1] >> 3) + 80 + 1
				, (- data[0] >> 3) + 64 - 1
				, (- data[0] >> 3) + 64 + 1);

	}

	ADXL345_stop();
	ADXL345_int_enable(0x0);

	while(uart_kbhit()) uart_getc(); // clear UART buffer
}


_SWORD curve_adxl345_x(_UWORD t)
{
	return (((_SWORD *)test_buf)[t*3] >> 3);
}

_SWORD curve_adxl345_y(_UWORD t)
{
	return (((_SWORD *)test_buf)[t*3+1] >> 3);
}

_SWORD curve_adxl345_z(_UWORD t)
{
	return (((_SWORD *)test_buf)[t*3+2] >> 3);
}


void test_adxl345_log()
{
	signed short *p_data;
	int i;

	printf("\r\nADXL345 logging\r\n");
	printf("log depth : %d\r\n", ADXL345_LOG_DEPTH);
	printf("press any key to start\r\n");

	while(!uart_kbhit()) ;
	while(uart_kbhit()) uart_getc(); // clear UART buffer

	p_data = (signed short *)test_buf;

	ADXL345_start();
	ADXL345_int_enable(ADXL345_INT_BIT_DATA_READY);

	for(i = 0; i < ADXL345_LOG_DEPTH; i++){
		while(!ADXL345_ready()) ;
		ADXL345_get(p_data);

		p_data += 3;
	}

	p_data = (signed short *)test_buf;
	printf("stored data\r\n");
	printf("    i,    X,    Y,    Z\r\n");
	for(i = 0; i < ADXL345_LOG_DEPTH; i++){
		printf("%5d, %5d, %5d, %5d\r\n", i, p_data[0], p_data[1], p_data[2]);
		p_data += 3;
	}

	ADXL345_stop();
	ADXL345_int_enable(0x0);

	printf("\r\n");
	while(uart_kbhit()) uart_getc(); // clear UART buffer

	lcdc_fill_area(LCDC_BLACK, 0, 0x9F, 0, 0x7F);
	lcdc_draw_curve(curve_adxl345_x, 64, LCDC_RED, 0, 0x9F, 0, 0x7F);
	lcdc_draw_curve(curve_adxl345_y, 64, LCDC_GREEN, 0, 0x9F, 0, 0x7F);
	lcdc_draw_curve(curve_adxl345_z, 64, LCDC_BLUE, 0, 0x9F, 0, 0x7F);

}


void test_adxl345_logf()
{
	FRESULT res;
	signed short data[3];
	int i, j;


//	f_open(&(wk.fl), "adxl345_log.csv", FA_OPEN_ALWAYS);
	f_open(&(wk.fl), "adxl345_log.csv", FA_WRITE);
	f_lseek(&(wk.fl), f_size(&(wk.fl))); // move cursor to end position

	f_printf(&(wk.fl), "\r\n----\r\n");
	printf("Start logging\r\n");

	ADXL345_start();
	ADXL345_int_enable(ADXL345_INT_BIT_DATA_READY);

	while(!uart_kbhit()){

		for(i = 0; i < LCDC_ROW; i++){
			while(!ADXL345_ready())
				;
			ADXL345_get(data);
			f_printf(&(wk.fl), "%d,%d,%d\r\n", data[0], data[1], data[2]);
			printf(".");
		}
	}

	ADXL345_stop();
	ADXL345_int_enable(0x0);

	f_close(&(wk.fl));
}

#endif // DEBUG_GSENS


//---- LCD debug commands ----//
#ifdef DEBUG_LCD

// LCD
void test_lcd_init()
{
	lcdc_init();
	printf("LCD initialization completed\r\n");
}

void test_lcd_cs()
{
	char s[20];
	static bool last;

	commandline_get_arg(1, s, 20);
	LCD_CS = ( last = test_gpio(last, s[0]) );
}

void test_lcd_rs()
{
	char s[20];
	static bool last;

	commandline_get_arg(1, s, 20);
	LCD_RS = ( last = test_gpio(last, s[0]) );
}

void test_lcd_nrst()
{
	char s[20];
	static bool last;

	commandline_get_arg(1, s, 20);
	LCD_NRST = ( last = test_gpio(last, s[0]) );
}

void test_lcd_tx()
{
	int i, n_bytes;
	uint8_t tx_bytes[19];
	char s[20];

	n_bytes = commandline_narg() - 1;

	for(i = 0; i < n_bytes; i++){
		commandline_get_arg(i+1, s, 20);
		tx_bytes[i] = (uint8_t)strtoul(s, NULL, 16);
	}

	printf("input : ");
	for(i = 0; i < n_bytes; i++)
		printf("%#02x ", tx_bytes[i]);
	printf("\r\n");

	for(i = 0; i < n_bytes; i++)
		sci12_LCD_transmit(tx_bytes[i]);
}

void test_lcd_clk()
{
	sci12_LCD_com_mode(SCI12_GPIORX); // GPIO RX mode

	sci12_LCD_dummy_clock();

	sci12_LCD_com_mode(SCI12_SPITX); // SPI TX mode
}

void test_lcd_rx()
{
	sci12_LCD_com_mode(SCI12_GPIORX); // GPIO RX mode

	printf("%x\r\n", sci12_LCD_read());

	sci12_LCD_com_mode(SCI12_SPITX); // SPI TX mode
}


// command format : lcd_area [xs] [xe] [ys] [ye]
// xs : horizontal start point
// xe : horizontal end point
// ys : vertical start point
// ye : vertical end point
void test_lcd_area()
{
	char s[20];
	bool failed = false;

	_UWORD xs, xe, ys, ye;

	if(commandline_get_arg(1, s, 20))
		xs = strtoul(s, NULL, 16);
	else
		failed = true;

	if(commandline_get_arg(2, s, 20))
		xe = strtoul(s, NULL, 16);
	else
		failed = true;

	if(commandline_get_arg(3, s, 20))
		ys = strtoul(s, NULL, 16);
	else
		failed = true;

	if(commandline_get_arg(4, s, 20))
		ye = strtoul(s, NULL, 16);
	else
		failed = true;

	if(failed)
		printf("insufficient arguments\r\n");
	else
		lcdc_set_area(xs, xe, ys, ye);
}


// command format : lcd_fill [r] [g] [b]
// r : RED brightness (in hexadecimal)
// g : GREEN brightness (in hexadecimal)
// b : BLUE brightness (in hexadecimal)
void test_lcd_fill()
{
	_UWORD color, color_r, color_g, color_b;
	char s[20];
	unsigned long tm;

	if(!commandline_get_arg(3, s, 20))
		printf("color argument is missing\r\n");
	else{
		color_b = (_UWORD)strtoul(s, NULL, 16);

		commandline_get_arg(2, s, 20);
		color_g = (_UWORD)strtoul(s, NULL, 16);

		commandline_get_arg(1, s, 20);
		color_r = (_UWORD)strtoul(s, NULL, 16);
	}

	color = (color_r << 11) | (color_g << 5) | color_b;
	printf("color:%x\r\n", color);

	timer_soft_reset(&tm);
	lcdc_fill(color);

	printf("Elapsed time : %dms\r\n", timer_soft_count(&tm));
}

// command format : lcd_test [a] [b] [c]
// a : character to display
// b : x position (hexadecimal)
// c : y position (hexadecimal)
void test_lcd_putc()
{
	_UWORD x, y;
	char c;
	char s[20];
	bool failed = false;

	if(commandline_get_arg(3, s, 20))
		y = strtoul(s, NULL, 16);
	else
		failed = true;

	if(commandline_get_arg(2, s, 20))
		x = strtoul(s, NULL, 16);
	else
		failed = true;

	if(commandline_get_arg(1, s, 20))
		c = s[0];
	else
		failed = true;

	if(failed)
		printf("insufficient arguments\r\n");
	else
		lcdc_putchar(c, LCDC_WHITE, x, y);

}

void test_lcd_puts()
{
	char s[100];
	printf("string to display : \r\n");
	gets_pol(s);

	lcdc_puts(s, LCDC_WHITE, 0,0);
}

void test_lcd_rinv()
{
	lcdc_row_invert();
}

void test_lcd_cinv()
{
	lcdc_col_invert();
}

void test_lcd_ainv()
{
	lcdc_row_col_exchange();
}

#ifdef ST7735S_REG_ACCESS

// command format : lcd_reg [a] [b]
// a : "W" or "w" -> write operation,
//     "R" or "r" -> read operation
// b : register address in hexadecimal
void test_lcd_reg()
{
	char s[20];
	unsigned char addr;
	ST7735S_REG_TYPE r_w;
	int n_transfer, i;
	bool no_read = true;


	while(uart_kbhit()) uart_getc(); // clear UART buffer

	if(commandline_get_arg(1, s, 20)){
		if( (s[0] == 'W') || (s[0] == 'w') )
			r_w = REG_W;
		else if( (s[0] == 'R') || (s[0] == 'r') )
			r_w = REG_R;
		else{
			printf("R or W must be specified\r\n");
			return;
		}

	}
	else{
		printf("R or W must be specified\r\n");
		return;
	}

	if(!commandline_get_arg(2, s, 20)){
		printf("address must be specified\r\n");
		return;
	}
	else{
		addr = strtoul(s, NULL, 16);
	}

	if(!ST7735S_open(addr, r_w))
		printf("ST7735S_open failed\r\n");
	else
		printf("opened ST7735S register\r\n");


	if(r_w == REG_R){
		test_lcd_read();
	}
	else if(r_w == REG_W){
		test_lcd_write();
	}

	ST7735S_close();

}

// command format : lcd_open [a] [b]
// a : "W" or "w" -> write operation,
//     "R" or "r" -> read operation
// b : register address in hexadecimal
void test_lcd_open()
{
	char s[20];
	unsigned char addr;
	ST7735S_REG_TYPE r_w;
	int n_transfer, i;
	bool no_read = true;


	while(uart_kbhit()) uart_getc(); // clear UART buffer

	if(commandline_get_arg(1, s, 20)){
		if( (s[0] == 'W') || (s[0] == 'w') )
			r_w = REG_W;
		else if( (s[0] == 'R') || (s[0] == 'r') )
			r_w = REG_R;
		else{
			printf("R or W must be specified\r\n");
			return;
		}

	}
	else{
		printf("R or W must be specified\r\n");
		return;
	}

	if(!commandline_get_arg(2, s, 20)){
		printf("address must be specified\r\n");
		return;
	}
	else{
		addr = strtoul(s, NULL, 16);
	}

	if(!ST7735S_open(addr, r_w))
		printf("ST7735S_open failed\r\n");
	else
		printf("opened ST7735S register\r\n");

}


void test_lcd_write()
{
	char s[20];
	unsigned char data;

	while(1){
		printf("data to write (q:end) : \r\n");

		if(!gets_q(s, 20))
			break;

		timer_soft_wait(10);
		while(uart_kbhit())
			uart_getc(); // clear UART buffer

		data = (unsigned char)strtoul(s, NULL, 16);
		printf("write data : %x\r\n", data);
		ST7735S_write(&data, 1);

		}

}

void test_lcd_read()
{
	char c;
	int n_transfer;
	unsigned char data;

	while(1){
		n_transfer = ST7735S_read(&data, 1);
		if(n_transfer){
			printf("read data (n:continue,else:end) : %x\r\n", data);

			c = uart_getc();
			uart_putc('\b');

			while(uart_kbhit())
				uart_getc();

			if(c != 'n')
				break;
		}
		else{
			printf("No more to read\r\n");
			break;
		}
	}

}

void test_lcd_close()
{
	ST7735S_close();
}


#endif // ST7735S_REG_ACCESS

#endif // DEBUG_LCD


//---- Miscellaneous tests ----//

void test_misc()
{
	unsigned long tm, tm_d;
	float d1, d2, d3;
	double d4, d5, d6, d6_sqrt;
	int d7;
	int i;

	FIX_T f1, f2, f3;
	FIX_T f4, f5, f6;

	d1 = 14.5444;
	d2 = 522.055;
	d4 = d1;
	d5 = d2;

	f1 = fix_fl2fix(d1);
	f2 = fix_fl2fix(d2);

	// Multiply float values
	d3 = d2;
	timer_soft_reset(&tm);
	for(i = 0; i < 1000; i++){
//		d3 = d3 * 1.04;
		d3 = d1 * d2;
	}
	tm_d = timer_soft_count(&tm);
	printf("d3 = %f, Elapsed time : %d\r\n", d3, tm_d);

	// Multiply fix values
	timer_soft_reset(&tm);
	for(i = 0; i < 1000; i++){
		f3 = fix_mul(f1, f2);
	}
	tm_d = timer_soft_count(&tm);
	printf("f1 : %d, f2 : %d\r\n", f1, f2);
	printf("f3 = %d.%d, Elapsed time : %d\r\n", fix_fix2int(f3), fix_frac_dec(f3, 4), tm_d);

	// f4 = -f1;	f5 = f2;	f6 = fix_mul(f4, f5);
	// printf("f6 : %d (%08x)\r\n", fix_fix2int(f6), f6);
	// f4 = -f1;	f5 = -f2;	f6 = fix_mul(f4, f5);
	// printf("f6 : %d (%08x)\r\n", fix_fix2int(f6), f6);

	printf("d1 * d2 = %f\r\n", d1 * d2);
	printf("d4 * d5 = %f\r\n", d4 * d5);

	d7 = INT32_MAX;
	d6 = (double)d7;
	d6 *= 100;
	printf("d7 : %d, d6 : %f\r\n", d7, d6);

	timer_soft_reset(&tm);
	d6_sqrt = sqrt(d6);
	tm_d = timer_soft_count(&tm);
	printf("sqrt(d6) = %f, Elapsed time : %d\r\n", d6_sqrt, tm_d);

}


//-------------------------------------------
// Sub funtions
//-------------------------------------------

unsigned char test_gpio(bool last, char opt)
{
	bool rtn;

	if(opt == '\0')
		rtn = !last;
	else if( (opt == '0') || (opt == 'L') || (opt == 'l') )
		rtn = false;
	else
		rtn = true;

	printf("port level => ");
	if(rtn)
		uart_putc('H');
	else
		uart_putc('L');

	uart_putc('\r'); uart_putc('\n');

	return rtn;
}

#ifdef DEBUG_SD

void print_bytes_matrix(uint8_t *buf, int count, int n_col, bool ascii)
{
	int i, j;
	uint8_t tmp;

	for(i = 0; i < 1000; i++){
		printf("%#8x : ", i);
		for(j = 0; j < n_col; j++){
			if(i*n_col + j >= count){
				i++;
				break;
			}
			tmp = buf[i*n_col + j];
			if(ascii){
				if( (tmp < 0x20) | (tmp > 0x7e) ){
//						printf("xx ");
					printf("%02x ", tmp);
				}
				else
					printf(" %c ", tmp);
			}
			else{
				printf("%02x ", tmp);
			}
		}
		printf("\r\n");
		if(i*n_col >= count)
			break;
	}
	printf("\r\n");

}

#endif // DEBUG_SD

