#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../../gui/cli/gui.h"
#include "../snake/snake.h"

#define SNAKE_GAME 0
#define TETRIS_GAME 1

/**
 * @brief Запускает игру, создавая и выполняя команду для запуска указанного
 * исполняемого файла игры.
 * @param game Название игры
 */
void launchGame(const char* game) {
  std::string command = "build/cli/";
  command += game;
  bool err = std::system(command.c_str());
  if (err != 0) std::cerr << "Command failed with code " << err << std::endl;
}

/**
 * @brief Отображает главное меню с вариантами выбора различных игр.
 * @param highlight Параметр определяет, какой элемент меню в данный момент
 * выделен
 * @param info Структура, ответственная за информацию о меню и состояние поля
 * @param front Объект, ответственный за рендеринг игры
 */
void displayMenu(int highlight, s21::GameInfo_t& info, s21::Front& front) {
  const char* choices[] = {"Snake", "Tetris"};
  int nChoices = sizeof(choices) / sizeof(choices[0]);

  front.init_front(&info);
  for (int i = 0; i < nChoices; ++i) {
    if (i == highlight)
      attron(A_REVERSE);
    else
      attroff(A_REVERSE);

    mvprintw(MAP_ROWS / 2 + i, (MAP_COLS + PADDING * 4) / 2 - 4, "%s",
             choices[i]);
  }
  attroff(A_REVERSE);
  refresh();
}

/**
 * @brief Обновляет выделение в меню
 * @param highlight Новый выделенный элемент
 * @param prev_highlight Предыдущий элемент
 * @param choices Массив названий игр
 */
void updateSelection(int highlight, int prev_highlight, const char* choices[]) {
  move(MAP_ROWS / 2 + prev_highlight, (MAP_COLS + PADDING * 4) / 2 - 4);
  printw("%s", choices[prev_highlight]);

  attron(A_REVERSE);
  move(MAP_ROWS / 2 + highlight, (MAP_COLS + PADDING * 4) / 2 - 4);
  printw("%s", choices[highlight]);
  attroff(A_REVERSE);

  refresh();
}

/**
 * @brief Основная функция для управления меню и процессом выбора игры
 */
int main() {
  int highlight = 0, choice = 0;
  bool running = true;
  s21::Front front;
  s21::GameInfo_t info;
  front.init_front(&info);
  const char* choices[] = {"Snake", "Tetris"};
  int nChoices = sizeof(choices) / sizeof(choices[0]);
  displayMenu(highlight, info, front);

  while (running) {
    int c = getch();
    int prev_highlight = highlight;
    switch (c) {
      case KEY_UP:
        if (highlight > 0) --highlight;
        break;
      case KEY_DOWN:
        if (highlight < nChoices - 1) ++highlight;
        break;
      case ENTER:
        choice = highlight;
        switch (choice) {
          case SNAKE_GAME:
            endwin();
            launchGame("snake");
            clear();
            displayMenu(highlight, info, front);
            break;
          case TETRIS_GAME:
            endwin();
            launchGame("tetris");
            clear();
            displayMenu(highlight, info, front);
            break;
          default:
            break;
        }
        break;
      case ESCAPE:
        running = false;
      default:
        break;
    }
    if (highlight != prev_highlight)
      updateSelection(highlight, prev_highlight, choices);
  }
  endwin();
  return 0;
}
