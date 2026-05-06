/* { dg-do compile } */

int foo (int);
#pragma intrinsic (foo)
/* { dg-error "pragma intrinsic: APEX attribute 'name' is missing" "" { target *-*-* } 4 } */
/* { dg-error "pragma intrinsic: APEX attribute 'opcode' is missing" "" { target *-*-* } 4 } */
