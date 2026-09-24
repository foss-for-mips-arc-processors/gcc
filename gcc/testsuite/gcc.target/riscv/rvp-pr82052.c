/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O1" } */

/* Regression test for pr82052.c which previously caused an ICE
   with MVM/MVMN XOR pattern constraints.
   
   This is a reduced version that tests the specific pattern that
   caused the register allocation constraint violation:
   ((a ^ b) & mask) ^ c where c is not equal to a or b after reload.  */

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;

uint64_t test_complex_xor_1 (uint64_t a, uint64_t b, uint64_t mask, uint64_t c)
{
  /* This pattern should compile without ICE, even if it doesn't
     match the MVM XOR optimization.  */
  return ((a ^ b) & mask) ^ c;
}

uint64_t test_complex_xor_2 (uint64_t a, uint64_t b, uint64_t mask)
{
  /* This should optimize to MVM since c == a.  */
  uint64_t c = a;
  return ((a ^ b) & mask) ^ c;
}

uint64_t test_complex_xor_3 (uint64_t a, uint64_t b, uint64_t mask)
{
  /* This should optimize to MVMN since c == b.  */
  uint64_t c = b;
  return ((a ^ b) & mask) ^ c;
}

uint32_t test_complex_xor_32_1 (uint32_t a, uint32_t b, uint32_t mask, uint32_t c)
{
  return ((a ^ b) & mask) ^ c;
}

uint32_t test_complex_xor_32_2 (uint32_t a, uint32_t b, uint32_t mask)
{
  uint32_t c = a;
  return ((a ^ b) & mask) ^ c;
}

/* This test should compile without errors (previously caused ICE).  */
