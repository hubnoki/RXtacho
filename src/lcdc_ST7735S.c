/*
 * lcdc_ST7735S.c
 *
 *  Created on: 2016/02/15
 *      Author: akihiro
 *
 *  reference : http://www.aitendo3.sakura.ne.jp/aitendo_data/product_img/lcd/tft2015/M018/M018C7735S_demo.txt
 *
 *  2016/11/07 kinoshita
 *  	basic functions are verified
 *
 */

#include "hardware_lib.h"
#include "lcdc_ST7735S.h"
#include "timer_soft.h"

#include "stdio.h"

#include "font.h"


#ifdef ST7735S_REG_ACCESS

static const ST7735S_REG ST7735S_regs_00to3A[] =
{
    {REG_W, 0}, // 00h ST7735S_NOP
    {REG_W, 0}, // 01h ST7735S_SWRESET
    {REG_N, 0},
    {REG_N, 0},
    {REG_R, 3}, // 04h ST7735S_RDDID
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_R, 4}, // 09h ST7735S_RDDST
    {REG_R, 1}, // 0Ah ST7735S_RDDPM
    {REG_R, 1}, // 0Bh ST7735S_RDD_MADCTL
    {REG_R, 1}, // 0Ch ST7735S_RDD_COLMOD
    {REG_R, 1}, // 0Dh ST7735S_RDDIM
    {REG_R, 1}, // 0Eh ST7735S_RDDSM
    {REG_R, 1}, // 0Fh ST7735S_RDDSDR

    {REG_W, 0}, // 10h ST7735S_SLPIN
    {REG_W, 0}, // 11h ST7735S_SLPOUT
    {REG_W, 0}, // 12h ST7735S_PTLON
    {REG_W, 0}, // 13h ST7735S_NORON
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_W, 0}, // 20h ST7735S_INVOFF
    {REG_W, 0}, // 21h ST7735S_INVON
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 1}, // 26h ST7735S_GAMSET
    {REG_N, 0},
    {REG_W, 0}, // 28h ST7735S_DISPOFF
    {REG_W, 0}, // 29h ST7735S_DISPON
    {REG_W, 4}, // 2Ah ST7735S_CASET
    {REG_W, 4}, // 2Bh ST7735S_RASET
    {REG_W, LCDC_ROW*LCDC_COL}, // 2Ch ST7735S_RAMWR
    {REG_W, 128}, // 2Dh ST7735S_RGBSET
    {REG_R, LCDC_ROW*LCDC_COL}, // 2Eh ST7735S_RAMRD
    {REG_N, 0},

    {REG_W, 4}, // 30h ST7735S_PTLAR
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 6}, // 33h ST7735S_SCRLAR
    {REG_W, 0}, // 34h ST7735S_TEOFF
    {REG_W, 0}, // 35h ST7735S_TEON
    {REG_W, 1}, // 36h ST7735S_MADCTL
    {REG_W, 2}, // 37h ST7735S_VSCSAD
    {REG_W, 0}, // 38h ST7735S_IDMOFF
    {REG_W, 0}, // 39h ST7735S_IDMON
    {REG_W, 1} // 3Ah ST7735S_COLMOD
};

static const ST7735S_REG ST7735S_regs_B0toFF[] =
{
    {REG_N, 0},
    {REG_W, 3}, // B1h ST7735S_FRMCTR1
    {REG_W, 3}, // B2h ST7735S_FRMCTR2
    {REG_W, 6}, // B3h ST7735S_FRMCTR3
    {REG_W, 1}, // B4h ST7735S_INVCTR
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_W, 3}, // C0h ST7735S_PWCTR1
    {REG_W, 1}, // C1h ST7735S_PWCTR2
    {REG_W, 2}, // C2h ST7735S_PWCTR3
    {REG_W, 2}, // C3h ST7735S_PWCTR4
    {REG_W, 2}, // C4h ST7735S_PWCTR5
    {REG_W, 1}, // C5h ST7735S_VMCTR1
    {REG_N, 0},
    {REG_W, 1}, // C7h ST7735S_VMOFCTR
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_N, 0},
    {REG_W, 1}, // D1h ST7735S_WRID2
    {REG_W, 1}, // D2h ST7735S_WRID3
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 1}, // D9h ST7735S_NVFCTR1
    {REG_R, 1}, // DAh ST7735S_RDID1
    {REG_R, 1}, // DBh ST7735S_RDID2
    {REG_R, 1}, // DCh ST7735S_RDID3
    {REG_N, 0},
    {REG_W, 2}, // DEh ST7735S_NVFCTR2
    {REG_W, 2}, // DFh ST7735S_NVFCTR3

    {REG_W, 16}, // E0h ST7735S_GMCTRP1
    {REG_W, 16}, // E1h ST7735S_GMCTRN1
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},

    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0},
    {REG_W, 1},  // FCh ST7735S_GCV
    {REG_N, 0},
    {REG_N, 0},
    {REG_N, 0}
};


#endif // ST7735S_REG_ACCESS


#if LCDC_ORT_SEL == LCDC_VRT_ROW
#define LCDC_X_WIDTH LCDC_COL
#define LCDC_Y_WIDTH LCDC_ROW
#else
#define LCDC_X_WIDTH LCDC_ROW
#define LCDC_Y_WIDTH LCDC_COL
#endif


static struct{
	_UBYTE madctl;
	_UINT x_st, x_ed, y_st, y_ed;
	
}lcdc_state;

#define LCDC_MADCTL_MY_BIT 0x80
#define LCDC_MADCTL_MX_BIT 0x40
#define LCDC_MADCTL_MV_BIT 0x20
#define LCDC_MADCTL_RGB_BIT 0x08


//// Hardware dependent functions ////
#pragma inline(DEVICE_SPI_TX)
static void DEVICE_SPI_TX(_UBYTE d){SCI12_LCD_TXDATA = d; while(!SCI12_LCD_TX_END);}

// write data into SPI TX buffer
// Actual transmission may not be completed in this function.
// (This function can be implemented as above function; DEVICE_SPI_TX.)
#pragma inline(DEVICE_SPI_TX_BUFW)
static void DEVICE_SPI_TX_BUFW(_UBYTE d){while(!SCI12_LCD_TXI); SCI12_LCD_TXI = 0; SCI12_LCD_TXDATA = d;}

// flag that indicates transmission completion
// (This define can be "1".)
#define DEVICE_SPI_TX_END SCI12_LCD_TX_END

#pragma inline(DEVICE_CS_CLEAR)
static void DEVICE_CS_CLEAR(void){LCD_CS = 0;}
#pragma inline(DEVICE_CS_SET)
static void DEVICE_CS_SET(void){LCD_CS = 1;}

#pragma inline(DEVICE_RS_CLEAR)
static void DEVICE_RS_CLEAR(void){LCD_RS = 0;}	// Clear RS -> transmit command
#pragma inline(DEVICE_RS_SET)
static void DEVICE_RS_SET(void){LCD_RS = 1;}	// Set RS -> transmit data
#pragma inline(DEVICE_NRST_CLEAR)
static void DEVICE_NRST_CLEAR(void){LCD_NRST = 0;}
#pragma inline(DEVICE_NRST_SET)
static void DEVICE_NRST_SET(void){LCD_NRST = 1;}


static void wait_ms(int ms)
{
	timer_soft_wait(ms);
		// timer_soft : unit should be 1ms
}

//////////////////////////////////////



static void write_command(_UBYTE cmd)
{
	DEVICE_RS_CLEAR();
	DEVICE_CS_CLEAR();

	DEVICE_SPI_TX(cmd);

	DEVICE_CS_SET();
}

static void write_data(_UBYTE dat)
{
	DEVICE_RS_SET();
	DEVICE_CS_CLEAR();

	DEVICE_SPI_TX(dat);

	DEVICE_CS_SET();
}


void lcdc_init(void)
{
	int i;

	DEVICE_NRST_SET();
	wait_ms(1);

	DEVICE_NRST_CLEAR();
	wait_ms(1);

	DEVICE_NRST_SET();
	wait_ms(120);

	write_command(ST7735S_SLPOUT); // Exit Sleep
	wait_ms(120);



	write_command(ST7735S_GAMSET); // Set Default Gamma
	write_data(0x01);

//	write_command(0xB1); // Set Frame Rate
//	write_data(0x05);
//	write_data(0x3C);
//	write_data(0x3C);

	write_command(0xB4); //Display Inversion Control
    write_data(0x03); // Inversion setting in Idle mode and full Colors partial mode




    write_command(0xC0); // Power Control Setting (GVDD Voltage)
    write_data(0xA2); // AVDD=5, GVDD=4.6
    write_data(0x02); // VGCL=-4.6
    write_data(0x84); // MODE=AUTO

    write_command(0xC1); // Power Control Setting (VGH/VGL Voltage)
    write_data(0xC5); // VGH and VGL supply power level = 2.4, VGL=-10, VGH=3*AVDD-0.5

    write_command(0xC2); // In Normal Mode(Full Colors) APA/DCA
    write_data(0x0D); // SAP=Small, AP=Large
    write_data(0x00); // Clock frequency for Booster circuit/1,/3,/1,/1,/1

    write_command(0xC5); // VCOM
    write_data(0x05); // -0.55

    lcdc_state.madctl = LCDC_MADCTL_MY_BIT;
#if LCDC_ORT_SEL == LCDC_HRZ_ROW
	lcdc_state.madctl |= LCDC_MADCTL_MV_BIT;
#endif
    write_command(0x36); // Memory Data Access Control
    write_data(lcdc_state.madctl);


    write_command(0xE0); // Gamma Adjustment (+Polarity)
    write_data(0x03);
    write_data(0x1B);
    write_data(0x09);
    write_data(0x0E);
    write_data(0x32);
    write_data(0x2D);
    write_data(0x28);
    write_data(0x2C);
    write_data(0x2B);
    write_data(0x29);
    write_data(0x30);
    write_data(0x3B);
    write_data(0x00);
    write_data(0x01);
    write_data(0x02);
    write_data(0x10);

    write_command(0xE1); // Gamma Adjustment (-Polarity)
    write_data(0x03);
    write_data(0x1B);
    write_data(0x09);
    write_data(0x0E);
    write_data(0x32);
    write_data(0x2E);
    write_data(0x28);
    write_data(0x2C);
    write_data(0x2B);
    write_data(0x28);
    write_data(0x31);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x00);
    write_data(0x02);
    write_data(0x10);


    write_command(0x3A); // Interface Pixel Format
    write_data(0x05); // 16-bit/pixel


	write_command(0x2A); // Set Column Address
	write_data(0x00);
	write_data(0x00);
	write_data(0x00);
	write_data(0x7F);

	write_command(0x2B); // Set Page Address
	write_data(0x00);
	write_data(0x00);
	write_data(0x00);
	write_data(0x9F);

	wait_ms(100);

	write_command(0x29); // Display On

#if LCDC_ORT_SEL == LCDC_VRT_ROW
	lcdc_set_area(0, LCDC_COL-1, 0, LCDC_ROW-1);
#else
	lcdc_set_area(0, LCDC_ROW-1, 0, LCDC_COL-1);
#endif

}

void lcdc_on(void)
{
	write_command(0x29);
}

void lcdc_off(void)
{
	write_command(0x28);
}

// Area to update display data
//   x_start, x_end : horizontal range
//   y_start, y_end : vertical range
void lcdc_set_area(_UWORD x_start, _UWORD x_end, _UWORD y_start, _UWORD y_end)
{
	lcdc_state.x_st = x_start;
	lcdc_state.x_ed = x_end;
	lcdc_state.y_st = y_start;
	lcdc_state.y_ed = y_end;

	write_command(0x2A); // Set Column Address
	write_data( (_UBYTE)(x_start >> 8) );
	write_data( (_UBYTE)x_start );
	write_data( (_UBYTE)(x_end >> 8) );
	write_data( (_UBYTE)x_end  );

	write_command(0x2B); // Set Page Address
	write_data( (_UBYTE)(y_start >> 8) );
	write_data( (_UBYTE)y_start );
	write_data( (_UBYTE)(y_end >> 8) );
	write_data( (_UBYTE)y_end );

}

void lcdc_row_col_exchange()
{
	lcdc_state.madctl ^= LCDC_MADCTL_MV_BIT;

	write_command(0x36);
	write_data(lcdc_state.madctl);
}

void lcdc_row_invert()
{
	lcdc_state.madctl ^= LCDC_MADCTL_MY_BIT;

	write_command(0x36);
	write_data(lcdc_state.madctl);
}
void lcdc_col_invert()
{
	lcdc_state.madctl ^= LCDC_MADCTL_MX_BIT;

	write_command(0x36);
	write_data(lcdc_state.madctl);
}

// lcdc_set_area must be called before this function
void lcdc_fill(_UWORD color)
{
	int i, j;

	write_command(0x2C);

	DEVICE_RS_SET();
	DEVICE_CS_CLEAR();

	for(j = lcdc_state.y_st; j <= lcdc_state.y_ed; j++){			// y direction
		for(i = lcdc_state.x_st; i <= lcdc_state.x_ed; i++){	// x direction
			DEVICE_SPI_TX_BUFW( (_UBYTE)(color >> 8) );
			DEVICE_SPI_TX_BUFW( (_UBYTE)color );
		}
	}

	while(!DEVICE_SPI_TX_END)
		;
	DEVICE_CS_SET();
}

void lcdc_fill_area(_UWORD color, _UWORD x_start, _UWORD x_end, _UWORD y_start, _UWORD y_end)
{
	int i, j;

	lcdc_set_area(x_start, x_end, y_start, y_end);
	
	lcdc_fill(color);
}

void lcdc_draw_pixel(_UWORD color, _UWORD x0, _UWORD y0)
{
	lcdc_fill_area(color, x0, x0, y0, y0);
}

// _SWORD curve(_UWORD) : curve function
// sweep x direction
// dir : Y axis direction, 0 -> from y_start to y_end , 1 -> from y_end to y_start
void lcdc_draw_curve(_SWORD (*curve)(_UWORD), _SWORD offset, _SWORD dir, _UWORD color
				, _UWORD x_start, _UWORD x_end, _UWORD y_start, _UWORD y_end)
{
	_UWORD x_tmp, y_tmp;

	for(x_tmp = x_start; x_tmp <= x_end; x_tmp++){
		y_tmp = offset + ((dir == 0) ? curve(x_tmp) : -curve(x_tmp));
		if( (y_tmp >= y_start) && (y_tmp <= y_end) )
			lcdc_draw_pixel(color, x_tmp, y_tmp);
	}

}


// bit_ptn[j].bit(b) : (j)th y, (b)th x
// display area : rectangle of (x0, y0), (x0 + 7, y0 + dy - 1)
static void lcdc_draw_8x(const unsigned char *bit_ptn, _UWORD color, _UWORD x0, _UWORD y0, _UWORD dy)
{
	int i, j;
	unsigned char index, tmp;


	lcdc_set_area(x0, x0 + 7, y0, y0 + dy-1);

	write_command(0x2C);

	DEVICE_RS_SET();
	DEVICE_CS_CLEAR();

	for(j = 0; j < dy; j++){			// Row loop

		tmp = bit_ptn[j];

		for(i = 0; i < 8; i++){	// Column loop

			if( tmp & 0x01 ){
				DEVICE_SPI_TX_BUFW( (_UBYTE)(color >> 8) );
				DEVICE_SPI_TX_BUFW( (_UBYTE)color );
			}
			else{
				DEVICE_SPI_TX_BUFW(0x0);
				DEVICE_SPI_TX_BUFW(0x0);
			}

			tmp >>= 1;
		}
	}

	while(!DEVICE_SPI_TX_END)
		;
	DEVICE_CS_SET();

}


void lcdc_putchar(char c, _UWORD color, _UWORD x0, _UWORD y0)
{
	int i, j;
	unsigned char index, tmp;
	
	if( (c < 0x20) || (c > 0x7F) )
		index = 0x20;
	else
		index = c - 0x20;
		
	lcdc_row_col_exchange();

	lcdc_draw_8x(font[index].f, color, y0, x0, 5);

	lcdc_row_col_exchange();
}

#define VERTICAL_PITCH 1
#define HORIZONTAL_PITCH 1
void lcdc_puts(char *s, _UWORD color, _UWORD x0, _UWORD y0)
{
	_UWORD x_tmp, y_tmp;
	char *p;

	p = s;

	x_tmp = x0;
	y_tmp = y0;

	while(*p != '\0'){
		if(x_tmp > LCDC_X_WIDTH - 5){
			// If there is not enough space for x direction,
			// rewind x position, and increment y position.
			x_tmp = x0;
			y_tmp += 8 + VERTICAL_PITCH;
			if(y_tmp >= LCDC_Y_WIDTH)
				break;
		}
		else{
			lcdc_putchar(*p, color, x_tmp, y_tmp);
			p++;
			x_tmp += (5 + HORIZONTAL_PITCH);
		}
	}

}



#ifdef ST7735S_REG_ACCESS

static struct {
	_UBYTE adr;
	ST7735S_REG_TYPE r_w;
	int n_byte;
	bool read_first;
	bool open;
} ST7735S_REG_STATE;

bool ST7735S_open(_UBYTE adr, ST7735S_REG_TYPE r_w)
{
	int n_byte;

	ST7735S_REG_STATE.r_w = r_w;

	printf("adr:%x, r_w:%d\r\n",adr,r_w);

	if(adr <= 0x3A){
		if(ST7735S_regs_00to3A[adr].r_w == r_w){
			ST7735S_REG_STATE.n_byte = ST7735S_regs_00to3A[adr].n_byte;
		}
		else{
			ST7735S_REG_STATE.open = false;
			return false;
		}
	}
	else if(adr >= 0xB0){
		if(ST7735S_regs_B0toFF[adr-0xB0].r_w == r_w){
			ST7735S_REG_STATE.n_byte = ST7735S_regs_B0toFF[adr-0xB0].n_byte;
		}
		else{
			ST7735S_REG_STATE.open = false;
			return false;
		}
	}
	else{
		ST7735S_REG_STATE.open = false;
		return false;
	}

	printf("n_byte:%d\r\n", ST7735S_REG_STATE.n_byte);

	sci12_LCD_com_mode(SCI12_SPITX);

	DEVICE_RS_CLEAR();
	timer_soft_wait(1);
	DEVICE_CS_CLEAR();
	timer_soft_wait(1);

	DEVICE_SPI_TX(adr);

	if( (r_w == REG_R) && (ST7735S_REG_STATE.n_byte > 1) ){
		timer_soft_wait(1); // wait before dummy clock is needed
		sci12_LCD_com_mode(SCI12_GPIORX);
		sci12_LCD_dummy_clock();
		sci12_LCD_com_mode(SCI12_SPITX);
	}


	ST7735S_REG_STATE.open = true;

	return true;

}

// return : number of actually read data (byte)
// n : maximum length of data[]
int ST7735S_read(_UBYTE *data, int n)
{
	int i;

	if((!ST7735S_REG_STATE.open) || (ST7735S_REG_STATE.r_w != REG_R))
		return 0;

	sci12_LCD_com_mode(SCI12_GPIORX);

	i = 0;
	while(ST7735S_REG_STATE.n_byte){
		if(i >= n) break;

		data[i] = sci12_LCD_read();

		ST7735S_REG_STATE.n_byte--;
		i++;
	}

	sci12_LCD_com_mode(SCI12_SPITX);

	return i;

}


// return : number of actually written data (byte)
// n : maximum length of data[]
int ST7735S_write(_UBYTE *data, int n)
{
	int i;

	if((!ST7735S_REG_STATE.open) || (ST7735S_REG_STATE.r_w != REG_W))
		return 0;

	DEVICE_RS_SET();

	i = 0;
	while(ST7735S_REG_STATE.n_byte){
		if(i >= n) break;

		DEVICE_SPI_TX(data[i]);

		ST7735S_REG_STATE.n_byte--;
		i++;
	}

	return i;

}

bool ST7735S_close()
{
	if(ST7735S_REG_STATE.open){
		DEVICE_CS_SET();
		ST7735S_REG_STATE.open = false;
		return true;
	}
	else
		return false;
}


#endif // ST7735S_REG_ACCESS

