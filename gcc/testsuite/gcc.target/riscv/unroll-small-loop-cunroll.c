/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-cunroll-details" } */

unsigned short data;

void
small_loop_cunroll (void)
{
  unsigned char x;

  for (unsigned int i = 0; i < 8; ++i)
    {
      x = data & 1;
      data >>= 1;
      if (x == 1)
	data ^= 0x4;
      data >>= 1;
    }
}

/* { dg-final { scan-tree-dump "Not unrolling loop \[0-9\]\+: size would grow" "cunroll" } } */
/* { dg-final { scan-tree-dump-not "completely unrolled" "cunroll" } } */
