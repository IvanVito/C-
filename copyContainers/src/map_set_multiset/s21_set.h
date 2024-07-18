#ifndef CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_SET_H_
#define CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_SET_H_

#include "../vector_array/s21_vector.h"
#include "s21_base_container.h"
#include "s21_red_black_tree.h"

namespace s21 {

template <typename KeyType>
class IteratorSet
    : public IteratorBase<KeyType, KeyType, Node<KeyType, KeyType> *> {
 public:
  using IteratorBase<KeyType, KeyType, Node<KeyType, KeyType> *>::IteratorBase;

  KeyType &operator*() { return this->currentNode_->key_; }
  KeyType *operator->() { return &(this->currentNode_->key_); }
};

template <typename KeyType>
class ConstIteratorSet
    : public IteratorBase<KeyType, KeyType, const Node<KeyType, KeyType> *> {
 public:
  using IteratorBase<KeyType, KeyType,
                     const Node<KeyType, KeyType> *>::IteratorBase;

  const KeyType &operator*() const { return this->currentNode_->key_; }
  const KeyType *operator->() const { return &(this->currentNode_->key_); }
};

template <typename KeyType>
class set : public BaseContainer<KeyType, KeyType, IteratorSet<KeyType>,
                                 ConstIteratorSet<KeyType>> {
 public:
  using key_type = KeyType;
  using value_type = KeyType;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = IteratorSet<key_type>;
  using const_iterator = ConstIteratorSet<key_type>;
  using size_type = size_t;
  using allocator = std::allocator<Node<key_type, value_type>>;

  using BaseContainer<key_type, value_type, iterator,
                      const_iterator>::BaseContainer;

  template <typename SetType>
  bool operator==(const SetType s) const {
    bool equal = true;
    auto itLeftSet = this->begin();
    auto itRightSet = s.begin();
    if (this->size() == s.size()) {
      while ((itLeftSet != this->end()) && (equal == true)) {
        if ((*itLeftSet) != (*itRightSet)) equal = false;
        ++itLeftSet;
        ++itRightSet;
      }
    } else {
      equal = false;
    }
    return equal;
  }

  void merge(set &other) {
    if (this != &other) {
      auto it = other.begin();
      while (it != other.end()) {
        auto currentKey = *it;
        ++it;
        if (this->tree_.search(currentKey) == this->tree_.getNullNode()) {
          this->insert(currentKey);
          other.tree_.remove(currentKey);
        }
      }
    }
  }

  iterator erase(iterator pos) {
    key_type key = *pos;
    ++pos;
    this->tree_.remove(key);
    return pos;
  }

  void swap(set &other) noexcept { this->tree_.swap(other.tree_); }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    if constexpr (sizeof...(args) > 0) {
      s21::vector<std::pair<iterator, bool>> results;
      results.reserve(sizeof...(args));
      (results.push_back(this->insert(args)), ...);
      return results;
    } else {
      throw std::invalid_argument(
          "Количество элементов должно быть больше нуля");
    }
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_SET_H_
