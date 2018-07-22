/* 
 * File:   timer_soft.h
 * Author: kinoshita.akihiro
 *
 * Created on 2013/09/19, 15:52
 * 
 * 2013/10/25 modified argument of timer_soft_ms()
 * 2013/10/28 renamed : timer_soft_ms() -> timer_soft_count()
 */

#ifndef TIMER_SOFT_H
#define	TIMER_SOFT_H

// tm : timer variable
// tm is reset
void timer_soft_reset(unsigned long *tm);

// tm : timer variable
// return : count from resetting tm
unsigned long timer_soft_count(unsigned long *tm);

void timer_soft_wait(unsigned long t);
// wait t counts

// increment counter
// must be called by interrupt routine
void timer_soft_int();

#endif	/* TIMER_SOFT_H */

