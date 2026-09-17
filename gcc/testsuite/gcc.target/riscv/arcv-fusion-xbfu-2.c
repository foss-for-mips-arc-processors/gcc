/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rpx-100-series -march=rv64im_zbs -mabi=lp64" } */

#define bit_extract32(x,start,amt) (((x)>>(start)) & (~(0xffffffff << (amt))))
#define bit_extract64(x,start,amt) (((x)>>(start)) & (~(0xffffffffffffffffL << (amt))))

int
f (int x)
{
  return bit_extract32(x,10,14) + bit_extract32(x,1,1);
}

long long
g (long long x)
{
  return bit_extract64(x,10,14) + bit_extract64(x,1,1);
}


/* { dg-final { scan-assembler-times {\sslli\s([ast][0-9]+),a0,40\n\ssrli\s([ast][0-9]+),\1,50\n\sbexti\sa0,a0,1[^\n]*\n\sadd\sa0,\2,a0} 2 } } */
