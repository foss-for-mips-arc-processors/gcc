/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_multiple_exits (unsigned int *arr, unsigned int n)
{
  for (unsigned int i = 0; i < n; i++)
    {
      if (arr[i] == 0)
	break;
      arr[i] = i;
    }
}

/* { dg-final { scan-tree-dump-not "Successfully versioned loop" "ivbound" } } */
