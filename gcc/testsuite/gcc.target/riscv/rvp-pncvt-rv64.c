/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

typedef signed char int8x4_t  __attribute__((vector_size(4)));
typedef short       int16x4_t __attribute__((vector_size(8)));
typedef short       int16x2_t __attribute__((vector_size(4)));
typedef int         int32x2_t __attribute__((vector_size(8)));

int8x4_t
trunc_b (int16x4_t a)
{
  return __builtin_convertvector (a, int8x4_t);
}

int16x2_t
trunc_h (int32x2_t a)
{
  return __builtin_convertvector (a, int16x2_t);
}

/* { dg-final { scan-assembler-times {\mpncvt\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpncvt\.h\M} 1 } } */
