/* Signed and unsigned clipping use different assembly width conventions.  */

#include <riscv_packed_simd.h>

#define SELECT(COND, A, B) (((COND) & (A)) | (~(COND) & (B)))

#define CLIP(NAME, TYPE, LO, HI) \
TYPE __attribute__ ((noipa)) \
NAME (TYPE a) \
{ \
  TYPE hi = (TYPE) { 0 } + (HI); \
  TYPE lo = (TYPE) { 0 } + (LO); \
  TYPE t = SELECT (a > hi, hi, a); \
  return SELECT (t < lo, lo, t); \
}

/* Large halfword bounds can use a constant pool and need not reach the
   saturation matcher.  Keep those cases as ordinary-C controls.  */
#define HALFWORD_CLIPS(TAG, TYPE) \
CLIP (TAG##_s2, TYPE, -2, 1) \
CLIP (TAG##_s8, TYPE, -128, 127) \
CLIP (TAG##_s15, TYPE, -16384, 16383) \
CLIP (TAG##_u1, TYPE, 0, 1) \
CLIP (TAG##_u8, TYPE, 0, 255) \
CLIP (TAG##_u14, TYPE, 0, 16383) \
CLIP (TAG##_lower, TYPE, -127, 127) \
CLIP (TAG##_upper, TYPE, -128, 126)

HALFWORD_CLIPS (clip_h2, int16x2_t)
HALFWORD_CLIPS (clip_h4, int16x4_t)

CLIP (clip_w2_s2, int32x2_t, -2, 1)
CLIP (clip_w2_s8, int32x2_t, -128, 127)
CLIP (clip_w2_s16, int32x2_t, -32768, 32767)
CLIP (clip_w2_s31, int32x2_t, -1073741824, 1073741823)
CLIP (clip_w2_u1, int32x2_t, 0, 1)
CLIP (clip_w2_u8, int32x2_t, 0, 255)
CLIP (clip_w2_u30, int32x2_t, 0, 1073741823)
CLIP (clip_w2_lower, int32x2_t, -127, 127)
CLIP (clip_w2_upper, int32x2_t, -128, 126)

/* An unsigned input must not be interpreted as a negative signed value.  */
#define UPPER(NAME, TYPE) \
TYPE __attribute__ ((noipa)) \
NAME (TYPE a) \
{ \
  TYPE hi = (TYPE) { 0 } + 255; \
  return SELECT (a > hi, hi, a); \
}

UPPER (upper_h2, uint16x2_t)
UPPER (upper_h4, uint16x4_t)
UPPER (upper_w2, uint32x2_t)

/* Generic width-one and full-width clamps may fold to other operations.
   Intrinsics check the inclusive immediate endpoints directly.  */
#define INTRINSIC(NAME, TYPE, OP, WIDTH) \
TYPE __attribute__ ((noipa)) \
NAME (TYPE a) \
{ \
  return __riscv_##OP (a, WIDTH); \
}

INTRINSIC (intrinsic_h2_min, int16x2_t, psati_i16x2, 1)
INTRINSIC (intrinsic_h2_max, int16x2_t, psati_i16x2, 16)
INTRINSIC (intrinsic_h2_large, int16x2_t, psati_i16x2, 15)
INTRINSIC (intrinsic_h4_min, int16x4_t, psati_i16x4, 1)
INTRINSIC (intrinsic_h4_max, int16x4_t, psati_i16x4, 16)
INTRINSIC (intrinsic_h4_large, int16x4_t, psati_i16x4, 15)
INTRINSIC (intrinsic_w2_min, int32x2_t, psati_i32x2, 1)
INTRINSIC (intrinsic_w2_max, int32x2_t, psati_i32x2, 32)

uint16x2_t __attribute__ ((noipa))
intrinsic_h2_unsigned (int16x2_t a)
{
  return __riscv_pusati_u16x2 (a, 14);
}

uint16x4_t __attribute__ ((noipa))
intrinsic_h4_unsigned (int16x4_t a)
{
  return __riscv_pusati_u16x4 (a, 14);
}

