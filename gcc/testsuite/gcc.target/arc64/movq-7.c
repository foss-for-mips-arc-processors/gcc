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

/* assign memory to a memory */
char mem_dst, mem_src;
void foo(void)
{
  mem_dst = mem_src;
}
/* { dg-final { scan-assembler "ldb\\s+r\[0-9\]+,\\\[@mem_src\\\]" } } */
/* { dg-final { scan-assembler-not "ext\[bhw\]\\s+" } } */
/* { dg-final { scan-assembler "stb\\s+r0,\\\[@mem_dst\\\]" } } */
