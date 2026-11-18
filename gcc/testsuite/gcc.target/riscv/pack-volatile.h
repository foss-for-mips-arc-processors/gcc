/* A discarded packed field must not discard its volatile producer.  */
unsigned long long __attribute__ ((noipa))
pack_volatile_sign (volatile unsigned int *a, unsigned int b)
{
  return (int) ((unsigned short) *a | (b << 16)) < 0;
}

unsigned long long __attribute__ ((noipa))
pack_volatile_step (volatile unsigned int **a, unsigned int b)
{
  return (int) ((unsigned short) *(*a)++ | (b << 16)) < 0;
}

unsigned long long __attribute__ ((noipa))
pack_volatile_twice (volatile unsigned int *a, volatile unsigned int *b)
{
  return (int) ((unsigned short) *a | (*b << 16)) < 0;
}

unsigned long long __attribute__ ((noipa))
pack_volatile_shared (volatile unsigned int *a, unsigned int b,
		      unsigned int *out)
{
  unsigned int low = *a;
  *out = low;
  return (int) ((unsigned short) low | (b << 16)) < 0;
}
