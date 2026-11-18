typedef unsigned int v2si __attribute__ ((vector_size (8)));

v2si masked_both (v2si, v2si);
v2si masked_asymmetric (v2si, v2si);
v2si masked_commuted (v2si, v2si);
v2si masked_shared (v2si, v2si);
v2si masked_one (v2si, v2si);
v2si masked_nonimmediate (v2si, v2si);
v2si masked_retained (v2si, v2si, v2si *, v2si *);
void masked_loop (unsigned int *, const unsigned int *, const unsigned int *,
		  unsigned int);
unsigned int masked_sum (const unsigned int *, const unsigned int *,
			 unsigned int);

#ifndef RVP_MASKED_DECLARATIONS_ONLY
v2si __attribute__ ((noipa))
masked_both (v2si a, v2si b)
{
  return (a & (v2si) { 15, 15 }) * (b & (v2si) { 127, 127 });
}

v2si __attribute__ ((noipa))
masked_asymmetric (v2si a, v2si b)
{
  return (a & (v2si) { -2048u, 127 }) * (b & (v2si) { 2047, -1u });
}

v2si __attribute__ ((noipa))
masked_commuted (v2si a, v2si b)
{
  return (b & (v2si) { 127, 127 }) * (a & (v2si) { 15, 15 });
}

v2si __attribute__ ((noipa))
masked_shared (v2si a, v2si b)
{
  return (a & (v2si) { 15, 15 }) * (a & (v2si) { 127, 127 });
}

v2si __attribute__ ((noipa))
masked_one (v2si a, v2si b)
{
  return (a & (v2si) { 15, 15 }) * b;
}

v2si __attribute__ ((noipa))
masked_nonimmediate (v2si a, v2si b)
{
  return (a & (v2si) { 2048, -2049u }) * (b & (v2si) { 127, 127 });
}

v2si __attribute__ ((noipa))
masked_retained (v2si a, v2si b, v2si *left, v2si *right)
{
  a &= (v2si) { 15, 15 };
  b &= (v2si) { 127, 127 };
  *left = a;
  *right = b;
  return a * b;
}

void __attribute__ ((noipa))
masked_loop (unsigned int *restrict out, const unsigned int *restrict a,
	     const unsigned int *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    out[i] = (a[i] & 2047) * (b[i] & -2048u);
}

unsigned int __attribute__ ((noipa))
masked_sum (const unsigned int *a, const unsigned int *b, unsigned int n)
{
  unsigned int sum = 0;
  for (unsigned int i = 0; i < n; ++i)
    sum += (a[i] & 15) * (b[i] & 127);
  return sum;
}
#endif
