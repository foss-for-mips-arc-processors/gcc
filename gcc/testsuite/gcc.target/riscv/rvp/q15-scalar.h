/* Scalar Q15 forms, promoted inputs and distinct arithmetic controls.  */
#define FN __attribute__ ((noipa))
#define Q15_SCALAR(NAME, WIDE, RESULT, ROUND) \
RESULT FN \
NAME (short a, short b) \
{ \
  WIDE value = ((WIDE) a * b + (ROUND)) >> 15; \
  return value > 32767 ? 32767 : value; \
}

Q15_SCALAR (q15_scalar, int, short, 0)
Q15_SCALAR (q15_scalar_round, int, short, 16384)
Q15_SCALAR (q15_scalar_wide, int, int, 0)
Q15_SCALAR (q15_scalar_ll, long long, long long, 0)
Q15_SCALAR (q15_scalar_ll_round, long long, long long, 16384)

int FN
q15_scalar_save (short a, short b, int *saved)
{
  int product = (int) a * b;
  int value = product >> 15;
  *saved = product;
  return value > 32767 ? 32767 : value;
}

long long FN
q15_scalar_round_save (short a, short b, long long *saved)
{
  long long product = (long long) a * b;
  long long value = (product + 16384) >> 15;
  *saved = product;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_full (unsigned long long a, unsigned long long b,
		 unsigned long long *saved)
{
  int value = ((int) (short) a * (short) b) >> 15;
  *saved = a + b;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_cond (short a, short b, int select)
{
  int product = (int) a * b;
  if (select)
    {
      int value = product >> 15;
      return value > 32767 ? 32767 : value;
    }
  return product >> 16;
}

int FN
q15_scalar_two_shifts (short a, short b)
{
  int value = ((((int) a * b) >> 14) + 1) >> 1;
  return value > 32767 ? 32767 : value;
}

long long FN
q15_scalar_ll_two_shifts (short a, short b)
{
  long long value = ((((long long) a * b) >> 14) + 1) >> 1;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_wrong_limit (short a, short b)
{
  int value = ((int) a * b) >> 15;
  return value > 32766 ? 32766 : value;
}

int FN
q15_scalar_wrong_round (short a, short b)
{
  long long value = ((long long) a * b + 16383) >> 15;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_wrong_two_shifts (short a, short b)
{
  int value = ((((int) a * b) >> 14) + 2) >> 1;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_unsigned (unsigned short a, unsigned short b)
{
  unsigned long long value = ((unsigned long long) a * b + 16384) >> 15;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_mixed (short a, unsigned short b)
{
  long long value = ((long long) a * b + 16384) >> 15;
  return value > 32767 ? 32767 : value;
}

int FN
q15_scalar_unsigned_cast (short a, short b)
{
  long long value = ((long long) (unsigned int) a * (unsigned short) b
		     + 16384) >> 15;
  return value > 32767 ? 32767 : value;
}

short FN
q15_scalar_wrap (short a, short b)
{
  return ((int) a * b) >> 15;
}

int FN
q15_scalar_truncated (short a, short b)
{
  short product = (int) a * b;
  return product >> 15;
}

int FN
q15_scalar_low_bits (short a, short b)
{
  int value = ((int) a * b) >> 15;
  return (signed char) (value > 32767 ? 32767 : value);
}
