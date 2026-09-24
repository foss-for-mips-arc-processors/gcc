/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef unsigned char  uint8x4_t  __attribute__((vector_size(4)));
typedef unsigned short uint16x4_t __attribute__((vector_size(8)));
typedef unsigned short uint16x2_t __attribute__((vector_size(4)));
typedef unsigned int   uint32x2_t __attribute__((vector_size(8)));
typedef short          int16x4_t  __attribute__((vector_size(8)));
typedef int            int32x2_t  __attribute__((vector_size(8)));

#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

uint8x4_t
pnclipup_b_zero (uint16x4_t a)
{
  uint16x4_t hi = {255, 255, 255, 255};
  uint16x4_t t = VSEL (a > hi, hi, a);
  return __builtin_convertvector (t, uint8x4_t);
}

/* pnclipup.b has no shift field, so this splits into psrli.h + pnclipup.b.  */
uint8x4_t
pnclipup_b_lshr4 (uint16x4_t a)
{
  uint16x4_t hi = {255, 255, 255, 255};
  uint16x4_t s = a >> 4;
  uint16x4_t t = VSEL (s > hi, hi, s);
  return __builtin_convertvector (t, uint8x4_t);
}

uint16x2_t
pnclipup_h_zero (uint32x2_t a)
{
  uint32x2_t hi = {65535, 65535};
  uint32x2_t t = VSEL (a > hi, hi, a);
  return __builtin_convertvector (t, uint16x2_t);
}

uint16x2_t
pnclipup_h_lshr4 (uint32x2_t a)
{
  uint32x2_t hi = {65535, 65535};
  uint32x2_t s = a >> 4;
  uint32x2_t t = VSEL (s > hi, hi, s);
  return __builtin_convertvector (t, uint16x2_t);
}

/* A signed clamp is safe here because the logical shift makes the value
   non-negative, so the clamp to 0 is a no-op.  */
uint8x4_t
pnclipup_b_lshr4_sclamp (uint16x4_t a)
{
  int16x4_t hi = {255, 255, 255, 255}, lo = {0, 0, 0, 0};
  int16x4_t s = (int16x4_t) (a >> 4);
  int16x4_t t = VSEL (s > hi, hi, s);
  int16x4_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint8x4_t);
}

uint16x2_t
pnclipup_h_lshr4_sclamp (uint32x2_t a)
{
  int32x2_t hi = {65535, 65535}, lo = {0, 0};
  int32x2_t s = (int32x2_t) (a >> 4);
  int32x2_t t = VSEL (s > hi, hi, s);
  int32x2_t u = VSEL (t < lo, lo, t);
  return __builtin_convertvector (u, uint16x2_t);
}

/* { dg-final { scan-assembler-times {\mpnclipup\.b\M[^\n]*zero} 3 } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.h\M[^\n]*zero} 3 } } */
/* { dg-final { scan-assembler-times {\mpsrli\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsrli\.w\M} 2 } } */
/* { dg-final { scan-assembler-not {\mpusati} } } */
