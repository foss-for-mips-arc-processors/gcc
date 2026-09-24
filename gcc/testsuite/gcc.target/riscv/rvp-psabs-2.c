/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -ftree-vectorize" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Oz" "-Og" "-flto" "-funroll-loops" "-fpeel-loops" } } */

typedef signed char int8_t;
typedef short int16_t;

/* Test psabs.b via loop vectorization for 4 bytes */
void test_psabs_b_v4 (int8_t *dst, int8_t *src)
{
  for (int i = 0; i < 4; i++)
    dst[i] = src[i] < 0 ? -src[i] : src[i];
}

/* Test psabs.b via loop vectorization for 8 bytes (RV64) */
void test_psabs_b_v8 (int8_t *dst, int8_t *src)
{
  for (int i = 0; i < 8; i++)
    dst[i] = src[i] < 0 ? -src[i] : src[i];
}

/* Test psabs.h via loop vectorization for 2 halfwords */
void test_psabs_h_v2 (int16_t *dst, int16_t *src)
{
  for (int i = 0; i < 2; i++)
    dst[i] = src[i] < 0 ? -src[i] : src[i];
}

/* Test psabs.h via loop vectorization for 4 halfwords (RV64) */
void test_psabs_h_v4 (int16_t *dst, int16_t *src)
{
  for (int i = 0; i < 4; i++)
    dst[i] = src[i] < 0 ? -src[i] : src[i];
}

/* { dg-final { scan-assembler-times "psabs\\.b" 2 } } */
/* { dg-final { scan-assembler-times "psabs\\.h" 3 } } */
