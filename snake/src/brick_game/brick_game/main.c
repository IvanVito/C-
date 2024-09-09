#define _POSIX_C_SOURCE 199309L

#include "../../gui/cli/gui.h"
#include "fsm.h"
#include "tetris.h"

/**
 * @brief The function handles two states : pause and game over.To exit from the
 * pause, you can only press "p" or "Esc".When the game is over, the score is
 * reset, the field is cleared, and a splash screen is displayed.From the game
 * over state, you can either start a new game or exit
 * @param action Current action
 * @param state Current state FSM
 * @param frame Structure responsible for menu information and field state
 * @param tetr Structure responsible for the type of figure and its location
 */
void front_action(UserAction_t* action, states state, GameInfo_t* frame,
                  figure* tetr) {
  if (*action == Pause) {
    print_pause();
    refresh();
    int game_paused = 1, button = 0;
    while (game_paused == 1) {
      button = getch();
      if (button == PAUSE_KEY || button == 'P' || button == ESCAPE)
        game_paused = 0;
    }
    if (button == PAUSE_KEY || button == 'P')
      *action = Pause;
    else
      *action = Terminate;
  }

  if (state == GAME_OVER) {
    tetr->type = END;
    clear_sector(frame->field, MAP_ROWS, MAP_COLS);
    clear_sector(frame->next, FIGURE_ROWS, FIGURE_COLS);
    clear_sector(tetr->current_shape, FIGURE_ROWS, FIGURE_COLS);
    refresh_scr(frame, tetr);
    print_game_over();
    refresh();
    int button = getch();
    while (button != ENTER && button != ESCAPE) button = getch();
    if (button == ENTER) {
      *action = Start;
      score(frame, 0, RESTART);
    }
  }
}

/**
 * @brief Main function. Initial field, figure, and time-before-move-down
 * initialization is performed. The finite state machine operates until the EXIT
 * stage is reached. Memory is cleared before exiting the program
 * @param action Current action
 * @param hold Flag for button action press
 */
void userInput(UserAction_t action, int hold) {
  (void)hold;
  int go = 0;
  states state = START;
  GameInfo_t frame = updateCurrentState();
  figure tetr = update_current_figure();
  init_front(&frame);
  print_field(&frame);
  print_start();
  srand(time(NULL));
  struct timespec last_fall;
  clock_gettime(CLOCK_MONOTONIC, &last_fall);
  while (go != ENTER && go != ESCAPE) go = getch();
  if (go == ENTER) {
    while (state != EXIT) {
      front_action(&action, state, &frame, &tetr);
      sigact(&action, &state, &frame, &tetr, &last_fall);
      if (state == MOVE_FIGURE || state == START) action = get_signal(getch());
      frame = updateCurrentState();
      refresh_scr(&frame, &tetr);
    }
  }

  napms(200);  // For displaying figure drop, if only one block goes out of
  clear_field(&frame.field, MAP_ROWS);
  clear_field(&frame.next, FIGURE_ROWS);
  clear_field(&tetr.current_shape, FIGURE_ROWS);
}

int main() {
  UserAction_t action = Start;
  userInput(action, 0);
  endwin();
  return 0;
}