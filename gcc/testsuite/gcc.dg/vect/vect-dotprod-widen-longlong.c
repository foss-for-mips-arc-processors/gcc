/* { dg-do run } */
/* { dg-require-effective-target vect_int } */

#include "tree-vect.h"

/* A single wide accumulator can still consume multiple packed inputs.  */
__attribute__ ((noipa)) long long
dot (const short *a, const short *b)
{
  long long sum = 0;
  for (unsigned int i = 0; i < 128; ++i)
    sum += (int) a[i] * b[i];
  return sum;
}

int
main (void)
{
  short a[128] __attribute__ ((aligned (16)));
  short b[128] __attribute__ ((aligned (16)));
  check_vect ();
  for (unsigned int i = 0; i < 128; ++i)
    {
      a[i] = -32768;
      b[i] = -32768;
      __asm__ volatile ("" : : : "memory");
    }
  if (dot (a, b) != 137438953472LL)
    __builtin_abort ();
  for (unsigned int i = 0; i < 128; ++i)
    {
      b[i] = i & 1 ? 32767 : -32768;
      __asm__ volatile ("" : : : "memory");
    }
  if (dot (a, b) != 2097152LL)
    __builtin_abort ();
  return 0;
}
