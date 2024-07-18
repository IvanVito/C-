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
  int GetRows() const;
  int GetCols() const;
  void Mutator(const int rows, const int cols);

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
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& o);
  void SubMatrix(const S21Matrix& o);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  // Вспомогательные функции
  void AllocateMem();
  void DeleteMatrix();
  void PrintMatrix();
  void FillMatrixStr(const std::string& src);  // Заполнение матрицы из строки
  void DifSize(const S21Matrix& o);
  void NotMul(const S21Matrix& o);
  void NotSquare();

  /**
   * @brief Меняет строки местами, если ноль на главной диагонали
   * @param CopyMatrix Копия исходной матрицы
   * @param count Текущая строка, в которой идет проверка на ноль
   * @param Determ При перестановке строк детерминант меняет знак
   * @return Либо удалось поменять строки и получить на главной диагонали не
   * ноль (NotNull = count), либо NotNull = -1
   */
  int SearchNotNull(S21Matrix& CopyMatrix, int count, double& Determ);

  /**
   * @brief Функция зануляет элементы ниже главной диагонали
   * @param CopyMatrix Копия матрицы, подготовленная для зануления элементов
   * ниже count
   * @param count Индекс текущей строки
   */
  void GausStr(S21Matrix& CopyMatrix, int count);

  /**
   * @brief Выеркивает строку и столбец из исходной матрицы, создавая матрицу на
   * размерность меньше
   * @param IndexRow Индекс строки вычеркиваемого элемента
   * @param IndexColumn Индекс столбца вычеркиваемого элемента
   * @param origin Оригинальная матрица
   * @param temp Временная матрица
   */
  void CrossOff(int IndexRow, int IndexColumn, const S21Matrix& origin,
                S21Matrix& temp);
};

#endif  // __S21MATRIX_H__
