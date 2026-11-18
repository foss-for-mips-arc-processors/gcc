/* { dg-do run } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-O3" } */

#include "round-mulhi-wide.h"

static uint64_t __attribute__ ((noipa, optimize ("O0")))
reference (uint64_t a, uint64_t b, unsigned int kind)
{
  uint64_t p = a * b;
  if ((kind == 0 || kind == 2) && (a >> 31))
    p -= b << 32;
  if (kind == 0 && (b >> 31))
    p -= a << 32;
  p += UINT64_C (2147483648);
  if (kind == 3)
    return p;
  uint32_t high = p >> 32;
  if (kind == 0 || kind == 2)
    return (int64_t) (int32_t) high;
  return high;
}

int
main (void)
{
  static const unsigned int lengths[] = { 0, 1, 2, 3, 7, 8, 9, 65, 128 };
  static const uint32_t edge[] = {
    0, 1, 2, 32767, 32768, 65535, 65536, 0x3fffffff,
    0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001,
    0xc0000000, 0xfffffffe, 0xffffffff
  };
  int32_t a[160], b[160];
  uint32_t ua[160], ub[160];
  uint64_t wa[160], wb[160], ud[160];
  int64_t d[160];
  for (unsigned int k = 0; k < 9; ++k)
    for (unsigned int kind = 0; kind < 5; ++kind)
      {
	for (unsigned int i = 0; i < 160; ++i)
	  {
	    a[i] = ua[i] = edge[i % 16];
	    b[i] = ub[i] = edge[(i * 7 + k) % 16];
	    wa[i] = (uint64_t) ua[i] << 32 | ub[i];
	    wb[i] = (uint64_t) ub[i] << 32 | ua[i];
	    d[i] = ud[i] = 42;
	  }
	unsigned int n = lengths[k];
	if (kind == 0)
	  round_s_wide_loop (d + 4, a + 1, b + 3, n);
	else if (kind == 1)
	  round_u_wide_loop (ud + 4, ua + 1, ub + 3, n);
	else if (kind == 2)
	  round_su_wide_loop (d + 4, a + 1, ub + 3, n);
	else if (kind == 3)
	  round_full_loop (ud + 4, ua + 1, ub + 3, n);
	else
	  round_unknown_loop (ud + 4, wa + 1, wb + 3, n);
	for (unsigned int i = 0; i < 160; ++i)
	  {
	    uint64_t expected = 42;
	    if (i >= 4 && i < n + 4)
	      expected = reference (kind == 4 ? wa[i - 3] : ua[i - 3],
				    kind == 4 ? wb[i - 1] : ub[i - 1], kind);
	    if (kind == 0 || kind == 2)
	      {
		if ((uint64_t) d[i] != expected || ud[i] != 42)
		  return 1;
	      }
	    else if (ud[i] != expected || d[i] != 42)
	      return 2;
	  }
      }
  return 0;
}
