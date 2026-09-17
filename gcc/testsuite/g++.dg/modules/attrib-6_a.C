// PR c++/124957
// { dg-do compile { target c++17 } }
// { dg-additional-options "-fmodules" }

export module mod:partition;

int dummy;
struct [[gnu::abi_tag("cxx11")]] A { int m; };
export inline int A::*x = &A::m;
// x does not get mangled in this TU => cxx11 abi_tag not propagated to x
