typedef unsigned int u32;
typedef unsigned long long u64;

u32 __attribute__ ((noipa))
umulhi_acc (u32 c, u32 a, u32 b)
{
  return c + (u32) (((u64) a * b) >> 32);
}

void __attribute__ ((noipa))
umulhi_store (u32 *p, u32 a, u32 b)
{
  *p += (u32) (((u64) a * b) >> 32);
}

u32 __attribute__ ((noipa))
umulhi_store_return (u32 *p, u32 a, u32 b)
{
  u32 result = *p + (u32) (((u64) a * b) >> 32);
  *p = result;
  return result;
}

void __attribute__ ((noipa))
umulhi_volatile (volatile u32 *p, u32 a, u32 b)
{
  *p += (u32) (((u64) a * b) >> 32);
}

u32 __attribute__ ((noipa))
umulhi_left (u32 a, u32 b)
{
  return a + (u32) (((u64) a * b) >> 32);
}

u32 __attribute__ ((noipa))
umulhi_right (u32 a, u32 b)
{
  return b + (u32) (((u64) a * b) >> 32);
}

/* The low words determine the product, but both complete input values
   remain live after the accumulation.  */
u64 __attribute__ ((noipa))
umulhi_live_upper (u64 a, u64 b, u32 c)
{
  u32 result = c + (u32) (((u64) (u32) a * (u32) b) >> 32);
  return (a ^ b) + result;
}

u64 __attribute__ ((noipa))
umulhi_preserve_acc (u64 c, u32 a, u32 b)
{
  u32 result = (u32) c + (u32) (((u64) a * b) >> 32);
  return (c & 0xffffffff00000000ULL) | result;
}

/* This addition keeps its carry instead of wrapping in the low word.  */
u64 __attribute__ ((noipa))
umulhi_wide (u64 c, u32 a, u32 b)
{
  return c + (((u64) a * b) >> 32);
}

u32 __attribute__ ((noipa))
umulhi_shared_product (u32 c, u32 a, u32 b, u64 *saved)
{
  u64 product = (u64) a * b;
  *saved = product;
  return c + (u32) (product >> 32);
}

u32 __attribute__ ((noipa))
umulhi_shared_high (u32 c, u32 a, u32 b, u32 *saved)
{
  u32 high = ((u64) a * b) >> 32;
  *saved = high;
  return c + high;
}

u32 __attribute__ ((noipa))
umulhi_shift31 (u32 c, u32 a, u32 b)
{
  return c + (u32) (((u64) a * b) >> 31);
}

u32 __attribute__ ((noipa))
umulhi_wrong_bias (u32 c, u32 a, u32 b)
{
  return c + (u32) (((u64) a * b + 0x40000000ULL) >> 32);
}

/* Neither operand is restricted to an extended word here.  */
u32 __attribute__ ((noipa))
umulhi_full_width (u32 c, u64 a, u64 b)
{
  return c + (u32) ((a * b) >> 32);
}
