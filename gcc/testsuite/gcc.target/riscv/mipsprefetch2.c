/* { dg-do compile } */
/* { dg-options "-march=rv64gc_xmipscbop -mtune=mips-i8500" { target { rv64 } } } */
/* { dg-skip-if "" { riscv32-*-* } { "-O0" "-Og" } } */

void test1(char *a)
{
  __builtin_prefetch (&a[0], 0, 0);
}

void test2(char *a)
{
  __builtin_prefetch (&a[1], 1, 0);
}

void test3(char *a)
{
  __builtin_prefetch (&a[511], 0, 1);
}

void test4(char *a)
{
  __builtin_prefetch (&a[512], 1, 1);
}

/* { dg-final { scan-assembler-times "mips.pref" 2 } } */
