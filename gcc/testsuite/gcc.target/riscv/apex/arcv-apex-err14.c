/* { dg-do compile } */

void foo (int, int);
#pragma intrinsic (foo, FOP, 10, "XC") /* { dg-error "pragma intrinsic: APEX function 'foo' must return the same type as the first parameter for the 'XC' format class" } */