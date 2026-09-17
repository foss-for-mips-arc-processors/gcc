/* { dg-do compile } */
/* { dg-require-effective-target trampolines } */
/* { dg-options "" } */


void *a0() {
  int b = 1;
  struct bar { char c[b]; };
  struct bar e() { struct bar f; return f; }
  return &e;	/* { dg-warning "referencing local context" } */
}

void *a1() {
  int b = 1;
  struct bar { char c[b]; };
  struct bar e() { }
  return &e;
}

void *a2() {
  int b = 1;
  struct bar { char c[b]; };
  struct bar e() { typeof(struct bar) f; return f; }
  return &e;	/* { dg-warning "referencing local context" } */
}

void *a3() {
  int b = 1;
  struct bar { char c[b]; };
  struct bar (*d)();
  struct bar e() { typeof((*d)()) f; return f; }
  return &e;	/* { dg-warning "referencing local context" } */
}

void *a4() {
  int b = 1;
  struct bar { char c[b]; };
  struct bar e() { struct bar f; return f; }
  return &e;	/* { dg-warning "referencing local context" } */
}


