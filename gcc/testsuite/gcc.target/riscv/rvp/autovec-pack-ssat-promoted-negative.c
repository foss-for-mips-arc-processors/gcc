/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details -fdump-tree-slp1-details" } */

#include <stdint.h>

/* Keep the intermediate in its promoted type so that its original SSA
   result, rather than a separately narrowed copy, has another consumer.  */
#define SHARED_CLAMP(NAME, OUT, IN, TMP, LOW, HIGH, OUTER) \
  void __attribute__ ((noipa)) \
  NAME (OUT *restrict dst, TMP *restrict observed, \
	const IN *restrict src, unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      { \
	TMP value = src[i]; \
	if (value < LOW) \
	  value = LOW; \
	if (!OUTER) \
	  observed[i] = value; \
	if (value > HIGH) \
	  value = HIGH; \
	if (OUTER) \
	  observed[i] = value; \
	dst[i] = value; \
      } \
  }

SHARED_CLAMP (shared_inner_h, int8_t, int16_t, int32_t, -128, 127, 0)
SHARED_CLAMP (shared_outer_h, int8_t, int16_t, int32_t, -128, 127, 1)
SHARED_CLAMP (shared_inner_w, int16_t, int32_t, int64_t, -32768, 32767, 0)
SHARED_CLAMP (shared_outer_w, int16_t, int32_t, int64_t, -32768, 32767, 1)

#undef SHARED_CLAMP

/* { dg-final { scan-tree-dump-not "vect_recog_promoted_sat_trunc_clamp" "vect" } } */
/* { dg-final { scan-tree-dump-not "vect_recog_promoted_sat_trunc_clamp" "slp1" } } */
