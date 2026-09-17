/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_outer_signed_inner_unsigned (int *arr, int n, unsigned int m)
{
  for (int i = 0; i < n; i++)  /* signed - no versioning needed */
    for (unsigned int j = 0; j < m; j++)  /* unsigned - needs versioning */
      arr[i * m + j] = i + j;
}

/* Inner loop needs versioning.  Bound 'm' is invariant to outer, so hoist.  */
/* { dg-final { scan-tree-dump "Successfully versioned loop" "ivbound" } } */
/* { dg-final { scan-tree-dump "Hoisting versioning from loop" "ivbound" } } */
