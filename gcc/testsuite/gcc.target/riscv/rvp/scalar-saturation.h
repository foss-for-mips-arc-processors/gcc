/* Exercise the lower and upper width bounds of scalar saturation.  */

#define TEST_SATURATION(NAME, RET, ARG, WIDTH)                             \
RET                                                                        \
test_##NAME##_##WIDTH (ARG rs1)                                           \
{                                                                          \
  return __riscv_##NAME (rs1, WIDTH);                                     \
}

TEST_SATURATION (sati_i32, int32_t, int32_t, 1)
TEST_SATURATION (sati_i32, int32_t, int32_t, 32)
TEST_SATURATION (usati_u32, uint32_t, int32_t, 0)
TEST_SATURATION (usati_u32, uint32_t, int32_t, 31)

#if __riscv_xlen == 64
TEST_SATURATION (sati_i64, int64_t, int64_t, 1)
TEST_SATURATION (sati_i64, int64_t, int64_t, 64)
TEST_SATURATION (usati_u64, uint64_t, int64_t, 0)
TEST_SATURATION (usati_u64, uint64_t, int64_t, 63)
#endif

/* The maximum signed widths exercise the width-to-encoding conversion.  */
TEST_SATURATION (psati_i16x2, int16x2_t, int16x2_t, 16)
TEST_SATURATION (psati_i16x4, int16x4_t, int16x4_t, 16)
TEST_SATURATION (psati_i32x2, int32x2_t, int32x2_t, 32)
