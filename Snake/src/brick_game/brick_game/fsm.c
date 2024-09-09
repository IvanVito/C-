#include "fsm.h"

actions fsm_table[8][9] = {
    {start_game, start_game, exit_state, start_game, start_game, start_game,
     start_game, start_game, start_game},
    {NULL, game_pause, exit_state, move_left, move_right, move_up, move_down,
     rotate_figure, shift_figure},
    {shift_figure, shift_figure, exit_state, shift_figure, shift_figure,
     shift_figure, shift_figure, shift_figure, shift_figure},
    {check_over, check_over, exit_state, check_over, check_over, check_over,
     check_over, check_over, check_over},
    {init_figure, init_figure, exit_state, init_figure, init_figure,
     init_figure, init_figure, init_figure, init_figure},
    {game_pause, game_pause, exit_state, game_pause, game_pause, game_pause,
     game_pause, game_pause, game_pause},
    {game_over, game_over, game_over, game_over, game_over, game_over,
     game_over, game_over, game_over},
    {exit_state, exit_state, exit_state, exit_state, exit_state, exit_state,
     exit_state, exit_state, exit_state}};

void start_game(params_t* prms) {
  prms->tetr->next_type = rand() % 7;
  init_figure(prms);
  *(prms->state) = MOVE_FIGURE;
}

void move_up(params_t* prms) { (void)prms; }

void move_down(params_t* prms) {
  clear_past_state(prms->frame, prms->tetr);
  while (attaching(prms->frame, prms->tetr) != 1) down(prms->tetr);
  *(prms->state) = SHIFT;
}

void move_right(params_t* prms) {
  right(prms->tetr);
  *(prms->state) = SHIFT;
}

void move_left(params_t* prms) {
  left(prms->tetr);
  *(prms->state) = SHIFT;
}

void rotate_figure(params_t* prms) {
  rotate(prms->frame, prms->tetr);
  *(prms->state) = SHIFT;
}

void shift_figure(params_t* prms) {
  shift(prms->frame, prms->tetr, prms->last_fall);
  move_figure(prms->frame, prms->tetr);
  *(prms->state) = CHECK;
}

void check_over(params_t* prms) {
  if (attaching(prms->frame, prms->tetr) == 1) {
    int game = game_end(prms->tetr);
    fix_figure(prms->frame, prms->tetr);
    if (game == 0) *(prms->state) = INIT_FIGURE;
    if (game == 1) *(prms->state) = GAME_OVER;
  } else {
    *(prms->state) = MOVE_FIGURE;
  }
}

void game_over(params_t* prms) {
  if (*(prms->action) == Start)
    *(prms->state) = START;
  else
    *(prms->state) = EXIT;
}

void init_figure(params_t* prms) {
  init(prms->frame, prms->tetr);
  if (*prms->state != START) *(prms->state) = MOVE_FIGURE;
}

void game_pause(params_t* prms) {
  if (*(prms->action) == Pause)
    *(prms->state) = MOVE_FIGURE;
  else
    *(prms->state) = EXIT;
}

void exit_state(params_t* prms) { *(prms->state) = EXIT; }

UserAction_t get_signal(int user_input) {
  UserAction_t sig = Nosig;
  if (user_input == ARROW_UP)
    sig = Up;
  else if (user_input == ARROW_DOWN)
    sig = Down;
  else if (user_input == ARROW_LEFT)
    sig = Left;
  else if (user_input == ARROW_RIGHT)
    sig = Right;
  else if (user_input == ESCAPE)
    sig = Terminate;
  else if (user_input == PAUSE_KEY)
    sig = Pause;
  else if (user_input == SPACE)
    sig = Action;
  else if (user_input == ENTER)
    sig = Start;
  return sig;
}

void sigact(UserAction_t* sig, states* state, GameInfo_t* frame, figure* tetr,
            struct timespec* last_fall) {
  actions act = fsm_table[*state][*sig];
  if (act != NULL) {
    params_t prms;
    prms.tetr = tetr;
    prms.frame = frame;
    prms.last_fall = last_fall;
    prms.state = state;
    prms.action = sig;
    act(&prms);
  }
}
