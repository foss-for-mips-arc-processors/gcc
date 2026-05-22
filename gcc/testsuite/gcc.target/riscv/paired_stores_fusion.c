/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc -mabi=lp64d -mfusion=aligned-std -fno-lto -fdump-rtl-sched2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_ALIGNED_STD" 8 "sched2" } } */
struct frob {
  int x0;
  int x1;
  int x2;
  int x3;
};

void oof (struct frob *, int a1, int a2);

void fubar (int a, int b)
{
  struct frob x;
  int c = a << b;

  x.x0 = c;
  x.x0 <<= a;

  x.x3 = x.x0 << b;
  x.x3 -= b;

  x.x2 = x.x0 - x.x3;
  x.x2 += a;

  x.x1 = b;

  oof (&x, x.x1, x.x2);
}

struct frob2 {
  char x0;
  char x1;
  char x2;
  char x3;
};

void oof2 (struct frob2 *, char a1, char a2);

void fubar2 (char a, char b)
{
  struct frob2 x;
  char c = a << b;

  x.x0 = c;
  x.x0 <<= a;

  x.x3 = x.x0 << b;
  x.x3 -= b;

  x.x2 = x.x0 - x.x3;
  x.x2 += a;

  x.x1 = b;

  oof2 (&x, x.x1, x.x2);
}

struct frob3 {
  short x0;
  short x1;
  short x2;
  short x3;
};

void oof3 (struct frob3 *, short a1, short a2);

void fubar3 (short a, short b)
{
  struct frob3 x;
  short c = a << b;

  x.x0 = c;
  x.x0 <<= a;

  x.x3 = x.x0 << b;
  x.x3 -= b;

  x.x2 = x.x0 - x.x3;
  x.x2 += a;

  x.x1 = b;

  oof3 (&x, x.x1, x.x2);
}

struct frob4 {
  long x0;
  long x1;
  long x2;
  long x3;
};

void oof4 (struct frob4 *, long a1, long a2);

void fubar4 (long a, long b)
{
  struct frob4 x;
  long c = a << b;

  x.x0 = c;
  x.x0 <<= a;

  x.x3 = x.x0 << b;
  x.x3 -= b;

  x.x2 = x.x0 - x.x3;
  x.x2 += a;

  x.x1 = b;

  oof4 (&x, x.x1, x.x2);
}
