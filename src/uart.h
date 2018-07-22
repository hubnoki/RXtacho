/*
 * uart.h
 *
 *  Created on: 2015/09/15
 *      Author: akihiro
 *
 *  2016/02/10 kinoshita
 *      renamed "uart_kbhit_crlf()" -> "uart_kbhit_s()"
 *  2016/02/13 kinoshita
 *  	added "uart_gets()"
 *
 */

#ifndef UART_H_
#define UART_H_

#include <stdbool.h>

#define UART_ECHO 1

// initialize SCI1 module
// prepare FIFO buffer for RX interrupt routine
void uart_set(char *rxbuf, int nrxbuf);

void uart_putc(char c);
void uart_puts(char *s);

char uart_getc();
void uart_gets(char *s);

// return if one or more characters are received
bool uart_kbhit();
// return if '\r' or '\n' are received
bool uart_kbhit_s();

// RX interrupt routine
// input received data into FIFO buffer
void uart_rx_int();


#endif /* UART_H_ */
