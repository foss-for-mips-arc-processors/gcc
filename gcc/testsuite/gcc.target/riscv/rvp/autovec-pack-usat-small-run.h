#include "autovec-pack-usat-small.h"

int __attribute__ ((optimize ("no-tree-vectorize")))
main (void)
{
  uint16_t src[4] __attribute__ ((aligned (8)));
  uint8_t dst[8] __attribute__ ((aligned (8)));

  for (unsigned int base = 0; base < 65536; base += 4)
    {
      for (unsigned int i = 0; i < 4; ++i)
	src[i] = base + i;
      for (unsigned int i = 0; i < 8; ++i)
	dst[i] = 42;

      pack_four_unsigned (dst, src);

      for (unsigned int i = 0; i < 4; ++i)
	if (dst[i] != (base + i < 256 ? base + i : 255))
	  __builtin_abort ();
      for (unsigned int i = 4; i < 8; ++i)
	if (dst[i] != 42)
	  __builtin_abort ();
    }
  return 0;
}
