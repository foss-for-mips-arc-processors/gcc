/* { dg-do run } */
/* { dg-options "-O3" } */

#include "scalar-uabd.h"

static unsigned int __attribute__ ((noipa, optimize ("O0")))
diff (int a, int b)
{
  return a >= b ? a - b : b - a;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  unsigned short a[272] __attribute__ ((aligned (16)));
  unsigned short b[272] __attribute__ ((aligned (16)));
  for (unsigned int i = 0; i < 65536; ++i)
    for (unsigned int k = 0; k < 4; ++k)
      {
	unsigned short x = i;
	unsigned short y = k == 0 ? 0 : k == 1 ? 65535
	  : k == 2 ? i * 65521 + 32768 : i * 257 + 32767;
	unsigned int expected = diff (x, y);
	unsigned long nx = (unsigned long) i * 0xdeadbeefUL + x;
	unsigned long ny = ~(unsigned long) i * 0x1234567UL + y;
	if (half_diff (x, y) != expected || half_wide (x, y) != expected
	    || half_load (&x, &y) != expected
	    || signed_control ((short) x, (short) y) != diff ((short) x, (short) y)
	    || native_diff (nx, ny) != diff (nx & 65535, ny & 65535)
	    || wide_control (nx, ny) != diff (nx & 131071, ny & 131071))
	  __builtin_abort ();
	if (byte_diff (i >> 8, i & 255) != diff (i >> 8, i & 255))
	  __builtin_abort ();
      }
  for (unsigned int i = 0; i < 272; ++i)
    {
      a[i] = i % 5 ? i * 65521 + 32768 : 0;
      b[i] = i % 5 ? i * 257 + 32767 : 65535;
    }
  for (unsigned int n = 0; n <= 257; ++n)
    for (unsigned int x = 0; x < 8; ++x)
      for (unsigned int y = 0; y < 8; ++y)
	{
	  unsigned long long expected = 0;
	  for (unsigned int i = 0; i < n; ++i)
	    expected += diff (a[x + i], b[y + i]);
	  if (half_loop (a + x, b + y, n) != expected)
	    __builtin_abort ();
	}
  return 0;
}
