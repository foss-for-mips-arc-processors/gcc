/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_decrementing_iv (unsigned int *arr, unsigned int n)
{
  for (unsigned int i = n; i > 0; i--)
    arr[i - 1] = i;
}

/* { dg-final { scan-tree-dump-not "Successfully versioned loop" "ivbound" } } */
