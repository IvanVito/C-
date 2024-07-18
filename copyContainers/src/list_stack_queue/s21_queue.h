#ifndef CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_QUEUE_H_
#define CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 private:
  Container node;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  queue() : node{} {}

  queue(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push(*it);
    }
  }

  queue(const queue &q) : node(q.node) {}

  queue(queue &&q) : node(std::move(q.node)) {}

  ~queue() { node.clear(); }

  queue &operator=(queue &&q) {
    if (this != &q) {
      node = (std::move(q.node));
    }
    return *this;
  }

  const_reference front() { return node.front(); }

  const_reference back() { return node.back(); }

  bool empty() { return node.empty(); }

  size_type size() { return node.size(); }

  void push(const_reference value) { node.push_back(value); }

  void pop() {
    if (!empty()) node.pop_front();
  }

  void swap(queue &other) { std::swap(this->node, other.node); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &item : {args...}) push(item);
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_QUEUE_H_