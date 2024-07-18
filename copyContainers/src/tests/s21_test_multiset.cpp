#include "s21_test.h"

TEST(constructorsMultiset, defaultConstructor) {
  s21::multiset<int> myMultiset;
  std::multiset<int> originMultiset;

  EXPECT_TRUE(myMultiset.empty());
  EXPECT_TRUE(originMultiset.empty());
}

TEST(constructorsMultiset, initializerListInt) {
  s21::multiset<int> myMultiset = {1, 1, 2, 3, 3, 4, 5, 6, 6, 6, 7};
  std::multiset<int> originMultiset = {1, 1, 2, 3, 3, 4, 5, 6, 6, 6, 7};

  EXPECT_EQ(true, myMultiset == originMultiset);
}

TEST(constructorsMultiset, initializerListIntNE) {
  s21::multiset<int> myMultiset = {1, 1, 2, 3, 3, 4, 5, 6, 6, 6, 7};
  std::multiset<int> originMultiset = {1, 1, 2, 3, 3, 4, 5, 6, 6, 7};

  EXPECT_EQ(false, myMultiset == originMultiset);
}

TEST(constructorsMultiset, initializerListSFloatDiffInsert) {
  s21::multiset<float> myMultiset = {4.55, 3.3, 2.11, 3.3, 4.55};
  std::multiset<float> originMultiset = {3.3, 4.55, 2.11, 4.55, 3.3};

  EXPECT_EQ(true, myMultiset == originMultiset);
}

TEST(constructorsMultiset, initializerListAndTestOverloadPointer) {
  s21::multiset<float> myMultiset = {3.3, 3.3, 4.556, 2.11};
  std::multiset<float> originMultiset = {3.3, 3.3, 4.55, 2.11};

  s21::IteratorSet<float> myIt = myMultiset.begin();
  float *myItPtr = myIt.operator->();
  auto originIt = originMultiset.begin();
  auto *originItPtr = originIt.operator->();

  EXPECT_EQ(true, *myItPtr == *originItPtr);
}

TEST(constructorsMultiset, initializerListAndTestOverloadPointerConst) {
  const s21::multiset<float> myMultiset = {3.3, 3.3, 3.3};
  const std::multiset<float> originMultiset = {3.3, 3.3, 3.3};

  auto myIt = myMultiset.begin();
  const float *myItPtr = myIt.operator->();
  auto originIt = originMultiset.begin();
  auto *originItPtr = originIt.operator->();

  EXPECT_EQ(true, *myItPtr == *originItPtr);
}

TEST(constructorsMultiset, copyConstructor) {
  s21::multiset<float> myMultiset = {3.3, 3.3, 3.33};
  s21::multiset<float> myMultiset2(myMultiset);

  EXPECT_EQ(true, myMultiset == myMultiset2);
}

TEST(constructorsMultiset, copyConstructorOverload) {
  s21::multiset<float> myMultiset = {3.3, 3.3, 3.3};
  s21::multiset<float> myMultiset2;
  myMultiset2 = myMultiset;

  EXPECT_EQ(true, myMultiset == myMultiset2);
}

TEST(constructorsMultiset, moveConstructorOverload) {
  s21::multiset<float> myMultiset = {3.3, 3.33, 3.3};
  s21::multiset<float> myMultiset2;
  myMultiset2 = std::move(myMultiset);

  EXPECT_EQ(3, myMultiset2.size());
  EXPECT_EQ(true, myMultiset.empty());
}

TEST(constructorsMultiset, moveConstructor) {
  s21::multiset<float> myMultiset = {3.3, 3.33, 3.3};
  s21::multiset<float> myMultiset2 = std::move(myMultiset);

  EXPECT_EQ(3, myMultiset2.size());
  EXPECT_EQ(true, myMultiset.empty());
}

TEST(insertMultiset, uniqueValueInsert) {
  s21::multiset<float> myMultiset = {3.3, 3.3, 3.3};
  myMultiset.insert(4.4F);
  auto itMySet = myMultiset.find(4.4F);

  EXPECT_EQ(*itMySet, 4.4F);
}

TEST(insertMultiset, insertInEmpty) {
  s21::multiset<float> myMultiset;
  myMultiset.insert(3.3F);
  auto itMySet = myMultiset.find(3.3F);

  EXPECT_EQ(*itMySet, 3.3F);
}

TEST(editTreeMultiset, mergeAllInsert) {
  s21::multiset<float> myMultiset1 = {1.1, 1.1};
  s21::multiset<float> myMultiset2 = {2.2, 2.2};
  s21::multiset<float> myMultiset3 = {1.1, 2.2, 1.1, 2.2};
  myMultiset1.merge(myMultiset2);

  EXPECT_EQ(true, myMultiset3 == myMultiset1);
  EXPECT_EQ(true, myMultiset2.empty());
}

TEST(editTreeMultiset, mergeWithSameValues) {
  s21::multiset<float> myMultiset1 = {1.1, 2.2};
  s21::multiset<float> myMultiset2 = {1.1, 4.4};
  s21::multiset<float> myMultiset3 = {1.1, 1.1, 2.2, 4.4};

  myMultiset1.merge(myMultiset2);

  EXPECT_EQ(true, myMultiset3 == myMultiset1);
  EXPECT_EQ(true, myMultiset2.empty());
}

TEST(editTreeMultiset, EmptyMerge) {
  s21::multiset<float> myMultiset1;
  s21::multiset<float> myMultiset2 = {1.1, 2.2, 1.1};
  s21::multiset<float> myMultiset3 = {1.1, 1.1, 2.2};

  myMultiset1.merge(myMultiset2);

  EXPECT_EQ(true, myMultiset3 == myMultiset1);
  EXPECT_EQ(true, myMultiset2.empty());
}

TEST(editTreeMultiset, erase) {
  s21::multiset<float> myMultiset1 = {1.1, 3.3, 3.3, 3.3, 4.4};
  s21::multiset<float> myMultiset2 = {1.1, 3.3, 3.3, 4.4};

  auto it = myMultiset1.begin();
  it++;
  myMultiset1.erase(it);
  EXPECT_EQ(true, myMultiset1 == myMultiset2);
}

TEST(editTreeMultiset, eraseOneValue) {
  s21::multiset<float> myMultiset1 = {1.1};
  auto it = myMultiset1.begin();
  myMultiset1.erase(it);

  EXPECT_EQ(true, myMultiset1.empty());
}

TEST(editTreeMultiset, eraseNothing) {
  s21::multiset<float> myMultiset1;
  auto it = myMultiset1.begin();
  it = myMultiset1.erase(it);

  EXPECT_EQ(true, myMultiset1.empty());
  EXPECT_EQ(it, myMultiset1.end());
}

TEST(editTreeMultiset, clearAndEmpty) {
  s21::multiset<float> myMultiset1 = {1.1, 2.2, 1.1};
  s21::multiset<float> myMultiset2 = {3.3, 4.4, 4.4};
  s21::multiset<float> myMultiset3 = {1.1, 1.1, 2.2, 4.4, 4.4};
  s21::multiset<float> myMultiset4;

  myMultiset1.clear();
  myMultiset3.clear();

  EXPECT_EQ(true, myMultiset1.empty());
  EXPECT_EQ(false, myMultiset2.empty());
  EXPECT_EQ(true, myMultiset3.empty());
  EXPECT_EQ(true, myMultiset4.empty());
}

TEST(editTreeMultiset, swap) {
  s21::multiset<float> myMultiset1 = {5.5, 6.6, 6.6};
  s21::multiset<float> myMultiset2 = {1.1, 2.2, 2.2, 3.3, 4.4};
  myMultiset1.swap(myMultiset2);

  EXPECT_EQ(true, myMultiset1.contains(2.2F));
  EXPECT_EQ(true, myMultiset2.contains(6.6F));
}

TEST(editTreeMultiset, swapEmpty) {
  s21::multiset<float> myMultiset1;
  s21::multiset<float> myMultiset2 = {1.1, 1.1, 2.2, 3.3, 4.4};
  myMultiset1.swap(myMultiset2);

  EXPECT_EQ(true, myMultiset1.contains(1.1F));
  EXPECT_EQ(true, myMultiset2.empty());
}

TEST(findersMultiset, findFirstKey) {
  s21::multiset<float> myMultiset1 = {1.1, 2.2, 2.2, 3.3, 4.4};
  auto it = myMultiset1.find(2.2);
  it++;

  EXPECT_EQ(*it, 2.2F);
}

TEST(findersMultiset, findNoExist) {
  s21::multiset<float> myMultiset1 = {1.1, 1.1, 2.2, 3.3, 4.4, 4.4};
  auto it = myMultiset1.find(5.5);

  EXPECT_EQ(it, myMultiset1.end());
}

TEST(findersMultiset, constFind) {
  const s21::multiset<float> myMultiset1 = {1.1, 2.2, 2.2, 3.3, 4.4};
  auto it = myMultiset1.find(2.2);

  EXPECT_EQ(*it, 2.2F);
}

TEST(findersMultiset, constFindNoExist) {
  const s21::multiset<float> myMultiset1 = {1.1, 2.2, 2.2, 3.3, 4.4};
  auto it = myMultiset1.find(5.5);

  EXPECT_EQ(it, myMultiset1.end());
}

TEST(findersMultiset, contains) {
  const s21::multiset<float> myMultiset1 = {1.1, 2.2, 3.3, 4.4, 4.4};

  EXPECT_EQ(true, myMultiset1.contains(1.1));
  EXPECT_EQ(true, myMultiset1.contains(4.4));
  EXPECT_EQ(false, myMultiset1.contains(0));
  EXPECT_EQ(false, myMultiset1.contains(5.5));
}

TEST(beginAndEndMultiset, begin) {
  s21::multiset<float> myMultiset1 = {1.1, 2.2, 3.3, 4.4, 4.4};
  auto it = myMultiset1.begin();
  it++;
  it++;
  it++;

  EXPECT_EQ(*it, 4.4F);
  it++;
  EXPECT_EQ(*it, 4.4F);
  it++;
  EXPECT_EQ(it, myMultiset1.end());
}

TEST(beginAndEndMultiset, constBegin) {
  const s21::multiset<float> myMultiset1 = {1.1, 1.1, 2.2, 3.3, 4.4};
  auto it = myMultiset1.begin();

  EXPECT_EQ(*it, 1.1F);
  it++;
  EXPECT_EQ(*it, 1.1F);
}

TEST(beginAndEndMultiset, end) {
  s21::multiset<float> myMultiset1 = {1.1, 2.2, 4.4, 4.4};
  auto it = myMultiset1.end();
  it--;
  EXPECT_EQ(*it, 4.4F);
  it--;
  EXPECT_EQ(*it, 4.4F);
  it--;
  EXPECT_EQ(*it, 2.2F);
}

TEST(beginAndEndMultiset, constEnd) {
  const s21::multiset<float> myMultiset1 = {1.1, 2.2, 4.4, 4.4};
  auto it = myMultiset1.end();
  it--;
  EXPECT_EQ(*it, 4.4F);
  it--;
  EXPECT_EQ(*it, 4.4F);
  it--;
  EXPECT_EQ(*it, 2.2F);
}

TEST(sizeMultiset, size) {
  s21::multiset<float> myMultiset1 = {1.1, 1.1};
  s21::multiset<float> myMultiset2 = {3.3, 3.3, 3.3};
  s21::multiset<float> myMultiset3 = {2.2, 2.2, 3.3, 3.3};
  s21::multiset<float> myMultiset4;

  EXPECT_EQ(2, myMultiset1.size());
  EXPECT_EQ(3, myMultiset2.size());
  EXPECT_EQ(4, myMultiset3.size());
  EXPECT_NE(5, myMultiset3.size());
  EXPECT_EQ(0, myMultiset4.size());
}

TEST(sizeMultiset, maxSize) {
  s21::multiset<float> myMultiset1 = {1.1, 1.1};
  s21::multiset<int> myMultiset2 = {3, 3, 3};
  s21::multiset<std::string> myMultiset3 = {"one", "one", "two", "two"};
  s21::multiset<float> myMultiset4;

  std::multiset<float> originMultiset1 = {1.1, 1.1};
  std::multiset<int> originMultiset2 = {3, 3, 3};
  std::multiset<std::string> originMultiset3 = {"one", "one", "two", "two"};
  std::multiset<float> originMultiset4;

  EXPECT_EQ(originMultiset1.max_size(), myMultiset1.max_size());
  EXPECT_EQ(originMultiset2.max_size(), myMultiset2.max_size());
  EXPECT_NE(originMultiset3.max_size(), myMultiset3.max_size());
  EXPECT_NE(4, myMultiset3.max_size());
  EXPECT_EQ(originMultiset4.max_size(), myMultiset4.max_size());
}

TEST(insertManyMultiset, standart) {
  s21::multiset<float> myMultiset1;
  myMultiset1.insert_many(3.3, 4.4, 5.5, 3.3, 4.4);
  std::multiset<float> originMultiset1 = {3.3, 4.4, 5.5, 3.3, 4.4};

  EXPECT_EQ(true, myMultiset1 == originMultiset1);
}

TEST(insertManyMultiset, nullValues) {
  s21::multiset<float> myMultiset1;
  EXPECT_THROW(myMultiset1.insert_many(), std::invalid_argument);
}

TEST(count, countMany) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {1, 1, 1, 1, 11, 12};

  EXPECT_EQ(true, myMultiset.count(1) == originMultiset.count(1));
}

TEST(count, countOne) {
  s21::multiset<int> myMultiset = {1, 0, 10};
  std::multiset<int> originMultiset = {1, 11, 12};

  EXPECT_EQ(true, myMultiset.count(1) == originMultiset.count(1));
}

TEST(count, countZero) {
  s21::multiset<int> myMultiset = {0, 10};
  std::multiset<int> originMultiset = {11, 12};

  EXPECT_EQ(true, myMultiset.count(1) == originMultiset.count(1));
}

TEST(boundAndRange, lowerBound) {
  s21::multiset<int> myMultiset = {2, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {2, 1, 1, 1, 11, 12};

  EXPECT_EQ(*(myMultiset.lower_bound(1)), *(originMultiset.lower_bound(1)));
  EXPECT_EQ(1, *(myMultiset.lower_bound(1)));
}

TEST(boundAndRange, lowerBoundWithoutKey) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {1, 1, 1, 1, 10, 12};

  EXPECT_EQ(*(myMultiset.lower_bound(2)), *(originMultiset.lower_bound(2)));
  EXPECT_EQ(10, *(myMultiset.lower_bound(2)));
}

TEST(boundAndRange, lowerBoundLessKey) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};

  EXPECT_EQ(myMultiset.end(), myMultiset.lower_bound(12));
}

TEST(boundAndRange, lowerBoundGraterKey) {
  s21::multiset<int> myMultiset = {5, 6, 6};

  EXPECT_EQ(5, *(myMultiset.lower_bound(4)));
}

TEST(boundAndRange, lowerBoundNull) {
  s21::multiset<int> myMultiset;

  EXPECT_EQ(myMultiset.end(), myMultiset.lower_bound(4));
}

TEST(boundAndRange, upperBound) {
  s21::multiset<int> myMultiset = {2, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {2, 1, 1, 1, 11, 12};

  EXPECT_EQ(*(myMultiset.upper_bound(1)), *(originMultiset.upper_bound(1)));
  EXPECT_EQ(2, *(myMultiset.upper_bound(1)));
}

TEST(boundAndRange, upperBoundWithoutKey) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {1, 1, 1, 1, 10, 12};

  EXPECT_EQ(*(myMultiset.upper_bound(2)), *(originMultiset.upper_bound(2)));
  EXPECT_EQ(10, *(myMultiset.upper_bound(2)));
}

TEST(boundAndRange, upperBoundLessKey) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};

  EXPECT_EQ(myMultiset.end(), myMultiset.upper_bound(12));
}

TEST(boundAndRange, upperBoundGraterThanLast) {
  s21::multiset<int> myMultiset = {5, 6, 6};

  EXPECT_EQ(myMultiset.end(), myMultiset.upper_bound(6));
}

TEST(boundAndRange, upperBoundNull) {
  s21::multiset<int> myMultiset;

  EXPECT_EQ(myMultiset.end(), myMultiset.upper_bound(4));
}

TEST(boundAndRange, equalRange) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {1, 1, 1, 1, 10, 12};

  EXPECT_EQ(*((myMultiset.equal_range(1)).first),
            *((originMultiset.equal_range(1)).first));
  EXPECT_EQ(*((myMultiset.equal_range(1)).second), 10);
  EXPECT_EQ(*((myMultiset.equal_range(1)).first), 1);
}

TEST(boundAndRange, equalRangeNoKey) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};
  std::multiset<int> originMultiset = {1, 1, 1, 1, 10, 12};

  EXPECT_EQ(*((myMultiset.equal_range(2)).first),
            *((originMultiset.equal_range(2)).first));
  EXPECT_EQ(*((myMultiset.equal_range(2)).second), 10);
  EXPECT_EQ(*((myMultiset.equal_range(2)).first), 10);
}

TEST(boundAndRange, equalRangeKeyIsLast) {
  s21::multiset<int> myMultiset = {1, 1, 1, 1, 0, 10};

  EXPECT_EQ(((myMultiset.equal_range(10)).second), myMultiset.end());
  EXPECT_EQ(*((myMultiset.equal_range(10)).first), 10);
}