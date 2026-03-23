/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rpx-100-series -march=rv64im_zbs -mabi=lp64 -fdump-rtl-sched2" } */
#include <stdint.h>

__int128_t
foo (int64_t x, int64_t y, int64_t *result)
{
  __int128_t z = (__int128_t) x * y;
  return z + 1;
}

__int128_t
bar (int64_t x, uint64_t y)
{
  __int128_t z = (__int128_t) x * y;
  return z + 1;
}

__uint128_t
baz (uint64_t x, uint64_t y)
{
  __uint128_t z = (__uint128_t) x * y;
  return z + 1;
}

/* { dg-final { scan-rtl-dump "0-->.*a4=trn\\(sxn\\(a0\\)\\*sxn\\(a1\\) 0>>0x40\\).*\n.*1-->.*a5=a0\\*a1.*\n.*6-->.*a0=a5\\+0x1.*" "sched2" } } */
/* { dg-final { scan-rtl-dump "0-->.*a4=trn\\(zxn\\(a1\\)\\*sxn\\(a0\\) 0>>0x40\\).*\n.*1-->.*a5=a1\\*a0.*\n.*6-->.*a0=a5\\+0x1.*" "sched2" } } */
/* { dg-final { scan-rtl-dump "0-->.*a4=trn\\(zxn\\(a0\\)\\*zxn\\(a1\\) 0>>0x40\\).*\n.*1-->.*a5=a0\\*a1.*\n.*6-->.*a0=a5\\+0x1.*" "sched2" } } */
