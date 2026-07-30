/* Test with multiple functions and control flow.  */

static int
helper (int x)
{
  if (x < 0)
    return -x;
  return x + 1;
}

int
compute (int a, int b)
{
  int sum = a + b;
  int abs_a = helper (a);
  int abs_b = helper (b);

  if (sum > abs_a + abs_b)
    return sum;
  return abs_a + abs_b;
}

int
main (void)
{
  return compute (3, -5);
}
