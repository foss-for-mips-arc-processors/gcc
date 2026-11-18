/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-vect-details" } */

void
half_word (unsigned *restrict d, const unsigned *restrict a, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}

/* One scalar store each for the alignment prologue, the single-element
   epilogue and the separate scalar loop.  */
/* { dg-final { scan-tree-dump "versioning bounds the scalar epilogue" "vect" } } */
/* { dg-final { scan-assembler-times {\msw\M} 3 } } */
/* { dg-final { scan-assembler-times {\msd\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.w\M} 1 } } */
