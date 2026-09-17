// PR c++/124991
// { dg-do run { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>

struct X { union { char b; float c; }; };
constexpr auto ctx = std::meta::access_context::unchecked ();

int
main ()
{
  if (typeid (typename [: parent_of (^^X::b) :])
      != typeid (typename [: members_of (^^X, ctx)[0] :]))
    __builtin_abort ();
}
