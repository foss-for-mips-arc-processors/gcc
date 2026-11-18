/* { dg-do run } */
/* { dg-options "-O2" } */

#include "scalar-extend.h"

int
main (void)
{
  static const unsigned int unsigned_edges[] =
    { 0, 1, 0x7fffffffU, 0x80000000U, 0xfffffffeU, 0xffffffffU };
  static const int signed_edges[] =
    { 0, 1, -1, 2147483647, -2147483647 - 1, -2147483647 };
  static const extend_uint64 unsigned_expected[] =
    { 0ULL, 1ULL, 0x7fffffffULL, 0x80000000ULL,
      0xfffffffeULL, 0xffffffffULL };
  static const extend_int64 signed_expected[] =
    { 0LL, 1LL, -1LL, 2147483647LL, -2147483648LL, -2147483647LL };
  for (unsigned int i = 0; i < 6; ++i)
    {
      unsigned int u = unsigned_edges[i];
      int s = signed_edges[i];
      extend_uint64 u_expected = unsigned_expected[i];
      extend_int64 s_expected = signed_expected[i];
      if (extend_u0 (u) != u_expected
          || extend_u1 (0x51, u) != u_expected
          || extend_u2 (0x51, 0xa2, u) != u_expected
          || extend_um (&u) != u_expected
          || extend_s0 (s) != s_expected
          || extend_s1 (0x51, s) != s_expected
          || extend_s2 (0x51, 0xa2, s) != s_expected
          || extend_sm (&s) != s_expected)
        __builtin_abort ();
    }
  if (extend_add64 (0xffffffffULL, 1) != 0x100000000ULL
      || extend_sub64 (0x100000000ULL, 1) != 0xffffffffULL
      || extend_neg64 (1) != 0xffffffffffffffffULL
      || extend_umul (0xffffffffU, 0xffffffffU) != 0xfffffffe00000001ULL
      || extend_smul (-2147483647 - 1, -2147483647 - 1)
         != 0x4000000000000000LL
      || extend_sumul (-2147483647 - 1, 0xffffffffU)
         != -9223372034707292160LL
      || extend_uadd (0xffffffffU, 1) != 0x100000000ULL
      || extend_usub (0, 1) != 0xffffffffffffffffULL
      || extend_sadd (-2147483647 - 1, -2147483647 - 1) != -4294967296LL
      || extend_ssub (2147483647, -2147483647 - 1) != 4294967295LL
      || extend_umacc (1, 0xffffffffU, 0xffffffffU)
         != 0xfffffffe00000002ULL
      || extend_smacc (0xffffffffffffffffULL, -2147483647 - 1, 1)
         != 0xffffffff7fffffffULL
      || extend_sumacc (0, -2147483647 - 1, 0xffffffffU)
         != 0x8000000080000000ULL
      || extend_umsub (0, 0xffffffffU, 0xffffffffU) != 0x1ffffffffULL
      || extend_smsub (0, -2147483647 - 1, 1) != 0x80000000ULL)
    __builtin_abort ();
  if (extend_uwadda (1, 0xffffffffU, 1) != 0x100000001ULL
      || extend_swadda (0, -2147483647 - 1, -2147483647 - 1)
         != 0xffffffff00000000ULL
      || extend_uwsuba (1, 0, 1) != 0
      || extend_swsuba (1, 2147483647, -2147483647 - 1) != 0x100000000ULL
      || extend_u_add (1, 0xffffffffU) != 0x100000000ULL
      || extend_s_add (1, -2147483647 - 1) != 0xffffffff80000001ULL)
    __builtin_abort ();
  if (extend_dot (0x80008000U, 0x80008000U) != 2147483648LL
      || extend_dot (0x80007fffU, 0x7fff8000U) != -2147418112LL
      || extend_cross_dot (0x80007fffU, 0x7fff8000U) != 2147418113LL
      || extend_difference (0x00018000U, 0x00028000U) != 1073741822LL
      || extend_cross_difference (0x00018000U, 0x80000002U) != 1073741822LL
      || extend_scaled_low (0xffffffffU, 1) != -1LL
      || extend_scaled_low (0x80000000U, 0x8000U) != 1073741824LL
      || extend_scaled_high (0xffffffffU, 0x10000U) != -1LL
      || extend_scaled_high (0x80000000U, 0x8000ffffU) != 1073741824LL
      || extend_scaled_low_si (0xffffffffU, 1) != -1
      || extend_scaled_low_si (0x80000000U, 0x8000U) != 1073741824
      || extend_scaled_high_si (0xffffffffU, 0x10000U) != -1
      || extend_scaled_high_si (0x80000000U, 0x8000ffffU) != 1073741824)
    __builtin_abort ();
  return 0;
}
