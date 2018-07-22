/*
 * uart.c
 *
 *  Created on: 2015/09/15
 *      Author: akihiro
 *
 *  2015/10/13 modified uart_putc() and uart_putc_multi() to wait for last transmission completion
 *  2016/02/10 kinoshita
 *      modified for RXtacho project
 *      renamed "uart_kbhit_crlf()" -> "uart_kbhit_s()"
 *  2016/02/13 kinoshita
 *  	added "uart_gets()"
 *
 *
 */

#include "uart.h"
#include "fifo_char.h"
#include "hardware_lib.h"

static FIFO_CHAR rx_buf;

static char rx_break_flag;


#define UART_RX_BUF_INT SCI1_UART_RXDATA


// prepare FIFO buffer for RX interrupt routine
void uart_set(char *rxbuf, int nrxbuf)
{
	rx_buf.buf = rxbuf;
	rx_buf.bufsz = nrxbuf;
	fifoc_clear(&rx_buf);

	rx_break_flag = false;

}


void uart_putc(char c)
{
	while(!SCI1_UART_TX_END)
		;	// wait UART module to complete last transmission
	SCI1_UART_TXDATA = c;
}

void uart_puts(char *s)
{
	char *p;

	p = s;
	while(*p != '\0'){
		uart_putc(*p);
		p++;
	}

}


char uart_getc()
{
	static bool poped_CR = false;
	char c;

	while( fifoc_empty(&rx_buf) )
		;
	fifoc_out(&rx_buf, &c);

	// put the line break flag down
	// assume line break code to be CR, LF, or CR+LF
	if(c == '\r'){
		poped_CR = true;
		rx_break_flag = false;
	}
	else{
		if(c == '\n'){
			if(!poped_CR)
				rx_break_flag = false;
		}
		poped_CR = false;
	}

	return c;
}

void uart_gets(char *s)
{
	char *p, c;

	p = s;
	c = uart_getc();
	while( (c != '\r') & (c != '\n') ){
		*p = c;
		p++;
		c = uart_getc();
	}
	*p = '\0';
}

// return if one or more characters are received
bool uart_kbhit()
{
	return !fifoc_empty(&rx_buf);
}

// return if '\r' or '\n' are received
bool uart_kbhit_s()
{
	return rx_break_flag;
}

// RX interrupt routine
// input received data into FIFO buffer
// If buffer is almost full (capacity - 1), do not accept input data,
// except for CR or LF.
void uart_rx_int()
{
	char rx_tmp;
	static bool received_CR = false;
	bool empty;

	int rest_capacity;


	rx_tmp = UART_RX_BUF_INT;
	rest_capacity = fifoc_capacity(&rx_buf) - fifoc_size(&rx_buf);

	//// backspace ////
	if(rx_tmp == '\b'){
		empty = fifoc_empty(&rx_buf); // check empty before pop
		fifoc_pop(&rx_buf);
		received_CR = false;
#if UART_ECHO == 1
		if(!empty){
			uart_putc('\b'); uart_putc(' '); uart_putc('\b');
		}
#endif
	}
	//// CR ////
	else if(rx_tmp == '\r'){
		if(rest_capacity > 0){
			fifoc_in(&rx_buf, rx_tmp);
			rx_break_flag = true;
			received_CR = true;
#if UART_ECHO == 1
			uart_putc('\r'); uart_putc('\n');
#endif
		}
	}
	//// LF ////
	else if(rx_tmp == '\n'){
		if(rest_capacity > 0){
			fifoc_in(&rx_buf, rx_tmp);
			if(!received_CR){
				rx_break_flag = true;
#if UART_ECHO == 1
				uart_putc('\r'); uart_putc('\n');
#endif
			}
			received_CR = false;
		}
	}
	//// other characters ////
	else{
		if(rest_capacity > 1){
			fifoc_in(&rx_buf, rx_tmp);
			received_CR = false;
#if UART_ECHO == 1
			uart_putc(rx_tmp);
#endif
		}
	}


}

