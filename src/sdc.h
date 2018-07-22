/*
 * sdc.h
 *
 *  Created on: 2015/08/09
 *      Author: akihiro
 *
 *  2016/02/21 kinoshita
 *  	modified for RXtacho project
 *
 */

#ifndef SDC_H_
#define SDC_H_

#include <stdint.h>


typedef union{
	uint8_t result;
	struct{
		uint8_t cmd0_timeout :1;
		uint8_t cmd8_timeout :1;
		uint8_t acmd41_timeout :1;
		uint8_t cmd58_timeout :1;
	};
}SDC_INIT_RESULT;

typedef union{
	struct{
		uint8_t cmd_resp;
		union{
			uint8_t err_token; // in case of read operation
			uint8_t dat_resp; 	// in case of write operation,
								// 0x00 -> data accepted
								// 0x01 -> CRC error
								// 0x02 -> write error
								// 0x03 -> other response
		};
		uint8_t cmd12_resp; // CMD12 response in case of multiple block operation
		uint8_t prv;
			// prv : bit0 -> command response timeout
		    //       bit1 -> START BLOCK TOKEN timeout (read operation)
			//       bit2 -> busy check time out
			//       bit3 -> write error (write operation, data response indicates error)
			//       bit4 -> CMD12 time out (command response or busy state)
	};
	uint32_t result;
}SDC_RW_RESULT;

//// initialize this driver
//void sdc_drvinit(void);

SDC_INIT_RESULT sdc_init(void);

SDC_RW_RESULT sdc_SingleBlockRead(uint8_t *buff, unsigned long sec_addr);
SDC_RW_RESULT sdc_MultiBlockRead(uint8_t *buff, unsigned long sec_addr, unsigned int count);
SDC_RW_RESULT sdc_SingleBlockWrite(const uint8_t *buff, unsigned long sec_addr);
SDC_RW_RESULT sdc_MultiBlockWrite(const uint8_t *buff, unsigned long sec_addr, unsigned int count);

// return : 0xff -> error
//          else -> command response
uint8_t sdc_SendStatus(uint8_t *status); // status data : 2bytes
uint8_t sdc_AcmdSendStatus(uint8_t *status); // status data : 64 bytes
uint8_t sdc_SendCID(uint8_t *cid); // CID data : 16bytes
uint8_t sdc_SendCSD(uint8_t *csd); // CSD data : 16bytes

unsigned long sdc_EraseBlockSize();
unsigned long sdc_SectorCount();

#endif /* SDC_H_ */
