#ifndef CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_MAP_H_
#define CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_MAP_H_

#include "../vector_array/s21_vector.h"
#include "s21_base_container.h"
#include "s21_red_black_tree.h"

namespace s21 {

template <typename KeyType, typename ValueType>
class IteratorMap
    : public IteratorBase<KeyType, ValueType, Node<KeyType, ValueType> *> {
 public:
  using IteratorBase<KeyType, ValueType,
                     Node<KeyType, ValueType> *>::IteratorBase;

  std::shared_ptr<std::pair<const KeyType &, ValueType &>> pairPtr_;

  std::pair<const KeyType &, ValueType &> operator*() {
    return {this->currentNode_->key_, this->currentNode_->value_};
  }

  std::pair<const KeyType &, ValueType &> *operator->() {
    pairPtr_ = std::make_shared<std::pair<const KeyType &, ValueType &>>(
        this->currentNode_->key_, this->currentNode_->value_);
    return pairPtr_.get();
  }
};

template <typename KeyType, typename ValueType>
class ConstIteratorMap : public IteratorBase<KeyType, ValueType,
                                             const Node<KeyType, ValueType> *> {
 public:
  using IteratorBase<KeyType, ValueType,
                     const Node<KeyType, ValueType> *>::IteratorBase;

  std::shared_ptr<std::pair<const KeyType &, const ValueType &>> pairPtr_;

  std::pair<const KeyType &, const ValueType &> operator*() {
    return {this->currentNode_->key_, this->currentNode_->value_};
  }

  std::pair<const KeyType &, const ValueType &> *operator->() {
    pairPtr_ = std::make_shared<std::pair<const KeyType &, const ValueType &>>(
        this->currentNode_->key_, this->currentNode_->value_);
    return pairPtr_.get();
  }
};

template <typename KeyType, typename ValueType>
class map
    : public BaseContainer<KeyType, ValueType, IteratorMap<KeyType, ValueType>,
                           ConstIteratorMap<KeyType, ValueType>> {
 public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = IteratorMap<key_type, mapped_type>;
  using const_iterator = ConstIteratorMap<key_type, mapped_type>;
  using size_type = size_t;
  using allocator = std::allocator<Node<key_type, value_type>>;

  using BaseContainer<key_type, mapped_type, iterator,
                      const_iterator>::BaseContainer;

  map(std::initializer_list<value_type> const &items) {
    for (auto &item : items) this->insert(item);
  }

  Node<key_type, mapped_type> *getRoot() const { return this->tree_.getRoot(); }

  template <typename MapType>
  bool operator==(const MapType m) const {
    bool equal = true;
    auto itLeftMap = this->begin();
    auto itRightMap = m.begin();
    if (this->size() == m.size()) {
      while ((itLeftMap != this->end()) && (equal == true)) {
        if ((itLeftMap->first) != (itRightMap->first) ||
            (itLeftMap->second) != (itRightMap->second))
          equal = false;
        itLeftMap++;
        itRightMap++;
      }
    } else {
      equal = false;
    }
    return equal;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool isInsert = this->tree_.insert(value.first, value.second);
    iterator it = this->find(value.first);
    return {it, isInsert};
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    return insert({key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    bool isInsert = false;
    auto search = this->find(key);
    if (search == this->end()) {
      this->insert(key, obj);
      search = this->find(key);
      isInsert = true;
    } else {
      search->second = obj;
    }
    return {search, isInsert};
  }

  mapped_type &at(const key_type &key) {
    iterator value = this->find(key);
    if (value == this->end()) throw std::out_of_range("Key not found");
    return value->second;
  }

  mapped_type &operator[](const key_type &key) {
    iterator search = this->find(key);
    if (search == this->end()) {
      auto value = this->insert(key, mapped_type());
      search->second = value.first->second;
    }
    return search->second;
  }

  void merge(map &other) {
    if (this != &other) {
      auto it = other.begin();
      while (it != other.end()) {
        auto currentKey = it->first;
        auto currentValue = it->second;
        ++it;
        if (this->tree_.search(currentKey) == this->tree_.getNullNode()) {
          this->insert(currentKey, currentValue);
          other.tree_.remove(currentKey);
        }
      }
    }
  }

  iterator erase(iterator pos) {
    key_type key = pos->first;
    ++pos;
    this->tree_.remove(key);
    return pos;
  }

  void swap(map &other) noexcept { this->tree_.swap(other.tree_); }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    if constexpr (sizeof...(args) % 2 == 0 && sizeof...(args) > 0) {
      s21::vector<std::pair<iterator, bool>> results;
      results.reserve(sizeof...(args) / 2);
      inserts(results, args...);
      return results;
    } else {
      throw std::invalid_argument("Количество элементов должно быть четным");
    }
  }

  template <typename... Args>
  void inserts(s21::vector<std::pair<iterator, bool>> &results, key_type key,
               mapped_type value, Args &&...args) {
    auto pair = this->insert(key, value);
    results.push_back(std::move(pair));
    if constexpr (sizeof...(args) > 0) inserts(results, args...);
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_MAP_H_
