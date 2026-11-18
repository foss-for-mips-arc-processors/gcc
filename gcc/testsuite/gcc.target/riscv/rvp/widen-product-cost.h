typedef signed char s8x4 __attribute__ ((vector_size (4)));
typedef unsigned char u8x4 __attribute__ ((vector_size (4)));
typedef short s16x2 __attribute__ ((vector_size (4)));
typedef unsigned short u16x2 __attribute__ ((vector_size (4)));
typedef short s16x4 __attribute__ ((vector_size (8)));
typedef unsigned short u16x4 __attribute__ ((vector_size (8)));
typedef int s32x2 __attribute__ ((vector_size (8)));
typedef unsigned int u32x2 __attribute__ ((vector_size (8)));

/* The widening product must remain profitable when either or both of its
   extensions are also needed by another operation.  Use unsigned additions
   so accumulator wrapping is defined independently of the input types.  */
#define SHARED(NAME, A, B, W, U) \
  __attribute__ ((noipa)) U \
  shared_##NAME (U acc, A a, B b) \
  { \
    W wa = __builtin_convertvector (a, W); \
    W wb = __builtin_convertvector (b, W); \
    return acc + (U) (wa * wb) + (U) wa; \
  } \
  __attribute__ ((noipa)) U \
  shared_both_##NAME (U acc, A a, B b) \
  { \
    W wa = __builtin_convertvector (a, W); \
    W wb = __builtin_convertvector (b, W); \
    return acc + (U) (wa * wb) + (U) wa + (U) wb; \
  } \
  __attribute__ ((noipa)) void \
  shared_store_##NAME (U *extended, U *product, A a, B b) \
  { \
    W wa = __builtin_convertvector (a, W); \
    W wb = __builtin_convertvector (b, W); \
    *extended = (U) wa; \
    *product = (U) (wa * wb); \
  }

SHARED (ss_b, s8x4, s8x4, s16x4, u16x4)
SHARED (uu_b, u8x4, u8x4, u16x4, u16x4)
SHARED (su_b, s8x4, u8x4, s16x4, u16x4)
SHARED (us_b, u8x4, s8x4, s16x4, u16x4)
SHARED (ss_h, s16x2, s16x2, s32x2, u32x2)
SHARED (uu_h, u16x2, u16x2, u32x2, u32x2)
SHARED (su_h, s16x2, u16x2, s32x2, u32x2)
SHARED (us_h, u16x2, s16x2, s32x2, u32x2)

#undef SHARED

/* Full-width and partially widened products cannot use the two-narrow-input
   pattern.  In particular, retain the high bits of A in partial_word.  */
__attribute__ ((noipa)) u16x4
full_half (u16x4 a, u16x4 b)
{
  return a * b;
}

__attribute__ ((noipa)) u32x2
full_word (u32x2 a, u32x2 b)
{
  return a * b;
}

__attribute__ ((noipa)) u32x2
partial_word (u32x2 a, u16x2 b)
{
  return a * __builtin_convertvector (b, u32x2);
}
