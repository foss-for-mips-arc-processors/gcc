/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32imafd -mabi=ilp32d -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: FLD + FMAC fusion.
   The floating-point load and fadd should be scheduled in the same cycle
   when there is no RAW hazard.  */

double
test_fld_fmac (double *p, double a, double b, double c)
{
  double x = *p;
  double y = a + b;
  return x + y + c;
}

/* Verify FLD and FADD are both at cycle 0 (fused, no RAW hazard).  */
/* { dg-final { scan-rtl-dump "0-->.*fa5=\\\[a0\\\].*\n.*0-->.*fa0=fa0\\+fa1" "sched2" } } */
