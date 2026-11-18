/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

#define TEST(TYPE, NAME) \
  void xor_##NAME (TYPE *restrict d, const TYPE *restrict a, \
		  const TYPE *restrict b, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (a[i] & b[i]) + ((a[i] ^ b[i]) >> 1); \
  } \
  void carry_##NAME (TYPE *restrict d, const TYPE *restrict a, \
		    const TYPE *restrict b, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (a[i] >> 1) + (b[i] >> 1) + ((a[i] & b[i]) & 1); \
  }

TEST (int, s32)
TEST (unsigned int, u32)

/* { dg-final { scan-assembler-times {\mpaadd\.dw\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dw\M} 2 } } */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
