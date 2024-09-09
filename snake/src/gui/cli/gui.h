#ifndef CPP3_BRICKGAME_V2_0_SRC_GUI_CLI_TETRIS_GUI_H_
#define CPP3_BRICKGAME_V2_0_SRC_GUI_CLI_TETRIS_GUI_H_

#define MAP_ROWS 20
#define MAP_COLS 10
#define BOARD_ROWS 12
#define BOARD_COLS 12
#define FIGURE_ROWS 4
#define FIGURE_COLS 4
#define END (-1)
#define PADDING 1

#include <ncurses.h>

#ifdef SNAKE
#define ESCAPE 27
#define SPACE 32
#define ENTER 10
#define LETTER_P 'p'
#define ARROW_UP 259
#define ARROW_DOWN 258
#define ARROW_LEFT 260
#define ARROW_RIGHT 261

/**
 * @brief Макрос для указания префикса имени класса (для С: пусто, а для С++:
 * Front::)
 */
#define CLASS Front::

#include "../../brick_game/snake/controller.h"

/**
 * @brief Класс, отвечающий за отрисовку игры
 */
namespace s21 {
struct GameInfo_t;
class Controller;
class Front {
 public:
  Front() = default;
  Front(Front&) = delete;
  Front(Front&&) = delete;

  ~Front() = default;
#else
#include "../../brick_game/brick_game/tetris.h"
#define CLASS
#endif  // SNAKE

  /**
   * @brief Функция отвечает за отрисовку игрового поля
   * @param frame Содержит информацию об игре
   */
  void print_field(GameInfo_t* frame);

  /**
   * @brief Функция печатает текущий счет, рекорд и уровень
   * @param tetr В данной игре не используется
   * @param stats Содержит информацию об игре
   */
  void print_stats(GameInfo_t* stats, void* tetr);

  /**
   * @brief Печатает шаблон рамки по координатам
   */
  void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

  /**
   * @brief Печатает рамки и графику меню
   */
  void menu();

  /**
   * @brief Печатает графику старта
   */
  void print_start();

  /**
   * @brief Печатает графику паузы
   */
  void print_pause();

  /**
   * @brief Печатает поле игры, устанавливает настройки терминала
   * @param frame Содержит информацию об игре
   */
  void init_front(GameInfo_t* frame);

  /**
   * @brief Печатает графику конца игры
   */
  void print_game_over();

  /**
   * @brief Обновляет игровое поле, счет и уровень
   * @param frame Содержит информацию об игре
   * @param tetr Не используется в данной игре
   */
  void refresh_scr(GameInfo_t* frame, void* tetr);

#ifdef SNAKE
  /**
   * @brief Функция печатает графику победы в игре
   */
  void print_win();
};
}  // namespace s21
#endif  // SNAKE

#endif  // CPP3_BRICKGAME_V2_0_SRC_GUI_CLI_TETRIS_GUI_H_
