#define FN __attribute__ ((noipa))

unsigned int FN
byte_diff (unsigned char a, unsigned char b)
{
  return __builtin_abs ((int) a - (int) b);
}

unsigned int FN
half_diff (unsigned short a, unsigned short b)
{
  return __builtin_abs ((int) a - (int) b);
}

unsigned long long FN
half_wide (unsigned short a, unsigned short b)
{
  return __builtin_abs ((int) a - (int) b);
}

unsigned long FN
native_diff (unsigned long a, unsigned long b)
{
  return __builtin_labs ((long) (a & 65535) - (long) (b & 65535));
}

unsigned int FN
half_load (const unsigned short *a, const unsigned short *b)
{
  return __builtin_abs ((int) *a - (int) *b);
}

unsigned long long FN
half_loop (const unsigned short *a, const unsigned short *b, unsigned int n)
{
  unsigned long long sum = 0;
  for (unsigned int i = 0; i < n; ++i)
    sum += __builtin_abs ((int) a[i] - (int) b[i]);
  return sum;
}

unsigned int FN
signed_control (short a, short b)
{
  return __builtin_abs ((int) a - (int) b);
}

unsigned int FN
wide_control (unsigned int a, unsigned int b)
{
  return __builtin_abs ((int) (a & 131071) - (int) (b & 131071));
}
