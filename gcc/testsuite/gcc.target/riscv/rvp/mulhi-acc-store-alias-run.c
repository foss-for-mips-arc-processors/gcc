/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "mulhi-acc-loop.h"

static u32 __attribute__ ((noipa, optimize ("O0")))
high_word (u32 a, u32 b, unsigned kind, unsigned rounded)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0, bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535, high = t >> 16;
  t = a0 * b1 + middle;
  u32 low = (t << 16) | bottom;
  high += a1 * b1 + (t >> 16);
  if ((kind == 0 || kind == 2) && a >> 31)
    high -= b;
  if ((kind == 0 || kind == 3) && b >> 31)
    high -= a;
  return high + (rounded ? low >> 31 : 0);
}

#define SIZE 136
static u32 a[SIZE] __attribute__ ((aligned (64)));
static u32 b[SIZE] __attribute__ ((aligned (64)));
static u32 ra[SIZE], rb[SIZE];

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned sizes[] = { 0, 1, 2, 3, 4, 7, 8, 15, 16, 17,
				   31, 32, 33, 63, 64, 65, 127, 128 };
#define OFFSETS 2
#define ALIASES 4
  static const u32 values[]
    = { 0, 1, 0x7fffffff, 0x80000000, 0xffffffff, 0x80000001,
	0x10000, 0xffff, 0xfffffffe };
  for (unsigned off = 0; off < OFFSETS; ++off)
    for (unsigned s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
      for (unsigned alias = 0; alias < ALIASES; ++alias)
	for (unsigned kind = 0; kind < 8; ++kind)
	  {
	    unsigned n = sizes[s], delta = alias & 1;
	    for (unsigned i = 0; i < SIZE; ++i)
	      {
		a[i] = ra[i] = i % 3 ? i * 2654435761U : values[i % 9];
		b[i] = rb[i] = i % 3 ? ~i * 987654321U : values[(i + 4) % 9];
	      }
	    u32 *d = (alias < 2 ? a : b) + off + delta;
	    u32 *r = (alias < 2 ? ra : rb) + off + delta;
	    for (unsigned i = 0; i < n; ++i)
	      r[i] += high_word (ra[off + i], rb[off + i], kind % 4, kind / 4);
	    switch (kind)
	      {
	      case 0: map_s (d, (i32 *) a + off, (i32 *) b + off, n); break;
	      case 1: map_u (d, a + off, b + off, n); break;
	      case 2: map_su (d, (i32 *) a + off, b + off, n); break;
	      case 3: map_us (d, a + off, (i32 *) b + off, n); break;
	      case 4: map_rs (d, (i32 *) a + off, (i32 *) b + off, n); break;
	      case 5: map_ru (d, a + off, b + off, n); break;
	      case 6: map_rsu (d, (i32 *) a + off, b + off, n); break;
	      case 7: map_rus (d, a + off, (i32 *) b + off, n); break;
	      }
	    for (unsigned i = 0; i < SIZE; ++i)
	      if (a[i] != ra[i] || b[i] != rb[i])
		__builtin_abort ();
	  }
  return 0;
}
