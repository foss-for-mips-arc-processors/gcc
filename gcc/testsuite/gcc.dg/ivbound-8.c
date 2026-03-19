/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_step_greater_than_one (unsigned int *arr, unsigned int n)
{
  for (unsigned int i = 0; i < n; i += 2)
    arr[i] = i;
}

/* { dg-final { scan-tree-dump "candidate for versioning" "ivbound" } } */
/* { dg-final { scan-tree-dump "Successfully versioned loop" "ivbound" } } */
