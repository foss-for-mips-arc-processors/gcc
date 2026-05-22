/* { dg-do compile } */
/* { dg-require-effective-target codedensity } */
/* { dg-options "-Os" } */

volatile int *p = (int *)0xa30000;

int
test_ld_s_volatile (void)
{
  return *p;
}

int
test_ld_s_array (void)
{
  int arr[10] = {0};
  return arr[2];
}

int
test_ld_s_pointer (int *ptr)
{
  return *ptr;
}

/* { dg-final { scan-assembler "ld_s\\s+r\[0-9\]" } } */
