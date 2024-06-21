/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" } } */
/* { dg-options "-mtune=arc-v-rhx-100-series -march=rv32im" } */

int
f (int x, int y, int z, int v, int w)
{
  return x + y * z + v * w;
}

/* { dg-final { scan-assembler {\smul\s([ast][0-9]+),a1,a2\n\sadd\s\1,\1,a0\n\smul\sa0,a3,a4\n\sadd\sa0,a0,\1\n} } } */
