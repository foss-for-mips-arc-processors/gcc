/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fno-omit-frame-pointer -foptimize-sibling-calls -O1" } */

/* In all the following cases, the return address
   should be loaded to the ra register instead of t0 */

int f1 (int);

/* sibcall.  */
int f2 (int a) {
  return f1 (a);
}

/* eh_return.  */
/* only push, pop handled by exception handling */
int f3 (long offset, void *handler) {
  __builtin_eh_return (offset, handler);
}

/* interrupt handlers */
__attribute__((noinline)) __attribute__((interrupt("machine")))
void f5() {
  asm volatile ("":::"ra");
}

__attribute__((noinline)) __attribute__((interrupt("supervisor"))) 
void f6() {
  asm volatile ("":::"ra");
}

/* multi push pop */
__attribute__((optimize("Os", "omit-frame-pointer"), target("arch=+zce")))
int f7 (int a) {
  asm volatile ("":::"ra");
  return a;
}

/* { dg-final { scan-assembler-times {addi\tgp,gp,4} 5 { target rv32 } } } */
/* { dg-final { scan-assembler-times {sw\tra,(-4|0)\(gp\)} 5 { target rv32 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-4} 4 { target rv32 } } } */
/* { dg-final { scan-assembler-times {lw\tra,(-4|0)\(gp\)} 4 { target rv32 } } } */

/* { dg-final { scan-assembler-times {addi\tgp,gp,8} 5 { target rv64 } } } */
/* { dg-final { scan-assembler-times {sd\tra,(-8|0)\(gp\)} 5 { target rv64 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-8} 4 { target rv64 } } } */
/* { dg-final { scan-assembler-times {ld\tra,(-8|0)\(gp\)} 4 { target rv64 } } } */

/* { dg-final { scan-assembler {\mmret} } } */
/* { dg-final { scan-assembler {\msret} } } */
