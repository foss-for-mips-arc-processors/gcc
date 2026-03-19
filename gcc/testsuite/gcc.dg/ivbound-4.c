/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_nested_loops (unsigned int *arr, unsigned int n, unsigned int m)
{
  for (unsigned int i = 0; i < n; i++)
    for (unsigned int j = 0; j < m; j++)
      arr[i * m + j] = i + j;
}

/* { dg-final { scan-tree-dump "Hoisting versioning from loop" "ivbound" } } */
/* { dg-final { scan-tree-dump "Successfully versioned loop" "ivbound" } } */
