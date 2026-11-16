/*
 * Minimal fdlibm.h for building the Sun fdlibm 5.3 sources in this
 * directory (taken from GNU Classpath's native/fdlibm copy) with vbcc for
 * ppc-amigaos.  They replace the LIBMOTO objects atan.emb.o (atan, atan2),
 * pow.emb.o (pow, exp, log, log10), trig.emb.o (sin, cos) and sqrt.emb.o
 * (sqrt), which may only be redistributed as object code.
 *
 * The fdlibm sources carry this notice:
 *
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 */
#ifndef FDLIBM_H
#define FDLIBM_H

#include <math.h>

typedef int int32_t;
typedef unsigned int uint32_t;

#define __P(p) p

/* PowerPC is big endian */
typedef union
{
  double value;
  struct
  {
    uint32_t msw;
    uint32_t lsw;
  } parts;
} ieee_double_shape_type;

#define EXTRACT_WORDS(ix0,ix1,d)	\
  do {					\
    ieee_double_shape_type ew_u;	\
    ew_u.value = (d);			\
    (ix0) = ew_u.parts.msw;		\
    (ix1) = ew_u.parts.lsw;		\
  } while (0)

#define GET_HIGH_WORD(i,d)		\
  do {					\
    ieee_double_shape_type gh_u;	\
    gh_u.value = (d);			\
    (i) = gh_u.parts.msw;		\
  } while (0)

#define GET_LOW_WORD(i,d)		\
  do {					\
    ieee_double_shape_type gl_u;	\
    gl_u.value = (d);			\
    (i) = gl_u.parts.lsw;		\
  } while (0)

#define INSERT_WORDS(d,ix0,ix1)		\
  do {					\
    ieee_double_shape_type iw_u;	\
    iw_u.parts.msw = (ix0);		\
    iw_u.parts.lsw = (ix1);		\
    (d) = iw_u.value;			\
  } while (0)

#define SET_HIGH_WORD(d,v)		\
  do {					\
    ieee_double_shape_type sh_u;	\
    sh_u.value = (d);			\
    sh_u.parts.msw = (v);		\
    (d) = sh_u.value;			\
  } while (0)

#define SET_LOW_WORD(d,v)		\
  do {					\
    ieee_double_shape_type sl_u;	\
    sl_u.value = (d);			\
    sl_u.parts.lsw = (v);		\
    (d) = sl_u.value;			\
  } while (0)

/* helpers, not in <math.h> */
extern double copysign(double, double);
extern double scalbn(double, int);

/* ieee style elementary functions, wrapped by w_*.c */
extern double __ieee754_sqrt(double);
extern double __ieee754_log(double);
extern double __ieee754_atan2(double,double);
extern double __ieee754_exp(double);
extern double __ieee754_pow(double,double);
extern double __ieee754_log10(double);
extern int32_t __ieee754_rem_pio2(double,double*);

/* vbcc works out a division by a constant zero, and x-x, at compile time
   and gives 0 for it, so where fdlibm divides by zero to make an infinity
   or a NaN, it divides by this instead.  */
static volatile double vzero = 0.0;

/* fdlibm kernel functions */
extern double __kernel_sin(double,double,int);
extern double __kernel_cos(double,double);
extern int __kernel_rem_pio2(double*,double*,int,int,int,const int*);

#endif
