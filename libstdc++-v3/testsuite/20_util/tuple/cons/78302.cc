// { dg-do compile { target c++20 } }

// Bug 78302 is_move_constructible_v<tuple<nonmovable>> should be false
// LWG 2899. is_(nothrow_)move_constructible and tuple, optional and unique_ptr

#include <tuple>
#include <type_traits>

struct NotMovable { NotMovable(NotMovable&&) = delete; };
static_assert(!std::is_move_constructible_v<std::tuple<NotMovable>>);
static_assert(!std::is_move_constructible_v<std::tuple<int, NotMovable>>);
static_assert(!std::is_move_constructible_v<std::tuple<int&, NotMovable>>);
static_assert(!std::is_move_constructible_v<std::tuple<int&&, NotMovable>>);
static_assert(std::is_nothrow_move_constructible_v<std::tuple<int>>);
static_assert(std::is_nothrow_move_constructible_v<std::tuple<int&>>);
static_assert(std::is_nothrow_move_constructible_v<std::tuple<int&&>>);
static_assert(std::is_nothrow_move_constructible_v<std::tuple<int&&, int&>>);
