/* { dg-do run } */
/* { dg-options "-O2" } */

#include "scalar-clrsb.h"

/* CLRSB is defined for every input, including zero and signed MIN.
   The word expectations use GCC's low-32-bit conversion to int.  Passing
   a long long to clrsb_low_word exercises unrelated upper bits without
   violating the ABI's sign-extended int-argument requirement.  */
static const struct
{
  long long input;
  int word_count;
  int doubleword_count;
} cases[] =
{
  { 0, 31, 63 },
  { -1, 31, 63 },
  { 1, 30, 62 },
  { -2, 30, 62 },
  { 2147483647LL, 0, 32 },
  { -2147483648LL, 0, 32 },
  { 0x3fffffffLL, 1, 33 },
  { -0x40000000LL, 1, 33 },
  { 0x80000000LL, 0, 31 },
  { 0xffffffffLL, 31, 31 },
  { 0x100000000LL, 31, 30 },
  { -0x100000000LL, 31, 31 },
  { -0xffffffffLL, 30, 31 },
  { 0x12345678ffffffffLL, 31, 2 },
  { 0x7fffffffffffffffLL, 31, 0 },
  { -0x7fffffffffffffffLL - 1, 31, 0 },
  { -0x7fffffffffffffffLL, 30, 0 }
};

int
main (void)
{
  unsigned int failed = 0;

  for (unsigned int i = 0; i < sizeof (cases) / sizeof (cases[0]); ++i)
    {
      int word = (int) cases[i].input;
      failed |= clrsb_word (word) != cases[i].word_count;
      failed |= clrsb_low_word (cases[i].input) != cases[i].word_count;
      failed |= clrsb_doubleword (cases[i].input) != cases[i].doubleword_count;
      failed |= clrsb_word_wide (word) != (unsigned int) cases[i].word_count;
#ifdef __riscv_p
      failed |= cls_intrinsic_word (word) != (unsigned int) cases[i].word_count;
      failed |= cls_intrinsic_word_high_bits (word) != 0;
#if __riscv_xlen == 64
      failed |= (cls_intrinsic_doubleword (cases[i].input)
                 != (unsigned int) cases[i].doubleword_count);
#endif
#endif
    }

  if (failed)
    __builtin_abort ();
  return 0;
}
