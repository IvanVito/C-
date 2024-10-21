#ifndef PARSER
#define PARSER

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * @brief Макрос для правильной обработки полигонов (отсчет полигонов в Obj с
 * 1-цы, а в векторе с 0-ля)
 */
#define OBJ_INDEX 1

namespace s21 {

/**
 * @brief Класс для парсинга OBJ-файлов и работы с вершинами и полигонами.
 *
 * Этот класс предоставляет функциональность для загрузки, обработки и вывода
 * данных о вершинах и полигонах из файлов формата OBJ.
 */
class Parser {
 public:
  std::vector<std::vector<double>>
      vertexes_;  ///< Контейнер для хранения вершин.

  std::vector<std::vector<int>>
      poligons_;  ///< Контейнер для хранения полигонов.

  bool error_ = false;  ///< Флаг ошибки

  /**
   * @brief Парсинг вершин из входного файла.
   *
   * @param inputFile Поток файла для чтения данных.
   */
  void parserVertex(std::ifstream& inputFile);

  /**
   * @brief Парсинг полигонов из входного файла.
   *
   * @param inputFile Поток файла для чтения данных.
   */
  void parserPoligon(std::ifstream& inputFile);

  /**
   * @brief Проверка строки на соответствие формату числа для полигона.
   *
   * @param str Строка для проверки.
   * @return true Если строка является корректным числом.
   * @return false Если строка не является корректным числом.
   */
  bool isNumberPoligon(const std::string& str);

  /**
   * @brief Добавление числа в список полигонов.
   *
   * @param num Строка с числовым значением полигона.
   * @param vertex Вектор для хранения индексов полигона.
   */
  void pushPoligon(const std::string& num, std::vector<int>& vertex);

  /**
   * @brief Парсинг OBJ-файла.
   *
   * @param fileName Имя файла OBJ для парсинга.
   */
  void parser(const std::string& fileName);

  /**
   * @brief Получение объекта класса Parser (синглтон).
   *
   * @return Ссылка на объект класса Parser.
   */
  static Parser& getObject();

 private:
  /**
   * @brief Приватный конструктор класса Parser для реализации паттерна
   * Singleton.
   */
  Parser() = default;

  /**
   * @brief Удаление копирующего конструктора.
   */
  Parser(Parser& o) = delete;

  /**
   * @brief Удаление конструктора перемещения.
   */
  Parser(Parser&& other) = delete;

  /**
   * @brief Приватный деструктор.
   */
  ~Parser() = default;
};

}  // namespace s21

#endif  // PARSER
