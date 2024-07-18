#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

// Конструкторы

TEST(Test_1__Constructors, Default) {
  S21Matrix m1;
  EXPECT_EQ(3, m1.GetRows());
  EXPECT_EQ(3, m1.GetCols());
}

TEST(Test_1__Constructors, WithParametrs) {
  S21Matrix m1(10, 10);
  EXPECT_EQ(10, m1.GetRows());
  EXPECT_EQ(10, m1.GetCols());
}

TEST(Test_1__Constructors, CopyConstructor) {
  S21Matrix m1(4, 3);
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9 11.1 12.2 13.3");
  S21Matrix m2(m1);
  EXPECT_EQ(SUCCESS, m1 == m2);
}

TEST(Test_1__Constructors, MoveConstructor) {
  S21Matrix m1(4, 3);
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9 11.1 12.2 13.3");
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(0, m1.GetRows());
  EXPECT_EQ(0, m1.GetCols());
  EXPECT_EQ(13.3, m2(3, 2));
}

TEST(Test_1__Constructors, Exceptions) {
  EXPECT_THROW(S21Matrix m1(0, 5), std::invalid_argument);
}

// Функции

TEST(Test_2__Functions, EqMatrix0) {
  S21Matrix m1, m2;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  m2.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  EXPECT_EQ(SUCCESS, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix1) {
  S21Matrix m1, m2;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 0");
  m2.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  EXPECT_EQ(FAILURE, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix2) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1.FillMatrixStr("1.132 2.6378 3.1214 4.24214");
  m2.FillMatrixStr("1.132 2.6378 3.1214 4.24214");
  EXPECT_EQ(SUCCESS, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix3) {
  S21Matrix m1, m2;
  m1.FillMatrixStr("1.132 2.6378 3.1214 4.24214");
  m2.FillMatrixStr("1.132 2.6379 3.1214 4.24214");
  EXPECT_EQ(FAILURE, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix4) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222222 3.3333333 4.4444444");
  m2.FillMatrixStr("1.1111111 2.2222222 3.3333333 4.4444444");
  EXPECT_EQ(SUCCESS, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix5) {
  S21Matrix m1, m2;
  m1.FillMatrixStr("1.1111111 2.2222222 3.3333333 4.4444444");
  m2.FillMatrixStr("1.1111111 2.2222225 3.3333333 4.4444444");
  EXPECT_EQ(FAILURE, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix6) {
  S21Matrix m1(2, 3), m2(3, 2);
  m1.FillMatrixStr("1.132 2.6378 3.1214 4.24214 1 2");
  m2.FillMatrixStr("1.132 2.6378 3.1214 4.24214 1 2");
  EXPECT_EQ(FAILURE, m1 == m2);
}

TEST(Test_2__Functions, EqMatrix7) {
  EXPECT_THROW(S21Matrix m1(0, 2), std::invalid_argument);
}

TEST(Test_3__Functions, SumMatrix0) {
  S21Matrix m1, m2, ExpRes;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  m2.FillMatrixStr("9 8 7 6 5 4 3 2 1");
  ExpRes.FillMatrixStr("10 10 10 10 10 10 10 10 10");
  m1.SumMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_3__Functions, SumMatrix1) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 3.3 0.1234567");
  m2.FillMatrixStr("9.9999999 8.8888881 3.7 0.9876543");
  ExpRes.FillMatrixStr("11.1111110 11.1111109 7.0000000 1.1111110");
  m1.SumMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_3__Functions, SumMatrix2) {
  S21Matrix m1(1, 2), m2(1, 1);
  m1.FillMatrixStr("1.1111111 2.2222228");
  m2.FillMatrixStr("9.9999999");
  EXPECT_THROW(m1.SumMatrix(m2), std::out_of_range);
}

TEST(Test_3__Functions, SumMatrix3) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 0.0000001 -0.0000001");
  m2.FillMatrixStr("9.9999999 8.8888881 0.0000001 -0.0000001");
  ExpRes.FillMatrixStr("11.1111110 11.1111109 0.0000002 -0.0000002");
  m1.SumMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_3__Functions, SumMatrix4) {
  S21Matrix m1(1, 1), m2(1, 1), ExpRes(1, 1);
  m1.FillMatrixStr("0.0000001");
  m2.FillMatrixStr("9.9999999");
  ExpRes.FillMatrixStr("10");
  m1.SumMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_3__Functions, SumMatrix5) {
  S21Matrix m1(1, 1), m2(1, 1), ExpRes(1, 1);
  m1.FillMatrixStr("0.0000002");
  m2.FillMatrixStr("9.9999999");
  ExpRes.FillMatrixStr("10");
  m1.SumMatrix(m2);
  EXPECT_EQ(FAILURE, m1 == ExpRes);
}

TEST(Test_4__Functions, SubMatrix0) {
  S21Matrix m1, m2, ExpRes;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  m2.FillMatrixStr("9 8 7 6 5 4 3 2 1");
  ExpRes.FillMatrixStr("-8 -6 -4 -2 0 2 4 6 8");
  m1.SubMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_4__Functions, SubMatrix1) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 3.3 0.1234567");
  m2.FillMatrixStr("9.9999999 8.8888881 3.7 0.9876543");
  ExpRes.FillMatrixStr("-8.8888888 -6.6666653 -0.4 -0.8641976");
  m1.SubMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_4__Functions, SubMatrix2) {
  S21Matrix m1(1, 2), m2(1, 2), ExpRes(1, 2);
  m1.FillMatrixStr("1.1111111  2.2222228");
  m2.FillMatrixStr("9.9999999 8.8888881");
  ExpRes.FillMatrixStr("-8.8888888 -6.6666653");
  m1.SubMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_4__Functions, SubMatrix3) {
  S21Matrix m1(1, 2), m2(2, 1);
  m1.FillMatrixStr("1.1111111  2.2222228");
  m2.FillMatrixStr("9.9999999 8.8888881");
  EXPECT_THROW(m1.SubMatrix(m2), std::out_of_range);
}

TEST(Test_4__Functions, SubMatrix4) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 0.0000001 -0.0000001");
  m2.FillMatrixStr("9.9999999 8.8888881 0.0000001 -0.0000001");
  ExpRes.FillMatrixStr("-8.8888888 -6.6666653 0.0000000 -0.0000000");
  m1.SubMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_4__Functions, SubMatrix5) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 0.0000001 -0.0000001");
  m2.FillMatrixStr("9.9999998 8.8888881 0.0000001 -0.0000001");
  ExpRes.FillMatrixStr("-8.8888888 -6.6666653 0.0000000 -0.0000000");
  m1.SubMatrix(m2);
  EXPECT_EQ(FAILURE, m1 == ExpRes);
}

TEST(Test_5__Functions, MulNumber0) {
  S21Matrix m1, ExpRes;
  double number = 7;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  ExpRes.FillMatrixStr("7 14 21 28 35 42 49 56 63");
  m1.MulNumber(number);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_5__Functions, MulNumber1) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  double number = 7;
  m1.FillMatrixStr("1.1111111 0.5555555 0.1 0");
  ExpRes.FillMatrixStr("7.7777777 3.8888885 0.7000000 0.0000000");
  m1.MulNumber(number);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_5__Functions, MulNumber2) {
  S21Matrix m1(1, 2), ExpRes(1, 2);
  double number = 7;
  m1.FillMatrixStr("1.1111111 0.5555555");
  ExpRes.FillMatrixStr("7.7777777 3.8888885");
  m1.MulNumber(number);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_5__Functions, MulNumber3) {
  S21Matrix m1(1, 1), ExpRes(1, 1);
  double number = 0.0001;
  m1.FillMatrixStr("0.001");
  ExpRes.FillMatrixStr("0.0000001");
  m1.MulNumber(number);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_5__Functions, MulNumber4) {
  S21Matrix m1(1, 1), ExpRes(1, 1);
  double number = 0.0001;
  m1.FillMatrixStr("0.01");
  ExpRes.FillMatrixStr("0.0000001");
  m1.MulNumber(number);
  EXPECT_EQ(FAILURE, m1 == ExpRes);
}

TEST(Test_6__Functions, MulMatrix0) {
  S21Matrix m1(3, 2), m2(2, 3), ExpRes(3, 3);
  m1.FillMatrixStr("1 4 2 5 3 6");
  m2.FillMatrixStr("1 -1 1 2 3 4");
  ExpRes.FillMatrixStr("9 11 17 12 13 22 15 15 27");
  m1.MulMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_6__Functions, MulMatrix1) {
  S21Matrix m1(3, 2), m2(2, 3), ExpRes(3, 3);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  m2.FillMatrixStr("-1.1 -1.01 0 0 1 0.0000001");
  ExpRes.FillMatrixStr(
      "-1.10000011 2.993999899 0.0000004004 0 -3.3 -0.00000033 -36.3 -27.33 "
      "0.0000006");
  m1.MulMatrix(m2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_6__Functions, MulMatrix2) {
  S21Matrix m1(3, 2), m2(2, 3), ExpRes(3, 3);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  m2.FillMatrixStr("-1.1 -1.01 0 0 1 0.0000001");
  ExpRes.FillMatrixStr(
      "-1.10000011 2.993999899 1 0 -3.3 -0.00000033 -36.3 -27.33 "
      "0.0000006");
  m1.MulMatrix(m2);
  EXPECT_EQ(FAILURE, m1 == ExpRes);
}

TEST(Test_6__Functions, MulMatrix3) {
  S21Matrix m1(3, 2), m2(3, 2);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  m2.FillMatrixStr("-1.1 -1.01 0 0 1 0.0000001");
  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

TEST(Test_7__Functions, Transpose0) {
  S21Matrix m1, ExpRes;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  ExpRes.FillMatrixStr("1 4 7 2 5 8 3 6 9");
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_7__Functions, Transpose1) {
  S21Matrix m1, ExpRes;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  ExpRes.FillMatrixStr("1 4 7 2 5 8 3 6 91");
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(FAILURE, res == ExpRes);
}

TEST(Test_7__Functions, Transpose2) {
  S21Matrix m1(2, 3), ExpRes(3, 2);
  m1.FillMatrixStr("1.2222221 2.1111112 0 0.1111112 1234567 1234567.1234567");
  ExpRes.FillMatrixStr(
      "1.2222221 0.1111112 2.1111112 1234567 0 1234567.1234567");
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_7__Functions, Transpose3) {
  S21Matrix m1(3, 2), ExpRes(2, 3);
  m1.FillMatrixStr("1.2222221 2.1111112 0 0.1111112 1234567 1234567.1234567");
  ExpRes.FillMatrixStr(
      "1.2222221 0 1234567 2.1111112 0.1111112 1234567.1234567");
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_7__Functions, Transpose4) {
  S21Matrix m1(3, 2), ExpRes(2, 3);
  m1.FillMatrixStr("1.2222221 2.1111112 0 0.1111112 1234567 1234567.1234567");
  ExpRes.FillMatrixStr(
      "1.2222221 0 1234567 2.1111112 0.1111112 1234567.1234567");
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_7__Functions, Transpose5) {
  S21Matrix m1(1, 1), ExpRes(1, 1);
  m1.FillMatrixStr("1.2222221");
  ExpRes.FillMatrixStr("1.2222221");
  S21Matrix res = m1.Transpose();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_8__Functions, Determinant0) {
  S21Matrix m1;
  double res = 0, ExpRes = 0;
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant1) {
  S21Matrix m1;
  double res = 0, ExpRes = 61.171861;
  m1.FillMatrixStr("1.22 9.12 4.71 2.01 0.001 5.1 3.5 7.1 6.8");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant2) {
  S21Matrix m1;
  double res = 0, ExpRes = 0;
  m1.FillMatrixStr("0 0 0 2.01 0.001 5.1 3.5 7.1 6.8");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant3) {
  S21Matrix m1;
  double res = 0, ExpRes = 0;
  m1.FillMatrixStr("0 9.12 4.71 0 0.001 5.1 0 7.1 6.8");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant4) {
  S21Matrix m1(2, 2);
  double res = 0, ExpRes = -6;
  m1.FillMatrixStr("2 4 6 9");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant5) {
  S21Matrix m1(2, 2);
  double res = 0, ExpRes = -12.1063958;
  m1.FillMatrixStr("2.325 4.1356 6.6864 6.6864");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant6) {
  S21Matrix m1(4, 4);
  double res = 0, ExpRes = 789;
  m1.FillMatrixStr("4 7 8 8 2 4 0 -1 1 7 -4 1 3 4 1 8");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, MulMatrix7) {
  S21Matrix m1(3, 4);
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9 10 11 12");
  EXPECT_THROW(m1.Determinant(), std::out_of_range);
}

TEST(Test_8__Functions, Determinant8) {
  S21Matrix m1(1, 1);
  double res = 0, ExpRes = -7;
  m1.FillMatrixStr("-7");
  res = m1.Determinant();
  EXPECT_EQ(SUCCESS, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_8__Functions, Determinant9) {
  S21Matrix m1(2, 2);
  double res = 0, ExpRes = 0;
  m1.FillMatrixStr("2.325 4.1356 6.6864 6.6864");
  res = m1.Determinant();
  EXPECT_EQ(FAILURE, std::fabs(res - ExpRes) <= ACCURACY);
}

TEST(Test_9__Functions, CalcComplements0) {
  S21Matrix m1, ExpRes;
  m1.FillMatrixStr("1 2 3 0 4 2 5 2 1");
  ExpRes.FillMatrixStr("0 10 -20 4 -14 8 -8 -2 4");
  S21Matrix res = m1.CalcComplements();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_9__Functions, CalcComplements1) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1 2 4 3");
  ExpRes.FillMatrixStr("3 -4 -2 1");
  S21Matrix res = m1.CalcComplements();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_9__Functions, CalcComplements2) {
  S21Matrix m1, ExpRes;
  m1.FillMatrixStr("1.234 2.464 5.8654 9.142 5.325 0 1.675 3.6778 9.999999");
  ExpRes.FillMatrixStr(
      "53.2499947 -91.4199909 24.7030726 -3.0682294 2.5154538 -0.4112052 "
      "-31.2332550 53.6214868 -15.9548380");
  S21Matrix res = m1.CalcComplements();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_9__Functions, CalcComplements3) {
  S21Matrix m1(4, 4), ExpRes(4, 4);
  m1.FillMatrixStr("2.5 1 8 0 2 5 7 7.8 1.24 25 100 34.4 5 6 111 5.232");
  ExpRes.FillMatrixStr(
      "1018.2 8258.22176 -240.6064 -5338.88 2690.4 -6913.90144 "
      "23.48768 4859.38 -664.056 1844.652 -23.064 -991.5 355.2 -1821.024 "
      "116.628 971.58");
  S21Matrix res = m1.CalcComplements();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_9__Functions, CalcComplements4) {
  S21Matrix m1(3, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1 2 4 3 4 5 6");
  ExpRes.FillMatrixStr("3 -4 -2 1");
  EXPECT_THROW(m1.CalcComplements(), std::out_of_range);
}

TEST(Test_9__Functions, CalcComplements5) {
  S21Matrix m1(1, 1), ExpRes(1, 1);
  m1.FillMatrixStr("-7");
  ExpRes.FillMatrixStr("7");
  S21Matrix res = m1.CalcComplements();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_10__Functions, Inverse0) {
  S21Matrix m1, ExpRes;
  m1.FillMatrixStr("2 5 7 6 3 4 5 -2 -3");
  ExpRes.FillMatrixStr("1 -1 1 -38 41 -34 27 -29 24");
  S21Matrix res = m1.InverseMatrix();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_10__Functions, Inverse1) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("2.57 5.1312367 9.9 100");
  ExpRes.FillMatrixStr("0.4849643 -0.0248847 -0.0480115 0.0124636");
  S21Matrix res = m1.InverseMatrix();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_10__Functions, Inverse2) {
  S21Matrix m1(4, 4), ExpRes(4, 4);
  m1.FillMatrixStr("2.5 1 8 0 2 5 7 7.8 1.24 25 100 34.4 5 6 111 5.232");
  ExpRes.FillMatrixStr(
      "0.1146767 0.3030115 -0.0747906 0.0400051 0.9300982 -0.7786915 0.2077575 "
      "-0.2050964 -0.0270988 0.0026453 -0.0025976 0.0131355 -0.6013017 "
      "0.5472971 -0.1116696 0.1094261");
  S21Matrix res = m1.InverseMatrix();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

TEST(Test_10__Functions, Inverse3) {
  S21Matrix m1(3, 2);
  m1.FillMatrixStr("2.57 5.1312367 9.9 100 1 2");
  EXPECT_THROW(m1.InverseMatrix(), std::out_of_range);
}

TEST(Test_10__Functions, Inverse4) {
  S21Matrix m1(3, 3);
  m1.FillMatrixStr("1 2 3 4 5 6 7 8 9");
  EXPECT_THROW(m1.InverseMatrix(), std::invalid_argument);
}

TEST(Test_10__Functions, Inverse5) {
  S21Matrix m1, ExpRes;
  m1.FillMatrixStr("2 5 7 6 3 4 5 -2 -3");
  ExpRes.FillMatrixStr("0 -1 1 -38 41 -34 27 -29 24");
  S21Matrix res = m1.InverseMatrix();
  EXPECT_EQ(FAILURE, res == ExpRes);
}

TEST(Test_10__Functions, Inverse6) {
  S21Matrix m1(1, 1), ExpRes(1, 1);
  m1.FillMatrixStr("-7");
  ExpRes.FillMatrixStr("-0.1428571");
  S21Matrix res = m1.InverseMatrix();
  EXPECT_EQ(SUCCESS, res == ExpRes);
}

// ############################### #######################################
// ###############################Перегрузки#######################################
// ############################### #######################################

TEST(Test_11__Overloads, Assignment) {
  S21Matrix m1, m2(4, 4);
  m1.FillMatrixStr("2 5 7 6 3.000003 4 5 -2 -3");
  m2 = m1;
  EXPECT_EQ(SUCCESS, m2 == m1);
}

TEST(Test_11__Overloads, Equal) {
  S21Matrix m1, m2;
  m1.FillMatrixStr("2 5 7 6 3.000003 4 5 -2 -3");
  m2.FillMatrixStr("2 5 7 6 3.000003 4 5 -2 -3");
  EXPECT_EQ(SUCCESS, m2 == m1);
}

TEST(Test_11__Overloads, Plus) {
  S21Matrix m1, m2, ExpRes;
  m1.FillMatrixStr("1.1111111 2.2222228 0.0000001 -0.0000001");
  m2.FillMatrixStr("9.9999999 8.8888881 0.0000001 -0.0000001");
  ExpRes.FillMatrixStr("11.1111110 11.1111109 0.0000002 -0.0000002");
  EXPECT_EQ(SUCCESS, (m1 + m2) == ExpRes);
}

TEST(Test_11__Overloads, PlusEqual) {
  S21Matrix m1, m2, ExpRes;
  m1.FillMatrixStr("1.1111111 2.2222228 0.0000001 -0.0000001");
  m2.FillMatrixStr("9.9999999 8.8888881 0.0000001 -0.0000001");
  ExpRes.FillMatrixStr("11.1111110 11.1111109 0.0000002 -0.0000002");
  m1 += m2;
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_11__Overloads, Minus) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 3.3 0.1234567");
  m2.FillMatrixStr("9.9999999 8.8888881 3.7 0.9876543");
  ExpRes.FillMatrixStr("-8.8888888 -6.6666653 -0.4 -0.8641976");
  EXPECT_EQ(SUCCESS, (m1 - m2) == ExpRes);
}

TEST(Test_11__Overloads, MinusEqual) {
  S21Matrix m1(2, 2), m2(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.1111111 2.2222228 3.3 0.1234567");
  m2.FillMatrixStr("9.9999999 8.8888881 3.7 0.9876543");
  ExpRes.FillMatrixStr("-8.8888888 -6.6666653 -0.4 -0.8641976");
  m1 -= m2;
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_11__Overloads, MulNumberMatrix) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  double number = 7;
  m1.FillMatrixStr("1.1111111 0.5555555 0.1 0");
  ExpRes.FillMatrixStr("7.7777777 3.8888885 0.7000000 0.0000000");
  EXPECT_EQ(SUCCESS, (number * m1) == ExpRes);
}

TEST(Test_11__Overloads, MulMatrixNumber) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  double number = 7;
  m1.FillMatrixStr("1.1111111 0.5555555 0.1 0");
  ExpRes.FillMatrixStr("7.7777777 3.8888885 0.7000000 0.0000000");
  EXPECT_EQ(SUCCESS, (m1 * number) == ExpRes);
}

TEST(Test_11__Overloads, MulEqMatrixNumber) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  double number = 7;
  m1.FillMatrixStr("1.1111111 0.5555555 0.1 0");
  ExpRes.FillMatrixStr("7.7777777 3.8888885 0.7000000 0.0000000");
  m1 *= number;
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_11__Overloads, MulMatrixMatrix) {
  S21Matrix m1(3, 2), m2(2, 3), ExpRes(3, 3);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  m2.FillMatrixStr("-1.1 -1.01 0 0 1 0.0000001");
  ExpRes.FillMatrixStr(
      "-1.10000011 2.993999899 0.0000004004 0 -3.3 -0.00000033 -36.3 -27.33 "
      "0.0000006");
  EXPECT_EQ(SUCCESS, (m1 * m2) == ExpRes);
}

TEST(Test_11__Overloads, MulEqMatrixMatrix) {
  S21Matrix m1(3, 2), m2(2, 3), ExpRes(3, 3);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  m2.FillMatrixStr("-1.1 -1.01 0 0 1 0.0000001");
  ExpRes.FillMatrixStr(
      "-1.10000011 2.993999899 0.0000004004 0 -3.3 -0.00000033 -36.3 -27.33 "
      "0.0000006");
  m1 *= m2;
  EXPECT_EQ(SUCCESS, (m1 == ExpRes));
}

TEST(Test_11__Overloads, Index) {
  S21Matrix m1(3, 2);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  EXPECT_EQ(SUCCESS, m1(2, 1) == 6);
}

TEST(Test_11__Overloads, BrokenIndex) {
  S21Matrix m1(3, 2);
  EXPECT_THROW(m1(3, 1), std::out_of_range);
}

TEST(Test_12__Mutator, GreaterSize) {
  S21Matrix m1(3, 2), ExpRes;
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  ExpRes.FillMatrixStr("1.0000001 4.004 0 0 -3.3 0 33 6 0");
  m1.Mutator(3, 3);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_12__Mutator, LessSize) {
  S21Matrix m1(3, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3 33 6");
  ExpRes.FillMatrixStr("1.0000001 4.004 0 -3.3");
  m1.Mutator(2, 2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_12__Mutator, EqualSize) {
  S21Matrix m1(2, 2), ExpRes(2, 2);
  m1.FillMatrixStr("1.0000001 4.004 0 -3.3");
  ExpRes.FillMatrixStr("1.0000001 4.004 0 -3.3");
  m1.Mutator(2, 2);
  EXPECT_EQ(SUCCESS, m1 == ExpRes);
}

TEST(Test_12__Mutator, Throw) {
  S21Matrix m1(2, 2);
  EXPECT_THROW(m1.Mutator(0, 2), std::invalid_argument);
}

int main() {
  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
