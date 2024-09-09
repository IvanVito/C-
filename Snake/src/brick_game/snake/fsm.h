#ifndef CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_FSM_H_
#define CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_FSM_H_

#include <chrono>
#include <thread>

#include "snake.h"
/**
 * @brief Кнопка выхода
 */
#define ESCAPE 27

/**
 * @brief Кнопка действия
 */
#define SPACE 32

/**
 * @brief Кнопка старт
 */
#define ENTER 10

/**
 * @brief Кнопка паузы
 */
#define LETTER_P 'p'

/**
 * @brief Стартовая задержка
 */
#define START_SPEED 460

/**
 * @brief Значение уменьшения задержки при ускорении
 */
#define ACCELERATE 200

/**
 * @brief Максимальное количество очков
 */
#define MAX_SCORE 200

namespace s21 {

/**
 * @brief Структура состояний змейки в конечном автомате
 */
enum class States { Start, Move, Check, Pause, GameOver, Win, Exit };

/**
 * @brief Конечный автомат на матрице указателей на функции.
 */
class SnakeStateMachine {
 public:
  using StateFunction = void (SnakeStateMachine::*)();

  /**
   * @brief Конструктор по умолчанию.
   */
  SnakeStateMachine();

  /**
   * @brief Конструктор с параметрами.
   * @param state Текущее состояние конечного автомата.
   * @param x Координата X (столбец) для спавна головы змейки.
   * @param y Координата Y (строка) для спавна головы змейки.
   * @param dir Направление движения змейки при спавне.
   */
  SnakeStateMachine(States state, int x, int y, s21::Direction dir, int score);

  /**
   * @brief Конструктор копирования.
   */
  SnakeStateMachine(const SnakeStateMachine&) = default;

  /**
   * @brief Оператор присваивания копированием.
   * @return Ссылка на объект после присваивания.
   */
  SnakeStateMachine& operator=(const SnakeStateMachine&) = default;

  /**
   * @brief Конструктор перемещения.
   */
  SnakeStateMachine(SnakeStateMachine&&) = default;

  /**
   * @brief Оператор присваивания перемещением.
   * @return Ссылка на объект после присваивания.
   */
  SnakeStateMachine& operator=(SnakeStateMachine&&) = default;

  /**
   * @brief Деструктор.
   */
  ~SnakeStateMachine() = default;

  /**
   * @brief Обрабатывает сигнал от пользователся
   * @param action Сигнал от пользователя
   * @param hold Переменная, отвечающая за то, была ли нажата клавиша
   */
  void userInput(UserAction_t action, bool hold);

  /**
   * @brief Возвращает значение флага нажатия на кнопку
   */
  bool getHold();

  /**
   * @brief Возвращает текущее значение состояния КА
   */
  States getCurrentState();

  /**
   * @brief Возвращает текущее значение задержки
   */
  int getDelay();

  /**
   * @brief Сеттер. Устанавливает ускорение
   */
  void setAccelerate(bool value);

  /**
   * @brief Геттер. Получает флаг ускорения
   */
  bool getAccelerate();

  /**
   * @brief Возвращает объект змейки
   */
  Snake& getSnake();

  /**
   * @brief Возвращает значение поступившего сигнала
   */
  UserAction_t getCurrentAction();

  /**
   * @brief Функия возвращает указатель на объект поля с текущим состоянием
   */
  GameInfo_t updateCurrentState();

 private:
  /**
   * @brief Текущее действие в КА
   */
  UserAction_t action_;

  /**
   * @brief Текущее состояние КА
   */
  States currentState_;

  /**
   * @brief Экземпляр змейки в КА
   */
  Snake snake_;

  /**
   * @brief Флаг, отвечающий за то, была ли нажата кнопка
   */
  bool hold_;

  /**
   * @brief Текущее время задержки между перемещениями
   */
  int delay_;

  /**
   * @brief Флаг, отвечающий за наличие или отсутствие ускорения
   */
  bool accelerate_;

  /**
   * @brief Функция КА. Переводит КА в состояние "Check" или "Exit"
   */
  void start();

  /**
   * @brief Функция КА. Обеспечивает движение змейки, но не отрисовывает ее.
   * Переводит КА в состояние "EatApple"
   */
  void move();

  /**
   * @brief Функция КА. Проверяет состояние змейки: коллизия, выйгрыш, пауза или
   * продолжение игры. Перемещает КА в соответсвующее состояние
   */
  void check();

  /**
   * @brief Функция КА. Переводит КА в состояние "Check" или "Exit"
   */
  void pause();

  /**
   * @brief Функция КА. Переводит КА в состояние "Start" или "Exit". При
   * переходе в состояние "Start" обновляет объект информации об игре,
   * инициализирует новую змейку
   */
  void gameOver();

  /**
   * @brief Функция КА. Переводит КА в состояние "Exit"
   */
  void win();

  /**
   * @brief Функция КА.  Переводит КА в состояние "Exit"
   */
  void exit();

  /**
   * @brief Матрица состояний и возможных дейсвий в этих состояниях.
   */
  static constexpr StateFunction stateMatrix[7][8] = {
      /* Start */
      {&SnakeStateMachine::start, &SnakeStateMachine::check,
       &SnakeStateMachine::exit, &SnakeStateMachine::start,
       &SnakeStateMachine::start, &SnakeStateMachine::start,
       &SnakeStateMachine::start, &SnakeStateMachine::start},
      /* Move */
      {&SnakeStateMachine::move, &SnakeStateMachine::move,
       &SnakeStateMachine::exit, &SnakeStateMachine::move,
       &SnakeStateMachine::move, &SnakeStateMachine::move,
       &SnakeStateMachine::move, &SnakeStateMachine::move},
      /* Check */
      {&SnakeStateMachine::check, &SnakeStateMachine::check,
       &SnakeStateMachine::exit, &SnakeStateMachine::check,
       &SnakeStateMachine::check, &SnakeStateMachine::check,
       &SnakeStateMachine::check, &SnakeStateMachine::check},
      /* Pause */
      {&SnakeStateMachine::pause, &SnakeStateMachine::pause,
       &SnakeStateMachine::pause, &SnakeStateMachine::check,
       &SnakeStateMachine::pause, &SnakeStateMachine::pause,
       &SnakeStateMachine::pause, &SnakeStateMachine::pause},
      /* GameOver */
      {&SnakeStateMachine::gameOver, &SnakeStateMachine::gameOver,
       &SnakeStateMachine::gameOver, &SnakeStateMachine::gameOver,
       &SnakeStateMachine::gameOver, &SnakeStateMachine::gameOver,
       &SnakeStateMachine::gameOver, &SnakeStateMachine::gameOver},
      /* Win */
      {&SnakeStateMachine::win, &SnakeStateMachine::win,
       &SnakeStateMachine::win, &SnakeStateMachine::win,
       &SnakeStateMachine::win, &SnakeStateMachine::win,
       &SnakeStateMachine::win, &SnakeStateMachine::win},
      /* Exit */
      {&SnakeStateMachine::exit, &SnakeStateMachine::exit,
       &SnakeStateMachine::exit, &SnakeStateMachine::exit,
       &SnakeStateMachine::exit, &SnakeStateMachine::exit,
       &SnakeStateMachine::exit, &SnakeStateMachine::exit}};
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_SRC_BRICK_GAME_SNAKE_FSM_H_
