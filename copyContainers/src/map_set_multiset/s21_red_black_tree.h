#ifndef CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_RED_BLACK_TREE_H_
#define CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_RED_BLACK_TREE_H_

#include <iostream>
#include <memory>

namespace s21 {

enum Color { RED, BLACK };

template <typename KeyType, typename ValueType>
struct Node {
 public:
  KeyType key_;
  ValueType value_;
  Color color_;
  Node *left_, *right_, *parent_;

  Node(const KeyType &key, const ValueType &value)
      : key_(key),
        value_(value),
        color_(RED),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr) {}

  Node()
      : key_(),
        value_(),
        color_(BLACK),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr) {}

  Node(const Node &) = default;
  Node &operator=(const Node &) = default;
  Node(Node &&) = default;
  Node &operator=(Node &&) = default;
  ~Node() = default;
};

template <typename KeyType, typename ValueType>
class RedBlackTree {
 public:
  RedBlackTree(bool allowDuplicates = false)
      : root_(nullptr),
        nullNode_(new Node<KeyType, ValueType>()),
        allowDuplicates_(allowDuplicates) {
    nullNode_->left_ = nullNode_->right_ = nullNode_->parent_ = nullNode_;
    root_ = nullNode_;
  }

  RedBlackTree(const KeyType &key, const ValueType &value,
               bool allowDuplicates = false)
      : nullNode_(new Node<KeyType, ValueType>()),
        allowDuplicates_(allowDuplicates) {
    nullNode_->left_ = nullNode_->right_ = nullNode_->parent_ = nullNode_;
    root_ = new Node<KeyType, ValueType>(key, value);
    root_->color_ = BLACK;
    root_->left_ = root_->right_ = root_->parent_ = nullNode_;
  }

  ~RedBlackTree() {
    destroyTree(root_);
    delete nullNode_;
  }

  RedBlackTree(const RedBlackTree &other) {
    nullNode_ = new Node<KeyType, ValueType>();
    nullNode_->left_ = nullNode_->right_ = nullNode_->parent_ = nullNode_;
    root_ = copyTree(other.root_, other.nullNode_);
  }

  RedBlackTree(RedBlackTree &&other) noexcept
      : root_(other.root_), nullNode_(other.nullNode_) {
    other.root_ = other.nullNode_ = nullptr;
  }

  RedBlackTree &operator=(const RedBlackTree &other) {
    if (this != &other) {
      destroyTree(root_);
      delete nullNode_;
      nullNode_ = new Node<KeyType, ValueType>();
      nullNode_->left_ = nullNode_->right_ = nullNode_->parent_ = nullNode_;
      root_ = copyTree(other.root_, other.nullNode_);
    }
    return *this;
  }

  RedBlackTree &operator=(RedBlackTree &&other) noexcept {
    if (this != &other) {
      destroyTree(root_);
      delete nullNode_;
      root_ = other.root_;
      nullNode_ = other.nullNode_;
      other.root_ = other.nullNode_ = nullptr;
    }
    return *this;
  }

  void destroyTree(Node<KeyType, ValueType> *node) {
    Node<KeyType, ValueType> *current = node;
    Node<KeyType, ValueType> *temp = nullptr;

    while (current != nullNode_) {
      if (current->left_ != nullNode_) {
        current = current->left_;
        continue;
      }

      if (current->right_ != nullNode_) {
        current = current->right_;
        continue;
      }

      temp = current;
      current = current->parent_;

      if (temp != nullNode_) {
        if (current->left_ == temp)
          current->left_ = nullNode_;
        else
          current->right_ = nullNode_;
        delete temp;
      }
    }
  }

  bool insert(const KeyType &key, const ValueType &value) {
    bool isInsert = false;
    if (search(key) == nullNode_ || allowDuplicates_ == true) {
      Node<KeyType, ValueType> *newNode =
          new Node<KeyType, ValueType>(key, value);
      newNode->left_ = newNode->right_ = newNode->parent_ = nullNode_;
      root_ = insertBST(root_, newNode);
      balance(newNode);
      root_->color_ = BLACK;
      isInsert = true;
    }
    return isInsert;
  }

  void remove(const KeyType &key) {
    Node<KeyType, ValueType> *node = search(key);
    if (node != nullNode_) deleteNode(node);
  }

  void swap(RedBlackTree<KeyType, ValueType> &other) {
    std::swap(root_, other.root_);
    std::swap(nullNode_, other.nullNode_);
  }

  Node<KeyType, ValueType> *search(const KeyType &key) const {
    Node<KeyType, ValueType> *node = root_;
    Node<KeyType, ValueType> *result = nullNode_;
    while (node != nullNode_) {
      if (key < node->key_)
        node = node->left_;
      else if (key > node->key_)
        node = node->right_;
      else {
        result = node;
        node = node->left_;
      }
    }

    return result;
  }

  Node<KeyType, ValueType> *lowerBound(const KeyType &key) const {
    Node<KeyType, ValueType> *current = root_;
    Node<KeyType, ValueType> *result = nullNode_;

    while (current != nullNode_) {
      if (current->key_ >= key) {
        result = current;
        current = current->left_;
      } else {
        current = current->right_;
      }
    }
    return result;
  }

  Node<KeyType, ValueType> *getNullNode() const { return nullNode_; }
  Node<KeyType, ValueType> *getRoot() const { return root_; }
  void setRoot(Node<KeyType, ValueType> *newRoot) { root_ = newRoot; }

 private:
  Node<KeyType, ValueType> *root_;
  Node<KeyType, ValueType> *nullNode_;
  bool allowDuplicates_;

  Node<KeyType, ValueType> *copyTree(Node<KeyType, ValueType> *node,
                                     Node<KeyType, ValueType> *otherNullNode) {
    if (node == otherNullNode || node == nullptr) return nullNode_;

    Node<KeyType, ValueType> *newNode =
        new Node<KeyType, ValueType>(node->key_, node->value_);
    newNode->color_ = node->color_;

    newNode->left_ = copyTree(node->left_, otherNullNode);
    if (newNode->left_ != nullNode_) {
      newNode->left_->parent_ = newNode;
    }

    newNode->right_ = copyTree(node->right_, otherNullNode);
    if (newNode->right_ != nullNode_) {
      newNode->right_->parent_ = newNode;
    }

    newNode->parent_ = nullNode_;

    return newNode;
  }

  Node<KeyType, ValueType> *insertBST(Node<KeyType, ValueType> *root,
                                      Node<KeyType, ValueType> *newNode) {
    Node<KeyType, ValueType> *current = root;
    Node<KeyType, ValueType> *parent = nullNode_;

    while (current != nullNode_) {
      parent = current;
      if (newNode->key_ < current->key_)
        current = current->left_;
      else
        current = current->right_;
    }

    newNode->parent_ = parent;
    if (parent == nullNode_)
      root = newNode;
    else if (newNode->key_ < parent->key_)
      parent->left_ = newNode;
    else
      parent->right_ = newNode;

    return root;
  }

  void balance(Node<KeyType, ValueType> *&ptr) {
    Node<KeyType, ValueType> *parent = nullptr;
    Node<KeyType, ValueType> *grand_parent = nullptr;

    while ((ptr != root_) && (ptr->color_ == RED) &&
           (ptr->parent_->color_ == RED)) {
      parent = ptr->parent_;
      grand_parent = parent->parent_;

      bool isLeft = (parent == grand_parent->left_);
      Node<KeyType, ValueType> *uncle =
          isLeft ? grand_parent->right_ : grand_parent->left_;

      if (uncle && uncle->color_ == RED) {
        grand_parent->color_ = RED;
        parent->color_ = BLACK;
        uncle->color_ = BLACK;
        ptr = grand_parent;
      } else {
        if (isLeft) {
          if (ptr == parent->right_) {
            rotate(parent, true);
            ptr = parent;
            parent = ptr->parent_;
          }
          rotate(grand_parent, false);
        } else {
          if (ptr == parent->left_) {
            rotate(parent, false);
            ptr = parent;
            parent = ptr->parent_;
          }
          rotate(grand_parent, true);
        }
        std::swap(parent->color_, grand_parent->color_);
        ptr = parent;
      }
    }
    root_->color_ = BLACK;
  }

  Node<KeyType, ValueType> *minimum(Node<KeyType, ValueType> *node) const {
    while (node->left_ != nullNode_) node = node->left_;
    return node;
  }

  void transplant(Node<KeyType, ValueType> *del,
                  Node<KeyType, ValueType> *insert) {
    if (del->parent_ == nullNode_)
      root_ = insert;
    else if (del == del->parent_->left_)
      del->parent_->left_ = insert;
    else
      del->parent_->right_ = insert;

    insert->parent_ = del->parent_;
  }

  void deleteNode(Node<KeyType, ValueType> *&node) {
    Node<KeyType, ValueType> *y = node;
    Node<KeyType, ValueType> *x;
    Color yOriginalColor = y->color_;

    if (node->left_ == nullNode_) {
      x = node->right_;
      transplant(node, node->right_);
    } else if (node->right_ == nullNode_) {
      x = node->left_;
      transplant(node, node->left_);
    } else {
      y = minimum(node->right_);
      yOriginalColor = y->color_;
      x = y->right_;

      if (y->parent_ == node) {
        x->parent_ = y;
      } else {
        transplant(y, y->right_);
        y->right_ = node->right_;
        y->right_->parent_ = y;
      }

      transplant(node, y);
      y->left_ = node->left_;
      y->left_->parent_ = y;
      y->color_ = node->color_;
    }

    if (yOriginalColor == BLACK) balanceDelete(x);
    if (node != nullNode_) {
      delete node;
      node = nullNode_;
    }
  }

  void balanceDelete(Node<KeyType, ValueType> *x) {
    while (x != root_ && x->color_ == BLACK) {
      bool isLeft = (x == x->parent_->left_);
      Node<KeyType, ValueType> *brother =
          isLeft ? x->parent_->right_ : x->parent_->left_;

      if (brother->color_ == RED) {
        brother->color_ = BLACK;
        x->parent_->color_ = RED;
        rotate(x->parent_, isLeft);
        brother = isLeft ? x->parent_->right_ : x->parent_->left_;
      }

      if ((isLeft && brother->left_->color_ == BLACK &&
           brother->right_->color_ == BLACK) ||
          (!isLeft && brother->right_->color_ == BLACK &&
           brother->left_->color_ == BLACK)) {
        brother->color_ = RED;
        x = x->parent_;
      } else {
        balanceDeleteCase(x, brother, isLeft);
        x = root_;
      }
    }
    x->color_ = BLACK;
  }

  void balanceDeleteCase(Node<KeyType, ValueType> *x,
                         Node<KeyType, ValueType> *brother, bool isLeft) {
    if (isLeft) {
      if (brother->right_->color_ == BLACK) {
        brother->left_->color_ = BLACK;
        brother->color_ = RED;
        rotate(brother, false);
        brother = x->parent_->right_;
      }
      brother->color_ = x->parent_->color_;
      x->parent_->color_ = BLACK;
      brother->right_->color_ = BLACK;
      rotate(x->parent_, true);
    } else {
      if (brother->left_->color_ == BLACK) {
        brother->right_->color_ = BLACK;
        brother->color_ = RED;
        rotate(brother, true);
        brother = x->parent_->left_;
      }
      brother->color_ = x->parent_->color_;
      x->parent_->color_ = BLACK;
      brother->left_->color_ = BLACK;
      rotate(x->parent_, false);
    }
  }

  void rotate(Node<KeyType, ValueType> *&x, bool left) {
    Node<KeyType, ValueType> *y = left ? x->right_ : x->left_;
    if (left) {
      x->right_ = y->left_;
      if (y->left_ != nullNode_) y->left_->parent_ = x;
    } else {
      x->left_ = y->right_;
      if (y->right_ != nullNode_) y->right_->parent_ = x;
    }
    y->parent_ = x->parent_;

    if (x->parent_ == nullNode_)
      root_ = y;
    else if (x == x->parent_->left_)
      x->parent_->left_ = y;
    else
      x->parent_->right_ = y;

    if (left)
      y->left_ = x;
    else
      y->right_ = x;

    x->parent_ = y;
  }
};

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_1_SRC_MAP_SET_MULTISET_S21_RED_BLACK_TREE_H_
