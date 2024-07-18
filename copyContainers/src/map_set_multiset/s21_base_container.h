#ifndef CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_BASE_CONTAINER_H_
#define CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_BASE_CONTAINER_H_

#include "s21_red_black_tree.h"

namespace s21 {

template <typename KeyType, typename ValueType, typename NodePtrType>
class IteratorBase {
 public:
  IteratorBase(NodePtrType node, NodePtrType root, NodePtrType nullNode)
      : currentNode_(node), root_(root), nullNode_(nullNode) {}

  IteratorBase() : currentNode_(nullptr), root_(nullptr), nullNode_(nullptr) {}

  IteratorBase(const IteratorBase &other)
      : currentNode_(other.currentNode_),
        root_(other.root_),
        nullNode_(other.nullNode_) {}

  IteratorBase &operator=(const IteratorBase &other) {
    if (this != &other) {
      currentNode_ = other.currentNode_;
      root_ = other.root_;
      nullNode_ = other.nullNode_;
    }
    return *this;
  }

  IteratorBase(IteratorBase &&) = default;
  IteratorBase &operator=(IteratorBase &&) = default;
  ~IteratorBase() = default;

  IteratorBase &operator--() {
    currentNode_ = predecessor(currentNode_);
    if (currentNode_ == nullNode_) currentNode_ = maximum(root_);

    return *this;
  }

  IteratorBase &operator++() {
    currentNode_ = successor(currentNode_);
    return *this;
  }

  IteratorBase operator--(int) {
    IteratorBase temp = *this;
    --(*this);
    return temp;
  }

  IteratorBase operator++(int) {
    IteratorBase temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const IteratorBase &other) const {
    return (currentNode_ == other.currentNode_);
  }

  bool operator!=(const IteratorBase &other) const {
    return (currentNode_ != other.currentNode_);
  }

 protected:
  NodePtrType currentNode_;

 private:
  NodePtrType root_;
  NodePtrType nullNode_;

  NodePtrType successor(NodePtrType node) const {
    if (node == nullNode_) return nullNode_;

    NodePtrType returnNode;
    if (node->right_ != nullNode_) {
      node = node->right_;
      while (node->left_ != nullNode_) node = node->left_;
      returnNode = node;
    } else {
      NodePtrType parent = node->parent_;
      while (parent != nullNode_ && node == parent->right_) {
        node = parent;
        parent = parent->parent_;
      }
      returnNode = parent;
    }
    return returnNode;
  }

  NodePtrType predecessor(NodePtrType node) const {
    if (node == nullNode_) return nullNode_;

    NodePtrType returnNode;
    if (node->left_ != nullNode_) {
      node = node->left_;
      while (node->right_ != nullNode_) node = node->right_;
      returnNode = node;
    } else {
      NodePtrType parent = node->parent_;
      while (parent != nullNode_ && node == parent->left_) {
        node = parent;
        parent = parent->parent_;
      }
      returnNode = parent;
    }
    return returnNode;
  }

  NodePtrType maximum(NodePtrType node) const {
    while (node->right_ != nullNode_) node = node->right_;
    return node;
  }
};

template <typename KeyType, typename ValueType, typename IteratorType,
          typename ConstIteratorType>
class BaseContainer {
 public:
  using key_type = KeyType;
  using value_type = ValueType;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using allocator = std::allocator<Node<key_type, value_type>>;

  BaseContainer(bool allowDuplicates = false) : tree_(allowDuplicates) {}

  BaseContainer(std::initializer_list<value_type> const &items,
                bool allowDuplicates = false)
      : tree_(allowDuplicates) {
    for (auto &item : items) this->insert(item);
  }

  BaseContainer(const BaseContainer &obj) : tree_(obj.tree_) {}

  BaseContainer &operator=(const BaseContainer &obj) {
    if (this != &obj) tree_ = obj.tree_;
    return *this;
  }

  BaseContainer(BaseContainer &&obj) noexcept : tree_(std::move(obj.tree_)) {}

  BaseContainer &operator=(BaseContainer &&obj) noexcept {
    tree_ = std::move(obj.tree_);
    return *this;
  }

  ~BaseContainer() { clear(); }

  bool empty() const { return (tree_.getRoot() == tree_.getNullNode()); }

  void clear() {
    tree_.destroyTree(tree_.getRoot());
    tree_.setRoot(tree_.getNullNode());
  }

  bool contains(const key_type &key) const {
    return tree_.search(key) != tree_.getNullNode();
  }

  size_type size() const {
    size_type count = 0;
    for (ConstIteratorType it = begin(); it != end(); ++it) ++count;
    return count;
  }

  size_type max_size() const { return allocator().max_size(); }

  IteratorType find(const key_type &key) {
    return IteratorType(tree_.search(key), tree_.getRoot(),
                        tree_.getNullNode());
  }

  ConstIteratorType find(const key_type &key) const {
    return ConstIteratorType(tree_.search(key), tree_.getRoot(),
                             tree_.getNullNode());
  }

  IteratorType begin() {
    Node<key_type, value_type> *node = tree_.getRoot();
    while (node->left_ != tree_.getNullNode()) node = node->left_;
    return IteratorType(node, tree_.getRoot(), tree_.getNullNode());
  }

  IteratorType end() {
    return IteratorType(tree_.getNullNode(), tree_.getRoot(),
                        tree_.getNullNode());
  }

  ConstIteratorType begin() const {
    Node<key_type, value_type> *node = tree_.getRoot();
    while (node->left_ != tree_.getNullNode()) node = node->left_;
    return ConstIteratorType(node, tree_.getRoot(), tree_.getNullNode());
  }

  ConstIteratorType end() const {
    return ConstIteratorType(tree_.getNullNode(), tree_.getRoot(),
                             tree_.getNullNode());
  }

  std::pair<IteratorType, bool> insert(const value_type &value) {
    bool isInsert = this->tree_.insert(value, value);
    IteratorType it = find(value);
    return {it, isInsert};
  }

  RedBlackTree<KeyType, ValueType> &getTree() { return tree_; }
  Node<key_type, value_type> *getNullNode() { return tree_.getNullNode(); }
  Node<key_type, value_type> *getRoot() { return tree_.getRoot(); }
  void setRoot(Node<key_type, value_type> *newRoot) { tree_.setRoot(newRoot); }

 protected:
  RedBlackTree<KeyType, ValueType> tree_;
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_BASE_CONTAINER_H_
