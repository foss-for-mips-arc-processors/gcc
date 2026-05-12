/* { dg-do compile } */

int foo (int);
#pragma intrinsic (foo, "%FOP", 10, "XD")  /* { dg-error "pragma intrinsic: APEX name '%FOP' is not lexically valid" } */
