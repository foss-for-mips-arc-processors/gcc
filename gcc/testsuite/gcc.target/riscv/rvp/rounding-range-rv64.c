/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -fwrapv" } */

#include <stdint.h>

/* These inputs have arbitrary upper bits.  The word addition wraps before
   the final shift, unlike an XLEN-wide SRARI of the original input.  */
#define TEST(SHIFT) \
  __attribute__ ((noipa)) int64_t raw_word_##SHIFT (uint64_t x) \
  { return (int32_t) ((uint32_t) (x >> ((SHIFT) - 1)) + 1u) >> 1; }

TEST (4)
TEST (16)
TEST (31)

/* { dg-final { scan-assembler-not {\msrari\M} } } */
