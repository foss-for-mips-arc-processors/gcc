/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" } } */

typedef signed short pv4hi __attribute__((vector_size(8)));
typedef signed char pv8qi __attribute__((vector_size(8)));
typedef unsigned short pv4hiu __attribute__((vector_size(8)));
typedef unsigned char pv8qiu __attribute__((vector_size(8)));

pv4hi
test_1 (pv4hi a, pv4hi b)
{
  pv4hi r;
  r[0] = ((int)a[0] * (int)b[0]) >> 16;
  r[1] = ((int)a[1] * (int)b[1]) >> 16;
  r[2] = ((int)a[2] * (int)b[2]) >> 16;
  r[3] = ((int)a[3] * (int)b[3]) >> 16;
  return r;
}

pv8qi
test_2 (pv8qi a, pv8qi b)
{
  pv8qi r;
  for (int i = 0; i < 8; i++)
    r[i] = ((short)a[i] * (short)b[i]) >> 8;
  return r;
}

pv4hiu
test_3 (pv4hiu a, pv4hiu b)
{
  pv4hiu r;
  r[0] = ((unsigned)a[0] * (unsigned)b[0]) >> 16;
  r[1] = ((unsigned)a[1] * (unsigned)b[1]) >> 16;
  r[2] = ((unsigned)a[2] * (unsigned)b[2]) >> 16;
  r[3] = ((unsigned)a[3] * (unsigned)b[3]) >> 16;
  return r;
}

pv8qiu
test_4 (pv8qiu a, pv8qiu b)
{
  pv8qiu r;
  for (int i = 0; i < 8; i++)
    r[i] = ((unsigned short)a[i] * (unsigned short)b[i]) >> 8;
  return r;
}

/* { dg-final { scan-assembler-times {\mpmulh\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmulh\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmulhu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmulhu\.b\M} 2 } } */
