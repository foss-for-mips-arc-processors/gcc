/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=hs6x -mfpu=fpud" } */

int *a;
int b, c, d;
double e, g;
double f[0];
double *h;
int i[0];
void l() {
  int j;
k:
  for (; g; b++, g--)
    i[b] = 1.67772160000000000000e07 * e;
  if (b) {
    for (; b <= d; b++) {
      f[b] = a[b];
      c = 0.0;
      for (; c <= j; c++)
        e = h[c] * f[c];
    }
    goto k;
  }
}
