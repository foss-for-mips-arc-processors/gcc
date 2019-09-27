/* { dg-do compile } */
/* { dg-options "-O2" } */

/* check "movq-1.c" for further details. */

/* assign a register to register */
char foo(char a, char b)
{
  return b;
}
/* { dg-final { scan-assembler "mov_s\\s+r\[0-9\]+,r\[0-9\]+" } } */
