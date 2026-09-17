/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

void
fuse_adjacent_store (int *p, int x, int y)
{
  p[0] = x;
  p[1] = y;
}

/* { dg-final { scan-rtl-dump "ARCV_FUSE_ADJACENT_STORE" "sched2" } } */
