/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -ffreestanding" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

uint8_t usati_u8_from_i32 (int32_t x)
{
  if (x < 0) x = 0;
  if (x > 255) x = 255;
  return (uint8_t) x;
}
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,8} } } */

uint16_t usati_u16_from_i32 (int32_t x)
{
  if (x < 0) x = 0;
  if (x > 65535) x = 65535;
  return (uint16_t) x;
}
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,16} } } */

uint8_t usati_i8_from_i16 (int16_t x)
{
  int32_t xe = (int32_t) x;
  if (xe < 0) xe = 0;
  if (xe > 255) xe = 255;
  return (uint8_t) xe;
}
/* { dg-final { scan-assembler {\tusati\t[a-x0-9]+,[a-x0-9]+,8} } } */

/* Total: 3 usati instructions.  */
/* { dg-final { scan-assembler-times {\tusati\t} 3 } } */
