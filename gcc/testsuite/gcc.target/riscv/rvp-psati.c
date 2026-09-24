/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test PSATI.H / PSATI.W / PUSATI.H / PUSATI.W codegen on RV64.
   Use mask-based select (GCC C vector comparison yields -1/0 per element)
   to express clamp; combine recognizes smax+smin and emits psati/pusati.  */

typedef short          int16x2_t  __attribute__((vector_size (4)));
typedef int            int32x2_t  __attribute__((vector_size (8)));
typedef unsigned short uint16x2_t __attribute__((vector_size (4)));
typedef unsigned int   uint32x2_t __attribute__((vector_size (8)));

/* Vector conditional select using -1/0 mask from comparison.  */
#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

/* Signed halfword clamp [-128, 127] => psati.h imm=7.  */
int16x2_t psati_h_imm7 (int16x2_t a)
{
  int16x2_t hi = {127, 127}, lo = {-128, -128};
  int16x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.h\M.*, 7} } } */

/* Signed word clamp [-128, 127] => psati.w imm=7.  */
int32x2_t psati_w_imm7 (int32x2_t a)
{
  int32x2_t hi = {127, 127}, lo = {-128, -128};
  int32x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.w\M.*, 7} } } */

/* Signed word clamp [-32768, 32767] => psati.w imm=15 (exercises large broadcast bounds).  */
int32x2_t psati_w_imm15 (int32x2_t a)
{
  int32x2_t hi = {32767, 32767}, lo = {-32768, -32768};
  int32x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.w\M.*, 15} } } */

/* Unsigned halfword clamp [0, 255] => pusati.h imm=8.  */
uint16x2_t pusati_h_imm8 (uint16x2_t a)
{
  uint16x2_t hi = {255, 255};
  return VSEL (a > hi, hi, a);
}
/* { dg-final { scan-assembler {\mpusati\.h\M.*, 8} } } */

/* Unsigned word clamp [0, 255] => pusati.w imm=8.  */
uint32x2_t pusati_w_imm8 (uint32x2_t a)
{
  uint32x2_t hi = {255, 255};
  return VSEL (a > hi, hi, a);
}

/* Signed word clamp [0, 255] => pusati.w imm=8 (smax+smin form).  */
int32x2_t pusati_w_signed_imm8 (int32x2_t a)
{
  int32x2_t hi = {255, 255}, lo = {0, 0};
  int32x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler-times {pusati\.w\s+\S+,\s*\S+,\s*8} 2 } } */
