#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QVBoxLayout>

#ifdef SNAKE
#include "../../brick_game/snake/controller.h"
#include "../../brick_game/snake/fsm.h"
#include "../../brick_game/snake/snake.h"
#endif  // SNAKE

#ifdef TETRIS
#include "../../brick_game/brick_game/fsm.h"
#include "../../brick_game/brick_game/tetris.h"
#endif  // TETRIS

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief Главный класс окна приложения
 *
 * Этот класс представляет собой основное окно приложения и управляет его
 * интерфейсом.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса MainWindow
   * @param parent Родительский виджет (по умолчанию nullptr)
   */
  explicit MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Деструктор класса MainWindow
   */
  ~MainWindow();

 protected:
  Ui::MainWindow *ui;  ///< Указатель на пользовательский интерфейс

#ifdef SNAKE
  s21::Controller control;  ///< Контроллер игры "Змейка"
  s21::States state;        ///< Состояние игры "Змейка"
#endif                      // SNAKE

  QPixmap framePixmap;       ///< Изображение для рамки
  QPixmap bricksPixmap;      ///< Изображение для кирпичей
  QPixmap backGroundPixmap;  ///< Изображение для фона

  QLabel *highScoreValue =
      new QLabel(" ", this);  ///< Метка для отображения рекорда
  QLabel *scoreValue =
      new QLabel(" ", this);  ///< Метка для отображения текущего счета
  QLabel *levelValue = new QLabel(" ", this);  ///< Метка для отображения уровня
  QTimer *timer =
      new QTimer(this);  ///< Таймер для управления обновлением экрана

  static const int ROWS = 20;  ///< Количество строк в игровом поле
  static const int COLS = 10;  ///< Количество колонок в игровом поле
  static const int CELL_WIDTH = 30;  ///< Ширина ячейки игрового поля
  static const int CELL_HEIGHT = 30;  ///< Высота ячейки игрового поля
  static const int BORDER_THICKNESS = 10;  ///< Толщина границы игрового поля
  static const int FIELD_WIDTH = COLS * CELL_WIDTH;  ///< Ширина игрового поля
  static const int FIELD_HEIGHT = ROWS * CELL_HEIGHT;  ///< Высота игрового поля

  /**
   * @brief Настройка игрового окна
   */
  void GameWindow();

  /**
   * @brief Создание метки с текстом
   * @param text Текст метки
   * @param font Шрифт
   * @return Указатель на созданную метку
   */
  QLabel *createLabel(const QString &text, const QFont &font);

  /**
   * @brief Отображение следующей фигуры
   * @param painter Объект для отрисовки на полотне
   * @param nextFigure Прямоугольник для отображения следующей фигуры
   * @param backGround Изображения для фона
   */
  void printNext(QPainter &painter, QRect &nextFigure, QPixmap &backGround);

  /**
   * @brief Установка шрифта
   * @param font Шрифт
   */
  void setupFonts(QFont &font);

  /**
   * @brief Настройка компоновки меню
   * @param menuLayout Компоновка меню
   * @param font Шрифт
   */
  void setupMenuLayout(QVBoxLayout *menuLayout, const QFont &font);

  /**
   * @brief Рисование границы и меню
   * @param painter Объект для отрисовки на полотне
   * @param borderRectGame Прямоугольник для границы игрового поля
   * @param backGround Изображение для фона
   */
  void borderAndMenuPainter(QPainter &painter, QRect &borderRectGame,
                            QPixmap &backGround);

  /**
   * @brief Отображение текста по центру
   * @param painter Объект для отрисовки на полотне
   * @param rect Прямоугольник для текста
   * @param text Текст для отображения
   * @param color Цвет текста
   * @param fontSize Размер шрифта
   */
  void drawCenteredText(QPainter &painter, const QRect &rect,
                        const QString &text, QColor color, int fontSize);

  /**
   * @brief Отображение сообщения о паузе
   * @param painter Объект для отрисовки на полотне
   * @param borderRectGame Прямоугольник для границы игрового поля
   */
  void printPause(QPainter &painter, QRect &borderRectGame);

  /**
   * @brief Отображение сообщения о завершении игры
   * @param painter Объект для отрисовки на полотне
   * @param borderRectGame Прямоугольник для границы игрового поля
   */
  void printGameOver(QPainter &painter, QRect &borderRectGame);

  /**
   * @brief Отображение сообщения о победе
   * @param painter Объект для отрисовки на полотне
   * @param borderRectGame Прямоугольник для границы игрового поля
   */
  void printWin(QPainter &painter, QRect &borderRectGame);

  /**
   * @brief Отображение сообщения о начале игры
   * @param painter Объект для отрисовки на полотне
   * @param borderRectGame Прямоугольник для границы игрового поля
   * @param text Текст для отображения
   */
  void printStart(QPainter &painter, const QRect &borderRectGame,
                  const QString &text);

  /**
   * @brief Обновление информации в меню
   */
  void updateMenu();
};

#endif  // MAINWINDOW_H
