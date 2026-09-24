/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" } } */
/* { dg-require-effective-target rv32 } */

typedef signed char    pv8qi  __attribute__((vector_size (8)));
typedef signed short   pv4hi  __attribute__((vector_size (8)));
typedef signed int     pv2si  __attribute__((vector_size (8)));

typedef unsigned char  pvu8qi __attribute__((vector_size (8)));
typedef unsigned short pvu4hi __attribute__((vector_size (8)));
typedef unsigned int   pvu2si __attribute__((vector_size (8)));

/* --- psrai.db / psra.dbs: arithmetic right shift, 8-bit elements --- */

pv8qi
test_srai_db (pv8qi a)
{
  return a >> 1;
}

pv8qi
test_sra_dbs (pv8qi a, int b)
{
  return a >> b;
}

/* --- psrai.dh / psra.dhs: arithmetic right shift, 16-bit elements --- */

pv4hi
test_srai_dh (pv4hi a)
{
  return a >> 1;
}

pv4hi
test_sra_dhs (pv4hi a, int b)
{
  return a >> b;
}

/* --- psrai.dw / psra.dws: arithmetic right shift, 32-bit elements --- */

pv2si
test_srai_dw (pv2si a)
{
  return a >> 1;
}

pv2si
test_sra_dws (pv2si a, int b)
{
  return a >> b;
}

/* --- psrli.db / psrl.dbs: logical right shift, 8-bit elements --- */

pvu8qi
test_srli_db (pvu8qi a)
{
  return a >> 1;
}

pvu8qi
test_srl_dbs (pvu8qi a, int b)
{
  return a >> b;
}

/* --- psrli.dh / psrl.dhs: logical right shift, 16-bit elements --- */

pvu4hi
test_srli_dh (pvu4hi a)
{
  return a >> 1;
}

pvu4hi
test_srl_dhs (pvu4hi a, int b)
{
  return a >> b;
}

/* --- psrli.dw / psrl.dws: logical right shift, 32-bit elements --- */

pvu2si
test_srli_dw (pvu2si a)
{
  return a >> 1;
}

pvu2si
test_srl_dws (pvu2si a, int b)
{
  return a >> b;
}

/* { dg-final { scan-assembler-times {psrai\.db} 1 } } */
/* { dg-final { scan-assembler-times {psra\.dbs} 1 } } */
/* { dg-final { scan-assembler-times {psrai\.dh} 1 } } */
/* { dg-final { scan-assembler-times {psra\.dhs} 1 } } */
/* { dg-final { scan-assembler-times {psrai\.dw} 1 } } */
/* { dg-final { scan-assembler-times {psra\.dws} 1 } } */
/* { dg-final { scan-assembler-times {psrli\.db} 1 } } */
/* { dg-final { scan-assembler-times {psrl\.dbs} 1 } } */
/* { dg-final { scan-assembler-times {psrli\.dh} 1 } } */
/* { dg-final { scan-assembler-times {psrl\.dhs} 1 } } */
/* { dg-final { scan-assembler-times {psrli\.dw} 1 } } */
/* { dg-final { scan-assembler-times {psrl\.dws} 1 } } */
