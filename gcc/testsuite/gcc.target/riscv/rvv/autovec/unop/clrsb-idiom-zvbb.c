/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcpv_zvbb -mabi=lp64d -fdump-tree-vect-details -fdump-tree-optimized" } */

void
headroom (int *__restrict out, const unsigned int *__restrict in,
	  unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      unsigned int value = in[i];
      unsigned int mask = 0u - (value >> 31);
      out[i] = __builtin_clzg (value ^ mask, 32) - 1;
    }
}

/* The late scalar fold must not hide the vector CLZ opportunity.  */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 1 "vect" } } */
/* { dg-final { scan-tree-dump-not {\.CLRSB \(} "optimized" } } */
/* { dg-final { scan-assembler-times {\tvclz\.v\t} 1 } } */
