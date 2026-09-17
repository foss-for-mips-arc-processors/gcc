// PR c++/125206
// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>
#include <type_traits>

template<auto...> struct mp_list_v
{
};

template<class...> struct mp_list
{
};

template<auto V> using mp_value = std::integral_constant<decltype(V), V>;

template<class L, template<class...> class B> struct mp_rename_impl;

template<template<class...> class L, class... T, template<class...> class B> struct mp_rename_impl<L<T...>, B>
{
    using type = B<T...>;
};

template<template<auto...> class L, auto... A, template<class...> class B> struct mp_rename_impl<L<A...>, B>
{
    using type = B<mp_value<A>...>;
};

template<class L, template<class...> class B> using mp_rename = typename mp_rename_impl<L, B>::type;

class X1
{
};

class Z: public X1
{
};

int main()
{
    constexpr auto all = std::meta::access_context::unchecked();
    constexpr auto L1 = ^^mp_list_v< bases_of(^^Z, all)[0] >;
    using L2 = mp_rename<typename [: L1 :], mp_list>;
}
