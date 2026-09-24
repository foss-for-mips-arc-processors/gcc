/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

typedef unsigned long long uint64_t;

/* Bitwise select operations using MVM/MVMN.
   The compiler may choose either instruction based on register allocation. */

uint64_t test_select_1 (uint64_t rd, uint64_t rs1, uint64_t mask)
{
  return (~mask & rd) | (mask & rs1);
}

uint64_t test_select_2 (uint64_t rd, uint64_t rs1, uint64_t mask)
{
  return (mask & rd) | (~mask & rs1);
}

uint64_t test_select_3 (uint64_t rd, uint64_t rs1, uint64_t mask)
{
  return (mask & rs1) | (~mask & rd);
}

uint64_t test_select_4 (uint64_t rd, uint64_t rs1, uint64_t mask)
{
  return (~mask & rs1) | (mask & rd);
}

/* { dg-final { scan-assembler "\\tmvmn?\\t" } } */
