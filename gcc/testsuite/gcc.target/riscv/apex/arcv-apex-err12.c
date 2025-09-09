/* { dg-do compile } */
/* { dg-options "-O0" } */

int foo (int, int);
#pragma intrinsic (foo, FOP, 10, "XS")

int main() {
  int x = 12;
  int y = foo (x, 100000); /* { dg-error "argument value 100000 is outside the valid range \\\[-128, 127\\\]" } */
  return foo (y, x); /* { dg-error "argument to 'foo' must be a constant integer" } */
}