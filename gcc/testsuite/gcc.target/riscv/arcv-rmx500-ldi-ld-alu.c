/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: LD + ALU fusion.
   The load and addi should be scheduled in the same cycle (cycle 0).  */

int
test_ld_alu (int *p, int a)
{
  int x = *p;
  int y = a + 1;
  return x + y;
}

/* Verify LD and ALU are both at cycle 0 in sched2 output (fused).  */
/* { dg-final { scan-rtl-dump "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
/* { dg-final { scan-rtl-dump "total time = 3" "sched2" } } */
