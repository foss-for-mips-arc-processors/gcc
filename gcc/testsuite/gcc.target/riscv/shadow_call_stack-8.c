/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -funwind-tables -fomit-frame-pointer" } */

int g (int);

int f1 (int a) {
  return g (a) + 1;
}

int f2 (int a) {
  return g (a) + 2;
}

/* { dg-final { scan-assembler-times {\.cfi_escape 0x16,0x3,0x2,0x73,0x7c} 2 { target rv32 } } } */
/* { dg-final { scan-assembler-times {\.cfi_escape 0x16,0x3,0x2,0x73,0x78} 2 { target rv64 } } } */

/* { dg-final { scan-assembler-times {\.cfi_restore 3} 2 } } */
