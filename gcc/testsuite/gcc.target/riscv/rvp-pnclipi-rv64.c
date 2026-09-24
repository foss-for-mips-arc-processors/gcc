/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef signed char  int8x4_t  __attribute__((vector_size(4)));
typedef short        int16x4_t __attribute__((vector_size(8)));
typedef short        int16x2_t __attribute__((vector_size(4)));
typedef int          int32x2_t __attribute__((vector_size(8)));

#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

/* pnclipp.b rs2=zero: signed clip[-128,127] + narrow PV4HI->PV4QI, no shift.  */
int8x4_t pnclipp_b_zero(int16x4_t a)
{
  int16x4_t hi = {127, 127, 127, 127}, lo = {-128, -128, -128, -128};
  int16x4_t t = VSEL(a > hi, hi, a);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int8x4_t);
}
/* { dg-final { scan-assembler {\mpnclipp\.b\M.*zero} } } */

/* shift + clamp[-128,127] splits to psrai.h + pnclipp.b zero.  */
int8x4_t pnclipp_b_shift4(int16x4_t a)
{
  int16x4_t hi = {127, 127, 127, 127}, lo = {-128, -128, -128, -128};
  int16x4_t shifted = a >> 4;
  int16x4_t t = VSEL(shifted > hi, hi, shifted);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int8x4_t);
}
/* { dg-final { scan-assembler {\mpsrai\.h\M} } } */
/* { dg-final { scan-assembler {\mpnclipp\.b\M.*zero} } } */

/* pnclipp.h rs2=zero: signed clip[-32768,32767] + narrow PV2SI->PV2HI, no shift.  */
int16x2_t pnclipp_h_zero(int32x2_t a)
{
  int32x2_t hi = {32767, 32767}, lo = {-32768, -32768};
  int32x2_t t = VSEL(a > hi, hi, a);
  int32x2_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int16x2_t);
}
/* { dg-final { scan-assembler {\mpnclipp\.h\M.*zero} } } */

/* shift + clamp[-32768,32767] splits to psrai.w + pnclipp.h zero.  */
int16x2_t pnclipp_h_shift4(int32x2_t a)
{
  int32x2_t hi = {32767, 32767}, lo = {-32768, -32768};
  int32x2_t shifted = a >> 4;
  int32x2_t t = VSEL(shifted > hi, hi, shifted);
  int32x2_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int16x2_t);
}
/* { dg-final { scan-assembler {\mpsrai\.w\M} } } */
/* { dg-final { scan-assembler {\mpnclipp\.h\M.*zero} } } */
