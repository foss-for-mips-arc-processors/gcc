/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -O1" } */

/* leaf function.  */
/* no need for shadow call stack */
int f1 (void) {
  return 0;
}

/* leaf function uses return address.  */
/* need shadow call stack push/pop */
/* return address in t0 */
int f2 (void)
{
  asm volatile ("":::"ra");
  return 0;
}

/* { dg-final { scan-assembler-times {addi\tgp,gp,4} 1 { target rv32 } } } */
/* { dg-final { scan-assembler-times {sw\tra,(-4|0)\(gp\)} 1 { target rv32 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-4} 1 { target rv32 } } } */
/* { dg-final { scan-assembler-times {lw\tt0,(-4|0)\(gp\)} 1 { target rv32 } } } */

/* { dg-final { scan-assembler-times {addi\tgp,gp,8} 1 { target rv64 } } } */
/* { dg-final { scan-assembler-times {sd\tra,(-8|0)\(gp\)} 1 { target rv64 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-8} 1 { target rv64 } } } */
/* { dg-final { scan-assembler-times {ld\tt0,(-8|0)\(gp\)} 1 { target rv64 } } } */
