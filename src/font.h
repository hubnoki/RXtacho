/*
 * font.h
 *
 *  Created on: 2016/10/05
 *      Author: akihiro
 *
 *      This file is the header file for font.c
 *
 *  2016/11/03 kinoshita
 *  	added type "FONT_DATA"
 *      type of "font" is changed to array of "FONT_DATA"
 */

#ifndef FONT_H_
#define FONT_H_

typedef struct{
	unsigned char f[5];
}FONT_DATA;

extern const FONT_DATA font[];

////extern const unsigned char font[][5];
//extern unsigned char font[][5];


#endif /* FONT_H_ */
