/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -mstrict-align -fdump-tree-vect-details" } */

int
dot (const signed char *a, const signed char *b, unsigned int n)
{
  int sum = 0;
  for (unsigned int i = 0; i < n; ++i)
    sum += (int) a[i] * b[i];
  return sum;
}

/* The vector path must use aligned word loads, not byte assembly.  */
/* { dg-final { scan-tree-dump "loop versioned for vectorization to enhance alignment" "vect" } } */
/* { dg-final { scan-assembler {pm4adda\.b} } } */
/* { dg-final { scan-assembler-not {\mlbu\M} } } */
