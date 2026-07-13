/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */
/* { dg-final { check-function-bodies "**" "" "" } } */

#include <riscv_packed_simd.h>

/*
**test_abs_u32:
** ...
** absw\ta[0-9],a[0-9]
** ...
*/
uint32_t
test_abs_u32 (int32_t x)
{
  return __riscv_abs_u32 (x);
}

/*
**test_abs_u64:
** ...
** abs\ta[0-9],a[0-9]
** ...
*/
uint64_t
test_abs_u64 (int64_t x)
{
  return __riscv_abs_u64 (x);
}

/*
**test_cls_32:
** ...
** clsw\ta[0-9],a[0-9]
** ...
*/
unsigned
test_cls_32 (int32_t x)
{
  return __riscv_cls_32 (x);
}

/*
**test_cls_64:
** ...
** cls\ta[0-9],a[0-9]
** ...
*/
unsigned
test_cls_64 (int64_t x)
{
  return __riscv_cls_64 (x);
}

/*
**test_rev_64:
** ...
** rev\ta[0-9],a[0-9]
** ...
*/
uint64_t
test_rev_64 (uint64_t x)
{
  return __riscv_rev_64 (x);
}

/*
**test_rev16_64:
** ...
** rev16\ta[0-9],a[0-9]
** ...
*/
uint64_t
test_rev16_64 (uint64_t x)
{
  return __riscv_rev16_64 (x);
}

/*
**test_sha_i64:
** ...
** sha\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t
test_sha_i64 (int64_t x, int y)
{
  return __riscv_sha_i64 (x, y);
}

/*
**test_shar_i64:
** ...
** shar\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t
test_shar_i64 (int64_t x, int y)
{
  return __riscv_shar_i64 (x, y);
}

/*
**test_shl_u64:
** ...
** shl\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t
test_shl_u64 (uint64_t x, int y)
{
  return __riscv_shl_u64 (x, y);
}

/*
**test_shlr_u64:
** ...
** shlr\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t
test_shlr_u64 (uint64_t x, int y)
{
  return __riscv_shlr_u64 (x, y);
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
** pmv.bs\ta[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmv_s_u8x8(uint8_t x)
{
  return __riscv_pmv_s_u8x8(x);
}

/*
**test_pmv_s_i8x8:
** ...
** pmv.bs\ta[0-9],a[0-9]
** ...
*/
int8x8_t test_pmv_s_i8x8(int8_t x)
{
  return __riscv_pmv_s_i8x8(x);
}

/*
**test_pmv_s_u16x4:
** ...
** pmv.hs\ta[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmv_s_u16x4(uint16_t x)
{
  return __riscv_pmv_s_u16x4(x);
}

/*
**test_pmv_s_i16x4:
** ...
** pmv.hs\ta[0-9],a[0-9]
** ...
*/
int16x4_t test_pmv_s_i16x4(int16_t x)
{
  return __riscv_pmv_s_i16x4(x);
}

/*
**test_pmv_s_u32x2:
** ...
** pmv.ws\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmv_s_u32x2(uint32_t x)
{
  return __riscv_pmv_s_u32x2(x);
}

/*
**test_pmv_s_i32x2:
** ...
** pmv.ws\ta[0-9],a[0-9]
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
** padd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_padd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_padd_i8x8(a, b);
}

/*
**test_padd_u8x8:
** ...
** padd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_padd_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_padd_u8x8(a, b);
}

/*
**test_padd_i16x4:
** ...
** padd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_padd_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_padd_i16x4(a, b);
}

/*
**test_padd_u16x4:
** ...
** padd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_padd_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_padd_u16x4(a, b);
}

/*
**test_padd_i32x2:
** ...
** padd.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_padd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_padd_i32x2(a, b);
}

/*
**test_padd_u32x2:
** ...
** padd.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_padd_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_padd_u32x2(a, b);
}

/*
**test_psub_i8x8:
** ...
** psub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_psub_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_psub_i8x8(a, b);
}

/*
**test_psub_u8x8:
** ...
** psub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_psub_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_psub_u8x8(a, b);
}

/*
**test_psub_i16x4:
** ...
** psub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_psub_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_psub_i16x4(a, b);
}

/*
**test_psub_u16x4:
** ...
** psub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psub_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_psub_u16x4(a, b);
}

/*
**test_psub_i32x2:
** ...
** psub.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psub_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psub_i32x2(a, b);
}

/*
**test_psub_u32x2:
** ...
** psub.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psub_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_psub_u32x2(a, b);
}

/*
**test_pneg_i8x8:
** ...
** pneg.b\ta[0-9],a[0-9]
** ...
*/
int8x8_t test_pneg_i8x8(int8x8_t a)
{
  return __riscv_pneg_i8x8(a);
}

/*
**test_pneg_i16x4:
** ...
** pneg.h\ta[0-9],a[0-9]
** ...
*/
int16x4_t test_pneg_i16x4(int16x4_t a)
{
  return __riscv_pneg_i16x4(a);
}

/*
**test_pneg_i32x2:
** ...
** pneg.w\ta[0-9],a[0-9]
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
** padd.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_padd_s_u8x8(uint8x8_t a, uint8_t b)
{
  return __riscv_padd_s_u8x8(a, b);
}

/*
**test_padd_s_i8x8:
** ...
** padd.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_padd_s_i8x8(int8x8_t a, int8_t b)
{
  return __riscv_padd_s_i8x8(a, b);
}

/*
**test_padd_s_u16x4:
** ...
** padd.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_padd_s_u16x4(uint16x4_t a, uint16_t b)
{
  return __riscv_padd_s_u16x4(a, b);
}

/*
**test_padd_s_i16x4:
** ...
** padd.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_padd_s_i16x4(int16x4_t a, int16_t b)
{
  return __riscv_padd_s_i16x4(a, b);
}

/*
**test_padd_s_u32x2:
** ...
** padd.ws\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_padd_s_u32x2(uint32x2_t a, uint32_t b)
{
  return __riscv_padd_s_u32x2(a, b);
}

/*
**test_padd_s_i32x2:
** ...
** padd.ws\ta[0-9],a[0-9],a[0-9]
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
** psadd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_psadd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_psadd_i8x8(a, b);
}

/*
**test_psadd_i16x4:
** ...
** psadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_psadd_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_psadd_i16x4(a, b);
}

/*
**test_psadd_i32x2:
** ...
** psadd.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psadd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psadd_i32x2(a, b);
}

/*
**test_psaddu_u8x8:
** ...
** psaddu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_psaddu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_psaddu_u8x8(a, b);
}

/*
**test_psaddu_u16x4:
** ...
** psaddu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psaddu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_psaddu_u16x4(a, b);
}

/*
**test_psaddu_u32x2:
** ...
** psaddu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psaddu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_psaddu_u32x2(a, b);
}

/*
**test_pssub_i8x8:
** ...
** pssub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pssub_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pssub_i8x8(a, b);
}

/*
**test_pssub_i16x4:
** ...
** pssub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pssub_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pssub_i16x4(a, b);
}

/*
**test_pssub_i32x2:
** ...
** pssub.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pssub_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pssub_i32x2(a, b);
}

/*
**test_pssubu_u8x8:
** ...
** pssubu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pssubu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pssubu_u8x8(a, b);
}

/*
**test_pssubu_u16x4:
** ...
** pssubu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pssubu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pssubu_u16x4(a, b);
}

/*
**test_pssubu_u32x2:
** ...
** pssubu.w\ta[0-9],a[0-9],a[0-9]
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
** paadd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_paadd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_paadd_i8x8(a, b);
}

/*
**test_paadd_i16x4:
** ...
** paadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_paadd_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_paadd_i16x4(a, b);
}

/*
**test_paadd_i32x2:
** ...
** paadd.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_paadd_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_paadd_i32x2(a, b);
}

/*
**test_paaddu_u8x8:
** ...
** paaddu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_paaddu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_paaddu_u8x8(a, b);
}

/*
**test_paaddu_u16x4:
** ...
** paaddu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_paaddu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_paaddu_u16x4(a, b);
}

/*
**test_paaddu_u32x2:
** ...
** paaddu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_paaddu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_paaddu_u32x2(a, b);
}

/*
**test_pasub_i8x8:
** ...
** pasub.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pasub_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pasub_i8x8(a, b);
}

/*
**test_pasub_i16x4:
** ...
** pasub.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pasub_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pasub_i16x4(a, b);
}

/*
**test_pasub_i32x2:
** ...
** pasub.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pasub_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pasub_i32x2(a, b);
}

/*
**test_pasubu_u8x8:
** ...
** pasubu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pasubu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pasubu_u8x8(a, b);
}

/*
**test_pasubu_u16x4:
** ...
** pasubu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pasubu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pasubu_u16x4(a, b);
}

/*
**test_pasubu_u32x2:
** ...
** pasubu.w\ta[0-9],a[0-9],a[0-9]
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
**test_psh1add_i16x4:
** ...
** psh1add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_psh1add_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_psh1add_i16x4(a, b);
}

/*
**test_psh1add_u16x4:
** ...
** psh1add.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psh1add_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_psh1add_u16x4(a, b);
}

/*
**test_psh1add_i32x2:
** ...
** psh1add.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psh1add_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psh1add_i32x2(a, b);
}

/*
**test_psh1add_u32x2:
** ...
** psh1add.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psh1add_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_psh1add_u32x2(a, b);
}

/*
**test_pssh1sadd_i16x4:
** ...
** pssh1sadd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pssh1sadd_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pssh1sadd_i16x4(a, b);
}

/*
**test_pssh1sadd_i32x2:
** ...
** pssh1sadd.w\ta[0-9],a[0-9],a[0-9]
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
**test_pas_x_i16x4:
** ...
** pas.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pas_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pas_x_i16x4(a, b);
}

/*
**test_pas_x_i32x2:
** ...
** pas.wx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pas_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pas_x_i32x2(a, b);
}

/*
**test_psa_x_i16x4:
** ...
** psa.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_psa_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_psa_x_i16x4(a, b);
}

/*
**test_psa_x_i32x2:
** ...
** psa.wx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psa_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psa_x_i32x2(a, b);
}

/*
**test_psas_x_i16x4:
** ...
** psas.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_psas_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_psas_x_i16x4(a, b);
}

/*
**test_psas_x_i32x2:
** ...
** psas.wx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_psas_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_psas_x_i32x2(a, b);
}

/*
**test_pssa_x_i16x4:
** ...
** pssa.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pssa_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pssa_x_i16x4(a, b);
}

/*
**test_pssa_x_i32x2:
** ...
** pssa.wx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pssa_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pssa_x_i32x2(a, b);
}

/*
**test_paas_x_i16x4:
** ...
** paas.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_paas_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_paas_x_i16x4(a, b);
}

/*
**test_paas_x_i32x2:
** ...
** paas.wx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_paas_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_paas_x_i32x2(a, b);
}

/*
**test_pasa_x_i16x4:
** ...
** pasa.hx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pasa_x_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pasa_x_i16x4(a, b);
}

/*
**test_pasa_x_i32x2:
** ...
** pasa.wx\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pasa_x_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pasa_x_i32x2(a, b);
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
** pabd.b\ta[0-9],a[0-9],x0
** ...
*/
uint8x8_t test_pabs_i8x8(int8x8_t a)
{
  return __riscv_pabs_i8x8(a);
}

/*
**test_pabs_i16x4:
** ...
** pabd.h\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pabs_i16x4(int16x4_t a)
{
  return __riscv_pabs_i16x4(a);
}

/*
**test_pabd_i8x8:
** ...
** pabd.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pabd_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pabd_i8x8(a, b);
}

/*
**test_pabd_i16x4:
** ...
** pabd.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pabd_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pabd_i16x4(a, b);
}

/*
**test_pabdu_u8x8:
** ...
** pabdu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pabdu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdu_u8x8(a, b);
}

/*
**test_pabdu_u16x4:
** ...
** pabdu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pabdu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pabdu_u16x4(a, b);
}

// TODO(difficult): Packed Absolute Difference Sum

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
** psabs.b\ta[0-9],a[0-9]
** ...
*/
int8x8_t test_psabs_i8x8(int8x8_t a)
{
  return __riscv_psabs_i8x8(a);
}

/*
**test_psabs_i16x4:
** ...
** psabs.h\ta[0-9],a[0-9]
** ...
*/
int16x4_t test_psabs_i16x4(int16x4_t a)
{
  return __riscv_psabs_i16x4(a);
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
** predsum.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_predsum_i8x8_i32(int8x8_t a, int32_t b)
{
  return __riscv_predsum_i8x8_i32(a, b);
}

/*
**test_predsumu_u8x8_u32:
** ...
** predsumu.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_predsumu_u8x8_u32(uint8x8_t a, uint32_t b)
{
  return __riscv_predsumu_u8x8_u32(a, b);
}

/*
**test_predsum_i16x4_i32:
** ...
** predsum.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_predsum_i16x4_i32(int16x4_t a, int32_t b)
{
  return __riscv_predsum_i16x4_i32(a, b);
}

/*
**test_predsumu_u16x4_u32:
** ...
** predsumu.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32_t test_predsumu_u16x4_u32(uint16x4_t a, uint32_t b)
{
  return __riscv_predsumu_u16x4_u32(a, b);
}

/*
**test_predsum_i8x8_i64:
** ...
** predsum.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_predsum_i8x8_i64(int8x8_t a, int64_t b)
{
  return __riscv_predsum_i8x8_i64(a, b);
}

/*
**test_predsumu_u8x8_u64:
** ...
** predsumu.bs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_predsumu_u8x8_u64(uint8x8_t a, uint64_t b)
{
  return __riscv_predsumu_u8x8_u64(a, b);
}

/*
**test_predsum_i16x4_i64:
** ...
** predsum.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_predsum_i16x4_i64(int16x4_t a, int64_t b)
{
  return __riscv_predsum_i16x4_i64(a, b);
}

/*
**test_predsumu_u16x4_u64:
** ...
** predsumu.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_predsumu_u16x4_u64(uint16x4_t a, uint64_t b)
{
  return __riscv_predsumu_u16x4_u64(a, b);
}

/*
**test_predsum_i32x2_i64:
** ...
** predsum.ws\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_predsum_i32x2_i64(int32x2_t a, int64_t b)
{
  return __riscv_predsum_i32x2_i64(a, b);
}

/*
**test_predsumu_u32x2_u64:
** ...
** predsumu.ws\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint64_t test_predsumu_u32x2_u64(uint32x2_t a, uint64_t b)
{
  return __riscv_predsumu_u32x2_u64(a, b);
}

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
** pmin.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pmin_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmin_i8x8(a, b);
}

/*
**test_pmin_i16x4:
** ...
** pmin.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmin_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmin_i16x4(a, b);
}

/*
**test_pmin_i32x2:
** ...
** pmin.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmin_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmin_i32x2(a, b);
}

/*
**test_pminu_u8x8:
** ...
** pminu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pminu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pminu_u8x8(a, b);
}

/*
**test_pminu_u16x4:
** ...
** pminu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pminu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pminu_u16x4(a, b);
}

/*
**test_pminu_u32x2:
** ...
** pminu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pminu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pminu_u32x2(a, b);
}

/*
**test_pmax_i8x8:
** ...
** pmax.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pmax_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmax_i8x8(a, b);
}

/*
**test_pmax_i16x4:
** ...
** pmax.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmax_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmax_i16x4(a, b);
}

/*
**test_pmax_i32x2:
** ...
** pmax.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmax_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmax_i32x2(a, b);
}

/*
**test_pmaxu_u8x8:
** ...
** pmaxu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmaxu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmaxu_u8x8(a, b);
}

/*
**test_pmaxu_u16x4:
** ...
** pmaxu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmaxu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmaxu_u16x4(a, b);
}

/*
**test_pmaxu_u32x2:
** ...
** pmaxu.w\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.b\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.b\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.b\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.b\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.h\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.h\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.h\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.h\ta[0-9],a[0-9],a[0-9]
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
** pmseq.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmseq_i8x8_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmseq_i8x8_u8x8(a, b);
}

/*
**test_pmseq_u8x8_u8x8:
** ...
** pmseq.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmseq_u8x8_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmseq_u8x8_u8x8(a, b);
}

/*
**test_pmslt_u8x8:
** ...
** pmslt.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmslt_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmslt_u8x8(a, b);
}

/*
**test_pmsgt_u8x8:
** ...
** pmsgt.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsgt_u8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_pmsgt_u8x8(a, b);
}

/*
**test_pmsltu_u8x8:
** ...
** pmsltu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsltu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsltu_u8x8(a, b);
}

/*
**test_pmsgtu_u8x8:
** ...
** pmsgtu.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pmsgtu_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_pmsgtu_u8x8(a, b);
}

/*
**test_pmsne_i8x8_u8x8:
** ...
** pmseq.b\ta[0-9],a[0-9],a[0-9]
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
** pmseq.b\ta[0-9],a[0-9],a[0-9]
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
** pmslt.b\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.b\ta[0-9],a[0-9],a[0-9]
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
** pmsltu.b\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.b\ta[0-9],a[0-9],a[0-9]
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
** pmseq.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmseq_i16x4_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmseq_i16x4_u16x4(a, b);
}

/*
**test_pmseq_u16x4_u16x4:
** ...
** pmseq.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmseq_u16x4_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmseq_u16x4_u16x4(a, b);
}

/*
**test_pmslt_u16x4:
** ...
** pmslt.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmslt_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmslt_u16x4(a, b);
}

/*
**test_pmsgt_u16x4:
** ...
** pmsgt.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsgt_u16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmsgt_u16x4(a, b);
}

/*
**test_pmsltu_u16x4:
** ...
** pmsltu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsltu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsltu_u16x4(a, b);
}

/*
**test_pmsgtu_u16x4:
** ...
** pmsgtu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmsgtu_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmsgtu_u16x4(a, b);
}

/*
**test_pmsne_i16x4_u16x4:
** ...
** pmseq.h\ta[0-9],a[0-9],a[0-9]
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
** pmseq.h\ta[0-9],a[0-9],a[0-9]
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
** pmslt.h\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.h\ta[0-9],a[0-9],a[0-9]
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
** pmsltu.h\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.h\ta[0-9],a[0-9],a[0-9]
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
** pmseq.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmseq_i32x2_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmseq_i32x2_u32x2(a, b);
}

/*
**test_pmseq_u32x2_u32x2:
** ...
** pmseq.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmseq_u32x2_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmseq_u32x2_u32x2(a, b);
}

/*
**test_pmslt_u32x2:
** ...
** pmslt.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmslt_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmslt_u32x2(a, b);
}

/*
**test_pmsgt_u32x2:
** ...
** pmsgt.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsgt_u32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmsgt_u32x2(a, b);
}

/*
**test_pmsltu_u32x2:
** ...
** pmsltu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsltu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsltu_u32x2(a, b);
}

/*
**test_pmsgtu_u32x2:
** ...
** pmsgtu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsgtu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsgtu_u32x2(a, b);
}

/*
**test_pmsne_i32x2_u32x2:
** ...
** pmseq.w\ta[0-9],a[0-9],a[0-9]
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
** pmseq.w\ta[0-9],a[0-9],a[0-9]
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
** pmslt.w\ta[0-9],a[0-9],a[0-9]
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
** pmsgt.w\ta[0-9],a[0-9],a[0-9]
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
** pmsltu.w\ta[0-9],a[0-9],a[0-9]
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
** pmsgtu.w\ta[0-9],a[0-9],a[0-9]
** not\ta[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmsleu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmsleu_u32x2(a, b);
}

/* Packed Merge */
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

/*
**test_pmerge_u8x8:
** ...
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
** ...
*/
uint16x4_t test_pmerge_u16x4(uint16x4_t a, uint16x4_t b, uint16x4_t m)
{
  return __riscv_pmerge_u16x4(a, b, m);
}

/*
**test_pmerge_i16x4:
** ...
** (mvm|merge|mvmn)\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmerge_i16x4(int16x4_t a, int16x4_t b, uint16x4_t m)
{
  return __riscv_pmerge_i16x4(a, b, m);
}

/*
**test_pmerge_u32x2:
** ...
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
**test_psext_b_i16x4:
** ...
** psext.h.b\ta[0-9],a[0-9]
** ...
*/
int16x4_t test_psext_b_i16x4(int16x4_t a)
{
  return __riscv_psext_b_i16x4(a);
}

/*
**test_psext_b_i32x2:
** ...
** psext.w.b\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_psext_b_i32x2(int32x2_t a)
{
  return __riscv_psext_b_i32x2(a);
}

/*
**test_psext_h_i32x2:
** ...
** psext.w.h\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_psext_h_i32x2(int32x2_t a)
{
  return __riscv_psext_h_i32x2(a);
}

/*
**test_pzext_b_u16x4:
** ...
** ppaire.b\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pzext_b_u16x4(uint16x4_t a)
{
  return __riscv_pzext_b_u16x4(a);
}

/*
**test_pzext_h_u32x2:
** ...
** ppaire.h\ta[0-9],a[0-9],x0
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
** pslli.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint8x8_t test_psll_s_u8x8(uint8x8_t a)
{
  return __riscv_psll_s_u8x8(a, 3);
}

/*
**test_psll_s_i8x8:
** ...
** pslli.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
int8x8_t test_psll_s_i8x8(int8x8_t a)
{
  return __riscv_psll_s_i8x8(a, 3);
}

/*
**test_psll_s_u16x4:
** ...
** pslli.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint16x4_t test_psll_s_u16x4(uint16x4_t a)
{
  return __riscv_psll_s_u16x4(a, 3);
}

/*
**test_psll_s_i16x4:
** ...
** pslli.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x4_t test_psll_s_i16x4(int16x4_t a)
{
  return __riscv_psll_s_i16x4(a, 3);
}

/*
**test_psll_s_u32x2:
** ...
** pslli.w\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint32x2_t test_psll_s_u32x2(uint32x2_t a)
{
  return __riscv_psll_s_u32x2(a, 3);
}

/*
**test_psll_s_i32x2:
** ...
** pslli.w\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_psll_s_i32x2(int32x2_t a)
{
  return __riscv_psll_s_i32x2(a, 3);
}

/*
**test_psrl_s_u8x8:
** ...
** psrli.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint8x8_t test_psrl_s_u8x8(uint8x8_t a)
{
  return __riscv_psrl_s_u8x8(a, 3);
}

/*
**test_psrl_s_u16x4:
** ...
** psrli.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint16x4_t test_psrl_s_u16x4(uint16x4_t a)
{
  return __riscv_psrl_s_u16x4(a, 3);
}

/*
**test_psrl_s_u32x2:
** ...
** psrli.w\ta[0-9],a[0-9],[0-9]+
** ...
*/
uint32x2_t test_psrl_s_u32x2(uint32x2_t a)
{
  return __riscv_psrl_s_u32x2(a, 3);
}

/*
**test_psra_s_i8x8:
** ...
** psrai.b\ta[0-9],a[0-9],[0-9]+
** ...
*/
int8x8_t test_psra_s_i8x8(int8x8_t a)
{
  return __riscv_psra_s_i8x8(a, 3);
}

/*
**test_psra_s_i16x4:
** ...
** psrai.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x4_t test_psra_s_i16x4(int16x4_t a)
{
  return __riscv_psra_s_i16x4(a, 3);
}

/*
**test_psra_s_i32x2:
** ...
** psrai.w\ta[0-9],a[0-9],[0-9]+
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
**test_pssha_s_i16x4:
** ...
** psrai.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x4_t test_pssha_s_i16x4(int16x4_t a)
{
  return __riscv_pssha_s_i16x4(a, -3);
}

/*
**test_pssha_s_i32x2:
** ...
** psrai.w\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_pssha_s_i32x2(int32x2_t a)
{
  return __riscv_pssha_s_i32x2(a, -3);
}

/*
**test_psshar_s_i16x4:
** ...
** psrari.h\ta[0-9],a[0-9],[0-9]+
** ...
*/
int16x4_t test_psshar_s_i16x4(int16x4_t a)
{
  return __riscv_psshar_s_i16x4(a, -3);
}

/*
**test_psshar_s_i32x2:
** ...
** psrari.w\ta[0-9],a[0-9],[0-9]+
** ...
*/
int32x2_t test_psshar_s_i32x2(int32x2_t a)
{
  return __riscv_psshar_s_i32x2(a, -3);
}

/*
**test_psshl_s_u16x4:
** ...
** psshl.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psshl_s_u16x4(uint16x4_t a)
{
  return __riscv_psshl_s_u16x4(a, 3);
}

/*
**test_psshl_s_u32x2:
** ...
** psshl.ws\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_psshl_s_u32x2(uint32x2_t a)
{
  return __riscv_psshl_s_u32x2(a, 3);
}

/*
**test_psshlr_s_u16x4:
** ...
** psshlr.hs\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_psshlr_s_u16x4(uint16x4_t a)
{
  return __riscv_psshlr_s_u16x4(a, 3);
}

/*
**test_psshlr_s_u32x2:
** ...
** psshlr.ws\ta[0-9],a[0-9],a[0-9]
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
** ppaire.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x2_t test_ppaire_u16x2(uint16x2_t a, uint16x2_t b)
{
  return __riscv_ppaire_u16x2(a, b);
}

/*
**test_ppaire_i16x2:
** ...
** ppaire.h\ta[0-9],a[0-9],a[0-9]
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
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppaire_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppaire_u8x8(a, b);
}

/*
**test_ppaire_i8x8:
** ...
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppaire_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppaire_i8x8(a, b);
}

/*
**test_ppaireo_u8x8:
** ...
** ppaireo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppaireo_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppaireo_u8x8(a, b);
}

/*
**test_ppaireo_i8x8:
** ...
** ppaireo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppaireo_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppaireo_i8x8(a, b);
}

/*
**test_ppairoe_u8x8:
** ...
** ppairoe.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppairoe_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppairoe_u8x8(a, b);
}

/*
**test_ppairoe_i8x8:
** ...
** ppairoe.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppairoe_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppairoe_i8x8(a, b);
}

/*
**test_ppairo_u8x8:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_ppairo_u8x8(uint8x8_t a, uint8x8_t b)
{
  return __riscv_ppairo_u8x8(a, b);
}

/*
**test_ppairo_i8x8:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_ppairo_i8x8(int8x8_t a, int8x8_t b)
{
  return __riscv_ppairo_i8x8(a, b);
}

/*
**test_ppaire_u16x4:
** ...
** ppaire.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppaire_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppaire_u16x4(a, b);
}

/*
**test_ppaire_i16x4:
** ...
** ppaire.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_ppaire_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_ppaire_i16x4(a, b);
}

/*
**test_ppaireo_u16x4:
** ...
** ppaireo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppaireo_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppaireo_u16x4(a, b);
}

/*
**test_ppaireo_i16x4:
** ...
** ppaireo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_ppaireo_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_ppaireo_i16x4(a, b);
}

/*
**test_ppairoe_u16x4:
** ...
** ppairoe.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppairoe_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppairoe_u16x4(a, b);
}

/*
**test_ppairoe_i16x4:
** ...
** ppairoe.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_ppairoe_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_ppairoe_i16x4(a, b);
}

/*
**test_ppairo_u16x4:
** ...
** ppairo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_ppairo_u16x4(uint16x4_t a, uint16x4_t b)
{
  return __riscv_ppairo_u16x4(a, b);
}

/*
**test_ppairo_i16x4:
** ...
** ppairo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_ppairo_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_ppairo_i16x4(a, b);
}

/*
**test_ppaire_u32x2:
** ...
** pack\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_ppaire_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_ppaire_u32x2(a, b);
}

/*
**test_ppaire_i32x2:
** ...
** pack\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_ppaire_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_ppaire_i32x2(a, b);
}

/*
**test_ppaireo_u32x2:
** ...
** ppaireo.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_ppaireo_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_ppaireo_u32x2(a, b);
}

/*
**test_ppaireo_i32x2:
** ...
** ppaireo.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_ppaireo_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_ppaireo_i32x2(a, b);
}

/*
**test_ppairoe_u32x2:
** ...
** ppairoe.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_ppairoe_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_ppairoe_u32x2(a, b);
}

/*
**test_ppairoe_i32x2:
** ...
** ppairoe.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_ppairoe_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_ppairoe_i32x2(a, b);
}

/*
**test_ppairo_u32x2:
** ...
** ppairo.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_ppairo_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_ppairo_u32x2(a, b);
}

/*
**test_ppairo_i32x2:
** ...
** ppairo.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_ppairo_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_ppairo_i32x2(a, b);
}

/* Packed Widening Convert */

/*
**test_pwcvt_i16x4:
** ...
** zip8p\ta[0-9],a[0-9],x0
** psext.h.b\ta[0-9],a[0-9]
** ...
*/
int16x4_t test_pwcvt_i16x4(int8x4_t a)
{
  return __riscv_pwcvt_i16x4(a);
}

/*
**test_pwcvt_i32x2:
** ...
** zip16p\ta[0-9],a[0-9],x0
** psext.w.h\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_pwcvt_i32x2(int16x2_t a)
{
  return __riscv_pwcvt_i32x2(a);
}

/*
**test_pwcvtu_u16x4:
** ...
** zip8p\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pwcvtu_u16x4(uint8x4_t a)
{
  return __riscv_pwcvtu_u16x4(a);
}

/*
**test_pwcvtu_u32x2:
** ...
** zip16p\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pwcvtu_u32x2(uint16x2_t a)
{
  return __riscv_pwcvtu_u32x2(a);
}

/*
**test_pwcvth_i16x4:
** ...
** zip8p\ta[0-9],x0,a[0-9]
** ...
*/
int16x4_t test_pwcvth_i16x4(int8x4_t a)
{
  return __riscv_pwcvth_i16x4(a);
}

/*
**test_pwcvth_u16x4:
** ...
** zip8p\ta[0-9],x0,a[0-9]
** ...
*/
uint16x4_t test_pwcvth_u16x4(uint8x4_t a)
{
  return __riscv_pwcvth_u16x4(a);
}

/*
**test_pwcvth_i32x2:
** ...
** zip16p\ta[0-9],x0,a[0-9]
** ...
*/
int32x2_t test_pwcvth_i32x2(int16x2_t a)
{
  return __riscv_pwcvth_i32x2(a);
}

/*
**test_pwcvth_u32x2:
** ...
** zip16p\ta[0-9],x0,a[0-9]
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
** unzip8p\ta[0-9],a[0-9],x0
** ...
*/
int8x4_t test_pncvt_i8x4(int16x4_t a)
{
  return __riscv_pncvt_i8x4(a);
}

/*
**test_pncvt_u8x4:
** ...
** unzip8p\ta[0-9],a[0-9],x0
** ...
*/
uint8x4_t test_pncvt_u8x4(uint16x4_t a)
{
  return __riscv_pncvt_u8x4(a);
}

/*
**test_pncvt_i16x2:
** ...
** unzip16p\ta[0-9],a[0-9],x0
** ...
*/
int16x2_t test_pncvt_i16x2(int32x2_t a)
{
  return __riscv_pncvt_i16x2(a);
}

/*
**test_pncvt_u16x2:
** ...
** unzip16p\ta[0-9],a[0-9],x0
** ...
*/
uint16x2_t test_pncvt_u16x2(uint32x2_t a)
{
  return __riscv_pncvt_u16x2(a);
}

/*
**test_pncvth_i8x4:
** ...
** unzip8hp\ta[0-9],a[0-9],x0
** ...
*/
int8x4_t test_pncvth_i8x4(int16x4_t a)
{
  return __riscv_pncvth_i8x4(a);
}

/*
**test_pncvth_u8x4:
** ...
** unzip8hp\ta[0-9],a[0-9],x0
** ...
*/
uint8x4_t test_pncvth_u8x4(uint16x4_t a)
{
  return __riscv_pncvth_u8x4(a);
}

/*
**test_pncvth_i16x2:
** ...
** unzip16hp\ta[0-9],a[0-9],x0
** ...
*/
int16x2_t test_pncvth_i16x2(int32x2_t a)
{
  return __riscv_pncvth_i16x2(a);
}

/*
**test_pncvth_u16x2:
** ...
** unzip16hp\ta[0-9],a[0-9],x0
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
** zip8p\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pzip_i8x8(int8x4_t a, int8x4_t b)
{
  return __riscv_pzip_i8x8(a, b);
}

/*
**test_pzip_u8x8:
** ...
** zip8p\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pzip_u8x8(uint8x4_t a, uint8x4_t b)
{
  return __riscv_pzip_u8x8(a, b);
}

/*
**test_pzip_i16x4:
** ...
** zip16p\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pzip_i16x4(int16x2_t a, int16x2_t b)
{
  return __riscv_pzip_i16x4(a, b);
}

/*
**test_pzip_u16x4:
** ...
** zip16p\ta[0-9],a[0-9],a[0-9]
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
** unzip8p\ta[0-9],a[0-9],x0
** ...
*/
int8x4_t test_punzipe_i8x4(int8x8_t a)
{
  return __riscv_punzipe_i8x4(a);
}

/*
**test_punzipe_u8x4:
** ...
** unzip8p\ta[0-9],a[0-9],x0
** ...
*/
uint8x4_t test_punzipe_u8x4(uint8x8_t a)
{
  return __riscv_punzipe_u8x4(a);
}

/*
**test_punzipo_i8x4:
** ...
** unzip8hp\ta[0-9],a[0-9],x0
** ...
*/
int8x4_t test_punzipo_i8x4(int8x8_t a)
{
  return __riscv_punzipo_i8x4(a);
}

/*
**test_punzipo_u8x4:
** ...
** unzip8hp\ta[0-9],a[0-9],x0
** ...
*/
uint8x4_t test_punzipo_u8x4(uint8x8_t a)
{
  return __riscv_punzipo_u8x4(a);
}

/*
**test_punzipe_i16x2:
** ...
** unzip16p\ta[0-9],a[0-9],x0
** ...
*/
int16x2_t test_punzipe_i16x2(int16x4_t a)
{
  return __riscv_punzipe_i16x2(a);
}

/*
**test_punzipe_u16x2:
** ...
** unzip16p\ta[0-9],a[0-9],x0
** ...
*/
uint16x2_t test_punzipe_u16x2(uint16x4_t a)
{
  return __riscv_punzipe_u16x2(a);
}

/*
**test_punzipo_i16x2:
** ...
** unzip16hp\ta[0-9],a[0-9],x0
** ...
*/
int16x2_t test_punzipo_i16x2(int16x4_t a)
{
  return __riscv_punzipo_i16x2(a);
}

/*
**test_punzipo_u16x2:
** ...
** unzip16hp\ta[0-9],a[0-9],x0
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
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pnzip_i8x8(int16x4_t a, int16x4_t b)
{
  return __riscv_pnzip_i8x8(a, b);
}

/*
**test_pnzip_u8x8:
** ...
** ppaire.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pnzip_u8x8(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pnzip_u8x8(a, b);
}

/*
**test_pnziph_i8x8:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
int8x8_t test_pnziph_i8x8(int16x4_t a, int16x4_t b)
{
  return __riscv_pnziph_i8x8(a, b);
}

/*
**test_pnziph_u8x8:
** ...
** ppairo.b\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint8x8_t test_pnziph_u8x8(uint16x4_t a, uint16x4_t b)
{
  return __riscv_pnziph_u8x8(a, b);
}

/*
**test_pnzip_i16x4:
** ...
** ppaire.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pnzip_i16x4(int32x2_t a, int32x2_t b)
{
  return __riscv_pnzip_i16x4(a, b);
}

/*
**test_pnzip_u16x4:
** ...
** ppaire.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pnzip_u16x4(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pnzip_u16x4(a, b);
}

/*
**test_pnziph_i16x4:
** ...
** ppairo.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pnziph_i16x4(int32x2_t a, int32x2_t b)
{
  return __riscv_pnziph_i16x4(a, b);
}

/*
**test_pnziph_u16x4:
** ...
** ppairo.h\ta[0-9],a[0-9],a[0-9]
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
**test_pwunzipe_i16x4:
** ...
** psext.h.b\ta[0-9],a[0-9]
** ...
*/
int16x4_t test_pwunzipe_i16x4(int8x8_t a)
{
  return __riscv_pwunzipe_i16x4(a);
}

/*
**test_pwunzipo_i16x4:
** ...
** psrai.h\ta[0-9],a[0-9],8
** ...
*/
int16x4_t test_pwunzipo_i16x4(int8x8_t a)
{
  return __riscv_pwunzipo_i16x4(a);
}

/*
**test_pwunzipue_u16x4:
** ...
** ppaire.b\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pwunzipue_u16x4(uint8x8_t a)
{
  return __riscv_pwunzipue_u16x4(a);
}

/*
**test_pwunzipuo_u16x4:
** ...
** ppairo.b\ta[0-9],a[0-9],x0
** ...
*/
uint16x4_t test_pwunzipuo_u16x4(uint8x8_t a)
{
  return __riscv_pwunzipuo_u16x4(a);
}

/*
**test_pwunziphe_i16x4:
** ...
** pslli.h\ta[0-9],a[0-9],8
** ...
*/
int16x4_t test_pwunziphe_i16x4(int8x8_t a)
{
  return __riscv_pwunziphe_i16x4(a);
}

/*
**test_pwunziphe_u16x4:
** ...
** pslli.h\ta[0-9],a[0-9],8
** ...
*/
uint16x4_t test_pwunziphe_u16x4(uint8x8_t a)
{
  return __riscv_pwunziphe_u16x4(a);
}

/*
**test_pwunzipho_i16x4:
** ...
** ppairo.b\ta[0-9],x0,a[0-9]
** ...
*/
int16x4_t test_pwunzipho_i16x4(int8x8_t a)
{
  return __riscv_pwunzipho_i16x4(a);
}

/*
**test_pwunzipho_u16x4:
** ...
** ppairo.b\ta[0-9],x0,a[0-9]
** ...
*/
uint16x4_t test_pwunzipho_u16x4(uint8x8_t a)
{
  return __riscv_pwunzipho_u16x4(a);
}

/*
**test_pwunzipe_i32x2:
** ...
** psext.w.h\ta[0-9],a[0-9]
** ...
*/
int32x2_t test_pwunzipe_i32x2(int16x4_t a)
{
  return __riscv_pwunzipe_i32x2(a);
}

/*
**test_pwunzipo_i32x2:
** ...
** psrai.w\ta[0-9],a[0-9],16
** ...
*/
int32x2_t test_pwunzipo_i32x2(int16x4_t a)
{
  return __riscv_pwunzipo_i32x2(a);
}

/*
**test_pwunzipue_u32x2:
** ...
** ppaire.h\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pwunzipue_u32x2(uint16x4_t a)
{
  return __riscv_pwunzipue_u32x2(a);
}

/*
**test_pwunzipuo_u32x2:
** ...
** ppairo.h\ta[0-9],a[0-9],x0
** ...
*/
uint32x2_t test_pwunzipuo_u32x2(uint16x4_t a)
{
  return __riscv_pwunzipuo_u32x2(a);
}

/*
**test_pwunziphe_i32x2:
** ...
** pslli.w\ta[0-9],a[0-9],16
** ...
*/
int32x2_t test_pwunziphe_i32x2(int16x4_t a)
{
  return __riscv_pwunziphe_i32x2(a);
}

/*
**test_pwunziphe_u32x2:
** ...
** pslli.w\ta[0-9],a[0-9],16
** ...
*/
uint32x2_t test_pwunziphe_u32x2(uint16x4_t a)
{
  return __riscv_pwunziphe_u32x2(a);
}

/*
**test_pwunzipho_i32x2:
** ...
** ppairo.h\ta[0-9],x0,a[0-9]
** ...
*/
int32x2_t test_pwunzipho_i32x2(int16x4_t a)
{
  return __riscv_pwunzipho_i32x2(a);
}

/*
**test_pwunzipho_u32x2:
** ...
** ppairo.h\ta[0-9],x0,a[0-9]
** ...
*/
uint32x2_t test_pwunzipho_u32x2(uint16x4_t a)
{
  return __riscv_pwunzipho_u32x2(a);
}

/* Packed Widening Shift (RV64 TODO) */

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

/* Packed Multiply High 64-bit (RV64 single insn) */

/*
**test_pmulh_i16x4:
** ...
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
** ...
*/
int16x4_t test_pmulhrsu_i16x4(int16x4_t a, uint16x4_t b)
{
  return __riscv_pmulhrsu_i16x4(a, b);
}

/* Packed Multiply High 64-bit i32x2 (RV64 single pmulh.w; RV32 TODO) */

/*
**test_pmulh_i32x2:
** ...
** pmulh.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulh_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmulh_i32x2(a, b);
}

/*
**test_pmulhr_i32x2:
** ...
** pmulhr.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulhr_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmulhr_i32x2(a, b);
}

/*
**test_pmulhu_u32x2:
** ...
** pmulhu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmulhu_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmulhu_u32x2(a, b);
}

/*
**test_pmulhru_u32x2:
** ...
** pmulhru.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmulhru_u32x2(uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmulhru_u32x2(a, b);
}

/*
**test_pmulhsu_i32x2:
** ...
** pmulhsu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulhsu_i32x2(int32x2_t a, uint32x2_t b)
{
  return __riscv_pmulhsu_i32x2(a, b);
}

/*
**test_pmulhrsu_i32x2:
** ...
** pmulhrsu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulhrsu_i32x2(int32x2_t a, uint32x2_t b)
{
  return __riscv_pmulhrsu_i32x2(a, b);
}

/* Packed Multiply High Accumulate (RV64 single insn) */

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

/*
**test_pmhacc_i16x4:
** ...
** pmhacc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhacc_i16x4(int16x4_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmhacc_i16x4(rd, a, b);
}

/*
**test_pmhracc_i16x4:
** ...
** pmhracc.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhracc_i16x4(int16x4_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmhracc_i16x4(rd, a, b);
}

/*
**test_pmhaccu_u16x4:
** ...
** pmhaccu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmhaccu_u16x4(uint16x4_t rd, uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmhaccu_u16x4(rd, a, b);
}

/*
**test_pmhraccu_u16x4:
** ...
** pmhraccu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint16x4_t test_pmhraccu_u16x4(uint16x4_t rd, uint16x4_t a, uint16x4_t b)
{
  return __riscv_pmhraccu_u16x4(rd, a, b);
}

/*
**test_pmhaccsu_i16x4:
** ...
** pmhaccsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhaccsu_i16x4(int16x4_t rd, int16x4_t a, uint16x4_t b)
{
  return __riscv_pmhaccsu_i16x4(rd, a, b);
}

/*
**test_pmhraccsu_i16x4:
** ...
** pmhraccsu.h\ta[0-9],a[0-9],a[0-9]
** ...
*/
int16x4_t test_pmhraccsu_i16x4(int16x4_t rd, int16x4_t a, uint16x4_t b)
{
  return __riscv_pmhraccsu_i16x4(rd, a, b);
}

/*
**test_pmhacc_i32x2:
** ...
** pmhacc.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhacc_i32x2(int32x2_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_pmhacc_i32x2(rd, a, b);
}

/*
**test_pmhracc_i32x2:
** ...
** pmhracc.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhracc_i32x2(int32x2_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_pmhracc_i32x2(rd, a, b);
}

/*
**test_pmhaccu_u32x2:
** ...
** pmhaccu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmhaccu_u32x2(uint32x2_t rd, uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmhaccu_u32x2(rd, a, b);
}

/*
**test_pmhraccu_u32x2:
** ...
** pmhraccu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
uint32x2_t test_pmhraccu_u32x2(uint32x2_t rd, uint32x2_t a, uint32x2_t b)
{
  return __riscv_pmhraccu_u32x2(rd, a, b);
}

/*
**test_pmhaccsu_i32x2:
** ...
** pmhaccsu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhaccsu_i32x2(int32x2_t rd, int32x2_t a, uint32x2_t b)
{
  return __riscv_pmhaccsu_i32x2(rd, a, b);
}

/*
**test_pmhraccsu_i32x2:
** ...
** pmhraccsu.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmhraccsu_i32x2(int32x2_t rd, int32x2_t a, uint32x2_t b)
{
  return __riscv_pmhraccsu_i32x2(rd, a, b);
}

/* Packed Q-format Multiplication (i16x2 both ISAs; i16x4/i32x2 RV64-only) */

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
** ...
*/
int16x4_t test_pmulqr_i16x4(int16x4_t a, int16x4_t b)
{
  return __riscv_pmulqr_i16x4(a, b);
}

/*
**test_pmulq_i32x2:
** ...
** pmulq.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulq_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmulq_i32x2(a, b);
}

/*
**test_pmulqr_i32x2:
** ...
** pmulqr.w\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmulqr_i32x2(int32x2_t a, int32x2_t b)
{
  return __riscv_pmulqr_i32x2(a, b);
}

/* Packed Q-format Multiply Parts Accumulate
   h-series i32 (both ISAs): RV64 pmqacc.w.hNN / pmqracc.w.hNN.
   h-series i32x2 (packed): RV64 pmqacc.w.hNN / pmqracc.w.hNN (single insn).
   w-series i64 (RV64-only): mqacc.wNN / mqracc.wNN.  */

/*
**test_mqacc_h00_i32:
** ...
** pmqacc.w.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqacc_h00_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqacc_h00_i32(rd, a, b);
}

/*
**test_mqacc_h01_i32:
** ...
** pmqacc.w.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqacc_h01_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqacc_h01_i32(rd, a, b);
}

/*
**test_mqacc_h11_i32:
** ...
** pmqacc.w.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqacc_h11_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqacc_h11_i32(rd, a, b);
}

/*
**test_mqracc_h00_i32:
** ...
** pmqracc.w.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqracc_h00_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqracc_h00_i32(rd, a, b);
}

/*
**test_mqracc_h01_i32:
** ...
** pmqracc.w.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqracc_h01_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqracc_h01_i32(rd, a, b);
}

/*
**test_mqracc_h11_i32:
** ...
** pmqracc.w.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32_t test_mqracc_h11_i32(int32_t rd, int16x2_t a, int16x2_t b)
{
  return __riscv_mqracc_h11_i32(rd, a, b);
}

/*
**test_pmqacc_h00_i32x2:
** ...
** pmqacc.w.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqacc_h00_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqacc_h00_i32x2(rd, a, b);
}

/*
**test_pmqacc_h01_i32x2:
** ...
** pmqacc.w.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqacc_h01_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqacc_h01_i32x2(rd, a, b);
}

/*
**test_pmqacc_h11_i32x2:
** ...
** pmqacc.w.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqacc_h11_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqacc_h11_i32x2(rd, a, b);
}

/*
**test_pmqracc_h00_i32x2:
** ...
** pmqracc.w.h00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqracc_h00_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqracc_h00_i32x2(rd, a, b);
}

/*
**test_pmqracc_h01_i32x2:
** ...
** pmqracc.w.h01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqracc_h01_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqracc_h01_i32x2(rd, a, b);
}

/*
**test_pmqracc_h11_i32x2:
** ...
** pmqracc.w.h11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int32x2_t test_pmqracc_h11_i32x2(int32x2_t rd, int16x4_t a, int16x4_t b)
{
  return __riscv_pmqracc_h11_i32x2(rd, a, b);
}

/*
**test_mqacc_w00_i64:
** ...
** mqacc.w00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_mqacc_w00_i64(int64_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_mqacc_w00_i64(rd, a, b);
}

/*
**test_mqacc_w01_i64:
** ...
** mqacc.w01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_mqacc_w01_i64(int64_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_mqacc_w01_i64(rd, a, b);
}

/*
**test_mqacc_w11_i64:
** ...
** mqacc.w11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_mqacc_w11_i64(int64_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_mqacc_w11_i64(rd, a, b);
}

/*
**test_mqracc_w00_i64:
** ...
** mqracc.w00\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_mqracc_w00_i64(int64_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_mqracc_w00_i64(rd, a, b);
}

/*
**test_mqracc_w01_i64:
** ...
** mqracc.w01\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_mqracc_w01_i64(int64_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_mqracc_w01_i64(rd, a, b);
}

/*
**test_mqracc_w11_i64:
** ...
** mqracc.w11\ta[0-9],a[0-9],a[0-9]
** ...
*/
int64_t test_mqracc_w11_i64(int64_t rd, int32x2_t a, int32x2_t b)
{
  return __riscv_mqracc_w11_i64(rd, a, b);
}
