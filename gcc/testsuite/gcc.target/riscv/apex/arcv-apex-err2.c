/* { dg-do compile } */

int foo (int,int);
#pragma intrinsic (foo,FOP,10,"XU") /* { dg-error "pragma intrinsic: APEX attribute 'XU' is not recognized" } */
