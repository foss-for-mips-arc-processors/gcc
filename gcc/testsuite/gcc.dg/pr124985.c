/* { dg-do compile } */
/* { dg-require-effective-target trampolines } */
/* { dg-options "-O1 -fno-tree-dse" } */

void a() {
  int b = 0;
  struct bar { char c[b]; };
  struct bar (*d)();
  struct bar e() { struct bar f; return f; }
  d = e;
  d();
}

