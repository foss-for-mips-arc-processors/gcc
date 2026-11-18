/* Scalar saturating arithmetic from ordinary C.  */

unsigned __attribute__ ((noipa))
add_u (unsigned x, unsigned y)
{
  unsigned sum = x + y;
  return sum < x ? ~0u : sum;
}

unsigned __attribute__ ((noipa))
sub_u (unsigned x, unsigned y)
{
  return x < y ? 0 : x - y;
}

int __attribute__ ((noipa))
add_s_overflow (int x, int y)
{
  int sum;
  if (__builtin_add_overflow (x, y, &sum))
    return x < 0 ? (-2147483647 - 1) : 2147483647;
  return sum;
}

int __attribute__ ((noipa))
sub_s_overflow (int x, int y)
{
  int diff;
  if (__builtin_sub_overflow (x, y, &diff))
    return x < 0 ? (-2147483647 - 1) : 2147483647;
  return diff;
}
