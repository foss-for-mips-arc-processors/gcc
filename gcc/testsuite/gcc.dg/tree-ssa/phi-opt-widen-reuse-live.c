/* { dg-do compile } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */
/* { dg-options "-O2 -fgimple -fdump-tree-phiopt1-details" } */

typedef unsigned int u32;
typedef unsigned long long u64;

/* The old cast has a single use.  It is the unconverted sum, not the cast,
   that has another consumer and must keep its arithmetic live.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
live_source (u32 x, u32 y, u32 *out, u32 *raw)
{
  u32 sum;
  u32 narrow;
  u64 converted;
  u64 wide;
__BB(2):
  sum_5 = x_1(D) + y_2(D);
  if (sum_5 >= x_1(D))
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_6 = (u64) sum_5;
  goto __BB4;
__BB(4):
  narrow_7 = __PHI (__BB2: 4294967295u, __BB3: sum_5);
  wide_8 = __PHI (__BB2: 4294967295ULL, __BB3: converted_6);
  __MEM <u32> (out_3(D)) = narrow_7;
  __MEM <u32> (raw_4(D)) = sum_5;
  return wide_8;
}

/* Even without an extra raw or flag output, the bounded profitability
   exception excludes projections of a multi-result operation.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
real_no_extra (u32 x, u32 y, u32 *out)
{
  __complex__ unsigned int pair;
  u32 sum;
  u32 flag;
  u32 narrow;
  u64 converted;
  u64 wide;
__BB(2):
  pair_4 = .ADD_OVERFLOW (x_1(D), y_2(D));
  sum_5 = __real pair_4;
  flag_6 = __imag pair_4;
  if (flag_6 == 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_7 = (u64) sum_5;
  goto __BB4;
__BB(4):
  narrow_8 = __PHI (__BB2: 4294967295u, __BB3: sum_5);
  wide_9 = __PHI (__BB2: 4294967295ULL, __BB3: converted_7);
  __MEM <u32> (out_3(D)) = narrow_8;
  return wide_9;
}

/* The sum has only the old cast and narrow PHI as users.  Its sibling
   overflow flag is separately observable, so checking sum uses is not
   enough to establish profitability.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
real_live_flag (u32 x, u32 y, u32 *out, u32 *flag_out)
{
  __complex__ unsigned int pair;
  u32 sum;
  u32 flag;
  u32 narrow;
  u64 converted;
  u64 wide;
__BB(2):
  pair_5 = .ADD_OVERFLOW (x_1(D), y_2(D));
  sum_6 = __real pair_5;
  flag_7 = __imag pair_5;
  if (flag_7 == 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_8 = (u64) sum_6;
  goto __BB4;
__BB(4):
  narrow_9 = __PHI (__BB2: 4294967295u, __BB3: sum_6);
  wide_10 = __PHI (__BB2: 4294967295ULL, __BB3: converted_8);
  __MEM <u32> (out_3(D)) = narrow_9;
  __MEM <u32> (flag_out_4(D)) = flag_7;
  return wide_10;
}

/* Cover IMAGPART directly, without depending on an overflow flag's range
   or on the front end's lowering of a complex expression.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
imaginary (__complex__ unsigned int value, u32 choose, u32 *out)
{
  u32 part;
  u32 narrow;
  u64 converted;
  u64 wide;
__BB(2):
  part_4 = __imag value_1(D);
  if (choose_2(D) != 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_5 = (u64) part_4;
  goto __BB4;
__BB(4):
  narrow_6 = __PHI (__BB2: 42u, __BB3: part_4);
  wide_7 = __PHI (__BB2: 42ULL, __BB3: converted_5);
  __MEM <u32> (out_3(D)) = narrow_6;
  return wide_7;
}

/* A same-typed SSA copy must not hide a multi-result producer.  Its only
   users are the old single-use cast and narrow peer, while the underlying
   operation has a separately observable overflow flag.  */
u64 __attribute__ ((noipa))
__GIMPLE (ssa, startwith ("phiopt"))
copy_real_live_flag (u32 x, u32 y, u32 choose, u64 *out)
{
  __complex__ unsigned int pair;
  u32 raw;
  u32 flag;
  u32 copied;
  u32 narrow;
  u64 converted;
  u64 wide;
  u64 observed;
  u64 observed_flag;
__BB(2):
  pair_5 = .ADD_OVERFLOW (x_1(D), y_2(D));
  raw_6 = __real pair_5;
  flag_7 = __imag pair_5;
  copied_8 = raw_6;
  if (flag_7 == 0u)
    goto __BB3;
  else
    goto __BB4;
__BB(3):
  converted_9 = (u64) copied_8;
  goto __BB4;
__BB(4):
  narrow_10 = __PHI (__BB2: 4294967295u, __BB3: copied_8);
  wide_11 = __PHI (__BB2: 4294967295ULL, __BB3: converted_9);
  observed_12 = (u64) narrow_10;
  __MEM <u64> (out_4(D)) = observed_12;
  observed_flag_13 = (u64) flag_7;
  __MEM <u64> (out_4(D) + _Literal (__SIZETYPE__) 8) = observed_flag_13;
  return wide_11;
}

/* Existing rules may still simplify individual functions.  None should
   use the new two-PHI profitability exception.  */
/* { dg-final { scan-tree-dump-not "Reusing existing narrow PHI" "phiopt1" } } */
