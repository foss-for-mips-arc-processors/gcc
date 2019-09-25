/* { dg-do compile } */
/* { dg-options "-O0" } */

/* Tests for verification of "movqi" assembly output.  *
 * Here we try to cover as much as different scenarios *
 * that a "movqi" could happen.                        *
 * "movqi" is an assigning of a _byte_.                *
 *                                                     *
 * ,--------.----------.----------.-----------------.  *
 * | test   | notation | dest.    | source          |  *
 * |--------|---------------------------------------|  *
 * | test01 | r <- i   | register | immediate       |  *
 * | test02 | r <- r   |          | register        |  *
 * | test03 | r <- m   |          | memory          |  *
 * |--------+----------+----------+-----------------|  *
 * | test04 | m <- r   |          | register        |  *
 * | test05 | m <- i   | memroy   | immediate small |  *
 * | test06 | m <- I   |          | immediate big   |  *
 * | test07 | m <- m   |          | memory          |  *
 * `--------^----------^----------^-----------------'  */

/* assign immediate to register */
volatile char test01_dummy;
void test01(void)
{
  register char dst;
  dst = 0x0;
  dst = 0x22;
  dst = 0x40;
  dst = 0x80;
  dst = 0xFF;
  test01_dummy = dst;
}
/* FIXME: why not mov_s? */
/* { dg-final { scan-assembler "mov\\s+r14,0" } } */
/* { dg-final { scan-assembler "mov\\s+r14,34" } } */
/* { dg-final { scan-assembler "mov\\s+r14,64" } } */
/* { dg-final { scan-assembler "mov\\s+r14,128" } } */
/* { dg-final { scan-assembler "mov\\s+r14,255" } } */

/* assign a register to register */
volatile char test02_dummy;
void test02(void)
{
  register char src, dst;
  src = 0x37;
  test02_dummy = src;
  dst = src;
  test02_dummy = dst;
}
/* FIXME: figure out how to produce mov r,r; then reverse gd */
/* { gd-final { scan-assembler "mov\\s+r\[0-9\]+,r\[0-9\]+" } } */

/* assign memory to register */
volatile char test03_mem;
void test03(void)
{
  register char dst = test03_mem;
}
/* { dg-final { scan-assembler "ldb\\s+r0,\\\[@test03_mem\\\]" } } */

/* register to memory */
char test04_mem;
void test04(void)
{
  register char reg_char;
  test04_mem = reg_char;
}
/* { dg-final { scan-assembler "stb\\s+r\[0-9\]+,\\\[@test04_mem\\\]" } } */

/* assign immediate to a memory: this immediate is small *
 * enough to be covered by w6 (signed 6 bit number).     */
char test05_mem;
void test05(void)
{
  test05_mem = 0x00;    /* the usual suspect: 0 */
  test05_mem = 0x1F;    /* largest positive number in w6 */
  test05_mem = 0x3F;    /* smallest negative number in w6 */
}
/* { dg-final { scan-assembler "stb\\s+0,\\\[@test05_mem\\\]" } } */
/* { dg-final { scan-assembler "stb\\s+31,\\\[@test05_mem\\\]" } } */
/* { dg-final { scan-assembler "stb\\s+63,\\\[@test05_mem\\\]" } } */

///* assign immediate to a memory: this immediate cannot be   *
// * represented by 6-bit, hence stb w6, mem is not an option */
//char test06_mem;
//void test06(void)
//{
//  test06_mem = 0x40;    /* smallest 7-bit number */
//  test06_mem = 0x7F;    /* largest  7-bit number */
//  test06_mem = 0x80;    /* smallest 8-bit number */
//  test06_mem = 0xFF;    /* largest  8-bit number */
//}
/* FIXME: reverse gd so dejagnu would be triggered */
/* { gd-final { scan-assembler "mov_s\\s+r2,64" } } */
/* { gd-final { scan-assembler "mov_s\\s+r2,127" } } */
/* { gd-final { scan-assembler "mov\\s+r2,-128" } } */
/* { gd-final { scan-assembler "mov_s\\s+r2,-1" } } */
/* { gd-final { scan-assembler-times "stb\\s+r2,\\\[@test06_mem\\\]" 3 } } */

/* assign memory to a memory */
char test07_mem_dst, test07_mem_src;
void test07(void)
{
  test07_mem_dst = test07_mem_src;
}
/* { dg-final { scan-assembler "ldb\\s+r\[0-9\]+,@test07_mem_src" } } */
/* { dg-final { scan-assembler "stb\\s+r0,\\\[@test07_mem_dst\\\]" } } */
