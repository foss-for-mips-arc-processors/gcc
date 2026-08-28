/* { dg-do compile } */
/* { dg-options "-O2" } */

long long foo(long long x)
{
  return x >> 1;
}

/* { dg-final { scan-assembler "asr.f\\s+r1,r1"  { target arc-*-* } } } */
/* { dg-final { scan-assembler "rrc\\s+r0,r0"  { target arc-*-* } } } */
/* { dg-final { scan-assembler "asr.f\\s+r0,r0"  { target arceb-*-* } } } */
/* { dg-final { scan-assembler "rrc\\s+r1,r1"  { target arceb-*-* } } } */
