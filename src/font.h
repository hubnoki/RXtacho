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

#define W_FONT 5

typedef struct{
	unsigned char f[W_FONT];
}FONT_DATA;

extern const FONT_DATA font[];

#define W_FONT_X4 20

typedef struct{
	unsigned int f[W_FONT_X4];
}FONT_DATA_X4;

extern const FONT_DATA_X4 font_x4[];


#endif /* FONT_H_ */
