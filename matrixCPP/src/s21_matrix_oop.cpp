#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Недопустимое значение строки или колонки");
  AllocateMem();
}

S21Matrix::S21Matrix(const S21Matrix& o)
    : rows_(o.rows_), cols_(o.cols_), matrix_(nullptr) {
  AllocateMem();
  for (int rows = 0; rows < rows_; rows++)
    std::memmove(matrix_[rows], o.matrix_[rows], o.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

void S21Matrix::AllocateMem() {
  if (matrix_ != nullptr) DeleteMatrix();
  matrix_ = new double*[rows_];
  for (int rows = 0; (rows < rows_); rows++) matrix_[rows] = new double[cols_];
  for (int row = 0; (row < rows_); row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = 0;
    }
  }
}
S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::DeleteMatrix() {
  for (int row = 0; row < rows_; row++) {
    delete[] matrix_[row];
    matrix_[row] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
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

void S21Matrix::SumMatrix(const S21Matrix& o) {
  DifSize(o);
  for (int rows = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      matrix_[rows][cols] += o.matrix_[rows][cols];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& o) {
  DifSize(o);
  for (int rows = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      matrix_[rows][cols] -= o.matrix_[rows][cols];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int rows = 0; rows < rows_; rows++) {
    for (int cols = 0; cols < cols_; cols++) {
      matrix_[rows][cols] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  NotMul(other);
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

double S21Matrix::Determinant() {
  NotSquare();
  double Determ = 1;
  S21Matrix CopyMatrix(*this);
  for (int count = 0; (count < (rows_ - 1)) && (Determ != 0); count++) {
    int IndNotNull = SearchNotNull(CopyMatrix, count, Determ);
    if (IndNotNull >= 0)
      GausStr(CopyMatrix, count);
    else
      Determ = 0;
  }
  for (int column = 0; column < cols_; column++)
    Determ *= CopyMatrix.matrix_[column][column];
  return Determ;
}

int S21Matrix::SearchNotNull(S21Matrix& CopyMatrix, int count, double& Determ) {
  int NotNull = -1;
  for (int row = count; (row < CopyMatrix.rows_) && (NotNull == -1); row++)
    if (CopyMatrix.matrix_[row][count])
      NotNull = row;  // Нашли ненулевой элемент в столбце

  if ((NotNull != count) && (NotNull != -1)) {
    for (int column = count; column < CopyMatrix.cols_; column++) {
      double temp = 0;
      temp = CopyMatrix.matrix_[count][column];  // Меняем строки местами, если
                                                 // ноль на главной диагонали
      CopyMatrix.matrix_[count][column] = CopyMatrix.matrix_[NotNull][column];
      CopyMatrix.matrix_[NotNull][column] = temp;
    }
    Determ *= -1;
    NotNull = count;
  }
  return NotNull;
}

void S21Matrix::GausStr(S21Matrix& CopyMatrix, int count) {
  for (int row = count + 1; row < CopyMatrix.rows_; row++) {
    double divider =
        CopyMatrix.matrix_[row][count] / CopyMatrix.matrix_[count][count];
    for (int column = count; column < CopyMatrix.cols_; column++) {
      CopyMatrix.matrix_[row][column] -=
          CopyMatrix.matrix_[count][column] *
          divider;  // Зануляем элемент в столбце count ниже главной
                    // диагонали
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix Matrix(cols_, rows_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      Matrix.matrix_[col][row] = matrix_[row][col];
    }
  }
  return Matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  NotSquare();
  S21Matrix CopyMatrix(rows_, cols_);
  if (rows_ != 1) {
    for (int row = 0; row < rows_; row++) {
      for (int column = 0; column < cols_; column++) {
        S21Matrix TempMatrix(rows_ - 1, cols_ - 1);
        CrossOff(row, column, *this, TempMatrix);
        double res = TempMatrix.Determinant();
        CopyMatrix.matrix_[row][column] = pow(-1, row + column) * res;
      }
    }
  } else {
    CopyMatrix.matrix_[0][0] = -matrix_[0][0];
  }
  return CopyMatrix;
}

void S21Matrix::CrossOff(int IndexRow, int IndexColumn, const S21Matrix& origin,
                         S21Matrix& temp) {
  int CountRow = -1;
  for (int row = 0; row < origin.rows_; row++) {
    if (row != IndexRow) {  // Пропускает вычеркнутые элементы строки IndexRow
      CountRow++;
      int CountColumn = -1;
      for (int column = 0; column < origin.cols_; column++) {
        if (column != IndexColumn) {  // Пропускает вычеркнутые элементы
                                      // столбца IndexColumn
          CountColumn++;
          temp.matrix_[CountRow][CountColumn] = origin.matrix_[row][column];
        }
      }
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double deter = Determinant();
  if (deter == 0) throw std::invalid_argument("Определитель матрицы равен 0");
  S21Matrix ResMat(1, 1);
  if (rows_ != 1) {
    S21Matrix CalcMat = CalcComplements();
    ResMat = CalcMat.Transpose();
    ResMat.MulNumber(1 / deter);
  } else {
    ResMat.matrix_[0][0] = 1 / deter;
  }
  return ResMat;
}

void S21Matrix::operator=(const S21Matrix& o) {
  DeleteMatrix();
  rows_ = o.rows_;
  cols_ = o.cols_;
  AllocateMem();
  for (int rows = 0; rows < rows_; rows++)
    std::memmove(matrix_[rows], o.matrix_[rows], o.cols_ * sizeof(double));
}

bool operator==(const S21Matrix& lm, const S21Matrix& rm) {
  bool res = lm.EqMatrix(rm);
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  DifSize(o);
  S21Matrix s_matrix = *this;
  s_matrix.SumMatrix(o);
  return s_matrix;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  DifSize(o);
  SumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  DifSize(o);
  S21Matrix s_matrix = *this;
  s_matrix.SubMatrix(o);
  return s_matrix;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  DifSize(o);
  SubMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  NotMul(o);
  MulMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  NotMul(o);
  S21Matrix MulMat = *this;
  MulMat.MulMatrix(o);
  return MulMat;
}

S21Matrix operator*(double o, const S21Matrix& matrix) {
  S21Matrix MulMat = matrix;
  MulMat.MulNumber(o);
  return MulMat;
}

S21Matrix operator*(const S21Matrix& matrix, double o) {
  S21Matrix MulMat = matrix;
  MulMat.MulNumber(o);
  return MulMat;
}

S21Matrix& S21Matrix::operator*=(double o) {
  MulNumber(o);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Индекс за пределами матрицы");
  return matrix_[row][col];
}

void S21Matrix::Mutator(const int rows, const int cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("Строка или столбец не может быть меньше 1");
  S21Matrix NewMatrix(rows, cols);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (row < rows_ && col < cols_) {
        NewMatrix.matrix_[row][col] = matrix_[row][col];
      } else {
        NewMatrix.matrix_[row][col] = 0;
      }
    }
  }
  *this = NewMatrix;
}

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::FillMatrixStr(const std::string& src) {
  std::istringstream iss(src);
  for (int row = 0; row < rows_; row++) {
    for (int column = 0; column < cols_; column++) {
      iss >> matrix_[row][column];
    }
  }
}

void S21Matrix::DifSize(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_)
    throw std::out_of_range("Различная размерность матриц");
}

void S21Matrix::NotMul(const S21Matrix& o) {
  if (o.rows_ != cols_ || o.cols_ != rows_)
    throw std::invalid_argument(
        "Число столбцов первой матрицы не равно числу строк второй "
        "матрицы");
}

void S21Matrix::NotSquare() {
  if (rows_ != cols_) throw std::out_of_range("Матрица не является квадратной");
}
