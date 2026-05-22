/* { dg-do compile } */
/* { dg-skip-if "" { ! { arc6xx || arc700 } } } */
/* { dg-options "-Os" } */

void
test_st_s_arcv1_array (int val)
{
  int arr[10];
  arr[2] = val;
}

void
test_st_s_arcv1_pointer (int *ptr, int val)
{
  *ptr = val;
}

/* { dg-final { scan-assembler "st_s\\s+r\[0-9\]" } } */
