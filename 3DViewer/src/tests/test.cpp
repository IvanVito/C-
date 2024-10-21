#include "../back/affinTrans.h"
#include "../back/facade.h"
#include "../back/parser.h"
#include "gtest/gtest.h"

TEST(testsParser, readOkFile) {
  s21::Facade obj;
  obj.parseFile("models/cube.obj");
  EXPECT_EQ(8, obj.getSizeVertexes());
  EXPECT_EQ(12, obj.getSizePoligons());
}

TEST(testsParser, readNotOkFile) {
  s21::Facade obj;
  obj.parseFile("models/brokenCube.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(testsParser, doubleOpen) {
  s21::Facade obj;
  obj.parseFile("models/cube.obj");
  EXPECT_EQ(8, obj.getSizeVertexes());
  EXPECT_EQ(12, obj.getSizePoligons());
  obj.parseFile("models/cube.obj");
  EXPECT_EQ(8, obj.getSizeVertexes());
  EXPECT_EQ(12, obj.getSizePoligons());
}

TEST(testsParser, doubleOpenNotOkFile) {
  s21::Facade obj;
  obj.parseFile("models/brokenCube.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
  obj.parseFile("models/brokenCube.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(testsParser, openOkOpenBroken) {
  s21::Facade obj;
  obj.parseFile("models/cube.obj");
  EXPECT_EQ(8, obj.getSizeVertexes());
  EXPECT_EQ(12, obj.getSizePoligons());
  obj.parseFile("models/brokenCube.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(testsParser, openBrokenOpenOk) {
  s21::Facade obj;
  obj.parseFile("models/cube.obj");
  EXPECT_EQ(8, obj.getSizeVertexes());
  EXPECT_EQ(12, obj.getSizePoligons());
  obj.parseFile("models/brokenCube.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(testsParser, openNotExistFile) {
  s21::Facade obj;
  obj.parseFile("models/notExist.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(testsParser, vertexLetter) {
  s21::Facade obj;
  obj.parseFile("models/cubeVertexLetter.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(testsParser, poligonLetter) {
  s21::Facade obj;
  obj.parseFile("models/cubePoligonLetter.obj");
  EXPECT_EQ(0, obj.getSizeVertexes());
  EXPECT_EQ(0, obj.getSizePoligons());
}

TEST(affinsTrans, scale) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-3, -3, 0}, {3, -3, 0}, {3, 3, 0.0}, {-3, 3, 0.0}};

  obj1.scale(3);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, scaleDouble) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-3.3, -3.3, 0.0}, {3.3, -3.3, 0.0}, {3.3, 3.3, 0.0}, {-3.3, 3.3, 0.0}};

  obj1.scale(3.3);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, scaleX) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-3.3, -1, 0.0}, {3.3, -1, 0.0}, {3.3, 1, 0.0}, {-3.3, 1, 0.0}};

  obj1.scaleXYZ(3.3);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, scaleY) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, -3.3, 0.0}, {1, -3.3, 0.0}, {1, 3.3, 0.0}, {-1, 3.3, 0.0}};

  obj1.scaleXYZ(1, 3.3);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, scaleXZero) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {0.0, -1, 0.0}, {0.0, -1, 0.0}, {0.0, 1, 0.0}, {0.0, 1, 0.0}};

  obj1.scaleXYZ(0);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, Rotate90X) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, 0.0, -1}, {1, 0.0, -1}, {1, 0.0, 1}, {-1, 0.0, 1}};

  obj1.rotate(90);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, Rotate720X) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, -1, 0.0}, {1, -1, 0.0}, {1, 1, 0.0}, {-1, 1, 0.0}};

  obj1.rotate(720);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, Rotate0Y) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, -1, 0.0}, {1, -1, 0.0}, {1, 1, 0.0}, {-1, 1, 0.0}};

  obj1.rotate(0, 'y');

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, Rotate180Z) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {1, 1, 0.0}, {-1, 1, 0.0}, {-1, -1, 0.0}, {1, -1, 0.0}};

  obj1.rotate(180, 'z');

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, Move1X) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {0.0, -1, 0.0}, {2, -1, 0.0}, {2, 1, 0.0}, {0.0, 1, 0.0}};

  obj1.move(1);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, Move1Point5Y) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, 0.5, 0.0}, {1, 0.5, 0.0}, {1, 2.5, 0.0}, {-1, 2.5, 0.0}};

  obj1.move(0, 1.5);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(affinsTrans, MoveX1Y1ZMinus5) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {0.0, 0.0, -5}, {2, 0.0, -5}, {2, 2, -5}, {0.0, 2, -5}};

  obj1.move(1, 1, -5);

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(otherTrans, centerX5) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, -1, 0.0}, {1, -1, 0.0}, {1, 1, 0.0}, {-1, 1, 0.0}};

  obj1.move(5);
  obj1.centerModel();

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

TEST(otherTrans, centerX5Y1Point5ZMinus8) {
  s21::Facade obj1;
  obj1.parseFile("models/cubeTest.obj");

  std::vector<std::vector<double>> obj2 = {
      {-1, -1, 0.0}, {1, -1, 0.0}, {1, 1, 0.0}, {-1, 1, 0.0}};

  obj1.move(5, 1.5, -8);
  obj1.centerModel();

  for (size_t i = 0; i < obj2.size(); i++) {
    EXPECT_NEAR(obj2[i][0], obj1.object_.vertexes_[i][0], 1e-6);
    EXPECT_NEAR(obj2[i][1], obj1.object_.vertexes_[i][1], 1e-6);
    EXPECT_NEAR(obj2[i][2], obj1.object_.vertexes_[i][2], 1e-6);
  }
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
