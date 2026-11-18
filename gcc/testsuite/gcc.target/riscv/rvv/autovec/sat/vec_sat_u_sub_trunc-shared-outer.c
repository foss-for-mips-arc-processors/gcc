/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -ftree-vectorize -fdump-tree-optimized" } */

#include <stdint.h>

/* The subtraction has one use, but its narrowing conversion is shared.
   Keep the low byte available for both the raw and selected stores.  */
void
vec_sat_u_sub_trunc_shared_outer (uint8_t *__restrict selected,
				  uint8_t *__restrict raw,
				  const uint32_t *__restrict x,
				  const uint32_t *__restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint32_t a = x[i];
      uint32_t b = y[i];
      uint16_t d = (uint16_t) a - (uint16_t) b;
      uint8_t low = (uint8_t) d;
      raw[i] = low;
      selected[i] = a >= b ? low : 0;
    }
}

/* { dg-final { scan-tree-dump-not {\.SAT_SUB } "optimized" } } */
/* { dg-final { scan-assembler-not {vssubu\.} } } */
