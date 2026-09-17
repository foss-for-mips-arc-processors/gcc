/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32imafd -mabi=ilp32d -fdump-rtl-sched2" } */

int
test_ld_alu (int *p, int a)
{
  int x = *p;
  int y = a + 1;
  return x + y;
}

double
test_fld_fmac_raw (double *p, double a, double b)
{
  double x = *p;
  return a * b + x;
}

/* { dg-final { scan-rtl-dump "0-->.*a0=\\\[a0\\\].*\n.*0-->.*a1=a1\\+0x1" "sched2" } } */
/* { dg-final { scan-rtl-dump "0-->.*fa5=\\\[a0\\\].*\n.*2-->.*fa0=\\{fa0\\*fa1\\+fa5\\}" "sched2" } } */
