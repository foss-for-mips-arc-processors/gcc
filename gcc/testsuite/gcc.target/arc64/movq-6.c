/* { dg-do compile } */
/* { dg-options "-O0" } */

/* check "movq-1.c" for further details. */

/* assign immediate to a memory: this immediate cannot be   *
 * represented by 6-bit, hence stb w6, mem is not an option */
char mem;
void foo(void)
{
  mem = 0x40;    /* smallest 7-bit number */
  mem = 0x7F;    /* largest  7-bit number */
  mem = 0x80;    /* smallest 8-bit number */
  mem = 0xFF;    /* largest  8-bit number */
}
/* { dg-final { scan-assembler "mov_s\\s+r2,64" } } */
/* { dg-final { scan-assembler "mov_s\\s+r2,127" } } */
/* { dg-final { scan-assembler "mov\\s+r2,-128" } } */
/* { dg-final { scan-assembler "mov_s\\s+r2,-1" } } */
/* { dg-final { scan-assembler-times "stb\\s+r2,\\\[@mem\\\]" 4 } } */
