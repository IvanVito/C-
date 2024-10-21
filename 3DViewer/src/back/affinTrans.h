#ifndef AFFIN_TRANS
#define AFFIN_TRANS

#include <algorithm>
#include <cmath>
#include <vector>

#include "matrix/s21MatrixOop.h"
#include "otherTrans.h"
#include "parser.h"

namespace s21 {

/**
 * @brief Абстрактный класс для аффинных преобразований. Реализованно с
 * использованием паттерна "Шаблонный метод"
 *
 * Этот класс определяет интерфейс для аффинных преобразований,
 * включая метод для применения преобразования к матрице вершин (x, y, z, 1).
 */
class AffinTrans {
 public:
  AffinTrans()
      : matrixTrans(4, 4),
        matrixMoveToOrigin(4, 4),
        matrixMoveBack(4, 4),
        oldCenterX(0),
        oldCenterY(0),
        oldCenterZ(0){};
  AffinTrans(AffinTrans& o) = delete;
  AffinTrans(AffinTrans&& other) = delete;
  virtual ~AffinTrans() = default;

  /**
   * @brief Применяет аффинное преобразование к вершинам.
   *
   * Вызывает метод для создания матрицы преобразования,
   * а затем применяет это преобразование. Является общим методом для всех
   * подклассов
   */
  void transform();

 protected:
  /**
   * @brief Создает матрицу преобразования.
   *
   * @return S21Matrix Матрица аффинного преобразования.
   *
   * Этот метод должен быть переопределен в подклассах.
   */
  virtual S21Matrix createTransMatrix() = 0;

  /**
   * @brief Применяет данное преобразование к матрице.
   *
   * @param matrix Матрица аффинного преобразования.
   */
  void transformation(S21Matrix& matrix);

  /**
   * @brief Инциализирует матрицы преобразования, возврата к начальной системе
   * координат и возврата к текущей позиции.
   */
  void initMatrix();

  S21Matrix matrixTrans;  ///< Матрица преобразования
  S21Matrix
      matrixMoveToOrigin;  ///< Матрица возврата к начальной системе координат
  S21Matrix matrixMoveBack;  ///< Матрица возврата к текущей позиции
  OtherTrans trans_;  ///< Объект с методами различных преобразований

  double oldCenterX;  ///< Центр фигуры по оси X до поворота
  double oldCenterY;  ///< Центр фигуры по оси Y до поворота
  double oldCenterZ;  ///< Центр фигуры по оси Z до поворота
};

/**
 * @brief Класс для перемещения объектов.
 *
 * Этот класс реализует аффинное преобразование для
 * перемещения объекта в 3D-пространстве.
 */
class AffinMove : public AffinTrans {
 public:
  AffinMove() = default;
  /**
   * @brief Конструктор для перемещения.
   *
   * @param x ///< Сдвиг по оси X.
   * @param y ///< Сдвиг по оси Y.
   * @param z ///< Сдвиг по оси Z.
   */
  AffinMove(double x, double y, double z) : x_(x), y_(y), z_(z) {}
  AffinMove(AffinMove& o) = delete;
  AffinMove(AffinMove&& other) = delete;
  virtual ~AffinMove() = default;

  /**
   * @brief Создает матрицу перемещения.
   *
   * @return S21Matrix Матрица перемещения.
   */
  S21Matrix createTransMatrix() override;

  /**
   * @brief Сбрасывет значения статических переменных обекта
   */
  static void clearStaticVariable();

 protected:
 private:
  double x_;  ///< Сдвиг по оси X.
  double y_;  ///< Сдвиг по оси Y.
  double z_;  ///< Сдвиг по оси Z.

  static double lastMoveX;  ///< Прошлое переданное значение по оси X.
  static double lastMoveY;  ///< Прошлое переданное значение по оси Y.
  static double lastMoveZ;  ///< Прошлое переданное значение по оси Z.
};

/**
 * @brief Класс для вращения объектов.
 *
 * Этот класс реализует аффинное преобразование для
 * вращения объекта вокруг заданной оси.
 */
class AffinRotate : public AffinTrans {
 public:
  AffinRotate() = default;
  /**
   * @brief Конструктор для вращения.
   *
   * @param degree Угол вращения в градусах.
   * @param axis Ось вращения ('x', 'y' или 'z').
   */
  AffinRotate(double degree, char axis) : degree_(degree), axis_(axis) {}
  AffinRotate(AffinRotate& o) = delete;
  AffinRotate(AffinRotate&& other) = delete;
  virtual ~AffinRotate() = default;

  /**
   * @brief Сбрасывет значения статических переменных обекта
   */
  static void clearStaticVariable();

 protected:
  /**
   * @brief Создает матрицу вращения.
   *
   * @return S21Matrix Матрица вращения.
   */
  S21Matrix createTransMatrix() override;

 private:
  double degree_;  ///< Угол вращения в градусах.
  char axis_;      ///< Ось вращения ('x', 'y' или 'z').

  static double lastRotateX;  ///< Прошлый переданный угол относительно оси X.
  static double lastRotateY;  ///< Прошлый переданный угол относительно оси Y.
  static double lastRotateZ;  ///< Прошлый переданный угол относительно оси Z.
};

/**
 * @brief Класс для масштабирования объектов.
 *
 * Этот класс реализует аффинное преобразование для
 * масштабирования объекта в 3D-пространстве.
 */
class AffinScale : public AffinTrans {
 public:
  AffinScale() = default;
  /**
   * @brief Конструктор для масштабирования.
   *
   * @param scaleX Масштаб по оси X.
   * @param scaleY Масштаб по оси Y.
   * @param scaleZ Масштаб по оси Z.
   */
  AffinScale(double scaleX, double scaleY, double scaleZ)
      : scaleX_(scaleX), scaleY_(scaleY), scaleZ_(scaleZ) {}
  AffinScale(AffinTrans& o) = delete;
  AffinScale(AffinTrans&& other) = delete;
  virtual ~AffinScale() = default;

  /**
   * @brief Сбрасывет значения статических переменных обекта
   */
  static void clearStaticVariable();

 protected:
  /**
   * @brief Создает матрицу масштабирования.
   *
   * @return S21Matrix Матрица масштабирования.
   */
  S21Matrix createTransMatrix() override;

 private:
  double scaleX_;  ///< Масштаб по оси X.
  double scaleY_;  ///< Масштаб по оси Y.
  double scaleZ_;  ///< Масштаб по оси Z.

  static double lastScaleX;  ///< Прошлое переданное значение по оси X.
  static double lastScaleY;  ///< Прошлое переданное значение по оси Y.
  static double lastScaleZ;  ///< Прошлое переданное значение по оси Z.
};

}  // namespace s21
#endif  // AFFIN_TRANS
