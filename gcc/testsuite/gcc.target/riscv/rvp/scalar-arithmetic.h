/* Exercise scalar saturating, averaging, and shift-add interfaces.  */

#define TEST_BINARY(NAME, TYPE)                                            \
TYPE                                                                       \
test_##NAME (TYPE rs1, TYPE rs2)                                           \
{                                                                          \
  return __riscv_##NAME (rs1, rs2);                                       \
}

TEST_BINARY (sadd_i32, int32_t)
TEST_BINARY (saddu_u32, uint32_t)
TEST_BINARY (ssub_i32, int32_t)
TEST_BINARY (ssubu_u32, uint32_t)
TEST_BINARY (aadd_i32, int32_t)
TEST_BINARY (aaddu_u32, uint32_t)
TEST_BINARY (asub_i32, int32_t)
TEST_BINARY (asubu_u32, uint32_t)
TEST_BINARY (ssh1sadd_i32, int32_t)
