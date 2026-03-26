/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: ST + BR fusion.
   The store and conditional branch should be scheduled in the same cycle.
   The branch condition is independent of the store.  */

extern void bar (void);

int
test_st_br (int *p, int val, int cond1, int cond2)
{
  *p = val;
  if (cond1 != cond2)
    bar ();
  return val;
}

/* Verify ST+BR fusion occurs.  */
/* { dg-final { scan-rtl-dump "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
