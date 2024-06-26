/* { dg-do compile } */
/* { dg-skip-if "avoid conflicts with -mcpu options" { *-*-* } { "-mcpu=*" } { "-mcpu=em" } } */
/* { dg-options "-O2 -mcpu=em -mswap" } */

unsigned int foo(unsigned int x)
{
  return x >> 16;
}

/* { dg-final { scan-assembler "lsr16\\s+r0,r0" } } */

