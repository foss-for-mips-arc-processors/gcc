/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test that 4-byte packed vectors (PV4QI, PV2HI) are supported on RV64.
   P-extension instructions like padd.b and padd.h should work on both
   4-byte and 8-byte operands on RV64.  */

typedef signed char int8x4_t __attribute__((vector_size(4)));
typedef short int16x2_t __attribute__((vector_size(4)));
typedef unsigned char uint8x4_t __attribute__((vector_size(4)));
typedef unsigned short uint16x2_t __attribute__((vector_size(4)));

/* Test PV4QI (4 x int8) operations on RV64.  */

int8x4_t test_add_b_4 (int8x4_t a, int8x4_t b)
{
  return a + b;
}
/* { dg-final { scan-assembler-times "\\mpadd\\.b\\M" 1 } } */

int8x4_t test_sub_b_4 (int8x4_t a, int8x4_t b)
{
  return a - b;
}
/* { dg-final { scan-assembler-times "\\mpsub\\.b\\M" 1 } } */

/* Test PV2HI (2 x int16) operations on RV64.  */

int16x2_t test_add_h_2 (int16x2_t a, int16x2_t b)
{
  return a + b;
}
/* { dg-final { scan-assembler-times "\\mpadd\\.h\\M" 1 } } */

int16x2_t test_sub_h_2 (int16x2_t a, int16x2_t b)
{
  return a - b;
}
/* { dg-final { scan-assembler-times "\\mpsub\\.h\\M" 1 } } */

/* Test bitwise operations on 4-byte vectors.  */

int8x4_t test_and_b_4 (int8x4_t a, int8x4_t b)
{
  return a & b;
}

int8x4_t test_or_b_4 (int8x4_t a, int8x4_t b)
{
  return a | b;
}

int8x4_t test_xor_b_4 (int8x4_t a, int8x4_t b)
{
  return a ^ b;
}

/* Bitwise operations should use standard and/or/xor instructions.  */
/* { dg-final { scan-assembler-times "\\mand\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mor\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mxor\\M" 1 } } */

/* Test constant vectors on RV64.
   Note: 4-byte vectors cannot use PLI on RV64 because PLI broadcasts
   the value to all 64 bits, which would not match the 32-bit vector.
   These are included to verify the compiler handles them correctly.  */

int8x4_t test_const_b_4 (void)
{
  return (int8x4_t){42, 42, 42, 42};
}

int16x2_t test_const_h_2 (void)
{
  return (int16x2_t){500, 500};
}

/* Test pair operations on 4-byte vectors (PV4QI) on RV64.  */

int8x4_t test_ppaireo_b_4 (int8x4_t a, int8x4_t b)
{
  /* {a[0], b[1], a[2], b[3]} */
  return (int8x4_t){a[0], b[1], a[2], b[3]};
}
/* { dg-final { scan-assembler-times "\\mppaireo\\.b\\M" 1 } } */

int8x4_t test_ppairoe_b_4 (int8x4_t a, int8x4_t b)
{
  /* {a[1], b[0], a[3], b[2]} */
  return (int8x4_t){a[1], b[0], a[3], b[2]};
}
/* { dg-final { scan-assembler-times "\\mppairoe\\.b\\M" 1 } } */

int8x4_t test_ppairo_b_4 (int8x4_t a, int8x4_t b)
{
  /* {a[1], b[1], a[3], b[3]} */
  return (int8x4_t){a[1], b[1], a[3], b[3]};
}
/* { dg-final { scan-assembler-times "\\mppairo\\.b\\M" 1 } } */

int8x4_t test_ppaire_b_4 (int8x4_t a, int8x4_t b)
{
  /* {a[0], b[0], a[2], b[2]} */
  return (int8x4_t){a[0], b[0], a[2], b[2]};
}
/* { dg-final { scan-assembler-times "\\mppaire\\.b\\M" 1 } } */
