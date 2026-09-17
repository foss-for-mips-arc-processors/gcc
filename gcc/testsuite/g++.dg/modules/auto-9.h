namespace ranges {
struct _Begin {
  template <typename _Tp> auto operator()(_Tp __t) { return __t.begin(); }
};
struct _Data {
  template <typename _Tp> auto operator()(_Tp __t) { return __t.data(); }
};
inline _Begin begin;
inline _Data data;
struct subrange;
template <typename _Tp> struct view_interface {
  subrange _M_derived();
  auto data() noexcept(noexcept(begin(_M_derived()))) { return begin(_M_derived()); }
};
} // namespace ranges
struct basic_string_view {
  basic_string_view(const char *);
  template <typename _Range>
  basic_string_view(_Range __r) : _M_str(ranges::data(__r)) {}
  char *_M_str;
} typedef string_view;
namespace ranges {
struct subrange : view_interface<int> {
  char *begin();
};
struct split_view {
  struct _Iterator {
    subrange operator*();
  };
  template <typename _Range> split_view(_Range, _Range);
  _Iterator begin();
};
namespace views {
inline
struct _Split {
  template <typename _Range, typename _Pattern>
  auto operator()(_Range, _Pattern) {
    return split_view(0, 0);
  }
} split;
} // namespace views
} // namespace ranges
