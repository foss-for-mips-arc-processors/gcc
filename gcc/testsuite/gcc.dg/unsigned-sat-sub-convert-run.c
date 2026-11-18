/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */

/* A saturation result must retain its operand type before conversion.  */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define DEF(NAME, ARG, RESULT) \
  __attribute__ ((noipa)) RESULT \
  NAME (ARG x, ARG y) \
  { \
    return x >= y ? (RESULT) (x - y) : 0; \
  }

#define ROW(BITS, ARG) \
  DEF (sub_##BITS##_8, ARG, u8) \
  DEF (sub_##BITS##_16, ARG, u16) \
  DEF (sub_##BITS##_32, ARG, u32) \
  DEF (sub_##BITS##_64, ARG, u64)

ROW (8, u8)
ROW (16, u16)
ROW (32, u32)
ROW (64, u64)

#define CHECK(NAME, ARG, RESULT) \
  do \
    { \
      ARG max = (ARG) ~0ULL; \
      ARG high = (ARG) (1ULL << (sizeof (ARG) * __CHAR_BIT__ - 1)); \
      if (NAME (max, 0) != (RESULT) max \
          || NAME (high, 0) != (RESULT) high \
          || NAME (max, 1) != (RESULT) (max - 1) \
          || NAME (max, max) != 0 || NAME (1, max) != 0) \
        __builtin_abort (); \
    } \
  while (0)

#define CHECK_ROW(BITS, ARG) \
  CHECK (sub_##BITS##_8, ARG, u8); \
  CHECK (sub_##BITS##_16, ARG, u16); \
  CHECK (sub_##BITS##_32, ARG, u32); \
  CHECK (sub_##BITS##_64, ARG, u64)

int
main (void)
{
  CHECK_ROW (8, u8);
  CHECK_ROW (16, u16);
  CHECK_ROW (32, u32);
  CHECK_ROW (64, u64);
  return 0;
}
