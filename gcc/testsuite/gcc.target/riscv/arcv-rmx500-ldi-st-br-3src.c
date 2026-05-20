/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: ST + BR with >3 source operands.
   The store and branch have 4 unique source registers (a0, a1, a2, a3),
   exceeding the 3-source-operand limit, so they must NOT be fused.  */

extern void bar (void);

int
test_st_br_4src (int *p, int val, int cond1, int cond2)
{
  *p = val;
  if (cond1 != cond2)
    bar ();
  return val;
}

/* Verify ST and BR are on different cycles (not fused due to >3 sources).  */
/* { dg-final { scan-rtl-dump "0-->.*\\\[a0\\\]=a1.*\n.*1-->.*pc=" "sched2" } } */
