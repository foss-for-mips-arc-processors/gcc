/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* pnclipup.b/.h clamp a zero-extended (unsigned) lane to [0, 255]/[0, 65535].
   A *signed* clamp to that range maps negatives to 0, and a signed arithmetic
   shift differs from a logical one, so neither may be lowered to pnclipup --
   doing so miscompiles negative inputs (they would saturate to 255/65535
   instead of 0).  The correct lowering is pusati (+ psrai for the shift)
   followed by a narrowing pack.  */

typedef unsigned char  uint8x4_t  __attribute__((vector_size(4)));
typedef unsigned short uint16x2_t __attribute__((vector_size(4)));
typedef short          int16x4_t  __attribute__((vector_size(8)));
typedef int            int32x2_t  __attribute__((vector_size(8)));

#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

uint8x4_t
sclamp255_b_noshift (int16x4_t a)
{
  int16x4_t hi = {255, 255, 255, 255}, lo = {0, 0, 0, 0};
  int16x4_t t = VSEL (a > hi, hi, a);
  int16x4_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint8x4_t);
}

uint8x4_t
sclamp255_b_ashr (int16x4_t a)
{
  int16x4_t hi = {255, 255, 255, 255}, lo = {0, 0, 0, 0};
  int16x4_t s = a >> 4;
  int16x4_t t = VSEL (s > hi, hi, s);
  int16x4_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint8x4_t);
}

uint16x2_t
sclamp65535_h_noshift (int32x2_t a)
{
  int32x2_t hi = {65535, 65535}, lo = {0, 0};
  int32x2_t t = VSEL (a > hi, hi, a);
  int32x2_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint16x2_t);
}

uint16x2_t
sclamp65535_h_ashr (int32x2_t a)
{
  int32x2_t hi = {65535, 65535}, lo = {0, 0};
  int32x2_t s = a >> 4;
  int32x2_t t = VSEL (s > hi, hi, s);
  int32x2_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint16x2_t);
}

/* The bound is fixed at 255, so a narrower one may not use pnclipup either.  */
uint8x4_t
uclamp63_b (int16x4_t a)
{
  int16x4_t hi = {63, 63, 63, 63}, lo = {0, 0, 0, 0};
  int16x4_t t = VSEL (a > hi, hi, a);
  int16x4_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint8x4_t);
}

/* { dg-final { scan-assembler-not {\mpnclipup\.[bh]\M} } } */
/* { dg-final { scan-assembler {\mpusati} } } */
