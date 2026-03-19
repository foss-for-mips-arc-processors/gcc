/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_inner_bound_not_invariant (unsigned int *arr, unsigned int n)
{
  for (unsigned int i = 0; i < n; i++)
    for (unsigned int j = 0; j < i; j++)  /* bound 'i' varies with outer loop */
      arr[i * n + j] = i + j;
}

/* Inner loop's bound is not invariant to outer, cannot hoist to outer.  */
/* { dg-final { scan-tree-dump "Successfully versioned loop" "ivbound" } } */
