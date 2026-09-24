/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" } } */

typedef unsigned char v4qi __attribute__ ((vector_size (4)));

v4qi
zip_lo (v4qi a, v4qi b)
{
  return __builtin_shufflevector (a, b, 0, 4, 1, 5);
}

v4qi
zip_hi (v4qi a, v4qi b)
{
  return __builtin_shufflevector (a, b, 2, 6, 3, 7);
}

v4qi
unzip_lo (v4qi a, v4qi b)
{
  return __builtin_shufflevector (a, b, 0, 2, 4, 6);
}

v4qi
unzip_hi (v4qi a, v4qi b)
{
  return __builtin_shufflevector (a, b, 1, 3, 5, 7);
}

/* { dg-final { scan-assembler-times {\mzip8p\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpncvt\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpncvth\.b\M} 1 } } */
