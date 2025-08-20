/* { dg-do compile } */
/* { dg-options " -march=rv32imac -mabi=ilp32 -mno-compress" } */

int a, b, c;
int foo(void) { return a + b + c; }

/* { dg-final { scan-assembler "\.attribute arch, \"rv32i2p1_m2p0_a2p1_zaamo1p0_zalrsc1p0\"" } } */
