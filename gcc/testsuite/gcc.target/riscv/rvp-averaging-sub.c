/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test averaging subtract instructions for P-extension.
   Pattern: (truncate (ashiftrt (minus (extend a) (extend b)) 1))
   This tests the avg_sub<mode>3_floor and uavg_sub<mode>3_floor expanders.  */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

/* pasub.b: signed averaging subtract byte (8 bytes) - widening pattern */
int8x8_t test_pasub_b (int8x8_t a, int8x8_t b)
{
  return (int8x8_t){
    (int8_t)(((int16_t)a[0] - (int16_t)b[0]) >> 1),
    (int8_t)(((int16_t)a[1] - (int16_t)b[1]) >> 1),
    (int8_t)(((int16_t)a[2] - (int16_t)b[2]) >> 1),
    (int8_t)(((int16_t)a[3] - (int16_t)b[3]) >> 1),
    (int8_t)(((int16_t)a[4] - (int16_t)b[4]) >> 1),
    (int8_t)(((int16_t)a[5] - (int16_t)b[5]) >> 1),
    (int8_t)(((int16_t)a[6] - (int16_t)b[6]) >> 1),
    (int8_t)(((int16_t)a[7] - (int16_t)b[7]) >> 1)
  };
}

/* pasub.b: signed averaging subtract byte (4 bytes) - widening pattern */
int8x4_t test_pasub_b_4 (int8x4_t a, int8x4_t b)
{
  return (int8x4_t){
    (int8_t)(((int16_t)a[0] - (int16_t)b[0]) >> 1),
    (int8_t)(((int16_t)a[1] - (int16_t)b[1]) >> 1),
    (int8_t)(((int16_t)a[2] - (int16_t)b[2]) >> 1),
    (int8_t)(((int16_t)a[3] - (int16_t)b[3]) >> 1)
  };
}

/* pasub.h: signed averaging subtract halfword (4 halfwords) - widening pattern */
int16x4_t test_pasub_h (int16x4_t a, int16x4_t b)
{
  return (int16x4_t){
    (int16_t)(((int32_t)a[0] - (int32_t)b[0]) >> 1),
    (int16_t)(((int32_t)a[1] - (int32_t)b[1]) >> 1),
    (int16_t)(((int32_t)a[2] - (int32_t)b[2]) >> 1),
    (int16_t)(((int32_t)a[3] - (int32_t)b[3]) >> 1)
  };
}

/* pasub.h: signed averaging subtract halfword (2 halfwords) - widening pattern */
int16x2_t test_pasub_h_2 (int16x2_t a, int16x2_t b)
{
  return (int16x2_t){
    (int16_t)(((int32_t)a[0] - (int32_t)b[0]) >> 1),
    (int16_t)(((int32_t)a[1] - (int32_t)b[1]) >> 1)
  };
}

/* pasub.w: signed averaging subtract word (2 words) - widening pattern */
int32x2_t test_pasub_w (int32x2_t a, int32x2_t b)
{
  return (int32x2_t){
    (int32_t)(((int64_t)a[0] - (int64_t)b[0]) >> 1),
    (int32_t)(((int64_t)a[1] - (int64_t)b[1]) >> 1)
  };
}

/* pasubu.b: unsigned averaging subtract byte (8 bytes) - widening pattern
   Use (uint32_t) cast to ensure unsigned arithmetic and logical shift.  */
uint8x8_t test_pasubu_b (uint8x8_t a, uint8x8_t b)
{
  return (uint8x8_t){
    (uint8_t)(((uint32_t)(uint16_t)a[0] - (uint32_t)(uint16_t)b[0]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[1] - (uint32_t)(uint16_t)b[1]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[2] - (uint32_t)(uint16_t)b[2]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[3] - (uint32_t)(uint16_t)b[3]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[4] - (uint32_t)(uint16_t)b[4]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[5] - (uint32_t)(uint16_t)b[5]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[6] - (uint32_t)(uint16_t)b[6]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[7] - (uint32_t)(uint16_t)b[7]) >> 1)
  };
}

/* pasubu.b: unsigned averaging subtract byte (4 bytes) - widening pattern
   Use (uint32_t) cast to ensure unsigned arithmetic and logical shift.  */
uint8x4_t test_pasubu_b_4 (uint8x4_t a, uint8x4_t b)
{
  return (uint8x4_t){
    (uint8_t)(((uint32_t)(uint16_t)a[0] - (uint32_t)(uint16_t)b[0]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[1] - (uint32_t)(uint16_t)b[1]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[2] - (uint32_t)(uint16_t)b[2]) >> 1),
    (uint8_t)(((uint32_t)(uint16_t)a[3] - (uint32_t)(uint16_t)b[3]) >> 1)
  };
}

/* pasubu.h: unsigned averaging subtract halfword (4 halfwords) - widening pattern */
uint16x4_t test_pasubu_h (uint16x4_t a, uint16x4_t b)
{
  return (uint16x4_t){
    (uint16_t)(((uint32_t)a[0] - (uint32_t)b[0]) >> 1),
    (uint16_t)(((uint32_t)a[1] - (uint32_t)b[1]) >> 1),
    (uint16_t)(((uint32_t)a[2] - (uint32_t)b[2]) >> 1),
    (uint16_t)(((uint32_t)a[3] - (uint32_t)b[3]) >> 1)
  };
}

/* pasubu.h: unsigned averaging subtract halfword (2 halfwords) - widening pattern */
uint16x2_t test_pasubu_h_2 (uint16x2_t a, uint16x2_t b)
{
  return (uint16x2_t){
    (uint16_t)(((uint32_t)a[0] - (uint32_t)b[0]) >> 1),
    (uint16_t)(((uint32_t)a[1] - (uint32_t)b[1]) >> 1)
  };
}

/* pasubu.w: unsigned averaging subtract word (2 words) - widening pattern */
uint32x2_t test_pasubu_w (uint32x2_t a, uint32x2_t b)
{
  return (uint32x2_t){
    (uint32_t)(((uint64_t)a[0] - (uint64_t)b[0]) >> 1),
    (uint32_t)(((uint64_t)a[1] - (uint64_t)b[1]) >> 1)
  };
}

/* On RV64, both 8-byte and 4-byte packed vectors can use pasub/pasubu
   instructions. The 8-byte vectors use RVP packed modes (PV8QI/PV4HI/PV2SI),
   while 4-byte vectors also benefit from the same averaging subtract pattern.  */
/* { dg-final { scan-assembler-times {\tpasub\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpasub\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpasub\.w\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpasubu\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpasubu\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpasubu\.w\t} 1 } } */

