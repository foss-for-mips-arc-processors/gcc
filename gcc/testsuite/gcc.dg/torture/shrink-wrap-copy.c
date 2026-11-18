/* { dg-do run } */

/* Check early exits and live parameters across a call, including a path
   that needs a frame pointer for a dynamic stack allocation.  */

unsigned int __attribute__ ((noipa))
sum (const unsigned int *p, unsigned int n)
{
  unsigned int r = 0;
  for (unsigned int i = 0; i < n; ++i)
    r += p[i];
  return r;
}

unsigned int __attribute__ ((noipa))
test (unsigned int a, unsigned int b, unsigned int c, unsigned int d,
      unsigned int n)
{
  if (!n)
    return a ^ c;
  if (n == 1)
    return b + d;

  unsigned int *p = __builtin_alloca (n * sizeof (*p));
  for (unsigned int i = 0; i < n; ++i)
    p[i] = (a + i * b) ^ (c - i * d);
  unsigned int r = sum (p, n);
  return r + a - b + c - d;
}

int
main (void)
{
  const unsigned int values[] = { 0, 1, 17, 255, 65535, ~0U, ~0U / 2 };
  for (unsigned int i = 0; i < 7; ++i)
    for (unsigned int j = 0; j < 7; ++j)
      for (unsigned int n = 0; n < 40; ++n)
	{
	  unsigned int a = values[i];
	  unsigned int b = values[j];
	  unsigned int c = values[(i + 2) % 7];
	  unsigned int d = values[(j + 4) % 7];
	  unsigned int expected = 0;
	  if (!n)
	    expected = a ^ c;
	  else if (n == 1)
	    expected = b + d;
	  else
	    {
	      /* Use volatile intermediates to keep the oracle independent of
		 the loop transformations used by the function under test.  */
	      volatile unsigned int x = a;
	      volatile unsigned int y = c;
	      for (unsigned int k = 0; k < n; ++k)
		{
		  expected += x ^ y;
		  x += b;
		  y -= d;
		}
	      expected += a - b + c - d;
	    }
	  if (test (a, b, c, d, n) != expected)
	    __builtin_abort ();
	}
  return 0;
}
