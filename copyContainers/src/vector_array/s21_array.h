#ifndef CPP_S21_CONTAINERS_1_SRC_VECTOR_ARRAY_S21_ARRAY_H_
#define CPP_S21_CONTAINERS_1_SRC_VECTOR_ARRAY_S21_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace s21 {

template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = size_t;

 private:
  value_type aPtr_[N];

 public:
  array() : aPtr_{} {};

  array(std::initializer_list<value_type> const &items) {
    std::copy(items.begin(), items.end(), aPtr_);
  }

  array(const array &a) { std::copy(a.aPtr_, a.aPtr_ + N, aPtr_); }

  array(array &&a) noexcept { std::move(a.aPtr_, a.aPtr_ + N, aPtr_); }

  ~array() = default;

  array &operator=(const array &a) {
    if (this != &a) std::copy(a.aPtr_, a.aPtr_ + N, aPtr_);
    return *this;
  }

  array &operator=(array &&a) noexcept {
    if (this != &a) std::move(a.aPtr_, a.aPtr_ + N, aPtr_);
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("Выход за пределы массива");
    return aPtr_[pos];
  }

  reference operator[](size_type pos) { return aPtr_[pos]; }

  const_reference front() const {
    return N > 0 ? aPtr_[0] : throw std::out_of_range("Массив пуст");
  }

  const_reference back() const {
    size_type count_siz = size();
    --count_siz;
    return N <= 0 ? throw std::out_of_range("Массив пуст") : aPtr_[count_siz];
  }

  iterator data() noexcept { return iterator(aPtr_); }

  iterator begin() noexcept { return N == 0 ? end() : aPtr_; }

  const_iterator cbegin() noexcept { return N == 0 ? end() : aPtr_; }

  iterator end() noexcept { return aPtr_ + size(); }

  const_iterator cend() noexcept { return aPtr_ + size(); }

  bool empty() { return N == 0; }

  size_type size() const noexcept { return N; }

  size_type max_size() const noexcept { return size(); }

  void swap(array &other) { std::swap(aPtr_, other.aPtr_); }

  void fill(const_reference value) {
    for (size_type i = 0; i < static_cast<size_type>(end() - aPtr_); ++i) {
      aPtr_[i] = value;
    }
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_VECTOR_ARRAY_S21_ARRAY_H_