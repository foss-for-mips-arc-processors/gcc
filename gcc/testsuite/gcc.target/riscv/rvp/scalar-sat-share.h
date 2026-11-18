/* Both the word and its widened value should use the same saturated sum.  */

unsigned long long
sat_shared (unsigned int x, unsigned int y)
{
  unsigned int r = x + y;
  r = r < x ? ~0u : r;
  return (unsigned long long) r + ((unsigned long long) (r ^ x) << 32)
    + (r > y);
}
