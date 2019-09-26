/* { dg-do compile } */
/* { dg-options "-O0" } */

/* "movqi" is about assigning 8-bit of data (byte).   *
 *                                                    *
 * This is one of the tests in series of testing for  *
 * "movqi" support. The test scenarios are as the     *
 * following table:                                   *
 *                                                    *
 * ,--------.----------.----------.-----------------. *
 * | test   | notation | dest.    | source          | *
 * |--------|---------------------------------------| *
 * | movq-1 | r <- i   | register | immediate       | *
 * | movq-2 | r <- r   |          | register        | *
 * | movq-3 | r <- m   |          | memory          | *
 * |--------+----------+----------+-----------------| *
 * | movq-4 | m <- r   |          | register        | *
 * | movq-5 | m <- i   | memroy   | immediate small | *
 * | movq-6 | m <- I   |          | immediate big   | *
 * | movq-7 | m <- m   |          | memory          | *
 * `--------^----------^----------^-----------------' */

/* assign immediate to a memory: this immediate cannot be   *
 * represented by 6-bit, hence stb w6, mem is not an option */
char test06_mem;
void test06(void)
{
  test06_mem = 0x40;    /* smallest 7-bit number */
  test06_mem = 0x7F;    /* largest  7-bit number */
  test06_mem = 0x80;    /* smallest 8-bit number */
  test06_mem = 0xFF;    /* largest  8-bit number */
}
/* { dg-final { scan-assembler "mov_s\\s+r2,64" } } */
/* { dg-final { scan-assembler "mov_s\\s+r2,127" } } */
/* { dg-final { scan-assembler "mov\\s+r2,-128" } } */
/* { dg-final { scan-assembler "mov_s\\s+r2,-1" } } */
/* { dg-final { scan-assembler-times "stb\\s+r2,\\\[@test06_mem\\\]" 3 } } */
