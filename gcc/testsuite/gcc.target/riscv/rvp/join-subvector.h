/* Exercise all packed element join and subvector interfaces.  */

#define TEST_JOIN2(NAME, TYPE, ELEMENT)                                    \
TYPE                                                                       \
test_##NAME (ELEMENT e0, ELEMENT e1)                                       \
{                                                                          \
  return __riscv_##NAME (e0, e1);                                         \
}

#define TEST_JOIN4(NAME, TYPE, ELEMENT)                                    \
TYPE                                                                       \
test_##NAME (ELEMENT e0, ELEMENT e1, ELEMENT e2, ELEMENT e3)               \
{                                                                          \
  return __riscv_##NAME (e0, e1, e2, e3);                                 \
}

#define TEST_SUBVECTOR_GET(NAME, TYPE, SUBVECTOR)                          \
SUBVECTOR                                                                  \
test_##NAME (TYPE value)                                                   \
{                                                                          \
  return __riscv_##NAME (value, 1);                                       \
}

#define TEST_SUBVECTOR_SET(NAME, TYPE, SUBVECTOR, INDEX)                   \
TYPE                                                                       \
test_##NAME (TYPE value, SUBVECTOR subvector)                              \
{                                                                          \
  return __riscv_##NAME (value, subvector, INDEX);                         \
}

#define TEST_SUBVECTOR_JOIN(NAME, TYPE, SUBVECTOR)                         \
TYPE                                                                       \
test_##NAME (SUBVECTOR lo, SUBVECTOR hi)                                   \
{                                                                          \
  return __riscv_##NAME (lo, hi);                                         \
}

TEST_JOIN4 (pjoin4_i8x4, int8x4_t, int8_t)
TEST_JOIN4 (pjoin4_u8x4, uint8x4_t, uint8_t)
TEST_JOIN2 (pjoin2_i16x2, int16x2_t, int16_t)
TEST_JOIN2 (pjoin2_u16x2, uint16x2_t, uint16_t)
TEST_JOIN4 (pjoin4_i16x4, int16x4_t, int16_t)
TEST_JOIN4 (pjoin4_u16x4, uint16x4_t, uint16_t)
TEST_JOIN2 (pjoin2_i32x2, int32x2_t, int32_t)
TEST_JOIN2 (pjoin2_u32x2, uint32x2_t, uint32_t)

TEST_SUBVECTOR_GET (pget_i8x8_i8x4, int8x8_t, int8x4_t)
TEST_SUBVECTOR_GET (pget_u8x8_u8x4, uint8x8_t, uint8x4_t)
TEST_SUBVECTOR_GET (pget_i16x4_i16x2, int16x4_t, int16x2_t)
TEST_SUBVECTOR_GET (pget_u16x4_u16x2, uint16x4_t, uint16x2_t)

TEST_SUBVECTOR_SET (pset_i8x4_i8x8, int8x8_t, int8x4_t, 0)
TEST_SUBVECTOR_SET (pset_u8x4_u8x8, uint8x8_t, uint8x4_t, 1)
TEST_SUBVECTOR_SET (pset_i16x2_i16x4, int16x4_t, int16x2_t, 0)
TEST_SUBVECTOR_SET (pset_u16x2_u16x4, uint16x4_t, uint16x2_t, 1)

TEST_SUBVECTOR_JOIN (pjoin2_i8x8, int8x8_t, int8x4_t)
TEST_SUBVECTOR_JOIN (pjoin2_u8x8, uint8x8_t, uint8x4_t)
TEST_SUBVECTOR_JOIN (pjoin2_i16x4, int16x4_t, int16x2_t)
TEST_SUBVECTOR_JOIN (pjoin2_u16x4, uint16x4_t, uint16x2_t)
