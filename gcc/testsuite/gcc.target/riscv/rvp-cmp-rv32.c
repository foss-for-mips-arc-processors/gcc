/* { dg-do compile } */
/* { dg-options "-march=rv32gcbp0p21 -mabi=ilp32 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test PMSEQ/PMSLT/PMSLTU register-pair instructions on RV32.
   On RV32, 8-byte (64-bit) vector comparisons use register pairs with
   double-wide suffixes: .db (byte), .dh (halfword), .dw (word).
   The PCMP mode iterator enables these for PV8QI, PV4HI, PV2SI modes.  */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;

typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

/* pmseq.db: 8 signed bytes equal */
int8x8_t test_pmseq_db (int8x8_t a, int8x8_t b)
{
  return a == b;
}

/* pmslt.db: 8 signed bytes less-than */
int8x8_t test_pmslt_db (int8x8_t a, int8x8_t b)
{
  return a < b;
}

/* pmsltu.db: 8 unsigned bytes less-than */
uint8x8_t test_pmsltu_db (uint8x8_t a, uint8x8_t b)
{
  return a < b;
}

/* pmseq.dh: 4 signed halfwords equal */
int16x4_t test_pmseq_dh (int16x4_t a, int16x4_t b)
{
  return a == b;
}

/* pmslt.dh: 4 signed halfwords less-than */
int16x4_t test_pmslt_dh (int16x4_t a, int16x4_t b)
{
  return a < b;
}

/* pmsltu.dh: 4 unsigned halfwords less-than */
uint16x4_t test_pmsltu_dh (uint16x4_t a, uint16x4_t b)
{
  return a < b;
}

/* pmseq.dw: 2 signed words equal */
int32x2_t test_pmseq_dw (int32x2_t a, int32x2_t b)
{
  return a == b;
}

/* pmslt.dw: 2 signed words less-than */
int32x2_t test_pmslt_dw (int32x2_t a, int32x2_t b)
{
  return a < b;
}

/* pmsltu.dw: 2 unsigned words less-than */
uint32x2_t test_pmsltu_dw (uint32x2_t a, uint32x2_t b)
{
  return a < b;
}

/* { dg-final { scan-assembler-times {\tpmseq\.db\t}  1 } } */
/* { dg-final { scan-assembler-times {\tpmslt\.db\t}  1 } } */
/* { dg-final { scan-assembler-times {\tpmsltu\.db\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpmseq\.dh\t}  1 } } */
/* { dg-final { scan-assembler-times {\tpmslt\.dh\t}  1 } } */
/* { dg-final { scan-assembler-times {\tpmsltu\.dh\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpmseq\.dw\t}  1 } } */
/* { dg-final { scan-assembler-times {\tpmslt\.dw\t}  1 } } */
/* { dg-final { scan-assembler-times {\tpmsltu\.dw\t} 1 } } */
