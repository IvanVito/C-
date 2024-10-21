#include "s21MatrixOop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Недопустимое значение строки или колонки");
  allocateMem();
}

S21Matrix::S21Matrix(const S21Matrix& o)
    : rows_(o.rows_), cols_(o.cols_), matrix_(nullptr) {
  allocateMem();
  for (int rows = 0; rows < rows_; rows++)
    std::memmove(matrix_[rows], o.matrix_[rows], o.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

void S21Matrix::allocateMem() {
  if (matrix_ != nullptr) deleteMatrix();
  matrix_ = new double*[rows_];
  for (int rows = 0; (rows < rows_); rows++) matrix_[rows] = new double[cols_];
  for (int row = 0; (row < rows_); row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = 0;
    }
  }
}
S21Matrix::~S21Matrix() { deleteMatrix(); }

void S21Matrix::deleteMatrix() {
  for (int row = 0; row < rows_; row++) {
    delete[] matrix_[row];
    matrix_[row] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::eqMatrix(const S21Matrix& other) const {
  bool res = SUCCESS;
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    res = FAILURE;
  } else {
    for (int row = 0; (row < rows_); row++) {
      for (int column = 0; column < cols_; column++) {
        if (std::fabs(matrix_[row][column] - other.matrix_[row][column]) >=
            ACCURACY)
          res = FAILURE;
      }
    }
  }

  return res;
}

void S21Matrix::sumMatrix(const S21Matrix& o) {
  difSize(o);
  for (int rows = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      matrix_[rows][cols] += o.matrix_[rows][cols];
    }
  }
}

void S21Matrix::subMatrix(const S21Matrix& o) {
  difSize(o);
  for (int rows = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      matrix_[rows][cols] -= o.matrix_[rows][cols];
    }
  }
}

void S21Matrix::mulNumber(const double num) {
  for (int rows = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      matrix_[rows][cols] *= num;
    }
  }
}

void S21Matrix::mulMatrix(const S21Matrix& other) {
  notMul(other);
  S21Matrix res(rows_, other.cols_);
  for (int row = 0; row < this->rows_; row++) {
    for (int column = 0; column < other.cols_; column++) {
      for (int k = 0; k < this->cols_; k++) {
        res.matrix_[row][column] +=
            this->matrix_[row][k] * other.matrix_[k][column];
      }
    }
  }
  *this = res;
}

double S21Matrix::determinant() {
  notSquare();
  double determ = 1;
  S21Matrix copyMatrix(*this);
  for (int count = 0; (count < (rows_ - 1)) && (determ != 0); count++) {
    int indNotNull = searchNotNull(copyMatrix, count, determ);
    if (indNotNull >= 0)
      gausStr(copyMatrix, count);
    else
      determ = 0;
  }
  for (int column = 0; column < cols_; column++)
    determ *= copyMatrix.matrix_[column][column];
  return determ;
}

int S21Matrix::searchNotNull(S21Matrix& copyMatrix, int count, double& determ) {
  int notNull = -1;
  for (int row = count; (row < copyMatrix.rows_) && (notNull == -1); row++)
    if (copyMatrix.matrix_[row][count])
      notNull = row;  // Нашли ненулевой элемент в столбце

  if ((notNull != count) && (notNull != -1)) {
    for (int column = count; column < copyMatrix.cols_; column++) {
      double temp = 0;
      temp = copyMatrix.matrix_[count][column];  // Меняем строки местами, если
                                                 // ноль на главной диагонали
      copyMatrix.matrix_[count][column] = copyMatrix.matrix_[notNull][column];
      copyMatrix.matrix_[notNull][column] = temp;
    }
    determ *= -1;
    notNull = count;
  }
  return notNull;
}

void S21Matrix::gausStr(S21Matrix& copyMatrix, int count) {
  for (int row = count + 1; row < copyMatrix.rows_; row++) {
    double divider =
        copyMatrix.matrix_[row][count] / copyMatrix.matrix_[count][count];
    for (int column = count; column < copyMatrix.cols_; column++) {
      copyMatrix.matrix_[row][column] -=
          copyMatrix.matrix_[count][column] *
          divider;  // Зануляем элемент в столбце count ниже главной
                    // диагонали
    }
  }
}

S21Matrix S21Matrix::transpose() {
  S21Matrix matrix(cols_, rows_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix.matrix_[col][row] = matrix_[row][col];
    }
  }
  return matrix;
}

S21Matrix S21Matrix::calcComplements() {
  notSquare();
  S21Matrix copyMatrix(rows_, cols_);
  if (rows_ != 1) {
    for (int row = 0; row < rows_; row++) {
      for (int column = 0; column < cols_; column++) {
        S21Matrix tempMatrix(rows_ - 1, cols_ - 1);
        crossOff(row, column, *this, tempMatrix);
        double res = tempMatrix.determinant();
        copyMatrix.matrix_[row][column] = pow(-1, row + column) * res;
      }
    }
  } else {
    copyMatrix.matrix_[0][0] = -matrix_[0][0];
  }
  return copyMatrix;
}

void S21Matrix::crossOff(int indexRow, int indexColumn, const S21Matrix& origin,
                         S21Matrix& temp) {
  int countRow = -1;
  for (int row = 0; row < origin.rows_; row++) {
    if (row != indexRow) {  // Пропускает вычеркнутые элементы строки IndexRow
      countRow++;
      int countColumn = -1;
      for (int column = 0; column < origin.cols_; column++) {
        if (column != indexColumn) {  // Пропускает вычеркнутые элементы
                                      // столбца IndexColumn
          countColumn++;
          temp.matrix_[countRow][countColumn] = origin.matrix_[row][column];
        }
      }
    }
  }
}

S21Matrix S21Matrix::inverseMatrix() {
  double deter = determinant();
  if (deter == 0) throw std::invalid_argument("Определитель матрицы равен 0");
  S21Matrix resMat(1, 1);
  if (rows_ != 1) {
    S21Matrix calcMat = calcComplements();
    resMat = calcMat.transpose();
    resMat.mulNumber(1 / deter);
  } else {
    resMat.matrix_[0][0] = 1 / deter;
  }
  return resMat;
}

void S21Matrix::operator=(const S21Matrix& o) {
  deleteMatrix();
  rows_ = o.rows_;
  cols_ = o.cols_;
  allocateMem();
  for (int rows = 0; rows < rows_; rows++)
    std::memmove(matrix_[rows], o.matrix_[rows], o.cols_ * sizeof(double));
}

bool operator==(const S21Matrix& lm, const S21Matrix& rm) {
  bool res = lm.eqMatrix(rm);
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  difSize(o);
  S21Matrix sMatrix = *this;
  sMatrix.sumMatrix(o);
  return sMatrix;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  difSize(o);
  sumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  difSize(o);
  S21Matrix sMatrix = *this;
  sMatrix.subMatrix(o);
  return sMatrix;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  difSize(o);
  subMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  notMul(o);
  mulMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  notMul(o);
  S21Matrix mulMat = *this;
  mulMat.mulMatrix(o);
  return mulMat;
}

S21Matrix operator*(double o, const S21Matrix& matrix) {
  S21Matrix mulMat = matrix;
  mulMat.mulNumber(o);
  return mulMat;
}

S21Matrix operator*(const S21Matrix& matrix, double o) {
  S21Matrix mulMat = matrix;
  mulMat.mulNumber(o);
  return mulMat;
}

S21Matrix& S21Matrix::operator*=(double o) {
  mulNumber(o);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Индекс за пределами матрицы");
  return matrix_[row][col];
}

void S21Matrix::mutator(const int rows, const int cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("Строка или столбец не может быть меньше 1");
  S21Matrix newMatrix(rows, cols);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (row < rows_ && col < cols_) {
        newMatrix.matrix_[row][col] = matrix_[row][col];
      } else {
        newMatrix.matrix_[row][col] = 0;
      }
    }
  }
  *this = newMatrix;
}

int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }

void S21Matrix::fillMatrixStr(const std::string& src) {
  std::istringstream iss(src);
  for (int row = 0; row < rows_; row++) {
    for (int column = 0; column < cols_; column++) {
      iss >> matrix_[row][column];
    }
  }
}

void S21Matrix::difSize(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_)
    throw std::out_of_range("Различная размерность матриц");
}

void S21Matrix::notMul(const S21Matrix& o) {
  if (cols_ != o.rows_) {
    throw std::invalid_argument(
        "Число столбцов первой матрицы не равно числу строк второй "
        "матрицы");
  }
}

void S21Matrix::notSquare() {
  if (rows_ != cols_) throw std::out_of_range("Матрица не является квадратной");
}
