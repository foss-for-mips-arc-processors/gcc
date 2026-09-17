// { dg-do compile { target c++20 } }

// Bug 121919 ranges::shuffle assumes a uniform_random_bit_generator
// provides result_type

#include <algorithm>
#include <testsuite_iterators.h>

struct G
{
  constexpr static unsigned min() { return 0;  }
  constexpr static unsigned max() { return 10; }
  unsigned operator()() const;
};

static_assert(std::uniform_random_bit_generator<G>);

void
test_pr121919()
{
  int arr[2]{ 1, 2 };
  __gnu_test::test_random_access_range r(arr);
  std::ranges::shuffle(r, G{});
  std::ranges::shuffle(std::ranges::begin(r), std::ranges::end(r), G{});
}
