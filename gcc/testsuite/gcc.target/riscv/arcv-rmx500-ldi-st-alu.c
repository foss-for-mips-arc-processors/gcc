/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: ST + ALU fusion.
   The store and add should be scheduled in the same cycle when
   the ALU result is independent of the store.  */

int
test_st_alu (int *p, int val, int a)
{
  *p = val;
  return val + a;
}

/* Verify ST and ALU are both at cycle 0 (fused).  */
/* { dg-final { scan-rtl-dump "0-->.*\\\[a0\\\]=a1.*\n.*0-->.*a0=a1\\+a2" "sched2" } } */
