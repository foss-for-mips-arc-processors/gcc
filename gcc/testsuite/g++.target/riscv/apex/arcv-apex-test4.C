/* { dg-do compile } */

void void_func ();
void void_unary (int);
void void_binary (int, int);

int func ();
int unary (int);
int binary (int, int);

#pragma intrinsic (void_func, "VOID_FUNC", 1, "XD")
#pragma intrinsic (void_unary, "VOID_UNARY", 2, "XD")
#pragma intrinsic (void_binary, "VOID_BINARY", 3, "XD")
#pragma intrinsic (func, "FUNC", 4, "XD")
#pragma intrinsic (unary, "UNARY", 5, "XD")
#pragma intrinsic (binary, "BINARY", 6, "XD")

int
test (void)
{
  void_func ();
  void_unary (1);
  void_binary (1, 2);
  return func () + unary (3) + binary (4, 5);
}

/* { dg-final { scan-assembler-times ".extInstruction" 6 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_func,1,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_unary,2,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction void_binary,3,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction func,4,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction unary,5,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction binary,6,XD" 1 } } */
