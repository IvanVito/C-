#include "fsm.h"

using namespace s21;

SnakeStateMachine::SnakeStateMachine()
    : action_(UserAction_t::Down),
      currentState_(States::Start),
      snake_(),
      hold_(false),
      delay_(START_SPEED),
      accelerate_(false) {}

SnakeStateMachine::SnakeStateMachine(States state, int x, int y,
                                     s21::Direction dir, int score)
    : action_(),
      currentState_(state),
      snake_(INIT_SIZE_SNAKE, {y, x}, dir),
      hold_(false),
      delay_(START_SPEED),
      accelerate_(false) {
  snake_.info_.score = score;
}

void SnakeStateMachine::userInput(UserAction_t action, bool hold) {
  action_ = action;
  delay_ =
      START_SPEED - (snake_.info_.speed + accelerate_ * ACCELERATE * (int)hold);

  (this->*stateMatrix[static_cast<int>(currentState_)]
                     [static_cast<int>(action_)])();
}

void SnakeStateMachine::start() {
  if (action_ == UserAction_t::Start) {
    snake_.readRecord();
    snake_.placeApple();
    snake_.printSnake();
    currentState_ = States::Check;
  } else if (action_ == UserAction_t::Terminate)
    currentState_ = States::Exit;
}

void SnakeStateMachine::move() {
  snake_.handleInput(action_);
  snake_.clearPastState();
  if (action_ != s21::UserAction_t::Pause) snake_.move();
  snake_.printSnake();
  currentState_ = States::Check;
}

void SnakeStateMachine::check() {
  if (snake_.checkCollision()) {
    snake_.clearField();
    currentState_ = States::GameOver;
  } else if (snake_.info_.score == MAX_SCORE) {
    snake_.clearField();
    currentState_ = States::Win;
  } else if (action_ == UserAction_t::Pause) {
    currentState_ = States::Pause;
  } else {
    currentState_ = States::Move;
  }
}

void SnakeStateMachine::pause() {
  if (action_ == UserAction_t::Pause) {
    action_ = UserAction_t::Start;
    currentState_ = States::Check;
  } else if (action_ == UserAction_t::Terminate) {
    currentState_ = States::Exit;
  }
}

void SnakeStateMachine::gameOver() {
  if (action_ == s21::UserAction_t::Start) {
    snake_.info_ = GameInfo_t();
    snake_ = Snake();
    action_ = UserAction_t::Down;
    currentState_ = States::Start;
  } else if (action_ == s21::UserAction_t::Terminate)
    currentState_ = States::Exit;
}

void SnakeStateMachine::win() {
  if (action_ == UserAction_t::Terminate) currentState_ = States::Exit;
}
void SnakeStateMachine::exit() { currentState_ = States::Exit; }
bool SnakeStateMachine::getHold() { return hold_; }
States SnakeStateMachine::getCurrentState() { return currentState_; }
GameInfo_t SnakeStateMachine::updateCurrentState() { return snake_.info_; }
UserAction_t SnakeStateMachine::getCurrentAction() { return action_; }
int SnakeStateMachine::getDelay() { return delay_; }
Snake& SnakeStateMachine::getSnake() { return snake_; }
void SnakeStateMachine::setAccelerate(bool value) { accelerate_ = value; }
bool SnakeStateMachine::getAccelerate() { return accelerate_; }
