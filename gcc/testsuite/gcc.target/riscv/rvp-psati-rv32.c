/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test PSATI.H / PSATI.DH / PSATI.DW / PUSATI.H / PUSATI.DH / PUSATI.DW
   codegen on RV32.  4-byte vector modes (PV2HI) use single-register
   psati.h / pusati.h; 8-byte modes use register-pair variants.  */

typedef short          int16x2_t  __attribute__((vector_size (4)));
typedef short          int16x4_t  __attribute__((vector_size (8)));
typedef int            int32x2_t  __attribute__((vector_size (8)));
typedef unsigned short uint16x2_t __attribute__((vector_size (4)));
typedef unsigned short uint16x4_t __attribute__((vector_size (8)));
typedef unsigned int   uint32x2_t __attribute__((vector_size (8)));

/* Vector conditional select using -1/0 mask from comparison.  */
#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

/* PV2HI: single register => psati.h imm=7.  */
int16x2_t psati_h_imm7 (int16x2_t a)
{
  int16x2_t hi = {127, 127}, lo = {-128, -128};
  int16x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.h\M.*, 7} } } */

/* PV4HI: register pair => psati.dh imm=7.  */
int16x4_t psati_dh_imm7 (int16x4_t a)
{
  int16x4_t hi = {127, 127, 127, 127}, lo = {-128, -128, -128, -128};
  int16x4_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.dh\M.*, 7} } } */

/* PV2SI: register pair => psati.dw imm=7.  */
int32x2_t psati_dw_imm7 (int32x2_t a)
{
  int32x2_t hi = {127, 127}, lo = {-128, -128};
  int32x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.dw\M.*, 7} } } */

/* PV2SI: register pair => psati.dw imm=15 (exercises large broadcast bounds).  */
int32x2_t psati_dw_imm15 (int32x2_t a)
{
  int32x2_t hi = {32767, 32767}, lo = {-32768, -32768};
  int32x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler {\mpsati\.dw\M.*, 15} } } */

/* PV2HI: unsigned single register => pusati.h imm=8.  */
uint16x2_t pusati_h_imm8 (uint16x2_t a)
{
  uint16x2_t hi = {255, 255};
  return VSEL (a > hi, hi, a);
}
/* { dg-final { scan-assembler {\mpusati\.h\M.*, 8} } } */

/* PV4HI: unsigned register pair => pusati.dh imm=8.  */
uint16x4_t pusati_dh_imm8 (uint16x4_t a)
{
  uint16x4_t hi = {255, 255, 255, 255};
  return VSEL (a > hi, hi, a);
}
/* { dg-final { scan-assembler {\mpusati\.dh\M.*, 8} } } */

/* PV2SI: unsigned register pair => pusati.dw imm=8.  */
uint32x2_t pusati_dw_imm8 (uint32x2_t a)
{
  uint32x2_t hi = {255, 255};
  return VSEL (a > hi, hi, a);
}

/* PV2SI: signed clamp [0, 255] => pusati.dw imm=8 (smax+smin form).  */
int32x2_t pusati_dw_signed_imm8 (int32x2_t a)
{
  int32x2_t hi = {255, 255}, lo = {0, 0};
  int32x2_t t = VSEL (a > hi, hi, a);
  return VSEL (t < lo, lo, t);
}
/* { dg-final { scan-assembler-times {pusati\.dw\s+\S+,\s*\S+,\s*8} 2 } } */
