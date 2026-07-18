/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-cunroll-details" } */

unsigned short data;

__attribute__ ((optimize ("unroll-loops")))
void
explicit_attr_cunroll (void)
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

/* { dg-final { scan-tree-dump "loop with 7 iterations completely unrolled" "cunroll" } } */
