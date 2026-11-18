/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -ftree-vectorize -fdump-tree-optimized" } */

#include <stdint.h>

/* Keep the modulo-16-bit subtraction for both the raw result and the
   selected low byte.  Recognizing a separate full-width SAT_SUB duplicates
   arithmetic instead of reusing the live narrow result.  */
void
vec_sat_u_sub_trunc_shared (uint8_t *__restrict dst,
			    uint16_t *__restrict raw,
			    _Bool *__restrict flag,
			    const uint32_t *__restrict x,
			    const uint32_t *__restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint32_t a = x[i];
      uint32_t b = y[i];
      uint16_t d = (uint16_t) a - (uint16_t) b;
      _Bool c = a >= b;
      dst[i] = c ? (uint8_t) d : 0;
      raw[i] = d;
      flag[i] = c;
    }
}

/* { dg-final { scan-tree-dump-not {\.SAT_SUB } "optimized" } } */
/* { dg-final { scan-assembler-not {vssubu\.} } } */
