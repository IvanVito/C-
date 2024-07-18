#ifndef CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_CONST_ITERATOR_LIST_H_
#define CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_S21_CONST_ITERATOR_LIST_H_

#include "s21_iterator_list.h"
#include "s21_list.h"

namespace s21 {

template <typename T>
class list;
template <typename T>
class ListIteratos;

template <typename T>
class ListConstIterator : public ListIterator<T> {
 private:
  friend class list<T>;

  const typename list<T>::node<T> *mptr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  ListConstIterator(const typename list<T>::node<T> *mptr = nullptr)
      : ListIterator<T>(mptr), mptr(mptr) {}

  reference operator*() const { return mptr->data; }

  ListConstIterator operator->() { return &(mptr->data); }

  ListConstIterator &operator++() {
    mptr = mptr->pNext;
    return *this;
  }

  ListConstIterator &operator--() {
    mptr = mptr->pPrev;
    return *this;
  }

  ListConstIterator operator--(int) {
    ListConstIterator temp = *this;
    mptr = mptr->pPrev;
    return temp;
  }

  ListConstIterator operator++(int) {
    ListConstIterator temp = *this;
    mptr = mptr->pNext;
    return temp;
  }

  bool operator!=(const ListConstIterator &other) const {
    return mptr != other.mptr;
  }

  bool operator==(const ListConstIterator &other) const {
    return mptr == other.mptr;
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_LIST_STACK_QUEUE_CONST_ITERATOR_LIST_H_