/* { dg-do compile } */
/* { dg-options "-O0 -fomit-frame-pointer" } */

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
 * | movq-8 | m <- m   | volatile causes ext, why?  | *
 * `--------^----------^----------^-----------------' */

/* assign immediate to register */
volatile char dummy;
void foo(void)
{
  register char dst;
  dst = 0x0;
  dst = 0x22;
  dst = 0x40;
  dst = 0x80;
  dst = 0xFF;
  dummy = dst;
}
/* FIXME: expect mov_s! movsi pattern is used instead, buty why? */
/* { dg-final { scan-assembler "mov\\s+r14,0" } } */
/* { dg-final { scan-assembler "mov\\s+r14,34" } } */
/* { dg-final { scan-assembler "mov\\s+r14,64" } } */
/* { dg-final { scan-assembler "mov\\s+r14,128" } } */
/* { dg-final { scan-assembler "mov\\s+r14,255" } } */
