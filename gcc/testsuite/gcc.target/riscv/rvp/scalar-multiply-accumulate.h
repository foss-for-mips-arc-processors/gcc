/* Exercise scalar multiply-high and Q-format accumulate intrinsics.  */

#define TEST_TERNARY(NAME, RET, ARG1, ARG2, ARG3)              \
RET                                                            \
test_##NAME (ARG1 rd, ARG2 rs1, ARG3 rs2)                      \
{                                                              \
  return __riscv_##NAME (rd, rs1, rs2);                        \
}

TEST_TERNARY (mhacc_i32, int32_t, int32_t, int32_t, int32_t)
TEST_TERNARY (mhracc_i32, int32_t, int32_t, int32_t, int32_t)
TEST_TERNARY (mhaccu_u32, uint32_t, uint32_t, uint32_t, uint32_t)
TEST_TERNARY (mhraccu_u32, uint32_t, uint32_t, uint32_t, uint32_t)
TEST_TERNARY (mhaccsu_i32, int32_t, int32_t, int32_t, uint32_t)
TEST_TERNARY (mhraccsu_i32, int32_t, int32_t, int32_t, uint32_t)
TEST_TERNARY (mqwacc_i64, int64_t, int64_t, int32_t, int32_t)
TEST_TERNARY (mqrwacc_i64, int64_t, int64_t, int32_t, int32_t)
