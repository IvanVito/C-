#include "facade.h"

namespace s21 {

/**
 * @brief Класс Controller управляет операциями над 3D моделями.
 *
 * Этот класс предоставляет интерфейс для взаимодействия с классом Facade,
 * позволяя выполнять такие операции, как парсинг файлов, трансформации модели
 * (масштабирование, перемещение, вращение) и доступ к вершинам и полигонам.
 */
class Controller {
 public:
  s21::Facade facade; /**< Объект класса Facade для обработки данных модели. */

  /**
   * @brief Парсит файл с указанным именем.
   *
   * Этот метод вызывает метод parseFile класса Facade для загрузки данных из
   * файла.
   *
   * @param fileName Имя файла, который нужно распарсить.
   */
  void parseFile(const std::string& fileName);

  /**
   * @brief Метод определяет количество вершин.
   *
   * @return Размер вектора вершин.
   */
  size_t getSizeVertexes();

  /**
   * @brief Метод определяет количество полигонов.
   *
   * @return Размер вектора полигонов.
   */
  size_t getSizePoligons();

  /**
   * @brief Метод определяет вектор вершин.
   *
   * @return Ссылка на вектор вершин (вектор векторов).
   */
  std::vector<std::vector<double>>& getVertexes();

  /**
   * @brief Метод определяет вектор полигонов.
   *
   * @return Ссылка на вектор полигонов (вектор векторов).
   */
  std::vector<std::vector<int>>& getPoligons();

  /**
   * @brief Метод масштабирует модель.
   *
   * @param scale Коэффициент масштабирования.
   */
  void scale(double scale);

  /**
   * @brief Метод центрирует модель.
   *
   * Этот метод вызывает соответствующий метод класса Facade для
   * центрирования модели в координатной системе.
   */
  void centerModel();

  /**
   * @brief Метод перемещает модель.
   *
   * @param x Смещение по оси X.
   * @param y Смещение по оси Y.
   * @param z Смещение по оси Z.
   */
  void move(double x, double y, double z);

  /**
   * @brief Метод вращает модель вокруг заданной оси.
   *
   * @param degree Угол вращения в градусах.
   * @param axis Ось вращения ('x', 'y' или 'z').
   */
  void rotate(double degree, char axis);

  /**
   * @brief Метод масштабирует модель по осям X, Y и Z.
   *
   * @param scaleX Коэффициент масштабирования по оси X.
   * @param scaleY Коэффициент масштабирования по оси Y.
   * @param scaleZ Коэффициент масштабирования по оси Z.
   */
  void scaleXYZ(double scaleX, double scaleY, double scaleZ);

  /**
   * @brief Проверка на вылидное число
   *
   * @return Истина, если число валидное, и ложь в обратном случае
   */
  bool isValidNumber(const std::string& numberStr);
};

}  // namespace s21
