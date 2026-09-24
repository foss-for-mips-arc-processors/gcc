/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-g" "-flto" } } */

/* Test RV32 PV2SI (2×32-bit packed vector) move patterns.
   On RV32, PV2SI uses register pairs and splits into two 32-bit lw/sw.
   No PLI.DW instruction exists, so non-zero const_vector with duplicate
   values splits into two li instructions.  Zero const uses addd rd,x0,x0.  */

typedef int pv2si __attribute__((vector_size (8)));

/* Test load operations - should generate two lw instructions */
pv2si
load_pv2si (pv2si *p)
{
  return *p;
}

/* Test store operations - should generate two sw instructions */
void
store_pv2si (pv2si *p, pv2si v)
{
  *p = v;
}

/* Test register-to-register move (function parameter passing) */
pv2si
move_pv2si (pv2si a)
{
  return a;
}

/* Test even register pair move using ADDD.
   When both source and destination are even-numbered register pairs,
   we use addd rd, rs, x0 (x0 pair reads as 64-bit zero) to copy the pair.
   PMV.DWS is a scalar broadcast instruction, not a pair copy.  */
pv2si
copy_pv2si_even (pv2si a, pv2si b)
{
  /* a is in a0,a1, b is in a2,a3 - both even starts */
  return b;  /* Should use addd a0,a2,x0 */
}

/* Test const_vector with duplicate values - should generate two li */
pv2si
const_dup_42 (void)
{
  return (pv2si){42, 42};
}

/* Test zero const_vector - should use addd rd, x0, x0 (single instruction) */
pv2si
const_zero (void)
{
  return (pv2si){0, 0};
}

/* { dg-final { scan-assembler-times {\mlw\M} 2 } } */
/* { dg-final { scan-assembler-times {\msw\M} 2 } } */
/* { dg-final { scan-assembler-times {\mli\t} 2 } } */
/* { dg-final { scan-assembler-times {\maddd\M} 2 } } */

