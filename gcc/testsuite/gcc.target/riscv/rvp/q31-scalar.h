/* Exact scalar Q31 products and controls with different arithmetic.  */
#define FN __attribute__ ((noipa))
#define Q31_SCALAR(NAME, TYPE, ROUND) \
TYPE FN \
NAME (int a, int b) \
{ \
  long long value = ((long long) a * b + (ROUND)) >> 31; \
  return value > 2147483647 ? 2147483647 : value; \
}

Q31_SCALAR (q31_scalar, int, 0)
Q31_SCALAR (q31_scalar_round, int, 1073741824)
Q31_SCALAR (q31_scalar_wide, long long, 0)
Q31_SCALAR (q31_scalar_round_wide, long long, 1073741824)

#define Q31_SAVE(NAME, ROUND) \
int FN \
NAME (int a, int b, long long *saved) \
{ \
  long long product = (long long) a * b; \
  long long value = (product + (ROUND)) >> 31; \
  *saved = product; \
  return value > 2147483647 ? 2147483647 : value; \
}

Q31_SAVE (q31_scalar_save, 0)
Q31_SAVE (q31_scalar_round_save, 1073741824)

int FN
q31_scalar_full (unsigned long long a, unsigned long long b,
		 unsigned long long *saved)
{
  long long value = ((long long) (int) a * (int) b) >> 31;
  *saved = a + b;
  return value > 2147483647 ? 2147483647 : value;
}

int FN
q31_scalar_cond (int a, int b, int select)
{
  long long product = (long long) a * b;
  if (select)
    {
      long long value = product >> 31;
      return value > 2147483647 ? 2147483647 : value;
    }
  return product >> 32;
}

int FN
q31_scalar_wrong_limit (int a, int b)
{
  long long value = ((long long) a * b) >> 31;
  return value > 2147483646 ? 2147483646 : value;
}

int FN
q31_scalar_wrong_round (int a, int b)
{
  long long value = ((long long) a * b + 1073741823) >> 31;
  return value > 2147483647 ? 2147483647 : value;
}

int FN
q31_scalar_unsigned (unsigned int a, unsigned int b)
{
  unsigned long long value = ((unsigned long long) a * b + 1073741824) >> 31;
  return value > 2147483647 ? 2147483647 : value;
}

int FN
q31_scalar_mixed (int a, unsigned int b)
{
  long long value = ((long long) a * b + 1073741824) >> 31;
  return value > 2147483647 ? 2147483647 : value;
}

int FN
q31_scalar_wrap (int a, int b)
{
  return ((long long) a * b) >> 31;
}

int FN
q31_scalar_truncated (int a, int b)
{
  int product = (long long) a * b;
  return product >> 31;
}

int FN
q31_scalar_shift32 (int a, int b)
{
  long long value = ((long long) a * b) >> 32;
  return value > 2147483647 ? 2147483647 : value;
}

int FN
q31_scalar_low_bits (int a, int b)
{
  long long value = ((long long) a * b) >> 31;
  return (short) (value > 2147483647 ? 2147483647 : value);
}
