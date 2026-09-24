#define TEST_SLIDE1(SUFFIX, TYPE, ELEMENT) \
TYPE \
test_pslide1up_##SUFFIX (TYPE a, ELEMENT b) \
{ \
  return __riscv_pslide1up_##SUFFIX (a, b); \
} \
TYPE \
test_pslide1down_##SUFFIX (TYPE a, ELEMENT b) \
{ \
  return __riscv_pslide1down_##SUFFIX (a, b); \
}

#define TEST_SLIDE(SUFFIX, TYPE) \
TYPE \
test_pslideupx_##SUFFIX (TYPE a, TYPE b, unsigned int c) \
{ \
  return __riscv_pslideupx_##SUFFIX (a, b, c); \
} \
TYPE \
test_pslidedownx_##SUFFIX (TYPE a, TYPE b, unsigned int c) \
{ \
  return __riscv_pslidedownx_##SUFFIX (a, b, c); \
}

TEST_SLIDE1 (i8x4, int8x4_t, int8_t)
TEST_SLIDE1 (u8x4, uint8x4_t, uint8_t)
TEST_SLIDE1 (i16x2, int16x2_t, int16_t)
TEST_SLIDE1 (u16x2, uint16x2_t, uint16_t)
TEST_SLIDE1 (i8x8, int8x8_t, int8_t)
TEST_SLIDE1 (u8x8, uint8x8_t, uint8_t)
TEST_SLIDE1 (i16x4, int16x4_t, int16_t)
TEST_SLIDE1 (u16x4, uint16x4_t, uint16_t)
TEST_SLIDE1 (i32x2, int32x2_t, int32_t)
TEST_SLIDE1 (u32x2, uint32x2_t, uint32_t)

TEST_SLIDE (i8x4, int8x4_t)
TEST_SLIDE (u8x4, uint8x4_t)
TEST_SLIDE (i16x2, int16x2_t)
TEST_SLIDE (u16x2, uint16x2_t)
TEST_SLIDE (i8x8, int8x8_t)
TEST_SLIDE (u8x8, uint8x8_t)
TEST_SLIDE (i16x4, int16x4_t)
TEST_SLIDE (u16x4, uint16x4_t)
TEST_SLIDE (i32x2, int32x2_t)
TEST_SLIDE (u32x2, uint32x2_t)
