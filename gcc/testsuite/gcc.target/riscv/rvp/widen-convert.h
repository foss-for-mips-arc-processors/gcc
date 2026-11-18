typedef signed char cv_s8x4 __attribute__ ((vector_size (4)));
typedef unsigned char cv_u8x4 __attribute__ ((vector_size (4)));
typedef short cv_s16x2 __attribute__ ((vector_size (4)));
typedef unsigned short cv_u16x2 __attribute__ ((vector_size (4)));
typedef short cv_s16x4 __attribute__ ((vector_size (8)));
typedef unsigned short cv_u16x4 __attribute__ ((vector_size (8)));
typedef int cv_s32x2 __attribute__ ((vector_size (8)));
typedef unsigned int cv_u32x2 __attribute__ ((vector_size (8)));

#define CONVERT(NAME, S, D) \
  __attribute__ ((noinline, noclone)) D \
  NAME (S a) \
  { \
    return __builtin_convertvector (a, D); \
  }

CONVERT (convert_s_b, cv_s8x4, cv_s16x4)
CONVERT (convert_u_b, cv_u8x4, cv_u16x4)
CONVERT (convert_s_h, cv_s16x2, cv_s32x2)
CONVERT (convert_u_h, cv_u16x2, cv_u32x2)

#undef CONVERT

/* These products must retain all input bits, not just the low byte or
   halfword of each lane as in a widening multiplication.  */
__attribute__ ((noinline, noclone)) cv_u16x4
full_mul_h (cv_u16x4 a, cv_u16x4 b)
{
  return a * b;
}

__attribute__ ((noinline, noclone)) cv_u32x2
full_mul_w (cv_u32x2 a, cv_u32x2 b)
{
  return a * b;
}
