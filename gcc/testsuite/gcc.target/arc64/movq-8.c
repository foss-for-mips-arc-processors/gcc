/* { dg-do compile } */
/* { dg-options "-O0 -fomit-frame-pointer" } */

/* check "movq-1.c" for further details. */

/* FIXME: with a 'volatile' this test generates an unnecessary extb */
/* assign memory to a memory */
volatile char mem_dst, mem_src;
void foo(void)
{
  mem_dst = mem_src;
}
/* { dg-final { scan-assembler "ldb\\s+r\[0-9\]+,\\\[@mem_src\\\]" } } */
/* { dg-final { scan-assembler-not "ext\[bhw\]" } } */
/* { dg-final { scan-assembler "stb\\s+r0,\\\[@mem_dst\\\]" } } */
