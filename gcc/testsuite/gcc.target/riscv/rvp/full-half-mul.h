typedef unsigned short full_u16x4 __attribute__ ((vector_size (8)));
typedef short full_s16x4 __attribute__ ((vector_size (8)));

__attribute__ ((noipa)) full_u16x4
full_mul (full_u16x4 a, full_u16x4 b)
{
  return a * b;
}

/* Interpret the signed input bits modulo 2^16, avoiding signed overflow.  */
__attribute__ ((noipa)) full_u16x4
full_mul_signed_bits (full_s16x4 a, full_s16x4 b)
{
  return (full_u16x4) a * (full_u16x4) b;
}

__attribute__ ((noipa)) full_u16x4
full_square (full_u16x4 a)
{
  return a * a;
}

__attribute__ ((noipa)) full_u16x4
full_mac (full_u16x4 acc, full_u16x4 a, full_u16x4 b)
{
  return acc + a * b;
}

__attribute__ ((noipa)) full_u16x4
full_msub (full_u16x4 acc, full_u16x4 a, full_u16x4 b)
{
  return acc - a * b;
}

__attribute__ ((noipa)) full_u16x4
full_shared (full_u16x4 a, full_u16x4 b)
{
  return (a * b) ^ (a + b);
}

__attribute__ ((noipa)) full_u16x4
full_pressure (full_u16x4 a, full_u16x4 b, full_u16x4 c, full_u16x4 d,
	       full_u16x4 e, full_u16x4 f, full_u16x4 g, full_u16x4 h)
{
  return (a * b) + (c * d) + (e * f) + (g * h)
    + (a ^ c ^ e ^ g) + (b ^ d ^ f ^ h);
}

__attribute__ ((noipa)) void
full_vector_loop (full_u16x4 *d, const full_u16x4 *a, const full_u16x4 *b,
		  unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = a[i] * b[i];
}

__attribute__ ((noipa)) void
full_scalar_loop (unsigned short *d, const unsigned short *a,
		  const unsigned short *b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (unsigned int) a[i] * b[i];
}

__attribute__ ((noipa)) void
full_scalar_mac (unsigned short *d, const unsigned short *a,
		 const unsigned short *b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] += (unsigned int) a[i] * b[i];
}
