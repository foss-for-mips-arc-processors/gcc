// { dg-do compile { target c++20 } }

// Bug 121919 ranges::sample assumes a uniform_random_bit_generator
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
  int i2[2]{ 1, 2 };
  __gnu_test::test_random_access_range from(i2);
  int i1[1];
  __gnu_test::test_random_access_range to(i1);
  std::ranges::sample(from, std::ranges::begin(to), 1, G{});
  std::ranges::sample(std::ranges::begin(from), std::ranges::end(to),
		      std::ranges::begin(to), 1, G{});
}
