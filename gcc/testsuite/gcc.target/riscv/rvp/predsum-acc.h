#include <riscv_packed_simd.h>

#define TEST(NAME, TYPE, VTYPE, INTRINSIC) \
  TYPE NAME##_zero (VTYPE v) { return INTRINSIC (v, 0); } \
  TYPE NAME##_const (VTYPE v) { return INTRINSIC (v, 7); } \
  TYPE NAME##_var (VTYPE v, TYPE acc) { return INTRINSIC (v, acc); }

#if __riscv_xlen == 32
TEST (bytes, int32_t, int8x4_t, __riscv_predsum_i8x4_i32)
TEST (halves, int32_t, int16x2_t, __riscv_predsum_i16x2_i32)
#else
TEST (bytes, int64_t, int8x8_t, __riscv_predsum_i8x8_i64)
TEST (halves, int64_t, int16x4_t, __riscv_predsum_i16x4_i64)
#endif

#undef TEST
