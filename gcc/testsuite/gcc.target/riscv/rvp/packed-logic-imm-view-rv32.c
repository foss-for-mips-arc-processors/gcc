/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-rtl-split1" } */

typedef unsigned int v2si __attribute__ ((vector_size (8)));

/* The original scalar pair remains live after masking.  Expose its words
   before allocation instead of requiring a second complete packed pair.  */
void
masked_and_original (unsigned int *out, const unsigned int *in,
		     unsigned int n)
{
  for (unsigned int i = 0; i < n; i += 2)
    {
      v2si value;
      __builtin_memcpy (&value, in + i, sizeof (value));
      v2si masked = value & (v2si) { 2047, -2048u };
      __builtin_memcpy (out + 2 * i, &masked, sizeof (masked));
      __builtin_memcpy (out + 2 * i + 2, &value, sizeof (value));
    }
}

/* { dg-final { scan-rtl-dump-not {and:PV2SI} "split1" } } */
/* { dg-final { scan-assembler-times {\mandi\M} 2 } } */
