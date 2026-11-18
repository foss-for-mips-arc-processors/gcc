/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -mlittle-endian -O3" } */

#include <stdint.h>

/* The four-element epilogue must not keep an undefined register pair
   live across the main loop.  The bound is not a saturating byte pack.  */
void __attribute__ ((noipa))
pack_near (uint8_t *restrict dst, uint16_t *restrict unused,
	   const uint16_t *restrict src, unsigned int n)
{
  dst = __builtin_assume_aligned (dst, 8);
  src = __builtin_assume_aligned (src, 8);
  for (unsigned int i = 0; i < n; ++i)
    {
      uint16_t value = src[i];
      if (value > 254)
	value = 254;
      dst[i] = value;
    }
}

/* { dg-final { scan-assembler-times {\mpncvt\.b\M} 3 } } */
/* { dg-final { scan-assembler-not {\mpnclipiu\.b\M} } } */
/* { dg-final { scan-assembler-not {\(sp\)} } } */
