/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_LDST_PAIR_DEC" 4 "sched2" { xfail *-*-* } } } */

typedef int int32_t;
typedef long int64_t;

int64_t
test_ld_pair_dec (int64_t *p)
{
  return p[1] + p[0];
}

int64_t
test_lw_pair_dec (int32_t *p)
{
  return (int64_t) p[1] + p[0];
}

void
test_sd_pair_dec (int64_t *p, int64_t a, int64_t b)
{
  p[1] = b;
  p[0] = a;
}

void
test_sw_pair_dec (int32_t *p, int32_t a, int32_t b)
{
  p[1] = b;
  p[0] = a;
}
