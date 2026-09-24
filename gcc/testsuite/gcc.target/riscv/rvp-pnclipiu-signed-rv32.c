/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* pnclipiu.b/.h clamp a zero-extended (unsigned), logically shifted lane to
   [0, 255]/[0, 65535].  A *signed* clamp to that range maps negatives to 0,
   and a signed arithmetic shift differs from the instruction's logical shift,
   so neither may be lowered to pnclipiu -- doing so miscompiles negative
   inputs (negatives would saturate to 255/65535 instead of 0).  The correct
   lowering is pusati (+ psrai for the shift) followed by a narrowing pack.  */

typedef signed char    int8x4_t   __attribute__((vector_size(4)));
typedef short          int16x4_t  __attribute__((vector_size(8)));
typedef short          int16x2_t  __attribute__((vector_size(4)));
typedef unsigned char  uint8x4_t  __attribute__((vector_size(4)));
typedef unsigned short uint16x2_t __attribute__((vector_size(4)));
typedef int            int32x2_t  __attribute__((vector_size(8)));

#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

/* signed clamp[0,255], no shift.  */
uint8x4_t sclamp255_b_noshift(int16x4_t a)
{
  int16x4_t hi = {255, 255, 255, 255}, lo = {0, 0, 0, 0};
  int16x4_t t = VSEL(a > hi, hi, a);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, uint8x4_t);
}

/* signed arithmetic shift + clamp[0,255].  */
uint8x4_t sclamp255_b_ashr(int16x4_t a)
{
  int16x4_t hi = {255, 255, 255, 255}, lo = {0, 0, 0, 0};
  int16x4_t s = a >> 4;
  int16x4_t t = VSEL(s > hi, hi, s);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, uint8x4_t);
}

/* signed clamp[0,65535], no shift.  */
uint16x2_t sclamp65535_h_noshift(int32x2_t a)
{
  int32x2_t hi = {65535, 65535}, lo = {0, 0};
  int32x2_t t = VSEL(a > hi, hi, a);
  int32x2_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, uint16x2_t);
}

/* signed arithmetic shift + clamp[0,65535].  */
uint16x2_t sclamp65535_h_ashr(int32x2_t a)
{
  int32x2_t hi = {65535, 65535}, lo = {0, 0};
  int32x2_t s = a >> 4;
  int32x2_t t = VSEL(s > hi, hi, s);
  int32x2_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, uint16x2_t);
}

/* signed clamp to a sub-range [0,63] narrowed to 8-bit must not use pnclipiu
   either (its bound is fixed at 255, not 63).  */
uint8x4_t uclamp63_b(int16x4_t a)
{
  int16x4_t hi = {63, 63, 63, 63}, lo = {0, 0, 0, 0};
  int16x4_t t = VSEL(a > hi, hi, a);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, uint8x4_t);
}

/* { dg-final { scan-assembler-not {\mpnclipiu\.[bh]\M} } } */
/* { dg-final { scan-assembler {\mpusati} } } */
