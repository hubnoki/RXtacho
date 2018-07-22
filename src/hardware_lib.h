/*
 * hardware_lib.h
 *
 *  Created on: 2016/01/20
 *      Author: akihiro
 */

#ifndef HARDWARE_LIB_H_
#define HARDWARE_LIB_H_

#include <stdbool.h>
#include "iodefine.h"
#include "typedefine.h"

void rx220_init_setup();

//------------------------------------------------------------------------
// RTC
//------------------------------------------------------------------------
#define USE_RTC 0

void rtc_reset();
void rtc_start();
void rtc_stop();
// RTC must be stopped before below functions are called
void rtc_set_yr(unsigned char yr10, unsigned char yr1);
void rtc_set_mon(unsigned char mon10, unsigned char mon1);
void rtc_set_day(unsigned char day10, unsigned char day1);
void rtc_set_wk(unsigned char wk); // 0 : Sunday, 1 : Monday, ...
void rtc_set_hr(unsigned char hr10, unsigned char hr1);
void rtc_set_min(unsigned char min10, unsigned char min1);
void rtc_set_sec(unsigned char sec10, unsigned char sec1);
void rtc_adj(unsigned char adj); // adj : 0 ~ 63 (subclock cycles)


//------------------------------------------------------------------------
// UART
//------------------------------------------------------------------------
// SCI1 -> UART : 9600bps, RX interrupt enabled, TX interrupt disabled
void sci1_uart_rx_enable();
void sci1_uart_rx_disable();
void sci1_uart_tx(char d);
void sci1_uart_tx_enable();
void sci1_uart_tx_disable();

#define SCI1_UART_RXDATA SCI1.RDR
#define SCI1_UART_TXDATA SCI1.TDR
#define SCI1_UART_TX_END SCI1.SSR.BIT.TEND // 1 -> TX shift register is cleared
#define SCI1_UART_RX_ENABLE SCI1.SCR.BIT.RE
#define SCI1_UART_TX_ENABLE SCI1.SCR.BIT.TE

#define SCI1_UART_TXDATA_READY IR(SCI1, TXI1) // asserted when TDR data is latched into shift register
												// (this is edge signal)

//------------------------------------------------------------------------
// SD card
//------------------------------------------------------------------------
#define SD_CS PORTA.PODR.BIT.B0

#define SCI5_SD_TXDATA 		SCI5.TDR
#define SCI5_SD_RXDATA 		SCI5.RDR
#define SCI5_SD_TX_END 		SCI5.SSR.BIT.TEND // 1 -> TX shift register is cleared
#define SCI5_SD_RXI 		IR(SCI5, RXI5)
#define SCI5_SD_TXI 		IR(SCI5, TXI5)

#define SCI5_SD_STATE 		SCI5.SSR.BYTE
#define SCI5_SD_STATE_TEND 	0x04 // transmit end
#define SCI5_SD_STATE_PER	0x08 // parity error
#define SCI5_SD_STATE_FER	0x10 // framing error
#define SCI5_SD_STATE_ORER	0x20 // overrun error

#define SCI5_SD_BAUD_REG SCI5.BRR
#define SCI5_SD_BAUD_100K 49
#define SCI5_SD_BAUD_1M 4

void sci5_sd_enable(void);
void sci5_sd_disable(void);
void sci5_sd_set_baud_high(void);
void sci5_sd_set_baud_low(void);
void sci5_sd_set_baud(_UBYTE d);
_UBYTE sci5_sd_transceive(_UBYTE d);


//------------------------------------------------------------------------
// ADXL345
//------------------------------------------------------------------------
#define SCI6_ADXL345_CS PORTB.PODR.BIT.B5

#define SCI6_ADXL345_TXDATA 		SCI6.TDR
#define SCI6_ADXL345_RXDATA 		SCI6.RDR
#define SCI6_ADXL345_TX_END 		SCI6.SSR.BIT.TEND // 1 -> TX shift register is cleared
#define SCI6_ADXL345_RXI 		IR(SCI6, RXI6)
#define SCI6_ADXL345_TXI 		IR(SCI6, TXI6)

#define SCI6_ADXL345_STATE 		SCI6.SSR.BYTE
#define SCI6_ADXL345_STATE_TEND 	0x04 // transmit end
#define SCI6_ADXL345_STATE_PER	0x08 // parity error
#define SCI6_ADXL345_STATE_FER	0x10 // framing error
#define SCI6_ADXL345_STATE_ORER	0x20 // overrun error

#define SCI6_ADXL345_BAUD_REG SCI5.BRR
#define SCI6_ADXL345_BAUD_100K 49
#define SCI6_ADXL345_BAUD_1M 4

void sci6_ADXL345_enable(void);
void sci6_ADXL345_disable(void);
_UBYTE sci6_ADXL345_transceive(_UBYTE d);

#define ADXL345_INT1_PIN PORTH.PIDR.BIT.B1

// ADXL345 interrupt (connected to IRQ0) functions
void adxl345int1_int_enable();
void adxl345int1_int_disable();
void adxl345int1_int_set_callback(void (*cb)(void));



//------------------------------------------------------------------------
// LCD
//------------------------------------------------------------------------
#define LCD_NPWR PORT4.PODR.BIT.B0  // also supplies power to SD card
#define LCD_NRST PORT4.PODR.BIT.B1
#define LCD_LED PORT4.PODR.BIT.B2

#define LCD_CS PORTE.PODR.BIT.B2
#define LCD_RS PORTE.PODR.BIT.B3

#define SCI12_LCD_TXDATA SCI12.TDR
#define SCI12_LCD_TX_END SCI12.SSR.BIT.TEND // 1 -> TX shift register is cleared
#define SCI12_LCD_TX_ENABLE SCI12.SCR.BIT.TE

#define SCI12_LCD_TXI IR(SCI12, TXI12)

void sci12_LCD_enable(void);
void sci12_LCD_disable(void);
void sci12_LCD_set_baud(_UBYTE d);
void sci12_LCD_transmit(_UBYTE d);

#define SCI12_SPITX 1
#define SCI12_GPIORX 0
void sci12_LCD_com_mode(char spitx_gpiorx);

void sci12_LCD_dummy_clock();
_UBYTE sci12_LCD_read();


//------------------------------------------------------------------------
// PSW
//------------------------------------------------------------------------
#define PSW_PIN PORTH.PIDR.BIT.B2

void psw_int_enable();
void psw_int_disable();
void psw_int_set_callback(void (*cb)(void));




void enable_IRQ0();
void disable_IRQ0();



#endif /* HARDWARE_LIB_H_ */
