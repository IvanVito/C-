#ifndef SNAKE_QT_H
#define SNAKE_QT_H

#include "../../brick_game/brick_game/fsm.h"
#include "../../brick_game/brick_game/tetris.h"
#include "mainwindow.h"

/**
 * @brief Класс для управления игрой "Тетрис" с графическим интерфейсом
 *
 * Класс расширяет функциональность основного окна и добавляет
 * поддержку рисования и обработки событий для игры "Тетрис".
 */
class TetrisQT : public MainWindow {
 public:
  /**
   * @brief Конструктор класса TetrisQT
   * Инициализирует начальные состояния, загружает изображения для
   * плиток и фона, а также настраивает таймер для периодической обработки
   * сигналов.
   */
  TetrisQT();

 private:
  states stateFSM;  ///< Текущее состояние игры
  UserAction_t action;  ///< Действие, выбранное пользователем (
  struct timespec last_fall;  ///< Время последнего падения фигуры
  GameInfo_t frame;  ///< Информация о текущем состоянии игры
  figure tetr;  ///< Текущая фигура в игре
  bool hold;  ///< Флаг, указывающий, удерживается ли клавиша дейсвия

  QPixmap bricks;  ///< Изображение для изображения плиток
  QPixmap backGround;  ///< Изображение для фона

  /**
   * @brief Обновляет поле игры и перерисовывает окно
   */
  void updateField();

  /**
   * @brief Обрабатывает пользовательский ввод
   * @param action Действие, выбранное пользователем
   * @param hold Флаг, указывающий, удерживается ли клавиша действия
   */
  void userInput(UserAction_t action, int hold);

  /**
   * @brief Обрабатывает нажатие клавиш
   * @param event Параметр не используется
   */
  void keyPressEvent(QKeyEvent *event) override;

  /**
   * @brief Отрисовывает содержимое окна
   * @param event Параметр не используется
   */
  void paintEvent(QPaintEvent *event) override;

  /**
   * @brief Отправляет периодический сигнал для обновления состояния игры
   */
  void sendPeriodicSignal();

  /**
   * @brief Обрабатывает пользовательский ввод и выполняет соответствующее
   * действие
   * @param userInput Введенное пользователем значение
   * @param hold Флаг, указывающий, удерживается ли клавиша действия
   */
  void getSignal(int userInput, bool hold);
};

#endif  // SNAKE_QT_H
