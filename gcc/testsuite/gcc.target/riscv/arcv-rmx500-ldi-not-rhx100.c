/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test that RMX-500 limited dual-issue fusions do NOT fire on RHX-100.
   Even with the advanced fusion flag, the limited dual-issue is RMX-500 only.
   RHX-100 uses its own dual-pipe scheduling instead.  */

extern void bar (void);

int
test_st_br_rhx (int *p, int val, int cond1, int cond2)
{
  *p = val;
  if (cond1 != cond2)
    bar ();
  return val;
}

/* RHX-100 should not use RMX-500 limited dual-issue fusion.  */
/* { dg-final { scan-rtl-dump-not "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
