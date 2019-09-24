/* { dg-do compile } */
/* { dg-options "-O2" } */

/* Tests for verification of "movqi" assembly output.  *
 * Here we try to cover as much as different scenarios *
 * that a "movqi" could happen.                        *
 * "movqi" is an assigning of a _byte_.                */


/* assign immediate to a memory: this immediate is small *
 * enough to be covered by w6 (signed 6 bit number).     */
volatile unsigned char test01_mem;
void test01(void)
{ test01_mem = 0x01; }
/* { dg-final { scan-assembler "stb\\s+1,\\\[@test01_mem\\\]" } } */
