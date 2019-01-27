/*
 * work_area.h
 *
 *  Created on: 2019/01/12
 *      Author: akicl
 */

#ifndef WORK_AREA_H_
#define WORK_AREA_H_

#include "ff11/src/ff.h"

#define WK_N_FNAME 100

typedef struct{
	FATFS 			fatfs;
	DIR 			dj;
	FIL				fl;
    FILINFO 		fno;
	char 			fname[WK_N_FNAME];

} WORK_AREA;

extern WORK_AREA wk;


#endif /* WORK_AREA_H_ */
