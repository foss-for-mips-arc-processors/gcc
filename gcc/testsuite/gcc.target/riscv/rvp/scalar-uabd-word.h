#define FN __attribute__ ((noipa))

unsigned int FN
word_byte_add (unsigned char a, unsigned char b, unsigned int sum)
{
  return sum + __builtin_abs ((int) a - (int) b);
}

unsigned int FN
word_half_add (unsigned short a, unsigned short b, unsigned int sum)
{
  return sum + __builtin_abs ((int) a - (int) b);
}

unsigned int FN
word_load_add (const unsigned short *a, const unsigned short *b,
	       unsigned int sum)
{
  return sum + __builtin_abs ((int) *a - (int) *b);
}

unsigned int FN
word_loop (const unsigned short *a, const unsigned short *b,
	   unsigned int n, unsigned int sum)
{
  for (unsigned int i = 0; i < n; ++i)
    sum += __builtin_abs ((int) a[i] - (int) b[i]);
  return sum;
}
