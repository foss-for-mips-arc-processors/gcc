#define TEST_CLIP_PAIR(NAME, RET, ARG) \
RET \
test_##NAME (ARG a, ARG b) \
{ \
  return __riscv_##NAME (a, b); \
}

TEST_CLIP_PAIR (pnclipp_i8x4, int8x4_t, int16x2_t)
TEST_CLIP_PAIR (pnclipup_u8x4, uint8x4_t, uint16x2_t)
TEST_CLIP_PAIR (pnclipp_i16x2, int16x2_t, int32_t)
TEST_CLIP_PAIR (pnclipup_u16x2, uint16x2_t, uint32_t)
TEST_CLIP_PAIR (pnclipp_i8x8, int8x8_t, int16x4_t)
TEST_CLIP_PAIR (pnclipup_u8x8, uint8x8_t, uint16x4_t)
TEST_CLIP_PAIR (pnclipp_i16x4, int16x4_t, int32x2_t)
TEST_CLIP_PAIR (pnclipup_u16x4, uint16x4_t, uint32x2_t)
TEST_CLIP_PAIR (pnclipp_i32x2, int32x2_t, int64_t)
TEST_CLIP_PAIR (pnclipup_u32x2, uint32x2_t, uint64_t)
