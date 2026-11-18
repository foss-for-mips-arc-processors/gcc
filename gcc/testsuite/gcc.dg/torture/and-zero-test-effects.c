/* { dg-do run } */
/* { dg-require-effective-target inf } */

static volatile unsigned calls;

__attribute__ ((noipa)) unsigned
next_value (unsigned x)
{
  ++calls;
  return x;
}

__attribute__ ((noipa)) unsigned
both_zero (unsigned a, unsigned b)
{
  return (next_value (a) == 0) & (next_value (b) == 0);
}

__attribute__ ((noipa)) unsigned
inverse_flags (unsigned a, unsigned b)
{
  return ((next_value (a) & 1) ^ 1) & ((next_value (b) & 1) ^ 1);
}

__attribute__ ((noipa)) unsigned
mixed_modes (__UINT32_TYPE__ a, __UINT64_TYPE__ b)
{
  return (a == 0) & (b == 0);
}

__attribute__ ((noipa)) unsigned
floating_zero (double a, double b)
{
  return (a == 0.0) & (b == 0.0);
}

int
main (void)
{
  for (unsigned a = 0; a < 8; ++a)
    for (unsigned b = 0; b < 8; ++b)
      {
        calls = 0;
        unsigned result = both_zero (a, b);
        if (calls != 2 || result != (a + b == 0))
          __builtin_abort ();
        calls = 0;
        result = inverse_flags (a, b);
        if (calls != 2 || result != ((a | b) % 2 == 0))
          __builtin_abort ();
      }
  if (!mixed_modes (0, 0) || mixed_modes (0, 0x100000000ULL)
      || mixed_modes (0, 0x8000000000000000ULL) || mixed_modes (1, 0)
      || mixed_modes (0x80000000U, 0))
    __builtin_abort ();
  static const double values[] =
    { 0.0, -0.0, 1.0, -1.0, __builtin_inf (), -__builtin_inf (),
      __builtin_nan ("") };
  unsigned n = sizeof (values) / sizeof (values[0]);
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = 0; j < n; ++j)
      if (floating_zero (values[i], values[j]) != (i < 2 && j < 2))
        __builtin_abort ();
  return 0;
}
