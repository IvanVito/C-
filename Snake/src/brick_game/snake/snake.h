#ifndef CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_SNAKE_H_
#define CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_SNAKE_H_

#include <algorithm>
#include <array>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>

/**
 * @brief Начальный размер змейки
 */
#define INIT_SIZE_SNAKE 4

/**
 * @brief Уменьшение задержки при получении уровня
 */
#define SPEED_STEP 20

/**
 * @brief Максимальное количество уровней
 */
#define MAX_LVL 10

/**
 * @brief Количество съеденных яблок для перехода на следующий уровень
 */
#define LVL_STEP 5

/**
 * @brief Количество рядов в поле
 */
#define MAP_ROWS 20

/**
 * @brief Количество столбцов в поле
 */
#define MAP_COLS 10

namespace s21 {

/**
 * @brief Структура с информацией об игре
 * @param field Массив для отрисовки игрового поля
 * @param next Массив для следующего кадра поля. В данном проекте не
 * используется
 * @param score Текущий Счет
 * @param high_score Текущий рекорд
 * @param level Текущий уровень
 * @param speed Скорость игры. Время, в течение которого можно выбрать следующее
 * действие
 */
struct GameInfo_t {
 public:
  std::array<std::array<int, MAP_COLS>, MAP_ROWS> field;
  std::array<std::array<int, MAP_COLS>, MAP_ROWS> next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

  GameInfo_t();
  GameInfo_t(const GameInfo_t&) = default;
  GameInfo_t& operator=(const GameInfo_t&) = default;
  GameInfo_t(GameInfo_t&&) = default;
  GameInfo_t& operator=(GameInfo_t&&) = default;

  ~GameInfo_t() = default;
};

/**
 * @brief Структура возможных сигналов
 * @param Action Сигнал уменьшает время выбора действия (ускоряет игру)
 * @param Terminate Стгнал выхода из игры
 */
enum class UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
};
/**
 * @brief Структура, определяющая направление змейки
 */
enum Direction { UP, DOWN, LEFT, RIGHT };

/**
 * @brief Класс змейки. Отвечает за логику поведения змейки и ее взаимодействия
 * с полем.
 */
class Snake {
 public:
  /**
   * @brief Псевдоним координат
   */
  using Coordinate = std::pair<int, int>;
  friend class SnakeStateMachine;

  /**
   * @brief Конструктор по умолчанию
   */
  Snake();
  /**
   * @brief Конструктор с параметрами
   * @param initialLength Длина змейки при инициализации
   * @param initialPosition Пара координат головы
   * @param dir Направление движения при инициализаци
   */
  Snake(int initialLength, Coordinate initialPosition, Direction dir);

  /**
   * @brief Конструктор копирования.
   */
  Snake(const Snake&) = default;

  /**
   * @brief Оператор присваивания копированием.
   * @return Ссылка на объект после присваивания.
   */
  Snake& operator=(const Snake&) = default;

  /**
   * @brief Конструктор перемещения.
   */
  Snake(Snake&&) = default;

  /**
   * @brief Оператор присваивания перемещением.
   * @return Ссылка на объект после присваивания.
   */
  Snake& operator=(Snake&&) = default;

  /**
   * @brief Деструктор
   */
  ~Snake() = default;

  /**
   * @brief Чистит поле (Все элементы поля переводит в 0)
   */
  void clearField();

  /**
   * @brief Геттер. Используется в тестах для доступа к змейке (двухсторонней
   * очереди)
   */
  std::deque<Coordinate> getBody();

  /**
   * @brief Геттер. Используется в тестах для спавна яблока на одном и том же
   * месте
   */
  void testPlaceApple(bool test = true);

  /**
   * @brief Геттер. Используется в QT для получения направления змейки
   */
  Direction getDirection();

 private:
  /**
   * @brief Тело змейки из обратной очереди
   */
  std::deque<Coordinate> body_;

  /**
   * @brief Пара координат яблока
   */
  Coordinate applePosition_;

  /**
   * @brief Направление движения змейки
   */
  Direction dir_ = Direction::UP;

  /**
   * @brief Объект содержит основную информацию об игре
   */
  GameInfo_t info_;

  /**
   * @brief В зависимости от подаваемого действия определяется направлени
   * движения
   */
  void handleInput(UserAction_t action);

  /**
   * @brief В зависимости от направления, создает новую часть змейки и вставляет
   * ее в голову текущей. Из хвоста убирается один сегмент. Змейка движется
   */
  void move();

  /**
   * @brief Затирает змейку на поле
   */
  void clearPastState();

  /**
   * @brief Рисует змейку на поле
   */
  void printSnake();

  /**
   * @brief Определяет положение змейки
   * @param test Нужен только для тестов. В этом режиме яблоко появляется в
   * одном месте
   */
  void placeApple(bool test = false);

  /**
   * @brief Функция читает рекорд из файла или создает файл и записывает туда
   * "0"
   */
  void readRecord();

  /**
   * @brief Записывает рекорд в файл
   * @param Рекорд, который нужно записать в файл
   */
  void writeRecord(int record);

  /**
   * @brief Вызывается при съедении яблока. В функци увеличивается счет и может
   * увеличиваться уровень и рекорд
   */
  void score();

  /**
   * @brief Функция отвечает за распознование столкновения змейки со стенками
   * поля и с самой собой
   */
  bool checkCollision() const;
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_SNAKE_H_
