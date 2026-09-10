/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */
/* { dg-final { check-function-bodies "**" "" "" } } */

#include <riscv_packed_simd.h>

/* Bitmanip */

/*
**test_cls_32:
** cls\ta[0-9],a[0-9]
** ...
*/
unsigned test_cls_32(int32_t rs1)
{
  return __riscv_cls_32(rs1);
}

/*
**test_rev_32:
** rev\ta[0-9],a[0-9]
** ...
*/
uint32_t test_rev_32(uint32_t rs1)
{
  return __riscv_rev_32(rs1);
}

/*
**test_slx_32:
** slx\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_slx_32(uint32_t rd, uint32_t rs1, unsigned shamt)
{
  return __riscv_slx_32(rd, rs1, shamt);
}

/*
**test_srx_32:
** srx\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_srx_32(uint32_t rd, uint32_t rs1, unsigned shamt)
{
  return __riscv_srx_32(rd, rs1, shamt);
}

/*
**test_wzip8p_64:
** wzip8p\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_wzip8p_64(uint32_t rs1, uint32_t rs2)
{
  return __riscv_wzip8p_64(rs1, rs2);
}

/*
**test_wzip16p_64:
** wzip16p\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_wzip16p_64(uint32_t rs1, uint32_t rs2)
{
  return __riscv_wzip16p_64(rs1, rs2);
}

/* Packed Splat (32-bit) */

/*
**test_pmv_s_u8x4:
** ...
** pmv.bs\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmv_s_u8x4(uint8_t x)
{
  return __riscv_pmv_s_u8x4(x);
}

/*
**test_pmv_s_i8x4:
** ...
** pmv.bs\ta[0-9],a[0-9]
** ...
*/
int8x4_t test_pmv_s_i8x4(int8_t x)
{
  return __riscv_pmv_s_i8x4(x);
}

/*
**test_pmv_s_u16x2:
** ...
** pmv.hs\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmv_s_u16x2(uint16_t x)
{
  return __riscv_pmv_s_u16x2(x);
}

/*
**test_pmv_s_i16x2:
** ...
** pmv.hs\ta[0-9],a[0-9]
** ...
*/
int16x2_t test_pmv_s_i16x2(int16_t x)
{
  return __riscv_pmv_s_i16x2(x);
}

/* Packed Splat (64-bit) */

/*
**test_pmv_s_u8x8:
** ...
** pmv.dbs\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmv_s_u8x8(uint8_t x)
{
  return __riscv_pmv_s_u8x8(x);
}

/*
**test_pmv_s_i8x8:
** ...
** pmv.dbs\ta[0-9],a[0-9]
** ...
*/
int8x8_t test_pmv_s_i8x8(int8_t x)
{
  return __riscv_pmv_s_i8x8(x);
}

/*
**test_pmv_s_u16x4:
** ...
** pmv.dhs\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmv_s_u16x4(uint16_t x)
{
  return __riscv_pmv_s_u16x4(x);
}

/*
**test_pmv_s_u32x2:
** ...
** pmv.dws\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmv_s_u32x2(uint32_t x)
{
  return __riscv_pmv_s_u32x2(x);
}

/*
**test_pmv_s_i32x2:
** ...
** pmv.dws\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_pmv_s_i32x2(int32_t x)
{
  return __riscv_pmv_s_i32x2(x);
}

/* Packed Addition and Subtraction (32-bit) */

/*
**test_padd_i8x4:
** ...
** padd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_padd_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_padd_i8x4(a, b);
}

/*
**test_padd_u8x4:
** ...
** padd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_padd_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_padd_u8x4(a, b);
}

/*
**test_padd_i16x2:
** ...
** padd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_padd_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_padd_i16x2(a, b);
}

/*
**test_padd_u16x2:
** ...
** padd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_padd_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_padd_u16x2(a, b);
}

/*
**test_psub_i8x4:
** ...
** psub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_psub_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_psub_i8x4(a, b);
}

/*
**test_psub_u8x4:
** ...
** psub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_psub_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_psub_u8x4(a, b);
}

/*
**test_psub_i16x2:
** ...
** psub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_psub_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_psub_i16x2(a, b);
}

/*
**test_psub_u16x2:
** ...
** psub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_psub_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_psub_u16x2(a, b);
}

/*
**test_pneg_i8x4:
** ...
** pneg.b\ta[0-9],a[0-9]
** ...
*/
int8x4_t test_pneg_i8x4(int8x4_t a)
{
  return __riscv_pneg_i8x4(a);
}

/*
**test_pneg_i16x2:
** ...
** pneg.h\ta[0-9],a[0-9]
** ...
*/
int16x2_t test_pneg_i16x2(int16x2_t a)
{
  return __riscv_pneg_i16x2(a);
}

/* Packed Addition and Subtraction (64-bit) */

/*
**test_padd_i8x8:
** ...
** padd.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_padd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_padd_i8x8(a, b);
}

/*
**test_padd_u8x8:
** ...
** padd.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_padd_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_padd_u8x8(a, b);
}

/*
**test_padd_u16x4:
** ...
** padd.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_padd_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_padd_u16x4(a, b);
}

/*
**test_padd_i32x2:
** ...
** padd.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_padd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_padd_i32x2(a, b);
}

/*
**test_padd_u32x2:
** ...
** padd.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_padd_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_padd_u32x2(a, b);
}

/*
**test_psub_i8x8:
** ...
** psub.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_psub_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_psub_i8x8(a, b);
}

/*
**test_psub_u8x8:
** ...
** psub.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_psub_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_psub_u8x8(a, b);
}

/*
**test_psub_u16x4:
** ...
** psub.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psub_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_psub_u16x4(a, b);
}

/*
**test_psub_i32x2:
** ...
** psub.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psub_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psub_i32x2(a, b);
}

/*
**test_psub_u32x2:
** ...
** psub.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psub_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_psub_u32x2(a, b);
}

/*
**test_pneg_i8x8:
** ...
** pneg.db\ta[0-9],a[0-9]
** ...
*/
int8x8_t test_pneg_i8x8(int8x8_t a)
{
  return __riscv_pneg_i8x8(a);
}

/*
**test_pneg_i32x2:
** ...
** pneg.dw\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_pneg_i32x2(int32x2_t a)
{
  return __riscv_pneg_i32x2(a);
}

/* Packed Addition with Scalar (32-bit) */

/*
**test_padd_s_u8x4:
** ...
** padd.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_padd_s_u8x4(uint8x4_t a, uint8_t b)
{
  return __riscv_padd_s_u8x4(a, b);
}

/*
**test_padd_s_i8x4:
** ...
** padd.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_padd_s_i8x4(int8x4_t a, int8_t b)
{
  return __riscv_padd_s_i8x4(a, b);
}

/*
**test_padd_s_u16x2:
** ...
** padd.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_padd_s_u16x2(uint16x2_t a, uint16_t b)
{
  return __riscv_padd_s_u16x2(a, b);
}

/*
**test_padd_s_i16x2:
** ...
** padd.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_padd_s_i16x2(int16x2_t a, int16_t b)
{
  return __riscv_padd_s_i16x2(a, b);
}

/* Packed Addition with Scalar (64-bit) */

/*
**test_padd_s_u8x8:
** ...
** padd.dbs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_padd_s_u8x8(uint8x8_t a, uint8_t b)
{
  return __riscv_padd_s_u8x8(a, b);
}

/*
**test_padd_s_i8x8:
** ...
** padd.dbs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_padd_s_i8x8(int8x8_t a, int8_t b)
{
  return __riscv_padd_s_i8x8(a, b);
}

/*
**test_padd_s_u16x4:
** ...
** padd.dhs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_padd_s_u16x4(uint16x4_t a, uint16_t b)
{
  return __riscv_padd_s_u16x4(a, b);
}

/*
**test_padd_s_u32x2:
** ...
** padd.dws\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_padd_s_u32x2(uint32x2_t a, uint32_t b)
{
  return __riscv_padd_s_u32x2(a, b);
}

/*
**test_padd_s_i32x2:
** ...
** padd.dws\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_padd_s_i32x2(int32x2_t a, int32_t b)
{
  return __riscv_padd_s_i32x2(a, b);
}

/* Packed Saturating Addition and Subtraction (32-bit) */

/*
**test_psadd_i8x4:
** ...
** psadd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_psadd_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_psadd_i8x4(a, b);
}

/*
**test_psadd_i16x2:
** ...
** psadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_psadd_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_psadd_i16x2(a, b);
}

/*
**test_psaddu_u8x4:
** ...
** psaddu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_psaddu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_psaddu_u8x4(a, b);
}

/*
**test_psaddu_u16x2:
** ...
** psaddu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_psaddu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_psaddu_u16x2(a, b);
}

/*
**test_pssub_i8x4:
** ...
** pssub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pssub_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pssub_i8x4(a, b);
}

/*
**test_pssub_i16x2:
** ...
** pssub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pssub_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pssub_i16x2(a, b);
}

/*
**test_pssubu_u8x4:
** ...
** pssubu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pssubu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pssubu_u8x4(a, b);
}

/*
**test_pssubu_u16x2:
** ...
** pssubu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pssubu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pssubu_u16x2(a, b);
}

/* Packed Saturating Addition and Subtraction (64-bit) */

/*
**test_psadd_i8x8:
** ...
** psadd.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_psadd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_psadd_i8x8(a, b);
}

/*
**test_psadd_i32x2:
** ...
** psadd.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psadd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psadd_i32x2(a, b);
}

/*
**test_psaddu_u8x8:
** ...
** psaddu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_psaddu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_psaddu_u8x8(a, b);
}

/*
**test_psaddu_u16x4:
** ...
** psaddu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psaddu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_psaddu_u16x4(a, b);
}

/*
**test_psaddu_u32x2:
** ...
** psaddu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psaddu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_psaddu_u32x2(a, b);
}

/*
**test_pssub_i8x8:
** ...
** pssub.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pssub_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pssub_i8x8(a, b);
}

/*
**test_pssub_i32x2:
** ...
** pssub.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pssub_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pssub_i32x2(a, b);
}

/*
**test_pssubu_u8x8:
** ...
** pssubu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pssubu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pssubu_u8x8(a, b);
}

/*
**test_pssubu_u16x4:
** ...
** pssubu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pssubu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pssubu_u16x4(a, b);
}

/*
**test_pssubu_u32x2:
** ...
** pssubu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pssubu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pssubu_u32x2(a, b);
}

/* Packed Averaging Addition and Subtraction (32-bit) */

/*
**test_paadd_i8x4:
** ...
** paadd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_paadd_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_paadd_i8x4(a, b);
}

/*
**test_paadd_i16x2:
** ...
** paadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_paadd_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_paadd_i16x2(a, b);
}

/*
**test_paaddu_u8x4:
** ...
** paaddu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_paaddu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_paaddu_u8x4(a, b);
}

/*
**test_paaddu_u16x2:
** ...
** paaddu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_paaddu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_paaddu_u16x2(a, b);
}

/*
**test_pasub_i8x4:
** ...
** pasub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pasub_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pasub_i8x4(a, b);
}

/*
**test_pasub_i16x2:
** ...
** pasub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pasub_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pasub_i16x2(a, b);
}

/*
**test_pasubu_u8x4:
** ...
** pasubu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pasubu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pasubu_u8x4(a, b);
}

/*
**test_pasubu_u16x2:
** ...
** pasubu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pasubu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pasubu_u16x2(a, b);
}

/* Packed Averaging Addition and Subtraction (64-bit) */

/*
**test_paadd_i8x8:
** ...
** paadd.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_paadd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_paadd_i8x8(a, b);
}

/*
**test_paadd_i32x2:
** ...
** paadd.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_paadd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_paadd_i32x2(a, b);
}

/*
**test_paaddu_u8x8:
** ...
** paaddu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_paaddu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_paaddu_u8x8(a, b);
}

/*
**test_paaddu_u16x4:
** ...
** paaddu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_paaddu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_paaddu_u16x4(a, b);
}

/*
**test_paaddu_u32x2:
** ...
** paaddu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_paaddu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_paaddu_u32x2(a, b);
}

/*
**test_pasub_i8x8:
** ...
** pasub.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pasub_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pasub_i8x8(a, b);
}

/*
**test_pasub_i32x2:
** ...
** pasub.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pasub_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pasub_i32x2(a, b);
}

/*
**test_pasubu_u8x8:
** ...
** pasubu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pasubu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pasubu_u8x8(a, b);
}

/*
**test_pasubu_u16x4:
** ...
** pasubu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pasubu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pasubu_u16x4(a, b);
}

/*
**test_pasubu_u32x2:
** ...
** pasubu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pasubu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pasubu_u32x2(a, b);
}

/* Packed Shift-Add (32-bit) */

/*
**test_psh1add_i16x2:
** ...
** psh1add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_psh1add_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_psh1add_i16x2(a, b);
}

/*
**test_psh1add_u16x2:
** ...
** psh1add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_psh1add_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_psh1add_u16x2(a, b);
}

/*
**test_pssh1sadd_i16x2:
** ...
** pssh1sadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pssh1sadd_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pssh1sadd_i16x2(a, b);
}

/* Packed Shift-Add (64-bit) */

/*
**test_psh1add_u16x4:
** ...
** psh1add.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psh1add_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_psh1add_u16x4(a, b);
}

/*
**test_psh1add_i32x2:
** ...
** psh1add.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psh1add_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psh1add_i32x2(a, b);
}

/*
**test_psh1add_u32x2:
** ...
** psh1add.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psh1add_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_psh1add_u32x2(a, b);
}

/*
**test_pssh1sadd_i32x2:
** ...
** pssh1sadd.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pssh1sadd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pssh1sadd_i32x2(a, b);
}

/* Packed Exchanged Addition and Subtraction (32-bit) */

/*
**test_pas_x_i16x2:
** ...
** pas.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pas_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pas_x_i16x2(a, b);
}

/*
**test_psa_x_i16x2:
** ...
** psa.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_psa_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_psa_x_i16x2(a, b);
}

/*
**test_psas_x_i16x2:
** ...
** psas.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_psas_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_psas_x_i16x2(a, b);
}

/*
**test_pssa_x_i16x2:
** ...
** pssa.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pssa_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pssa_x_i16x2(a, b);
}

/*
**test_paas_x_i16x2:
** ...
** paas.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_paas_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_paas_x_i16x2(a, b);
}

/*
**test_pasa_x_i16x2:
** ...
** pasa.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pasa_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pasa_x_i16x2(a, b);
}

/* Packed Exchanged Addition and Subtraction (64-bit) */

/*
**test_pas_x_i32x2:
** ...
** add\ta[0-9],a[0-9],a[0-9]
** sub\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pas_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pas_x_i32x2(a, b);
}

/*
**test_psa_x_i32x2:
** ...
** sub\ta[0-9],a[0-9],a[0-9]
** add\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psa_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psa_x_i32x2(a, b);
}

/* Packed Absolute Value and Absolute Difference (32-bit) */

/*
**test_pabs_i8x4:
** ...
** pabd.b\ta[0-9],a[0-9],x0
** ...
*/
uint8x4_t test_pabs_i8x4(int8x4_t a)
{
  return __riscv_pabs_i8x4(a);
}

/*
**test_pabs_i16x2:
** ...
** pabd.h\ta[0-9],a[0-9],x0
** ...
*/
uint16x2_t test_pabs_i16x2(int16x2_t a)
{
  return __riscv_pabs_i16x2(a);
}

/*
**test_pabd_i8x4:
** ...
** pabd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pabd_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pabd_i8x4(a, b);
}

/*
**test_pabd_i16x2:
** ...
** pabd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pabd_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pabd_i16x2(a, b);
}

/*
**test_pabdu_u8x4:
** ...
** pabdu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pabdu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdu_u8x4(a, b);
}

/*
**test_pabdu_u16x2:
** ...
** pabdu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pabdu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pabdu_u16x2(a, b);
}

/* Packed Absolute Value and Absolute Difference (64-bit) */

/*
**test_pabs_i8x8:
** ...
** pabd.db\ta[0-9],a[0-9],x0
** ...
*/
uint8x8_t test_pabs_i8x8(int8x8_t a)
{
  return __riscv_pabs_i8x8(a);
}

/*
**test_pabd_i8x8:
** ...
** pabd.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pabd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pabd_i8x8(a, b);
}

/*
**test_pabdu_u8x8:
** ...
** pabdu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pabdu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdu_u8x8(a, b);
}

/*
**test_pabdu_u16x4:
** ...
** pabdu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pabdu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pabdu_u16x4(a, b);
}

/* Packed Absolute Difference Sum is covered by
   packed-absolute-difference-sum-rv32.c.  */

/* Packed Saturating Absolute Value (32-bit) */

/*
**test_psabs_i8x4:
** ...
** psabs.b\ta[0-9],a[0-9]
** ...
*/
int8x4_t test_psabs_i8x4(int8x4_t a)
{
  return __riscv_psabs_i8x4(a);
}

/*
**test_psabs_i16x2:
** ...
** psabs.h\ta[0-9],a[0-9]
** ...
*/
int16x2_t test_psabs_i16x2(int16x2_t a)
{
  return __riscv_psabs_i16x2(a);
}

/* Packed Saturating Absolute Value (64-bit) */

/*
**test_psabs_i8x8:
** ...
** psabs.db\ta[0-9],a[0-9]
** ...
*/
int8x8_t test_psabs_i8x8(int8x8_t a)
{
  return __riscv_psabs_i8x8(a);
}

/* Packed Reduction Sum (32-bit) */

/*
**test_predsum_i8x4_i32:
** ...
** predsum.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_predsum_i8x4_i32(int8x4_t a, int32_t b)
{
  return __riscv_predsum_i8x4_i32(a, b);
}

/*
**test_predsumu_u8x4_u32:
** ...
** predsumu.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_predsumu_u8x4_u32(uint8x4_t a, uint32_t b)
{
  return __riscv_predsumu_u8x4_u32(a, b);
}

/*
**test_predsum_i16x2_i32:
** ...
** predsum.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_predsum_i16x2_i32(int16x2_t a, int32_t b)
{
  return __riscv_predsum_i16x2_i32(a, b);
}

/*
**test_predsumu_u16x2_u32:
** ...
** predsumu.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_predsumu_u16x2_u32(uint16x2_t a, uint32_t b)
{
  return __riscv_predsumu_u16x2_u32(a, b);
}

/* Packed Reduction Sum (64-bit) */

/*
**test_predsum_i8x8_i32:
** ...
** predsum.dbs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_predsum_i8x8_i32(int8x8_t a, int32_t b)
{
  return __riscv_predsum_i8x8_i32(a, b);
}

/*
**test_predsumu_u8x8_u32:
** ...
** predsumu.dbs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_predsumu_u8x8_u32(uint8x8_t a, uint32_t b)
{
  return __riscv_predsumu_u8x8_u32(a, b);
}

/*
**test_predsum_i16x4_i32:
** ...
** predsum.dhs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_predsum_i16x4_i32(int16x4_t a, int32_t b)
{
  return __riscv_predsum_i16x4_i32(a, b);
}

/*
**test_predsumu_u16x4_u32:
** ...
** predsumu.dhs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_predsumu_u16x4_u32(uint16x4_t a, uint32_t b)
{
  return __riscv_predsumu_u16x4_u32(a, b);
}

/* The i64 Packed Reduction Sum interfaces are covered by
   packed-reduction-sum-i64-rv32.c.  */

/* Packed Minimum and Maximum (32-bit) */

/*
**test_pmin_i8x4:
** ...
** pmin.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pmin_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmin_i8x4(a, b);
}

/*
**test_pmin_i16x2:
** ...
** pmin.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmin_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmin_i16x2(a, b);
}

/*
**test_pminu_u8x4:
** ...
** pminu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pminu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pminu_u8x4(a, b);
}

/*
**test_pminu_u16x2:
** ...
** pminu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pminu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pminu_u16x2(a, b);
}

/*
**test_pmax_i8x4:
** ...
** pmax.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pmax_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmax_i8x4(a, b);
}

/*
**test_pmax_i16x2:
** ...
** pmax.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmax_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmax_i16x2(a, b);
}

/*
**test_pmaxu_u8x4:
** ...
** pmaxu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmaxu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmaxu_u8x4(a, b);
}

/*
**test_pmaxu_u16x2:
** ...
** pmaxu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmaxu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmaxu_u16x2(a, b);
}

/* Packed Minimum and Maximum (64-bit) */

/*
**test_pmin_i8x8:
** ...
** pmin.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pmin_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmin_i8x8(a, b);
}

/*
**test_pmin_i32x2:
** ...
** pmin.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmin_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmin_i32x2(a, b);
}

/*
**test_pminu_u8x8:
** ...
** pminu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pminu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pminu_u8x8(a, b);
}

/*
**test_pminu_u16x4:
** ...
** pminu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pminu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pminu_u16x4(a, b);
}

/*
**test_pminu_u32x2:
** ...
** pminu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pminu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pminu_u32x2(a, b);
}

/*
**test_pmax_i8x8:
** ...
** pmax.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pmax_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmax_i8x8(a, b);
}

/*
**test_pmax_i32x2:
** ...
** pmax.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmax_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmax_i32x2(a, b);
}

/*
**test_pmaxu_u8x8:
** ...
** pmaxu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmaxu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmaxu_u8x8(a, b);
}

/*
**test_pmaxu_u16x4:
** ...
** pmaxu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmaxu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmaxu_u16x4(a, b);
}

/*
**test_pmaxu_u32x2:
** ...
** pmaxu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmaxu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmaxu_u32x2(a, b);
}

/* Packed Comparison (32-bit) */

/*
**test_pmseq_i8x4_u8x4:
** ...
** pmseq.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmseq_i8x4_u8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmseq_i8x4_u8x4(a, b);
}

/*
**test_pmseq_u8x4_u8x4:
** ...
** pmseq.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmseq_u8x4_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmseq_u8x4_u8x4(a, b);
}

/*
**test_pmslt_u8x4:
** ...
** pmslt.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmslt_u8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmslt_u8x4(a, b);
}

/*
**test_pmsgt_u8x4:
** ...
** pmslt.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsgt_u8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmsgt_u8x4(a, b);
}

/*
**test_pmsltu_u8x4:
** ...
** pmsltu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsltu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmsltu_u8x4(a, b);
}

/*
**test_pmsgtu_u8x4:
** ...
** pmsltu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsgtu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmsgtu_u8x4(a, b);
}

/*
**test_pmsne_i8x4_u8x4:
** ...
** pmseq.b\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsne_i8x4_u8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmsne_i8x4_u8x4(a, b);
}

/*
**test_pmsne_u8x4_u8x4:
** ...
** pmseq.b\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsne_u8x4_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmsne_u8x4_u8x4(a, b);
}

/*
**test_pmsge_u8x4:
** ...
** pmslt.b\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsge_u8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmsge_u8x4(a, b);
}

/*
**test_pmsle_u8x4:
** ...
** pmslt.b\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsle_u8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pmsle_u8x4(a, b);
}

/*
**test_pmsgeu_u8x4:
** ...
** pmsltu.b\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsgeu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmsgeu_u8x4(a, b);
}

/*
**test_pmsleu_u8x4:
** ...
** pmsltu.b\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmsleu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pmsleu_u8x4(a, b);
}

/*
**test_pmseq_i16x2_u16x2:
** ...
** pmseq.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmseq_i16x2_u16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmseq_i16x2_u16x2(a, b);
}

/*
**test_pmseq_u16x2_u16x2:
** ...
** pmseq.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmseq_u16x2_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmseq_u16x2_u16x2(a, b);
}

/*
**test_pmslt_u16x2:
** ...
** pmslt.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmslt_u16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmslt_u16x2(a, b);
}

/*
**test_pmsgt_u16x2:
** ...
** pmslt.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsgt_u16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmsgt_u16x2(a, b);
}

/*
**test_pmsltu_u16x2:
** ...
** pmsltu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsltu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmsltu_u16x2(a, b);
}

/*
**test_pmsgtu_u16x2:
** ...
** pmsltu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsgtu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmsgtu_u16x2(a, b);
}

/*
**test_pmsne_i16x2_u16x2:
** ...
** pmseq.h\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsne_i16x2_u16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmsne_i16x2_u16x2(a, b);
}

/*
**test_pmsne_u16x2_u16x2:
** ...
** pmseq.h\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsne_u16x2_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmsne_u16x2_u16x2(a, b);
}

/*
**test_pmsge_u16x2:
** ...
** pmslt.h\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsge_u16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmsge_u16x2(a, b);
}

/*
**test_pmsle_u16x2:
** ...
** pmslt.h\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsle_u16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmsle_u16x2(a, b);
}

/*
**test_pmsgeu_u16x2:
** ...
** pmsltu.h\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsgeu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmsgeu_u16x2(a, b);
}

/*
**test_pmsleu_u16x2:
** ...
** pmsltu.h\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmsleu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmsleu_u16x2(a, b);
}

/* Packed Comparison (64-bit) */

/*
**test_pmseq_i8x8_u8x8:
** ...
** pmseq.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmseq_i8x8_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmseq_i8x8_u8x8(a, b);
}

/*
**test_pmseq_u8x8_u8x8:
** ...
** pmseq.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmseq_u8x8_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmseq_u8x8_u8x8(a, b);
}

/*
**test_pmslt_u8x8:
** ...
** pmslt.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmslt_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmslt_u8x8(a, b);
}

/*
**test_pmsgt_u8x8:
** ...
** pmslt.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsgt_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmsgt_u8x8(a, b);
}

/*
**test_pmsltu_u8x8:
** ...
** pmsltu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsltu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsltu_u8x8(a, b);
}

/*
**test_pmsgtu_u8x8:
** ...
** pmsltu.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsgtu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsgtu_u8x8(a, b);
}

/*
**test_pmsne_i8x8_u8x8:
** ...
** pmseq.db\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsne_i8x8_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmsne_i8x8_u8x8(a, b);
}

/*
**test_pmsne_u8x8_u8x8:
** ...
** pmseq.db\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsne_u8x8_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsne_u8x8_u8x8(a, b);
}

/*
**test_pmsge_u8x8:
** ...
** pmslt.db\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsge_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmsge_u8x8(a, b);
}

/*
**test_pmsle_u8x8:
** ...
** pmslt.db\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsle_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmsle_u8x8(a, b);
}

/*
**test_pmsgeu_u8x8:
** ...
** pmsltu.db\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsgeu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsgeu_u8x8(a, b);
}

/*
**test_pmsleu_u8x8:
** ...
** pmsltu.db\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsleu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsleu_u8x8(a, b);
}

/*
**test_pmseq_i16x4_u16x4:
** ...
** pmseq.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmseq_i16x4_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmseq_i16x4_u16x4(a, b);
}

/*
**test_pmseq_u16x4_u16x4:
** ...
** pmseq.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmseq_u16x4_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmseq_u16x4_u16x4(a, b);
}

/*
**test_pmslt_u16x4:
** ...
** pmslt.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmslt_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmslt_u16x4(a, b);
}

/*
**test_pmsgt_u16x4:
** ...
** pmslt.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsgt_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmsgt_u16x4(a, b);
}

/*
**test_pmsltu_u16x4:
** ...
** pmsltu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsltu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsltu_u16x4(a, b);
}

/*
**test_pmsgtu_u16x4:
** ...
** pmsltu.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsgtu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsgtu_u16x4(a, b);
}

/*
**test_pmsne_i16x4_u16x4:
** ...
** pmseq.dh\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsne_i16x4_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmsne_i16x4_u16x4(a, b);
}

/*
**test_pmsne_u16x4_u16x4:
** ...
** pmseq.dh\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsne_u16x4_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsne_u16x4_u16x4(a, b);
}

/*
**test_pmsge_u16x4:
** ...
** pmslt.dh\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsge_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmsge_u16x4(a, b);
}

/*
**test_pmsle_u16x4:
** ...
** pmslt.dh\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsle_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmsle_u16x4(a, b);
}

/*
**test_pmsgeu_u16x4:
** ...
** pmsltu.dh\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsgeu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsgeu_u16x4(a, b);
}

/*
**test_pmsleu_u16x4:
** ...
** pmsltu.dh\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsleu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsleu_u16x4(a, b);
}

/*
**test_pmseq_i32x2_u32x2:
** ...
** pmseq.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmseq_i32x2_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmseq_i32x2_u32x2(a, b);
}

/*
**test_pmseq_u32x2_u32x2:
** ...
** pmseq.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmseq_u32x2_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmseq_u32x2_u32x2(a, b);
}

/*
**test_pmslt_u32x2:
** ...
** pmslt.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmslt_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmslt_u32x2(a, b);
}

/*
**test_pmsgt_u32x2:
** ...
** pmslt.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsgt_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmsgt_u32x2(a, b);
}

/*
**test_pmsltu_u32x2:
** ...
** pmsltu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsltu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsltu_u32x2(a, b);
}

/*
**test_pmsgtu_u32x2:
** ...
** pmsltu.dw\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsgtu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsgtu_u32x2(a, b);
}

/*
**test_pmsne_i32x2_u32x2:
** ...
** pmseq.dw\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsne_i32x2_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmsne_i32x2_u32x2(a, b);
}

/*
**test_pmsne_u32x2_u32x2:
** ...
** pmseq.dw\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsne_u32x2_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsne_u32x2_u32x2(a, b);
}

/*
**test_pmsge_u32x2:
** ...
** pmslt.dw\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsge_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmsge_u32x2(a, b);
}

/*
**test_pmsle_u32x2:
** ...
** pmslt.dw\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsle_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmsle_u32x2(a, b);
}

/*
**test_pmsgeu_u32x2:
** ...
** pmsltu.dw\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsgeu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsgeu_u32x2(a, b);
}

/*
**test_pmsleu_u32x2:
** ...
** pmsltu.dw\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsleu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsleu_u32x2(a, b);
}

/* Packed Merge (32-bit)*/
/*
 * pmerge(rs1, rs2, mask) = (~mask & rs1) | (mask & rs2).
 * The merge, mvm and mvmn opcodes are functionally equivalent and only differ
 * in which input shares a register with the output (merge: mask==rd,
 * mvm: rs1==rd, mvmn: rs2==rd).  The compiler picks one to minimize register
 * copies, so the tests accept any of the three.
 */
/*
**test_pmerge_u8x4:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pmerge_u8x4(uint8x4_t a, uint8x4_t b, uint8x4_t m)
{
  return __riscv_pmerge_u8x4(a, b, m);
}

/*
**test_pmerge_i8x4:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pmerge_i8x4(int8x4_t a, int8x4_t b, uint8x4_t m)
{
  return __riscv_pmerge_i8x4(a, b, m);
}

/*
**test_pmerge_u16x2:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmerge_u16x2(uint16x2_t a, uint16x2_t b, uint16x2_t m)
{
  return __riscv_pmerge_u16x2(a, b, m);
}

/*
**test_pmerge_i16x2:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmerge_i16x2(int16x2_t a, int16x2_t b, uint16x2_t m)
{
  return __riscv_pmerge_i16x2(a, b, m);
}

/* Packed Merge (64-bit)*/
/*
**test_pmerge_u8x8:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmerge_u8x8(uint8x8_t a, uint8x8_t b, uint8x8_t m)
{
  return __riscv_pmerge_u8x8(a, b, m);
}

/*
**test_pmerge_i8x8:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pmerge_i8x8(int8x8_t a, int8x8_t b, uint8x8_t m)
{
  return __riscv_pmerge_i8x8(a, b, m);
}

/*
**test_pmerge_u16x4:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmerge_u16x4(uint16x4_t a, uint16x4_t b, uint16x4_t m)
{
  return __riscv_pmerge_u16x4(a, b, m);
}

/*
**test_pmerge_u32x2:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmerge_u32x2(uint32x2_t a, uint32x2_t b, uint32x2_t m)
{
  return __riscv_pmerge_u32x2(a, b, m);
}

/*
**test_pmerge_i32x2:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmerge_i32x2(int32x2_t a, int32x2_t b, uint32x2_t m)
{
  return __riscv_pmerge_i32x2(a, b, m);
}

/* Packed Sign and Zero Extend (32-bit)*/
/*
**test_psext_b_i16x2:
** ...
** psext.h.b\ta[0-9],a[0-9]
** ...
*/
int16x2_t test_psext_b_i16x2(int16x2_t a)
{
  return __riscv_psext_b_i16x2(a);
}

/*
**test_pzext_b_u16x2:
** ...
** ppaire.b\ta[0-9],a[0-9],x0
** ...
*/
uint16x2_t test_pzext_b_u16x2(uint16x2_t a)
{
  return __riscv_pzext_b_u16x2(a);
}

/* Packed Sign and Zero Extend (64-bit)*/
/*
**test_psext_b_i32x2:
** ...
** psext.dw.b\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_psext_b_i32x2(int32x2_t a)
{
  return __riscv_psext_b_i32x2(a);
}

/*
**test_psext_h_i32x2:
** ...
** psext.dw.h\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_psext_h_i32x2(int32x2_t a)
{
  return __riscv_psext_h_i32x2(a);
}

/*
**test_pzext_b_u16x4:
** ...
** ppaire.db\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pzext_b_u16x4(uint16x4_t a)
{
  return __riscv_pzext_b_u16x4(a);
}

/*
**test_pzext_h_u32x2:
** ...
** ppaire.dh\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pzext_h_u32x2(uint32x2_t a)
{
  return __riscv_pzext_h_u32x2(a);
}

/* Packed Shifts (32-bit) */

/*
**test_psll_s_u8x4:
** ...
** pslli.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint8x4_t test_psll_s_u8x4(uint8x4_t a)
{
  return __riscv_psll_s_u8x4(a, 3);
}

/*
**test_psll_s_i8x4:
** ...
** pslli.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
int8x4_t test_psll_s_i8x4(int8x4_t a)
{
  return __riscv_psll_s_i8x4(a, 3);
}

/*
**test_psll_s_u16x2:
** ...
** pslli.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint16x2_t test_psll_s_u16x2(uint16x2_t a)
{
  return __riscv_psll_s_u16x2(a, 3);
}

/*
**test_psll_s_i16x2:
** ...
** pslli.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x2_t test_psll_s_i16x2(int16x2_t a)
{
  return __riscv_psll_s_i16x2(a, 3);
}

/*
**test_psrl_s_u8x4:
** ...
** psrli.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint8x4_t test_psrl_s_u8x4(uint8x4_t a)
{
  return __riscv_psrl_s_u8x4(a, 3);
}

/*
**test_psrl_s_u16x2:
** ...
** psrli.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint16x2_t test_psrl_s_u16x2(uint16x2_t a)
{
  return __riscv_psrl_s_u16x2(a, 3);
}

/*
**test_psra_s_i8x4:
** ...
** psrai.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
int8x4_t test_psra_s_i8x4(int8x4_t a)
{
  return __riscv_psra_s_i8x4(a, 3);
}

/*
**test_psra_s_i16x2:
** ...
** psrai.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x2_t test_psra_s_i16x2(int16x2_t a)
{
  return __riscv_psra_s_i16x2(a, 3);
}

/* Packed Shifts (64-bit) */

/*
**test_psll_s_u8x8:
** ...
** pslli.db\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint8x8_t test_psll_s_u8x8(uint8x8_t a)
{
  return __riscv_psll_s_u8x8(a, 3);
}

/*
**test_psll_s_i8x8:
** ...
** pslli.db\ta[0-9],a[0-9],[0-9]+
** ...
*/
int8x8_t test_psll_s_i8x8(int8x8_t a)
{
  return __riscv_psll_s_i8x8(a, 3);
}

/*
**test_psll_s_u16x4:
** ...
** pslli.dh\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint16x4_t test_psll_s_u16x4(uint16x4_t a)
{
  return __riscv_psll_s_u16x4(a, 3);
}

/*
**test_psll_s_u32x2:
** ...
** pslli.dw\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint32x2_t test_psll_s_u32x2(uint32x2_t a)
{
  return __riscv_psll_s_u32x2(a, 3);
}

/*
**test_psll_s_i32x2:
** ...
** pslli.dw\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_psll_s_i32x2(int32x2_t a)
{
  return __riscv_psll_s_i32x2(a, 3);
}

/*
**test_psrl_s_u8x8:
** ...
** psrli.db\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint8x8_t test_psrl_s_u8x8(uint8x8_t a)
{
  return __riscv_psrl_s_u8x8(a, 3);
}

/*
**test_psrl_s_u16x4:
** ...
** psrli.dh\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint16x4_t test_psrl_s_u16x4(uint16x4_t a)
{
  return __riscv_psrl_s_u16x4(a, 3);
}

/*
**test_psrl_s_u32x2:
** ...
** psrli.dw\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint32x2_t test_psrl_s_u32x2(uint32x2_t a)
{
  return __riscv_psrl_s_u32x2(a, 3);
}

/*
**test_psra_s_i8x8:
** ...
** psrai.db\ta[0-9],a[0-9],[0-9]+
** ...
*/
int8x8_t test_psra_s_i8x8(int8x8_t a)
{
  return __riscv_psra_s_i8x8(a, 3);
}

/*
**test_psra_s_i32x2:
** ...
** psrai.dw\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_psra_s_i32x2(int32x2_t a)
{
  return __riscv_psra_s_i32x2(a, 3);
}


/* Packed Saturating and Rounding Shifts (32-bit) */

/*
**test_pssha_s_i16x2:
** ...
** psrai.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x2_t test_pssha_s_i16x2(int16x2_t a)
{
  return __riscv_pssha_s_i16x2(a, -3);
}

/*
**test_psshar_s_i16x2:
** ...
** psrari.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x2_t test_psshar_s_i16x2(int16x2_t a)
{
  return __riscv_psshar_s_i16x2(a, -3);
}

/*
**test_psshl_s_u16x2:
** ...
** psshl.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_psshl_s_u16x2(uint16x2_t a)
{
  return __riscv_psshl_s_u16x2(a, 3);
}

/*
**test_psshlr_s_u16x2:
** ...
** psshlr.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_psshlr_s_u16x2(uint16x2_t a)
{
  return __riscv_psshlr_s_u16x2(a, 3);
}

/* Packed Saturating and Rounding Shifts (64-bit) */

/*
**test_pssha_s_i32x2:
** ...
** psrai.dw\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_pssha_s_i32x2(int32x2_t a)
{
  return __riscv_pssha_s_i32x2(a, -3);
}

/*
**test_psshar_s_i32x2:
** ...
** psrari.dw\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_psshar_s_i32x2(int32x2_t a)
{
  return __riscv_psshar_s_i32x2(a, -3);
}

/*
**test_psshl_s_u16x4:
** ...
** psshl.dhs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psshl_s_u16x4(uint16x4_t a)
{
  return __riscv_psshl_s_u16x4(a, 3);
}

/*
**test_psshl_s_u32x2:
** ...
** psshl.dws\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psshl_s_u32x2(uint32x2_t a)
{
  return __riscv_psshl_s_u32x2(a, 3);
}

/*
**test_psshlr_s_u16x4:
** ...
** psshlr.dhs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psshlr_s_u16x4(uint16x4_t a)
{
  return __riscv_psshlr_s_u16x4(a, 3);
}

/*
**test_psshlr_s_u32x2:
** ...
** psshlr.dws\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psshlr_s_u32x2(uint32x2_t a)
{
  return __riscv_psshlr_s_u32x2(a, 3);
}

/* Packed Pair (32-bit) */

/*
**test_ppaire_u8x4:
** ...
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_ppaire_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_ppaire_u8x4(a, b);
}

/*
**test_ppaire_i8x4:
** ...
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_ppaire_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_ppaire_i8x4(a, b);
}

/*
**test_ppaireo_u8x4:
** ...
** ppaireo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_ppaireo_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_ppaireo_u8x4(a, b);
}

/*
**test_ppaireo_i8x4:
** ...
** ppaireo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_ppaireo_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_ppaireo_i8x4(a, b);
}

/*
**test_ppairoe_u8x4:
** ...
** ppairoe.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_ppairoe_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_ppairoe_u8x4(a, b);
}

/*
**test_ppairoe_i8x4:
** ...
** ppairoe.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_ppairoe_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_ppairoe_i8x4(a, b);
}

/*
**test_ppairo_u8x4:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_ppairo_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_ppairo_u8x4(a, b);
}

/*
**test_ppairo_i8x4:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_ppairo_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_ppairo_i8x4(a, b);
}

/*
**test_ppaire_u16x2:
** ...
** pack\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_ppaire_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_ppaire_u16x2(a, b);
}

/*
**test_ppaire_i16x2:
** ...
** pack\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_ppaire_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_ppaire_i16x2(a, b);
}

/*
**test_ppaireo_u16x2:
** ...
** ppaireo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_ppaireo_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_ppaireo_u16x2(a, b);
}

/*
**test_ppaireo_i16x2:
** ...
** ppaireo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_ppaireo_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_ppaireo_i16x2(a, b);
}

/*
**test_ppairoe_u16x2:
** ...
** ppairoe.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_ppairoe_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_ppairoe_u16x2(a, b);
}

/*
**test_ppairoe_i16x2:
** ...
** ppairoe.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_ppairoe_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_ppairoe_i16x2(a, b);
}

/*
**test_ppairo_u16x2:
** ...
** ppairo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_ppairo_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_ppairo_u16x2(a, b);
}

/*
**test_ppairo_i16x2:
** ...
** ppairo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_ppairo_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_ppairo_i16x2(a, b);
}

/* Packed Pair (64-bit) */

/*
**test_ppaire_u8x8:
** ...
** ppaire.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppaire_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppaire_u8x8(a, b);
}

/*
**test_ppaire_i8x8:
** ...
** ppaire.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppaire_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppaire_i8x8(a, b);
}

/*
**test_ppaireo_u8x8:
** ...
** ppaireo.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppaireo_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppaireo_u8x8(a, b);
}

/*
**test_ppaireo_i8x8:
** ...
** ppaireo.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppaireo_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppaireo_i8x8(a, b);
}

/*
**test_ppairoe_u8x8:
** ...
** ppairoe.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppairoe_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppairoe_u8x8(a, b);
}

/*
**test_ppairoe_i8x8:
** ...
** ppairoe.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppairoe_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppairoe_i8x8(a, b);
}

/*
**test_ppairo_u8x8:
** ...
** ppairo.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppairo_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppairo_u8x8(a, b);
}

/*
**test_ppairo_i8x8:
** ...
** ppairo.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppairo_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppairo_i8x8(a, b);
}

/*
**test_ppaire_u16x4:
** ...
** ppaire.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppaire_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppaire_u16x4(a, b);
}

/*
**test_ppaireo_u16x4:
** ...
** ppaireo.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppaireo_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppaireo_u16x4(a, b);
}

/*
**test_ppairoe_u16x4:
** ...
** ppairoe.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppairoe_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppairoe_u16x4(a, b);
}

/*
**test_ppairo_u16x4:
** ...
** ppairo.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppairo_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppairo_u16x4(a, b);
}

/* Packed Widening Convert */

/*
**test_pwcvt_i32x2:
** ...
** pwadd.h\ta[0-9],a[0-9],x0
** ...
*/
int32x2_t test_pwcvt_i32x2(int16x2_t a)
{
  return __riscv_pwcvt_i32x2(a);
}

/*
**test_pwcvtu_u16x4:
** ...
** wzip8p\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pwcvtu_u16x4(uint8x4_t a)
{
  return __riscv_pwcvtu_u16x4(a);
}

/*
**test_pwcvtu_u32x2:
** ...
** wzip16p\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pwcvtu_u32x2(uint16x2_t a)
{
  return __riscv_pwcvtu_u32x2(a);
}

/*
**test_pwcvth_u16x4:
** ...
** wzip8p\ta[0-9],x0,a[0-9]
** ...
*/
uint16x4_t test_pwcvth_u16x4(uint8x4_t a)
{
  return __riscv_pwcvth_u16x4(a);
}

/*
**test_pwcvth_i32x2:
** ...
** wzip16p\ta[0-9],x0,a[0-9]
** ...
*/
int32x2_t test_pwcvth_i32x2(int16x2_t a)
{
  return __riscv_pwcvth_i32x2(a);
}

/*
**test_pwcvth_u32x2:
** ...
** wzip16p\ta[0-9],x0,a[0-9]
** ...
*/
uint32x2_t test_pwcvth_u32x2(uint16x2_t a)
{
  return __riscv_pwcvth_u32x2(a);
}

/* Packed Narrowing Convert */

/*
**test_pncvt_i8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],0
** ...
*/
int8x4_t test_pncvt_i8x4(int16x4_t a)
{
  return __riscv_pncvt_i8x4(a);
}

/*
**test_pncvt_u8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],0
** ...
*/
uint8x4_t test_pncvt_u8x4(uint16x4_t a)
{
  return __riscv_pncvt_u8x4(a);
}

/*
**test_pncvt_i16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],0
** ...
*/
int16x2_t test_pncvt_i16x2(int32x2_t a)
{
  return __riscv_pncvt_i16x2(a);
}

/*
**test_pncvt_u16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],0
** ...
*/
uint16x2_t test_pncvt_u16x2(uint32x2_t a)
{
  return __riscv_pncvt_u16x2(a);
}

/*
**test_pncvth_i8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],8
** ...
*/
int8x4_t test_pncvth_i8x4(int16x4_t a)
{
  return __riscv_pncvth_i8x4(a);
}

/*
**test_pncvth_u8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],8
** ...
*/
uint8x4_t test_pncvth_u8x4(uint16x4_t a)
{
  return __riscv_pncvth_u8x4(a);
}

/*
**test_pncvth_i16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],16
** ...
*/
int16x2_t test_pncvth_i16x2(int32x2_t a)
{
  return __riscv_pncvth_i16x2(a);
}

/*
**test_pncvth_u16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],16
** ...
*/
uint16x2_t test_pncvth_u16x2(uint32x2_t a)
{
  return __riscv_pncvth_u16x2(a);
}

/* Packed Zip */

/*
**test_pzip_i8x8:
** ...
** wzip8p\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pzip_i8x8(int8x4_t a, int8x4_t b)
{
  return __riscv_pzip_i8x8(a, b);
}

/*
**test_pzip_u8x8:
** ...
** wzip8p\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pzip_u8x8(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pzip_u8x8(a, b);
}

/*
**test_pzip_u16x4:
** ...
** wzip16p\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pzip_u16x4(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pzip_u16x4(a, b);
}

/* Packed Unzip */

/*
**test_punzipe_i8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],0
** ...
*/
int8x4_t test_punzipe_i8x4(int8x8_t a)
{
  return __riscv_punzipe_i8x4(a);
}

/*
**test_punzipe_u8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],0
** ...
*/
uint8x4_t test_punzipe_u8x4(uint8x8_t a)
{
  return __riscv_punzipe_u8x4(a);
}

/*
**test_punzipo_i8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],8
** ...
*/
int8x4_t test_punzipo_i8x4(int8x8_t a)
{
  return __riscv_punzipo_i8x4(a);
}

/*
**test_punzipo_u8x4:
** ...
** pnsrli.b\ta[0-9],a[0-9],8
** ...
*/
uint8x4_t test_punzipo_u8x4(uint8x8_t a)
{
  return __riscv_punzipo_u8x4(a);
}

/*
**test_punzipe_i16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],0
** ...
*/
int16x2_t test_punzipe_i16x2(int16x4_t a)
{
  return __riscv_punzipe_i16x2(a);
}

/*
**test_punzipe_u16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],0
** ...
*/
uint16x2_t test_punzipe_u16x2(uint16x4_t a)
{
  return __riscv_punzipe_u16x2(a);
}

/*
**test_punzipo_i16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],16
** ...
*/
int16x2_t test_punzipo_i16x2(int16x4_t a)
{
  return __riscv_punzipo_i16x2(a);
}

/*
**test_punzipo_u16x2:
** ...
** pnsrli.h\ta[0-9],a[0-9],16
** ...
*/
uint16x2_t test_punzipo_u16x2(uint16x4_t a)
{
  return __riscv_punzipo_u16x2(a);
}

/* Packed Narrowing Zip */

/*
**test_pnzip_i8x4:
** ...
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pnzip_i8x4(int16x2_t a, int16x2_t b)
{
  return __riscv_pnzip_i8x4(a, b);
}

/*
**test_pnzip_u8x4:
** ...
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pnzip_u8x4(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pnzip_u8x4(a, b);
}

/*
**test_pnziph_i8x4:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pnziph_i8x4(int16x2_t a, int16x2_t b)
{
  return __riscv_pnziph_i8x4(a, b);
}

/*
**test_pnziph_u8x4:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pnziph_u8x4(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pnziph_u8x4(a, b);
}

/*
**test_pnzip_i8x8:
** ...
** ppaire.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pnzip_i8x8(int16x4_t a, int16x4_t b)
{
  return __riscv_pnzip_i8x8(a, b);
}

/*
**test_pnzip_u8x8:
** ...
** ppaire.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pnzip_u8x8(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pnzip_u8x8(a, b);
}

/*
**test_pnziph_i8x8:
** ...
** ppairo.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pnziph_i8x8(int16x4_t a, int16x4_t b)
{
  return __riscv_pnziph_i8x8(a, b);
}

/*
**test_pnziph_u8x8:
** ...
** ppairo.db\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pnziph_u8x8(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pnziph_u8x8(a, b);
}

/*
**test_pnzip_u16x4:
** ...
** ppaire.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pnzip_u16x4(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pnzip_u16x4(a, b);
}

/*
**test_pnziph_u16x4:
** ...
** ppairo.dh\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pnziph_u16x4(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pnziph_u16x4(a, b);
}

/* Packed Widening Unzip */

/*
**test_pwunzipe_i16x2:
** ...
** psext.h.b\ta[0-9],a[0-9]
** ...
*/
int16x2_t test_pwunzipe_i16x2(int8x4_t a)
{
  return __riscv_pwunzipe_i16x2(a);
}

/*
**test_pwunzipo_i16x2:
** ...
** psrai.h\ta[0-9],a[0-9],8
** ...
*/
int16x2_t test_pwunzipo_i16x2(int8x4_t a)
{
  return __riscv_pwunzipo_i16x2(a);
}

/*
**test_pwunzipue_u16x2:
** ...
** ppaire.b\ta[0-9],a[0-9],x0
** ...
*/
uint16x2_t test_pwunzipue_u16x2(uint8x4_t a)
{
  return __riscv_pwunzipue_u16x2(a);
}

/*
**test_pwunzipuo_u16x2:
** ...
** ppairo.b\ta[0-9],a[0-9],x0
** ...
*/
uint16x2_t test_pwunzipuo_u16x2(uint8x4_t a)
{
  return __riscv_pwunzipuo_u16x2(a);
}

/*
**test_pwunziphe_i16x2:
** ...
** pslli.h\ta[0-9],a[0-9],8
** ...
*/
int16x2_t test_pwunziphe_i16x2(int8x4_t a)
{
  return __riscv_pwunziphe_i16x2(a);
}

/*
**test_pwunziphe_u16x2:
** ...
** pslli.h\ta[0-9],a[0-9],8
** ...
*/
uint16x2_t test_pwunziphe_u16x2(uint8x4_t a)
{
  return __riscv_pwunziphe_u16x2(a);
}

/*
**test_pwunzipho_i16x2:
** ...
** ppairo.b\ta[0-9],x0,a[0-9]
** ...
*/
int16x2_t test_pwunzipho_i16x2(int8x4_t a)
{
  return __riscv_pwunzipho_i16x2(a);
}

/*
**test_pwunzipho_u16x2:
** ...
** ppairo.b\ta[0-9],x0,a[0-9]
** ...
*/
uint16x2_t test_pwunzipho_u16x2(uint8x4_t a)
{
  return __riscv_pwunzipho_u16x2(a);
}

/*
**test_pwunzipue_u16x4:
** ...
** ppaire.db\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pwunzipue_u16x4(uint8x8_t a)
{
  return __riscv_pwunzipue_u16x4(a);
}

/*
**test_pwunzipuo_u16x4:
** ...
** ppairo.db\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pwunzipuo_u16x4(uint8x8_t a)
{
  return __riscv_pwunzipuo_u16x4(a);
}

/*
**test_pwunziphe_u16x4:
** ...
** pslli.dh\ta[0-9],a[0-9],8
** ...
*/
uint16x4_t test_pwunziphe_u16x4(uint8x8_t a)
{
  return __riscv_pwunziphe_u16x4(a);
}

/*
**test_pwunzipho_u16x4:
** ...
** ppairo.db\ta[0-9],x0,a[0-9]
** ...
*/
uint16x4_t test_pwunzipho_u16x4(uint8x8_t a)
{
  return __riscv_pwunzipho_u16x4(a);
}

/*
**test_pwunzipe_i32x2:
** ...
** psext.dw.h\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_pwunzipe_i32x2(int16x4_t a)
{
  return __riscv_pwunzipe_i32x2(a);
}

/*
**test_pwunzipo_i32x2:
** ...
** psrai.dw\ta[0-9],a[0-9],16
** ...
*/
int32x2_t test_pwunzipo_i32x2(int16x4_t a)
{
  return __riscv_pwunzipo_i32x2(a);
}

/*
**test_pwunzipue_u32x2:
** ...
** ppaire.dh\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pwunzipue_u32x2(uint16x4_t a)
{
  return __riscv_pwunzipue_u32x2(a);
}

/*
**test_pwunzipuo_u32x2:
** ...
** ppairo.dh\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pwunzipuo_u32x2(uint16x4_t a)
{
  return __riscv_pwunzipuo_u32x2(a);
}

/*
**test_pwunziphe_i32x2:
** ...
** pslli.dw\ta[0-9],a[0-9],16
** ...
*/
int32x2_t test_pwunziphe_i32x2(int16x4_t a)
{
  return __riscv_pwunziphe_i32x2(a);
}

/*
**test_pwunziphe_u32x2:
** ...
** pslli.dw\ta[0-9],a[0-9],16
** ...
*/
uint32x2_t test_pwunziphe_u32x2(uint16x4_t a)
{
  return __riscv_pwunziphe_u32x2(a);
}

/*
**test_pwunzipho_i32x2:
** ...
** ppairo.dh\ta[0-9],x0,a[0-9]
** ...
*/
int32x2_t test_pwunzipho_i32x2(int16x4_t a)
{
  return __riscv_pwunzipho_i32x2(a);
}

/*
**test_pwunzipho_u32x2:
** ...
** ppairo.dh\ta[0-9],x0,a[0-9]
** ...
*/
uint32x2_t test_pwunzipho_u32x2(uint16x4_t a)
{
  return __riscv_pwunzipho_u32x2(a);
}

/* Packed Widening Addition and Subtraction (RV32-only; RV64 TODO) */

/*
**test_pwadd_i32x2:
** ...
** pwadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwadd_i32x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pwadd_i32x2(a, b);
}

/*
**test_pwaddu_u16x4:
** ...
** pwaddu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pwaddu_u16x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pwaddu_u16x4(a, b);
}

/*
**test_pwaddu_u32x2:
** ...
** pwaddu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwaddu_u32x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pwaddu_u32x2(a, b);
}

/*
**test_pwsub_i32x2:
** ...
** pwsub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwsub_i32x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pwsub_i32x2(a, b);
}

/*
**test_pwsubu_u16x4:
** ...
** pwsubu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pwsubu_u16x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pwsubu_u16x4(a, b);
}

/*
**test_pwsubu_u32x2:
** ...
** pwsubu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwsubu_u32x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pwsubu_u32x2(a, b);
}

/* Packed Widening Addition and Subtraction Accumulate (RV32-only; RV64 TODO) */

/*
**test_pwadda_i32x2:
** ...
** pwadda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwadda_i32x2(int32x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pwadda_i32x2(rd, a, b);
}

/*
**test_pwaddau_u16x4:
** ...
** pwaddau.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pwaddau_u16x4(uint16x4_t rd, uint8x4_t a, uint8x4_t b)
{
  return __riscv_pwaddau_u16x4(rd, a, b);
}

/*
**test_pwaddau_u32x2:
** ...
** pwaddau.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwaddau_u32x2(uint32x2_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pwaddau_u32x2(rd, a, b);
}

/*
**test_pwsuba_i32x2:
** ...
** pwsuba.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwsuba_i32x2(int32x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pwsuba_i32x2(rd, a, b);
}

/*
**test_pwsubau_u16x4:
** ...
** pwsubau.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pwsubau_u16x4(uint16x4_t rd, uint8x4_t a, uint8x4_t b)
{
  return __riscv_pwsubau_u16x4(rd, a, b);
}

/*
**test_pwsubau_u32x2:
** ...
** pwsubau.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwsubau_u32x2(uint32x2_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pwsubau_u32x2(rd, a, b);
}

/* Packed Widening Shift (RV32-only; RV64 TODO) */

/*
**test_pwsll_s_u16x4_imm:
** ...
** pwslli.b\ta[0-9],a[0-9],3
** ...
*/
uint16x4_t test_pwsll_s_u16x4_imm(uint8x4_t a)
{
  return __riscv_pwsll_s_u16x4(a, 3);
}

/*
**test_pwsll_s_u16x4_reg:
** ...
** pwsll.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pwsll_s_u16x4_reg(uint8x4_t a, uint32_t shamt)
{
  return __riscv_pwsll_s_u16x4(a, shamt);
}

/*
**test_pwsll_s_u32x2_imm:
** ...
** pwslli.h\ta[0-9],a[0-9],5
** ...
*/
uint32x2_t test_pwsll_s_u32x2_imm(uint16x2_t a)
{
  return __riscv_pwsll_s_u32x2(a, 5);
}

/*
**test_pwsll_s_u32x2_reg:
** ...
** pwsll.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwsll_s_u32x2_reg(uint16x2_t a, uint32_t shamt)
{
  return __riscv_pwsll_s_u32x2(a, shamt);
}

/*
**test_pwsla_s_i16x4_imm:
** ...
** pwslai.b\ta[0-9],a[0-9],3
** ...
*/
int16x4_t test_pwsla_s_i16x4_imm(int8x4_t a)
{
  return __riscv_pwsla_s_i16x4(a, 3);
}

/*
**test_pwsla_s_i16x4_reg:
** ...
** pwsla.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pwsla_s_i16x4_reg(int8x4_t a, uint32_t shamt)
{
  return __riscv_pwsla_s_i16x4(a, shamt);
}

/*
**test_pwsla_s_i32x2_imm:
** ...
** pwslai.h\ta[0-9],a[0-9],5
** ...
*/
int32x2_t test_pwsla_s_i32x2_imm(int16x2_t a)
{
  return __riscv_pwsla_s_i32x2(a, 5);
}

/*
**test_pwsla_s_i32x2_reg:
** ...
** pwsla.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwsla_s_i32x2_reg(int16x2_t a, uint32_t shamt)
{
  return __riscv_pwsla_s_i32x2(a, shamt);
}

/* Packed Narrowing Shift (RV32-only; RV64 TODO) */

/*
**test_pnsrl_s_u8x4_imm:
** ...
** pnsrli.b\ta[0-9],a[0-9],3
** ...
*/
uint8x4_t test_pnsrl_s_u8x4_imm(uint16x4_t a)
{
  return __riscv_pnsrl_s_u8x4(a, 3);
}

/*
**test_pnsrl_s_u8x4_reg:
** ...
** pnsrl.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pnsrl_s_u8x4_reg(uint16x4_t a, uint32_t shamt)
{
  return __riscv_pnsrl_s_u8x4(a, shamt);
}

/*
**test_pnsrl_s_u16x2_imm:
** ...
** pnsrli.h\ta[0-9],a[0-9],5
** ...
*/
uint16x2_t test_pnsrl_s_u16x2_imm(uint32x2_t a)
{
  return __riscv_pnsrl_s_u16x2(a, 5);
}

/*
**test_pnsrl_s_u16x2_reg:
** ...
** pnsrl.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pnsrl_s_u16x2_reg(uint32x2_t a, uint32_t shamt)
{
  return __riscv_pnsrl_s_u16x2(a, shamt);
}

/*
**test_pnsra_s_i8x4_imm:
** ...
** pnsrai.b\ta[0-9],a[0-9],3
** ...
*/
int8x4_t test_pnsra_s_i8x4_imm(int16x4_t a)
{
  return __riscv_pnsra_s_i8x4(a, 3);
}

/*
**test_pnsra_s_i8x4_reg:
** ...
** pnsra.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pnsra_s_i8x4_reg(int16x4_t a, uint32_t shamt)
{
  return __riscv_pnsra_s_i8x4(a, shamt);
}

/*
**test_pnsra_s_i16x2_imm:
** ...
** pnsrai.h\ta[0-9],a[0-9],5
** ...
*/
int16x2_t test_pnsra_s_i16x2_imm(int32x2_t a)
{
  return __riscv_pnsra_s_i16x2(a, 5);
}

/*
**test_pnsra_s_i16x2_reg:
** ...
** pnsra.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pnsra_s_i16x2_reg(int32x2_t a, uint32_t shamt)
{
  return __riscv_pnsra_s_i16x2(a, shamt);
}

/*
**test_pnsrar_s_i8x4_imm:
** ...
** pnsrari.b\ta[0-9],a[0-9],3
** ...
*/
int8x4_t test_pnsrar_s_i8x4_imm(int16x4_t a)
{
  return __riscv_pnsrar_s_i8x4(a, 3);
}

/*
**test_pnsrar_s_i8x4_reg:
** ...
** pnsrar.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pnsrar_s_i8x4_reg(int16x4_t a, uint32_t shamt)
{
  return __riscv_pnsrar_s_i8x4(a, shamt);
}

/*
**test_pnsrar_s_i16x2_imm:
** ...
** pnsrari.h\ta[0-9],a[0-9],5
** ...
*/
int16x2_t test_pnsrar_s_i16x2_imm(int32x2_t a)
{
  return __riscv_pnsrar_s_i16x2(a, 5);
}

/*
**test_pnsrar_s_i16x2_reg:
** ...
** pnsrar.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pnsrar_s_i16x2_reg(int32x2_t a, uint32_t shamt)
{
  return __riscv_pnsrar_s_i16x2(a, shamt);
}

/* Packed Narrowing Clip (RV32-only; RV64 TODO) */

/*
**test_pnclipu_s_u8x4_imm:
** ...
** pnclipiu.b\ta[0-9],a[0-9],3
** ...
*/
uint8x4_t test_pnclipu_s_u8x4_imm(uint16x4_t a)
{
  return __riscv_pnclipu_s_u8x4(a, 3);
}

/*
**test_pnclipu_s_u8x4_reg:
** ...
** pnclipu.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pnclipu_s_u8x4_reg(uint16x4_t a, uint32_t shamt)
{
  return __riscv_pnclipu_s_u8x4(a, shamt);
}

/*
**test_pnclipu_s_u16x2_imm:
** ...
** pnclipiu.h\ta[0-9],a[0-9],5
** ...
*/
uint16x2_t test_pnclipu_s_u16x2_imm(uint32x2_t a)
{
  return __riscv_pnclipu_s_u16x2(a, 5);
}

/*
**test_pnclipu_s_u16x2_reg:
** ...
** pnclipu.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pnclipu_s_u16x2_reg(uint32x2_t a, uint32_t shamt)
{
  return __riscv_pnclipu_s_u16x2(a, shamt);
}

/*
**test_pnclipru_s_u8x4_imm:
** ...
** pnclipriu.b\ta[0-9],a[0-9],3
** ...
*/
uint8x4_t test_pnclipru_s_u8x4_imm(uint16x4_t a)
{
  return __riscv_pnclipru_s_u8x4(a, 3);
}

/*
**test_pnclipru_s_u8x4_reg:
** ...
** pnclipru.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x4_t test_pnclipru_s_u8x4_reg(uint16x4_t a, uint32_t shamt)
{
  return __riscv_pnclipru_s_u8x4(a, shamt);
}

/*
**test_pnclipru_s_u16x2_imm:
** ...
** pnclipriu.h\ta[0-9],a[0-9],5
** ...
*/
uint16x2_t test_pnclipru_s_u16x2_imm(uint32x2_t a)
{
  return __riscv_pnclipru_s_u16x2(a, 5);
}

/*
**test_pnclipru_s_u16x2_reg:
** ...
** pnclipru.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pnclipru_s_u16x2_reg(uint32x2_t a, uint32_t shamt)
{
  return __riscv_pnclipru_s_u16x2(a, shamt);
}

/*
**test_pnclip_s_i8x4_imm:
** ...
** pnclipi.b\ta[0-9],a[0-9],3
** ...
*/
int8x4_t test_pnclip_s_i8x4_imm(int16x4_t a)
{
  return __riscv_pnclip_s_i8x4(a, 3);
}

/*
**test_pnclip_s_i8x4_reg:
** ...
** pnclip.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pnclip_s_i8x4_reg(int16x4_t a, uint32_t shamt)
{
  return __riscv_pnclip_s_i8x4(a, shamt);
}

/*
**test_pnclip_s_i16x2_imm:
** ...
** pnclipi.h\ta[0-9],a[0-9],5
** ...
*/
int16x2_t test_pnclip_s_i16x2_imm(int32x2_t a)
{
  return __riscv_pnclip_s_i16x2(a, 5);
}

/*
**test_pnclip_s_i16x2_reg:
** ...
** pnclip.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pnclip_s_i16x2_reg(int32x2_t a, uint32_t shamt)
{
  return __riscv_pnclip_s_i16x2(a, shamt);
}

/*
**test_pnclipr_s_i8x4_imm:
** ...
** pnclipri.b\ta[0-9],a[0-9],3
** ...
*/
int8x4_t test_pnclipr_s_i8x4_imm(int16x4_t a)
{
  return __riscv_pnclipr_s_i8x4(a, 3);
}

/*
**test_pnclipr_s_i8x4_reg:
** ...
** pnclipr.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x4_t test_pnclipr_s_i8x4_reg(int16x4_t a, uint32_t shamt)
{
  return __riscv_pnclipr_s_i8x4(a, shamt);
}

/*
**test_pnclipr_s_i16x2_imm:
** ...
** pnclipri.h\ta[0-9],a[0-9],5
** ...
*/
int16x2_t test_pnclipr_s_i16x2_imm(int32x2_t a)
{
  return __riscv_pnclipr_s_i16x2(a, 5);
}

/*
**test_pnclipr_s_i16x2_reg:
** ...
** pnclipr.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pnclipr_s_i16x2_reg(int32x2_t a, uint32_t shamt)
{
  return __riscv_pnclipr_s_i16x2(a, shamt);
}

// Packed Narrowing Clip Pair (TODO)

// Packed Reverse (TODO)

/* Packed Multiply High */

/*
**test_pmulh_i16x2:
** ...
** pmulh.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulh_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmulh_i16x2(a, b);
}

/*
**test_pmulhr_i16x2:
** ...
** pmulhr.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulhr_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmulhr_i16x2(a, b);
}

/*
**test_pmulhu_u16x2:
** ...
** pmulhu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmulhu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmulhu_u16x2(a, b);
}

/*
**test_pmulhru_u16x2:
** ...
** pmulhru.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmulhru_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmulhru_u16x2(a, b);
}

/*
**test_pmulhsu_i16x2:
** ...
** pmulhsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulhsu_i16x2(int16x2_t a, uint16x2_t b)
{
  return __riscv_pmulhsu_i16x2(a, b);
}

/*
**test_pmulhrsu_i16x2:
** ...
** pmulhrsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulhrsu_i16x2(int16x2_t a, uint16x2_t b)
{
  return __riscv_pmulhrsu_i16x2(a, b);
}

/* Packed Multiply High 64-bit (RV32: 2x pmulh.h on high/low halves) */

/* Packed Multiply High Accumulate (i16x2 single, i16x4 2x; i32x2 RV64-only TODO) */

/*
**test_pmhacc_i16x2:
** ...
** pmhacc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhacc_i16x2(int16x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pmhacc_i16x2(rd, a, b);
}

/*
**test_pmhracc_i16x2:
** ...
** pmhracc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhracc_i16x2(int16x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pmhracc_i16x2(rd, a, b);
}

/*
**test_pmhaccu_u16x2:
** ...
** pmhaccu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmhaccu_u16x2(uint16x2_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmhaccu_u16x2(rd, a, b);
}

/*
**test_pmhraccu_u16x2:
** ...
** pmhraccu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_pmhraccu_u16x2(uint16x2_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pmhraccu_u16x2(rd, a, b);
}

/*
**test_pmhaccsu_i16x2:
** ...
** pmhaccsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhaccsu_i16x2(int16x2_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_pmhaccsu_i16x2(rd, a, b);
}

/*
**test_pmhraccsu_i16x2:
** ...
** pmhraccsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhraccsu_i16x2(int16x2_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_pmhraccsu_i16x2(rd, a, b);
}

/* Packed Q-format Multiplication (i16x2 only; i16x4/i32x2 RV64-only TODO) */

/*
**test_pmulq_i16x2:
** ...
** pmulq.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulq_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmulq_i16x2(a, b);
}

/*
**test_pmulqr_i16x2:
** ...
** pmulqr.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulqr_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmulqr_i16x2(a, b);
}

/*
**test_pmulq_i16x4:
** ...
** pmulq.h\ta[0-9],a[0-9],a[0-9]
** pmulq.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulq_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmulq_i16x4(a, b);
}

/*
**test_pmulqr_i16x4:
** ...
** pmulqr.h\ta[0-9],a[0-9],a[0-9]
** pmulqr.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulqr_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmulqr_i16x4(a, b);
}

/* Packed Multiply High 64-bit i16x4 (RV32: 2x on high/low halves) */

/*
**test_pmulh_i16x4:
** ...
** pmulh.h\ta[0-9],a[0-9],a[0-9]
** pmulh.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulh_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmulh_i16x4(a, b);
}

/*
**test_pmulhr_i16x4:
** ...
** pmulhr.h\ta[0-9],a[0-9],a[0-9]
** pmulhr.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulhr_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmulhr_i16x4(a, b);
}

/*
**test_pmulhu_u16x4:
** ...
** pmulhu.h\ta[0-9],a[0-9],a[0-9]
** pmulhu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmulhu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmulhu_u16x4(a, b);
}

/*
**test_pmulhru_u16x4:
** ...
** pmulhru.h\ta[0-9],a[0-9],a[0-9]
** pmulhru.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmulhru_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmulhru_u16x4(a, b);
}

/*
**test_pmulhsu_i16x4:
** ...
** pmulhsu.h\ta[0-9],a[0-9],a[0-9]
** pmulhsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulhsu_i16x4(int16x4_t a, uint16x4_t b)
{
  return __riscv_pmulhsu_i16x4(a, b);
}

/*
**test_pmulhrsu_i16x4:
** ...
** pmulhrsu.h\ta[0-9],a[0-9],a[0-9]
** pmulhrsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulhrsu_i16x4(int16x4_t a, uint16x4_t b)
{
  return __riscv_pmulhrsu_i16x4(a, b);
}

/* Packed Q-format Multiply Parts Accumulate
   h-series i32 (both ISAs): RV32 mqacc.hNN / mqracc.hNN (single insn).
   h-series i32x2 (packed): RV32 two mqacc.hNN / mqracc.hNN on low/high halves.
   w-series i64 (RV64-only TODO: mqwacc/mqrwacc register pair) not present.  */

/*
**test_mqacc_h00_i32:
** ...
** mqacc.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqacc_h00_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqacc_h00_i32(rd, a, b);
}

/*
**test_mqacc_h01_i32:
** ...
** mqacc.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqacc_h01_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqacc_h01_i32(rd, a, b);
}

/*
**test_mqacc_h11_i32:
** ...
** mqacc.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqacc_h11_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqacc_h11_i32(rd, a, b);
}

/*
**test_mqracc_h00_i32:
** ...
** mqracc.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqracc_h00_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqracc_h00_i32(rd, a, b);
}

/*
**test_mqracc_h01_i32:
** ...
** mqracc.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqracc_h01_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqracc_h01_i32(rd, a, b);
}

/*
**test_mqracc_h11_i32:
** ...
** mqracc.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqracc_h11_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqracc_h11_i32(rd, a, b);
}

/*
**test_pmqacc_h00_i32x2:
** ...
** mqacc.h00\ta[0-9],a[0-9],a[0-9]
** mqacc.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqacc_h00_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqacc_h00_i32x2(rd, a, b);
}

/*
**test_pmqacc_h01_i32x2:
** ...
** mqacc.h01\ta[0-9],a[0-9],a[0-9]
** mqacc.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqacc_h01_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqacc_h01_i32x2(rd, a, b);
}

/*
**test_pmqacc_h11_i32x2:
** ...
** mqacc.h11\ta[0-9],a[0-9],a[0-9]
** mqacc.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqacc_h11_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqacc_h11_i32x2(rd, a, b);
}

/*
**test_pmqracc_h00_i32x2:
** ...
** mqracc.h00\ta[0-9],a[0-9],a[0-9]
** mqracc.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqracc_h00_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqracc_h00_i32x2(rd, a, b);
}

/*
**test_pmqracc_h01_i32x2:
** ...
** mqracc.h01\ta[0-9],a[0-9],a[0-9]
** mqracc.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqracc_h01_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqracc_h01_i32x2(rd, a, b);
}

/*
**test_pmqracc_h11_i32x2:
** ...
** mqracc.h11\ta[0-9],a[0-9],a[0-9]
** mqracc.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqracc_h11_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqracc_h11_i32x2(rd, a, b);
}

/* Packed Multiply Parts Accumulate (RV32)
   h-series i32 (scalar): macc.hNN/maccu.hNN/maccsu.hNN.
   h-series i32x2 (packed): 2x macc.hNN/etc.  w-series RV32 TODO (wmacc).  */

/*
**test_macc_h00_i32:
** macc.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_macc_h00_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_macc_h00_i32(rd, a, b);
}

/*
**test_macc_h01_i32:
** macc.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_macc_h01_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_macc_h01_i32(rd, a, b);
}

/*
**test_macc_h11_i32:
** macc.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_macc_h11_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_macc_h11_i32(rd, a, b);
}

/*
**test_maccu_h00_u32:
** maccu.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_maccu_h00_u32(uint32_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_maccu_h00_u32(rd, a, b);
}

/*
**test_maccu_h01_u32:
** maccu.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_maccu_h01_u32(uint32_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_maccu_h01_u32(rd, a, b);
}

/*
**test_maccu_h11_u32:
** maccu.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_maccu_h11_u32(uint32_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_maccu_h11_u32(rd, a, b);
}

/*
**test_maccsu_h00_i32:
** maccsu.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_maccsu_h00_i32(int32_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_maccsu_h00_i32(rd, a, b);
}

/*
**test_maccsu_h11_i32:
** maccsu.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_maccsu_h11_i32(int32_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_maccsu_h11_i32(rd, a, b);
}

/*
**test_pmacc_h00_i32x2:
** macc.h00\ta[0-9],a[0-9],a[0-9]
** macc.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmacc_h00_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmacc_h00_i32x2(rd, a, b);
}

/*
**test_pmacc_h01_i32x2:
** macc.h01\ta[0-9],a[0-9],a[0-9]
** macc.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmacc_h01_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmacc_h01_i32x2(rd, a, b);
}

/*
**test_pmacc_h11_i32x2:
** macc.h11\ta[0-9],a[0-9],a[0-9]
** macc.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmacc_h11_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmacc_h11_i32x2(rd, a, b);
}

/*
**test_pmaccu_h00_u32x2:
** maccu.h00\ta[0-9],a[0-9],a[0-9]
** maccu.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmaccu_h00_u32x2(uint32x2_t rd, uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmaccu_h00_u32x2(rd, a, b);
}

/*
**test_pmaccu_h01_u32x2:
** maccu.h01\ta[0-9],a[0-9],a[0-9]
** maccu.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmaccu_h01_u32x2(uint32x2_t rd, uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmaccu_h01_u32x2(rd, a, b);
}

/*
**test_pmaccu_h11_u32x2:
** maccu.h11\ta[0-9],a[0-9],a[0-9]
** maccu.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmaccu_h11_u32x2(uint32x2_t rd, uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmaccu_h11_u32x2(rd, a, b);
}

/*
**test_pmaccsu_h00_i32x2:
** maccsu.h00\ta[0-9],a[0-9],a[0-9]
** maccsu.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmaccsu_h00_i32x2(int32x2_t rd, int16x4_t a, uint16x4_t b)
{
  return __riscv_pmaccsu_h00_i32x2(rd, a, b);
}

/*
**test_pmaccsu_h11_i32x2:
** maccsu.h11\ta[0-9],a[0-9],a[0-9]
** maccsu.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmaccsu_h11_i32x2(int32x2_t rd, int16x4_t a, uint16x4_t b)
{
  return __riscv_pmaccsu_h11_i32x2(rd, a, b);
}

/* Packed Multiplication with Horizontal Addition (RV32)
   32-bit (single insn): pm4add.b/pm2add.h/etc.
   64-bit i32x2 (2x split): 2x pm4add.b/etc.  i64 RV32 TODO.  */

/*
**test_pm4add_i8x4:
** pm4add.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm4add_i8x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pm4add_i8x4(a, b);
}

/*
**test_pm2add_i16x2:
** pm2add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2add_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2add_i16x2(a, b);
}

/*
**test_pm2add_x_i16x2:
** pm2add.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2add_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2add_x_i16x2(a, b);
}

/*
**test_pm4addu_u8x4:
** pm4addu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_pm4addu_u8x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pm4addu_u8x4(a, b);
}

/*
**test_pm2addu_u16x2:
** pm2addu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_pm2addu_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pm2addu_u16x2(a, b);
}

/*
**test_pmq2add_i16x2:
** pmq2add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pmq2add_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmq2add_i16x2(a, b);
}

/*
**test_pmqr2add_i16x2:
** pmqr2add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pmqr2add_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pmqr2add_i16x2(a, b);
}

/*
**test_pm2sadd_i16x2:
** pm2sadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2sadd_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2sadd_i16x2(a, b);
}

/*
**test_pm2sadd_x_i16x2:
** pm2sadd.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2sadd_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2sadd_x_i16x2(a, b);
}

/*
**test_pm2sub_i16x2:
** pm2sub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2sub_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2sub_i16x2(a, b);
}

/*
**test_pm2sub_x_i16x2:
** pm2sub.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2sub_x_i16x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2sub_x_i16x2(a, b);
}

/*
**test_pm4addsu_i8x4:
** pm4addsu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm4addsu_i8x4(int8x4_t a, uint8x4_t b)
{
  return __riscv_pm4addsu_i8x4(a, b);
}

/*
**test_pm2addsu_i16x2:
** pm2addsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2addsu_i16x2(int16x2_t a, uint16x2_t b)
{
  return __riscv_pm2addsu_i16x2(a, b);
}

/* 64-bit i32x2 (packed): RV32 2x split */
/*
**test_pm4add_i8x8:
** pm4add.b\ta[0-9],a[0-9],a[0-9]
** pm4add.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm4add_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pm4add_i8x8(a, b);
}

/*
**test_pm2add_i16x4:
** pm2add.h\ta[0-9],a[0-9],a[0-9]
** pm2add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2add_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pm2add_i16x4(a, b);
}

/*
**test_pm2add_x_i16x4:
** pm2add.hx\ta[0-9],a[0-9],a[0-9]
** pm2add.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2add_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pm2add_x_i16x4(a, b);
}

/*
**test_pm4addu_u8x8:
** pm4addu.b\ta[0-9],a[0-9],a[0-9]
** pm4addu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pm4addu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pm4addu_u8x8(a, b);
}

/*
**test_pm2addu_u16x4:
** pm2addu.h\ta[0-9],a[0-9],a[0-9]
** pm2addu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pm2addu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pm2addu_u16x4(a, b);
}

/*
**test_pmq2add_i16x4:
** pmq2add.h\ta[0-9],a[0-9],a[0-9]
** pmq2add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmq2add_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmq2add_i16x4(a, b);
}

/*
**test_pmqr2add_i16x4:
** pmqr2add.h\ta[0-9],a[0-9],a[0-9]
** pmqr2add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqr2add_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmqr2add_i16x4(a, b);
}

/*
**test_pm2sadd_i16x4:
** pm2sadd.h\ta[0-9],a[0-9],a[0-9]
** pm2sadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2sadd_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pm2sadd_i16x4(a, b);
}

/*
**test_pm2sadd_x_i16x4:
** pm2sadd.hx\ta[0-9],a[0-9],a[0-9]
** pm2sadd.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2sadd_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pm2sadd_x_i16x4(a, b);
}

/*
**test_pm2sub_i16x4:
** pm2sub.h\ta[0-9],a[0-9],a[0-9]
** pm2sub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2sub_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pm2sub_i16x4(a, b);
}

/*
**test_pm2sub_x_i16x4:
** pm2sub.hx\ta[0-9],a[0-9],a[0-9]
** pm2sub.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2sub_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pm2sub_x_i16x4(a, b);
}

/*
**test_pm4addsu_i8x8:
** pm4addsu.b\ta[0-9],a[0-9],a[0-9]
** pm4addsu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm4addsu_i8x8(int8x8_t a, uint8x8_t b)
{
  return __riscv_pm4addsu_i8x8(a, b);
}

/*
**test_pm2addsu_i16x4:
** pm2addsu.h\ta[0-9],a[0-9],a[0-9]
** pm2addsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2addsu_i16x4(int16x4_t a, uint16x4_t b)
{
  return __riscv_pm2addsu_i16x4(a, b);
}

/* Packed Multiplication with Horizontal Addition and Accumulate (RV32, RMW)
   32-bit (single RMW insn): pm4adda.b/pm2adda.h/etc.
   64-bit i32x2 (2x split RMW): 2x pm4adda.b/etc.  i64 RV32 TODO.  */

/*
**test_pm4adda_i8x4:
** pm4adda.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm4adda_i8x4(int32_t rd, int8x4_t a, int8x4_t b)
{
  return __riscv_pm4adda_i8x4(rd, a, b);
}

/*
**test_pm2adda_i16x2:
** pm2adda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2adda_i16x2(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2adda_i16x2(rd, a, b);
}

/*
**test_pm2adda_x_i16x2:
** pm2adda.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2adda_x_i16x2(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2adda_x_i16x2(rd, a, b);
}

/*
**test_pm4addau_u8x4:
** pm4addau.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_pm4addau_u8x4(uint32_t rd, uint8x4_t a, uint8x4_t b)
{
  return __riscv_pm4addau_u8x4(rd, a, b);
}

/*
**test_pm2addau_u16x2:
** pm2addau.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_pm2addau_u16x2(uint32_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pm2addau_u16x2(rd, a, b);
}

/*
**test_pmq2adda_i16x2:
** pmq2adda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pmq2adda_i16x2(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pmq2adda_i16x2(rd, a, b);
}

/*
**test_pmqr2adda_i16x2:
** pmqr2adda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pmqr2adda_i16x2(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pmqr2adda_i16x2(rd, a, b);
}

/*
**test_pm2suba_i16x2:
** pm2suba.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2suba_i16x2(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2suba_i16x2(rd, a, b);
}

/*
**test_pm2suba_x_i16x2:
** pm2suba.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2suba_x_i16x2(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2suba_x_i16x2(rd, a, b);
}

/*
**test_pm4addasu_i8x4:
** pm4addasu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm4addasu_i8x4(int32_t rd, int8x4_t a, uint8x4_t b)
{
  return __riscv_pm4addasu_i8x4(rd, a, b);
}

/*
**test_pm2addasu_i16x2:
** pm2addasu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_pm2addasu_i16x2(int32_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_pm2addasu_i16x2(rd, a, b);
}

/* 64-bit i32x2 (packed, RMW): RV32 2x split */
/*
**test_pm4adda_i8x8:
** pm4adda.b\ta[0-9],a[0-9],a[0-9]
** pm4adda.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm4adda_i8x8(int32x2_t rd, int8x8_t a, int8x8_t b)
{
  return __riscv_pm4adda_i8x8(rd, a, b);
}

/*
**test_pm2adda_i16x4:
** pm2adda.h\ta[0-9],a[0-9],a[0-9]
** pm2adda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2adda_i16x4(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pm2adda_i16x4(rd, a, b);
}

/*
**test_pm2adda_x_i16x4:
** pm2adda.hx\ta[0-9],a[0-9],a[0-9]
** pm2adda.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2adda_x_i16x4(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pm2adda_x_i16x4(rd, a, b);
}

/*
**test_pm4addau_u8x8:
** pm4addau.b\ta[0-9],a[0-9],a[0-9]
** pm4addau.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pm4addau_u8x8(uint32x2_t rd, uint8x8_t a, uint8x8_t b)
{
  return __riscv_pm4addau_u8x8(rd, a, b);
}

/*
**test_pm2addau_u16x4:
** pm2addau.h\ta[0-9],a[0-9],a[0-9]
** pm2addau.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pm2addau_u16x4(uint32x2_t rd, uint16x4_t a, uint16x4_t b)
{
  return __riscv_pm2addau_u16x4(rd, a, b);
}

/*
**test_pmq2adda_i16x4:
** pmq2adda.h\ta[0-9],a[0-9],a[0-9]
** pmq2adda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmq2adda_i16x4(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmq2adda_i16x4(rd, a, b);
}

/*
**test_pmqr2adda_i16x4:
** pmqr2adda.h\ta[0-9],a[0-9],a[0-9]
** pmqr2adda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqr2adda_i16x4(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqr2adda_i16x4(rd, a, b);
}

/*
**test_pm2suba_i16x4:
** pm2suba.h\ta[0-9],a[0-9],a[0-9]
** pm2suba.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2suba_i16x4(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pm2suba_i16x4(rd, a, b);
}

/*
**test_pm2suba_x_i16x4:
** pm2suba.hx\ta[0-9],a[0-9],a[0-9]
** pm2suba.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2suba_x_i16x4(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pm2suba_x_i16x4(rd, a, b);
}

/*
**test_pm4addasu_i8x8:
** pm4addasu.b\ta[0-9],a[0-9],a[0-9]
** pm4addasu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm4addasu_i8x8(int32x2_t rd, int8x8_t a, uint8x8_t b)
{
  return __riscv_pm4addasu_i8x8(rd, a, b);
}

/*
**test_pm2addasu_i16x4:
** pm2addasu.h\ta[0-9],a[0-9],a[0-9]
** pm2addasu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pm2addasu_i16x4(int32x2_t rd, int16x4_t a, uint16x4_t b)
{
  return __riscv_pm2addasu_i16x4(rd, a, b);
}

/* Packed Multiply High Parts (RV32)
   b-series i16x2 (single insn): pmulh.h.bN/pmulhsu.h.bN.
   h-series i32 (scalar): mulh.hN/mulhsu.hN.
   b-series i16x4 (2x split): 2x pmulh.h.bN.
   h-series i32x2 (2x split): 2x mulh.hN.  */

/*
**test_pmulh_b0_i16x2:
** pmulh.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulh_b0_i16x2(int16x2_t a, int8x4_t b)
{
  return __riscv_pmulh_b0_i16x2(a, b);
}

/*
**test_pmulh_b1_i16x2:
** pmulh.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulh_b1_i16x2(int16x2_t a, int8x4_t b)
{
  return __riscv_pmulh_b1_i16x2(a, b);
}

/*
**test_pmulhsu_b0_i16x2:
** pmulhsu.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulhsu_b0_i16x2(int16x2_t a, uint8x4_t b)
{
  return __riscv_pmulhsu_b0_i16x2(a, b);
}

/*
**test_pmulhsu_b1_i16x2:
** pmulhsu.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmulhsu_b1_i16x2(int16x2_t a, uint8x4_t b)
{
  return __riscv_pmulhsu_b1_i16x2(a, b);
}

/*
**test_mulh_h0_i32:
** mulh.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mulh_h0_i32(int32_t a, int16x2_t b)
{
  return __riscv_mulh_h0_i32(a, b);
}

/*
**test_mulh_h1_i32:
** mulh.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mulh_h1_i32(int32_t a, int16x2_t b)
{
  return __riscv_mulh_h1_i32(a, b);
}

/*
**test_mulhsu_h0_i32:
** mulhsu.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mulhsu_h0_i32(int32_t a, uint16x2_t b)
{
  return __riscv_mulhsu_h0_i32(a, b);
}

/*
**test_mulhsu_h1_i32:
** mulhsu.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mulhsu_h1_i32(int32_t a, uint16x2_t b)
{
  return __riscv_mulhsu_h1_i32(a, b);
}

/*
**test_pmulh_b0_i16x4:
** pmulh.h.b0\ta[0-9],a[0-9],a[0-9]
** pmulh.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulh_b0_i16x4(int16x4_t a, int8x8_t b)
{
  return __riscv_pmulh_b0_i16x4(a, b);
}

/*
**test_pmulh_b1_i16x4:
** pmulh.h.b1\ta[0-9],a[0-9],a[0-9]
** pmulh.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulh_b1_i16x4(int16x4_t a, int8x8_t b)
{
  return __riscv_pmulh_b1_i16x4(a, b);
}

/*
**test_pmulhsu_b0_i16x4:
** pmulhsu.h.b0\ta[0-9],a[0-9],a[0-9]
** pmulhsu.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulhsu_b0_i16x4(int16x4_t a, uint8x8_t b)
{
  return __riscv_pmulhsu_b0_i16x4(a, b);
}

/*
**test_pmulhsu_b1_i16x4:
** pmulhsu.h.b1\ta[0-9],a[0-9],a[0-9]
** pmulhsu.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmulhsu_b1_i16x4(int16x4_t a, uint8x8_t b)
{
  return __riscv_pmulhsu_b1_i16x4(a, b);
}

/*
**test_pmulh_h0_i32x2:
** mulh.h0\ta[0-9],a[0-9],a[0-9]
** mulh.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulh_h0_i32x2(int32x2_t a, int16x4_t b)
{
  return __riscv_pmulh_h0_i32x2(a, b);
}

/*
**test_pmulh_h1_i32x2:
** mulh.h1\ta[0-9],a[0-9],a[0-9]
** mulh.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulh_h1_i32x2(int32x2_t a, int16x4_t b)
{
  return __riscv_pmulh_h1_i32x2(a, b);
}

/*
**test_pmulhsu_h0_i32x2:
** mulhsu.h0\ta[0-9],a[0-9],a[0-9]
** mulhsu.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulhsu_h0_i32x2(int32x2_t a, uint16x4_t b)
{
  return __riscv_pmulhsu_h0_i32x2(a, b);
}

/*
**test_pmulhsu_h1_i32x2:
** mulhsu.h1\ta[0-9],a[0-9],a[0-9]
** mulhsu.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulhsu_h1_i32x2(int32x2_t a, uint16x4_t b)
{
  return __riscv_pmulhsu_h1_i32x2(a, b);
}

/* Packed Multiply High Parts Accumulate (RV32, RMW)
   b-series i16x2 (single RMW insn): pmhacc.h.bN/pmhaccsu.h.bN.
   h-series i32 (scalar RMW): mhacc.hN/mhaccsu.hN.
   b-series i16x4 (2x split RMW): 2x pmhacc.h.bN.
   h-series i32x2 (2x split RMW): 2x mhacc.hN.  */

/*
**test_pmhacc_b0_i16x2:
** pmhacc.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhacc_b0_i16x2(int16x2_t rd, int16x2_t a, int8x4_t b)
{
  return __riscv_pmhacc_b0_i16x2(rd, a, b);
}

/*
**test_pmhacc_b1_i16x2:
** pmhacc.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhacc_b1_i16x2(int16x2_t rd, int16x2_t a, int8x4_t b)
{
  return __riscv_pmhacc_b1_i16x2(rd, a, b);
}

/*
**test_pmhaccsu_b0_i16x2:
** pmhaccsu.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhaccsu_b0_i16x2(int16x2_t rd, int16x2_t a, uint8x4_t b)
{
  return __riscv_pmhaccsu_b0_i16x2(rd, a, b);
}

/*
**test_pmhaccsu_b1_i16x2:
** pmhaccsu.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x2_t test_pmhaccsu_b1_i16x2(int16x2_t rd, int16x2_t a, uint8x4_t b)
{
  return __riscv_pmhaccsu_b1_i16x2(rd, a, b);
}

/*
**test_mhacc_h0_i32:
** mhacc.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mhacc_h0_i32(int32_t rd, int32_t a, int16x2_t b)
{
  return __riscv_mhacc_h0_i32(rd, a, b);
}

/*
**test_mhacc_h1_i32:
** mhacc.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mhacc_h1_i32(int32_t rd, int32_t a, int16x2_t b)
{
  return __riscv_mhacc_h1_i32(rd, a, b);
}

/*
**test_mhaccsu_h0_i32:
** mhaccsu.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mhaccsu_h0_i32(int32_t rd, int32_t a, uint16x2_t b)
{
  return __riscv_mhaccsu_h0_i32(rd, a, b);
}

/*
**test_mhaccsu_h1_i32:
** mhaccsu.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mhaccsu_h1_i32(int32_t rd, int32_t a, uint16x2_t b)
{
  return __riscv_mhaccsu_h1_i32(rd, a, b);
}

/*
**test_pmhacc_b0_i16x4:
** pmhacc.h.b0\ta[0-9],a[0-9],a[0-9]
** pmhacc.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhacc_b0_i16x4(int16x4_t rd, int16x4_t a, int8x8_t b)
{
  return __riscv_pmhacc_b0_i16x4(rd, a, b);
}

/*
**test_pmhacc_b1_i16x4:
** pmhacc.h.b1\ta[0-9],a[0-9],a[0-9]
** pmhacc.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhacc_b1_i16x4(int16x4_t rd, int16x4_t a, int8x8_t b)
{
  return __riscv_pmhacc_b1_i16x4(rd, a, b);
}

/*
**test_pmhaccsu_b0_i16x4:
** pmhaccsu.h.b0\ta[0-9],a[0-9],a[0-9]
** pmhaccsu.h.b0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhaccsu_b0_i16x4(int16x4_t rd, int16x4_t a, uint8x8_t b)
{
  return __riscv_pmhaccsu_b0_i16x4(rd, a, b);
}

/*
**test_pmhaccsu_b1_i16x4:
** pmhaccsu.h.b1\ta[0-9],a[0-9],a[0-9]
** pmhaccsu.h.b1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhaccsu_b1_i16x4(int16x4_t rd, int16x4_t a, uint8x8_t b)
{
  return __riscv_pmhaccsu_b1_i16x4(rd, a, b);
}

/*
**test_pmhacc_h0_i32x2:
** mhacc.h0\ta[0-9],a[0-9],a[0-9]
** mhacc.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhacc_h0_i32x2(int32x2_t rd, int32x2_t a, int16x4_t b)
{
  return __riscv_pmhacc_h0_i32x2(rd, a, b);
}

/*
**test_pmhacc_h1_i32x2:
** mhacc.h1\ta[0-9],a[0-9],a[0-9]
** mhacc.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhacc_h1_i32x2(int32x2_t rd, int32x2_t a, int16x4_t b)
{
  return __riscv_pmhacc_h1_i32x2(rd, a, b);
}

/*
**test_pmhaccsu_h0_i32x2:
** mhaccsu.h0\ta[0-9],a[0-9],a[0-9]
** mhaccsu.h0\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhaccsu_h0_i32x2(int32x2_t rd, int32x2_t a, uint16x4_t b)
{
  return __riscv_pmhaccsu_h0_i32x2(rd, a, b);
}

/*
**test_pmhaccsu_h1_i32x2:
** mhaccsu.h1\ta[0-9],a[0-9],a[0-9]
** mhaccsu.h1\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhaccsu_h1_i32x2(int32x2_t rd, int32x2_t a, uint16x4_t b)
{
  return __riscv_pmhaccsu_h1_i32x2(rd, a, b);
}

/* Packed Widening Multiply (RV32 single insn)
   pwmul.b/pwmul.h (signed), pwmulu.b/pwmulu.h (unsigned),
   pwmulsu.b/pwmulsu.h (signed x unsigned).  */

/*
**test_pwmul_i16x4:
** pwmul.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pwmul_i16x4(int8x4_t a, int8x4_t b)
{
  return __riscv_pwmul_i16x4(a, b);
}

/*
**test_pwmul_i32x2:
** pwmul.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwmul_i32x2(int16x2_t a, int16x2_t b)
{
  return __riscv_pwmul_i32x2(a, b);
}

/*
**test_pwmulu_u16x4:
** pwmulu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pwmulu_u16x4(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pwmulu_u16x4(a, b);
}

/*
**test_pwmulu_u32x2:
** pwmulu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwmulu_u32x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pwmulu_u32x2(a, b);
}

/*
**test_pwmulsu_i16x4:
** pwmulsu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pwmulsu_i16x4(int8x4_t a, uint8x4_t b)
{
  return __riscv_pwmulsu_i16x4(a, b);
}

/*
**test_pwmulsu_i32x2:
** pwmulsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwmulsu_i32x2(int16x2_t a, uint16x2_t b)
{
  return __riscv_pwmulsu_i32x2(a, b);
}

/* Packed Widening Multiply Accumulate (RV32 single RMW insn; RV64 TODO)
   pwmacc.h (signed), pwmaccu.h (unsigned), pwmaccsu.h (signed x unsigned).  */

/*
**test_pwmacc_i32x2:
** pwmacc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwmacc_i32x2(int32x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pwmacc_i32x2(rd, a, b);
}

/*
**test_pwmaccu_u32x2:
** pwmaccu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pwmaccu_u32x2(uint32x2_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pwmaccu_u32x2(rd, a, b);
}

/*
**test_pwmaccsu_i32x2:
** pwmaccsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pwmaccsu_i32x2(int32x2_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_pwmaccsu_i32x2(rd, a, b);
}

/* Packed "Q-format" Multiply with Widening Accumulate (RV32 single RMW insn; RV64 TODO)
   pmqwacc.h, pmqrwacc.h.  */

/*
**test_pmqwacc_i32x2:
** pmqwacc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqwacc_i32x2(int32x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pmqwacc_i32x2(rd, a, b);
}

/*
**test_pmqrwacc_i32x2:
** pmqrwacc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqrwacc_i32x2(int32x2_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pmqrwacc_i32x2(rd, a, b);
}

/* Packed Multiplication with Widening Horizontal Addition (RV32 single insn; RV64 TODO)
   pm2wadd.h/pm2wadd.hx/pm2waddu.h/pm2wsub.h/pm2wsub.hx/pm2waddsu.h.  */

/*
**test_pm2wadd_i64:
** pm2wadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wadd_i64(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wadd_i64(a, b);
}

/*
**test_pm2wadd_x_i64:
** pm2wadd.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wadd_x_i64(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wadd_x_i64(a, b);
}

/*
**test_pm2waddu_u64:
** pm2waddu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_pm2waddu_u64(uint16x2_t a, uint16x2_t b)
{
  return __riscv_pm2waddu_u64(a, b);
}

/*
**test_pm2wsub_i64:
** pm2wsub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wsub_i64(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wsub_i64(a, b);
}

/*
**test_pm2wsub_x_i64:
** pm2wsub.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wsub_x_i64(int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wsub_x_i64(a, b);
}

/*
**test_pm2waddsu_u64:
** pm2waddsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2waddsu_u64(int16x2_t a, uint16x2_t b)
{
  return __riscv_pm2waddsu_u64(a, b);
}

/* Packed Multiplication with Widening Horizontal Addition and Accumulate
   (RV32 single RMW insn; RV64 TODO)
   pm2wadda.h/pm2wadda.hx/pm2waddau.h/pm2wsuba.h/pm2wsuba.hx/pm2waddasu.h.  */

/*
**test_pm2wadda_i64:
** pm2wadda.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wadda_i64(int64_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wadda_i64(rd, a, b);
}

/*
**test_pm2wadda_x_i64:
** pm2wadda.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wadda_x_i64(int64_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wadda_x_i64(rd, a, b);
}

/*
**test_pm2waddau_u64:
** pm2waddau.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_pm2waddau_u64(uint64_t rd, uint16x2_t a, uint16x2_t b)
{
  return __riscv_pm2waddau_u64(rd, a, b);
}

/*
**test_pm2wsuba_i64:
** pm2wsuba.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wsuba_i64(int64_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wsuba_i64(rd, a, b);
}

/*
**test_pm2wsuba_x_i64:
** pm2wsuba.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2wsuba_x_i64(int64_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_pm2wsuba_x_i64(rd, a, b);
}

/*
**test_pm2waddasu_u64:
** pm2waddasu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_pm2waddasu_u64(int64_t rd, int16x2_t a, uint16x2_t b)
{
  return __riscv_pm2waddasu_u64(rd, a, b);
}
