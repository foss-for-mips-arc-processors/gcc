/* Exercise all packed load, store, element extract and element insert
   interfaces.  */

#define TEST_LOAD(NAME, TYPE, ELEMENT)                                     \
TYPE                                                                       \
test_##NAME (ELEMENT *p)                                                   \
{                                                                          \
  return __riscv_##NAME (p);                                               \
}

#define TEST_STORE(NAME, TYPE, ELEMENT)                                    \
void                                                                       \
test_##NAME (ELEMENT *p, TYPE value)                                       \
{                                                                          \
  __riscv_##NAME (p, value);                                               \
}

#define TEST_GET(NAME, TYPE, ELEMENT, INDEX)                               \
ELEMENT                                                                    \
test_##NAME (TYPE value)                                                   \
{                                                                          \
  return __riscv_##NAME (value, INDEX);                                    \
}

#define TEST_SET(NAME, TYPE, ELEMENT, INDEX)                               \
TYPE                                                                       \
test_##NAME (TYPE value, ELEMENT element)                                  \
{                                                                          \
  return __riscv_##NAME (value, element, INDEX);                           \
}

TEST_LOAD (pld_i8x4, int8x4_t, int8_t)
TEST_LOAD (pld_u8x4, uint8x4_t, uint8_t)
TEST_LOAD (pld_i16x2, int16x2_t, int16_t)
TEST_LOAD (pld_u16x2, uint16x2_t, uint16_t)
TEST_LOAD (pld_i8x8, int8x8_t, int8_t)
TEST_LOAD (pld_u8x8, uint8x8_t, uint8_t)
TEST_LOAD (pld_i16x4, int16x4_t, int16_t)
TEST_LOAD (pld_u16x4, uint16x4_t, uint16_t)
TEST_LOAD (pld_i32x2, int32x2_t, int32_t)
TEST_LOAD (pld_u32x2, uint32x2_t, uint32_t)

TEST_STORE (pst_i8x4, int8x4_t, int8_t)
TEST_STORE (pst_u8x4, uint8x4_t, uint8_t)
TEST_STORE (pst_i16x2, int16x2_t, int16_t)
TEST_STORE (pst_u16x2, uint16x2_t, uint16_t)
TEST_STORE (pst_i8x8, int8x8_t, int8_t)
TEST_STORE (pst_u8x8, uint8x8_t, uint8_t)
TEST_STORE (pst_i16x4, int16x4_t, int16_t)
TEST_STORE (pst_u16x4, uint16x4_t, uint16_t)
TEST_STORE (pst_i32x2, int32x2_t, int32_t)
TEST_STORE (pst_u32x2, uint32x2_t, uint32_t)

TEST_GET (pget_i8x4_i8, int8x4_t, int8_t, 3)
TEST_GET (pget_u8x4_u8, uint8x4_t, uint8_t, 3)
TEST_GET (pget_i16x2_i16, int16x2_t, int16_t, 1)
TEST_GET (pget_u16x2_u16, uint16x2_t, uint16_t, 1)
TEST_GET (pget_i8x8_i8, int8x8_t, int8_t, 7)
TEST_GET (pget_u8x8_u8, uint8x8_t, uint8_t, 7)
TEST_GET (pget_i16x4_i16, int16x4_t, int16_t, 3)
TEST_GET (pget_u16x4_u16, uint16x4_t, uint16_t, 3)
TEST_GET (pget_i32x2_i32, int32x2_t, int32_t, 1)
TEST_GET (pget_u32x2_u32, uint32x2_t, uint32_t, 1)

TEST_SET (pset_i8_i8x4, int8x4_t, int8_t, 3)
TEST_SET (pset_u8_u8x4, uint8x4_t, uint8_t, 3)
TEST_SET (pset_i16_i16x2, int16x2_t, int16_t, 1)
TEST_SET (pset_u16_u16x2, uint16x2_t, uint16_t, 1)
TEST_SET (pset_i8_i8x8, int8x8_t, int8_t, 7)
TEST_SET (pset_u8_u8x8, uint8x8_t, uint8_t, 7)
TEST_SET (pset_i16_i16x4, int16x4_t, int16_t, 3)
TEST_SET (pset_u16_u16x4, uint16x4_t, uint16_t, 3)
TEST_SET (pset_i32_i32x2, int32x2_t, int32_t, 1)
TEST_SET (pset_u32_u32x2, uint32x2_t, uint32_t, 1)
