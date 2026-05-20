/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: ST + ALU with >3 source operands.
   The store and add have 4 unique source registers (a0, a1, a2, a3),
   exceeding the 3-source-operand limit, so they must NOT be fused.  */

int
test_st_alu_4src (int *p, int val, int a, int b)
{
  *p = val;
  return a + b;
}

/* Verify no limited dual-issue fusion occurs.  */
/* { dg-final { scan-rtl-dump-not "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
/* Verify ST and ALU are on different cycles.  */
/* { dg-final { scan-rtl-dump "0-->.*\\\[a0\\\]=a1.*\n.*1-->.*a0=a2\\+a3" "sched2" } } */
