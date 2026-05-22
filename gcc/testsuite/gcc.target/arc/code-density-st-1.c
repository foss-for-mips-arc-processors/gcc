/* { dg-do compile } */
/* { dg-require-effective-target codedensity } */
/* { dg-options "-Os" } */

volatile int *p = (int *)0xa30000;

void
test_st_s_volatile (int val)
{
  *p = val;
}

void
test_st_s_array (int val)
{
  int arr[10];
  arr[2] = val;
}

void
test_st_s_pointer (int *ptr, int val)
{
  *ptr = val;
}

/* { dg-final { scan-assembler "st_s\\s+r\[0-9\]" } } */
