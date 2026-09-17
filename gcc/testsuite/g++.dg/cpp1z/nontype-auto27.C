// PR c++/115181
// { dg-do compile { target c++17 } }

template <auto> struct S {};
__extension__ S<(int[]){1}> x;  // { dg-error "not a valid template argument" }
