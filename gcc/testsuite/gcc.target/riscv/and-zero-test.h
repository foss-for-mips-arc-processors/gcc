unsigned long
aligned_bounds (unsigned long a, unsigned long b, unsigned long alignment)
{
  return (a > 4) & (b > 4) & ((alignment & 3) == 0);
}
