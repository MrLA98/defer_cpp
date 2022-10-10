# defer_cpp
> A implementation of "defer"(in go language) in cpp version 

In go language，we can easily use keyword defer to call a function later -- after the scope ends.

For instance：
```go
package main
import (
    "fmt"
)
func main() {
  fmt.Println("defer begin")
  // put some action in system stack
  defer fmt.Println(1)
  defer fmt.Println(2)
  // First in and last out
  defer fmt.Println(3)
  fmt.Println("defer end")
}

// # output like:
// defer begin
// defer end
// 3
// 2
// 1
```

As a wish, I designed the defer macro in cpp version, which only have one file with 100 lines of codes.

For instance:
```cpp
#include <iostream>
#include "defer.hpp"

int main() {
  std::cout << "defer begin" << std::endl;
  // put some action in system stack
  DEFER([]() { std::cout << 1 << std::endl; });
  DEFER([]() { std::cout << 2 << std::endl; });
  // First in and last out
  DEFER([]() { std::cout << 3 << std::endl; });
  std::cout << "defer end" << std::endl;
}

// # output like:
// defer begin
// defer end
// 3
// 2
// 1
```

Play Happily!