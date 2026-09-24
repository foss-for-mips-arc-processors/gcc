/* Exercise variable and immediate scalar narrowing clip forms.  */

#define TEST_VARIABLE(NAME, RET, ARG)                                      \
RET                                                                        \
test_##NAME##_variable (ARG rs1, unsigned shamt)                           \
{                                                                          \
  return __riscv_##NAME (rs1, shamt);                                     \
}

#define TEST_IMMEDIATE(NAME, RET, ARG, SUFFIX, SHAMT)                      \
RET                                                                        \
test_##NAME##_##SUFFIX (ARG rs1)                                           \
{                                                                          \
  return __riscv_##NAME (rs1, SHAMT);                                     \
}

#define TEST_NCLIP(NAME, RET, ARG)                                         \
  TEST_VARIABLE (NAME, RET, ARG)                                           \
  TEST_IMMEDIATE (NAME, RET, ARG, immediate, 3)                            \
  TEST_IMMEDIATE (NAME, RET, ARG, immediate_max, 63)                       \
  TEST_IMMEDIATE (NAME, RET, ARG, register_wrap, 64)

TEST_NCLIP (nclipu_u32, uint32_t, uint64_t)
TEST_NCLIP (nclipru_u32, uint32_t, uint64_t)
TEST_NCLIP (nsrar_i32, int32_t, int64_t)
TEST_NCLIP (nclip_i32, int32_t, int64_t)
TEST_NCLIP (nclipr_i32, int32_t, int64_t)
