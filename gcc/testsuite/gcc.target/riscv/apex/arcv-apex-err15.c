/* { dg-do compile } */

int foo (int);
int bar0 ();
int bar3 (int,int,int);

#pragma intrinsic (foo, FOP, 10, "XS") /* { dg-error "pragma intrinsic: APEX function 'foo' must have 2 scalar parameter\\(s\\) for the 'XS' format class" } */
#pragma intrinsic (bar0, bar0, 11, "XS") /* { dg-error "pragma intrinsic: APEX function 'bar0' must have 2 scalar parameter\\(s\\) for the 'XS' format class" } */
#pragma intrinsic (bar3, bar3, 12, "XS") /* { dg-warning "pragma intrinsic: Associated function can have no more than 2 parameters" } */
