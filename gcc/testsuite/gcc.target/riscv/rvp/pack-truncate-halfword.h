/* Truncate arbitrary wide inputs before inserting halfword fields.  */

unsigned int
wide_insert (unsigned long long a, unsigned long long b)
{
  return (unsigned short) a | ((unsigned int) b & 0xffff0000U);
}

unsigned long long
wide_insert_zero (unsigned long long a, unsigned long long b)
{
  return (unsigned int) ((unsigned short) a
                        | ((unsigned int) b & 0xffff0000U));
}

long long
wide_insert_sign (unsigned long long a, unsigned long long b)
{
  return (int) ((unsigned short) a | ((unsigned int) b & 0xffff0000U));
}

unsigned int
wide_pair_odd (unsigned long long a, unsigned long long b)
{
  return ((unsigned int) a >> 16) | ((unsigned int) b & 0xffff0000U);
}

unsigned long long
wide_pair_odd_zero (unsigned long long a, unsigned long long b)
{
  return (unsigned int) (((unsigned int) a >> 16)
                        | ((unsigned int) b & 0xffff0000U));
}

long long
wide_pair_odd_sign (unsigned long long a, unsigned long long b)
{
  return (int) (((unsigned int) a >> 16)
                | ((unsigned int) b & 0xffff0000U));
}
