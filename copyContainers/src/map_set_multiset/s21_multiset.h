#ifndef CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_MULTISET_H_
#define CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_MULTISET_H_

#include "s21_red_black_tree.h"
#include "s21_set.h"

namespace s21 {

template <typename KeyType>
class multiset : public set<KeyType> {
 public:
  using key_type = KeyType;
  using value_type = KeyType;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = IteratorSet<key_type>;
  using const_iterator = ConstIteratorSet<key_type>;
  using size_type = size_t;
  using allocator = std::allocator<Node<key_type, value_type>>;

  using set<key_type>::set;

  multiset() : set<key_type>(true) {}

  multiset(std::initializer_list<value_type> const &items)
      : set<key_type>(items, true) {}

  iterator insert(const value_type &value) {
    this->tree_.insert(value, value);
    iterator it = this->find(value);
    return it;
  }

  size_type count(const key_type &key) {
    size_type count = 0;
    auto it = this->find(key);
    while (it != this->end() && *it == key) {
      ++count;
      ++it;
    }
    return count;
  }

  iterator lower_bound(const key_type &key) {
    return iterator(this->tree_.lowerBound(key), this->tree_.getRoot(),
                    this->tree_.getNullNode());
  }

  iterator upper_bound(const key_type &key) {
    auto it = lower_bound(key);
    while (it != this->end() && *it == key) ++it;
    return it;
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return {lower_bound(key), upper_bound(key)};
  }

  void merge(multiset &other) {
    if (this != &other) {
      auto it = other.begin();
      while (it != other.end()) {
        auto currentKey = *it;
        ++it;
        this->insert(currentKey);
        other.tree_.remove(currentKey);
      }
    }
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_MULTISET_H_