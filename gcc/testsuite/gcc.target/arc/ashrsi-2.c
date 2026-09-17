/* { dg-do compile } */
/* { dg-skip-if "avoid conflicts with -mcpu options" { *-*-* } { "-mcpu=*" } { "-mcpu=em" } } */
/* { dg-options "-O2 -mcpu=em" } */

int foo(int x) { return x >> 1; }

/* { dg-final { scan-assembler-times "asr_s\\s+r0,r0" 1 } } */
/* { dg-final { scan-assembler "j_s\.d" } } */
