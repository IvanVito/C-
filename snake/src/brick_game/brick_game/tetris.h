#ifndef TETRIS_H
#define TETRIS_H
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L  // Для измерения временных интервалов
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Константы
#define ESCAPE 27
#define SPACE 32
#define ENTER 10
#define PAUSE_KEY 112
#define FIGURE_ROWS 4
#define FIGURE_COLS 4
#define FIGURES 10
#define RESTART 1
#define NO_RESTART 0
#define MAP_ROWS 20
#define MAP_COLS 10

/**
 * @brief Массив форм фигур
 */
static const int shapes[FIGURES][FIGURE_ROWS][FIGURE_COLS] = {
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // I 0
    {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // O
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // S
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // Z
    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // L
    {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // J
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // T
    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},  // I 90
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // I 180
    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},  // I 270
};

/**
 * @brief Структура фигуры
 * @param current_shape Указатель на массив с текущей формой фигуры
 * @param x Абсцисса
 * @param y Ордината
 * @param last_x Предыдущая абсцисса
 * @param type Тип фигуры из массива форм
 * @param next_type Тип следующей фигуры из массива форм
 */
typedef struct {
  int** current_shape;
  int x, y;
  int last_x;
  int type;
  int next_type;
} figure;

/**
 * @brief Структура поля
 * @param field Указатель на массив с игровым полем
 * @param next Указатель на массив с формой следующей фигуры
 * @param score Игровой счёт
 * @param high_score Рекорд игры
 * @param level Уровень игры
 * @param speed Скорость игры. Коэффициент, уменьшающий время между тиками
 */
typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
} GameInfo_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Возвращает текущую фигуру
 * @return Копия фигуры
 */
figure update_current_figure();

/**
 * @brief Выделяет память для поля с заданным количеством строк и столбцов
 */
int** create_field(int rows, int cols);

/**
 * @brief Освобождает память для поля, ранее выделенной с заданным количеством
 * строк
 */
void clear_field(int*** field, int rows);

/**
 * @brief Заполняет переданную матрицу шаблоном из массива фигур
 * @param matr Матрица для заполнения
 * @param matr_pattern Шаблон из массива фигур
 */
void picked_matrix(int** matr,
                   const int matr_pattern[FIGURE_ROWS][FIGURE_COLS]);

/**
 * @brief Поворачивает текущую фигуру на 90 градусов по часовой стрелке
 */
void transporate_matrix(figure* tetr);

/**
 * @brief Фиксирует фигуру на поле, если она больше не может падать
 */
void fix_figure(GameInfo_t* frame, figure* tetr);

/**
 * @brief Проверяет столкновение с боковыми границами
 * @return 1 если столкновение, иначе 0
 */
int collision_with_sides(GameInfo_t* frame, figure* tetr);

/**
 * @brief Проверяет столкновение с дном (с фиксированными фигурами или дном
 * поля)
 * @return 1 если столкновение, иначе 0
 */
int collision_with_bottom(GameInfo_t* frame, figure* tetr);

/**
 * @brief Проверяет возможность фиксации фигуры
 * @return 1 если возможна фиксация, иначе 0
 */
int attaching(GameInfo_t* frame, figure* tetr);

/**
 * @brief Двигает фигуру. Вызывается, если движение возможно
 */
void move_figure(GameInfo_t* frame, figure* tetr);

/**
 * @brief Отвечает за обновление поля. Удаляет заполненные строки и изменяет
 * счёт, максимальный счёт и скорость игры
 */
void delete_row(GameInfo_t* frame);

/**
 * @brief Перемещает строки поля вниз
 */
void pull_rows(GameInfo_t* frame, int before_row);

/**
 * @brief Записывает рекорд в файл. Создаёт файл, если он не существует, и
 * записывает в него 0
 * @param record Рекордный счёт
 * @return Ошибка. (1 - ошибка существует, 0 - ошибки нет)
 */
int record(int record);

/**
 * @brief Читает рекорд из файла. Создаёт файл, если он не существует, и
 * записывает в него 0. После этого читает его
 * @return Ошибка. (1 - ошибка существует, 0 - ошибки нет)
 */
int read_record(GameInfo_t* frame);

/**
 * @brief Удаляет предыдущую фигуру с поля
 */
void clear_past_state(GameInfo_t* frame, figure* tetr);

/**
 * @brief Проверяет, окончена ли игра. Игра заканчивается, когда фигура не может
 * двигаться и её y-координата отрицательная
 * @return 1 - если игра окончена, иначе 0
 */
int game_end(figure* tetr);

/**
 * @brief Заполняет выбранную область матрицы нулями
 * @param sector Указатель на матрицу
 * @param rows Строки, до которых значения матрицы устанавливаются в ноль
 * (исключительно)
 * @param cols Столбцы, до которых значения матрицы устанавливаются в ноль
 * (исключительно)
 */
void clear_sector(int** sector, int rows, int cols);

/**
 * @brief Проверяет возможность поворота фигуры. Если невозможно, отменяет
 * изменения
 */
void rotate(GameInfo_t* frame, figure* tetr);

/**
 * @brief Устанавливает начальные координаты фигуры, следующую и текущую форму
 */
void init(GameInfo_t* frame, figure* tetr);

/**
 * @brief Перемещает фигуру вниз через установленный интервал времени
 * @param last_fall Время последнего падения фигуры
 */
void shift(GameInfo_t* frame, figure* tetr, struct timespec* last_fall);

/**
 * @brief Функция обновляет состояние поля и возвращает его копию
 */
GameInfo_t updateCurrentState();

/**
 * @brief Двигает фигуру вниз
 */
void down(figure* tetr);

/**
 * @brief Двигает фигуру вправо
 */
void right(figure* tetr);

/**
 * @brief Двигает фигуру влево
 */
void left(figure* tetr);

/**
 * @brief Заглушка. Не используется
 */
void up(figure* tetr);

/**
 * @brief Эта функция обрабатывает счёт, записывает рекорд и
 * увеличивает уровень
 * @param lines Количество заполненных строк, за которые начисляются очки
 * @param restart Флаг перезапуска игры
 */
void score(GameInfo_t* frame, int lines, int restart);

#ifdef __cplusplus
}
#endif

#endif  // TETRIS_H
