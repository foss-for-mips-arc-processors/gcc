/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -mno-arc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
test_ld_alu_nofuse (int *p, int a)
{
  int x = *p;
  int y = a + 1;
  return x + y;
}

/* { dg-final { scan-rtl-dump-not "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
/* { dg-final { scan-rtl-dump "0-->.*a0=\\\[a0\\\].*\n.*1-->.*a1=a1\\+0x1.*\n.*2-->.*a0=a1\\+a0" "sched2" } } */
