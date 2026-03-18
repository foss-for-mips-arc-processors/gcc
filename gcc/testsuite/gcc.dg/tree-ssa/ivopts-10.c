/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-ivopts-details" } */

/* Test that SCEV analysis can prove IVs with non-constant steps don't
   overflow when the loop iteration count is bounded by a runtime check.  */

typedef unsigned int u32;

void
foo (u32 a[], u32 b[], u32 c[], u32 size)
{
  if (size < 500)
    for (u32 i = 0; i < size; i++)
      {
	for (u32 j = 0; j < size; j++)
	  {
	    c[i * size + j] = 0;
	    for (u32 k = 0; k < size; k++)
	      {
		c[i * size + j] += a[i * size + k] * b[k * size + j];
	      }
	  }
      }
}

/* { dg-final { scan-tree-dump "Selected IV set.*:13,.*5 IVs:" "ivopts" } } */
