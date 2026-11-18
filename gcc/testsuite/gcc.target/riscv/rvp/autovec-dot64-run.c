/* { dg-do run } */
/* { dg-options "-O3" } */

#include "autovec-dot64.h"
#include "autovec-dot64-negative.h"

static void __attribute__ ((noipa, optimize ("O0")))
check (const short *a, const short *b, const unsigned short *u,
       const unsigned short *v)
{
  long long ss = 0, su = 0, us = 0, truncated = 0, scaled = 0;
  unsigned long long uu = 0, extended = 0;
  for (unsigned int i = 0; i < 128; ++i)
    {
      long long p = (long long) a[i] * b[i];
      ss += p;
      uu += (unsigned long long) u[i] * v[i];
      su += (long long) a[i] * v[i];
      us += (long long) u[i] * b[i];
      unsigned int lo = (unsigned int) p & 65535;
      truncated += lo < 32768 ? (long long) lo : (long long) lo - 65536;
      scaled += p >= 0 ? p / 32768 : -((-p + 32767) / 32768);
      extended += (unsigned int) p;
    }
  if (dot_ss (a, b) != ss || dot_uu (u, v) != uu
      || dot_su (a, v) != su || dot_us (u, b) != us
      || dot_truncated (a, b) != truncated || dot_scaled (a, b) != scaled
      || dot_zero_extended_product (a, b) != extended)
    __builtin_abort ();
}

int
main (void)
{
  short a[128] __attribute__ ((aligned (8)));
  short b[128] __attribute__ ((aligned (8)));
  unsigned short u[128] __attribute__ ((aligned (8)));
  unsigned short v[128] __attribute__ ((aligned (8)));
  static const unsigned short edge[] = { 0, 1, 32767, 32768, 65535 };
  for (unsigned int j = 0; j < 5; ++j)
    for (unsigned int k = 0; k < 5; ++k)
      {
	for (unsigned int i = 0; i < 128; ++i)
	  {
	    a[i] = (short) edge[j];
	    b[i] = (short) edge[k];
	    u[i] = edge[j];
	    v[i] = edge[k];
	  }
	check (a, b, u, v);
      }
  return 0;
}
