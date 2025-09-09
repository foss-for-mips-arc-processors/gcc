/* { dg-do compile } */
/* { dg-options "-mabi=lp64d -march=rv64gc" }*/

#include <stdint.h>
void voidFunc ();
void voidUnary (int64_t);
void voidBinary (int64_t, int64_t);

int64_t Func ();
int64_t Unary (int64_t);
int64_t Binary (int64_t, int64_t);

#pragma intrinsic (voidFunc, "VOID_FUNC", 1)
#pragma intrinsic (voidUnary, "VOID_UNARY", 2)
#pragma intrinsic (voidBinary, "VOID_BINARY", 3)
#pragma intrinsic (Func, "FUNC", 4)
#pragma intrinsic (Unary, "UNARY", 5)
#pragma intrinsic (Binary, "BINARY", 6)

int64_t
foo (int64_t a, int64_t b, int64_t c)
{
  voidFunc();

  voidUnary(a);
  voidUnary(12);
  voidUnary(-2048);
  voidUnary(10000);

  voidBinary(a, b);
  voidBinary(a, 12);
  voidBinary(b, 2047);
  voidBinary(a, 10000);

  return Func() + Unary(a) + Unary(12) + Unary(-2048) + Unary(10000) +
                  Binary(a, b) + Binary(a, 12) + Binary(c, 1000) + Binary(a, 100000);
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