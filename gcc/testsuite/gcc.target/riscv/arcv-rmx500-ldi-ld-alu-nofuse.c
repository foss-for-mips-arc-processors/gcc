/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -mno-arc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test that without advanced fusion, LD + ALU are NOT fused and take
   separate cycles.  */

int
test_ld_alu_nofuse (int *p, int a)
{
  int x = *p;
  int y = a + 1;
  return x + y;
}

/* Without fusion: load at cycle 0, addi at cycle 1, add at cycle 2 (sequential).  */
/* { dg-final { scan-rtl-dump-not "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
/* { dg-final { scan-rtl-dump "0-->.*a0=\\\[a0\\\].*\n.*1-->.*a1=a1\\+0x1.*\n.*2-->.*a0=a1\\+a0" "sched2" } } */
