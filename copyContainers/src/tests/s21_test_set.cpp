#include "s21_test.h"

TEST(constructorsSet, defaultConstructor) {
  s21::set<int> mySet;
  std::set<int> originSet;

  EXPECT_TRUE(mySet.empty());
  EXPECT_TRUE(originSet.empty());
}

TEST(constructorsSet, initializerListInt) {
  s21::set<int> mySet = {1, 2, 3, 4, 5};
  std::set<int> originSet = {1, 2, 3, 4, 5};

  EXPECT_EQ(true, mySet == originSet);
}

TEST(constructorsSet, initializerListSFloat) {
  s21::set<float> mySet = {3.3, 4.55, 2.11};
  std::set<float> originSet = {3.3, 4.55, 2.11};

  EXPECT_EQ(true, mySet == originSet);
}

TEST(constructorsSet, initializerListFloatNE) {
  const s21::set<float> mySet = {3.3, 4.556, 2.11};
  const std::set<float> originSet = {3.3, 4.55, 2.11};

  EXPECT_EQ(false, mySet == originSet);
}

TEST(constructorsSet, initializerListAndTestOverloadPointer) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  std::set<float> originSet = {3.3, 4.55, 2.11};

  s21::IteratorSet<float> myIt = mySet.begin();
  float *myItPtr = myIt.operator->();
  auto originIt = originSet.begin();
  auto *originItPtr = originIt.operator->();

  EXPECT_EQ(true, *myItPtr == *originItPtr);
}

TEST(constructorsSet, initializerListAndTestOverloadPointerConst) {
  const s21::set<float> mySet = {3.3, 4.556, 2.11};
  const std::set<float> originSet = {3.3, 4.55, 2.11};

  auto myIt = mySet.begin();
  const float *myItPtr = myIt.operator->();
  auto originIt = originSet.begin();
  auto *originItPtr = originIt.operator->();

  EXPECT_EQ(true, *myItPtr == *originItPtr);
}

TEST(constructorsSet, copyConstructor) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  s21::set<float> mySet2(mySet);

  EXPECT_EQ(true, mySet == mySet2);
}

TEST(constructorsSet, copyConstructorOverload) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  s21::set<float> mySet2;
  mySet2 = mySet;

  EXPECT_EQ(true, mySet == mySet2);
}

TEST(constructorsSet, moveConstructorOverload) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  s21::set<float> mySet2;
  mySet2 = std::move(mySet);

  EXPECT_EQ(3, mySet2.size());
}

TEST(constructorsSet, moveConstructor) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  s21::set<float> mySet2 = std::move(mySet);

  EXPECT_EQ(3, mySet2.size());
  EXPECT_EQ(true, mySet.empty());
}

TEST(insertSet, uniqueValueInsert) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  mySet.insert(4.4F);
  auto itMySet = mySet.find(4.4F);

  EXPECT_EQ(*itMySet, 4.4F);
}

TEST(insertSet, noUniqueValueInsert) {
  s21::set<float> mySet = {3.3, 4.556, 2.11};
  mySet.insert(3.3F);
  auto itMySet = mySet.find(3.3F);

  EXPECT_EQ(*itMySet, 3.3F);
}

TEST(editTreeSet, mergeAllInsert) {
  s21::set<float> mySet1 = {1.1, 2.2};
  s21::set<float> mySet2 = {3.3, 4.4};
  s21::set<float> mySet3 = {1.1, 2.2, 3.3, 4.4};
  mySet1.merge(mySet2);

  EXPECT_EQ(true, mySet3 == mySet1);
  EXPECT_EQ(true, mySet2.empty());
}

TEST(editTreeSet, mergeWithSameValues) {
  s21::set<float> mySet1 = {1.1, 2.2};
  s21::set<float> mySet2 = {1.1, 4.4};
  s21::set<float> mySet3 = {1.1, 2.2, 4.4};

  mySet1.merge(mySet2);
  auto it = mySet2.begin();

  EXPECT_EQ(true, mySet3 == mySet1);
  EXPECT_EQ(1.1F, *it);
}

TEST(editTreeSet, NoMerge) {
  s21::set<float> mySet1 = {1.1, 2.2};
  s21::set<float> mySet2 = {1.1, 2.2};
  mySet1.merge(mySet2);

  EXPECT_EQ(true, mySet2 == mySet1);
}

TEST(editTreeSet, erase) {
  s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  s21::set<float> mySet2 = {1.1, 3.3, 4.4};

  auto it = mySet1.begin();
  it++;
  mySet1.erase(it);
  EXPECT_EQ(true, mySet1 == mySet2);
}

TEST(editTreeSet, eraseOneValue) {
  s21::set<float> mySet1 = {1.1};
  auto it = mySet1.begin();
  mySet1.erase(it);

  EXPECT_EQ(true, mySet1.empty());
}

TEST(editTreeSet, eraseNothing) {
  s21::set<float> mySet1;
  auto it = mySet1.begin();
  it = mySet1.erase(it);

  EXPECT_EQ(true, mySet1.empty());
  EXPECT_EQ(it, mySet1.end());
}

TEST(editTreeSet, clearAndEmpty) {
  s21::set<float> mySet1 = {1.1, 2.2};
  s21::set<float> mySet2 = {3.3, 4.4};
  s21::set<float> mySet3 = {1.1, 2.2, 3.3, 4.4};
  s21::set<float> mySet4;

  mySet1.clear();
  mySet3.clear();

  EXPECT_EQ(true, mySet1.empty());
  EXPECT_EQ(false, mySet2.empty());
  EXPECT_EQ(true, mySet3.empty());
  EXPECT_EQ(true, mySet4.empty());
}

TEST(editTreeSet, swap) {
  s21::set<float> mySet1 = {5.5, 6.6};
  s21::set<float> mySet2 = {1.1, 2.2, 3.3, 4.4};
  mySet1.swap(mySet2);

  EXPECT_EQ(true, mySet1.contains(1.1F));
  EXPECT_EQ(true, mySet2.contains(6.6F));
}

TEST(editTreeSet, swapEmpty) {
  s21::set<float> mySet1;
  s21::set<float> mySet2 = {1.1, 2.2, 3.3, 4.4};
  mySet1.swap(mySet2);

  EXPECT_EQ(true, mySet1.contains(3.3F));
  EXPECT_EQ(true, mySet2.empty());
}

TEST(findersSet, find) {
  s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.find(2.2);

  EXPECT_EQ(*it, 2.2F);
}

TEST(findersSet, findNoExist) {
  s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.find(5.5);

  EXPECT_EQ(it, mySet1.end());
}

TEST(findersSet, constFind) {
  const s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.find(2.2);

  EXPECT_EQ(*it, 2.2F);
}

TEST(findersSet, constFindNoExist) {
  const s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.find(5.5);

  EXPECT_EQ(it, mySet1.end());
}

TEST(findersSet, contains) {
  const s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};

  EXPECT_EQ(true, mySet1.contains(1.1));
  EXPECT_EQ(true, mySet1.contains(4.4));
  EXPECT_EQ(false, mySet1.contains(0));
  EXPECT_EQ(false, mySet1.contains(5.5));
}

TEST(beginAndEndSet, begin) {
  s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.begin();

  EXPECT_EQ(*it, 1.1F);
  it++;
  EXPECT_EQ(*it, 2.2F);
}

TEST(beginAndEndSet, constBegin) {
  const s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.begin();

  EXPECT_EQ(*it, 1.1F);
  it++;
  EXPECT_EQ(*it, 2.2F);
}

TEST(beginAndEndSet, end) {
  s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.end();
  it--;
  it--;

  EXPECT_EQ(*it, 3.3F);
}

TEST(beginAndEndSet, constEnd) {
  const s21::set<float> mySet1 = {1.1, 2.2, 3.3, 4.4};
  auto it = mySet1.end();
  --it;

  EXPECT_EQ(*it, 4.4F);
}

TEST(sizeSet, size) {
  s21::set<float> mySet1 = {1.1, 2.2};
  s21::set<float> mySet2 = {3.3, 4.4, 5.5};
  s21::set<float> mySet3 = {1.1, 2.2, 3.3, 4.4};
  s21::set<float> mySet4;

  EXPECT_EQ(2, mySet1.size());
  EXPECT_EQ(3, mySet2.size());
  EXPECT_EQ(4, mySet3.size());
  EXPECT_NE(5, mySet3.size());
  EXPECT_EQ(0, mySet4.size());
}

TEST(sizeSet, maxSize) {
  s21::set<float> mySet1 = {1.1, 2.2};
  s21::set<int> mySet2 = {3, 4, 5};
  s21::set<std::string> mySet3 = {"one", "two", "three", "four"};
  s21::set<float> mySet4;

  std::set<float> originSet1 = {1.1, 2.2};
  std::set<int> originSet2 = {3, 4, 5};
  std::set<std::string> originSet3 = {"one", "two", "three", "four"};
  std::set<float> originSet4;

  EXPECT_EQ(originSet1.max_size(), mySet1.max_size());
  EXPECT_EQ(originSet2.max_size(), mySet2.max_size());
  EXPECT_NE(originSet3.max_size(), mySet3.max_size());
  EXPECT_NE(4, mySet3.max_size());
  EXPECT_EQ(originSet4.max_size(), mySet4.max_size());
}

TEST(insertManySet, standart) {
  s21::set<float> mySet1;
  mySet1.insert_many(3.3, 4.4, 5.5);
  std::set<float> originSet1 = {3.3, 4.4, 5.5};

  EXPECT_EQ(true, mySet1 == originSet1);
}

TEST(insertManySet, nullValues) {
  s21::set<float> mySet1;
  EXPECT_THROW(mySet1.insert_many(), std::invalid_argument);
}