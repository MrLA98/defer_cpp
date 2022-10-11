#include <iostream>
#include <string>

#include "defer.hpp"

using namespace std;

void test_func(int t, string name) {
  cout << t << "-test_func-" << name << endl;
}

void use_defer() { DEFER(test_func, 2, "use_defer"); }

void recur_defer() {
  DEFER(test_func, 3, "recur_defer");
  DEFER(test_func, 4, "recur_defer");
  use_defer();
}

class Obj {
 private:
  int count_;
  double val_;

 public:
  Obj() : count_(10), val_(1){};
  void operator()(double val) {
    val_ = val;
    cout << "function obj-" << val_ / count_ << endl;
    ++count_;
  }
};

int main() {
  DEFER(test_func, 1, "main");
  use_defer();
  DEFER(test_func, 5, "main");
  recur_defer();
  DEFER([]() { cout << "lambda" << endl; });
  DEFER(Obj(), 22);

  return 0;
}
