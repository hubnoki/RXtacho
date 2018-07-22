/*
 * fifo_char.h
 *
 *  Created on: 2013/12/20
 *      Author: kinoshita.akihiro
 *
 *  2015/09/10 modified buffer size to be variable
 *  		   added "fifoc_setbuf()"
 *
 */

#ifndef FIFO_CHAR_H_
#define FIFO_CHAR_H_

typedef struct{
	char *buf;
	int bufsz;
	int p; 		// start point of the buffer
	int n;		// number of data
}FIFO_CHAR;


void fifoc_set_buf(FIFO_CHAR *fifoc, char *buf, int bufsz);
void fifoc_clear(FIFO_CHAR *fifoc);
void fifoc_in(FIFO_CHAR *fifoc, char data);
void fifoc_out(FIFO_CHAR *fifoc, char *data);
int fifoc_size(FIFO_CHAR *fifoc);
int fifoc_empty(FIFO_CHAR *fifoc);
int fifoc_full(FIFO_CHAR *fifoc);

// check oldest data (data to output next)
char fifoc_peek(FIFO_CHAR *fifoc);

// output latest data
char fifoc_pop(FIFO_CHAR *fifoc);

// return buffer size
int fifoc_capacity(FIFO_CHAR *fifoc);

#endif /* FIFO_CHAR_H_ */
