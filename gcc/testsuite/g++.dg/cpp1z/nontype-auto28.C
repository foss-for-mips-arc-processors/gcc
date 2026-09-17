// PR c++/125043
// { dg-do compile { target c++17 } }

template <auto V>
struct wrapper {
    static constexpr const auto& value = V;
};

template <int const& I>
auto f() -> void;

auto main() -> int {
    f<wrapper<42>::value>();  // { dg-error "no matching function|not a valid template argument" }
}
