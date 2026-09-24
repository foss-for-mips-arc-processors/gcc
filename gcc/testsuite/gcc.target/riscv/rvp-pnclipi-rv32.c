/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef signed char    int8x4_t   __attribute__((vector_size(4)));
typedef short          int16x4_t  __attribute__((vector_size(8)));
typedef short          int16x2_t  __attribute__((vector_size(4)));
typedef unsigned char  uint8x4_t  __attribute__((vector_size(4)));
typedef unsigned short uint16x4_t __attribute__((vector_size(8)));
typedef unsigned short uint16x2_t __attribute__((vector_size(4)));
typedef int            int32x2_t  __attribute__((vector_size(8)));
typedef unsigned int   uint32x2_t __attribute__((vector_size(8)));

#define VSEL(cond, a, b)  (((cond) & (a)) | (~(cond) & (b)))

/* pnclipi.b imm=0: signed clip[-128,127] + narrow, no shift.  */
int8x4_t pnclipi_b_imm0(int16x4_t a)
{
  int16x4_t hi = {127, 127, 127, 127}, lo = {-128, -128, -128, -128};
  int16x4_t t = VSEL(a > hi, hi, a);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int8x4_t);
}
/* { dg-final { scan-assembler {\mpnclipi\.b\M.*, 0} } } */

/* pnclipi.b imm=4: arithmetic shift + clamp[-128,127] + narrow.  */
int8x4_t pnclipi_b_imm4(int16x4_t a)
{
  int16x4_t hi = {127, 127, 127, 127}, lo = {-128, -128, -128, -128};
  int16x4_t shifted = a >> 4;
  int16x4_t t = VSEL(shifted > hi, hi, shifted);
  int16x4_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int8x4_t);
}
/* { dg-final { scan-assembler {\mpnclipi\.b\M.*, 4} } } */

/* pnclipi.h imm=0: signed clip[-32768,32767] + narrow, no shift.  */
int16x2_t pnclipi_h_imm0(int32x2_t a)
{
  int32x2_t hi = {32767, 32767}, lo = {-32768, -32768};
  int32x2_t t = VSEL(a > hi, hi, a);
  int32x2_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int16x2_t);
}
/* { dg-final { scan-assembler {\mpnclipi\.h\M.*, 0} } } */

/* pnclipi.h imm=4: arithmetic shift + clamp[-32768,32767] + narrow.  */
int16x2_t pnclipi_h_imm4(int32x2_t a)
{
  int32x2_t hi = {32767, 32767}, lo = {-32768, -32768};
  int32x2_t shifted = a >> 4;
  int32x2_t t = VSEL(shifted > hi, hi, shifted);
  int32x2_t u = VSEL(t < lo, lo, t);
  return __builtin_convertvector(u, int16x2_t);
}
/* { dg-final { scan-assembler {\mpnclipi\.h\M.*, 4} } } */

/* pnclipiu.b: logical shift of unsigned + clip[0,255], shift folded into the
   immediate.  pnclipiu.b zero-extends and shifts logically, so only an
   unsigned (logical) shift with a bound of exactly 255 may use it.  */
uint8x4_t pnclipiu_b_lshr4(uint16x4_t a)
{
  uint16x4_t hi = {255, 255, 255, 255};
  uint16x4_t shifted = a >> 4;
  uint16x4_t t = VSEL(shifted > hi, hi, shifted);
  return __builtin_convertvector(t, uint8x4_t);
}
/* { dg-final { scan-assembler {\mpnclipiu\.b\M.*, 4} } } */
/* { dg-final { scan-assembler-not {\mpsrli\.dh\M} } } */

/* pnclipiu.b imm=0: clip[0,255] + narrow, no shift.  */
uint8x4_t pnclipiu_b_imm0(uint16x4_t a)
{
  uint16x4_t hi = {255, 255, 255, 255};
  uint16x4_t t = VSEL(a > hi, hi, a);
  return __builtin_convertvector(t, uint8x4_t);
}
/* { dg-final { scan-assembler {\mpnclipiu\.b\M.*, 0} } } */

/* pnclipiu.h: logical shift of unsigned + clip[0,65535], shift folded in.  */
uint16x2_t pnclipiu_h_lshr4(uint32x2_t a)
{
  uint32x2_t hi = {65535, 65535};
  uint32x2_t shifted = a >> 4;
  uint32x2_t t = VSEL(shifted > hi, hi, shifted);
  return __builtin_convertvector(t, uint16x2_t);
}
/* { dg-final { scan-assembler {\mpnclipiu\.h\M.*, 4} } } */
/* { dg-final { scan-assembler-not {\mpsrli\.dw\M} } } */

/* pnclipiu.h imm=0: clip[0,65535] + narrow, no shift.  */
uint16x2_t pnclipiu_h_imm0(uint32x2_t a)
{
  uint32x2_t hi = {65535, 65535};
  uint32x2_t t = VSEL(a > hi, hi, a);
  return __builtin_convertvector(t, uint16x2_t);
}
/* { dg-final { scan-assembler {\mpnclipiu\.h\M.*, 0} } } */
