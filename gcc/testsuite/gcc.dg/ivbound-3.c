/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_small_constant_trip (unsigned int *arr)
{
  for (unsigned int i = 0; i < 100; i++)
    arr[i] = i;
}

/* { dg-final { scan-tree-dump "constant niter.*skipping" "ivbound" } } */
/* { dg-final { scan-tree-dump-not "Successfully versioned loop" "ivbound" } } */
