/* Aliasing requires scalar and vector versions of these loops.  After
   copy propagation simplifies the alias checks, scalar pointer copies
   can move into the scalar path without changing the vector path.  */

void __attribute__ ((noipa))
map_signed (unsigned int *d, const int *a, const int *b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] += (unsigned int) (((long long) a[i] * b[i]) >> 32);
}

void __attribute__ ((noipa))
map_unsigned (unsigned int *d, const unsigned int *a, const unsigned int *b,
	      unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] += (unsigned int) (((unsigned long long) a[i] * b[i]) >> 32);
}
