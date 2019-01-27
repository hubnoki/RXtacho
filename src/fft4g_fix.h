/*
 * fft4g_fix.h
 *
 *  Created on: 2018/12/29
 *      Author: akihiro
 */

#ifndef __FFT4G_FIX_H__
#define __FFT4G_FIX_H__


#include "fix_math.h"

void cdft_fix(int n, int isgn, FIX_T *a, int *ip, FIX_T *w);
void rdft_fix(int n, int isgn, FIX_T *a, int *ip, FIX_T *w);
void ddct_fix(int n, int isgn, FIX_T *a, int *ip, FIX_T *w);
void ddst_fix(int n, int isgn, FIX_T *a, int *ip, FIX_T *w);
void dfct_fix(int n, FIX_T *a, FIX_T *t, int *ip, FIX_T *w);
void dfst_fix(int n, FIX_T *a, FIX_T *t, int *ip, FIX_T *w);



#endif // __FFT4G_FIX_H__