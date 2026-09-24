/* Exercise scalar multiply-high and Q-format multiplication intrinsics.  */

#define TEST_BINARY(NAME, RET, ARG1, ARG2)                    \
RET                                                           \
test_##NAME (ARG1 rs1, ARG2 rs2)                              \
{                                                             \
  return __riscv_##NAME (rs1, rs2);                           \
}

TEST_BINARY (mulh_i32, int32_t, int32_t, int32_t)
TEST_BINARY (mulhr_i32, int32_t, int32_t, int32_t)
TEST_BINARY (mulhu_u32, uint32_t, uint32_t, uint32_t)
TEST_BINARY (mulhru_u32, uint32_t, uint32_t, uint32_t)
TEST_BINARY (mulhsu_i32, int32_t, int32_t, uint32_t)
TEST_BINARY (mulhrsu_i32, int32_t, int32_t, uint32_t)
TEST_BINARY (mulq_i32, int32_t, int32_t, int32_t)
TEST_BINARY (mulqr_i32, int32_t, int32_t, int32_t)
