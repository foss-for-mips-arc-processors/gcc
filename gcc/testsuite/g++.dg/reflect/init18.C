// PR c++/124770
// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

using info = decltype(^^::);

constexpr inline info v{};
static_assert(v == info{});
extern constexpr inline info v2{};
static_assert(v2 == info{});
constexpr inline info v3;
static_assert(v3 == info{});

extern constexpr inline info v4; // { dg-error "not a definition|consteval-only" }
