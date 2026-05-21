/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rmx-500-series -marc-v-rmx-500-series-advanced-fusion -march=rv32ifd_zfh -mabi=ilp32d -fdump-rtl-sched2" } */

_Float16
fuse_ls_update_h (_Float16 *p, int n)
{
  _Float16 sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

float
fuse_ls_update_f (float *p, int n)
{
  float sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

double
fuse_ls_update_d (double *p, int n)
{
  double sum = 0;
  for (int i = 0; i < n; i++)
    sum += *p++;
  return sum;
}

/* { dg-final { scan-rtl-dump {;; Function fuse_ls_update_h \((?:(?!;; Function).)*RISCV_FUSE_FP_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function fuse_ls_update_f \((?:(?!;; Function).)*RISCV_FUSE_FP_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function fuse_ls_update_d \((?:(?!;; Function).)*RISCV_FUSE_FP_LS_UPDATE} "sched2" } } */
