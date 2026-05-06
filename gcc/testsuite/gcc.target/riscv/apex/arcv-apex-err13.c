/* { dg-do compile } */
/* { dg-options "-O0" } */

void foo (int, int);
int bar (int);

#pragma intrinsic (foo, FOP, 10, "XS")
#pragma intrinsic (bar, BAR, 11, "XI")

int main() {
  foo (12, 100000); /* { dg-error "argument value 100000 is outside the valid range \\\[-128, 127\\\]" } */
  return bar (100000); /* { dg-error "argument value 100000 is outside the valid range \\\[-2048, 2047\\\]" } */
}
