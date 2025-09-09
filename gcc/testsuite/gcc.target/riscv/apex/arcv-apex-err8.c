/* { dg-do compile } */

int foo (int, int);
#pragma intrinsic (foo, FOP, 10, "XI")  /* { dg-error "pragma intrinsic: APEX function 'foo' must have 1 scalar parameter\\(s\\) for the 'XI' format class" } */