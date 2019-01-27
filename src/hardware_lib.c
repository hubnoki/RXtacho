/*
 * hardware_lib.c
 *
 *  Created on: 2016/01/20
 *      Author: akihiro
 */

#include "hardware_lib.h"
#include "uart.h"
#include <stdio.h>
#include "interrupt_handlers.h"


#define SCI_SCR_BIT_RE 0x10
#define SCI_SCR_BIT_TE 0x20

void rx220_init_setup()
{
	int i;

	////// Clock settings //////
	SYSTEM.SCKCR.BIT.PCKD = 0x00; // Peripheral clock D divider
	SYSTEM.SCKCR.BIT.PCKB = 0x00; // Peripheral clock B divider
	SYSTEM.SCKCR.BIT.BCK = 0x00; // External bus clock divider
	SYSTEM.SCKCR.BIT.ICK = 0x00; // System clock divider
	SYSTEM.SCKCR.BIT.FCK = 0x00; // Flash IF clock divider

//// Register protect off ////
	SYSTEM.PRCR.WORD = 0xA503;

	//// Main clock ////
	SYSTEM.MOSCCR.BIT.MOSTP = 0x1; // Main oscillator stop
	SYSTEM.MOFCR.BIT.MODRV = 0x0; //
	SYSTEM.MOFCR.BIT.MODRV2 = 0x3; //
	SYSTEM.MOFCR.BIT.MOSEL = 0; //
	// P36 : EXTAL, P37 : XTAL Port

	PORT3.PDR.BIT.B6 = 0;
	PORT3.PDR.BIT.B7 = 0;

	SYSTEM.MOSCWTCR.BIT.MSTS = 0xC; // Main oscillator wait cycle, 0xC : 65536 cycles
	SYSTEM.MOSCCR.BIT.MOSTP = 0x0; // Main oscillator start
	while(SYSTEM.MOSCCR.BIT.MOSTP != 0x0) ; // wait for oscillator to be stable
//	SYSTEM.SCKCR3.BIT.CKSEL = 0x2; // Switch clock source, 3 bits, 010 : main oscillator
	SYSTEM.SCKCR3.WORD = 0x200; // SCKCR3 ... bit access was unavailable

	//// HOCO stop ////
	SYSTEM.HOCOCR.BIT.HCSTP = 1;
	SYSTEM.HOCOPCR.BIT.HOCOPCNT = 1;

	//// LPC ////
	SYSTEM.MSTPCRA.BIT.ACSE = 0; // All module clock stop mode enable -> disable
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0; // CMT unit0 (CMT0, CMT1) enable
	SYSTEM.MSTPCRB.BIT.MSTPB30 = 0; // SCI1 enable
	SYSTEM.MSTPCRB.BIT.MSTPB26 = 0; // SCI5 enable
	SYSTEM.MSTPCRB.BIT.MSTPB25 = 0; // SCI6 enable
	SYSTEM.MSTPCRB.BIT.MSTPB4 = 0; // SCI12 enable


	//// RTC ////
#if USE_RTC == 1

	SYSTEM.SOSCCR.BIT.SOSTP = 1; // Sub clock (for RTC) stop
	while(!SYSTEM.SOSCCR.BIT.SOSTP) ;
	RTC.RCR3.BIT.RTCEN = 0; //RTC disable
	while(RTC.RCR3.BIT.RTCEN) ;

	RTC.RCR3.BIT.RTCDV = 0x6; // Sub clock drive ability : 110_b -> for standard CL

	SYSTEM.SOSCWTCR.BYTE = 0x0; // Sub clock oscillator wait time : 2sec + 2cycles
	SYSTEM.SOSCCR.BIT.SOSTP = 0; // Sub clock (for RTC) start
	while(SYSTEM.SOSCCR.BIT.SOSTP) ;

	RTC.RCR3.BIT.RTCEN = 1; // Sub clock (for RTC) start, RTC enable
	while(!RTC.RCR3.BIT.RTCEN) ;

	for(i = 0; i < 2000; i++)// Wait 6 counts of sub clock -> 0.18 [ms], about 3600 counts of 20MHz clock
		;

	RTC.RCR2.BYTE = 0x0; // START = 0, CNTMD = 0
	while(RTC.RCR2.BYTE != 0x0)
		;
	RTC.RCR2.BIT.RESET = 1; // Software reset
	while(RTC.RCR2.BIT.RESET)
		;

//	RTC.RCR1.BIT.AIE = 0; // Alarm interrupt : disable
//	RTC.RCR1.BIT.CIE = 0; // Carry interrupt : disable
//	RTC.RCR1.BIT.PES = 0xE; // periodic interrupt : occurs every 1 second
//	RTC.RCR1.BIT.RTCOS = 0; // RTC output select : 1Hz
	RTC.RCR1.BYTE = 0xE4;
	while(RTC.RCR1.BYTE != 0xE4)
		;

//	RTC.RCR2.BIT.CNTMD = 0;
//	RTC.RCR2.BIT.HR24 = 1;
//	RTC.RCR2.BIT.START = 1;
	RTC.RCR2.BYTE = 0x41;
	while(RTC.RCR2.BYTE != 0x41)
		;

#endif

//// Register protect on ////
	SYSTEM.PRCR.WORD = 0xA500;

	//// 1ms timer (CMT0) setting ////
	CMT0.CMCR.BIT.CKS = 0x0;	// count source : PCLK / 8
	CMT0.CMCR.BIT.CMIE = 1;		// interrupt enable
	CMT0.CMCOR = 2499; 			// interrupt cycle : PCLK(=20MHz) / 8 / 2499 = 1ms

	CMT.CMSTR0.BIT.STR0 = 1; // CMT0 count start

	// set PMR to GPIO
	PORT2.PMR.BYTE = 0;
	PORT3.PMR.BYTE = 0;
	PORTA.PMR.BYTE = 0;
	PORTB.PMR.BYTE = 0;
	PORTE.PMR.BYTE = 0;
	PORTH.PMR.BYTE = 0;

	//// UART (SCI1) setting ////

	SCI1.SMR.BYTE = 0x00; // clock : PCLK(no divider), UART
	SCI1.SCR.BYTE = 0x0;
	SCI1.SCR.BIT.CKE = 0x0; // internal clock, SCK1 is GPIO
	SCI1.SCR.BIT.RIE = 1;

	SCI1.SEMR.BIT.ABCS = 1; // 8 clocks per 1 bit transfer
	SCI1.BRR = 129; // Baud rate : 9600 bps (actually 9615, @ PCLK=20MHz, no divider )

	SCI1.SCMR.BYTE = 0x00;
	SCI1.SCMR.BIT.SDIR = 0; // LSB first



	// SPI for SD card (SCI5) setting
	SCI5.SCR.BYTE = 0x0; // RX, TX disable

	SCI5.SMR.BYTE = 0x00;
	SCI5.SMR.BIT.CKS = 0; // clock : PCLK
	SCI5.SMR.BIT.CM = 1; // synchronous communication

	SCI5.SCMR.BYTE = 0x00;
	SCI5.SCMR.BIT.SDIR = 1; // MSB first
//	SCI5.BRR = 0x4; // SCK rate : 0x4 -> 1MHz
	SCI5.BRR = 0x49; // SCK rate : 0x49 -> 100kHz

	SCI5.SPMR.BIT.MSS = 0;		// Master mode
	SCI5.SPMR.BIT.CKPH = 0;	//
	SCI5.SPMR.BIT.CKPOL = 0;	// Data is sampled at rising edge of SCK

//	SCI5.SCR.BIT.CKE = 0x1;
//	SCI5.SCR.BIT.RIE = 1; // RX interrupt enable (to assert RXI flag)
//	SCI5.SCR.BIT.TIE = 1; // TX interrupt enable (to assert TXI flag)
	SCI5.SCR.BYTE = 0xF0;

	// SPI for accelerometer ADXL345 (SCI6) setting
	SCI6.SCR.BYTE = 0x0; // RX, TX disable

	SCI6.SMR.BYTE = 0x00;
	SCI6.SMR.BIT.CKS = 0; // clock : PCLK
	SCI6.SMR.BIT.CM = 1; // synchronous communication

	SCI6.SCMR.BYTE = 0x00;
	SCI6.SCMR.BIT.SDIR = 1; // MSB first
	SCI6.BRR = 0x1; // SCK rate : 0x1 -> 2.5MHz
//	SCI6.BRR = 0x4; // SCK rate : 0x4 -> 1MHz

	SCI6.SPMR.BIT.MSS = 0;		// Master mode
	SCI6.SPMR.BIT.CKPH = 0;	//
	SCI6.SPMR.BIT.CKPOL = 0;	// Data is sampled at rising edge of SCK

//	SCI6.SCR.BIT.CKE = 0x1;
//	SCI6.SCR.BIT.RIE = 1; // RX interrupt enable (to assert RXI flag)
//	SCI6.SCR.BIT.TIE = 1; // TX interrupt enable (to assert TXI flag)
	SCI6.SCR.BYTE = 0xF0; // RX, TX enable


	// SPI for LCD module (SCI12) setting
	SCI12.SCR.BYTE = 0x00; // RX, TX disable

	SCI12.SMR.BYTE = 0x00;
	SCI12.SMR.BIT.CKS = 0; // clock : PCLK
	SCI12.SMR.BIT.CM = 1; // synchronous communication

	SCI12.SCMR.BYTE = 0x00;
	SCI12.SCMR.BIT.SDIR = 1; // MSB first

	SCI12.BRR = 0x0;			// SCK rate : 0x0 -> 5MHz
//	SCI12.BRR = 0x4;
//	SCI12.BRR = 0x49;

	SCI12.SPMR.BIT.MSS = 0;		// Master mode
	SCI12.SPMR.BIT.CKPH = 0;	//
	SCI12.SPMR.BIT.CKPOL = 0;	// Data is sampled at rising edge of SCK

	SCI12.SCR.BYTE = 0xA0; // TX, TXI enable

	// IO port function mapping

// MPC protect off //
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;

	MPC.P26PFS.BYTE = 0xA; // UART TX
	MPC.P30PFS.BYTE = 0xA; // UART RX

	MPC.PA0PFS.BYTE = 0x0; // SD_CS
	MPC.PA1PFS.BYTE = 0xA; // SD_SCK
	MPC.PA3PFS.BYTE = 0xA; // SD_MISO
 	MPC.PA4PFS.BYTE = 0xA; // SD_MOSI

 	MPC.PB0PFS.BYTE = 0xB; // ADXL345_MISO
 	MPC.PB1PFS.BYTE = 0xB; // ADXL345_MOSI
 	MPC.PB3PFS.BYTE = 0xB; // ADXL345_SCK
 	MPC.PB5PFS.BYTE = 0x0; // ADXL345_CS


	MPC.PE0PFS.BYTE = 0xC; // LCD_SCK
	MPC.PE1PFS.BYTE = 0xC; // LCD_SDI (MOSI)
	MPC.PE2PFS.BYTE = 0x0; // LCD_CS
	MPC.PE3PFS.BYTE = 0x0; // LCD_RS

	MPC.P40PFS.BYTE = 0x0; // LCD_NPWR
	MPC.P41PFS.BYTE = 0x0; // LCD_NRST
	MPC.P42PFS.BYTE = 0x0; // LCD_LED

	MPC.PH1PFS.BIT.ISEL = 1; // Use IRQ0 interrupt
	MPC.PH1PFS.BIT.PSEL = 0x0;

	MPC.PH2PFS.BIT.ISEL = 1; // Use IRQ1 interrupt
	MPC.PH2PFS.BIT.PSEL = 0x0;

// MPC protect on //
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;


//	PORT2.PDR.BIT.B6 = 0;
	PORT2.PMR.BIT.B6 = 1; // UART TX
//	PORT3.PDR.BIT.B0 = 0;
	PORT3.PMR.BIT.B0 = 1; // UART RX


	PORTA.PMR.BIT.B0 = 0; // SD_CS
	PORTA.PDR.BIT.B0 = 1;
	PORTA.PODR.BIT.B0 = 1;
	PORTA.PCR.BIT.B0 = 0;
//	PORTA.ODR0. = 0;

	PORTA.PDR.BIT.B1 = 1; // SD_SCK
	PORTA.PODR.BIT.B1 = 1;
	PORTA.PCR.BIT.B1 = 0;
	PORTA.ODR0.BIT.B2 = 0;
	PORTA.PMR.BIT.B1 = 1;

	PORTA.PDR.BIT.B3 = 0; // SD_MISO
	PORTA.PCR.BIT.B3 = 0;
	PORTA.ODR0.BIT.B6 = 0;
	PORTA.PMR.BIT.B3 = 1;

	PORTA.PDR.BIT.B4 = 1; // SD_MOSI
	PORTA.PODR.BIT.B4 = 1;
	PORTA.PCR.BIT.B4 = 0;
	PORTA.ODR1.BIT.B0 = 0;
	PORTA.PMR.BIT.B4 = 1;


	PORTB.PODR.BIT.B5 = 1; // ADXL345_CS
	PORTB.PCR.BIT.B5 = 0;
	PORTB.ODR1.BIT.B2 = 0;
	PORTB.PMR.BIT.B5 = 0;
	PORTB.PDR.BIT.B5 = 1;

	PORTB.PDR.BIT.B0 = 0;// ADXL345_MISO
	PORTB.PODR.BIT.B0 = 0;
	PORTB.PCR.BIT.B0 = 0;
	PORTB.ODR0.BIT.B0 = 0;
	PORTB.PMR.BIT.B0 = 1;

	PORTB.PDR.BIT.B1 = 1; // ADXL345_MOSI
	PORTB.PODR.BIT.B1 = 1;
	PORTB.PCR.BIT.B1 = 0;
	PORTB.ODR0.BIT.B2 = 0;
	PORTB.PMR.BIT.B1 = 1;

	PORTB.PDR.BIT.B3 = 0; // ADXL345_SCK
	PORTB.PCR.BIT.B3 = 0;
	PORTB.ODR0.BIT.B6 = 0;
	PORTB.PMR.BIT.B3 = 1;


	// ADXL345_INT1 interrupt
	ICU.IRQFLTE0.BIT.FLTEN0 = 0; // Digital filter disable
	ICU.IRQFLTC0.BIT.FCLKSEL0 = 0; // Digital filter source : PCLK
	PORTH.PDR.BIT.B1 = 0;
	PORTH.PMR.BIT.B1 = 0;
//	ICU.IRQCR[0].BIT.IRQMD = 0x02; // Interrupt mode : rising edge
	ICU.IRQCR[0].BIT.IRQMD = 0x01; // Interrupt mode : falling edge
	IR(ICU, IRQ0) = 0; // Clear IR flag
//	ICU.IRQFLTE0.BIT.FLTEN0 = 1; // Digital filter enable

	// Push switch
	ICU.IRQFLTE0.BIT.FLTEN1 = 0; // Digital filter disable
	ICU.IRQFLTC0.BIT.FCLKSEL1 = 3; // Digital filter source : PCLK / 64
	PORTH.PDR.BIT.B2 = 0;
	PORTH.PMR.BIT.B2 = 0;
	PORTH.PCR.BIT.B2 = 1;
//	ICU.IRQCR[1].BIT.IRQMD = 0x01; // Interrupt mode : falling edge
	ICU.IRQCR[1].BIT.IRQMD = 0x03; // Interrupt mode : both edges
	IR(ICU, IRQ1) = 0; // Clear IR flag
	ICU.IRQFLTE0.BIT.FLTEN1 = 1; // Digital filter enable

	// LCD_NPWR
	PORT4.PMR.BYTE = 0x0;
	PORT4.PDR.BIT.B0 = 1; // output
	PORT4.PODR.BIT.B0 = 0;
	// LCD_NRST
	PORT4.PDR.BIT.B1 = 1; // output
	PORT4.PODR.BIT.B1 = 0;
	// LCD_LED
	PORT4.PDR.BIT.B2 = 1; // output
	PORT4.PODR.BIT.B2 = 1;

	// LCD_SCK
	PORTE.PCR.BIT.B0 = 1; // pull up enable
	PORTE.PDR.BIT.B0 = 0;
	PORTE.PMR.BIT.B0 = 1;
	// LCD_SDA
	PORTE.PCR.BIT.B1 = 1; // pull up enable
	PORTE.PDR.BIT.B1 = 0;
	PORTE.PMR.BIT.B1 = 1; // SPI_MOSI

	// LCD_CS
	PORTE.PODR.BIT.B2 = 1;
	PORTE.PDR.BIT.B2 = 1; // output
	// LCD_RS
	PORTE.PODR.BIT.B3 = 1;
	PORTE.PDR.BIT.B3 = 1; // output



	// interrupt controller
	IPR(RTC, PRD) = 15;
	IPR(CMT0, CMI0) = 10;
	IPR(SCI1, RXI1) = 15;
	IPR(ICU, IRQ0) = 15;
	IPR(ICU, IRQ1) = 15;

	IEN(RTC, PRD) = 1;
	IEN(CMT0, CMI0) = 1;
	IEN(SCI1, RXI1) = 1;


}


//------------------------------------------------------------------------
// RTC
//------------------------------------------------------------------------
void rtc_reset()
{
	RTC.RCR2.BIT.RESET = 1;
	while(RTC.RCR2.BIT.RESET)
		;
}

void rtc_stop()
{
	RTC.RCR2.BIT.START = 0;
	while(RTC.RCR2.BIT.START)
		;
}
void rtc_start()
{
	RTC.RCR2.BIT.START = 1;
	while(!RTC.RCR2.BIT.START)
		;
}

void rtc_set_yr(unsigned char yr10, unsigned char yr1)
{
	RTC.RYRCNT.BIT.YR10 = yr10;
	RTC.RYRCNT.BIT.YR1 = yr1;
}
void rtc_set_mon(unsigned char mon10, unsigned char mon1)
{
	RTC.RMONCNT.BIT.MON10 = mon10;
	RTC.RMONCNT.BIT.MON1 = mon1;
}
void rtc_set_day(unsigned char day10, unsigned char day1)
{
	RTC.RDAYCNT.BIT.DATE10 = day10;
	RTC.RDAYCNT.BIT.DATE1 = day1;
}
void rtc_set_wk(unsigned char wk) // 0 : Sunday, 1 : Monday, ...
{
	RTC.RWKCNT.BYTE = wk;
}
void rtc_set_hr(unsigned char hr10, unsigned char hr1)
{
	RTC.RHRCNT.BIT.HR10 = hr10;
	RTC.RHRCNT.BIT.HR1 = hr1;
}
void rtc_set_min(unsigned char min10, unsigned char min1)
{
	RTC.RMINCNT.BIT.MIN10 = min10;
	RTC.RMINCNT.BIT.MIN1 = min1;
}
void rtc_set_sec(unsigned char sec10, unsigned char sec1)
{
	RTC.RSECCNT.BIT.SEC10 = sec10;
	RTC.RSECCNT.BIT.SEC1 = sec1;
}


//------------------------------------------------------------------------
// UART
//------------------------------------------------------------------------
void sci1_uart_rx_enable()
{
	SCI1.SCR.BIT.RE = 1;
}
void sci1_uart_rx_disable()
{
	SCI1.SCR.BIT.RE = 0;
}
void sci1_uart_tx(char d)
{
	SCI1.TDR = d;
}
void sci1_uart_tx_enable()
{
	SCI1.SCR.BIT.TE = 1;
}
void sci1_uart_tx_disable()
{
	SCI1.SCR.BIT.TE = 0;
}


//------------------------------------------------------------------------
// SD card
//------------------------------------------------------------------------
void sci5_sd_enable(void)
{
	SCI5.SCR.BYTE |= (SCI_SCR_BIT_RE | SCI_SCR_BIT_TE);
}
void sci5_sd_disable(void)
{
	SCI5.SCR.BYTE &= ( (~SCI_SCR_BIT_RE) & (~SCI_SCR_BIT_TE) );
}

void sci5_sd_set_baud_high(void)
{
	sci5_sd_disable();

// 100kHz
//	SCI5.BRR = 49;
//	SCI5.SMR.BIT.CKS = 0; // clock : PCLK

// 1MHz
	SCI5.BRR = 4;
	SCI5.SMR.BIT.CKS = 0; // clock : PCLK

	sci5_sd_enable();
}
void sci5_sd_set_baud_low(void)
{
	sci5_sd_disable();

// 10kHz
//	SCI5.BRR = 124;
//	SCI5.SMR.BIT.CKS = 1; // clock : PCLK/4

// 100kHz
	SCI5.BRR = 49;
	SCI5.SMR.BIT.CKS = 0; // clock : PCLK

	sci5_sd_enable();
}

void sci5_sd_set_baud(_UBYTE d)
{
	sci5_sd_disable();
	SCI5.BRR = d;
	SCI5.SMR.BIT.CKS = 0; // clock : PCLK
	sci5_sd_enable();
}


_UBYTE sci5_sd_transceive(_UBYTE d)
{
	while(!SCI5_SD_TX_END)
		;
//	while(!SCI5_SD_TXI)
//		;
//	SCI5_SD_TXI = 0;

	SCI5_SD_TXDATA = d;

	while(!SCI5_SD_RXI)
		;
	SCI5_SD_RXI = 0;
	return (_UBYTE)SCI5_SD_RXDATA;

}

//------------------------------------------------------------------------
// ADXL345
//------------------------------------------------------------------------
void sci6_ADXL345_enable(void)
{
	SCI6.SCR.BYTE |= (SCI_SCR_BIT_RE | SCI_SCR_BIT_TE);
}
void sci6_ADXL345_disable(void)
{
	SCI6.SCR.BYTE &= ( (~SCI_SCR_BIT_RE) & (~SCI_SCR_BIT_TE) );
}

_UBYTE sci6_ADXL345_transceive(_UBYTE d)
{
	while(!SCI6_ADXL345_TX_END)
		;
//	while(!SCI6_ADXL345_TXI)
//		;
//	SCI6_ADXL345_TXI = 0;

	SCI6_ADXL345_TXDATA = d;

	while(!SCI6_ADXL345_RXI)
		;
	SCI6_ADXL345_RXI = 0;
	return (_UBYTE)SCI6_ADXL345_RXDATA;

}

void adxl345int1_int_enable()
{
	IEN(ICU, IRQ0) = 1;
}
void adxl345int1_int_disable()
{
	IEN(ICU, IRQ0) = 0;
}

void (*adxl345int1_int_routine)(void);
void adxl345int1_int_set_callback(void (*cb)(void))
{
	adxl345int1_int_routine = cb;
}

void INT_Excep_ICU_IRQ0(void)
{
	(*adxl345int1_int_routine)();
}


//------------------------------------------------------------------------
// LCD
//------------------------------------------------------------------------
void sci12_LCD_enable(void)
{
	SCI12.SCR.BYTE |= (SCI_SCR_BIT_RE | SCI_SCR_BIT_TE);
}
void sci12_LCD_disable(void)
{
	SCI12.SCR.BYTE &= ( (~SCI_SCR_BIT_RE) & (~SCI_SCR_BIT_TE) );
}

void sci12_LCD_set_baud(_UBYTE d)
{
	sci12_LCD_disable();
	SCI12.BRR = d;
	SCI12.SMR.BIT.CKS = 0; // clock : PCLK
	sci12_LCD_enable();

}

void sci12_LCD_transmit(_UBYTE d)
{
//	while(!SCI12_LCD_TXI)
////		uart_puts("LCD_TXI\r\n");
//		;
//	SCI12_LCD_TXI = 0;
//	SCI12_LCD_TXDATA = d;

	SCI12_LCD_TXDATA = d;
	while(!SCI12_LCD_TX_END)
		;
}

#define LCD_SCK_O PORTE.PODR.BIT.B0
#define LCD_SDA_I PORTE.PIDR.BIT.B1

void sci12_LCD_com_mode(char spitx_gpiorx)
{
	if(spitx_gpiorx == SCI12_SPITX){ // use SPI (for TX)

		PORTE.PDR.BIT.B0 = 0;
		PORTE.PMR.BIT.B0 = 1; // LCD SCK

		PORTE.PDR.BIT.B1 = 0;
		PORTE.PMR.BIT.B1 = 1; // LCD SDI (MOSI)
	}
	else{ // use GPIO (for RX)

		PORTE.PODR.BIT.B0 = 1; // SCK is HIGH when in idle state
		PORTE.PDR.BIT.B0 = 1;
		PORTE.PMR.BIT.B0 = 0;

		PORTE.PDR.BIT.B1 = 0;
		PORTE.PMR.BIT.B1 = 0; // portE.bit1 is SDA input
	}
}

void sci12_LCD_dummy_clock()
{
	LCD_SCK_O = 0;
	LCD_SCK_O = 1;
}

_UBYTE sci12_LCD_read()
{
	_UBYTE rtn;
	int i;

	rtn = 0;

	// Data is shifted out at falling edge of SCK,
	// and SDA is disabled after SCK rises.
	for(i = 0; i < 8; i++){
		LCD_SCK_O = 0;
		rtn <<= 1;
		rtn |= LCD_SDA_I;
		LCD_SCK_O = 1;
	}

	return rtn;
}



//------------------------------------------------------------------------
// PSW
//------------------------------------------------------------------------
static void (*psw_int_routine)(void);
void INT_Excep_ICU_IRQ1(void){ (*psw_int_routine)(); };

void psw_int_enable()
{
	IEN(ICU, IRQ1) = 1;
}
void psw_int_disable()
{
	IEN(ICU, IRQ1) = 0;
}
void psw_int_set_callback(void (*cb)(void))
{
	psw_int_routine = cb;
}






