#include "s21_test.h"

TEST(insertAndDelete, createTree) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23");

  auto node = myMap1.getTree().search(19);
  EXPECT_EQ(18, node->parent_->key_);

  node = myMap1.getTree().search(17);
  EXPECT_EQ(18, node->parent_->key_);

  node = myMap1.getTree().search(22);
  EXPECT_EQ(23, node->parent_->key_);

  node = myMap1.getTree().search(24);
  EXPECT_EQ(23, node->parent_->key_);

  node = myMap1.getTree().search(20);
  EXPECT_EQ(16, node->parent_->key_);

  node = myMap1.getTree().search(7);
  EXPECT_EQ(16, node->parent_->key_);

  node = myMap1.getTree().search(10);
  EXPECT_EQ(7, node->parent_->key_);

  node = myMap1.getTree().search(2);
  EXPECT_EQ(7, node->parent_->key_);

  node = myMap1.getTree().search(1);
  EXPECT_EQ(2, node->parent_->key_);

  node = myMap1.getTree().search(4);
  EXPECT_EQ(2, node->parent_->key_);
}

TEST(insertAndDelete, deleteRoot) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23");

  myMap1.getTree().remove(16);
  EXPECT_EQ(17, myMap1.getTree().getRoot()->key_);

  auto node = myMap1.getTree().search(17);
  EXPECT_EQ(7, node->left_->key_);

  node = myMap1.getTree().search(17);
  EXPECT_EQ(20, node->right_->key_);

  node = myMap1.getTree().search(18);
  EXPECT_EQ(myMap1.getTree().getNullNode(), node->left_);
}

TEST(insertAndDelete, deleteRootLeft) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  myMap1.getTree().remove(7);

  auto node = myMap1.getTree().search(8);
  EXPECT_EQ(16, node->parent_->key_);

  node = myMap1.getTree().search(10);
  EXPECT_EQ(myMap1.getTree().getNullNode(), node->left_);
}

TEST(insertAndDelete, deleteRootRight) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  myMap1.getTree().remove(20);

  auto node = myMap1.getTree().search(22);
  EXPECT_EQ(16, node->parent_->key_);

  node = myMap1.getTree().search(23);
  EXPECT_EQ(myMap1.getTree().getNullNode(), node->left_);
}

TEST(insertAndDelete, deleteLeftLeft) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  myMap1.getTree().remove(2);

  auto node = myMap1.getTree().search(1);
  EXPECT_EQ(4, node->parent_->key_);

  node = myMap1.getTree().search(4);
  EXPECT_EQ(myMap1.getTree().getNullNode(), node->right_);

  node = myMap1.getTree().search(4);
  EXPECT_EQ(7, node->parent_->key_);
}

TEST(insertAndDelete, deleteLeftRight) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  myMap1.getTree().remove(10);

  auto node = myMap1.getTree().search(11);
  EXPECT_EQ(7, node->parent_->key_);

  node = myMap1.getTree().search(11);
  EXPECT_EQ(myMap1.getTree().getNullNode(), node->right_);

  node = myMap1.getTree().search(11);
  EXPECT_EQ(8, node->left_->key_);
}

TEST(insertAndDelete, deleteLeafRight) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  myMap1.getTree().remove(17);

  auto node = myMap1.getTree().search(18);
  EXPECT_EQ(myMap1.getTree().getNullNode(), node->left_);
}

TEST(insertAndDelete, deleteRightBranch) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  myMap1.getTree().remove(22);
  myMap1.getTree().remove(24);
  myMap1.getTree().remove(23);

  auto node = myMap1.getTree().search(18);
  EXPECT_EQ(16, node->parent_->key_);

  node = myMap1.getTree().search(18);
  EXPECT_EQ(17, node->left_->key_);

  node = myMap1.getTree().search(18);
  EXPECT_EQ(20, node->right_->key_);

  node = myMap1.getTree().search(20);
  EXPECT_EQ(19, node->left_->key_);
}

TEST(insertAndDelete, deleteRightLeaf) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11", 25, "25", 21, "21");
  myMap1.getTree().remove(22);

  auto node = myMap1.getTree().search(23);
  EXPECT_EQ(21, node->left_->key_);
}

TEST(insertAndDelete, balanceDeleteCaseRedBrother) {
  s21::map<int, std::string> myMap;
  myMap.insert_many(10, "10", 5, "5", 20, "20", 15, "15", 25, "25", 30, "30");
  myMap.getTree().remove(10);

  auto node = myMap.getTree().search(15);
  EXPECT_EQ(5, node->left_->key_);
  EXPECT_EQ(25, node->right_->key_);
}

TEST(insertAndDelete, blackBrotherWithBlackChildrenRight) {
  s21::map<int, std::string> myMap;
  myMap.insert_many(10, "10", 5, "5", 15, "15", 12, "12", 18, "18", 17, "17");
  myMap.getTree().remove(12);

  auto node = myMap.getTree().search(17);
  EXPECT_EQ(10, node->parent_->key_);
}

TEST(insertAndDelete, balanceDeleteCaseRedBrotherWithChildren) {
  s21::map<int, std::string> myMap;
  myMap.insert_many(10, "10", 5, "5", 20, "20", 15, "15", 25, "25", 30, "30");
  myMap.getTree().remove(5);
  auto node = myMap.getTree().search(20);

  EXPECT_EQ(10, node->left_->key_);
  EXPECT_EQ(25, node->right_->key_);
}

TEST(iterators, iterator) {
  std::array<std::string, 15> second = {"1",  "2",  "4",  "7",  "8",
                                        "10", "11", "16", "17", "18",
                                        "19", "20", "22", "23", "24"};
  std::array<int, 15> first = {1,  2,  4,  7,  8,  10, 11, 16,
                               17, 18, 19, 20, 22, 23, 24};
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");
  int count = 0;
  auto it = myMap1.begin();
  for (; it != myMap1.end(); it++, count++) {
    EXPECT_EQ(first[count], it->first);
    EXPECT_EQ(second[count], (*it).second);
  }
  it--;
  count--;
  for (; it != myMap1.begin(); it--, count--) {
    EXPECT_EQ(first[count], it->first);
    EXPECT_EQ(second[count], (*it).second);
  }
}

TEST(iterators, constIterator) {
  std::array<std::string, 15> second = {"1",  "2",  "4",  "7",  "8",
                                        "10", "11", "16", "17", "18",
                                        "19", "20", "22", "23", "24"};
  std::array<int, 15> first = {1,  2,  4,  7,  8,  10, 11, 16,
                               17, 18, 19, 20, 22, 23, 24};
  s21::map<int, std::string> myMap;
  myMap.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4", 7,
                    "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23, "23",
                    8, "8", 11, "11");
  const s21::map<int, std::string> myMap1 = myMap;

  int count = 0;
  auto it = myMap1.begin();
  for (; it != myMap1.end(); it++, count++) {
    EXPECT_EQ(first[count], it->first);
    EXPECT_EQ(second[count], (*it).second);
  }
  it--;
  count--;
  for (; it != myMap1.begin(); it--, count--) {
    EXPECT_EQ(first[count], it->first);
    EXPECT_EQ(second[count], (*it).second);
  }
}

TEST(iterators, copyIteratorOverload) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(16, "16", 20, "20", 10, "10", 24, "24", 19, "19", 4, "4",
                     7, "7", 1, "1", 2, "2", 17, "17", 18, "18", 22, "22", 23,
                     "23", 8, "8", 11, "11");

  s21::IteratorMap<int, std::string> it = myMap1.begin();
  s21::IteratorMap<int, std::string> itCopy;
  itCopy = it;

  for (; it != myMap1.end(); ++it, ++itCopy) {
    EXPECT_EQ(itCopy->first, it->first);
    EXPECT_EQ((*itCopy).second, (*it).second);
  }
}

TEST(initTree, initWithParams) {
  s21::RedBlackTree<int, std::string> RBT(1, "one");
  EXPECT_EQ(1, RBT.getRoot()->key_);
  EXPECT_EQ("one", RBT.getRoot()->value_);
}
