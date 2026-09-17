/* { dg-do compile } */

/* sub-opcodes reuse.  */
int foo (int,int);
#pragma intrinsic (foo, FOP, 1, "XD")
#pragma intrinsic (foo, FOP, 1, "XD")  /* { dg-error "pragma intrinsic: this specification defines an opcode that duplicates a previous one" } */

#pragma intrinsic (foo, FOP, 2, "XS")
#pragma intrinsic (foo, FOP, 2, "XS")  /* { dg-error "pragma intrinsic: this specification defines an opcode that duplicates a previous one" } */

#pragma intrinsic (foo, FOP, 4, "XC")
#pragma intrinsic (foo, FOP, 4, "XC")  /* { dg-error "pragma intrinsic: this specification defines an opcode that duplicates a previous one" } */

int bar (int);
#pragma intrinsic (bar, BAR, 8, "XI")
#pragma intrinsic (bar, BAR, 8, "XI")  /* { dg-error "pragma intrinsic: this specification defines an opcode that duplicates a previous one" } */