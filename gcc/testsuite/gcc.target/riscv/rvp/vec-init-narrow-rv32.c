/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fvect-cost-model=unlimited" } */

typedef unsigned char v8qi __attribute__ ((vector_size (8)));

unsigned long long
narrow_words (unsigned int a, unsigned int b, unsigned int c, unsigned int d,
	      unsigned int e, unsigned int f, unsigned int g, unsigned int h)
{
  union { v8qi lanes; unsigned long long raw; } value = {
    .lanes = { a, b, c, d, e, f, g, h }
  };
  return value.raw;
}

/* { dg-final { scan-assembler-times {\tpncvt\.h\t} 4 } } */
/* { dg-final { scan-assembler-times {\tpncvt\.b\t} 2 } } */
/* { dg-final { scan-assembler-not {\(sp\)} } } */
