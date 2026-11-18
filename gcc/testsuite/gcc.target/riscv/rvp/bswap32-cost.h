void
swap_words (unsigned int *restrict out, const unsigned int *restrict in,
	    unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = __builtin_bswap32 (in[i]);
}

void
swap_halfwords (unsigned short *restrict out, const unsigned short *restrict in,
		unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = __builtin_bswap16 (in[i]);
}
