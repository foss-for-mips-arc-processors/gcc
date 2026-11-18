/* { dg-do run } */
/* { dg-additional-options "-fcompare-debug" } */

/* Semantic controls for branch-local copies and loop-carried definitions.
   These do not require a particular copy to survive earlier passes.  */

static unsigned int __attribute__ ((noipa))
branch_copy (unsigned int x, unsigned int y, unsigned int n, int arm)
{
  unsigned int saved = x;
  if (arm)
    {
      for (unsigned int i = 0; i < n; ++i)
	saved = saved * 33 + y + i;
      return saved;
    }
  return x + 9;
}

static unsigned int __attribute__ ((noipa))
redefined_source (unsigned int x, unsigned int y, unsigned int n, int arm)
{
  unsigned int saved = x;
  x = y;
  if (arm)
    {
      for (unsigned int i = 0; i < n; ++i)
	saved = saved * 33 + x + i;
      return saved;
    }
  return x;
}

static unsigned int __attribute__ ((noipa))
both_arms (unsigned int x, unsigned int y, unsigned int n, int arm)
{
  unsigned int saved = x;
  if (arm)
    for (unsigned int i = 0; i < n; ++i)
      saved = saved * 33 + y + i;
  else
    for (unsigned int i = 0; i < n; ++i)
      saved = saved * 17 + y + i;
  return saved;
}

static unsigned int __attribute__ ((noipa))
dependent_copies (unsigned int x, unsigned int y, unsigned int n, int arm)
{
  unsigned int a = x, b = a;
  if (arm)
    {
      for (unsigned int i = 0; i < n; ++i)
	b = b * 33 + y + i;
      return b;
    }
  for (unsigned int i = 0; i < n; ++i)
    a = a * 17 + y + i;
  return a;
}

static unsigned int __attribute__ ((noipa, optimize ("O0")))
reference (unsigned int x, unsigned int y, unsigned int n, unsigned int factor)
{
  for (unsigned int i = 0; i < n; ++i)
    x = x * factor + y + i;
  return x;
}

int
main (void)
{
  static const unsigned int values[] =
    { 0, 1, 7, ~0U / 2, ~0U / 2 + 1, ~0U - 1, ~0U };
  for (unsigned int i = 0; i < sizeof values / sizeof values[0]; ++i)
    for (unsigned int j = 0; j < sizeof values / sizeof values[0]; ++j)
      for (unsigned int n = 0; n < 18; ++n)
	for (int arm = 0; arm < 2; ++arm)
	  {
	    unsigned int x = values[i], y = values[j];
	    unsigned int a = reference (x, y, n, 33);
	    unsigned int b = arm ? a : reference (x, y, n, 17);
	    if (branch_copy (x, y, n, arm) != (arm ? a : x + 9)
		|| redefined_source (x, y, n, arm) != (arm ? a : y)
		|| both_arms (x, y, n, arm) != b
		|| dependent_copies (x, y, n, arm) != b)
	      __builtin_abort ();
	  }
  return 0;
}
