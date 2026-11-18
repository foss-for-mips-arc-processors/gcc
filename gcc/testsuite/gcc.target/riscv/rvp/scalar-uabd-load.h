#define FN __attribute__ ((noipa))

unsigned int FN
load_byte (const unsigned char *a, const unsigned char *b)
{
  return __builtin_abs ((int) *a - (int) *b);
}

unsigned int FN
load_half (const unsigned short *a, const unsigned short *b)
{
  return __builtin_abs ((int) *a - (int) *b);
}

unsigned int FN
shared_load (unsigned long long *out, const unsigned short *a,
	     const unsigned short *b)
{
  unsigned int x = *a, y = *b;
  out[0] = (unsigned long long) x << 40;
  out[1] = ((unsigned long long) x << 32) | y;
  return __builtin_abs ((int) x - (int) y);
}

unsigned int FN
volatile_load (const volatile unsigned short *p)
{
  unsigned int x = *p, y = *p;
  return __builtin_abs ((int) x - (int) y);
}

unsigned int FN
alias_load (unsigned short *p, unsigned short *q)
{
  unsigned int x = *p;
  *q = x ^ 65535;
  unsigned int y = *p;
  return __builtin_abs ((int) x - (int) y);
}

unsigned int FN
signed_load (const short *a, const short *b)
{
  return __builtin_abs ((int) *a - (int) *b);
}

unsigned int FN
narrow_load (const unsigned short *a, const unsigned short *b)
{
  return __builtin_abs ((short) ((int) *a - (int) *b));
}

struct __attribute__ ((packed)) packed_half
{
  unsigned char padding;
  unsigned short value;
};

unsigned int FN
packed_load (const struct packed_half *a, const struct packed_half *b)
{
  return __builtin_abs ((int) a->value - (int) b->value);
}
