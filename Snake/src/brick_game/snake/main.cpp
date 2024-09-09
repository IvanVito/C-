#include "../../gui/cli/gui.h"
#include "controller.h"

/**
 * @brief Функция инициализирует и печатает поле, печатает графику состояния
 * "Start"
 * @param front Является объектом интерфейса
 * @param control Является объектом контроллера
 * @param action Является переменной для действия
 */
void startState(s21::Front &front, s21::Controller &control, int &action) {
  auto info = control.fsm.updateCurrentState();
  front.init_front(&info);
  front.print_field(&info);
  front.print_start();
  action = getch();
  while (action != ENTER && action != ESCAPE) action = getch();
}

/**
 * @brief Функция обеспечивает ввод следующего сигнала в течение врмени
 * задержки. Устанавливает или снимает ускорение
 * @param control Является объектом контроллера
 * @param action Является переменной для действия
 * @param hold Является переменной, отвечающей за факт нажатия кнопки
 */
void moveState(s21::Controller &control, int &action, bool &hold) {
  auto start = std::chrono::high_resolution_clock::now();
  auto end = start + std::chrono::milliseconds(control.fsm.getDelay());
  bool done = false;
  control.fsm.setAccelerate(false);
  while (std::chrono::high_resolution_clock::now() < end) {
    if (!done) action = getch();
    flushinp();
    if (action != ERR) done = true;
    if (action == SPACE) {
      control.fsm.setAccelerate(true);
      done = false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(40));
  }
  hold = (action != ERR);
}

/**
 * @brief Функция печатает графику паузы и ожидает ввода от пользователя
 * (продолжить игру или выйти)
 * @param front Является объектом интерфейса
 * @param action Является переменной для действия
 */
void pauseState(s21::Front &front, int &action) {
  front.print_pause();
  action = getch();
  while (action != LETTER_P && action != ESCAPE) action = getch();
}

/**
 * @brief Функция печатает графику конца игры и ждет ввода пользователя (начать
 * игру сначала или выйти)
 * @param front Является объектом интерфейса
 * @param control Является объектом контроллера
 * @param action Является переменной для действия
 */
void gameOverState(s21::Front &front, s21::Controller &control, int &action) {
  auto info = control.fsm.updateCurrentState();
  front.refresh_scr(&info, nullptr);
  front.print_game_over();
  action = getch();
  while (action != ENTER && action != ESCAPE) action = getch();
}

/**
 * @brief Функция печатает графику состояния победы и ждет ввода пользователя
 * для выхода из игры
 * @param front Является объектом интерфейса
 * @param control Является объектом контроллера
 * @param action Является переменной для действия
 */
void winState(s21::Front &front, s21::Controller &control, int &action) {
  auto info = control.fsm.updateCurrentState();
  front.refresh_scr(&info, nullptr);
  action = getch();
  front.print_win();
  while (action != ESCAPE) action = getch();
}

/**
 * @brief Функция преобразует введенную клавишу в вызов функции КА с игровым
 * сигналом
 * @param userInput Нажатая пользователем кнопка
 * @param control Является объектом контроллера
 * @param hold Отвечает за факт нажатия известной кнопки
 */

void getSignal(int userInput, bool hold, s21::Controller &control) {
  if (userInput == ARROW_UP)
    control.up(hold);
  else if (userInput == ARROW_DOWN)
    control.down(hold);
  else if (userInput == ARROW_LEFT)
    control.left(hold);
  else if (userInput == ARROW_RIGHT)
    control.right(hold);
  else if (userInput == ESCAPE)
    control.terminate(hold);
  else if (userInput == LETTER_P)
    control.pause(hold);
  else if (userInput == SPACE)
    control.action(hold);
  else if (userInput == ENTER)
    control.start(hold);
  else
    control.currentAction(hold);
}

/**
 * @brief Основной игровой цикл с созданием и управлением игровыми объектами
 */
int main() {
  s21::Controller control;
  s21::States state = s21::States::Start;
  s21::Front front;
  int action = ERR;
  bool hold = false;
  while (state != s21::States::Exit) {
    auto info = control.fsm.updateCurrentState();
    if (state == s21::States::Move)
      moveState(control, action, hold);
    else if (state == s21::States::Start)
      startState(front, control, action);

    getSignal(action, hold, control);
    state = control.fsm.getCurrentState();
    action = ERR;

    if (state == s21::States::Move) front.refresh_scr(&info, nullptr);
    if (state == s21::States::Pause)
      pauseState(front, action);
    else if (state == s21::States::GameOver)
      gameOverState(front, control, action);
    else if (state == s21::States::Win)
      winState(front, control, action);
  }
  endwin();
  return 0;
}