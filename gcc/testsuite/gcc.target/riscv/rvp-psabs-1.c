/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2 -ftree-vectorize" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Oz" "-Og" "-flto" "-funroll-loops" "-fpeel-loops" } } */

typedef signed char int8_t;
typedef short int16_t;

/* Test psabs.b via loop vectorization for 4 bytes */
void test_psabs_b (int8_t *dst, int8_t *src)
{
  for (int i = 0; i < 4; i++)
    dst[i] = src[i] < 0 ? -src[i] : src[i];
}

/* Test psabs.h via loop vectorization for 2 halfwords */
void test_psabs_h (int16_t *dst, int16_t *src)
{
  for (int i = 0; i < 2; i++)
    dst[i] = src[i] < 0 ? -src[i] : src[i];
}

/* Test scalar QI abs */
int8_t test_abs_qi (int8_t a)
{
  return a < 0 ? -a : a;
}

/* Test scalar HI abs */
int16_t test_abs_hi (int16_t a)
{
  return a < 0 ? -a : a;
}

/* { dg-final { scan-assembler-times "psabs\\.b" 2 } } */
/* { dg-final { scan-assembler-times "psabs\\.h" 3 } } */
