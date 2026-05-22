/* { dg-do compile } */
/* { dg-require-effective-target arcem } */
/* { dg-options "-Os -mno-code-density" } */

volatile int *p = (int *)0xa30000;

int
test_no_ld_s_volatile (void)
{
  return *p;
}

int
test_no_ld_s_array (void)
{
  int arr[10] = {0};
  return arr[2];
}

int
test_no_ld_s_pointer (int *ptr)
{
  return *ptr;
}

/* { dg-final { scan-assembler-not "ld_s\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler "ld\\s+r\[0-9\]" } } */
