/* Check that post-reload thunk generation does not try to create new pseudos. */
/* { dg-do compile } */
/* { dg-options "-O -mcmodel=large" } */

#include <cstddef>

#define NO_INLINE __attribute__((noinline))

class A {
  virtual void foo() = 0;
};
class B {
  virtual void bar() = 0;
};
class C : public A, public B {
  NO_INLINE void foo() {}
  NO_INLINE void bar() {}
};

C c;

int main() {
}

/* { dg-final { scan-assembler "movhl_s\\sr13,\@\.LTHUNK0"} } */
/* { dg-final { scan-assembler "j\\t\\\[r13\\\]"} } */
