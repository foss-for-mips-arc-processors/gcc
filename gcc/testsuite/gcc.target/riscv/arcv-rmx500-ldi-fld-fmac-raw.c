/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Os" "-Oz" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32imafd -mabi=ilp32d -fdump-rtl-sched2" } */

/* Test RMX-500 limited dual-issue: FLD + FMAC with RAW hazard.
   The fld writes to a register that fmadd reads, so they should NOT be
   scheduled in the same cycle.  */

double
test_fld_fmac_raw (double *p, double a, double b)
{
  double x = *p;
  return a * b + x;
}

/* The fmadd reads x (the fld destination), creating a RAW hazard.
   Fusion should NOT occur for this pair.  The fld is at cycle 0
   and fmadd at cycle 2 (after load latency).  */
/* { dg-final { scan-rtl-dump "total time = 4" "sched2" } } */
