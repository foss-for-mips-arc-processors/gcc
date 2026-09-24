/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-g" "-flto" } } */

/* Test RV32 8-byte packed vector constant loading with PLI.DB/DH/PLUI.DH.
   These are RV32-only instructions that load replicated constants into
   64-bit register pairs with a single instruction.  */

typedef signed char pv8qi __attribute__((vector_size (8)));
typedef short pv4hi __attribute__((vector_size (8)));

/* Test PLI.DB: replicated 8-bit immediate to 8 bytes */
pv8qi
pli_db_42 (void)
{
  return (pv8qi){42, 42, 42, 42, 42, 42, 42, 42};
}

pv8qi
pli_db_neg10 (void)
{
  return (pv8qi){-10, -10, -10, -10, -10, -10, -10, -10};
}

/* Test PLI.DH: replicated 10-bit signed immediate to 4 halfwords */
pv4hi
pli_dh_100 (void)
{
  return (pv4hi){100, 100, 100, 100};
}

pv4hi
pli_dh_neg256 (void)
{
  return (pv4hi){-256, -256, -256, -256};
}

/* Test PLUI.DH: (imm10 << 6) to 4 halfwords (values outside PLI.DH range) */
pv4hi
plui_dh_4096 (void)
{
  /* 4096 = 64 << 6 */
  return (pv4hi){4096, 4096, 4096, 4096};
}

pv4hi
plui_dh_neg32768 (void)
{
  /* -32768 = -512 << 6 */
  return (pv4hi){-32768, -32768, -32768, -32768};
}

/* Test SMALL_OPERAND replicated values: must use PLI not li (li only sets
   the low 32-bit register, leaving the upper half undefined).  */
pv8qi
pv8qi_minus1 (void)
{
  return (pv8qi){-1, -1, -1, -1, -1, -1, -1, -1};
}

/* Test zero: use addd rd, x0, x0 (not li which only sets low register).  */
pv8qi
pv8qi_zero (void)
{
  return (pv8qi){0, 0, 0, 0, 0, 0, 0, 0};
}

pv4hi
pv4hi_zero (void)
{
  return (pv4hi){0, 0, 0, 0};
}

/* { dg-final { scan-assembler-times {\mpli\.db\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpli\.dh\M} 2 } } */
/* { dg-final { scan-assembler-times {\mplui\.dh\M} 2 } } */
/* { dg-final { scan-assembler-times {\maddd\M} 2 } } */
