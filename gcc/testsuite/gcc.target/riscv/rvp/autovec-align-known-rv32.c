/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -mstrict-align -fdump-tree-vect-details" } */

int
dot (const signed char *a, const signed char *b, unsigned int n)
{
  a = __builtin_assume_aligned (a, 4);
  b = __builtin_assume_aligned (b, 4);
  int sum = 0;
  for (unsigned int i = 0; i < n; ++i)
    sum += (int) a[i] * b[i];
  return sum;
}

/* Four-byte alignment suffices for RV32 register-pair loads.  */
/* { dg-final { scan-tree-dump "LOOP VECTORIZED" "vect" } } */
/* { dg-final { scan-tree-dump-not "loop versioned" "vect" } } */
/* { dg-final { scan-assembler {pm4adda\.b} } } */
/* { dg-final { scan-assembler-not {\mlbu\M} } } */
