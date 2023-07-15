#pragma once
#include <functional>

#define CONCACT_(x, y) x##y
#define CONCACT(x, y) CONCACT_(x, y)
#define PREFIX CONCACT(d_, __LINE__)
#define DEFER(...) defer::Defer PREFIX(__VA_ARGS__)

namespace defer {
struct Defer {
  // constructors
  template <class Func, class... Args>
  Defer(Func &&f, Args &&...args)
      : func(std::bind(std::forward<Func>(f), std::forward<Args>(args)...)) {}
  Defer() : func(nullptr) {}

  std::function<void()> func;  // store a defer action function

  // destructor run the defer action function
  ~Defer() {
    if (func) {
      func();
    }
  }
};
}  // namespace defer
