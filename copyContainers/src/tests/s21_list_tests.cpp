#include "s21_test.h"

TEST(testListPushBack, PushBack1) {
  s21::list<int> myList;
  myList.push_back(42);
  myList.push_back(17);
  myList.push_back(89);
  myList.push_back(123);
  myList.push_back(55);
  myList.push_back(72);
  myList.push_back(33);

  EXPECT_EQ(myList.size(), 7);
  EXPECT_EQ(myList.empty(), false);
}

TEST(testListPushBack, PushBack) {
  s21::list<int> myList;
  std::list<int> stdList;

  for (int i = 0; i < 100; ++i) {
    myList.push_back(i);
    stdList.push_back(i);
  }

  EXPECT_EQ(myList.size(), stdList.size());

  auto myIt = myList.begin();
  auto stdIt = stdList.begin();

  while (myIt != myList.end() && stdIt != stdList.end()) {
    EXPECT_EQ(*myIt, *stdIt);
    ++myIt;
    ++stdIt;
  }
}

TEST(testListPopBack, PopBack) {
  s21::list<int> myList{1, 2, 3};
  myList.pop_back();

  EXPECT_EQ(myList.size(), 2);

  myList.pop_back();
  myList.pop_back();

  EXPECT_EQ(myList.size(), 0);
  EXPECT_EQ(myList.empty(), true);
}

TEST(testListPushFront, PushFront) {
  s21::list<int> myList;
  myList.push_front(100);
  myList.push_front(200);
  myList.push_front(300);

  EXPECT_EQ(myList.size(), 3);
  EXPECT_EQ(myList.empty(), false);
}

TEST(testListClear, Clear) {
  s21::list<int> myList;
  std::list<int> stdList;

  for (int i = 0; i < 100; ++i) {
    myList.push_back(i);
    stdList.push_back(i);
  }

  EXPECT_EQ(myList.size(), stdList.size());

  myList.clear();
  stdList.clear();

  EXPECT_EQ(myList.size(), stdList.size());
}

TEST(testListSort, Sort) {
  s21::list<int> myList = {3, 5, 1, 9, 8, 21, 1};
  std::list<int> sortList = {3, 5, 1, 9, 8, 21, 1};

  myList.sort();
  sortList.sort();

  EXPECT_EQ(myList.size(), sortList.size());

  auto myIt = myList.begin();
  auto stdIt = sortList.begin();

  while (myIt != myList.end() && stdIt != sortList.end()) {
    EXPECT_EQ(*myIt, *stdIt);
    ++myIt;
    ++stdIt;
  }
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  s21::list<int> moved(std::move(original));

  EXPECT_EQ(original.size(), 0);
  EXPECT_TRUE(original.empty());

  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);

  EXPECT_NE(moved.head, &moved.endNode);
  EXPECT_NE(moved.tail, &moved.endNode);
  EXPECT_EQ(moved.endNode.pNext, &moved.endNode);
  EXPECT_EQ(moved.endNode.pPrev, &moved.endNode);
  EXPECT_EQ(moved.sizenode, 3);
}

TEST(tesListSort, SortSimple) {
  s21::list<int> myList = {42, 21};
  myList.sort();
  EXPECT_EQ(myList.front(), 21);
  EXPECT_EQ(myList.back(), 42);
}

TEST(tesListSort, SortSortedList) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.sort();
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(tesListSort, SortReverseSortedList) {
  s21::list<int> myList = {5, 4, 3, 2, 1};
  myList.sort();
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(testListSwap, Swap) {
  s21::list<int> list1 = {12, 4, 21, 0, 3};
  s21::list<int> list2 = {2, 421, 121, 42, 13};

  std::list<int> swap1 = {2, 421, 121, 42, 13};
  std::list<int> swap2 = {12, 4, 21, 0, 3};

  list1.swap(list2);

  auto myIt = list1.begin();
  auto stdIt = swap1.begin();

  while (myIt != list1.end() && stdIt != swap1.end()) {
    EXPECT_EQ(*myIt, *stdIt);
    ++myIt;
    ++stdIt;
  }

  auto myIt2 = list2.begin();
  auto stdIt2 = swap2.begin();

  while (myIt2 != list2.end() && stdIt2 != swap2.end()) {
    EXPECT_EQ(*myIt2, *stdIt2);
    ++myIt2;
    ++stdIt2;
  }
}

TEST(testListUnique, unique1) {
  s21::list<int> s21list2 = {1, 2, 2, 2, 3, 4, 4, 4, 5, 5};
  std::list<int> list = {1, 2, 2, 2, 3, 4, 4, 4, 5, 5};
  s21list2.unique();

  list.unique();

  auto it = s21list2.begin();

  for (auto itStd = list.begin(); itStd != list.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(testListUnique, uniqueNon) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.unique();

  EXPECT_EQ(myList.size(), 5);
}

TEST(testListUnique, unique3) {
  s21::list<int> myList = {1, 2, 2, 1, 3, 4, 4, 4};
  s21::list<int> list = {1, 2, 2, 1, 3, 4, 4, 4};
  myList.unique();
  list.unique();

  EXPECT_EQ(myList.size(), list.size());
}

TEST(ListTest, MaxSize) {
  s21::list<int> myList;

  auto maxSize = myList.max_size();
  EXPECT_NE(maxSize, 0);
  EXPECT_EQ(maxSize,
            std::numeric_limits<typename std::list<int>::size_type>::max() /
                sizeof(typename std::list<int>::size_type) / 2);
}

TEST(testListMaxSize, maxsize) {
  s21::list<int> myList = {};
  myList.unique();

  EXPECT_EQ(myList.size(), 0);
}

TEST(testListMerge, MergeTwoListsTwo) {
  s21::list<int> list1 = {2, 4, 6};
  s21::list<int> list2 = {3, 9, 12};
  std::list<int> list3 = {2, 3, 4, 6, 9, 12};
  list1.merge(list2);

  auto myIt2 = list1.begin();
  auto stdIt2 = list3.begin();

  while (myIt2 != list1.end() && stdIt2 != list3.end()) {
    EXPECT_EQ(*myIt2, *stdIt2);
    ++myIt2;
    ++stdIt2;
  }

  EXPECT_EQ(list1.size(), 6);
}

TEST(testListMerge, MergeTwoEmptyLists) {
  std::list<int> list1;
  std::list<int> list2;
  list1.merge(list2);

  EXPECT_EQ(list1.size(), 0);
  EXPECT_EQ(list2.size(), 0);
}

TEST(testListReverse, reverse) {
  s21::list<int> list1 = {1, 2, 3, 4, 5, 6};

  list1.reverse();

  EXPECT_EQ(list1.front(), 6);
  EXPECT_EQ(list1.back(), 1);
}

TEST(testListReverse, reverseOne) {
  s21::list<int> list1 = {1};

  list1.reverse();

  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 1);
}

TEST(testListPopFront, popFront) {
  s21::list<int> s21List = {0};
  s21List.push_front(7);
  s21List.push_front(123);
  s21List.push_front(88);
  s21List.pop_front();
  int i = 3;
  EXPECT_EQ(i, s21List.size());
}

TEST(testListErase, Erase) {
  s21::list<int> s21List = {1, 2, 3, 4, 5, 6, 7};
  auto i = s21List.begin();
  ++i;
  s21List.erase(i);
  EXPECT_EQ(6, s21List.size());
}

TEST(testListErase, Erase2) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  auto it = myList.begin();
  ++it;

  EXPECT_NO_THROW(myList.erase(it));
  EXPECT_EQ(myList.size(), 4);

  int expected_values[] = {1, 3, 4, 5};
  int index = 0;
  for (auto &elem : myList) {
    EXPECT_EQ(elem, expected_values[index++]);
  }
}

TEST(testListErase, SingleElementList) {
  s21::list<int> myList = {42};
  auto it = myList.begin();

  EXPECT_NO_THROW(myList.erase(it));
  EXPECT_EQ(myList.size(), 0);
}

TEST(testListSize, listSize) {
  s21::list<int> myList = {};

  for (int i = 0; i < 100; ++i) {
    myList.push_back(i);
  }

  EXPECT_EQ(myList.size(), 100);
}

TEST(testListEmpty, EmptyFalse) {
  s21::list<int> s21List = {1, 2, 3};
  int res = s21List.empty();
  ASSERT_EQ(0, res);
}

TEST(testEmpty, EmptyTrue) {
  s21::list<int> s21List = {1, 2, 3};
  int res = s21List.empty();
  ASSERT_EQ(1, !res);
}

TEST(ListOperatorAssignmentTest, MoveAssignment) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};

  list1 = std::move(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list1.back(), 6);
}

TEST(ListTest, FrontBackBeginEnd) {
  s21::list<int> myList = {1, 2, 3};

  EXPECT_EQ(myList.front(), 1);

  EXPECT_EQ(myList.back(), 3);

  auto it = myList.begin();
  EXPECT_NE(it, myList.end());

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(List, ConstructorCopy) {
  s21::list<int> ourList = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  s21::list<int> ourCopy(ourList);
  std::list<int> stdCopy(stdList);
  EXPECT_EQ(ourCopy.front(), stdCopy.front());
  EXPECT_EQ(ourCopy.back(), stdCopy.back());
}

TEST(List, ConstructorList) {
  s21::list<int> ourList = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};
  EXPECT_EQ(ourList.front(), stdList.front());
  EXPECT_EQ(ourList.back(), stdList.back());
}

TEST(List, ConstructorDefault) {
  s21::list<int> ourList;
  std::list<int> stdList;
  EXPECT_EQ(ourList.empty(), stdList.empty());
}

TEST(List, ConstructorSize) {
  s21::list<int> ourList(5);
  std::list<int> stdList(5);
  EXPECT_EQ(ourList.size(), stdList.size());
}

TEST(TestList, InsertManyOnce) {
  s21::list<int> l({1, 2, 3});

  auto pos = l.begin();
  pos++;
  l.insert(pos, 4);

  EXPECT_EQ(4, l.size());

  int arr[] = {1, 4, 2, 3};
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(arr[i], *iter);
  }
}

TEST(testsOfList, Insert) {
  s21::list<int> s21List = {1, 2, 3, 4, 5};
  std::list<int> List = {1, 2, 3, 4, 5};
  auto it1 = s21List.begin();
  auto itStd = List.begin();

  auto it2 = s21List.insert(it1, 0);
  auto itStd2 = List.insert(itStd, 0);

  ASSERT_EQ(*itStd2, *it2);

  it1++;
  it1++;
  it1++;

  for (size_t i = 0; i < 3; i++) {
    itStd++;
  }

  it2 = s21List.insert(it1, 6);
  itStd2 = List.insert(itStd, 6);
  ASSERT_EQ(*itStd2, *it2);

  it1 = s21List.end();
  itStd = List.end();
  it2 = s21List.insert(it1, 7);
  itStd2 = List.insert(itStd, 7);
  ASSERT_EQ(*itStd2, *it2);
}

TEST(SpliceTest, EmptyList) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;

  auto pos = list1.cbegin();
  list1.splice(pos, list2);

  EXPECT_TRUE(list1.size() == 3);
  EXPECT_TRUE(list2.size() == 0);
}

TEST(SpliceTest, SpliceNonEmptyLists) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {10, 20, 30};

  auto pos = list1.cbegin();
  list1.splice(pos, list2);

  EXPECT_TRUE(list1.size() == 6);
  EXPECT_TRUE(list2.size() == 0);
}

TEST(SpliceTest, SpliceOne) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {10, 20, 30};

  std::list<int> list3 = {1, 2, 3};
  std::list<int> list4 = {10, 20, 30};

  auto pos = list1.cbegin();
  list1.splice(pos, list2);

  auto pos2 = list3.cbegin();
  list3.splice(pos2, list4);

  auto it1 = list1.begin();
  auto it3 = list3.begin();
  for (; it1 != list1.end(); ++it1, ++it3) {
    EXPECT_EQ(*it1, *it3);
  }
}

TEST(SpliceTest, SpliceTwo) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {10, 20, 30};

  std::list<int> list3 = {1, 2, 3};
  std::list<int> list4 = {10, 20, 30};

  auto pos = list1.cbegin();

  list1.splice(pos, list2);

  auto pos2 = list3.cbegin();

  list3.splice(pos2, list4);

  auto it1 = list1.begin();
  auto it3 = list3.begin();
  for (; it1 != list1.end(); ++it1, ++it3) {
    EXPECT_EQ(*it1, *it3);
  }
}

TEST(SpliceTest, SpliceBackFron) {
  s21::list<int> ourListFirst = {1};
  s21::list<int> ourListSecond = {2, 3, 4, 5};
  std::list<int> stdListFirst = {1};
  std::list<int> stdListSecond = {2, 3, 4, 5};
  auto ourIt = ourListFirst.cbegin();
  auto stdIt = stdListFirst.cbegin();
  ourListFirst.splice(ourIt, ourListSecond);
  stdListFirst.splice(stdIt, stdListSecond);
  EXPECT_EQ(ourListFirst.front(), stdListFirst.front());
  EXPECT_EQ(ourListFirst.back(), stdListFirst.back());
}

TEST(IteratorTests, IncrementOperator) {
  s21::list<int> list;
  list.push_back(5);
  list.push_back(10);

  s21::list<int>::iterator it = list.begin();

  ++it;
  EXPECT_EQ(*it, 10);
}

TEST(IteratorTests, DecrementOperator) {
  s21::list<int> list = {5, 10};
  s21::list<int>::iterator it = list.end();
  --it;
  EXPECT_EQ(*it, 10);
  --it;
  EXPECT_EQ(*it, 5);
}

TEST(IteratorTests, CompoundAssignmentOperator) {
  s21::list<int> list = {5, 10};
  s21::list<int>::iterator it = list.begin();
  it++;
  EXPECT_EQ(*it, 10);
}

TEST(testInsertManyFront, InsertManyFront) {
  s21::list<int> myList;

  myList.insert_many_front(5, 4, 3, 2, 1);

  EXPECT_EQ(myList.size(), 5);

  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(testInsertManyBack, InsertManyBack) {
  s21::list<int> myList;

  myList.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(myList.size(), 5);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 5);
}

TEST(testInsertMany, InsertMany) {
  s21::list<int> myList = {1, 2, 3, 7};

  auto it = myList.cbegin();

  myList.insert_many(it, 4, 5, 6);

  int expected[] = {4, 5, 6, 1, 2, 3, 7};

  int i = 0;
  for (const auto &item : myList) {
    EXPECT_EQ(item, expected[i]);
    ++i;
  }

  EXPECT_EQ(myList.size(), 7);
}

TEST(testStackEmpty, Empty) {
  s21::stack<int> st;
  EXPECT_EQ(st.empty(), true);
}

TEST(testStackEmpty, NotEmpty) {
  s21::stack<int> st{1, 2, 3};
  EXPECT_EQ(st.empty(), false);
}

TEST(StackTest, PopSingleElementStack) {
  s21::stack<int> st;
  st.push(1);
  EXPECT_EQ(st.size(), 1);
  st.pop();
  EXPECT_EQ(st.size(), 0);
}

TEST(StackTestPop, PopMultipleElementsStack) {
  s21::stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);
  EXPECT_EQ(st.size(), 3);
  st.pop();
  EXPECT_EQ(st.size(), 2);
  EXPECT_EQ(st.top(), 2);
  st.pop();
  EXPECT_EQ(st.size(), 1);
  EXPECT_EQ(st.top(), 1);
  st.pop();
  EXPECT_EQ(st.size(), 0);
}

TEST(StackTestPop, PopAfterPushAndPop) {
  s21::stack<int> st;
  st.push(1);
  st.pop();
  EXPECT_EQ(st.size(), 0);
  st.push(2);
  EXPECT_EQ(st.size(), 1);
  st.pop();
  EXPECT_EQ(st.size(), 0);
}

TEST(StackTestPop, PopMultipleTimes) {
  s21::stack<int> st;
  for (int i = 0; i < 10; ++i) {
    st.push(i);
  }
  EXPECT_EQ(st.size(), 10);
  for (int i = 9; i >= 0; --i) {
    st.pop();
    EXPECT_EQ(st.size(), i);
  }
}

TEST(StackTest, Swap) {
  s21::stack<int> st1;
  st1.push(1);
  st1.push(2);
  st1.push(3);

  s21::stack<int> st2;
  st2.push(4);
  st2.push(5);
  st2.push(6);

  st1.swap(st2);

  EXPECT_EQ(st1.size(), 3);
  EXPECT_EQ(st1.top(), 6);
  st1.pop();
  EXPECT_EQ(st1.top(), 5);
  st1.pop();
  EXPECT_EQ(st1.top(), 4);

  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st2.top(), 3);
  st2.pop();
  EXPECT_EQ(st2.top(), 2);
  st2.pop();
  EXPECT_EQ(st2.top(), 1);
}

TEST(StackTest, SwapWithSelf) {
  s21::stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);
  st.swap(st);
  EXPECT_EQ(st.size(), 3);
  EXPECT_EQ(st.top(), 3);
  st.pop();
  EXPECT_EQ(st.top(), 2);
  st.pop();
  EXPECT_EQ(st.top(), 1);
}

TEST(StackTest, SwapWithEmpty) {
  s21::stack<int> st1;
  st1.push(1);
  st1.push(2);
  st1.push(3);
  s21::stack<int> st2;
  st1.swap(st2);
  EXPECT_TRUE(st1.empty());
  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st2.top(), 3);
  st2.pop();
  EXPECT_EQ(st2.top(), 2);
  st2.pop();
  EXPECT_EQ(st2.top(), 1);
}

TEST(StackOperatorCopyTest, CopyEmpty) {
  s21::stack<int> st1;
  s21::stack<int> st2(st1);

  EXPECT_EQ(st1.size(), st2.size());
}

TEST(StackOperatorMoveTest, MoveNotEmpty) {
  s21::stack<int> st3;
  st3.push(1);
  st3.push(2);
  st3.push(3);
  s21::stack<int> st4;
  st4.push(4);
  st4.push(5);
  st4.push(6);
  st3 = std::move(st4);
  EXPECT_TRUE(st3.size() == 3);
  EXPECT_TRUE(st3.top() == 6);
}

TEST(StackOperatorMoveTest, MoveEmpty) {
  s21::stack<int> st1;
  s21::stack<int> st2;
  st1 = std::move(st2);
  EXPECT_EQ(st1.size(), st2.size());
}

TEST(StackConstructorTests, ConstructFromInitializerList) {
  std::initializer_list<int> items = {1, 2, 3, 4, 5};

  s21::stack<int> stack(items);
  ASSERT_EQ(stack.size(), 5);
  ASSERT_EQ(stack.top(), 5);

  for (int i = 5; i > 0; i--) {
    ASSERT_EQ(stack.top(), i);
    stack.pop();
  }
  ASSERT_TRUE(stack.empty());
}

TEST(StackOperatorEqTest, OperatorEq) {
  s21::stack<int> st1;
  st1.push(1);
  st1.push(2);
  st1.push(3);
  s21::stack<int> st2 = std::move(st1);

  ASSERT_TRUE(st1.empty());
  ASSERT_EQ(st2.size(), 3);
  ASSERT_EQ(st2.top(), 3);
}

TEST(StackOperatorInsertManyTest, InsertMany) {
  s21::stack<int> st1;

  st1.insert_many_front(1, 2, 3, 4, 5, 6);

  ASSERT_TRUE(!st1.empty());
  ASSERT_EQ(st1.size(), 6);
  ASSERT_EQ(st1.top(), 6);
}

TEST(QueueConstr, ConsrDef) {
  s21::queue<int> my;
  std::queue<int> original;
  ASSERT_EQ(my.size(), original.size());
}

TEST(QueuePushSizeDoubl, PushSize) {
  s21::queue<double> my;
  std::queue<double> original;
  my.push(0.485);
  original.push(0.485);
  ASSERT_EQ(my.size(), original.size());
}

TEST(QueuePushSizeFrontConstrBack, ConstConstr) {
  s21::queue<int> my{1, 2, 3};
  std::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);
  ASSERT_EQ(my.size(), original.size());
  ASSERT_EQ(my.front(), original.front());
  ASSERT_EQ(my.back(), original.back());
}

TEST(QueueCharTest, Char) {
  s21::queue<char> my{'k', 'r', 'o', 'v'};
  std::queue<char> original;
  original.push('k');
  original.push('r');
  original.push('o');
  original.push('v');
  ASSERT_EQ(my.size(), original.size());
  ASSERT_EQ(my.front(), original.front());
  ASSERT_EQ(my.back(), original.back());
}

TEST(QueueCharTestSec, CharMove) {
  s21::queue<char> my{'k', 'r', 'o', 'v'};
  s21::queue<char> my1(std::move(my));
  std::queue<char> original;
  original.push('k');
  original.push('r');
  original.push('o');
  original.push('v');
  ASSERT_EQ(my1.size(), original.size());
  ASSERT_EQ(my1.front(), original.front());
  ASSERT_EQ(my1.back(), original.back());
}
TEST(QueueEmpty, QNotEmpty) {
  s21::queue<int> my{122, 445, 323, 0};
  ASSERT_EQ(false, my.empty());
}
TEST(QueueEmpty, QEmpty) {
  s21::queue<int> my;
  ASSERT_EQ(true, my.empty());
}

TEST(Queue, EQTestFront) {
  s21::queue<int> my{21, 0, 42};
  std::queue<char> original;
  original.push(21);
  original.push(0);
  original.push(42);
  ASSERT_EQ(my.front(), original.front());
}

TEST(Queue, EQTestback) {
  s21::queue<int> my{21, 0, 42};
  std::queue<char> original;
  original.push(21);
  original.push(0);
  original.push(42);
  ASSERT_EQ(my.back(), original.back());
}

TEST(QueueSTDS21EQ, EQSTDS21) {
  s21::queue<double> my;
  my.push(1.44);
  my.push(4.55);
  my.push(8.99);
  my.push(8.020);
  my.pop();
  std::queue<double> original;
  original.push(1.44);
  original.push(4.55);
  original.push(8.99);
  original.push(8.020);
  original.pop();

  ASSERT_EQ(my.size(), original.size());
  ASSERT_EQ(my.front(), original.front());
  ASSERT_EQ(my.back(), original.back());
}

TEST(QueueSwap, Swap) {
  s21::queue<char> my{'v', 's', 'p', 'o'};
  s21::queue<char> my1{'a', 'a', 'a'};
  my.swap(my1);
  std::queue<char> original;
  original.push('a');
  original.push('a');
  original.push('a');

  ASSERT_EQ(my.size(), original.size());
  ASSERT_EQ(my.front(), original.front());
  ASSERT_EQ(my.back(), original.back());
}

TEST(QueueInsertManyBackTest, InsertManyBack) {
  s21::queue<int> q1;
  q1.insert_many_back(1, 2, 3, 4, 5);

  ASSERT_EQ(q1.size(), 5);
  ASSERT_EQ(q1.front(), 1);
  ASSERT_EQ(q1.back(), 5);

  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(q1.front(), i + 1);
    q1.pop();
  }
  ASSERT_TRUE(q1.empty());
}

TEST(QueueInsertManyBackTest, InsertManyBackChar) {
  s21::queue<std::string> q2;
  q2.insert_many_back("hello");

  ASSERT_EQ(q2.size(), 1);
  ASSERT_EQ(q2.front(), "hello");
  ASSERT_EQ(q2.back(), "hello");

  q2.pop();
  ASSERT_TRUE(q2.empty());
}

TEST(QueueMoveAssignmentTest, MoveAssignment) {
  s21::queue<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);

  s21::queue<int> q2;
  q2 = std::move(q1);

  ASSERT_EQ(q2.size(), 3);
  ASSERT_EQ(q2.front(), 1);
  q2.pop();
  ASSERT_EQ(q2.front(), 2);
  q2.pop();
  ASSERT_EQ(q2.front(), 3);
  q2.pop();
  ASSERT_TRUE(q2.empty());
}

TEST(QueueTest, JustTest) {
  s21::queue<int> q5;
  q5.push(7);
  q5.push(8);
  q5.push(9);

  ASSERT_EQ(q5.size(), 3);
  ASSERT_EQ(q5.front(), 7);
  q5.pop();
  ASSERT_EQ(q5.front(), 8);
  q5.pop();
  ASSERT_EQ(q5.front(), 9);
  q5.pop();
  ASSERT_TRUE(q5.empty());
}

TEST(QueueTestCopy, CopyTest) {
  s21::queue<int> q1;
  q1.push(7);
  q1.push(8);
  q1.push(9);
  s21::queue<int> q2(q1);
  EXPECT_FALSE(q1.empty());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.front(), 7);
  EXPECT_EQ(q1.back(), 9);
  EXPECT_EQ(q2.front(), 7);
  EXPECT_EQ(q2.back(), 9);
}

TEST(QueueTest, MoreSwapTest) {
  std::queue<int> q1, q2;
  q1.push(1);
  q1.push(2);
  q2.push(3);
  q2.push(4);
  q1.swap(q2);
  EXPECT_EQ(q1.front(), 3);
  EXPECT_EQ(q1.back(), 4);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 2);
}