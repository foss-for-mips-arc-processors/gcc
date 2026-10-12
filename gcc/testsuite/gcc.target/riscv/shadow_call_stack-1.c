/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fexceptions" } */

int i;

/* { dg-error "'-fsanitize=shadow-call-stack' requires '-fno-exceptions'" "" { target "riscv*-*-*" } 0 } */
