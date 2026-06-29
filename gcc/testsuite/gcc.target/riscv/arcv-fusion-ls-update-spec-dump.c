/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im_zbb -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

long
ld_xnor (long *p, unsigned long x, long *sink)
{
  long v = *p;
  unsigned long q = ~((unsigned long) p ^ x);
  *sink = v;
  return (long) q;
}

long
ld_off (long *p, unsigned long x, long *sink)
{
  long v = p[1];
  unsigned long q = (unsigned long) p + x;
  *sink = v;
  return (long) q;
}

unsigned long
st_off (long *p, long val)
{
  p[1] = val;
  return (unsigned long) p + 8;
}

unsigned long
st_op_add (long *p, long d)
{
  *p = d;
  return (unsigned long) p + (unsigned long) d;
}

unsigned long
st_op_sub (long *p, long d)
{
  *p = d;
  return (unsigned long) p - (unsigned long) d;
}

/* Must not fuse. */
unsigned long
st_op_unrel (long *p, long d, unsigned long x)
{
  *p = d;
  return (unsigned long) p + x;
}

/* { dg-final { scan-rtl-dump-times "ARCV_FUSE_LS_UPDATE" 5 "sched2" } } */
