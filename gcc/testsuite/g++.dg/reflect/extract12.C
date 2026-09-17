// PR c++/125111
// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>

using A = void ();
extern A &a;
constexpr auto b = ^^a;
constexpr auto c = std::meta::extract <A &> (b);	// { dg-error "uncaught exception of type 'std::meta::exception'; 'what\\\(\\\)': 'value cannot be extracted'" }
using B = int [];
extern B &d;
constexpr auto e = ^^d;
constexpr auto f = std::meta::extract <B &> (e);	// { dg-error "uncaught exception of type 'std::meta::exception'; 'what\\\(\\\)': 'value cannot be extracted'" }
