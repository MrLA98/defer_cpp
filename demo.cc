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

int main() {
  DEFER(test_func, 1, "main");
  //use_defer();
  DEFER(test_func, 5, "main");
  //recur_defer();
  DEFER(test_func, 6, "main");


  return 0;
}
