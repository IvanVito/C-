#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#define ACCURACY 1e-7  // Точность
#define SUCCESS 1
#define FAILURE 0

class S21Matrix {
 private:
  // атрибуты
  int rows_, cols_;
  double** matrix_;

 public:
  // Конструкторы
  S21Matrix();                    // Стандартый конструктор
  S21Matrix(int rows, int cols);  // Параметризованный конструктор
  S21Matrix(const S21Matrix& o);  // Конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор перемещения
  ~S21Matrix();                           // Деструктор

  // Аксессоры и мутатор
  int getRows() const;
  int getCols() const;
  void mutator(const int rows, const int cols);

  // Перегрузки
  void operator=(const S21Matrix& o);
  friend bool operator==(const S21Matrix& lm, const S21Matrix& rm);
  double& operator()(int row, int col);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix& operator*=(double o);
  friend S21Matrix operator*(double o, const S21Matrix& matrix);
  friend S21Matrix operator*(const S21Matrix& matrix, double o);

  // Методы
  bool eqMatrix(const S21Matrix& other) const;
  void sumMatrix(const S21Matrix& o);
  void subMatrix(const S21Matrix& o);
  void mulNumber(const double num);
  void mulMatrix(const S21Matrix& other);
  S21Matrix transpose();
  double determinant();
  S21Matrix calcComplements();
  S21Matrix inverseMatrix();

  // Вспомогательные функции
  void allocateMem();
  void deleteMatrix();
  void printMatrix();
  void fillMatrixStr(const std::string& src);  // Заполнение матрицы из строки
  void difSize(const S21Matrix& o);
  void notMul(const S21Matrix& o);
  void notSquare();

  /**
   * @brief Меняет строки местами, если ноль на главной диагонали
   * @param copyMatrix Копия исходной матрицы
   * @param count Текущая строка, в которой идет проверка на ноль
   * @param determ При перестановке строк детерминант меняет знак
   * @return Либо удалось поменять строки и получить на главной диагонали не
   * ноль (NotNull = count), либо NotNull = -1
   */
  int searchNotNull(S21Matrix& copyMatrix, int count, double& determ);

  /**
   * @brief Функция зануляет элементы ниже главной диагонали
   * @param copyMatrix Копия матрицы, подготовленная для зануления элементов
   * ниже count
   * @param count Индекс текущей строки
   */
  void gausStr(S21Matrix& copyMatrix, int count);

  /**
   * @brief Выеркивает строку и столбец из исходной матрицы, создавая матрицу на
   * размерность меньше
   * @param indexRow Индекс строки вычеркиваемого элемента
   * @param indexColumn Индекс столбца вычеркиваемого элемента
   * @param origin Оригинальная матрица
   * @param temp Временная матрица
   */
  void crossOff(int indexRow, int indexColumn, const S21Matrix& origin,
                S21Matrix& temp);
};

#endif  // __S21MATRIX_H__
