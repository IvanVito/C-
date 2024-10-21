#ifndef OTHER_TRANS
#define OTHER_TRANS

#include <algorithm>
#include <vector>

#include "parser.h"

namespace s21 {

/**
 * @brief Класс для выполнения операций с координатами и трансформации объекта.
 *
 * Этот класс предоставляет методы для работы с координатами X, Y, Z и
 * выполнения операций по их сортировке, нахождению экстремумов и центрированию.
 */
class OtherTrans {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  OtherTrans() = default;

  /**
   * @brief Удаление копирующего конструктора.
   */
  OtherTrans(OtherTrans& o) = delete;

  /**
   * @brief Удаление конструктора перемещения.
   */
  OtherTrans(OtherTrans&& other) = delete;

  /**
   * @brief Деструктор.
   */
  ~OtherTrans() = default;

  std::vector<double> x_;  ///< Вектор координат X
  std::vector<double> y_;  ///< Вектор координат Y
  std::vector<double> z_;  ///< Вектор координат Z

  /**
   * @brief Сортирует координаты X, Y, Z. Каждый раз очищает векторы перед
   * заполнением
   */
  void sortXYZ();

  /**
   * @brief Находит минимальное значение среди координат оси.
   *
   * @return Минимальное значение по указанной оси.
   */
  double findMin(std::vector<double> axis);

  /**
   * @brief Находит максимальное значение среди координат оси.
   *
   * @return Максимальное значение по указанной оси.
   */
  double findMax(std::vector<double> axis);

  /**
   * @brief Центрирует объект по координатам X, Y, Z.
   */
  void makeCenter();

  /**
   * @brief Возвращает центр координат оси
   *
   * @param Вектор координат одной оси
   *
   * @return Центр оси
   */
  double findCoordinateCenter(std::vector<double>& coordinats);

  /**
   * @brief Находит адаптивный скейл. Благодаря этому, любой объект адекватно
   * отображается в окне при загрузке
   *
   * @return Адаптивные коэффициент масштабирования для объекта
   */
  double adaptScale();
};

}  // namespace s21

#endif  // OTHER_TRANS
