/* { dg-do compile } */
/* { dg-options "-funroll-all-loops -fno-tree-vectorize -fdump-rtl-loop2_unroll-details" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-Os" "-Oz" } { "" } } */

int
sum (short *p, short *e)
{
  int s = 0;
  do
    s += *p;
  while (++p != e);
  return s;
}

/* { dg-final { scan-rtl-dump "Unrolled loop 7 times, counting # of iterations in runtime" "loop2_unroll" } } */
/* { dg-final { scan-assembler {\mandi\t[a-z0-9]+,[a-z0-9]+,14\M} } } */
/* { dg-final { scan-assembler-not {\msrli\M} } } */
