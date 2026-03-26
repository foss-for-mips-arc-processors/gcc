/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: ST + ALU fusion.
   The store and add should be scheduled in the same cycle when
   the ALU result is independent of the store.  */

int
test_st_alu (int *p, int val, int a, int b)
{
  *p = val;
  return a + b;
}

/* Verify fusion occurs.  */
/* { dg-final { scan-rtl-dump "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
