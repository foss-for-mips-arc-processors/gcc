/* { dg-do compile } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */
/* { dg-options "-O2 -fgimple -fdump-tree-phiopt1-details" } */

typedef unsigned int u32;
typedef unsigned long long u64;

/* Start at early phiopt so these paired PHIs cannot be hidden by CSE or
   another pass.  The narrow result already has a separate live use.  */
#define PAIR(NAME, NARROW, WIDE) \
  u64 __attribute__ ((noipa)) \
  __GIMPLE (ssa, startwith ("phiopt")) \
  NAME (u32 x, u32 choose, u32 *out) \
  { \
    u32 narrow; \
    u64 converted; \
    u64 wide; \
  __BB(2): \
    if (choose_2(D) != 0u) \
      goto __BB3; \
    else \
      goto __BB4; \
  __BB(3): \
    converted_4 = (u64) x_1(D); \
    goto __BB4; \
  __BB(4): \
    narrow_5 = __PHI (__BB2: NARROW, __BB3: x_1(D)); \
    wide_6 = __PHI (__BB2: WIDE, __BB3: converted_4); \
    __MEM <u32> (out_3(D)) = narrow_5; \
    return wide_6; \
  }

PAIR (constant, 42u, 42ULL)
PAIR (zero, 0u, 0ULL)
PAIR (maximum, 4294967295u, 4294967295ULL)
#undef PAIR

/* Reverse the condition, PHI statement order and incoming edge order.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
reordered (u32 x, u32 choose, u32 *out)
{
  u32 narrow;
  u64 converted;
  u64 wide;
__BB(2):
  if (choose_2(D) == 0u)
    goto __BB4;
  else
    goto __BB3;
__BB(3):
  converted_4 = (u64) x_1(D);
  goto __BB4;
__BB(4):
  wide_6 = __PHI (__BB3: converted_4, __BB2: 42ULL);
  narrow_5 = __PHI (__BB3: x_1(D), __BB2: 42u);
  __MEM <u32> (out_3(D)) = narrow_5;
  return wide_6;
}

/* Reuse exactly the existing PHI, with an explicit widening conversion.  */
/* { dg-final { scan-tree-dump-times "Reusing existing narrow PHI" 4 "phiopt1" } } */
/* { dg-final { scan-tree-dump-times "wide_\[0-9\]+ = \\(u64\\) narrow_\[0-9\]+;" 4 "phiopt1" } } */
/* { dg-final { scan-tree-dump-not "wide_\[0-9\]+ = PHI" "phiopt1" } } */
