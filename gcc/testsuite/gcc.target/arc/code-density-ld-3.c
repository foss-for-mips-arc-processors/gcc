/* { dg-do compile } */
/* { dg-skip-if "" { ! { arc6xx || arc700 } } } */
/* { dg-options "-Os" } */

int
test_ld_s_arcv1_array (void)
{
  int arr[10] = {0};
  return arr[2];
}

int
test_ld_s_arcv1_pointer (int *ptr)
{
  return *ptr;
}

/* { dg-final { scan-assembler "ld_s\\s+r\[0-9\]" } } */
