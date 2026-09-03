/* { dg-do run } */
/* { dg-options "-O2" } */

typedef short v4hi __attribute__((vector_size (8)));

__attribute__((noinline)) v4hi
foo (short c)
  {
    v4hi v = { c, c, c, c };
    return v;
  }

__attribute__((noinline)) v4hi
bar (short unused, short c)
  {
    v4hi v = { c, c, c, c };
    return v;
  }

static void
check (v4hi v, short c)
  {
    if (v[0] != c || v[1] != c || v[2] != c || v[3] != c)
    __builtin_abort ();
  }

int
main (void)
  {
    short val = -42;
    check (foo (val), val);
    check (bar (0, val), val);

    return 0;
  }
