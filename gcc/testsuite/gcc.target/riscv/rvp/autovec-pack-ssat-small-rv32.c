/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include <stdint.h>

/* The four-byte vector path packs two PV2HI inputs, rather than the two
   eight-byte sources used by vec_pack_ssat_pv4hi.  */
void __attribute__ ((noipa))
pack_four (int8_t *restrict dst, const int16_t *restrict src)
{
  dst = __builtin_assume_aligned (dst, 8);
  src = __builtin_assume_aligned (src, 8);
  for (unsigned int i = 0; i < 4; ++i)
    {
      int value = src[i];
      if (value < -128)
	value = -128;
      if (value > 127)
	value = 127;
      dst[i] = value;
    }
}

/* { dg-final { scan-tree-dump "vect_recog_promoted_sat_trunc_clamp" "vect" } } */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 1 "vect" } } */
/* { dg-final { scan-assembler-times {\mpnclipi\.b\M} 1 } } */
/* { dg-final { scan-assembler-not {\mpnclipp\.[bh]\M} } } */
