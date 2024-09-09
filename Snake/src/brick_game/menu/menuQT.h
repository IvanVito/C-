#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QApplication>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <iostream>

#include "../../gui/desktop/mainwindow.h"

#define SNAKE_GAME 0
#define TETRIS_GAME 1

/**
 * @brief Объект меню змейки
 */
class MenuWindow : public MainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса MenuWindow. В нем инициализруется массив
   * возможных опций и происходит настройка основного окна
   */
  MenuWindow();
  MenuWindow(MenuWindow &) = delete;
  MenuWindow(MenuWindow &&) = delete;

  ~MenuWindow() = default;

 protected:
  /**
   * @brief Функция отрисовывает фон, границы, сетку ячеек и текст
   * элементов меню на виджете.
   * @param event Не используется
   */
  void paintEvent(QPaintEvent *event) override;

  /**
   * @brief  Функция обрабатывает нажатия клавиш, позволяя перемещаться  и
   * выбирать элемент меню .После обработки события функция вызывает update()
   * для перерисовки виджета.
   * @param event Не используется
   */
  void keyPressEvent(QKeyEvent *event) override;

 private:
  const char *choices[2];
  int nChoices;
  int highlight;

  /**
   * @brief Запускает игру, создавая и выполняя команду для запуска указанного
   * исполняемого файла игры
   * @param game Имя игры
   */
  void launchGame(const char *game);
};

#endif  // MENUWINDOW_H
