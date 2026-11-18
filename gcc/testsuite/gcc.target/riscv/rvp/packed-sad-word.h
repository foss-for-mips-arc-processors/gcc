#include <riscv_packed_simd.h>

#define FN __attribute__ ((noipa))

uint32_t FN
sad_word4 (uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdsumu_u8x4_u32 (a, b);
}

uint32_t FN
sad_word8 (uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumu_u8x8_u32 (a, b);
}

uint64_t FN
sad_unsigned4 (uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdsumu_u8x4_u32 (a, b);
}

uint64_t FN
sad_unsigned8 (uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumu_u8x8_u32 (a, b);
}

int64_t FN
sad_signed4 (uint8x4_t a, uint8x4_t b)
{
  return (int32_t) __riscv_pabdsumu_u8x4_u32 (a, b);
}

int64_t FN
sad_signed8 (uint8x8_t a, uint8x8_t b)
{
  return (int32_t) __riscv_pabdsumu_u8x8_u32 (a, b);
}

uint32_t FN
sad_shared (uint8x8_t a, uint8x8_t b, uint64_t *saved)
{
  uint64_t sum = __riscv_pabdsumu_u8x8_u64 (a, b);
  *saved = sum;
  return sum;
}

/* Accumulating forms can overflow a word.  */
uint64_t FN
sad_wrap_unsigned (uint32_t acc, uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u32 (acc, a, b);
}

int64_t FN
sad_wrap_signed (uint32_t acc, uint8x8_t a, uint8x8_t b)
{
  return (int32_t) __riscv_pabdsumau_u8x8_u32 (acc, a, b);
}

/* The byte conversion cannot use the bound for a word conversion.  */
uint64_t FN
sad_byte (uint8x8_t a, uint8x8_t b)
{
  return (uint8_t) __riscv_pabdsumu_u8x8_u32 (a, b);
}
