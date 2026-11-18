/* { dg-do run } */
/* { dg-options "-O3" } */

#include "autovec-dot64-shared.h"

int __attribute__ ((optimize ("O0")))
main (void)
{
  short a[128] __attribute__ ((aligned (8)));
  short b[128] __attribute__ ((aligned (8)));
  int out[132] __attribute__ ((aligned (8)));
  static const short edge[] = { 0, 1, -1, 32767, -32768 };
  for (unsigned int j = 0; j < 5; ++j)
    for (unsigned int k = 0; k < 5; ++k)
      {
	long long expected = 0;
	for (unsigned int i = 0; i < 132; ++i)
	  out[i] = 0x12345678;
	for (unsigned int i = 0; i < 128; ++i)
	  {
	    a[i] = edge[(j + i) % 5];
	    b[i] = edge[(k + i / 5) % 5];
	    expected += (long long) a[i] * b[i];
	  }
	if (dot_shared (out + 2, a, b) != expected)
	  __builtin_abort ();
	for (unsigned int i = 0; i < 128; ++i)
	  if (out[i + 2] != (int) a[i] * b[i])
	    __builtin_abort ();
	if (out[0] != 0x12345678 || out[1] != 0x12345678
	    || out[130] != 0x12345678 || out[131] != 0x12345678)
	  __builtin_abort ();
      }
  return 0;
}
