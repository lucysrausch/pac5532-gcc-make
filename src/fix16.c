/**************************************************************************
 * Copyright (c) the authors of libfixmath as seen on https://code.google.com/p/libfixmath/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ***************************************************************************/

#include "fix16.h"

#define FIXMATH_NO_64BIT
#define FIXMATH_OPTIMIZE_8BIT

/* Subtraction and addition with overflow detection.
 * The versions without overflow detection are inlined in the header.
 */
#ifndef FIXMATH_NO_OVERFLOW
FIX16_RAMFUNC fix16_t fix16_add(fix16_t a, fix16_t b)
{
  // Use unsigned integers because overflow with signed integers is
  // an undefined operation (http://www.airs.com/blog/archives/120).
  uint32_t _a = a, _b = b;
  uint32_t sum = _a + _b;

  // Overflow can only happen if sign of a == sign of b, and then
  // it causes sign of sum != sign of a.
  if (!((_a ^ _b) & 0x80000000) && ((_a ^ sum) & 0x80000000))
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	// Return proper saturated value
	return (a > 0) ? fix16_max : fix16_min;
#endif
  }

  return sum;
}

FIX16_RAMFUNC fix16_t fix16_sub(fix16_t a, fix16_t b)
{
  uint32_t _a = a, _b = b;
  uint32_t diff = _a - _b;

  // Overflow can only happen if sign of a != sign of b, and then
  // it causes sign of diff != sign of a.
  if (((_a ^ _b) & 0x80000000) && ((_a ^ diff) & 0x80000000))
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	// Return proper saturated value
	return (a > 0) ? fix16_max : fix16_min;
#endif
  }
  
  return diff;
}

/* Saturating arithmetic */
FIX16_RAMFUNC fix16_t fix16_sadd(fix16_t a, fix16_t b)
{
  fix16_t result = fix16_add(a, b);

  if (result == fix16_overflow)
    return (a > 0) ? fix16_max : fix16_min;

  return result;
}  

FIX16_RAMFUNC fix16_t fix16_ssub(fix16_t a, fix16_t b)
{
  fix16_t result = fix16_sub(a, b);

  if (result == fix16_overflow)
    return (a > 0) ? fix16_max : fix16_min;

  return result;
}
#endif



/* 64-bit implementation for fix16_mul. Fastest version for e.g. ARM Cortex M3.
 * Performs a 32*32 -> 64bit multiplication. The middle 32 bits are the result,
 * bottom 16 bits are used for rounding, and upper 16 bits are used for overflow
 * detection.
 */
 
#if !defined(FIXMATH_NO_64BIT) && !defined(FIXMATH_OPTIMIZE_8BIT)
FIX16_RAMFUNC fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1)
{
  int64_t product = (int64_t)inArg0 * inArg1;
  
  #ifndef FIXMATH_NO_OVERFLOW
  // The upper 17 bits should all be the same (the sign).
  uint32_t upper = (product >> 47);
  #endif
  
  if (product < 0)
  {
    #ifndef FIXMATH_NO_OVERFLOW
    if (~upper)
        return fix16_overflow;
    #endif
    
    #ifndef FIXMATH_NO_ROUNDING
    // This adjustment is required in order to round -1/2 correctly
    product--;
    #endif
  }
  else
  {
    #ifndef FIXMATH_NO_OVERFLOW
    if (upper)
        return fix16_overflow;
    #endif
  }
  
  #ifdef FIXMATH_NO_ROUNDING
  return product >> 16;
  #else
  fix16_t result = product >> 16;
  result += (product & 0x8000) >> 15;
  
  return result;
  #endif
}
#endif

/* 32-bit implementation of fix16_mul. Potentially fast on 16-bit processors,
 * and this is a relatively good compromise for compilers that do not support
 * uint64_t. Uses 16*16->32bit multiplications.
 */
#if defined(FIXMATH_NO_64BIT) && !defined(FIXMATH_OPTIMIZE_8BIT)
FIX16_RAMFUNC fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1)
{
  // Each argument is divided to 16-bit parts.
  //          AB
  //      *   CD
  // -----------
  //          BD  16 * 16 -> 32 bit products
  //         CB
  //         AD
  //        AC
  //       |----| 64 bit product
  int32_t A = (inArg0 >> 16), C = (inArg1 >> 16);
  uint32_t B = (inArg0 & 0xFFFF), D = (inArg1 & 0xFFFF);
  
  int32_t AC = A*C;
  int32_t AD_CB = A*D + C*B;
  uint32_t BD = B*D;
  
  int32_t product_hi = AC + (AD_CB >> 16);
  
  // Handle carry from lower 32 bits to upper part of result.
  uint32_t ad_cb_temp = AD_CB << 16;
  uint32_t product_lo = BD + ad_cb_temp;
  if (product_lo < BD)
    product_hi++;
  
#ifndef FIXMATH_NO_OVERFLOW
  // The upper 17 bits should all be the same (the sign).
  if (product_hi >> 31 != product_hi >> 15)
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif

#endif
  
#ifdef FIXMATH_NO_ROUNDING
  return (product_hi << 16) | (product_lo >> 16);
#else
  // Subtracting 0x8000 (= 0.5) and then using signed right shift
  // achieves proper rounding to result-1, except in the corner
  // case of negative numbers and lowest word = 0x8000.
  // To handle that, we also have to subtract 1 for negative numbers.
  uint32_t product_lo_tmp = product_lo;
  product_lo -= 0x8000;
  product_lo -= (uint32_t)product_hi >> 31;
  if (product_lo > product_lo_tmp)
    product_hi--;
  
  // Discard the lowest 16 bits. Note that this is not exactly the same
  // as dividing by 0x10000. For example if product = -1, result will
  // also be -1 and not 0. This is compensated by adding +1 to the result
  // and compensating this in turn in the rounding above.
  fix16_t result = (product_hi << 16) | (product_lo >> 16);
  result += 1;
  return result;
#endif
}
#endif

FIX16_RAMFUNC fix16_t fix16_mul_new_16_16(fix16_t inArg0, fix16_t inArg1)
{
  // Each argument is divided to 16-bit parts.
  // AB
  // * CD
  // -----------
  // BD 16 * 16 -> 32 bit products
  // CB
  // AD
  // AC
  // |----| 64 bit product
  int32_t A = (inArg0 >> 16), C = (inArg1 >> 16);
  uint32_t B = (inArg0 & 0xFFFF), D = (inArg1 & 0xFFFF);

  int32_t AC = A*C;
  int32_t AD_CB = A*D + C*B;
  uint32_t BD = B*D;

  int32_t product_hi = AC + (AD_CB >> 16);

  // Handle carry from lower 32 bits to upper part of result.
  uint32_t ad_cb_temp = AD_CB << 16;
  uint32_t product_lo = BD + ad_cb_temp;
  if (product_lo < BD)
    product_hi++;

#ifndef FIXMATH_NO_OVERFLOW
  // The upper 17 bits should all be the same (the sign).
  if (product_hi >> 31 != product_hi >> 15)
    return fix16_overflow;
#endif

#ifdef FIXMATH_NO_ROUNDING
  return (product_hi << 16) | (product_lo >> 16);
#else
  // Subtracting 0x8000 (= 0.5) and then using signed right shift
  // achieves proper rounding to result-1, except in the corner
  // case of negative numbers and lowest word = 0x8000.
  // To handle that, we also have to subtract 1 for negative numbers.
  uint32_t product_lo_tmp = product_lo;
  product_lo -= 0x8000;
  product_lo -= (uint32_t)product_hi >> 31;
  if (product_lo > product_lo_tmp)
    product_hi--;

  // Discard the lowest 16 bits. Note that this is not exactly the same
  // as dividing by 0x10000. For example if product = -1, result will
  // also be -1 and not 0. This is compensated by adding +1 to the result
  // and compensating this in turn in the rounding above.
  fix16_t result = (product_hi << 16) | (product_lo >> 16);
  result += 1;
  return result;
#endif
}

FIX16_RAMFUNC fix16_t mul_i32_i32_new(fix16_t x, fix16_t y)
{
	fix16_t flag1 = 0;
	fix16_t flag2 = 0;
	fix16_t result = 0;
	int16_t hi[2];
	uint16_t lo[2];
	fix16_t r_hi;
	fix16_t r_md;
	uint32_t r_lo;
	fix16_t x1, y1;


//	if ((x == 0) || (y == 0))                     /*!< if any number zero then return result zero */
//		return result;

	x1 = x;
	y1 = y;

	if (x1 < 0)
	{
		x1  = 0 - x1;                               /*!< if negative number convert into positive number */
		flag1 = 1;
	}
	if (y1 < 0)
	{
		y1 = 0 - y1;                                /*!< if negative number convert into positive number */
		flag2 = 1;
	}

	hi[0] = (x1 >> 16);
	hi[1] = (y1 >> 16);

	lo[0] = (x1 & 0xFFFF);
	lo[1] = (y1 & 0xFFFF);

	r_hi = hi[0] * hi[1];
	r_md = (hi[0] * lo[1]) + (hi[1] * lo[0]);
	r_lo = lo[0] * lo[1];

	r_hi += (r_md >> 16);
	r_lo += (r_md << 16);

    if ((r_hi != 0) || (r_lo > 2147483647))      /*!< if its more then max limit or less then minimum limit return max limit or minimum limit */
    {
#if 0
    	if (flag1 ^ flag2)
            result = -2147483647;
        else
        	result = 2147483647;
#endif
        if ((flag1) && (flag2))
            result = 2147483647;
        else if ((flag1) && (!flag2))
        	result = -2147483647;
        else if ((!flag1) && (flag2))
        	result = -2147483647;
        else
        	result = 2147483647;
    }
    else
    {
#if 0
    	if ( flag1 ^ flag2)                     /*!< if only one number was negative then return negative number */
            result = 0 - r_lo;
        else
    	    result = (int32_t) r_lo;            /*!< return positive result */
#endif
        if (((flag1) && (!flag2)) || ((!flag1) && (flag2)))
            result = (fix16_t) 0 - r_lo;
        else
    	    result = (fix16_t) r_lo;
    }
    return (fix16_t) (result >> 8);
}


/* 8-bit implementation of fix16_mul. Fastest on e.g. Atmel AVR.
 * Uses 8*8->16bit multiplications, and also skips any bytes that
 * are zero.
 */
#if defined(FIXMATH_OPTIMIZE_8BIT)
FIX16_RAMFUNC fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1)
{
  uint32_t _a = (inArg0 >= 0) ? inArg0 : (-inArg0);
  uint32_t _b = (inArg1 >= 0) ? inArg1 : (-inArg1);
  
  uint8_t va[4] = {_a, (_a >> 8), (_a >> 16), (_a >> 24)};
  uint8_t vb[4] = {_b, (_b >> 8), (_b >> 16), (_b >> 24)};
  
  uint32_t low = 0;
  uint32_t mid = 0;
  
  // Result column i depends on va[0..i] and vb[i..0]

  #ifndef FIXMATH_NO_OVERFLOW
  // i = 6
  if (va[3] && vb[3])
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
  }

  #endif
  
  // i = 5
  if (va[2] && vb[3]) mid += (uint16_t)va[2] * vb[3];
  if (va[3] && vb[2]) mid += (uint16_t)va[3] * vb[2];
  mid <<= 8;
  
  // i = 4
  if (va[1] && vb[3]) mid += (uint16_t)va[1] * vb[3];
  if (va[2] && vb[2]) mid += (uint16_t)va[2] * vb[2];
  if (va[3] && vb[1]) mid += (uint16_t)va[3] * vb[1];
  
  #ifndef FIXMATH_NO_OVERFLOW
  if (mid & 0xFF000000)
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
  }
  #endif
  mid <<= 8;
  
  // i = 3
  if (va[0] && vb[3]) mid += (uint16_t)va[0] * vb[3];
  if (va[1] && vb[2]) mid += (uint16_t)va[1] * vb[2];
  if (va[2] && vb[1]) mid += (uint16_t)va[2] * vb[1];
  if (va[3] && vb[0]) mid += (uint16_t)va[3] * vb[0];
  
  #ifndef FIXMATH_NO_OVERFLOW
  if (mid & 0xFF000000)
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
  }
  #endif
  mid <<= 8;
  
  // i = 2
  if (va[0] && vb[2]) mid += (uint16_t)va[0] * vb[2];
  if (va[1] && vb[1]) mid += (uint16_t)va[1] * vb[1];
  if (va[2] && vb[0]) mid += (uint16_t)va[2] * vb[0];    
  
  // i = 1
  if (va[0] && vb[1]) low += (uint16_t)va[0] * vb[1];
  if (va[1] && vb[0]) low += (uint16_t)va[1] * vb[0];
  low <<= 8;
  
  // i = 0
  if (va[0] && vb[0]) low += (uint16_t)va[0] * vb[0];
  
  #ifndef FIXMATH_NO_ROUNDING
  low += 0x8000;
  #endif
  mid += (low >> 16);
  
  #ifndef FIXMATH_NO_OVERFLOW
  if (mid & 0x80000000)
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
  }
  #endif
  
  fix16_t result = mid;
  
  /* Figure out the sign of result */
  if ((inArg0 >= 0) != (inArg1 >= 0))
  {
    result = -result;
  }
  
  return result;
}
#endif

#ifndef FIXMATH_NO_OVERFLOW
/* Wrapper around fix16_mul to add saturating arithmetic. */
FIX16_RAMFUNC fix16_t fix16_smul(fix16_t inArg0, fix16_t inArg1) {
  fix16_t result = fix16_mul(inArg0, inArg1);
  
  if (result == fix16_overflow)
  {
    if ((inArg0 >= 0) == (inArg1 >= 0))
      return fix16_max;
    else
      return fix16_min;
  }
  
  return result;
}
#endif

/* 32-bit implementation of fix16_div. Fastest version for e.g. ARM Cortex M3.
 * Performs 32-bit divisions repeatedly to reduce the remainder. For this to
 * be efficient, the processor has to have 32-bit hardware division.
 */
#if !defined(FIXMATH_OPTIMIZE_8BIT)
#ifdef __GNUC__
// Count leading zeros, using processor-specific instruction if available.
#define clz(x) __builtin_clzl(x)
#else
FIX16_RAMFUNC static uint8_t clz(uint32_t x)
{
  uint8_t result = 0;
  if (x == 0) return 32;
  while (!(x & 0xF0000000)) { result += 4; x <<= 4; }
  while (!(x & 0x80000000)) { result += 1; x <<= 1; }
  return result;
}
#endif

FIX16_RAMFUNC fix16_t fix16_div(fix16_t a, fix16_t b)
{
  // This uses a hardware 32/32 bit division multiple times, until we have
  // computed all the bits in (a<<17)/b. Usually this takes 1-3 iterations.
  
  if (b == 0)
      return fix16_min;
  
  uint32_t remainder = (a >= 0) ? a : (-a);
  uint32_t divider = (b >= 0) ? b : (-b);
  uint32_t quotient = 0;
  int bit_pos = 17;
  
  // Kick-start the division a bit.
  // This improves speed in the worst-case scenarios where N and D are large
  // It gets a lower estimate for the result by N/(D >> 17 + 1).
  if (divider & 0xFFF00000)
  {
    uint32_t shifted_div = ((divider >> 17) + 1);
    quotient = remainder / shifted_div;
    remainder -= ((uint64_t)quotient * divider) >> 17;
  }
  
  // If the divider is divisible by 2^n, take advantage of it.
  while (!(divider & 0xF) && bit_pos >= 4)
  {
    divider >>= 4;
    bit_pos -= 4;
  }
  
  while (remainder && bit_pos >= 0)
  {
    // Shift remainder as much as we can without overflowing
    int shift = clz(remainder);
    if (shift > bit_pos) shift = bit_pos;
    remainder <<= shift;
    bit_pos -= shift;
    
    uint32_t div = remainder / divider;
    remainder = remainder % divider;
    quotient += div << bit_pos;

    #ifndef FIXMATH_NO_OVERFLOW
    if (div & ~(0xFFFFFFFF >> bit_pos))
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif

#endif
    
    remainder <<= 1;
    bit_pos--;
  }
  
  #ifndef FIXMATH_NO_ROUNDING
  // Quotient is always positive so rounding is easy
  quotient++;
  #endif
  
  fix16_t result = quotient >> 1;
  
  // Figure out the sign of the result
  if ((a ^ b) & 0x80000000)
  {
    #ifndef FIXMATH_NO_OVERFLOW
    if (result == fix16_min)
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((inArg0 >= 0) == (inArg1 >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif

#endif
    
    result = -result;
  }
  
  return result;
}
#endif

/* Alternative 32-bit implementation of fix16_div. Fastest on e.g. Atmel AVR.
 * This does the division manually, and is therefore good for processors that
 * do not have hardware division.
 */
#if defined(FIXMATH_OPTIMIZE_8BIT)
FIX16_RAMFUNC fix16_t fix16_div(fix16_t a, fix16_t b)
{
  // This uses the basic binary restoring division algorithm.
  // It appears to be faster to do the whole division manually than
  // trying to compose a 64-bit divide out of 32-bit divisions on
  // platforms without hardware divide.
  
  if (b == 0)
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((a >= 0) == (b >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
  }
  
  uint32_t remainder = (a >= 0) ? a : (-a);
  uint32_t divider = (b >= 0) ? b : (-b);

  uint32_t quotient = 0;
  uint32_t bit = 0x10000;
  
  /* The algorithm requires D >= R */
  while (divider < remainder)
  {
    divider <<= 1;
    bit <<= 1;
  }
  
  #ifndef FIXMATH_NO_OVERFLOW
  if (!bit)
  {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((a >= 0) == (b >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
  }
  #endif
  
  if (divider & 0x80000000)
  {
    // Perform one step manually to avoid overflows later.
    // We know that divider's bottom bit is 0 here.
    if (remainder >= divider)
    {
        quotient |= bit;
        remainder -= divider;
    }
    divider >>= 1;
    bit >>= 1;
  }
  
  /* Main division loop */
  while (bit && remainder)
  {
    if (remainder >= divider)
    {
        quotient |= bit;
        remainder -= divider;
    }
    
    remainder <<= 1;
    bit >>= 1;
  }   
      
  #ifndef FIXMATH_NO_ROUNDING
  if (remainder >= divider)
  {
    quotient++;
  }
  #endif
  
  fix16_t result = quotient;
  
  /* Figure out the sign of result */
  if ((a ^ b) & 0x80000000)
  {
    #ifndef FIXMATH_NO_OVERFLOW
    if (result == fix16_min)
    {
#ifdef FIX16_OVERFLOW_DETECT
	fault_mask |= FAULT_FIX16_OVERFLOW;
	fault(0);
	return fix16_overflow;
#else
	if ((a >= 0) == (b >= 0))
		return fix16_max;
	else
		return fix16_min;
#endif
    }
    #endif
    
    result = -result;
  }
  
  return result;
}
#endif

#ifndef FIXMATH_NO_OVERFLOW
/* Wrapper around fix16_div to add saturating arithmetic. */
FIX16_RAMFUNC fix16_t fix16_sdiv(fix16_t inArg0, fix16_t inArg1) {
  fix16_t result = fix16_div(inArg0, inArg1);
  
  if (result == fix16_overflow)
  {
    if ((inArg0 >= 0) == (inArg1 >= 0))
      return fix16_max;
    else
      return fix16_min;
  }
  
  return result;
}
#endif
