/* { dg-do compile } */
/* { dg-options "-O2" } */

long long foo(long long x)
{
  return x << 1;
}

/* { dg-final { scan-assembler "add.f\\s+r0,r0,r0" { target arc-*-* } } } */
/* { dg-final { scan-assembler "adc\\s+r1,r1,r1" { target arc-*-* } } } */
/* { dg-final { scan-assembler "add.f\\s+r1,r1,r1" { target arceb-*-* } } } */
/* { dg-final { scan-assembler "adc\\s+r0,r0,r0" { target arceb-*-* } } } */
