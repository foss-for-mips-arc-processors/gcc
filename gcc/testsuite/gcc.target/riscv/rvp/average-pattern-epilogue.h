void
half (short *restrict d, const short *restrict a, unsigned int n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}
