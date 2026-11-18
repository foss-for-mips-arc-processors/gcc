/* { dg-do compile } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */
/* { dg-options "-O2 -fgimple -fdump-tree-phiopt1-details" } */

typedef unsigned int u32;
typedef unsigned long long u64;

#define PAIR(NAME, SOURCE, CONSTANT, RESULT) \
  RESULT __attribute__ ((noipa)) \
  __GIMPLE (ssa, startwith ("phiopt")) \
  NAME (u32 x, u32 y, u32 choose, u32 *out) \
  { \
    u32 narrow; \
    RESULT converted; \
    RESULT wide; \
  __BB(2): \
    if (choose_3(D) != 0u) \
      goto __BB3; \
    else \
      goto __BB4; \
  __BB(3): \
    converted_5 = (RESULT) SOURCE; \
    goto __BB4; \
  __BB(4): \
    narrow_6 = __PHI (__BB2: 42u, __BB3: x_1(D)); \
    wide_7 = __PHI (__BB2: CONSTANT, __BB3: converted_5); \
    __MEM <u32> (out_4(D)) = narrow_6; \
    return wide_7; \
  }

PAIR (different_constant, x_1(D), 43ULL, u64)
PAIR (different_source, y_2(D), 42ULL, u64)
PAIR (signed_result, x_1(D), 42LL, long long)
PAIR (same_width, x_1(D), 42u, u32)
#undef PAIR

/* A third nontrivial PHI is outside the bounded peer search.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
third_phi (u32 x, u32 y, u32 choose, u32 *out)
{
  u32 narrow;
  u32 extra;
  u32 observed;
  u64 converted;
  u64 wide;
__BB(2):
  if (choose_3(D) != 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_5 = (u64) x_1(D);
  goto __BB4;
__BB(4):
  narrow_6 = __PHI (__BB2: 42u, __BB3: x_1(D));
  wide_7 = __PHI (__BB2: 42ULL, __BB3: converted_5);
  extra_8 = __PHI (__BB2: 3u, __BB3: y_2(D));
  observed_9 = narrow_6 ^ extra_8;
  __MEM <u32> (out_4(D)) = observed_9;
  return wide_7;
}

/* The cast has another use and must retain its unselected value.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
live_cast (u32 x, u32 choose, u32 *out)
{
  u32 narrow;
  u64 converted;
  u64 wide;
  u64 result;
__BB(2):
  converted_4 = (u64) x_1(D);
  if (choose_2(D) != 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  goto __BB4;
__BB(4):
  narrow_5 = __PHI (__BB2: 42u, __BB3: x_1(D));
  wide_6 = __PHI (__BB2: 42ULL, __BB3: converted_4);
  __MEM <u32> (out_3(D)) = narrow_5;
  result_7 = wide_6 ^ converted_4;
  return result_7;
}

/* A dead narrow PHI must not enable the new profitability exception.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
dead_peer (u32 x, u32 choose)
{
  u32 narrow;
  u64 converted;
  u64 wide;
__BB(2):
  if (choose_2(D) != 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_3 = (u64) x_1(D);
  goto __BB4;
__BB(4):
  narrow_4 = __PHI (__BB2: 42u, __BB3: x_1(D));
  wide_5 = __PHI (__BB2: 42ULL, __BB3: converted_3);
  return wide_5;
}

/* Existing rules may still simplify individual functions.  None should
   use the new two-PHI exception.  */
/* { dg-final { scan-tree-dump-not "Reusing existing narrow PHI" "phiopt1" } } */
