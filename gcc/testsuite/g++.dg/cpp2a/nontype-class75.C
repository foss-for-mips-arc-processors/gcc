// PR c++/124979
// { dg-do compile { target c++20 } }

template<auto X, class = decltype(X)>
struct cw;

struct base {

    template <class L>
    friend constexpr auto operator &(L) noexcept
        -> cw<(&L::value)> {
        return {};
    }
};

template<auto X, class>
struct cw : base {
    static constexpr const auto& value = X;
};
    template <auto L, auto R>
    constexpr auto operator ->*(cw<L>, cw<R>) noexcept
        -> cw<L ->* R> {
        return {};
    }

struct Divide { int value; };
auto cvalue = cw<&Divide::value>{};
constexpr const Divide &t = {42};
auto co = cw<Divide{42}>{};
auto co1 = cw<&t>{};  // { dg-error "not a valid template argument|is invalid" }

template<class> class TD;
template<int t> class TD<cw<t>>{};
TD<decltype((co1)->*cvalue)> _;	  // { dg-error "is invalid" }
