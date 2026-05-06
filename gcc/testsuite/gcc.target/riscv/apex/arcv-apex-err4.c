/* { dg-do compile } */

int foo (int);
#pragma intrinsic (foo,FOP,10,"XI","XC")  /* { dg-error "pragma intrinsic: APEX formats 'XI' and 'XC' are not compatible" } */
