/* { dg-do compile } */
/* { dg-additional-options "-ftree-vectorize" } */
/* { dg-additional-options "-mxop" { target { x86_64-*-* || i?86-*-* } } } */

long sum;
int *coef1;

void ac3_sum_square_butterfly_int32_c(int i, int cap) {
  for (; i < cap; i++) {
    int md = i + coef1[i];
    sum += (long)md * md;
  }
}
