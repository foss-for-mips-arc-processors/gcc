/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* No tune enables RISCV_FUSE_FLDFST_PAIR_DEC yet.  */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_FLDFST_PAIR_DEC" 4 "sched2" { xfail *-*-* } } } */

float
test_flw_pair_dec (float *p)
{
  return p[1] + p[0];
}

double
test_fld_pair_dec (double *p)
{
  return p[1] + p[0];
}

void
test_fsw_pair_dec (float *p, float a, float b)
{
  p[1] = b;
  p[0] = a;
}

void
test_fsd_pair_dec (double *p, double a, double b)
{
  p[1] = b;
  p[0] = a;
}
