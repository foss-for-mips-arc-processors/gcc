/* { dg-do compile } */

extern int foo2 (int, int);
extern int foo1 (int);
extern int foo0 ();
extern void vfoo2 (int, int);
extern void vfoo1 (int);
extern void vfoo0 ();

#pragma intrinsic (foo2, "FOP2", 102, "XD")
#pragma intrinsic (foo1, "FOP1", 101, "XD")
#pragma intrinsic (foo0, "FOP0", 100, "XD")
#pragma intrinsic (vfoo2, "VOP2", 202, "XD")
#pragma intrinsic (vfoo1, "VOP1", 201, "XD")
#pragma intrinsic (vfoo0, "VOP0", 200, "XD")

int
test (void)
{
  vfoo2 (1,2);
  vfoo1 (3);
  vfoo0 ();
  return foo2 (1,2) + foo1 (3) + foo0 ();
}

/* { dg-final { scan-assembler-times ".extInstruction" 6 } } */
/* { dg-final { scan-assembler-times ".extInstruction fop2,102,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction fop1,101,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction fop0,100,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction vop2,202,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction vop1,201,XD" 1 } } */
/* { dg-final { scan-assembler-times ".extInstruction vop0,200,XD" 1 } } */

/* { dg-final { scan-assembler "fop2\ta\[0-9\],a\[0-9\],a\[0-9\]" } } */
/* { dg-final { scan-assembler "fop1\ta\[0-9\],a\[0-9\]" } } */
/* { dg-final { scan-assembler "fop0\ta\[0-9\]" } } */
/* { dg-final { scan-assembler "vop2\ta\[0-9\],a\[0-9\]" } } */
/* { dg-final { scan-assembler "vop1\ta\[0-9\]" } } */
/* { dg-final { scan-assembler "vop0" } } */
