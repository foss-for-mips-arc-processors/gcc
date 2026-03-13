/* { dg-lto-do link } */
/* { dg-require-linker-plugin "" } */
/* { dg-lto-options { { -O2 -flto -fdump-tree-optimized -fdump-rtl-expand } } } */

extern int external_func(int);

__attribute__((noinline))
int
compute (int x)
{
  if (x > 100)
    return x * 2;
  return x + 10;
}

int
main (void)
{
  int result = compute (50);
  return external_func (result);
}

/* { dg-final { scan-ltrans-tree-dump "compute" "optimized" } } */
/* { dg-final { scan-ltrans-rtl-dump "main" "expand" } } */
