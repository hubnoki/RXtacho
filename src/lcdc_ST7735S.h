/*
 * lcdc_ST7735S.h
 *
 *  Created on: 2016/02/15
 *      Author: akihiro
 *
 *  2016/11/07 kinoshita
 *  	basic functions are verified
 *
 */

#ifndef LCDC_ST7735S_H_
#define LCDC_ST7735S_H_

#include "hardware_lib.h"
#include "typedefine.h"


//////// Defines ////////

//---- for application to access ST7735S registers ----//
#define ST7735S_REG_ACCESS

//---- ST7735S register addresses ----//
#define ST7735S_NOP                 0x00
#define ST7735S_SWRESET             0x01
#define ST7735S_RDDID               0x04
#define ST7735S_RDDST               0x09
#define ST7735S_RDDPM               0x0A
#define ST7735S_RDD_MADCTL          0x0B
#define ST7735S_RDD_COLMOD          0x0C
#define ST7735S_RDDIM               0x0D
#define ST7735S_RDDSM               0x0E
#define ST7735S_RDDSDR              0x0F

#define ST7735S_SLPIN               0x10
#define ST7735S_SLPOUT              0x11
#define ST7735S_PTLON               0x12
#define ST7735S_NORON               0x13

#define ST7735S_INVOFF              0x20
#define ST7735S_INVON               0x21
#define ST7735S_GAMSET              0x26
#define ST7735S_DISPOFF             0x28
#define ST7735S_DISPON              0x29
#define ST7735S_CASET               0x2A
#define ST7735S_RASET               0x2B
#define ST7735S_RAMWR               0x2C
#define ST7735S_RGBSET              0x2D
#define ST7735S_RAMRD               0x2E

#define ST7735S_PTLAR               0x30
#define ST7735S_SCRLAR             0x33
#define ST7735S_TEOFF               0x34
#define ST7735S_TEON                0x35
#define ST7735S_MADCTL              0x36
#define ST7735S_VSCSAD             0x37
#define ST7735S_IDMOFF              0x38
#define ST7735S_IDMON               0x39
#define ST7735S_COLMOD              0x3A

#define ST7735S_RDID1               0xDA
#define ST7735S_RDID2               0xDB
#define ST7735S_RDID3               0xDC

#define ST7735S_FRMCTR1             0xB1
#define ST7735S_FRMCTR2             0xB2
#define ST7735S_FRMCTR3             0xB3
#define ST7735S_INVCTR              0xB4

#define ST7735S_PWCTR1              0xC0
#define ST7735S_PWCTR2              0xC1
#define ST7735S_PWCTR3              0xC2
#define ST7735S_PWCTR4              0xC3
#define ST7735S_PWCTR5              0xC4
#define ST7735S_VMCTR1              0xC5
#define ST7735S_VMOFCTR             0xC7

#define ST7735S_WRID2               0xD1
#define ST7735S_WRID3               0xD2

#define ST7735S_NVFCTR1             0xD9
#define ST7735S_NVFCTR2             0xDE
#define ST7735S_NVFCTR3             0xDF

#define ST7735S_GMCTRP1             0xE0
#define ST7735S_GMCTRN1             0xE1
#define ST7735S_GCV                 0xFC

//---- LCD display resolution ----//
#define LCDC_ROW 160
#define LCDC_COL 128

//---- LCD display orientation ----//
#define LCDC_VRT_ROW 0 // vertical row, horizontal column
#define LCDC_HRZ_ROW 1 // horizontal row, vertical column
// LCDC_VRT_ROW or LCDC_HRZ_ROW
#define LCDC_ORT_SEL LCDC_HRZ_ROW

//---- LCD display color definition ----//
#define LCDC_BLACK 0x0
#define LCDC_WHITE 0xFFFF
#define LCDC_RED 0xF800
#define LCDC_GREEN 0x07E0
#define LCDC_BLUE 0x001F


//////// Functions ////////

void lcdc_init(void);
void lcdc_on(void);
void lcdc_off(void);

// Area to update display data
//   x_start, x_end : horizontal range
//   y_start, y_end : vertical range
void lcdc_set_area(_UWORD x_start, _UWORD x_end, _UWORD y_start, _UWORD y_end);

void lcdc_row_col_exchange();
void lcdc_row_invert();
void lcdc_col_invert();

// lcdc_set_area must be called before this function
void lcdc_fill(_UWORD color);

void lcdc_fill_area(_UWORD color, _UWORD x_start, _UWORD x_end, _UWORD y_start, _UWORD y_end);

void lcdc_draw_pixel(_UWORD color, _UWORD x0, _UWORD y0);

// _SWORD curve(_UWORD) : curve function
// sweep x direction
void lcdc_draw_curve(_SWORD (*curve)(_UWORD), _SWORD offset, _UWORD color, _UWORD x_start, _UWORD x_end, _UWORD y_start, _UWORD y_end);

void lcdc_putchar(char c, _UWORD color, _UWORD x0, _UWORD y0);
void lcdc_puts(char *s, _UWORD color, _UWORD x0, _UWORD y0);


#ifdef ST7735S_REG_ACCESS

typedef enum{
	REG_N,
	REG_R,
	REG_W
} ST7735S_REG_TYPE;

typedef struct {
	ST7735S_REG_TYPE r_w;
	int n_byte;
} ST7735S_REG;


bool ST7735S_open(_UBYTE adr, ST7735S_REG_TYPE r_w);

// return : number of actually read data (byte)
// n : maximum length of data[]
int ST7735S_read(_UBYTE *data, int n);

// return : number of actually written data (byte)
// n : maximum length of data[]
int ST7735S_write(_UBYTE *data, int n);

bool ST7735S_close();


#endif // ST7735S_REG_ACCESS

#endif /* LCDC_ST7735S_H_ */
