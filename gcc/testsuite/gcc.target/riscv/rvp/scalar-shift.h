/* Exercise variable and immediate scalar shift forms.  */

#define TEST_VARIABLE(NAME, RET, ARG)                                      \
RET                                                                        \
test_##NAME##_variable (ARG rs1, int rs2)                                  \
{                                                                          \
  return __riscv_##NAME (rs1, rs2);                                       \
}

#define TEST_IMMEDIATE(NAME, RET, ARG, SUFFIX, SHAMT)                      \
RET                                                                        \
test_##NAME##_##SUFFIX (ARG rs1)                                           \
{                                                                          \
  return __riscv_##NAME (rs1, SHAMT);                                     \
}

TEST_VARIABLE (ssha_i32, int32_t, int32_t)
TEST_VARIABLE (sshar_i32, int32_t, int32_t)
TEST_VARIABLE (sshl_u32, uint32_t, int32_t)
TEST_VARIABLE (sshlr_u32, uint32_t, int32_t)
TEST_IMMEDIATE (ssha_i32, int32_t, int32_t, left, 3)
TEST_IMMEDIATE (ssha_i32, int32_t, int32_t, right, -3)
TEST_IMMEDIATE (sshar_i32, int32_t, int32_t, left, 3)
TEST_IMMEDIATE (sshar_i32, int32_t, int32_t, right, -3)
TEST_IMMEDIATE (ssha_i32, int32_t, int32_t, left_max, 31)
TEST_IMMEDIATE (ssha_i32, int32_t, int32_t, right_max, -31)
TEST_IMMEDIATE (sshar_i32, int32_t, int32_t, left_max, 31)
TEST_IMMEDIATE (sshar_i32, int32_t, int32_t, right_max, -31)
TEST_IMMEDIATE (ssha_i32, int32_t, int32_t, register_left, 32)
TEST_IMMEDIATE (sshar_i32, int32_t, int32_t, register_right, -32)

#if __riscv_xlen == 64
TEST_VARIABLE (sha_i64, int64_t, int64_t)
TEST_VARIABLE (shar_i64, int64_t, int64_t)
TEST_VARIABLE (shl_u64, uint64_t, uint64_t)
TEST_VARIABLE (shlr_u64, uint64_t, uint64_t)
TEST_IMMEDIATE (sha_i64, int64_t, int64_t, left, 3)
TEST_IMMEDIATE (sha_i64, int64_t, int64_t, right, -3)
TEST_IMMEDIATE (shar_i64, int64_t, int64_t, left, 3)
TEST_IMMEDIATE (shar_i64, int64_t, int64_t, right, -3)
TEST_IMMEDIATE (sha_i64, int64_t, int64_t, left_max, 63)
TEST_IMMEDIATE (sha_i64, int64_t, int64_t, right_max, -63)
TEST_IMMEDIATE (shar_i64, int64_t, int64_t, left_max, 63)
TEST_IMMEDIATE (shar_i64, int64_t, int64_t, right_max, -63)
TEST_IMMEDIATE (sha_i64, int64_t, int64_t, register_left, 64)
TEST_IMMEDIATE (shar_i64, int64_t, int64_t, register_right, -64)
#endif
