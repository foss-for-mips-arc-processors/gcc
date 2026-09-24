/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -ffreestanding" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test USATI codegen for narrowing clamp patterns on RV32.
   GCC combine emits smin(x, upper) then smax(result, 0), which the
   *usati_alt pattern folds into a single usati instruction.  */

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

/* Clamp int32 to [0, 255] and narrow to int8.  */
int8_t usati_i8_from_i32 (int32_t x)
{
  if (x < 0) x = 0;
  if (x > 255) x = 255;
  return (int8_t) x;
}
/* { dg-final { scan-assembler {\musati\M.*,.*,\s*8} } } */

/* Clamp int32 to [0, 65535] and narrow to int16.  */
int16_t usati_i16_from_i32 (int32_t x)
{
  if (x < 0) x = 0;
  if (x > 65535) x = 65535;
  return (int16_t) x;
}
/* { dg-final { scan-assembler {\musati\M.*,.*,\s*16} } } */

/* Sign-extend int16 to int32, clamp to [0, 255], narrow to int8.  */
int8_t usati_i8_from_i16 (int16_t x)
{
  int32_t xe = (int32_t) x;
  if (xe < 0) xe = 0;
  if (xe > 255) xe = 255;
  return (int8_t) xe;
}
/* { dg-final { scan-assembler {\musati\M.*,.*,\s*8} } } */

/* Total: 3 usati instructions.  */
/* { dg-final { scan-assembler-times {\tusati\t} 3 } } */
