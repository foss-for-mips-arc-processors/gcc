/* { dg-do compile } */
/* { dg-options "-O2 -msdata" } */

__attribute__((section(".sdata"))) int a[300];

int f (void)
{
  return a[255];
}

int g (void)
{
  return a[256];
}

/* { dg-final { scan-assembler "ld_s\\s+r0,\\\[gp,@a@sda\\+1020\\\]" } } */
/* { dg-final { scan-assembler "ld\\s+r0,\\\[@a\\+1024\\\]" } } */
