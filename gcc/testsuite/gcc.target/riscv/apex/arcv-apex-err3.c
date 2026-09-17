/* { dg-do compile } */

int foo (int,int);
#pragma intrinsic (foo,FOP,10,"XC",opcode=>)  /* { dg-error "pragma intrinsic: APEX attribute 'opcode' is redundant" } */
