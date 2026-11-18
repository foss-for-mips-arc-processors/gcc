/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

void
and_bytes (unsigned char *restrict d, const unsigned char *restrict a,
	   const unsigned char *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = a[i] & b[i];
}

/* A pair-wide logical statement costs two scalar operations.  */
/* { dg-final { scan-tree-dump {1 times vector_stmt costs 2} "vect" } } */
/* { dg-final { scan-tree-dump "LOOP VECTORIZED" "vect" } } */
