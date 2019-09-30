/* { dg-do compile } */
/* { dg-options "-O0 -fomit-frame-pointer" } */

/* check "movd-1.c" for further details. */

/* assign immediate to a memory: this immediate cannot be   *
 * represented by 6-bit, hence stb w6, mem is not an option */
int mem;
void foo(void)
{
  mem = 0x40;    /* smallest 7-bit number */
  mem = 0x7F;    /* largest  7-bit number */
  mem = 0x80;    /* 128 */
  mem = -128;    /* smallest 8-bit number */
  mem = -33;     /* first negative number outside w6's range. else,
                    it would use something like 'sth -32, [@mem]'  */
}
/* { dg-final { scan-assembler "mov_s\\s+r0,64" } } */
/* { dg-final { scan-assembler "mov_s\\s+r0,127" } } */
/* FIXME: mov r0,-128 is emitted i.s.o mov_s r0,128 */
/* { dg-final { scan-assembler-times "mov_s\\s+r0,128" 2 } } */
/* { dg-final { scan-assembler "mov\\s+r0,-33" } } */
/* { dg-final { scan-assembler-times "st\\s+r0,\\\[@mem\\\]" 5 } } */
