/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" } } */
/* { dg-require-effective-target rv32 } */

typedef char  pv8qi __attribute__((vector_size (8)));
typedef short pv4hi __attribute__((vector_size (8)));
typedef int   pv2si __attribute__((vector_size (8)));

/* --- pslli.db / psll.dbs: 8-bit elements in 8-byte register pair --- */

pv8qi
test_slli_db (pv8qi a)
{
  return a << 1;
}

pv8qi
test_sll_dbs (pv8qi a, int b)
{
  return a << b;
}

/* --- pslli.dh / psll.dhs: 16-bit elements in 8-byte register pair --- */

pv4hi
test_slli_dh (pv4hi a)
{
  return a << 1;
}

pv4hi
test_sll_dhs (pv4hi a, int b)
{
  return a << b;
}

/* --- pslli.dw / psll.dws: 32-bit elements in 8-byte register pair --- */

pv2si
test_slli_dw (pv2si a)
{
  return a << 1;
}

pv2si
test_sll_dws (pv2si a, int b)
{
  return a << b;
}

/* { dg-final { scan-assembler-times {pslli\.db} 1 } } */
/* { dg-final { scan-assembler-times {psll\.dbs} 1 } } */
/* { dg-final { scan-assembler-times {pslli\.dh} 1 } } */
/* { dg-final { scan-assembler-times {psll\.dhs} 1 } } */
/* { dg-final { scan-assembler-times {pslli\.dw} 1 } } */
/* { dg-final { scan-assembler-times {psll\.dws} 1 } } */
