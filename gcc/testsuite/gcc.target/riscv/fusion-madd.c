/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32" { target { rv32 } } } */
/* { dg-options "-mtune=arc-v-rhx-100-series -march=rv64im -mabi=lp64" { target { rv64 } } } */

int
f (int x, short y, short z, short v, short w)
{
  return x + (int) y * (int) z + (int) v * (int) w;
}

/* { dg-final { scan-assembler {\smul\s([ast][0-9]+),a1,a2\n\sadd\s\1,\1,a0\n\smul\sa0,a3,a4\n\sadd\sa0,a0,\1\n} { target rv32 } } } */
/* { dg-final { scan-assembler {\smulw\sa2,a2,a1\n\saddw\sa2,a2,a0\n\smulw\sa0,a4,a3\n\saddw\sa0,a0,a2\n} { target rv64 } } } */
