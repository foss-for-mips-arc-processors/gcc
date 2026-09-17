// PR c++/124957
// { dg-do compile { target c++17 } }
// { dg-additional-options "-fmodules" }

export module mod; // { dg-module-cmi "mod" }
export import :partition;

// x gets mangled in this TU => cxx11 abi_tag propagated to x
