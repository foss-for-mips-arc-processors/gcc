/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

void
half_halfword (short *restrict d, const short *restrict a, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}

/* One scalar store for the alignment prologue, three for the epilogue
   and one for the separate scalar loop, not four epilogue stores.  */
/* { dg-final { scan-tree-dump "versioning bounds the scalar epilogue" "vect" } } */
/* { dg-final { scan-assembler-times {\msh\M} 5 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dh\M} 1 } } */
