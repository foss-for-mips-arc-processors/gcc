/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" { target { rv32 } } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im -mabi=lp64 -fdump-rtl-sched2" { target { rv64 } } } */

char *
fuse_sb (char *p, char d)
{
  *p = d;
  return p + 8;
}

short *
fuse_sh (short *p, short d)
{
  *p = d;
  return p + 8;
}

#if __riscv_xlen > 32
int *
fuse_sw (int *p, int d)
{
  *p = d;
  return p + 8;
}
#endif

/* { dg-final { scan-rtl-dump "(?s);; Function fuse_sb (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_sh (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_sw (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" { target { rv64 } } } } */
