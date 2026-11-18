/* { dg-do run } */
/* { dg-options "-O2" } */

#include "scalar-sat-word.h"

int
main (void)
{
  static const unsigned edges[] =
    { 0, 1, 2, 0x7ffffffeU, 0x7fffffffU, 0x80000000U,
      0x80000001U, 0xfffffffeU, 0xffffffffU };
  for (unsigned i = 0; i < sizeof (edges) / sizeof (edges[0]); ++i)
    for (unsigned j = 0; j < sizeof (edges) / sizeof (edges[0]); ++j)
      {
        unsigned x = edges[i], y = edges[j];
        unsigned long long au = (unsigned long long) x + y;
        long long su = (long long) x - y;
        long long as = (long long) (int) x + (int) y;
        long long ss = (long long) (int) x - (int) y;
        if (au > 0xffffffffULL)
          au = 0xffffffffULL;
        if (su < 0)
          su = 0;
        if (as > 2147483647LL)
          as = 2147483647LL;
        if (as < -2147483648LL)
          as = -2147483648LL;
        if (ss > 2147483647LL)
          ss = 2147483647LL;
        if (ss < -2147483648LL)
          ss = -2147483648LL;
        if (add_u (x, y) != (unsigned) au
            || sub_u (x, y) != (unsigned) su
            || add_s_overflow ((int) x, (int) y) != (int) as
            || sub_s_overflow ((int) x, (int) y) != (int) ss)
          __builtin_abort ();
      }
  return 0;
}
