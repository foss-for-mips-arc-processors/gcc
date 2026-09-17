/* { dg-do compile } */
/* { dg-options "-mlasx -O2" } */

#include <lasxintrin.h>
#include <lsxintrin.h>

#define TEST(to, from)								\
__m256i										\
vext2xv_##to##_##from (const short *p)						\
{										\
  return __lasx_vext2xv_##to##_##from (__lasx_cast_128 (__lsx_vld (p, 0)));	\
}

TEST (h, b)
TEST (w, b)
TEST (d, b)
TEST (w, h)
TEST (d, h)
TEST (d, w)
TEST (hu, bu)
TEST (wu, bu)
TEST (du, bu)
TEST (wu, hu)
TEST (du, hu)
TEST (du, wu)
