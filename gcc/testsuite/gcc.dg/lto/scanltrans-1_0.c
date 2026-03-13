/* { dg-lto-do link } */
/* { dg-require-linker-plugin "" } */
/* { dg-lto-options { { -O2 -flto -save-temps } } } */

int bar (int x);

int
foo (int a)
{
  return a * 2 + bar (a);
}

int
main (void)
{
  return foo (42);
}

/* { dg-final { scan-ltrans-assembler "main" } } */
