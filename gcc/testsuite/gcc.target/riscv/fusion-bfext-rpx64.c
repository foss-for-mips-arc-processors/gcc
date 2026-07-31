/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im -mabi=lp64 -fdump-rtl-sched2" } */

unsigned int
fusion_shift_bitextract_si (unsigned int x, unsigned int y, unsigned int z)
{
  unsigned int t = x << 8;
  unsigned int a = y + z;
  t = t >> 4;
  return t + a;
}

unsigned long long
fusion_shift_bitextract_di (unsigned long long x, unsigned long long y,
			    unsigned long long z)
{
  unsigned long long t = x << 8;
  unsigned long long a = y + z;
  t = t >> 4;
  return t + a;
}

/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_BFEXT_SRLI" 2 "sched2" } } */
