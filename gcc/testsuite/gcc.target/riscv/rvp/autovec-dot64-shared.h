/* Preserve the word products when a widened reduction has another user.  */

long long __attribute__ ((noipa))
dot_shared (int *restrict out, const short *restrict a,
	    const short *restrict b)
{
  out = __builtin_assume_aligned (out, 8);
  a = __builtin_assume_aligned (a, 8);
  b = __builtin_assume_aligned (b, 8);
  long long sum = 0;
  for (unsigned int i = 0; i < 128; ++i)
    {
      int product = (int) a[i] * b[i];
      out[i] = product;
      sum += product;
    }
  return sum;
}
