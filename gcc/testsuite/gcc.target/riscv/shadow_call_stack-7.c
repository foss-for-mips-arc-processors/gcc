/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -Os -fomit-frame-pointer" } */
/* { dg-additional-options "-march=rv32imac_zcmp -mabi=ilp32" { target rv32 } } */
/* { dg-additional-options "-march=rv64imac_zcmp -mabi=lp64" { target rv64 } } */

/* multi push pop */
/* zcmp conflicts with zcd, so this needs an arch without the D extension.
   The return address should be loaded to the ra register instead of t0.  */
int f1 (int a) {
  asm volatile ("":::"ra");
  return a;
}

/* { dg-final { scan-assembler-times {cm\.push} 1 } } */
/* { dg-final { scan-assembler-times {cm\.pop} 1 } } */

/* { dg-final { scan-assembler-times {addi\tgp,gp,4} 1 { target rv32 } } } */
/* { dg-final { scan-assembler-times {sw\tra,(-4|0)\(gp\)} 1 { target rv32 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-4} 1 { target rv32 } } } */
/* { dg-final { scan-assembler-times {lw\tra,(-4|0)\(gp\)} 1 { target rv32 } } } */

/* { dg-final { scan-assembler-times {addi\tgp,gp,8} 1 { target rv64 } } } */
/* { dg-final { scan-assembler-times {sd\tra,(-8|0)\(gp\)} 1 { target rv64 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-8} 1 { target rv64 } } } */
/* { dg-final { scan-assembler-times {ld\tra,(-8|0)\(gp\)} 1 { target rv64 } } } */
