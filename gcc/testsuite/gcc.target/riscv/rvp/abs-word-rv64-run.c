/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d" } */

#include "abs-word-rv64.c"

/* GCC's conversion to int retains the low 32 bits.  Each converted input
   to abs is representable and is not INT_MIN; no llabs input is LLONG_MIN.
   The expected values are literals, not expressions using the tested fold.  */
static const struct
{
  long long input;
  int word_magnitude;
  long long magnitude_word;
} scalar_cases[] =
{
  { 0, 0, 0 },
  { 37, 37, 37 },
  { -37, 37, 37 },
  { 0x1fffffffeLL, 2, -2 },
  { -0x1fffffffeLL, 2, -2 },
  { 0x100000002LL, 2, 2 },
  { -0x100000002LL, 2, 2 },
  { 0x1ffffffffLL, 1, -1 },
  { -0x1ffffffffLL, 1, -1 },
  { 0x100000000LL, 0, 0 },
  { -0x100000000LL, 0, 0 },
  { 0x7fffffffffffffffLL, 1, -1 },
  { -0x7fffffffffffffffLL, 1, -1 },
  { 0x180000001LL, 2147483647, -2147483647 },
  { -0x180000001LL, 2147483647, -2147483647 }
};

static const v2si packed_cases[] =
{
  { -2, 37 },
  { 2, -37 },
  { -2147483647, 1 },
  { 2147483647, -1 },
  { -37, -2 },
  { 0, 0 }
};

static const v2si packed_expected[] =
{
  { 2, 37 },
  { 2, 37 },
  { 2147483647, 1 },
  { 2147483647, 1 },
  { 37, 2 },
  { 0, 0 }
};

int
main (void)
{
  unsigned int failed = 0;
  for (unsigned int i = 0;
       i < sizeof (scalar_cases) / sizeof (scalar_cases[0]); ++i)
    {
      failed |= (abs_low_word (scalar_cases[i].input)
                 != scalar_cases[i].word_magnitude);
      failed |= (abs_then_word (scalar_cases[i].input)
                 != scalar_cases[i].magnitude_word);
    }

  for (unsigned int i = 0;
       i < sizeof (packed_cases) / sizeof (packed_cases[0]); ++i)
    {
      struct
      {
        v2si before;
        v2si result;
        v2si after;
      } output = { { 17, 23 }, { 0, 0 }, { 29, 31 } };

      abs_packed_words (&packed_cases[i], &output.result);
      failed |= output.result[0] != packed_expected[i][0];
      failed |= output.result[1] != packed_expected[i][1];
      failed |= output.before[0] != 17;
      failed |= output.before[1] != 23;
      failed |= output.after[0] != 29;
      failed |= output.after[1] != 31;
    }

  if (failed)
    __builtin_abort ();
  return 0;
}
