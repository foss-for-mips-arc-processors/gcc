#define FN __attribute__ ((noipa))

unsigned long FN
byte_acc (unsigned char a, unsigned char b, unsigned long sum)
{
  return sum + __builtin_abs ((int) a - (int) b);
}

unsigned long FN
load_acc (const unsigned char *a, const unsigned char *b, unsigned long sum)
{
  return sum + __builtin_abs ((int) *a - (int) *b);
}

unsigned long FN
loop_acc (const unsigned char *a, const unsigned char *b, unsigned int n,
	  unsigned long sum)
{
  for (unsigned int i = 0; i < n; ++i)
    sum += __builtin_abs ((int) a[i] - (int) b[i]);
  return sum;
}

unsigned long FN
overlap_acc (unsigned char a, unsigned char b)
{
  return (unsigned long) a + __builtin_abs ((int) a - (int) b);
}

unsigned long FN
retained_acc (unsigned char a, unsigned char b, unsigned long sum,
	      unsigned int *saved)
{
  unsigned int d = __builtin_abs ((int) a - (int) b);
  *saved = d;
  return sum + d;
}

unsigned long FN
high_acc (unsigned long a, unsigned long b, unsigned long sum,
	  unsigned long *saved)
{
  *saved = a ^ b;
  return sum + __builtin_abs ((int) (unsigned char) a
			     - (int) (unsigned char) b);
}

unsigned long FN
half_control (unsigned short a, unsigned short b, unsigned long sum)
{
  return sum + __builtin_abs ((int) a - (int) b);
}

unsigned long FN
signed_control (signed char a, signed char b, unsigned long sum)
{
  return sum + __builtin_abs ((int) a - (int) b);
}
