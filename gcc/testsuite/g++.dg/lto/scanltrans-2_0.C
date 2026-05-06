/* { dg-lto-do link } */
/* { dg-require-linker-plugin "" } */
/* { dg-lto-options {{-O0 -flto -fdump-tree-optimized}} } */

extern int process(int);

__attribute__((noinline))
int calculate(int x, int y)
{
  int result = x + y;
  result = result * 2;
  return process(result);
}

int main(void)
{
  return calculate(10, 20);
}

/* { dg-final { scan-ltrans-tree-dump "calculate" "optimized" } } */
