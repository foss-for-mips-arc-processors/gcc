// PR c++/125184
// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>

void
foo ()
{
  using std::meta::info;
}
