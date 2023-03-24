#pragma once
#include <cstdint>
#include <functional>
#include <list>
#include <unordered_map>

#define ADDRESS (uint64_t)(__builtin_return_address(0))
#define CONCACT_(x, y) x##y
#define CONCACT(x, y) CONCACT_(x, y)
#define PREFIX_ d_
#define PREFIX CONCACT(PREFIX_, __COUNTER__)
#define DEFER(...) defer::Defer PREFIX(ADDRESS, __VA_ARGS__)
// defer::Defer d1((uint64_t)(__builtin_return_address(0)), func, args...);

namespace defer {

using std::function;
using std::unordered_map;

class Defer {
private:
  // node with defer action function
  struct Node {
    // constructors
    Node(function<void()> &&f) : func(std::forward<function<void()>>(f)) {}
    Node() : func(nullptr), next(nullptr) {}

    function<void()> func; // store a defer action function
    Node *next;            // next node

    // destructor run the defer action function
    ~Node() {
      if (func) {
        func();
      }
    }
  };
  // head node helps manage the list-stack
  Node *head_;
  uint64_t addr_;
  static unordered_map<uint64_t, Node *> addr_map_;

  // add node between head and head's next
  // so that mocks a stack
  void add_func(Node *head, Node *new_node) {
    // add the new node between head and head's next
    new_node->next = head->next;
    head->next = new_node;
  }

  void del_addr() {
    if (!addr_map_.count(addr_)) {
      return;
    }
    addr_map_.erase(addr_);
  }

public:
  // constructors
  template <class Func, class... Args>
  explicit Defer(uint64_t addr, Func &&f, Args &&...args)
      : addr_(0), head_(nullptr) {
    // new function area, regist
    if (!addr_map_.count(addr) || !addr_map_[addr]) {
      head_ = new Node();
      addr_ = addr;
      addr_map_[addr_] = head_;
    }
    // create new node
    function<void()> func =
        std::bind(std::forward<Func>(f), std::forward<Args>(args)...);
    Node *new_node = new Node(std::move(func));
    // put the function node into the list-stack
    add_func(addr_map_[addr], new_node);
  };

  Defer(const Defer &another) = delete;
  Defer &operator=(const Defer &rhs) = delete;

  // destructor
  ~Defer() {
    auto node = head_;
    // from begin to the end -- running as a stack
    while (node) {
      auto tmp = node;
      node = node->next;
      delete tmp;
    }
    // remove from the map
    if (addr_ != 0) {
      del_addr();
    }
  }
};

// static variables
unordered_map<uint64_t, Defer::Node *> Defer::addr_map_;

} // namespace defer
