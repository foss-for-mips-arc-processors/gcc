/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
typedef long long s64;

__attribute__ ((noipa)) u64
narrow_operands (u64 x, u64 y)
{
  return x >= y ? (u64) ((u32) x - (u32) y) : 0;
}

__attribute__ ((noipa)) u64
signed_operands (u32 x, u32 y)
{
  return x >= y ? (u64) ((s32) x - (s32) y) : 0;
}

__attribute__ ((noipa)) u64
unsigned_wider (u32 x, u32 y)
{
  return x >= y ? (u64) x - (u64) y : 0;
}

__attribute__ ((noipa)) u64
signed_wider (u32 x, u32 y)
{
  return x >= y ? (u64) ((s64) x - (s64) y) : 0;
}

__attribute__ ((noipa)) u8
narrow_result (u64 x, u64 y)
{
  return x >= y ? (u8) ((u32) x - (u32) y) : 0;
}

__attribute__ ((noipa)) u64
promoted_narrow_operands (u32 x, u32 y)
{
  return x >= y ? (u64) ((u8) x - (u8) y) : 0;
}

int
main (void)
{
  if (narrow_operands (0x100000001ULL, 0) != 1
      || narrow_operands (0x100000000ULL, 1) != 0xffffffffULL
      || narrow_operands (0, 0x100000001ULL) != 0)
    __builtin_abort ();

  /* The selected signed subtraction does not overflow in these cases.  */
  if (signed_operands (~0u, 0) != ~0ULL
      || signed_operands (0x80000000u, 0) != 0xffffffff80000000ULL
      || signed_operands (~0u, 0x80000000u) != 0x7fffffffULL
      || signed_operands (0, ~0u) != 0)
    __builtin_abort ();

  if (unsigned_wider (~0u, 0) != 0xffffffffULL
      || signed_wider (~0u, 0) != 0xffffffffULL
      || narrow_result (0x100000011ULL, 0) != 17
      || narrow_result (0x100000000ULL, 1) != 255
      || promoted_narrow_operands (256, 1) != ~0ULL)
    __builtin_abort ();
  return 0;
}
