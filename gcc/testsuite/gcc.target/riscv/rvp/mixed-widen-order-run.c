/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

typedef unsigned int u32;
typedef unsigned long long u64;

u64 __attribute__ ((noipa))
word_product (u64 a, u64 b)
{
  return (long long) (int) a * (long long) (u32) b;
}

u64 __attribute__ ((noipa))
reverse_product (u64 a, u64 b)
{
  return (long long) (u32) a * (long long) (int) b;
}

u32 __attribute__ ((noipa))
half_product (u32 a, u32 b)
{
  return (int) (short) a * (unsigned short) b;
}

static u64 __attribute__ ((noipa, optimize ("O0")))
reference (u32 a, u32 b)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0, bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535, high = t >> 16;
  t = a0 * b1 + middle;
  u32 low = (t << 16) | bottom;
  high += a1 * b1 + (t >> 16);
  if (a >> 31)
    high -= b;
  return ((u64) high << 32) | low;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 0x7fff, 0x8000, 0xffff, 0x10000, 0x7fffffff,
	0x80000000, 0x80000001, 0xfffffffe, 0xffffffff };
  for (unsigned i = 0; i < sizeof values / sizeof values[0]; ++i)
    for (unsigned j = 0; j < sizeof values / sizeof values[0]; ++j)
      {
	u32 a = values[i], b = values[j];
	u64 aa = ((u64) ~b << 32) | a;
	u64 bb = ((u64) ~a << 32) | b;
	u32 half = a & 65535;
	u32 low = half * (b & 65535);
	if (half & 32768)
	  low -= (b & 65535) << 16;
	if (word_product (aa, bb) != reference (a, b)
	    || reverse_product (bb, aa) != reference (a, b)
	    || half_product (a, b) != low)
	  __builtin_abort ();
      }
  return 0;
}
