/* { dg-do run } */
/* { dg-options "-O3" } */

#include "packed-logic-imm-negative.h"

int __attribute__ ((optimize ("O0")))
main (void)
{
  unsigned int state = 1;
  for (unsigned int i = 0; i < 256; ++i)
    {
      state = state * 1664525u + 1013904223u;
      v4qi a = { state, state >> 8, state >> 16, state >> 24 };
      v2hi b = { state, state >> 16 };
      v2si c = { state, ~state };
      v4hi d = { state, state >> 16, ~state, ~state >> 16 };
      v8qi e = { a[0], a[1], a[2], a[3],
		 (unsigned char) ~a[0], (unsigned char) ~a[1],
		 (unsigned char) ~a[2], (unsigned char) ~a[3] };
      v4qi aa = and_bytes (a), ax = xor_bytes (a);
      v2hi bo = or_halfwords (b);
      v2si ca = and_words (c);
      v4hi dor = or_wide_halfwords (d);
      v8qi ex = xor_wide_bytes (e);
      v4qi an = nonimmediate_bytes (a);
      v2hi bn = nonimmediate_halfwords (b);
      v2si cn = nonimmediate_words (c);
      const unsigned char ma[] = { 127, 0, 0, 0 };
      const unsigned char mx[] = { 128, 255, 255, 255 };
      const unsigned short mb[] = { 2047, 0 };
#if __riscv_xlen == 32
      const unsigned int mc[] = { -2048u, 2047 };
      const unsigned short md[] = { 127, 0, 15, 0 };
      const unsigned char me[] = { 128, 255, 255, 255, 16, 0, 0, 0 };
#else
      const unsigned int mc[] = { 2047, 0 };
      const unsigned short md[] = { 63488, 65535, 65535, 65535 };
      const unsigned char me[] = { 128, 255, 255, 255, 255, 255, 255, 255 };
#endif
      for (unsigned int j = 0; j < 4; ++j)
	if (aa[j] != (a[j] & ma[j])
	    || ax[j] != (unsigned char) (a[j] ^ mx[j])
	    || dor[j] != (unsigned short) (d[j] | md[j])
	    || an[j] != (a[j] & 127))
	  __builtin_abort ();
      for (unsigned int j = 0; j < 2; ++j)
	if (bo[j] != (unsigned short) (b[j] | mb[j])
	    || ca[j] != (c[j] & mc[j])
	    || bn[j] != (unsigned short) (b[j] | 127)
	    || cn[j] != (c[j] ^ (j ? -2049u : 2048)))
	  __builtin_abort ();
      for (unsigned int j = 0; j < 8; ++j)
	if (ex[j] != (unsigned char) (e[j] ^ me[j]))
	  __builtin_abort ();
    }
  return 0;
}
