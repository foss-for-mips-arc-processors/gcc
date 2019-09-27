/* { dg-do compile } */
/* { dg-options "-O0" } */

/* check "movq-1.c" for further details. */

/* assign immediate to a memory: this immediate is small *
 * enough to be covered by w6 (signed 6 bit number).     */
char mem;
void foo(void)
{
  mem = 0x00;    /* the usual suspect: 0 */
  mem = 0x1F;    /* largest positive number in w6 */
  mem = 0x3F;    /* smallest negative number in w6 */
}
/* { dg-final { scan-assembler "stb\\s+0,\\\[@mem\\\]" } } */
/* { dg-final { scan-assembler "stb\\s+31,\\\[@mem\\\]" } } */
/* { dg-final { scan-assembler "stb\\s+63,\\\[@mem\\\]" } } */
