void
average_xor (unsigned short *restrict d,
	     const unsigned short *restrict a,
	     const unsigned short *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (a[i] & b[i]) + ((a[i] ^ b[i]) >> 1);
}

void
average_half (short *restrict d, const short *restrict a, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}
