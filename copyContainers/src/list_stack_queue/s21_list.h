#ifndef CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_LIST_H_
#define CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_LIST_H_

#include <algorithm>
#include <iostream>
#include <limits>

#include "s21_const_iterator_list.h"
#include "s21_iterator_list.h"

namespace s21 {

template <typename T>
class ListIterator;
template <typename T>
class ListConstIterator;

template <typename T>
class list {
 private:
  template <typename T2>
  class node {
   public:
    node *pNext;
    node *pPrev;
    T2 data;
    node(T2 data = T2(), node *pNext = nullptr, node *pPrev = nullptr) {
      this->data = data;
      this->pNext = pNext;
      this->pPrev = pPrev;
    }
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

  friend class ListIterator<T>;
  friend class ListConstIterator<T>;

  node<T> endNode;

  size_type sizenode;
  node<T> *head;
  node<T> *tail;

  list() {
    head = &endNode;
    tail = &endNode;
    endNode.pNext = &endNode;
    endNode.pPrev = &endNode;
    sizenode = 0;
  }

  list(size_type n) {
    sizenode = 0;
    head = &endNode;
    tail = &endNode;
    for (size_type i = 0; i < n; ++i) {
      push_back(0);
    }
  }

  list(std::initializer_list<value_type> const &items) {
    sizenode = 0;
    head = &endNode;
    tail = &endNode;
    for (auto const &item : items) {
      push_back(item);
    }
  }

  list(const list &l) {
    head = &endNode;
    tail = &endNode;
    endNode.pNext = &endNode;
    endNode.pPrev = &endNode;
    sizenode = 0;
    node<T> *current = l.head;
    while (current != &l.endNode) {
      push_back(current->data);
      current = current->pNext;
    }
  }

  list(list &&l) {
    head = l.head;
    tail = l.tail;
    endNode.pNext = &endNode;
    endNode.pPrev = &endNode;

    if (head) {
      head->pPrev = &endNode;
    }
    if (tail) {
      tail->pNext = &endNode;
    }

    sizenode = l.sizenode;

    l.head = l.tail = &l.endNode;
    l.endNode.pNext = l.endNode.pPrev = &l.endNode;
    l.sizenode = 0;
  }

  ~list() { clear(); }

  list &operator=(list &&l) {
    if (this != &l) {
      clear();
      head = &endNode;
      tail = &endNode;
      endNode.pNext = &endNode;
      endNode.pPrev = &endNode;
      sizenode = 0;
      node<T> *current = l.head;
      while (current != &l.endNode) {
        push_back(current->data);
        current = current->pNext;
      }
    }
    return *this;
  }

  const_reference front() { return head->data; }
  const_reference back() { return tail->data; }

  iterator begin() {
    iterator it(head);
    return it;
  }
  iterator end() {
    iterator it(&endNode);
    return it;
  }

  const_iterator cbegin() {
    const_iterator it(head);
    return it;
  }

  reference operator*() { return head->data; }

  bool empty() { return sizenode == 0; }

  size_type size() { return sizenode; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(size_type) / 2;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos.mptr == nullptr) {
      throw std::invalid_argument("Invalid iterator");
    }
    if (pos == this->begin()) {
      this->push_front(value);
      return this->begin();
    }
    if (pos == this->end()) {
      this->push_back(value);
      return --this->end();
    }
    node<T> *curr = pos.mptr;
    node<T> *newNode = new node<T>(value, curr, curr->pPrev);
    curr->pPrev->pNext = newNode;
    curr->pPrev = newNode;
    ++sizenode;
    return iterator(newNode);
  }

  void clear() {
    node<T> *curr = head;
    while (curr != &endNode) {
      node<T> *next = curr->pNext;
      delete curr;
      curr = next;
    }
    sizenode = 0;
    head = &endNode;
    tail = &endNode;
    endNode.pNext = &endNode;
    endNode.pPrev = &endNode;
  }

  void erase(iterator pos) {
    if (pos == this->end() || pos.mptr == nullptr)
      throw std::invalid_argument("Invalid iterator");

    node<T> *toDelete = pos.mptr;
    node<T> *prev = toDelete->pPrev;
    node<T> *next = toDelete->pNext;

    if (prev == &endNode)
      head = next;
    else
      prev->pNext = next;

    if (next == &endNode) {
      tail = prev;
      endNode.pPrev = tail;
    } else
      next->pPrev = prev;

    delete toDelete;
    --sizenode;
  }

  void push_back(const_reference value) {
    node<T> *newNode = new node<T>(value);
    newNode->pNext = &endNode;
    newNode->pPrev = tail;
    tail->pNext = newNode;
    tail = newNode;
    endNode.pPrev = tail;
    if (sizenode == 0) {
      head = newNode;
    }
    ++sizenode;
  }
  void pop_back() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    auto it = --(end());
    this->erase(it);
  }
  void push_front(const_reference value) {
    node<T> *newNode = new node<T>(value);
    newNode->pNext = head;
    newNode->pPrev = &endNode;
    head->pPrev = newNode;
    head = newNode;
    endNode.pNext = head;
    if (sizenode == 0) {
      tail = newNode;
    }
    ++sizenode;
  }
  void pop_front() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    auto it = begin();
    this->erase(it);
  }
  void swap(list &other) {
    std::swap(this->sizenode, other.sizenode);
    std::swap(this->head, other.head);
    std::swap(this->tail, other.tail);
    std::swap(this->endNode.pPrev, other.endNode.pPrev);
    std::swap(this->endNode.pNext, other.endNode.pNext);

    this->endNode.pNext->pPrev = &this->endNode;
    this->endNode.pPrev->pNext = &this->endNode;
    other.endNode.pNext->pPrev = &other.endNode;
    other.endNode.pPrev->pNext = &other.endNode;
  }
  void merge(list &other) {
    this->tail->pNext = other.head;
    other.head->pPrev = this->tail;
    this->tail = other.tail;
    this->endNode.pPrev = this->tail;
    this->tail->pNext = &this->endNode;

    sort();

    sizenode += other.sizenode;

    other.head = other.tail = &other.endNode;
    other.endNode.pNext = other.endNode.pPrev = &other.endNode;
    other.sizenode = 0;
  }
  void splice(const_iterator pos, list &other) {
    if (!other.empty()) {
      for (iterator it = other.begin(); it != other.end(); ++it) {
        insert(pos, *it);
      }
    }
    other.clear();
  }
  void reverse() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    auto start = begin();
    auto end_ = --end();
    while (start != tail) {
      std::swap(*end_, *start);
      ++start;
      end_--;
    }
  }
  void unique() {
    auto curr = begin();
    auto next = curr;
    ++next;
    while (next != end()) {
      if (*curr == *next) {
        erase(next);
        next = curr;
        ++next;
      } else {
        ++curr;
        ++next;
      }
    }
  }
  void sort() {
    auto curr = begin();
    while (curr != end()) {
      auto next = curr;
      ++next;
      while (next != end()) {
        if (*curr > *next) {
          std::swap(*next, *curr);
        }
        ++next;
      }
      ++curr;
    }
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &item : {args...}) {
      push_back(item);
    }
  }
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (const auto &item : {args...}) {
      push_front(item);
    }
  }
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    for (const auto &item : {args...}) {
      insert(pos, item);
    }
    return pos;
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_LIST_H_
