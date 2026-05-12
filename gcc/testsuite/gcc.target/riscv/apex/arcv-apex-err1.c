/* { dg-do compile } */

int foo (int,int);
#pragma intrinsic (foo,FOP,10,Key=>"bar") /* { dg-error "pragma intrinsic: APEX attribute 'Key' is not recognized" } */
