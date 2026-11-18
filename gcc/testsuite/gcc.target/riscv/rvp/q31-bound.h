void
q31_bound (int *__restrict d, const int *__restrict a,
	   const int *__restrict b, unsigned n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  b = __builtin_assume_aligned (b, 8);
  for (__SIZE_TYPE__ i = 0; i < n; ++i)
    {
      long long t = ((long long) a[i + 2] * b[i + 4]) >> 31;
      d[i + 6] = t > 2147483647 ? 2147483647 : t;
    }
}
