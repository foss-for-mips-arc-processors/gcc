long long __attribute__ ((noipa))
dot_truncated (const short *a, const short *b)
{
  long long sum = 0;
  for (unsigned int i = 0; i < 128; ++i)
    sum += (short) ((int) a[i] * b[i]);
  return sum;
}

long long __attribute__ ((noipa))
dot_scaled (const short *a, const short *b)
{
  long long sum = 0;
  for (unsigned int i = 0; i < 128; ++i)
    sum += ((int) a[i] * b[i]) >> 15;
  return sum;
}

unsigned long long __attribute__ ((noipa))
dot_zero_extended_product (const short *a, const short *b)
{
  unsigned long long sum = 0;
  for (unsigned int i = 0; i < 128; ++i)
    sum += (unsigned int) ((int) a[i] * b[i]);
  return sum;
}
