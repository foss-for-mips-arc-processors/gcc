/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

int
dot (const short *a, const short *b, unsigned int n)
{
  int sum = 0;
  for (unsigned int i = 0; i < n; ++i)
    sum += (int) a[i] * b[i];
  return sum;
}

/* Two loads and one MACC; do not charge the extensions and multiply again.  */
/* { dg-final { scan-tree-dump "Scalar iteration cost: 3" "vect" } } */
/* { dg-final { scan-assembler {\mmacc\.h00\M} } } */
