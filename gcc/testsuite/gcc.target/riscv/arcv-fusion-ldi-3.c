/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

int
test_st_alu_4src (int *p, int val, int a, int b)
{
  *p = val;
  return a + b;
}

extern void bar (void);

int
test_st_br_4src (int *p, int val, int cond1, int cond2)
{
  *p = val;
  if (cond1 != cond2)
    bar ();
  return val;
}

/* { dg-final { scan-rtl-dump "0-->.*\\\[a0\\\]=a1.*\n.*1-->.*a0=a2\\+a3" "sched2" } } */
/* { dg-final { scan-rtl-dump "0-->.*\\\[a0\\\]=a1.*\n.*1-->.*pc=" "sched2" } } */
