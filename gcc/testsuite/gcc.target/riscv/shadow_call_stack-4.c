/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fno-omit-frame-pointer -foptimize-sibling-calls" } */

int foo (int);

/* function disable shadow call stack.  */
int __attribute__((no_sanitize("shadow-call-stack"))) f1 (void)
{
  foo (1);
  return 0;
}

/* { dg-final { scan-assembler-not {addi\tgp,gp,4} { target rv32 } } } */
/* { dg-final { scan-assembler-not {sw\tra,(-4|0)\(gp\)} { target rv32 } } } */
/* { dg-final { scan-assembler-not {addi\tgp,gp,-4} { target rv32 } } } */
/* { dg-final { scan-assembler-not {lw\tt0,(-4|0)\(gp\)} { target rv32 } } } */

/* { dg-final { scan-assembler-not {addi\tgp,gp,8} { target rv64 } } } */
/* { dg-final { scan-assembler-not {sd\tra,(-8|0)\(gp\)} { target rv64 } } } */
/* { dg-final { scan-assembler-not {addi\tgp,gp,-8} { target rv64 } } } */
/* { dg-final { scan-assembler-not {ld\tt0,(-8|0)\(gp\)} { target rv64 } } } */
