/* Boolean inversions and non-boolean XOR controls.  */
#define ZERO_TEST_FUNCTIONS(F, T, N) \
  F (T, N, masked, ((a & 1) ^ 1) & ((b & 1) ^ 1)) \
  F (T, N, mixed, ((a & 1) ^ 1) & (b == 0)) \
  F (T, N, mixed_rev, (a == 0) & ((b & 1) ^ 1)) \
  F (T, N, aligned, (a > 4) & (b > 4) & ((c & 3) == 0)) \
  F (T, N, both, (a > 4) & (b > 4)) \
  F (T, N, xor_integer, (a ^ 1) & (b == 0)) \
  F (T, N, xor_pair, (a ^ 1) & (b ^ 1)) \
  F (T, N, xor_mask3, ((a & 3) ^ 1) & ((b & 3) ^ 1)) \
  F (T, N, xor_two, ((a & 1) ^ 2) & ((b & 1) ^ 2)) \
  F (T, N, equal_constants, (a == 1) & (b == 2)) \
  F (T, N, equal_zero, (a == 0) & (b == 0)) \
  F (T, N, different_bounds, (a > 3) & (b > 4))

#define ALL_ZERO_TEST_FUNCTIONS(F) \
  ZERO_TEST_FUNCTIONS (F, __UINT8_TYPE__, u8) \
  ZERO_TEST_FUNCTIONS (F, __UINT16_TYPE__, u16) \
  ZERO_TEST_FUNCTIONS (F, __UINT32_TYPE__, u32) \
  ZERO_TEST_FUNCTIONS (F, __UINT64_TYPE__, u64)
