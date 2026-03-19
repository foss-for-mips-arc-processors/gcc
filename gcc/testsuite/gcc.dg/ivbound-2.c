/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_signed_iv (int *arr, int n)
{
  for (int i = 0; i < n; i++)
    arr[i] = i;
}

/* { dg-final { scan-tree-dump-not "Found unsigned IV in loop" "ivbound" } } */
/* { dg-final { scan-tree-dump-not "Successfully versioned loop" "ivbound" } } */
