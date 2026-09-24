/* Exercise packed absolute-difference-sum intrinsics.  */

uint32_t
test_pabdsumu_u8x4_u32 (uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdsumu_u8x4_u32 (a, b);
}

uint32_t
test_pabdsumau_u8x4_u32 (uint32_t acc, uint8x4_t a, uint8x4_t b)
{
  return __riscv_pabdsumau_u8x4_u32 (acc, a, b);
}

uint32_t
test_pabdsumu_u8x8_u32 (uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumu_u8x8_u32 (a, b);
}

uint64_t
test_pabdsumu_u8x8_u64 (uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumu_u8x8_u64 (a, b);
}

uint32_t
test_pabdsumau_u8x8_u32 (uint32_t acc, uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u32 (acc, a, b);
}

uint64_t
test_pabdsumau_u8x8_u64 (uint64_t acc, uint8x8_t a, uint8x8_t b)
{
  return __riscv_pabdsumau_u8x8_u64 (acc, a, b);
}
