#ifndef FACADE_H
#define FACADE_H

#include "affinTrans.h"
#include "otherTrans.h"
#include "parser.h"
#include "regex"

namespace s21 {

/**
 * @brief Класс Фасад для взаимодействия с системой 3D Viewer.
 *
 * Этот класс предоставляет общий интерфейс для работы с объектом.
 */
class Facade {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  Facade() : object_(Parser::getObject()){};

  /**
   * @brief Удаление копирующего конструктора.
   */
  Facade(Facade& o) = delete;

  /**
   * @brief Удаление конструктора перемещения.
   */
  Facade(Facade&& other) = delete;

  /**
   * @brief Деструктор.
   */
  ~Facade() = default;

  /**
   * @brief Метод для парсинга OBJ-файла.
   *
   * @param fileName Имя файла OBJ для парсинга.
   */
  void parseFile(const std::string& fileName);

  /**
   * @brief Метод для выполнения сдвига.
   *
   * @param x Сдвиг по оси X.
   * @param y Сдвиг по оси Y.
   * @param z Сдвиг по оси Z.
   */
  void move(double x = 0, double y = 0, double z = 0);

  /**
   * @brief Метод для выполнения вращения модели.
   *
   * @param degree Угол поворота.
   * @param axis Ось вращения ('x', 'y', 'z').
   */
  void rotate(double degree, char axis = 'x');

  /**
   * @brief Метод для масштабирования модели по осям.
   *
   * @param scaleX Масштабирование по оси Х.
   * @param scaleY Масштабирование по оси Y.
   * @param scaleZ Масштабирование по оси Z.
   */
  void scaleXYZ(double scaleX = 1, double scaleY = 1, double scaleZ = 1);

  /**
   * @brief Метод для масштабирования модели целиком.
   *
   * @param scale Масштабирование по всем осям.
   */
  void scale(double scale = 2);

  /**
   * @brief Центрирование модели по координатам.
   */
  void centerModel();

  /**
   * @brief Геттер количества вершин.
   *
   * @return Количество вершин
   */
  size_t getSizeVertexes();

  /**
   * @brief Геттер колличества полигонов.
   *
   * @return Количество полигонов
   */
  size_t getSizePoligons();

  /**
   * @brief Геттер. Возвращает вершины объекта в векторах, помещенных в вектор.
   *
   * @return Вектор векторов с вершинами
   */
  std::vector<std::vector<double>>& getVertexes();

  /**
   * @brief Геттер. Возвращает полигоны объекта в векторах, помещенных в вектор.
   *
   * @return Вектор векторов с полигонами
   */
  std::vector<std::vector<int>>& getPoligons();

  /**
   * @brief Проверка на валидное число
   *
   * @return Истина, если число валидное, и ложь в обратном случае
   */
  bool isValidNumber(const std::string& numberStr);

  Parser& object_;  ///< Ссылка на синглтон парсера.

 private:
  OtherTrans otherTrans_;  ///< Объект для других трансформаций.
};

}  // namespace s21

#endif  // FACADE_H
