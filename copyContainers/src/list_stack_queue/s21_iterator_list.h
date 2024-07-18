#ifndef CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_ITERATOR_LIST_H_
#define CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_ITERATOR_LIST_H_

#include "s21_list.h"

namespace s21 {

template <typename T>
class list;
template <typename T>
class ListIterator {
  friend class list<T>;

 private:
  typename list<T>::node<T> *mptr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  ListIterator(const typename list<T>::node<T> *mptr = nullptr) {
    this->mptr = const_cast<typename list<T>::node<T> *>(mptr);
  }

  reference operator*() { return mptr->data; }

  // const node<T>* get_mptr() const { return mptr; }

  ListIterator operator->() { return &(mptr->data); }

  ListIterator &operator++() {
    mptr = mptr->pNext;
    return *this;
  }

  ListIterator &operator--() {
    mptr = mptr->pPrev;
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator temp = *this;
    mptr = mptr->pPrev;
    return temp;
  }

  ListIterator &operator=(size_t pos) {
    for (size_t i = 0; i < pos; i++) {
      mptr = mptr->pNext;
    }
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    mptr = mptr->pNext;
    return temp;
  }

  bool operator!=(const ListIterator &other) const {
    return mptr != other.mptr;
  }

  bool operator==(const ListIterator &other) const {
    return mptr == other.mptr;
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_ITERATOR_LIST_H_