/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-vect-details" } */

void
half_aligned (unsigned short *d, const unsigned short *a, unsigned n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  for (unsigned i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}

/* The alias-versioning threshold permits a two-element vector epilogue
   even when there are too few elements for the four-element main loop.  */
/* { dg-final { scan-tree-dump "LOOP EPILOGUE VECTORIZED" "vect" } } */
/* { dg-final { scan-tree-dump-not "versioning bounds the scalar epilogue" "vect" } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 2 } } */
