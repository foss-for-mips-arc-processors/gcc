/* { dg-do compile } */
/* { dg-options "-O2 -fno-version-loops-for-iv-overflow -fdump-tree-optimized" } */

void
test_flag_disabled (unsigned int *arr, unsigned int n)
{
  for (unsigned int i = 0; i < n; i++)
    arr[i] = i;
}

/* { dg-final { scan-tree-dump-not "32768" "optimized" } } */
