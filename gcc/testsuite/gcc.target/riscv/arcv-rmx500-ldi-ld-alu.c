/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: LD + ALU fusion.
   The load and addi should be scheduled in the same cycle (cycle 0).  */

int
test_ld_alu (int *p, int a)
{
  int x = *p;
  int y = a + 1;
  return x + y;
}

/* Verify LD and ALU are both at cycle 0 (fused), then add at cycle 1.  */
/* { dg-final { scan-rtl-dump "0-->.*a1=a1\\+0x1.*\n.*0-->.*a0=\\\[a0\\\].*\n.*1-->.*a0=a1\\+a0" "sched2" } } */
