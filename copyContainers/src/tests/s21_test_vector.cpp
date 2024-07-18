#include "s21_test.h"

TEST(vectorMemberFunctionsTests, defaultConstructor) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.empty(), stdVec.empty());
  EXPECT_EQ(vec.size(), stdVec.size());
  ASSERT_TRUE(vec.size() == 0U);
  ASSERT_TRUE(vec.capacity() == 0U);
}

TEST(vectorMemberFunctionsTests, parametrConstructor) {
  using size_type = s21::vector<int>::size_type;
  size_t n = 3;
  s21::vector<int> vec(n);
  std::vector<int> stdVec(n);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  ASSERT_TRUE(vec.size() == 3);
  ASSERT_TRUE(vec.capacity() == 3);
  for (size_type i = 0; i < n; i++) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(vectorMemberFunctionsTests, parametrConstructor0Elements) {
  using size_type = s21::vector<int>::size_type;
  size_type n = 0;
  s21::vector<int> vec(n);
  std::vector<int> stdVec(n);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_TRUE(vec.empty());
  ASSERT_TRUE(vec.capacity() == 0);
}

TEST(vectorMemberFunctionsTests, initListConstructor) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {4, 8, 15, 16, 23, 42};
  std::vector<int> stdVec = {4, 8, 15, 16, 23, 42};
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  ASSERT_TRUE(vec.size() == 6);
  ASSERT_TRUE(vec.capacity() == 6);
  ASSERT_TRUE(vec[0] == 4);
  ASSERT_TRUE(vec[1] == 8);
  ASSERT_TRUE(vec[2] == 15);
  ASSERT_TRUE(vec[3] == 16);
  ASSERT_TRUE(vec[4] == 23);
  ASSERT_TRUE(vec[5] == 42);
  for (size_type i = 0; i < vec.size(); i++) {
    EXPECT_EQ(vec[i], stdVec[i]);
  }
}

TEST(vectorMemberFunctionsTests, initListConstructor0Elements) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_TRUE(vec.empty());
  ASSERT_TRUE(vec.capacity() == 0);
}

TEST(vectorMemberFunctionsTests, copyConstructor) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> old = {2, 7};
  s21::vector<int> vec(old);
  EXPECT_EQ(old.size(), vec.size());
  EXPECT_EQ(old.capacity(), vec.capacity());
  ASSERT_TRUE(vec.size() == 2);
  ASSERT_TRUE(vec.capacity() == 2);
  size_type n = vec.size();
  for (size_type i = 0; i < n; i++) {
    EXPECT_EQ(vec[i], old[i]);
  }
}

TEST(vectorMemberFunctionsTests, copyConstructor0Elements) {
  s21::vector<int> old;
  s21::vector<int> vec(old);
  EXPECT_EQ(old.size(), vec.size());
  EXPECT_EQ(old.capacity(), vec.capacity());
  EXPECT_TRUE(vec.empty());
  ASSERT_TRUE(vec.capacity() == 0);
}

TEST(vectorMemberFunctionsTests, moveConstructor) {
  s21::vector<int> old = {2, 1};
  s21::vector<int> vec(std::move(old));
  EXPECT_TRUE(old.empty());
  ASSERT_TRUE(old.capacity() == 0);
  ASSERT_TRUE(vec.size() == 2);
  ASSERT_TRUE(vec.capacity() == 2);
  ASSERT_TRUE(vec[0] == 2);
  ASSERT_TRUE(vec[1] == 1);
}

TEST(vectorMemberFunctionsTests, moveConstructor0Elements) {
  s21::vector<int> old;
  s21::vector<int> vec(std::move(old));
  EXPECT_EQ(old.size(), vec.size());
  EXPECT_EQ(old.capacity(), vec.capacity());
  EXPECT_TRUE(old.empty());
  ASSERT_TRUE(old.capacity() == 0);
}

TEST(vectorMemberFunctionsTests, copyAssignOperator) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> old = {7, 9, 3};
  s21::vector<int> vec = {6, 5};
  ASSERT_TRUE(vec.size() == 2);
  ASSERT_TRUE(vec.capacity() == 2);
  vec = old;
  EXPECT_EQ(old.size(), vec.size());
  EXPECT_EQ(old.capacity(), vec.capacity());
  ASSERT_TRUE(vec.size() == 3);
  ASSERT_TRUE(vec.capacity() == 3);
  ASSERT_TRUE(vec[0] == 7);
  ASSERT_TRUE(vec[1] == 9);
  ASSERT_TRUE(vec[2] == 3);
  size_type n = vec.size();
  for (size_type i = 0; i < n; i++) {
    EXPECT_EQ(vec[i], old[i]);
  }
}

TEST(vectorMemberFunctionsTests, copyAssignOperator0Elements) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> old = {8, 4, 1};
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());
  ASSERT_TRUE(vec.capacity() == 0);
  vec = old;
  EXPECT_EQ(old.size(), vec.size());
  EXPECT_EQ(old.capacity(), vec.capacity());
  ASSERT_TRUE(vec.size() == 3);
  ASSERT_TRUE(vec.capacity() == 3);
  size_type n = vec.size();
  for (size_type i = 0; i < n; i++) {
    EXPECT_EQ(vec[i], old[i]);
  }
}

TEST(vectorMemberFunctionsTests, moveAssignOperator) {
  s21::vector<int> old = {7, 9, 3};
  s21::vector<int> vec = {6, 5};
  ASSERT_TRUE(vec.size() == 2);
  ASSERT_TRUE(vec.capacity() == 2);
  vec = std::move(old);
  ASSERT_TRUE(vec.size() == 3);
  ASSERT_TRUE(vec.capacity() == 3);
  ASSERT_TRUE(vec[0] == 7);
  ASSERT_TRUE(vec[1] == 9);
  ASSERT_TRUE(vec[2] == 3);
  ASSERT_TRUE(old.size() == 0);
  ASSERT_TRUE(old.capacity() == 0);
}

TEST(vectorMemberFunctionsTests, moveAssignOperator0Elements) {
  s21::vector<int> old = {7, 9, 3};
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());
  ASSERT_TRUE(vec.capacity() == 0);
  vec = std::move(old);
  ASSERT_TRUE(vec.size() == 3);
  ASSERT_TRUE(vec.capacity() == 3);
  ASSERT_TRUE(vec[0] == 7);
  ASSERT_TRUE(vec[1] == 9);
  ASSERT_TRUE(vec[2] == 3);
  ASSERT_TRUE(old.size() == 0);
  ASSERT_TRUE(old.capacity() == 0);
}

TEST(vectorElementAccessTests, atOk) {
  s21::vector<int> vec = {7, 9, 3};
  std::vector<int> stdVec = {7, 9, 3};
  EXPECT_EQ(vec.at(1), 9);
  EXPECT_EQ(stdVec.at(1), vec.at(1));
}

TEST(vectorElementAccessTests, atEmpty) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.at(0), std::out_of_range);
}

TEST(vectorElementAccessTests, atError) {
  s21::vector<int> vec = {7, 9, 3};
  EXPECT_THROW(vec.at(4), std::out_of_range);
}

TEST(vectorElementAccessTests, operatorSquareBrackets) {
  s21::vector<int> vec = {4, 2, 8};
  std::vector<int> stdVec = {4, 2, 8};
  EXPECT_EQ(vec[2], 8);
  EXPECT_EQ(stdVec[2], vec[2]);
}

TEST(vectorElementAccessTests, front) {
  s21::vector<int> vec = {666, 789, 342, 364, 96};
  std::vector<int> stdVec = {666, 789, 342, 364, 96};
  EXPECT_EQ(vec.front(), 666);
  EXPECT_EQ(vec.front(), stdVec.front());
}

TEST(vectorElementAccessTests, back) {
  s21::vector<int> vec = {666, 789, 342, 364, 96};
  std::vector<int> stdVec = {666, 789, 342, 364, 96};
  EXPECT_EQ(vec.back(), 96);
  EXPECT_EQ(vec.back(), stdVec.back());
}

TEST(vectorElementAccessTests, data) {
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec = {45, 32, 456};
  std::vector<int> stdVec = {45, 32, 456};
  iterator it = vec.data();
  auto stdIt = stdVec.data();
  EXPECT_EQ(vec[0], *it);
  EXPECT_EQ(*stdIt, *it);
}

TEST(vectorIteratorsTests, begin) {
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec = {78, 681, 362};
  std::vector<int> stdVec = {78, 681, 362};
  iterator it = vec.begin();
  auto stdIt = stdVec.begin();
  EXPECT_EQ(*stdIt, *it);
  EXPECT_EQ(vec[0], *it);
  EXPECT_EQ(stdVec[0], *stdIt);
}

TEST(vectorIteratorsTests, beginEmpty) {
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec;
  std::vector<int> stdVec;
  iterator it = vec.begin();
  auto stdIt = stdVec.begin();
  EXPECT_EQ(it, vec.end());
  EXPECT_EQ(stdIt, stdVec.end());
}

TEST(vectorIteratorsTests, cbegin) {
  using const_iterator = s21::vector<int>::const_iterator;
  s21::vector<int> vec = {15, 434, 391};
  std::vector<int> stdVec = {15, 434, 391};
  const_iterator it = vec.cbegin();
  auto stdIt = stdVec.cbegin();
  EXPECT_EQ(*stdIt, *it);
  EXPECT_EQ(vec[0], *it);
  EXPECT_EQ(stdVec[0], *stdIt);
}

TEST(vectorIteratorsTests, cbeginEmpty) {
  using const_iterator = s21::vector<int>::const_iterator;
  s21::vector<int> vec;
  std::vector<int> stdVec;
  const_iterator it = vec.cbegin();
  auto stdIt = stdVec.cbegin();
  EXPECT_EQ(it, vec.cend());
  EXPECT_EQ(stdIt, stdVec.cend());
}

TEST(vectorIteratorsTests, end) {
  using iterator = s21::vector<int>::iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {154, 462, 98};
  std::vector<int> stdVec = {154, 462, 98};
  iterator it = vec.end();
  auto stdIt = stdVec.end();
  size_type vSize = vec.size();
  size_type stdVSize = stdVec.size();
  EXPECT_EQ(vec.begin() + vSize, it);
  EXPECT_EQ(stdVec.begin() + stdVSize, stdIt);
}

TEST(vectorIteratorsTests, endEmpty) {
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec;
  std::vector<int> stdVec;
  iterator it = vec.end();
  auto stdIt = stdVec.end();
  EXPECT_EQ(it, vec.begin());
  EXPECT_EQ(stdIt, stdVec.begin());
}

TEST(vectorIteratorsTests, cend) {  //
  using const_iterator = s21::vector<int>::const_iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {154, 462, 98};
  std::vector<int> stdVec = {154, 462, 98};
  const_iterator it = vec.cend();
  auto stdIt = stdVec.cend();
  size_type vSize = vec.size();
  size_type stdVSize = stdVec.size();
  EXPECT_EQ(vec.cbegin() + vSize, it);
  EXPECT_EQ(stdVec.cbegin() + stdVSize, stdIt);
}

TEST(vectorIteratorsTests, cendEmpty) {
  using const_iterator = s21::vector<int>::const_iterator;
  s21::vector<int> vec;
  std::vector<int> stdVec;
  const_iterator it = vec.cend();
  auto stdIt = stdVec.cend();
  EXPECT_EQ(it, vec.cbegin());
  EXPECT_EQ(stdIt, stdVec.cbegin());
}

TEST(vectorCapacityTests, empty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_TRUE(vec.empty());
  EXPECT_TRUE(stdVec.empty());
}

TEST(vectorCapacityTests, notEmpty) {
  s21::vector<int> vec = {5, 98, 6};
  std::vector<int> stdVec = {5, 98, 6};
  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(stdVec.empty());
}

TEST(vectorCapacityTests, size) {
  s21::vector<int> vec = {98, 654, 12387, 874, 1564, 784, 32};
  std::vector<int> stdVec = {98, 654, 12387, 874, 1564, 784, 32};
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 7);
}

TEST(vectorCapacityTests, sizeEmpty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 0);
}

TEST(vectorCapacityTests, maxSize) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_GT(vec.max_size(), 0);
  EXPECT_GT(stdVec.max_size(), 0);
}

TEST(vectorCapacityTests, reserve) {
  s21::vector<int> vec = {65, 498};
  std::vector<int> stdVec = {65, 498};
  vec.reserve(4);
  stdVec.reserve(4);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 4);
  EXPECT_EQ(vec[0], stdVec[0]);
  EXPECT_EQ(vec[1], stdVec[1]);
  EXPECT_EQ(vec[0], 65);
  EXPECT_EQ(vec[1], 498);
}

TEST(vectorCapacityTests, reserveEmpty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  vec.reserve(3);
  stdVec.reserve(3);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 3);
}

TEST(vectorCapacityTests, capacity) {
  s21::vector<int> vec = {16, 878, 374, 1268, 1568};
  std::vector<int> stdVec = {16, 878, 374, 1268, 1568};
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 5);
}

TEST(vectorCapacityTests, capacityEmpty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(vectorCapacityTests, shrinkToFit) {
  s21::vector<int> vec = {919, 345};
  std::vector<int> stdVec = {919, 345};
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 2);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 2);
  vec.reserve(5);
  stdVec.reserve(5);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 5);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 2);
  vec.shrink_to_fit();
  stdVec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 2);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 2);
}

TEST(vectorCapacityTests, shrinkToFitEmpty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
  vec.reserve(3);
  stdVec.reserve(3);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 3);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
  vec.shrink_to_fit();
  stdVec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
}

TEST(vectorModifiersTests, clear) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {438, 9167, 37, 78, 134};
  std::vector<int> stdVec = {438, 9167, 37, 78, 134};
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 5);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 5);
  vec.clear();
  stdVec.clear();
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 5);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 0);
  for (size_type i = 0; i < vec.capacity(); ++i) {
    EXPECT_NO_THROW(vec[i]);
  }
}

TEST(vectorModifiersTests, clearEmpty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
  vec.clear();
  stdVec.clear();
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
}

TEST(vectorModifiersTests, insert) {
  using iterator = s21::vector<int>::iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {4564, 32, 98, 16};
  std::vector<int> stdVec = {4564, 32, 98, 16};
  size_type insPos = 2;
  iterator it = vec.begin() + insPos;
  auto stdIt = stdVec.begin() + insPos;
  iterator inVec = vec.insert(it, 666);
  auto inStdVec = stdVec.insert(stdIt, 666);
  EXPECT_EQ(vec[2], 666);
  EXPECT_EQ(stdVec[2], 666);
  EXPECT_EQ(*inVec, *inStdVec);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.size(), stdVec.size());
}

TEST(vectorModifiersTests, insertEmpty) {
  using iterator = s21::vector<int>::iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec;
  std::vector<int> stdVec;
  size_type insPos = 0;
  iterator it = vec.begin() + insPos;
  auto stdIt = stdVec.begin() + insPos;
  iterator inVec = vec.insert(it, 777);
  auto inStdVec = stdVec.insert(stdIt, 777);
  EXPECT_EQ(vec[0], 777);
  EXPECT_EQ(stdVec[0], 777);
  EXPECT_EQ(*inVec, *inStdVec);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.size(), stdVec.size());
}

TEST(vectorModifiersTests, insertThrow) {
  using iterator = s21::vector<int>::iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {787, 326, 14, 989};
  size_type insPos = 7;
  iterator it = vec.begin() + insPos;
  EXPECT_THROW(vec.insert(it, 7777), std::out_of_range);
}

TEST(vectorModifiersTests, insertMany) {
  using const_iterator = s21::vector<int>::const_iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {787, 19, 305, 408};
  std::vector<int> ready = {787, 19, 111, 999, 333, 305, 408};
  size_type insPos = 2;
  const_iterator it = vec.cbegin() + insPos;
  vec.insert_many(it, 111, 999, 333);
  EXPECT_EQ(vec.size(), ready.size());
  for (size_type i = 0; i < ready.size(); ++i) {
    EXPECT_EQ(vec[i], ready[i]);
  }
}

TEST(vectorModifiersTests, insertManyEmpty) {
  using const_iterator = s21::vector<int>::const_iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec;
  std::vector<int> ready = {888, 666, 444};
  size_type insPos = 0;
  const_iterator it = vec.cbegin() + insPos;
  vec.insert_many(it, 888, 666, 444);
  EXPECT_EQ(vec.size(), ready.size());
  for (size_type i = 0; i < ready.size(); ++i) {
    EXPECT_EQ(vec[i], ready[i]);
  }
}

TEST(vectorModifiersTests, insertManyThrow) {
  using const_iterator = s21::vector<int>::const_iterator;
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {45, 986, 33};
  size_type insPos = 5;
  const_iterator it = vec.cbegin() + insPos;
  EXPECT_THROW(vec.insert_many(it, 7898, 44, 13), std::out_of_range);
}

TEST(vectorModifiersTests, insertManyBack) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec = {456, 967, 304};
  std::vector<int> ready = {456, 967, 304, 909, 707, 202, 404};
  vec.insert_many_back(909, 707, 202, 404);
  EXPECT_EQ(vec.size(), ready.size());
  for (size_type i = 0; i < ready.size(); ++i) {
    EXPECT_EQ(vec[i], ready[i]);
  }
}

TEST(vectorModifiersTests, insertManyBackEmpty) {
  using size_type = s21::vector<int>::size_type;
  s21::vector<int> vec;
  std::vector<int> ready = {454, 989, 707, 646};
  vec.insert_many_back(454, 989, 707, 646);
  EXPECT_EQ(vec.size(), ready.size());
  for (size_type i = 0; i < ready.size(); ++i) {
    EXPECT_EQ(vec[i], ready[i]);
  }
}

TEST(vectorModifiersTests, erase) {
  using size_type = s21::vector<int>::size_type;
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec = {4984, 13513, 171, 916, 1565, 3545};
  std::vector<int> ready = {4984, 171, 916, 1565, 3545};
  size_type insPos = 1;
  iterator it = vec.begin() + insPos;
  vec.erase(it);
  EXPECT_EQ(vec.size(), ready.size());
  for (size_type i = 0; i < ready.size(); ++i) {
    EXPECT_EQ(vec[i], ready[i]);
  }
}

TEST(vectorModifiersTests, eraseEmpty) {
  using size_type = s21::vector<int>::size_type;
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec = {486451};
  std::vector<int> ready;
  size_type insPos = 0;
  iterator it = vec.begin() + insPos;
  vec.erase(it);
  EXPECT_EQ(vec.size(), ready.size());
  EXPECT_EQ(vec.empty(), ready.empty());
  EXPECT_TRUE(vec.empty());
}

TEST(vectorModifiersTests, eraseThrow) {
  using size_type = s21::vector<int>::size_type;
  using iterator = s21::vector<int>::iterator;
  s21::vector<int> vec = {454, 987, 123};
  size_type insPos = 4;
  iterator it = vec.begin() + insPos;
  EXPECT_THROW(vec.erase(it), std::out_of_range);
}

TEST(vectorModifiersTests, pushBack) {
  s21::vector<int> vec = {654, 316, 9157, 63};
  std::vector<int> stdVec = {654, 316, 9157, 63};
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 4);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 4);
  vec.push_back(777);
  stdVec.push_back(777);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 8);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.back(), 777);
  EXPECT_EQ(stdVec.back(), 777);
}

TEST(vectorModifiersTests, pushBackEmpty) {
  s21::vector<int> vec;
  std::vector<int> stdVec;
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_TRUE(vec.empty());
  vec.push_back(3333);
  stdVec.push_back(3333);
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 1);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec.back(), 3333);
  EXPECT_EQ(stdVec.back(), 3333);
}

TEST(vectorModifiersTests, popBack) {
  s21::vector<int> vec = {564, 84, 65, 78};
  std::vector<int> stdVec = {564, 84, 65, 78};
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 4);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec.back(), 78);
  EXPECT_EQ(stdVec.back(), 78);
  vec.pop_back();
  stdVec.pop_back();
  EXPECT_EQ(vec.capacity(), stdVec.capacity());
  EXPECT_EQ(vec.capacity(), 4);
  EXPECT_EQ(vec.size(), stdVec.size());
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.back(), 65);
  EXPECT_EQ(stdVec.back(), 65);
}

TEST(vectorModifiersTests, popBackEmpty) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
  vec.pop_back();
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(vectorModifiersTests, swap) {
  s21::vector<int> vec1 = {654, 316, 9157, 63};
  s21::vector<int> vec2 = {78, 96};
  std::vector<int> stdVec1 = {654, 316, 9157, 63};
  std::vector<int> stdVec2 = {78, 96};
  EXPECT_EQ(vec1.capacity(), stdVec1.capacity());
  EXPECT_EQ(vec1.capacity(), 4);
  EXPECT_EQ(vec1.size(), stdVec1.size());
  EXPECT_EQ(vec1.size(), 4);
  EXPECT_EQ(vec2.capacity(), stdVec2.capacity());
  EXPECT_EQ(vec2.capacity(), 2);
  EXPECT_EQ(vec2.size(), stdVec2.size());
  EXPECT_EQ(vec2.size(), 2);
  EXPECT_EQ(vec1.front(), 654);
  EXPECT_EQ(vec2.front(), 78);
  EXPECT_EQ(stdVec1.front(), 654);
  EXPECT_EQ(stdVec2.front(), 78);
  vec1.swap(vec2);
  stdVec1.swap(stdVec2);
  EXPECT_EQ(vec1.capacity(), stdVec1.capacity());
  EXPECT_EQ(vec1.capacity(), 2);
  EXPECT_EQ(vec1.size(), stdVec1.size());
  EXPECT_EQ(vec1.size(), 2);
  EXPECT_EQ(vec2.capacity(), stdVec2.capacity());
  EXPECT_EQ(vec2.capacity(), 4);
  EXPECT_EQ(vec2.size(), stdVec2.size());
  EXPECT_EQ(vec2.size(), 4);
  EXPECT_EQ(vec1.front(), 78);
  EXPECT_EQ(vec2.front(), 654);
  EXPECT_EQ(stdVec1.front(), 78);
  EXPECT_EQ(stdVec2.front(), 654);
}

TEST(vectorModifiersTests, swapEmpty) {
  s21::vector<int> vec1 = {654, 316, 9157, 63};
  s21::vector<int> vec2;
  std::vector<int> stdVec1 = {654, 316, 9157, 63};
  std::vector<int> stdVec2;
  EXPECT_EQ(vec1.capacity(), stdVec1.capacity());
  EXPECT_EQ(vec1.capacity(), 4);
  EXPECT_EQ(vec1.size(), stdVec1.size());
  EXPECT_EQ(vec1.size(), 4);
  EXPECT_EQ(vec2.capacity(), stdVec2.capacity());
  EXPECT_EQ(vec2.capacity(), 0);
  EXPECT_EQ(vec2.size(), stdVec2.size());
  EXPECT_TRUE(vec2.empty());
  EXPECT_EQ(vec1.front(), 654);
  vec1.swap(vec2);
  stdVec1.swap(stdVec2);
  EXPECT_EQ(vec1.capacity(), stdVec1.capacity());
  EXPECT_EQ(vec1.capacity(), 0);
  EXPECT_EQ(vec1.size(), stdVec1.size());
  EXPECT_TRUE(vec1.empty());
  EXPECT_EQ(vec2.capacity(), stdVec2.capacity());
  EXPECT_EQ(vec2.capacity(), 4);
  EXPECT_EQ(vec2.size(), stdVec2.size());
  EXPECT_EQ(vec2.size(), 4);
  EXPECT_EQ(vec2.front(), 654);
}