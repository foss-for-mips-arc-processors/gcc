/* Execution test for multiple virtual function inheritance.  */
/* { dg-do run } */
/* { dg-options "-O -mcmodel=large -lstdc++ -lm" } */

#include <cstddef>
#include <iostream>

#define NO_INLINE __attribute__((noinline))

class A {
  virtual void foo() = 0;
};
class B {
  virtual void bar() = 0;
};
class C : public A, public B {
public:
  NO_INLINE void foo() override {
    std::cout << "foo";
  }
  NO_INLINE void bar() override {
    std::cout << "bar"; 
  }
};

int main() {
  C c;
  c.foo();
  c.bar();
}

/* { dg-output "foobar" } */
