/* { dg-do compile { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-O[sgz]" "-flto" } } */
/* { dg-options "-march=rv64gc_zba -mabi=lp64d -mtune=xt-c9501fdvt -O2 -fdump-rtl-sched2-details" } */
/* No tune enables these fusion pairs yet.  */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_SRLI_ADD" 3 "sched2" { xfail *-*-* } } } */

typedef long int64_t;
typedef unsigned long uint64_t;
typedef int int32_t;
typedef unsigned int uint32_t;

/* srli by 2 followed by add should fuse.  */
int64_t
test_srli_add (uint64_t a, int64_t b)
{
  return (int64_t) (a >> 2) + b;
}

/* srliw by 2 followed by addw should fuse.  */
int32_t
test_srliw_addw (uint32_t a, int32_t b)
{
  return (int32_t) (a >> 2) + b;
}

/* srli by 2 followed by add.uw should fuse.  */
uint64_t
test_srli_adduw (uint64_t a, uint64_t b)
{
  return (uint64_t) (uint32_t) (a >> 2) + b;
}

