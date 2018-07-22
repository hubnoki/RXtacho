/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */

#include <stdio.h>
#include "../../sdc.h"

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */

#define SD1 0
#define SD2 1


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	uint8_t resp, status[2];

	switch (pdrv) {

	case SD1 :
		resp = sdc_SendStatus(status);
		if(resp == 0xff)
			stat = STA_NODISK;
		else if(resp != 0)
			stat = STA_NOINIT;
		else
			stat = 0;

		return stat;

	default :
		return STA_NODISK;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	SDC_INIT_RESULT res;

	switch (pdrv) {

	case SD1 :
		res = sdc_init();

		if(res.result == 0)
			stat = 0;
		else
			stat = STA_NODISK;

		return stat;

	default :
		return STA_NODISK;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	SDC_RW_RESULT sdc_res;

	switch (pdrv) {

	case SD1 :
		// translate the arguments here

		if(count == 1)
			sdc_res = sdc_SingleBlockRead(buff, sector);
		else
			sdc_res = sdc_MultiBlockRead(buff, sector, count);

		if(sdc_res.result != 0)
			res = RES_ERROR;
		else
			res = RES_OK;

		return res;

	default :
		return RES_NOTRDY;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
//	int result;
	SDC_RW_RESULT sdc_res;

	switch (pdrv) {
	case SD1 :

		if(count == 1)
			sdc_res = sdc_SingleBlockWrite(buff, sector);
		else
			sdc_res = sdc_MultiBlockWrite(buff, sector, count);

		if(sdc_res.result != 0)
			res = RES_ERROR;
		else
			res = RES_OK;

		return res;

	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	unsigned long result;

	switch (pdrv) {
	case SD1 :

		// Process of the command for the MMC/SD card

		switch(cmd){
		case CTRL_SYNC :
			res = RES_OK;
			break;
		case GET_SECTOR_COUNT :
			result = sdc_SectorCount();
			if( result != 0xffffffff){
				*(unsigned long *)buff = result;
				res = RES_OK;
			}
			else
				res = RES_ERROR;
			break;
		case GET_BLOCK_SIZE :
			printf("disk_ioctl(GET_BLOCK_SIZE)\r\n");
			result = sdc_EraseBlockSize();
			if( result != 0xffffffff){
				*(unsigned long *)buff = result;
				res = RES_OK;
			}
			else
				res = RES_ERROR;
			break;
		case CTRL_TRIM :
			res = RES_OK;
			break;
		default :
			res = RES_PARERR;
		}

		return res;

	}

	return RES_PARERR;
}
#endif
