/* { dg-do run } */
/* { dg-require-effective-target stdint_types } */

#include <stdint.h>

/* Check equivalence-note substitutions when inputs remain live, are
   read from memory, or are used across a call.  */

static uint64_t __attribute__ ((noipa, optimize ("O0")))
product (uint32_t a, uint32_t b)
{
  uint64_t p = (uint64_t) a * b;
  if (a >> 31)
    p -= (uint64_t) b << 32;
  return p;
}

static uint32_t __attribute__ ((noipa, optimize ("O0")))
reference (uint32_t a, uint32_t b, uint64_t bias)
{
  return (product (a, b) + bias) >> 32;
}

static uint32_t __attribute__ ((noipa))
rounded (int32_t a, uint32_t b)
{
  return ((int64_t) a * (int64_t) b + INT64_C (2147483648)) >> 32;
}

static uint32_t __attribute__ ((noipa))
retained (int32_t a, uint32_t b, uint64_t *p)
{
  int64_t v = (int64_t) a * (int64_t) b;
  *p = v;
  return (v + INT64_C (2147483648)) >> 32;
}

static uint32_t __attribute__ ((noipa))
variable (int32_t a, uint32_t b, volatile uint64_t *bias)
{
  uint64_t v = (int64_t) a * (int64_t) b;
  return (v + *bias) >> 32;
}

static uint32_t __attribute__ ((noipa))
aliased (int32_t *a, const uint32_t *b)
{
  int32_t saved = *a;
  *a = ~saved;
  return ((int64_t) saved * (int64_t) *b
	  + INT64_C (2147483648)) >> 32;
}

static uint32_t __attribute__ ((noipa))
advance (uint32_t *p)
{
  *p = *p * 1664525u + 1013904223u;
  return *p;
}

static uint32_t __attribute__ ((noipa))
across_call (int32_t a, uint32_t b, uint32_t *p)
{
  int64_t v = (int64_t) a * (int64_t) b;
  uint32_t q = advance (p);
  return ((v + INT64_C (2147483648)) >> 32) ^ q;
}

static uint32_t __attribute__ ((noipa))
narrowed (int32_t a, uint32_t b)
{
  int16_t x = a;
  uint16_t y = b;
  return ((int64_t) x * y + INT64_C (2147483648)) >> 32;
}

static void
check (uint32_t a, uint32_t b)
{
  const uint64_t bias = UINT64_C (2147483648);
  uint32_t expected = reference (a, b, bias);
  uint64_t p;
  if (rounded (a, b) != expected || retained (a, b, &p) != expected
      || p != product (a, b))
    __builtin_abort ();

  static const uint64_t biases[] = {
    0, 1, UINT64_C (2147483647), UINT64_C (2147483648),
    UINT64_C (2147483649), UINT64_MAX
  };
  for (unsigned int i = 0; i < sizeof (biases) / sizeof (biases[0]); ++i)
    {
      volatile uint64_t v = biases[i];
      if (variable (a, b, &v) != reference (a, b, biases[i]))
	__builtin_abort ();
    }

  int32_t x = a;
  if (aliased (&x, &b) != expected || (uint32_t) x != ~a)
    __builtin_abort ();
  x = a;
  if (aliased (&x, (uint32_t *) &x) != reference (a, ~a, bias)
      || (uint32_t) x != ~a)
    __builtin_abort ();

  uint32_t state = b;
  uint32_t next = b * 1664525u + 1013904223u;
  if (across_call (a, b, &state) != (expected ^ next) || state != next)
    __builtin_abort ();
  if (narrowed (a, b) != reference ((int16_t) a, (uint16_t) b, bias))
    __builtin_abort ();
}

int
main (void)
{
  static const uint32_t values[] = {
    0, 1, 32767, 32768, 65535, 65536, 0x3fffffff, 0x40000000,
    0x7fffffff, 0x80000000, 0x80000001, 0xc0000000, 0xfffffffe, 0xffffffff
  };
  for (unsigned int i = 0; i < sizeof (values) / sizeof (values[0]); ++i)
    for (unsigned int j = 0; j < sizeof (values) / sizeof (values[0]); ++j)
      check (values[i], values[j]);

  uint32_t state = 123456789;
  for (unsigned int i = 0; i < 4096; ++i)
    {
      uint32_t a = advance (&state);
      uint32_t b = advance (&state);
      check (a, b);
    }
  return 0;
}
