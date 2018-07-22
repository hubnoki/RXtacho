/*
 * sdc.c
 *
 *  Created on: 2015/08/10
 *      Author: akihiro
 *
 *  2016/02/21 kinoshita
 *  	modified for RXtacho project
 *
 *  2016/11/29 kinoshita
 *      fixed bug of "sdc_SendStatus()"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "typedefine.h"
#include "sdc.h"
#include "hardware_lib.h"
#include "timer_soft.h"


#define SDC_DEBUG_PRINT 0

//// Hardware dependent functions ////

#pragma inline(DEVICE_SPI_TRANSCEIVE)
static uint8_t DEVICE_SPI_TRANSCEIVE(uint8_t d)
{
//	while(!SCI5_SD_TX_END)
//		;
//	while(!SCI5_SD_TXI)
//		;
//	SCI5_SD_TXI = 0;

	SCI5_SD_TXDATA = d;
	while(!SCI5_SD_TX_END)
		;

	while(!SCI5_SD_RXI)
		;
	SCI5_SD_RXI = 0;
	return (_UBYTE)SCI5_SD_RXDATA;

}

#pragma inline(DEVICE_CS_CLEAR)
static void DEVICE_CS_CLEAR(void){SD_CS = 0;}
#pragma inline(DEVICE_CS_SET)
static void DEVICE_CS_SET(void){SD_CS = 1;}

static void DEVICE_BAUD_SET_HIGH()
{
	sci5_sd_set_baud_high();
}

static void DEVICE_BAUD_SET_LOW()
{
	sci5_sd_set_baud_low();
}
#define START_BLOCK_TOKEN	 	0xFE
#define START_BLOCK_TOKEN_MWRT 	0xFC
#define STOP_TRAN_TOKEN 		0xFD

#define DAT_RESP_AMASK 0x1F//0b00011111
#define DAT_RESP_ACCEPTED 0x05//0b00000101
#define DAT_RESP_CRC_ERR 0x0B//0b00001011
#define DAT_RESP_WRITE_ERR 0x0D//0b00001101


static bool sdc_v2; // V2.00 or later ?
static bool sdc_hc; // High Capacity ? (or Standard Capacity)


//static uint8_t tx_buf_i[20];
//static uint8_t rx_buf_i[20];

//static uint8_t dummy_buf[512]; // set all 0xff


static bool send_command(uint8_t cmd_id, unsigned long arg, uint8_t *resp1);
static bool wait_response(uint8_t *resp1);
static bool wait_busy();


//// initialize this driver
//void sdc_drvinit(void)
//{
//	int i;
//	for(i = 0; i < 512; i++) dummy_buf[i] = 0xff;
//}



SDC_INIT_RESULT sdc_init(void)
{
	int i;
	uint8_t resp;
	bool timeout_tmp;

	SDC_INIT_RESULT res;

#if SDC_DEBUG_PRINT
	printf("SD initialization\r\n");
#endif

	res.result = 0;

	DEVICE_CS_SET();
	DEVICE_BAUD_SET_LOW();

	// 80 clock (dummy clock) and data are 0xFF
	for(i = 0; i < 10; i++)
		DEVICE_SPI_TRANSCEIVE(0xFF);

#if SDC_DEBUG_PRINT
	printf("dummy clock sent\r\n");
#endif

	DEVICE_CS_CLEAR();

	// CMD0 :
	if( !send_command(0, 0, &resp) ){
		res.cmd0_timeout = 1;
		DEVICE_CS_SET();
		return res;
	}

#if SDC_DEBUG_PRINT
	printf("CMD0 sent\r\n");
#endif

	// CMD8 : check if the card is V2.00 or later
	if( send_command(8, 0x1AA, &resp) ){
		if(resp == 0x01){ // V2.00 or later
			sdc_v2 = true;
			DEVICE_SPI_TRANSCEIVE(0xFF);
			DEVICE_SPI_TRANSCEIVE(0xFF);
			DEVICE_SPI_TRANSCEIVE(0xFF);
			DEVICE_SPI_TRANSCEIVE(0xFF); // Read out following 4 bytes
		}
		else{ // command error : V1.xx
			sdc_v2 = false;
			sdc_hc = false;
		}
	}
	else{
		res.cmd8_timeout = 1;
		DEVICE_CS_SET();
		return res;
	}

#if SDC_DEBUG_PRINT
	printf("CMD8 sent\r\n");
#endif

	// ACMD41
	for(i = 0; i < 100; i++){
		timeout_tmp = !send_command(55, 0, &resp);
		timeout_tmp |= !send_command(41, 0x40000000, &resp);
		if( (!timeout_tmp) && (resp == 0x00) ) break;
	}
	if(i >= 100){
		res.acmd41_timeout = 1;
		DEVICE_CS_SET();
		return res;
	}

#if SDC_DEBUG_PRINT
	printf("ACMD41 sent\r\n");
#endif

	// CMD58
	if( !send_command(58, 0, &resp) ){
		res.cmd58_timeout = 1;
		DEVICE_CS_SET();
		return res;
	}

#if SDC_DEBUG_PRINT
	printf("CMD58 sent\r\n");
#endif

	// read first byte of R3 response
	if( (DEVICE_SPI_TRANSCEIVE(0xFF) & 0x40) && sdc_v2 ) // CCS bit is 1
		sdc_hc = true;
	else
		sdc_hc = false;
	DEVICE_SPI_TRANSCEIVE(0xFF);
	DEVICE_SPI_TRANSCEIVE(0xFF);
	DEVICE_SPI_TRANSCEIVE(0xFF); // read out rest of R3 response (3 bytes)

	// CMD16
	if(!sdc_hc)
		send_command(16, 512, &resp);

#if SDC_DEBUG_PRINT
	printf("CMD16 sent\r\n");
#endif

	DEVICE_CS_SET();
	DEVICE_BAUD_SET_HIGH();

	return res;
}


SDC_RW_RESULT sdc_SingleBlockRead(uint8_t *buff, unsigned long sec_addr)
{
	unsigned char resp;
	SDC_RW_RESULT ret;
	int i;

	ret.result = 0;

	DEVICE_CS_CLEAR();

	// CMD17
	if( !send_command(17, sec_addr, &(ret.cmd_resp)) ){
		ret.prv |= 0x01;
		DEVICE_CS_SET();
		return ret;
	}

	// wait for start block token or error token
	if( !wait_response(&resp) ){
		ret.prv|= 0x02;
		DEVICE_CS_SET();
		return ret;
	}

	if(resp != START_BLOCK_TOKEN){
		ret.err_token = resp;
		DEVICE_CS_SET();
		return ret;
	}

////	spi_tx_and_rx(SPI_NO_PTR, buff, 512); // Read Data
////	spi_tx_and_rx(SPI_NO_PTR, rx_buf_i, 2); // Read CRC (not used)
//	spi_tx_and_rx(dummy_buf, buff, 512); // Read Data
//	spi_tx_and_rx(dummy_buf, rx_buf_i, 2); // Read CRC (not used)

	for(i = 0; i < 512; i++) // Read Data
		buff[i] = DEVICE_SPI_TRANSCEIVE(0xFF);

	DEVICE_SPI_TRANSCEIVE(0xFF); DEVICE_SPI_TRANSCEIVE(0xFF); // Read CRC (not used)

	DEVICE_CS_SET();

	return ret;
}

SDC_RW_RESULT sdc_MultiBlockRead(uint8_t *buff, unsigned long sec_addr, unsigned int count)
{
	unsigned char resp;
	int i, j;
	SDC_RW_RESULT ret;

	ret.result = 0;

	if(count == 0)
		return ret;

	DEVICE_CS_CLEAR();

	// CMD18
	if( !send_command(18, sec_addr, &(ret.cmd_resp)) ){
		ret.prv |= 0x01;
		DEVICE_CS_SET();
		return ret;
	}

	for(i = 0; i < count; i++){

		// wait for start block token or error token
		if( !wait_response(&resp) ){
			ret.prv|= 0x02;
			break;
		}
		if(resp != START_BLOCK_TOKEN){
			ret.err_token = resp;
			break;
		}

////		spi_tx_and_rx(SPI_NO_PTR, buff, 512); // Read Data
//	//	spi_tx_and_rx(SPI_NO_PTR, rx_buf_i, 2); // Read CRC (not used)
//
//		spi_tx_and_rx(dummy_buf, buff, 512); // Read Data
//		spi_tx_and_rx(dummy_buf, rx_buf_i, 2); // Read CRC (not used)
//
		for(j = 0; j < 512; j++) // Read Data
			buff[j] = DEVICE_SPI_TRANSCEIVE(0xFF);

		DEVICE_SPI_TRANSCEIVE(0xFF); DEVICE_SPI_TRANSCEIVE(0xFF); // Read CRC (not used)

		buff += 512;
	}

	// CMD12 (STOP TRANSMISSION)
	if( !send_command(12, 0, &(ret.cmd12_resp)) )
		ret.prv |= 0x10;
	if( !wait_busy() )
		ret.prv |= 0x10;

	DEVICE_CS_SET();
	return ret;
}

SDC_RW_RESULT sdc_SingleBlockWrite(const uint8_t *buff, unsigned long sec_addr)
{
	SDC_RW_RESULT ret;
	uint8_t resp;
	int i;

	ret.result = 0;

	DEVICE_CS_CLEAR();

	// CMD24
	if( !send_command(24, sec_addr, &(ret.cmd_resp)) ){
		ret.prv |= 0x01;
		return ret;
	}

	if( ret.cmd_resp == 0x00 ){
		// send data packet
		DEVICE_SPI_TRANSCEIVE(START_BLOCK_TOKEN);
		for(i = 0; i < 512; i ++)
			DEVICE_SPI_TRANSCEIVE(buff[i]);
		DEVICE_SPI_TRANSCEIVE(0xFF);
		DEVICE_SPI_TRANSCEIVE(0xFF); // dummy CRC bytes

		// receive data response
		resp = DEVICE_SPI_TRANSCEIVE(0xFF);

		resp &= DAT_RESP_AMASK;
		switch(resp){
		case DAT_RESP_ACCEPTED :
			ret.dat_resp = 0x00; break;
		case DAT_RESP_CRC_ERR :
			ret.dat_resp = 0x01; break;
		case DAT_RESP_WRITE_ERR :
			ret.dat_resp = 0x02; break;
		default :
			ret.dat_resp = 0x03; break;
		}
	}

	// check busy state
	if( !wait_busy() ){
		ret.prv |= 0x04; // busy check time out
		return ret;
	}

	// optionally check the result using CMD13(SEND_STATUS) command


	DEVICE_CS_SET();

	return ret;

}

SDC_RW_RESULT sdc_MultiBlockWrite(const uint8_t *buff, unsigned long sec_addr, unsigned int count)
{
	uint8_t resp;
	int i;
	SDC_RW_RESULT ret;


	ret.result = 0;

	DEVICE_CS_CLEAR();


	// CMD25
	if( !send_command(25, sec_addr, &(ret.cmd_resp)) ){
		ret.prv |= 0x01;
		DEVICE_CS_SET();
		return ret;
	}
	else if(ret.cmd_resp != 0x00){
		DEVICE_CS_SET();
		return ret;
	}

	for(i = 0; i < count; i++){
		// send data packet
		DEVICE_SPI_TRANSCEIVE(START_BLOCK_TOKEN_MWRT);
		for(i = 0; i < 512; i ++)
			DEVICE_SPI_TRANSCEIVE(buff[i]);
		DEVICE_SPI_TRANSCEIVE(0xFF);
		DEVICE_SPI_TRANSCEIVE(0xFF); // dummy CRC bytes

		// receive data response
		resp = DEVICE_SPI_TRANSCEIVE(0xFF);

		switch(resp & DAT_RESP_AMASK){
		case DAT_RESP_ACCEPTED :
			ret.dat_resp = 0x00; break;
		case DAT_RESP_CRC_ERR :
			ret.dat_resp = 0x01; break;
		case DAT_RESP_WRITE_ERR :
			ret.dat_resp = 0x02; break;
		default :
			ret.dat_resp = 0x03; break;
		}

		if(ret.dat_resp != 0) break;

		// check busy state
		if( !wait_busy() ){
			ret.prv |= 0x04; // busy check time out
			return ret;
		}

		buff += 512;
	}

	// send Stop Tran Token
	DEVICE_SPI_TRANSCEIVE(STOP_TRAN_TOKEN);
	DEVICE_SPI_TRANSCEIVE(0xFF); // skip one byte

	if( !wait_busy() ){
		ret.prv |= 0x04;
		return ret;
	}

	// optionally check the result using CMD13(SEND_STATUS) command


	DEVICE_CS_SET();



	return ret;

}

uint8_t sdc_SendStatus(uint8_t *status)
{
	DEVICE_CS_CLEAR();

	*status = 0;
	if(!send_command(13, 0, status)) // receive first byte of R2 response
		return 0xff;

	*(status + 1) = DEVICE_SPI_TRANSCEIVE(0xFF); // second byte of R2 response

	DEVICE_CS_SET();

	return *status;
}

uint8_t sdc_AcmdSendStatus(uint8_t *status)
{
	uint8_t resp;
	int i;

	DEVICE_CS_CLEAR();

	if(!send_command(55, 0, &resp))
		return 0xff;
	if(resp != 0)
		return resp;

	if(!send_command(13, 0, &resp))
		return 0xff;
	if(resp != 0)
		return resp;

	DEVICE_SPI_TRANSCEIVE(0xFF); // ACMD13 response is R2 type, so skip one byte

	// wait for start block token or error token
	if( !wait_response(&resp) )
		return 0xff;
	if(resp != START_BLOCK_TOKEN)
		return 0xff;

	// Read 64 bytes data
	for(i = 0; i < 64; i++)
		status[i] = DEVICE_SPI_TRANSCEIVE(0xFF);

	DEVICE_SPI_TRANSCEIVE(0xFF); DEVICE_SPI_TRANSCEIVE(0xFF); // Read CRC (not used)

	DEVICE_CS_SET();

	return 0;

}

uint8_t sdc_SendCID(uint8_t *cid) // CID data : 16bytes
{
	uint8_t resp;
	int i;

	DEVICE_CS_CLEAR();

	if(!send_command(10, 0, &resp))
		return 0xff;
	if(resp != 0)
		return resp;

	// wait for start block token or error token
	if( !wait_response(&resp) )
		return 0xff;
	if(resp != START_BLOCK_TOKEN)
		return 0xff;

	// Read 16 bytes data
	for(i = 0; i < 64; i++)
		cid[i] = DEVICE_SPI_TRANSCEIVE(0xFF);

	DEVICE_SPI_TRANSCEIVE(0xFF); DEVICE_SPI_TRANSCEIVE(0xFF); // Read CRC (not used)

	DEVICE_CS_SET();

	return 0;

}

uint8_t sdc_SendCSD(uint8_t *csd) // CSD data : 16bytes
{
	uint8_t resp;
	int i;

	DEVICE_CS_CLEAR();

	if(!send_command(9, 0, &resp))
		return 0xff;
	if(resp != 0)
		return resp;

	// wait for start block token or error token
	if( !wait_response(&resp) )
		return 0xff;
	if(resp != START_BLOCK_TOKEN)
		return 0xff;

	// Read 16 bytes data
	for(i = 0; i < 16; i++)
		csd[i] = DEVICE_SPI_TRANSCEIVE(0xFF);

	DEVICE_SPI_TRANSCEIVE(0xFF); DEVICE_SPI_TRANSCEIVE(0xFF); // Read CRC (not used)

	DEVICE_CS_SET();

	return 0;
}


// buf : array of uint8_t
// lgh : length of buf (unit : byte)
// bStart : start bit number (counted from last bit)
// bEnd : end bit number (counted from last bit, bStart >= bEnd)
static unsigned long BitWindow(uint8_t *buf, int lgh, int StartBit, int EndBit);


// return : 0xffffffff -> SD card is not ready
//          else       -> erase block size
unsigned long sdc_EraseBlockSize()
{
	uint8_t buf[64];
	unsigned long ret;
	uint8_t au_size;

	if(sdc_hc){ // SDHC
		if( sdc_AcmdSendStatus(buf) == 0 ){

			// SD_STATUS[431:428] : AU_SIZE (the size of allocation units)
			// (number of sectors)
			// actual size is : 16 * 2^(AU_SIZE - 1) [KB]

			au_size = BitWindow(buf, 64, 431, 428);
			ret = ( (unsigned long)128 ) << au_size; // assume sector size to be 512 bits
		}
		else
			ret = 0xffffffff;
	}
	else{ // SDSC
		if( sdc_SendStatus(buf) == 0 ){

			// CSD[45:39] : SECTOR_SIZE
			// (number of sectors)
			// actual size is : SECTOR_SIZE + 1 [sectors]

			ret = BitWindow(buf, 16, 45, 39);
		}
		else
			ret = 0xffffffff;
	}

	return ret;
}

// number of sectors in card
unsigned long sdc_SectorCount()
{
	uint8_t buf[16];
	unsigned long ret;
	unsigned long pw;

	if(sdc_SendCSD(buf) == 0){
		if(sdc_v2){
			// SD V2.0
			// card capacity is : (C_SIZE + 1) * 512 [KB]

			ret = BitWindow(buf, 16, 69, 48) << 10;
		}
		else{
			// SD V1.xx
			// CSD[73:62] : C_SIZE
			// CSD[49:47] : C_SIZE_MULT
			// CSD[83:80] : READ_BL_LEN

			pw = BitWindow(buf, 16, 49, 47) + BitWindow(buf, 16, 83, 80) + 2;
			ret = BitWindow(buf, 16, 73, 62) << pw;
		}
	}
	else
		ret = 0xfffffff;


	return ret;
}

// buf : array of uint8_t
// lgh : length of buf (unit : byte)
// bStart : start bit number (counted from last bit)
// bEnd : end bit number (counted from last bit, bStart >= bEnd)
static unsigned long BitWindow(uint8_t *buf, int lgh, int StartBit, int EndBit)
{
	unsigned long ret;
	int tmp1, StartByte, EndByte, tmp_byte;
	uint8_t tmp2;

	StartByte = ((lgh << 3) - StartBit - 1) >> 3;
	EndByte = ((lgh << 3) - EndBit - 1) >> 3;

	tmp1 = (((uint8_t)StartBit) & 0x07) + 1; // first bit position in one byte (1 ~ 8)
	tmp2 = buf[StartByte] & (~((uint8_t)0xff << tmp1));
	ret = tmp2;

	tmp_byte = StartByte + 1;
	while(tmp_byte <= EndByte){
		ret <<= 8;
		ret += buf[tmp_byte];
		tmp_byte++;
	}

	tmp1 = (((uint8_t)EndBit) & 0x07); // end bit position in one byte (0 ~ 7)
	ret >>= tmp1;

	return ret;

}

// wait until response(first byte only) is received
// returns the first response into "resp1"
// if response type is other than R1, subsequent receiving returns the rest of response
// time out : after 1000 times received
static bool send_command(uint8_t cmd_id, unsigned long arg, uint8_t *resp1)
{
	uint8_t crc;

#if SDC_DEBUG_PRINT
	printf("CMD%d\r\n", cmd_id);
#endif

	DEVICE_SPI_TRANSCEIVE( 0x40 + cmd_id );
	DEVICE_SPI_TRANSCEIVE( (uint8_t)(arg >> 24) );
	DEVICE_SPI_TRANSCEIVE( (uint8_t)(arg >> 16) );
	DEVICE_SPI_TRANSCEIVE( (uint8_t)(arg >> 8) );
	DEVICE_SPI_TRANSCEIVE( (uint8_t)arg );

	switch(cmd_id){
	case 0 :
		crc = 0x95;
		break;
	case 8 :
		crc = 0x87; // assume argument bytes are 0x00, 0x00, 0x01, 0xAA
		break;
	default :
		crc = 0xff; // bit0 must be 1
	}
	DEVICE_SPI_TRANSCEIVE(crc);

	if(cmd_id == 12)
		DEVICE_SPI_TRANSCEIVE(0xFF); // CMD12 : skip one byte

	return wait_response(resp1);
}




static bool wait_response(uint8_t *resp1)
{
	int i;

	for(i = 0; i < 1000; i++){
		*resp1 = DEVICE_SPI_TRANSCEIVE(0xFF);
		if(*resp1 != 0xff) break;

//		timer_soft_wait(1);
	}

#if SDC_DEBUG_PRINT
	printf("wait count : %d\r\n", i);
#endif

	return (i != 1000);
}

static bool wait_busy()
{
	int i;

	for(i = 0; i < 1000; i++){

		if(DEVICE_SPI_TRANSCEIVE(0xFF) != 0x00)
			break;

//		timer_soft_wait(1);
	}
#if SDC_DEBUG_PRINT
	printf("busy count : %d\r\n", i);
#endif
	return (i != 1000);
}



//
//static const uint8_t Cmd0WithCRC[6] =
//	{0x40 + 0 /* 0x40 */, 0x00, 0x00, 0x00, 0x00, 0x95}; // GO_IDLE_STATE : Resets the SD Memory Card
//static const uint8_t Cmd8WithCRC[6] =
//	{0x40 + 8 /* 0x48 */, 0x00, 0x00, 0x01, 0xAA, 0x87}; // SEND_IF_COND : Sends SD Memory Card interface condition
//static const uint8_t Cmd55WithCRC[6] =
//	{0x40 + 55 /* 0x77 */, 0x00, 0x00, 0x00, 0x00, 0x65}; // APP_CMD : Defines to the card that the next command is an application specific command
//static const uint8_t Acmd41WithCRC[6] =
//	{0x40 + 41 /* 0x69 */, 0x40, 0x00, 0x00, 0x00, 0x77}; // SD_SEND_OP_COND : Sends host capacity support information and activates the card's initialization process.
//static const uint8_t Cmd58WithCRC[6] =
//	{0x40 + 58 /* 0x7A */, 0x00, 0x00, 0x00, 0x00, 0xFD }; // READ_OCR : Reads the OCR register of a card. CCS bit is assigned to OCR[30].
//static const uint8_t Cmd16_512bytes[6] =
//	{0x40 + 16 /* 0x50 */, 0x00, 0x01, 0x00, 0x00, 0x67 }; // SET_BLOCKLEN
////static const uint8_t Cmd59WithCRC_OFF[6] =
////	{0x40 + 59 /* 0x7B */, 0x00, 0x01, 0x00, 0x00, 0x91 }; // CRC_ON_OFF
////static const uint8_t Cmd59WithCRC_ON[6] =
////	{0x40 + 59 /* 0x7B */, 0x00, 0x01, 0x00, 0x01, 0x83 }; // CRC_ON_OFF
//static const uint8_t Cmd12[6] =
//	{0x40 + 12 /* 0x4C */, 0x00, 0x00, 0x00, 0x00, 0xFF }; // STOP_TRANSMISSION
//

