/* { dg-do run } */
/* { dg-options "-O3" } */

#include "scalar-uabd-load.h"

int __attribute__ ((optimize ("O0")))
main (void)
{
  for (unsigned int i = 0; i < 65536; ++i)
    {
      unsigned char ca = i, cb = i >> 8;
      int byte_diff = (int) ca - (int) cb;
      if (load_byte (&ca, &cb) != (byte_diff < 0 ? -byte_diff : byte_diff))
	__builtin_abort ();
      for (unsigned int j = 0; j < 3; ++j)
	{
	  unsigned short a = i, b = j == 0 ? 0 : j == 1 ? 65535 : i * 31337;
	  short sa = a, sb = b;
	  int diff = (int) a - (int) b;
	  unsigned int expected = diff < 0 ? -diff : diff;
	  short narrowed = (short) diff;
	  int signed_diff = (int) sa - (int) sb;
	  unsigned long long out[2];
	  volatile unsigned short v = a;
	  struct packed_half pa = { 17, a }, pb = { 93, b };
	  if (load_half (&a, &b) != expected
	      || shared_load (out, &a, &b) != expected
	      || out[0] != (unsigned long long) a << 40
	      || out[1] != (((unsigned long long) a << 32) | b)
	      || volatile_load (&v) != 0
	      || signed_load (&sa, &sb)
		 != (signed_diff < 0 ? -signed_diff : signed_diff)
	      || narrow_load (&a, &b) != (narrowed < 0 ? -narrowed : narrowed)
	      || packed_load (&pa, &pb) != expected)
	    __builtin_abort ();
	  unsigned short saved = a;
	  if (alias_load (&a, &b) != 0 || a != saved || b != (saved ^ 65535))
	    __builtin_abort ();
	  diff = (int) saved - (int) (saved ^ 65535);
	  if (alias_load (&a, &a) != (diff < 0 ? -diff : diff)
	      || a != (saved ^ 65535))
	    __builtin_abort ();
	}
    }
  return 0;
}
