#ifndef SNAKE_QT_H
#define SNAKE_QT_H

#include "mainwindow.h"

/**
 * @brief Класс для управления игрой "Змейка" с графическим интерфейсом
 *
 * Класс расширяет функциональность основного окна и добавляет
 * поддержку рисования и обработки событий для игры "Змейка".
 */
class SnakeQT : public MainWindow {
 public:
  /**
   * @brief Конструктор класса SnakeQT
   * Инициализирует изображения для различных частей змейки, яблока и фона.
   * Настраивает таймер для периодической обработки сигналов.
   */
  SnakeQT();

 private:
  int action;  ///< Действие, которое в данный момент выбрано пользователем
  bool hold;  ///< Флаг, указывающий, удерживается ли клавиша действия

  QPixmap apple;  ///< Изображение для изображения яблока
  QPixmap backGround;  ///< Изображение для фона
  QPixmap snakeHead;  ///< Изображение для головы змейки
  QPixmap snakeBody;  ///< Изображение для тела змейки
  QPixmap snakeBodyTurn;  ///< Изображение для поворота тела змейки
  QPixmap snakeTail;  ///< Изображение для хвоста змейки

  /**
   * @brief Обрабатывает нажатие клавиш
   * @param event Не используется
   */
  void keyPressEvent(QKeyEvent *event) override;

  /**
   * @brief Отрисовывает содержимое окна
   * @param event Не используется
   */
  void paintEvent(QPaintEvent *event) override;

  /**
   * @brief Отправляет периодический сигнал для обновления состояния игры
   */
  void sendPeriodicSignal();

  /**
   * @brief Рисует часть змейки с учетом поворота
   * @param painter Объект для отрисовки на полотне
   * @param cellRect Прямоугольник для рисования части змейки
   * @param pixmap Изображение для части змейки
   * @param angle Угол поворота
   */
  void drawSnakePart(QPainter &painter, const QRect &cellRect,
                     const QPixmap &pixmap, int angle);

  /**
   * @brief Обрабатывает пользовательский ввод и выполняет соответствующее
   * действие
   * @param userInput Введенное пользователем значение
   * @param hold Флаг, указывающий, удерживается ли клавиша дейсвия
   */
  void getSignal(int userInput, bool hold);

  /**
   * @brief Рисует голову змейки
   * @param painter Объект для отрисовки на полотне
   * @param cellRect Прямоугольник для рисования головы змейки
   */
  void drawSnakeHead(QPainter &painter, const QRect &cellRect);

  /**
   * @brief Рисует тело змейки
   * @param painter Объект для отрисовки на полотне
   * @param cellRect Прямоугольник для рисования тела змейки
   * @param prev Пара предыдущих координат
   * @param next Пара следующих координат
   * @param current Пара текущих координат
   */
  void drawSnakeBody(QPainter &painter, const QRect &cellRect,
                     const std::pair<int, int> &prev,
                     const std::pair<int, int> &next,
                     const std::pair<int, int> &current);

  /**
   * @brief Рисует хвост змейки
   * @param painter Объект для отрисовки на полотне
   * @param cellRect Прямоугольник для рисования хвоста змейки
   * @param prev Пара предыдущих координат
   * @param current Пара текущих координат
   */
  void drawSnakeTail(QPainter &painter, const QRect &cellRect,
                     const std::pair<int, int> &prev,
                     const std::pair<int, int> &current);
};

#endif  // SNAKE_QT_H
