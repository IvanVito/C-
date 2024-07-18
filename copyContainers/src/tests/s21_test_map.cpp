#include "s21_test.h"

TEST(constructorsMap, defaultConstructor) {
  s21::map<int, std::string> myMap;
  std::map<int, std::string> originMap;

  EXPECT_TRUE(myMap.empty());
  EXPECT_TRUE(originMap.empty());
}

TEST(constructorsMap, initializerListIntString) {
  s21::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> originMap = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(true, myMap == originMap);
}

TEST(constructorsMap, initializerListStringFloat) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  std::map<std::string, float> originMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};

  EXPECT_EQ(true, myMap == originMap);
}

TEST(constructorsMap, initializerListStringFloatNE) {
  s21::map<std::string, float> myMap = {
      {"onee", 1.1}, {"twoo", 2.2}, {"threee", 3.3}};
  std::map<std::string, float> originMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};

  EXPECT_EQ(false, myMap == originMap);
}

TEST(constructorsMap, copyConstructor) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  s21::map<std::string, float> myMap2(myMap);

  EXPECT_EQ(true, myMap == myMap2);
}

TEST(constructorsMap, copyConstructorOverload) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  s21::map<std::string, float> myMap2;
  myMap2 = myMap;

  EXPECT_EQ(true, myMap == myMap2);
}

TEST(constructorsMap, moveConstructorOverload) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  s21::map<std::string, float> myMap2;
  myMap2 = std::move(myMap);

  EXPECT_EQ(3, myMap2.size());
}

TEST(constructorsMap, moveConstructor) {
  s21::map<std::string, float> myMap = {{"one", 1.1}, {"two", 2.2}};
  s21::map<std::string, float> myMap2 = std::move(myMap);

  EXPECT_EQ(2, myMap2.size());
}

TEST(insertMap, valueTypeInsert) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  std::pair<std::string, float> addPair("four", 4.4);
  myMap.insert(addPair);
  auto itMyMap = myMap.find("four");

  EXPECT_EQ(itMyMap->second, 4.4F);
}

TEST(insertMap, keyAndMappedInsert) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  myMap.insert("four", 4.4);
  auto itMyMap = myMap.find("four");

  EXPECT_EQ(itMyMap->second, 4.4F);
}

TEST(insertMap, insertNotAssign) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  auto flag = myMap.insert_or_assign("four", 4.4);
  auto itMyMap = myMap.find("four");

  EXPECT_EQ(itMyMap->second, 4.4F);
  EXPECT_EQ(flag.second, true);
}

TEST(insertMap, insertAssign) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  auto flag = myMap.insert_or_assign("three", 4.4);
  auto itMyMap = myMap.find("three");

  EXPECT_EQ(itMyMap->second, 4.4F);
  EXPECT_EQ(flag.second, false);
}

TEST(insertMap, mappedOk) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  auto itMyMap = myMap.at("three");

  EXPECT_EQ(itMyMap, 3.3F);
}

TEST(insertMap, mappedNotOk) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};

  EXPECT_THROW(myMap.at("four"), std::out_of_range);
}

TEST(insertMap, mappedOkOverload) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}};
  auto itMyMap = myMap["three"];

  EXPECT_EQ(itMyMap, 3.3F);
}

TEST(insertMap, mappedNotOkOverload) {
  s21::map<std::string, float> myMap = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}, {"four", 4.4}};
  auto itMyMap = myMap["five"];

  EXPECT_EQ(itMyMap, 0);
}

TEST(editTreeMap, merge) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::map<std::string, float> myMap2 = {{"three", 3.3}, {"four", 4.4}};
  s21::map<std::string, float> myMap3 = {
      {"one", 1.1}, {"two", 2.2}, {"three", 3.3}, {"four", 4.4}};
  myMap1.merge(myMap2);

  EXPECT_EQ(true, myMap3 == myMap1);
  EXPECT_EQ(true, myMap2.empty());
}

TEST(editTreeMap, mergeWithSameValues) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::map<std::string, float> myMap2 = {{"one", 1.2}, {"four", 4.4}};
  s21::map<std::string, float> myMap3 = {
      {"one", 1.1}, {"two", 2.2}, {"four", 4.4}};
  myMap1.merge(myMap2);
  auto it = myMap2.begin();

  EXPECT_EQ(true, myMap3 == myMap1);
  EXPECT_EQ("one", it->first);
  EXPECT_EQ(1.2F, it->second);
}

TEST(editTreeMap, mergeNe) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::map<std::string, float> myMap2 = {{"three", 3.3}};
  s21::map<std::string, float> myMap3 = {{"one", 1.1}, {"two", 2.2}};
  myMap1.merge(myMap2);

  EXPECT_EQ(false, myMap3 == myMap1);
  EXPECT_EQ(true, myMap2.empty());
}

TEST(editTreeMap, erase) {
  s21::map<int, float> myMap1 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  auto it = myMap1.begin();
  it++;
  it = myMap1.erase(it);
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, 3.3F);
}

TEST(editTreeMap, eraseOneValue) {
  s21::map<int, float> myMap1 = {{1, 1.1}};
  auto it = myMap1.begin();
  it = myMap1.erase(it);

  EXPECT_EQ(it, myMap1.end());
}

TEST(editTreeMap, eraseEnd) {
  s21::map<int, float> myMap1 = {{1, 1.1}};
  auto it = myMap1.begin();
  it++;
  it = myMap1.erase(it);

  EXPECT_EQ(it, myMap1.end());
}

TEST(editTreeMap, clearAndEmpty) {
  s21::map<int, float> myMap1;
  s21::map<int, float> myMap2 = {{1, 1.1}};
  s21::map<int, float> myMap3 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  s21::map<std::string, float> myMap4 = {{"one", 1.1}, {"two", 2.2}};
  myMap3.clear();
  myMap4.clear();

  EXPECT_EQ(true, myMap1.empty());
  EXPECT_EQ(false, myMap2.empty());
  EXPECT_EQ(true, myMap3.empty());
  EXPECT_EQ(true, myMap4.empty());
}

TEST(editTreeMap, swap) {
  s21::map<int, float> myMap1 = {{4, 4.4}};
  s21::map<int, float> myMap2 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  myMap1.swap(myMap2);

  EXPECT_EQ(true, myMap1.contains(1));
  EXPECT_EQ(true, myMap2.contains(4));
}

TEST(editTreeMap, swapEmpty) {
  s21::map<int, float> myMap1;
  s21::map<int, float> myMap2 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  myMap1.swap(myMap2);

  EXPECT_EQ(true, myMap1.contains(3));
  EXPECT_EQ(true, myMap2.empty());
}

TEST(findersMap, find) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::IteratorMap<std::string, float> it = myMap1.find("two");

  EXPECT_EQ(it->second, 2.2F);
}

TEST(findersMap, findNoExist) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::IteratorMap<std::string, float> it = myMap1.find("three");

  EXPECT_EQ(it, myMap1.end());
}

TEST(findersMap, constFind) {
  const s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::ConstIteratorMap<std::string, float> it = myMap1.find("two");

  EXPECT_EQ(it->second, 2.2F);
}

TEST(findersMap, constFindNoExist) {
  const s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  s21::ConstIteratorMap<std::string, float> it = myMap1.find("three");

  EXPECT_EQ(it, myMap1.end());
}

TEST(findersMap, contains) {
  const s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};

  EXPECT_EQ(true, myMap1.contains("one"));
  EXPECT_EQ(false, myMap1.contains("three"));
}

TEST(beginAndEndMap, begin) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  auto it = myMap1.begin();

  EXPECT_EQ(it->first, "one");
  EXPECT_EQ(it->second, 1.1F);
}

TEST(beginAndEndMap, constBegin) {
  const s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  auto it = myMap1.begin();

  EXPECT_EQ(it->first, "one");
  EXPECT_EQ(it->second, 1.1F);
}

TEST(beginAndEndMap, end) {
  s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  auto it = myMap1.end();
  it--;
  it--;

  EXPECT_EQ(it->first, "one");
}

TEST(beginAndEndMap, constEnd) {
  const s21::map<std::string, float> myMap1 = {{"one", 1.1}, {"two", 2.2}};
  auto it = myMap1.end();
  --it;

  EXPECT_EQ(it->first, "two");
}

TEST(sizeMap, size) {
  s21::map<int, float> myMap1;
  s21::map<int, float> myMap2 = {{1, 1.1}};
  s21::map<int, float> myMap3 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  s21::map<std::string, float> myMap4 = {{"one", 1.1}, {"two", 2.2}};

  EXPECT_EQ(0, myMap1.size());
  EXPECT_EQ(1, myMap2.size());
  EXPECT_EQ(3, myMap3.size());
  EXPECT_NE(4, myMap3.size());
  EXPECT_EQ(2, myMap4.size());
}

TEST(sizeMap, maxSize) {
  s21::map<int, float> myMap1;
  s21::map<int, float> myMap2 = {{1, 1.1}};
  s21::map<int, float> myMap3 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  s21::map<std::string, float> myMap4 = {{"one", 1.1}, {"two", 2.2}};

  std::map<int, float> originMap1;
  std::map<int, float> originMap2 = {{1, 1.1}};
  std::map<int, float> originMap3 = {{1, 1.1}, {2, 2.2}, {3, 3.3}};
  std::map<std::string, float> originMap4 = {{"one", 1.1}, {"two", 2.2}};

  EXPECT_EQ(originMap1.max_size(), myMap1.max_size());
  EXPECT_EQ(originMap2.max_size(), myMap2.max_size());
  EXPECT_EQ(originMap3.max_size(), myMap3.max_size());
  EXPECT_NE(4, myMap3.max_size());
  EXPECT_NE(originMap4.max_size(), myMap4.max_size());
}

TEST(InsertManyMap, standart) {
  s21::map<int, std::string> myMap1;
  myMap1.insert_many(1, "one", 2, "two", 3, "three", 4, "four");
  s21::map<int, std::string> myMap2 = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

  EXPECT_EQ(true, myMap1 == myMap2);
}

TEST(InsertManyMap, fiveValues) {
  s21::map<int, std::string> myMap1;
  EXPECT_THROW(myMap1.insert_many(1, "one", 2, "two", 3, "three", 4),
               std::invalid_argument);
}

TEST(InsertManyMap, nullValues) {
  s21::map<int, std::string> myMap1;
  EXPECT_THROW(myMap1.insert_many(), std::invalid_argument);
}