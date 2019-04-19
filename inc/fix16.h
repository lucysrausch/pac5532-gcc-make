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

#ifndef __libfixmath_fix16_h__
#define __libfixmath_fix16_h__

/* These options may let the optimizer to remove some calls to the functions.
 * Refer to http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
 */
#ifndef FIXMATH_FUNC_ATTRS
# ifdef __GNUC__
#   define FIXMATH_FUNC_ATTRS __attribute__((leaf, nothrow, pure))
# else
#   define FIXMATH_FUNC_ATTRS
# endif
#endif

#define RAMFUNC_LINK

#ifdef RAMFUNC_LINK
#define FIX16_RAMFUNC PAC5XXX_RAMFUNC
#else
#define FIX16_RAMFUNC
#endif

#include <stdint.h>

#include "pac5xxx.h"

#define FIXMATH_NO_OVERFLOW
#define FIXMATH_NO_ROUNDING

typedef int32_t fix16_t;

#define FOUR_DIV_PI  				0x145F3           	/*!< Fix16 value of 4/PI */
#define _FOUR_DIV_PI2				0xFFFF9840       	/*!< Fix16 value of -4/PI² */
#define X4_CORRECTION_COMPONENT		0x399A 				/*!< Fix16 value of 0.225 */
#define PI_DIV_4					0x0000C90F          /*!< Fix16 value of PI/4 */
#define THREE_PI_DIV_4				0x00025B2F      	/*!< Fix16 value of 3PI/4 */

#define fix16_max					0x7FFFFFFF 			/*!< the maximum value of fix16_t */
#define fix16_min					0x80000000 			/*!< the minimum value of fix16_t */
#define fix16_overflow				0x80000000 			/*!< the value used to indicate overflows when FIXMATH_NO_OVERFLOW is not specified */

#define fix16_pi					205887     			/*!< fix16_t value of pi */
#define fix16_e						78145     			/*!< fix16_t value of e */
#define fix16_one					0x00010000 			/*!< fix16_t value of 1 */
#define fix16_neg_one				0xFFFF0000			/*!< fix16_t value of -1 */


/* Subtraction and addition with (optional) overflow detection. */
#ifdef FIXMATH_NO_OVERFLOW

FIX16_RAMFUNC static inline  fix16_t fix16_add(fix16_t inArg0, fix16_t inArg1) { return (inArg0 + inArg1); }
FIX16_RAMFUNC static inline PAC5XXX_RAMFUNC fix16_t fix16_sub(fix16_t inArg0, fix16_t inArg1) { return (inArg0 - inArg1); }

#else

extern FIX16_RAMFUNC fix16_t fix16_add(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;
extern FIX16_RAMFUNC fix16_t fix16_sub(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;

/* Saturating arithmetic */
extern FIX16_RAMFUNC fix16_t fix16_sadd(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;
extern FIX16_RAMFUNC fix16_t fix16_ssub(fix16_t a, fix16_t b) FIXMATH_FUNC_ATTRS;

#endif

/*! Multiplies the two given fix16_t's and returns the result.
*/
extern FIX16_RAMFUNC  fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;

/*! Divides the first given fix16_t by the second and returns the result.
*/
extern FIX16_RAMFUNC  fix16_t fix16_div(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;

extern FIX16_RAMFUNC fix16_t fix16_mul_new_16_16(fix16_t inArg0, fix16_t inArg1) FIXMATH_FUNC_ATTRS;
#endif
