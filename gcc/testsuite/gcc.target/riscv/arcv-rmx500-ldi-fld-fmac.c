/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32imafd -mabi=ilp32d -fdump-rtl-sched2" } */

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

/* Verify FLD+FMAC fusion occurs (no RAW hazard: fld writes fa5,
   fadd reads fa0 and fa1 which are different).  */
/* { dg-final { scan-rtl-dump "ARCV_RMX500_LIMITED_DUAL_ISSUE" "sched2" } } */
