#include <riscv_packed_simd.h>

#define FN __attribute__ ((noipa))

uint32_t FN
zero4 (uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdsumau_u8x4_u32 (0, a, b);
}

uint32_t FN
zero8w (uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u32 (0, a, b);
}

uint64_t FN
zero8d (uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u64 (0, a, b);
}

uint32_t FN
variable4 (uint32_t acc, uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdsumau_u8x4_u32 (acc, a, b);
}

uint32_t FN
variable8w (uint32_t acc, uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u32 (acc, a, b);
}

uint64_t FN
variable8d (uint64_t acc, uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u64 (acc, a, b);
}

uint32_t FN
shared_zero4 (uint8x4_t a, uint8x4_t b, uint32_t *saved)
{
  uint32_t acc = 0;
  *saved = acc;
  return __riscv_pabdsumau_u8x4_u32 (acc, a, b);
}

uint64_t FN
shared_zero8d (uint8x8_t a, uint8x8_t b, uint64_t *saved)
{
  uint64_t acc = 0;
  *saved = acc;
  return __riscv_pabdsumau_u8x8_u64 (acc, a, b);
}
