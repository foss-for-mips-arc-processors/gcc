/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_unsigned_iv (unsigned int *arr, unsigned int n)
{
  for (unsigned int i = 0; i < n; i++)
    arr[i] = i;
}

/* { dg-final { scan-tree-dump "candidate for versioning" "ivbound" } } */
/* { dg-final { scan-tree-dump "Successfully versioned loop" "ivbound" } } */
