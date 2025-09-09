/* { dg-do compile } */

int foo (int, int);
int bar (int, int);

#pragma intrinsic (foo, "FOO", 10, XD, XS)
#pragma intrinsic (bar, "BAR", 10, XS) /* { dg-error "pragma intrinsic: this specification defines an opcode that duplicates a previous one" } */