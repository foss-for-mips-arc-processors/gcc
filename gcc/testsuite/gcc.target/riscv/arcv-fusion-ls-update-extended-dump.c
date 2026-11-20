/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" { target { rv32 } } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im -mabi=lp64 -fdump-rtl-sched2" { target { rv64 } } } */

int
fuse_lb (char *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

int
fuse_lbu (unsigned char *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

int
fuse_lh (short *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

int
fuse_lhu (unsigned short *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

#if __riscv_xlen > 32
int
fuse_lw (int *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

int
fuse_lwu (unsigned int *p, int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}
#endif

/* { dg-final { scan-rtl-dump "(?s);; Function fuse_lb (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_lbu (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_lh (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_lhu (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_lw (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" { target { rv64 } } } } */
/* { dg-final { scan-rtl-dump "(?s);; Function fuse_lwu (?:(?!;; Function ).)*ARCV_FUSE_LS_UPDATE" "sched2" { target { rv64 } } } } */
