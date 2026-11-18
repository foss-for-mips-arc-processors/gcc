/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p6 -mabi=lp64 -O2 -fwrapv" } */

/* Narrow arithmetic wraps before shifting.  It is not a widened average.  */

typedef signed char pv8qi __attribute__ ((vector_size (8)));
typedef short pv4hi __attribute__ ((vector_size (8)));
typedef int pv2si __attribute__ ((vector_size (8)));
typedef unsigned char pv8uqi __attribute__ ((vector_size (8)));
typedef unsigned short pv4uhi __attribute__ ((vector_size (8)));
typedef unsigned int pv2usi __attribute__ ((vector_size (8)));

pv8qi
test_pasub_b (pv8qi a, pv8qi b)
{
  return (a - b) >> 1;
}

pv4hi
test_pasub_h (pv4hi a, pv4hi b)
{
  return (a - b) >> 1;
}

pv2si
test_pasub_w (pv2si a, pv2si b)
{
  return (a - b) >> 1;
}

pv8uqi
test_pasubu_b (pv8uqi a, pv8uqi b)
{
  return (a - b) >> 1;
}

pv4uhi
test_pasubu_h (pv4uhi a, pv4uhi b)
{
  return (a - b) >> 1;
}

pv2usi
test_pasubu_w (pv2usi a, pv2usi b)
{
  return (a - b) >> 1;
}

/* { dg-final { scan-assembler-not {\mpasubu?\.[bhw]\M} } } */

