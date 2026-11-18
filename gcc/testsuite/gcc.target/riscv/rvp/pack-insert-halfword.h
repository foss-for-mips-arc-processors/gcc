/* Scalar halfword insertion and cross-pairing of promoted words.  */
unsigned int
insert_low_halfword (unsigned int a, unsigned int b)
{
  return (a & 0xffffU) | (b & 0xffff0000U);
}

unsigned int
pair_cross_halfwords (unsigned int a, unsigned int b)
{
  return (a >> 16) | (b << 16);
}

unsigned int
pair_odd_halfwords (unsigned int a, unsigned int b)
{
  return (a >> 16) | (b & 0xffff0000U);
}

void
store_insert_low_halfword (unsigned int *out, unsigned int a, unsigned int b)
{
  *out = (a & 0xffffU) | (b & 0xffff0000U);
}

void
store_pair_cross_halfwords (unsigned int *out, unsigned int a, unsigned int b)
{
  *out = (a >> 16) | (b << 16);
}

void
store_pair_odd_halfwords (unsigned int *out, unsigned int a, unsigned int b)
{
  *out = (a >> 16) | (b & 0xffff0000U);
}

