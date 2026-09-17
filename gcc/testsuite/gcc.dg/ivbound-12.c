/* { dg-do compile } */
/* { dg-options "-O2 -fversion-loops-for-iv-overflow -fdump-tree-ivbound-details" } */

void
test_pointer_iv (int *start, int *end)
{
  for (int *p = start; p < end; p++)
    *p = 0;
}

/* { dg-final { scan-tree-dump-not "Found unsigned IV in loop" "ivbound" } } */
