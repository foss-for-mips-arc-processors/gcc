void
average_other (unsigned int *restrict d, const unsigned int *restrict a,
	       const unsigned int *restrict b,
	       const unsigned int *restrict c, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (a[i] & b[i]) + ((a[i] ^ c[i]) >> 1);
}

void
average_shared (unsigned int *restrict d, unsigned int *restrict q,
		unsigned int *restrict m, const unsigned int *restrict a,
		const unsigned int *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      unsigned int x = (a[i] ^ b[i]) >> 1, y = a[i] & b[i];
      d[i] = x + y;
      q[i] = x;
      m[i] = y;
    }
}

void
average_width (unsigned short *restrict d,
	       const unsigned short *restrict a,
	       const unsigned short *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (unsigned char) (a[i] & b[i])
      + (unsigned char) ((a[i] ^ b[i]) >> 1);
}
