#include "controller.h"

void s21::Controller::up(bool hold) {
  fsm.userInput(s21::UserAction_t::Up, hold);
}
void s21::Controller::down(bool hold) {
  fsm.userInput(s21::UserAction_t::Down, hold);
}
void s21::Controller::left(bool hold) {
  fsm.userInput(s21::UserAction_t::Left, hold);
}
void s21::Controller::right(bool hold) {
  fsm.userInput(s21::UserAction_t::Right, hold);
}
void s21::Controller::terminate(bool hold) {
  fsm.userInput(s21::UserAction_t::Terminate, hold);
}
void s21::Controller::pause(bool hold) {
  fsm.userInput(s21::UserAction_t::Pause, hold);
}
void s21::Controller::action(bool hold) {
  fsm.userInput(s21::UserAction_t::Action, hold);
}
void s21::Controller::start(bool hold) {
  fsm.userInput(s21::UserAction_t::Start, hold);
}
void s21::Controller::currentAction(bool hold) {
  fsm.userInput(fsm.getCurrentAction(), hold);
}
