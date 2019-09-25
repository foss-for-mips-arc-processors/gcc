/* { dg-do compile } */
/* { dg-options "-O0" } */

/* Tests for verification of "movqi" assembly output.  *
 * Here we try to cover as much as different scenarios *
 * that a "movqi" could happen.                        *
 * "movqi" is an assigning of a _byte_.                */


/* assign immediate to a memory: this immediate is small *
 * enough to be covered by w6 (signed 6 bit number).     */
char test01_mem;
void test01(void)
{
  test01_mem = 0x1F;    /* biggest positive number in w6 */
  test01_mem = 0x00;    /* somewhere in the middle */
  test01_mem = 0x3F;    /* smallest negative number in w6 */
}
/* { dg-final { scan-assembler "stb\\s+31,\\\[@test01_mem\\\]" } } */
/* { dg-final { scan-assembler "stb\\s+0,\\\[@test01_mem\\\]" } } */
/* { dg-final { scan-assembler "stb\\s+63,\\\[@test01_mem\\\]" } } */
