/* { dg-do run } */
/* { dg-options "-O2 -fgimple" } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */

typedef unsigned int u32;
typedef unsigned long long u64;

__attribute__ ((noipa)) u64
__GIMPLE (ssa, startwith ("widening_mul"))
assign_path (u32 x, u32 y)
{
  _Bool c;
  u32 d;
  u64 w;
  u64 r;

__BB(2):
  c_3 = x_1(D) >= y_2(D);
  d_4 = x_1(D) - y_2(D);
  w_5 = (u64) d_4;
  r_6 = c_3 ? w_5 : 0ULL;
  return r_6;
}

__attribute__ ((noipa)) u64
__GIMPLE (ssa, startwith ("widening_mul"))
phi_path (u32 x, u32 y)
{
  u32 d;
  u64 w;
  u64 r;

__BB(2):
  if (x_1(D) >= y_2(D))
    goto __BB3;
  else
    goto __BB4;

__BB(3):
  d_3 = x_1(D) - y_2(D);
  w_4 = (u64) d_3;
  goto __BB4;

__BB(4):
  r_5 = __PHI (__BB2: 0ULL, __BB3: w_4);
  return r_5;
}

int
main (void)
{
  if (assign_path (0x80000000u, 0) != 0x80000000ULL
      || phi_path (0x80000000u, 0) != 0x80000000ULL
      || assign_path (1, 2) != 0 || phi_path (1, 2) != 0)
    __builtin_abort ();
  return 0;
}
