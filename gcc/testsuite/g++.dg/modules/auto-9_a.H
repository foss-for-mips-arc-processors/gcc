// PR c++/125115
// { dg-do compile { target c++17 } }
// { dg-additional-options "-fmodule-header" }

#include "auto-9.h"

inline void foo() {
  auto x = string_view(*ranges::views::split(string_view("1.2"), '.').begin());
}
