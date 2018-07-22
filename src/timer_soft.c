/*
 * File:   timer_soft.c
 * Author: kinoshita.akihiro
 *
 * Created on 2013/09/19, 15:52
 *
 * 2013/10/15 modified timer_soft_ms()
 * 2013/10/25 modified timer_soft_ms(), timer_soft_reset()
 * 2013/10/28 renamed : timer_soft_ms() -> timer_soft_count()
 *            modified : timer_soft_count(), timer_soft_reset()
 * 2013/11/01 added : get_counter3()
 * 2015/01/23 modified for R8C
 * 
 */

#include"timer_soft.h"

static unsigned long t;
static unsigned long get_counter();

// tm : timer variable
// tm is reset
void timer_soft_reset(unsigned long *tm)
{
    *tm = get_counter();
}

// tm : timer variable
// return : count from resetting tm
unsigned long timer_soft_count(unsigned long *tm)
{
    return get_counter() - *tm;
}

void timer_soft_wait(unsigned long t)
{
	unsigned long tm;

	timer_soft_reset(&tm);
	while(timer_soft_count(&tm) < t)
		;
}


// increment counter
// must be called by interrupt routine
void timer_soft_int()
{
    t++;
}

/*
// get correct value of timer_soft_t
static unsigned long get_counter()
{
    unsigned long tm1, tm2;

    tm1 = t;
    tm2 = t;

    // tm1 > tm2  : carry occurred while tm1 calculation -> *tm = tm2
    // tm1 + 1 < tm2 : carry occured while tm2 calculation -> *tm = tm1+1
    // else( tm1 == tm2 or tm1 + 1 == tm2 )
    //     : no carry occurred while each calculation -> *tm = tm2;
    
    if( tm1 >= tm2 - 1 )
        return tm2;
    else
        return tm1 + 1;
}
*/
/*
static unsigned long get_counter()
{
    unsigned long t1;

    t1 = t;
    while(t1 != t)
        t1 = t;
    return t1;
}
*/

static unsigned long get_counter()
{
	return t;
}




