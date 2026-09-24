/* Exercise scalar absolute value, comparison, and merge interfaces.  */

#define TEST_UNARY(NAME, RET, ARG)                                         \
RET                                                                        \
test_##NAME (ARG rs1)                                                      \
{                                                                          \
  return __riscv_##NAME (rs1);                                            \
}

#define TEST_BINARY(NAME, RET, ARG)                                        \
RET                                                                        \
test_##NAME (ARG rs1, ARG rs2)                                             \
{                                                                          \
  return __riscv_##NAME (rs1, rs2);                                       \
}

#define TEST_MERGE(NAME, RET, ARG, MASK)                                   \
RET                                                                        \
test_##NAME (ARG rs1, ARG rs2, MASK mask)                                  \
{                                                                          \
  return __riscv_##NAME (rs1, rs2, mask);                                 \
}

TEST_UNARY (abs_u32, uint32_t, int32_t)
#if __riscv_xlen == 64
TEST_UNARY (abs_u64, uint64_t, int64_t)
#endif

TEST_BINARY (mseq_i32_u32, uint32_t, int32_t)
TEST_BINARY (mseq_u32_u32, uint32_t, uint32_t)
TEST_BINARY (mslt_u32, uint32_t, int32_t)
TEST_BINARY (msgt_u32, uint32_t, int32_t)
TEST_BINARY (msltu_u32, uint32_t, uint32_t)
TEST_BINARY (msgtu_u32, uint32_t, uint32_t)
TEST_BINARY (msne_i32_u32, uint32_t, int32_t)
TEST_BINARY (msne_u32_u32, uint32_t, uint32_t)
TEST_BINARY (msge_u32, uint32_t, int32_t)
TEST_BINARY (msle_u32, uint32_t, int32_t)
TEST_BINARY (msgeu_u32, uint32_t, uint32_t)
TEST_BINARY (msleu_u32, uint32_t, uint32_t)

TEST_MERGE (merge_i32, int32_t, int32_t, uint32_t)
TEST_MERGE (merge_u32, uint32_t, uint32_t, uint32_t)
TEST_MERGE (merge_i64, int64_t, int64_t, uint64_t)
TEST_MERGE (merge_u64, uint64_t, uint64_t, uint64_t)
