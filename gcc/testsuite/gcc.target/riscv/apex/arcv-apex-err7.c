/* { dg-do compile } */

int foo (int);
#pragma intrinsic (foo, FOP, 10000, "XD") /* { dg-error "pragma intrinsic: APEX opcode value '10000' must be an integer constant in the range 0 to 0xff, inclusive" } */
