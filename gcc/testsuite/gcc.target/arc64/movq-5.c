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
