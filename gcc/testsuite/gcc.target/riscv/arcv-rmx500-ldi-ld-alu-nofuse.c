/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -mno-arc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test that without advanced fusion, LD + ALU are NOT fused and take
   one more cycle than with fusion.  */

int
test_ld_alu_nofuse (int *p, int a)
{
  int x = *p;
  int y = a + 1;
  return x + y;
}

/* Without fusion: total time = 4 (each instruction in its own cycle).  */
/* { dg-final { scan-rtl-dump-not "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
/* { dg-final { scan-rtl-dump "total time = 4" "sched2" } } */
