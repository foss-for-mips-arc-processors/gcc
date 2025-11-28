/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rhx-100-series -march=rv32im_zbs -mabi=ilp32 -dp" } */

#define bit_extract(x,start,amt) (((x)>>(start)) & (~(0xffffffff << (amt))))

int
f (int x)
{
  return bit_extract(x,10,14) + bit_extract(x,1,1);
}

/* { dg-final { scan-assembler {\sslli\s([ast][0-9]+),a0,8.*zero_extract_fused\n\ssrli\s([ast][0-9]+),\1,18\n\sbexti\sa0,a0,1.*\n\sadd\sa0,\2,a0.*\n} } } */
