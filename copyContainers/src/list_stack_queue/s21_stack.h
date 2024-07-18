#ifndef CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_STACK_H_
#define CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_STACK_H_

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class stack {
 private:
  Container node;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack() : node{} {}

  stack(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push(*it);
    }
  }

  stack(const stack &s) : node(s.node) {}

  stack(stack &&s) : node(std::move(s.node)) {}

  ~stack() { node.clear(); }

  stack &operator=(stack &&s) {
    if (this != &s) {
      node = (std::move(s.node));
    }
    return *this;
  }

  const_reference top() { return node.back(); }

  bool empty() { return node.empty(); }

  size_type size() { return node.size(); }

  void push(const_reference value) { node.push_back(value); }

  void pop() { node.pop_back(); }

  void swap(stack &other) { std::swap(this->node, other.node); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (const auto &item : {args...}) push(item);
  }
};
}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_STACK_H_