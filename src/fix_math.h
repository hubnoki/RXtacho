/*
 * fix_math.h
 *
 *  Created on: 2018/11/25
 *      Author: akihiro
 */

#ifndef FIX_MATH_H_
#define FIX_MATH_H_

#include <stdint.h>

//------------------------------------------------------
// fix point data type
#define FIX_T 		int
// decimal point
#define FIX_P		16

//------------------------------------------------------
// Definitions for internal use
#define FIX_UNIT (((FIX_T)1) << FIX_P)
#define FIX_INT_MASK (~(0xFFFFFFFFU << FIX_P))

//------------------------------------------------------

static inline FIX_T fix_int2fix(int d){
	return (FIX_T)(d << FIX_P);
}

static inline FIX_T fix_fl2fix(float d)
{
	return (FIX_T)(d * FIX_UNIT);
}

static inline FIX_T fix_dbl2fix(double d)
{
	return (FIX_T)(d * FIX_UNIT);
}

static inline int fix_fix2int(FIX_T d){
	return d >> FIX_P;
}

static inline double fix_fix2dbl(FIX_T d){
	return ((double)d) / FIX_UNIT;
}

/**
 *
 * @param op1		Operand 1 (FIX_T type)
 * @param op2		Operand 2 (FIX_T type)
 * @return			FIX_T value of (op1 * op2)
 */
static inline FIX_T fix_mul(FIX_T op1, FIX_T op2){
	return (FIX_T)((((uint64_t)op1) * op2) >> FIX_P);
}

static inline FIX_T fix_abs(FIX_T f){
	return (f & (0x1 << 31)) ? -f : f;
}

/**
 *
 * @param f		Input value
 * @param dp	Digits of fractional number
 * @return		Fractional number in decimal format
 */
static inline int fix_frac_dec(FIX_T f, int dp){
	unsigned int dec_mul = 1;
	int i;

	for(i = 0; i < dp; i++)
		dec_mul *= 10;

	f = fix_abs(f) & FIX_INT_MASK;
	return (f * dec_mul) >> FIX_P;
}

#endif /* FIX_MATH_H_ */
