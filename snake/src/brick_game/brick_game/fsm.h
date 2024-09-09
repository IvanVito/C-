#ifndef FSM_H
#define FSM_H

#define ARROW_UP 259
#define ARROW_DOWN 258
#define ARROW_LEFT 260
#define ARROW_RIGHT 261

#include "tetris.h"

/**
 * @brief Перечисление возможных сигналов
 * @param Action Этот сигнал поворачивает фигуру на 90 градусов
 * @param Nosig Нет сигнала
 * @param Terminate Сигнал завершения
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Nosig
} UserAction_t;

/**
 * @brief Перечисление возможных состояний конечного автомата
 * @param START Этот этап обрабатывает переход в 'режим игры', печать игрового
 * поля и начальную инициализацию фигуры
 * @param MOVE_FIGURE Этот этап обрабатывает движение фигуры в разных
 * направлениях и её поворот
 * @param SHIFT Этот этап выполняет выбранное движение, обрабатывает интервал
 * времени для перемещения и обновляет экран
 * @param CHECK Этот этап проверяет, окончена ли игра и зафиксирована ли фигура.
 * Если фигура зафиксирована, инициализируется новая фигура, иначе происходит
 * переход к MOVE_FIGURE
 * @param INIT_FIGURE Этот этап инициализирует фигуру и переходит к MOVE_FIGURE
 * @param PAUSE С этого этапа можно только выйти из игры или продолжить игру
 * @param GAME_OVER С этого этапа можно начать новую игру или выйти из игры
 * @param EXIT Это этап окончания игры. Здесь ничего нет, кроме завершения игры
 */
typedef enum {
  START,
  MOVE_FIGURE,
  SHIFT,
  CHECK,
  INIT_FIGURE,
  PAUSE,
  GAME_OVER,
  EXIT
} states;

/**
 * @brief Структура с параметрами, необходимыми для функций
 */
typedef struct {
  figure* tetr;
  GameInfo_t* frame;
  struct timespec* last_fall;
  states* state;
  UserAction_t* action;
} params_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Функция вызывается на этапе START. Действия функции описаны в
 * описании этапа
 */
void start_game(params_t* prms);

/**
 * @brief Заглушка. Не используется
 */
void move_up(params_t* prms);

/**
 * @brief Опускает фигуры вниз до тех пор, пока они не зафиксируются
 */
void move_down(params_t* prms);
void move_right(params_t* prms);
void move_left(params_t* prms);
void rotate_figure(params_t* prms);

/**
 * @brief Перемещает фигуру вниз с интервалами времени и обновляет экран
 */
void shift_figure(params_t* prms);

/**
 * @brief Проверяет, может ли зафиксироваться фигура. Если может, то
 * фиксирует ее и переводит автомат в INIT_FIGURE. Иначе переводаит КА в
 * INIT_FIGURE. Также проверяет игру на завершение.
 */
void check_over(params_t* prms);

/**
 * @brief Инициализирует настоящую и следующую форму фигуры и переводит КА в
 * состояние MOVE_FIGURE
 */
void init_figure(params_t* prms);

/**
 * @brief Переводит КА в состояние MOVE_FIGURE, если действие в состоянии PAUSE
 * было Pause. Иначе переводит КА в состояние EXIT
 */
void game_pause(params_t* prms);

/**
 * @brief Завершает игру
 */
void exit_state(params_t* prms);

/**
 * @brief Очищает все поля, обновляет экран и предлагает сыграть снова
 */
void game_over(params_t* prms);

/**
 * @brief Преобразует нажатие кнопки в сигнал
 * @param user_input Нажатая кнопка
 * @return Сигнал
 */
UserAction_t get_signal(int user_input);

/**
 * @brief Инициализирует структуру параметров и выполняет выбранную функцию на
 * основе этапа и переданного сигнала
 * @param sig Указатель на сигнал
 * @param state Указатель на этап
 * @param frame Указатель на поле
 * @param tetr Указатель на фигуру
 * @param last_fall Указатель на время последнего падения фигуры
 */
void sigact(UserAction_t* sig, states* state, GameInfo_t* frame, figure* tetr,
            struct timespec* last_fall);

/**
 * @brief Определение указателя на функцию, принимающую указатель на структуру
 * 'params_t' и возвращающую void
 */
typedef void (*actions)(params_t* prms);

#ifdef __cplusplus
}
#endif

#endif  // FSM_H
