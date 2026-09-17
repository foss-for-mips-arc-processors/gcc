// PR c++/125096
// { dg-do compile { target c++26 } }
// { dg-additional-options "-freflection" }

#include <meta>
#include <vector>

namespace ctp {
    template <class T> struct Reflect;

    namespace impl {
        template <class T> using custom_target = Reflect<T>::target_type;
    }

    template <class T>
    using target = [: is_scalar_type(^^T) ? ^^T : substitute(^^impl::custom_target, {^^T}) :];

    template <class T>
    struct Reflect<std::vector<T>> {
        using underlying = target<T> const;
        using target_type = std::span<const target<T>>;
    };
}

static_assert(dealias(^^ctp::target<int>) == ^^int);
static_assert(dealias(^^ctp::target<std::vector<int>>) == ^^std::span<int const>);
static_assert(dealias(^^ctp::Reflect<std::vector<int>>::underlying) == ^^int const);
static_assert(dealias(^^ctp::Reflect<std::vector<int>>::target_type) == ^^std::span<int const>);
