/*
 * fifo_char.c
 *
 *  Created on: 2013/12/20
 *      Author: kinoshita.akihiro
 *
 * 2015/09/10 modified buffer size to be variable
 *            added "fifoc_set_buf()"
 *
 */

#include "fifo_char.h"


void fifoc_set_buf(FIFO_CHAR *fifoc, char *buf, int bufsz)
{
	fifoc->buf = buf;
	fifoc->bufsz = bufsz;
}

void fifoc_clear(FIFO_CHAR *fifoc)
{
	int i, sz;

	sz = fifoc->bufsz;

	fifoc->p = 0;
	fifoc->n = 0;
	for(i = 0; i < sz; i++)
		fifoc->buf[i] = 0;
}

void fifoc_in(FIFO_CHAR *fifoc, char data)
{
	int sz;

	sz = fifoc->bufsz;

	if(fifoc->n < sz){
		fifoc->buf[(fifoc->n + fifoc->p) % sz] = data;
		fifoc->n++;
	}
}

void fifoc_out(FIFO_CHAR *fifoc, char *data)
{
	if(fifoc->n){
		*data = fifoc->buf[fifoc->p];
		fifoc->n--;
		if( (++fifoc->p) >= (fifoc->bufsz) )
			fifoc->p = 0;
	}
}

int fifoc_size(FIFO_CHAR *fifoc)
{
	return fifoc->n;
}

int fifoc_empty(FIFO_CHAR *fifoc)
{
	return (fifoc->n == 0);
}

int fifoc_full(FIFO_CHAR *fifoc)
{
	return (fifoc->n >= (fifoc->bufsz) );
}


// check oldest data (data to output next)
char fifoc_peek(FIFO_CHAR *fifoc)
{
	return fifoc->buf[fifoc->p];
}


// output latest data
char fifoc_pop(FIFO_CHAR *fifoc)
{
	if(fifoc->n)
		fifoc->n--;

	return fifoc->buf[(fifoc->n + fifoc->p) % fifoc->bufsz];
}


// return buffer size
int fifoc_capacity(FIFO_CHAR *fifoc)
{
	return fifoc->bufsz;
}


