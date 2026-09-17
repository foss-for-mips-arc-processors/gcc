/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im -mabi=lp64 -mcmodel=medlow -fdump-rtl-sched2" { target rv64 } } */

int
fuse_memop_lui_zero (int p, int *q)
{
  *q = p;
  return 0;
}

/* { dg-final { scan-rtl-dump-not "ARCV_FUSE_MEMOP_LUI" "sched2" } } */
/* { dg-final { scan-rtl-dump-not "ARCV_FUSE_MEMOP_LUI" "sched2" } } */
