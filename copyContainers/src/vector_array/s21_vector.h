#ifndef CPP_S21_CONTAINERS_1_SRC_VECTOR_ARRAY_S21_VECTOR_H_
#define CPP_S21_CONTAINERS_1_SRC_VECTOR_ARRAY_S21_VECTOR_H_

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class T>
class VectorIterator {
 public:
  using value_type = T;
  using pointer = value_type *;
  using reference = value_type &;
  using difference_type = std::ptrdiff_t;

 protected:
  pointer vIter_;

 public:
  VectorIterator() : vIter_(nullptr) {}
  explicit VectorIterator(pointer ptr) : vIter_(ptr) {}
  VectorIterator(const VectorIterator &other) = default;
  VectorIterator(VectorIterator &&other) noexcept : vIter_(other.vIter_) {
    other.vIter_ = nullptr;
  }
  ~VectorIterator() = default;

  reference operator*() const { return *vIter_; }
  pointer operator->() const { return vIter_; }

  VectorIterator &operator=(const VectorIterator &other) = default;
  VectorIterator &operator=(VectorIterator &&other) noexcept {
    if (this != &other) this->vIter_ = std::exchange(other.vIter_, nullptr);
    return *this;
  }

  VectorIterator &operator++() {
    ++vIter_;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  VectorIterator &operator--() {
    --vIter_;
    return *this;
  }

  VectorIterator operator--(int) {
    VectorIterator tmp(*this);
    --(*this);
    return tmp;
  }

  VectorIterator &operator+=(int pos) {
    vIter_ += pos;
    return *this;
  }

  VectorIterator &operator-=(int pos) {
    vIter_ -= pos;
    return *this;
  }

  difference_type operator-(const VectorIterator &other) const {
    return this->vIter_ - other.vIter_;
  }

  VectorIterator operator-(difference_type offset) const {
    return VectorIterator(vIter_ - offset);
  }

  VectorIterator operator+(int n) const {
    VectorIterator vPtr_(*this);
    return vPtr_ += n;
  }

  bool operator==(const VectorIterator &other) const {
    return this->vIter_ == other.vIter_;
  }

  bool operator!=(const VectorIterator &other) const {
    return this->vIter_ != other.vIter_;
  }

  bool operator<(const VectorIterator &other) const {
    return this->vIter_ < other.vIter_;
  }

  bool operator<=(const VectorIterator &other) const {
    return this->vIter_ <= other.vIter_;
  }

  bool operator>(const VectorIterator &other) const {
    return this->vIter_ > other.vIter_;
  }

  bool operator>=(const VectorIterator &other) const {
    return this->vIter_ >= other.vIter_;
  }
};

template <class T>
class VectorConstIterator : public VectorIterator<T> {
 public:
  using value_type = T;
  using pointer = const value_type *;
  using reference = const value_type &;
  using difference_type = std::ptrdiff_t;

 protected:
  pointer vCiter_;

 public:
  VectorConstIterator() : VectorIterator<T>(), vCiter_(nullptr) {}
  explicit VectorConstIterator(pointer ptr)
      : VectorIterator<T>(
            const_cast<typename VectorIterator<T>::pointer>(ptr)) {
    this->vCiter_ = ptr;
  }
  VectorConstIterator(const VectorConstIterator &other) = default;
  VectorConstIterator(VectorConstIterator &&other) noexcept
      : VectorIterator<T>(other), vCiter_(other.vCiter_) {}
  ~VectorConstIterator() = default;

  reference operator*() const { return *vCiter_; }
  pointer operator->() const { return vCiter_; }

  VectorConstIterator &operator=(const VectorConstIterator &other) = default;
  VectorConstIterator &operator=(VectorConstIterator &&other) noexcept {
    if (this != &other) this->vCiter_ = std::exchange(other.vCiter_, nullptr);
    return *this;
  }

  VectorConstIterator &operator++() {
    ++vCiter_;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  VectorConstIterator &operator--() {
    --vCiter_;
    return *this;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator tmp(*this);
    --(*this);
    return tmp;
  }

  VectorConstIterator &operator+=(int pos) {
    vCiter_ += pos;
    return *this;
  }

  VectorConstIterator &operator-=(int pos) {
    vCiter_ -= pos;
    return *this;
  }

  difference_type operator-(const VectorConstIterator &other) const {
    return this->vCiter_ - other.vCiter_;
  }

  VectorConstIterator operator-(difference_type offset) const {
    return VectorConstIterator(vCiter_ - offset);
  }

  VectorConstIterator operator+(int n) const {
    VectorConstIterator vPtr_(*this);
    return vPtr_ += n;
  }

  bool operator==(const VectorConstIterator &other) const {
    return this->vCiter_ == other.vCiter_;
  }

  bool operator!=(const VectorConstIterator &other) const {
    return this->vCiter_ != other.vCiter_;
  }

  bool operator<(const VectorConstIterator &other) const {
    return this->vCiter_ < other.vCiter_;
  }

  bool operator<=(const VectorConstIterator &other) const {
    return this->vCiter_ <= other.vCiter_;
  }

  bool operator>(const VectorConstIterator &other) const {
    return this->vCiter_ > other.vCiter_;
  }

  bool operator>=(const VectorConstIterator &other) const {
    return this->vCiter_ >= other.vCiter_;
  }
};

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using iterator = VectorIterator<value_type>;
  using const_iterator = VectorConstIterator<value_type>;
  using size_type = size_t;

 private:
  size_type vSize_;
  size_type vCapacity_;
  value_type *vPtr_;

 public:
  vector() : vSize_(0U), vCapacity_(0U), vPtr_(nullptr) {}

  explicit vector(size_type n)
      : vSize_(n), vCapacity_(n), vPtr_(n ? new value_type[n] : nullptr) {
    std::fill(vPtr_, vPtr_ + n, value_type());
  }

  vector(std::initializer_list<value_type> const &items)
      : vSize_(items.size()),
        vCapacity_(items.size()),
        vPtr_(new value_type[items.size()]) {
    std::copy(items.begin(), items.end(), vPtr_);
  }

  vector(const vector &v)
      : vSize_(v.vSize_),
        vCapacity_(v.vCapacity_),
        vPtr_(new value_type[v.vCapacity_]) {
    std::copy(v.vPtr_, v.vPtr_ + v.vSize_, vPtr_);
  }

  vector(vector &&v) noexcept
      : vSize_(v.vSize_), vCapacity_(v.vCapacity_), vPtr_(v.vPtr_) {
    v.vPtr_ = nullptr;
    v.vSize_ = 0;
    v.vCapacity_ = 0;
  }

  ~vector() {
    delete[] vPtr_;
    vPtr_ = nullptr;
    vSize_ = 0;
    vCapacity_ = 0;
  }

  vector &operator=(const vector &v) {
    if (this != &v) {
      value_type *tmpVPtr_ = new value_type[v.vCapacity_];
      std::copy(v.vPtr_, v.vPtr_ + v.vSize_, tmpVPtr_);
      delete[] vPtr_;
      vPtr_ = tmpVPtr_;
      vSize_ = v.vSize_;
      vCapacity_ = v.vCapacity_;
    }
    return *this;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] vPtr_;
      vSize_ = std::exchange(v.vSize_, 0);
      vCapacity_ = std::exchange(v.vCapacity_, 0);
      vPtr_ = std::exchange(v.vPtr_, nullptr);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= vSize_) throw std::out_of_range("Выход за пределы вектора");
    return vPtr_[pos];
  }

  reference operator[](size_type pos) { return vPtr_[pos]; }

  const_reference front() { return vPtr_[0]; }

  const_reference back() { return vPtr_[vSize_ - 1]; }

  iterator data() noexcept { return iterator(vPtr_); }

  iterator begin() noexcept { return empty() ? end() : iterator(vPtr_); }

  const_iterator cbegin() const noexcept {
    return empty() ? cend() : const_iterator(vPtr_);
  }

  iterator end() noexcept { return iterator(vPtr_ + vSize_); }

  const_iterator cend() const noexcept {
    return const_iterator(vPtr_ + vSize_);
  }

  bool empty() const noexcept { return vSize_ == 0; }

  size_type size() const noexcept { return vSize_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size > vCapacity_) {
      if (size > max_size())
        throw std::length_error("Превышен максимальный размер");
      value_type *tempPtr = new value_type[size];
      for (size_type i = 0; i < vSize_; ++i) tempPtr[i] = std::move(vPtr_[i]);
      delete[] vPtr_;
      vCapacity_ = size;
      vPtr_ = tempPtr;
    }
  }

  size_type capacity() const noexcept { return vCapacity_; }

  void shrink_to_fit() {
    if (vCapacity_ > vSize_) {
      value_type *tempPtr = new value_type[vSize_];
      std::copy(vPtr_, vPtr_ + vSize_, tempPtr);
      delete[] vPtr_;
      vCapacity_ = vSize_;
      vPtr_ = tempPtr;
    }
  }

  void clear() noexcept {
    for (size_type i = 0; i < vSize_; ++i) (*this)[i].~value_type();
    vSize_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end())
      throw std::out_of_range("Итератор вне диапазона");
    size_type insSize = 1;
    size_type insPos = pos - begin();
    bool backFlag = false;
    preInsert(insSize, insPos, backFlag);
    vPtr_[insPos] = value;
    return begin() + insPos;
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    if (pos < cbegin() || pos > cend())
      throw std::out_of_range("Итератор вне диапазона");
    size_type insSize = sizeof...(Args);
    size_type insPos = pos - cbegin();
    bool backFlag = false;
    preInsert(insSize, insPos, backFlag);
    postInsert(insSize, insPos, std::forward<Args>(args)...);
    return begin() + insPos;
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    size_type insSize = sizeof...(Args);
    size_type insPos = size();
    bool backFlag = true;
    preInsert(insSize, insPos, backFlag);
    postInsert(insSize, insPos, std::forward<Args>(args)...);
  }

  void erase(iterator pos) {
    if (pos < begin() || pos >= end())
      throw std::out_of_range("Итератор вне диапазона");
    size_type insPos = pos - cbegin();
    for (size_type i = insPos; i < size() - 1; ++i) vPtr_[i] = vPtr_[i + 1];
    (*this)[vSize_].~value_type();
    --vSize_;
  }

  void push_back(const_reference value) {
    if (size() + 1 > max_size())
      throw std::length_error("Превышен максимальный размер");
    if (vSize_ + 1 > vCapacity_) reserve(vCapacity_ > 0 ? vCapacity_ * 2 : 1);
    vPtr_[vSize_] = value;
    ++vSize_;
  }

  void pop_back() {
    if (vSize_ > 0) {
      vPtr_[vSize_ - 1].~value_type();
      --vSize_;
    }
  }

  void swap(vector &other) {
    std::swap(vPtr_, other.vPtr_);
    std::swap(vSize_, other.vSize_);
    std::swap(vCapacity_, other.vCapacity_);
  }

  void preInsert(size_type insSize, size_type insPos, bool backFlag) {
    size_type oldSize = size();
    size_type newSize = vSize_ + insSize;
    if (newSize > max_size())
      throw std::length_error("Превышен максимальный размер");
    if (newSize > vCapacity_) {
      if (vCapacity_ > 0 && vCapacity_ * 2 >= newSize)
        reserve(vCapacity_ * 2);
      else
        reserve(newSize);
    }
    vSize_ += insSize;
    if (oldSize > 0 && !backFlag) {
      for (size_type i = vSize_; i > insPos; --i) vPtr_[i] = vPtr_[i - insSize];
    }
  }

  template <class... Args>
  void postInsert(size_type insSize, size_type insPos, Args &&...args) {
    vector<value_type> argscopy{std::forward<Args>(args)...};
    for (size_type i = 0; i < insSize; ++i)
      vPtr_[i + insPos] = std::move(argscopy[i]);
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_VECTOR_ARRAY_S21_VECTOR_H_