/* { dg-do compile } */
/* { dg-options "-mabi=lp64d -march=rv64gc" }*/

#include <stdint.h>
void void_func ();
void void_unary (int64_t);
void void_binary (int64_t, int64_t);

int64_t func ();
int64_t unary (int64_t);
int64_t binary (int64_t, int64_t);

#pragma intrinsic (void_func, "VOID_FUNC", 1)
#pragma intrinsic (void_unary, "VOID_UNARY", 2)
#pragma intrinsic (void_binary, "VOID_BINARY", 3)
#pragma intrinsic (func, "FUNC", 4)
#pragma intrinsic (unary, "UNARY", 5)
#pragma intrinsic (binary, "BINARY", 6)

int64_t
foo (int64_t a, int64_t b, int64_t c)
{
  void_func ();

  void_unary (a);
  void_unary (12);
  void_unary (-2048);
  void_unary (10000);

  void_binary (a, b);
  void_binary (a, 12);
  void_binary (b, 2047);
  void_binary (a, 10000);

  return func () + unary (a) + unary (12) + unary (-2048) + unary (10000)
     + binary (a, b) + binary (a, 12) + binary (c, 1000) + binary (a, 100000);
}

/* { dg-final { scan-assembler-times ".extInstruction" 10 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_func,1,XD,void,no_src0,no_src1" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_unary,2,XD,void,no_src1" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_unaryi,2,XI,void" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_binary,3,XD,void" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_binaryi,3,XS,void" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction func,4,XD,no_src0,no_src1" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction unary,5,XD,no_src1" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction unaryi,5,XI" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction binary,6,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction binaryi,6,XS,XC" 1 } } */

/* { dg-final { scan-assembler-times "\tvoid_func" 1 } } */
/* { dg-final { scan-assembler-times "\tvoid_unaryi\t(12|0xc)" 1 } } */
/* { dg-final { scan-assembler-times "\tvoid_unaryi\t(-2048|-0x800)" 1 } } */
/* { dg-final { scan-assembler-times "void_unary\t(a|t)\[0-5\]" 2 } } */
/* { dg-final { scan-assembler-times "void_binaryi\t(a|t)\[0-5\],(12|0xc)" 1 } } */
/* { dg-final { scan-assembler-times "void_binary\t(a|t)\[0-5\],(a|t)\[0-5\]" 3 } } */
/* { dg-final { scan-assembler-times "func\t(a|t)\[0-5\]" 1 } } */
/* { dg-final { scan-assembler-times "unaryi\t(a|t)\[0-5\],(12|0xc)" 1 } } */
/* { dg-final { scan-assembler-times "unaryi\t(a|t)\[0-5\],(-2048|-0x800)" 1 } } */
/* { dg-final { scan-assembler-times "unary\t(a|t)\[0-5\],(a|t)\[0-5\]" 2 } } */
/* { dg-final { scan-assembler-times "binaryi\t(a|t)\[0-5\],(a|t)\[0-5\],(12|0xc)" 1 } } */
/* { dg-final { scan-assembler-times "binaryi\t(a|t)\[0-5\],(a|t)\[0-5\],(1000|0x3e8)" 1 } } */
/* { dg-final { scan-assembler-times "binary\t(a|t)\[0-5\],(a|t)\[0-5\],(a|t)\[0-5\]" 2 } } */
