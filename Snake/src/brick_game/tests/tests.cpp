#include "tests.h"

TEST(move, ordinaryUpVectorUp) {
  s21::SnakeStateMachine FSM;
  FSM.userInput(s21::UserAction_t::Up, true);

  EXPECT_EQ(8, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryDownVectorUp) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Down, true);

  EXPECT_EQ(9, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryLeftVectorUp) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Left, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(4, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryRightVectorUp) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Right, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(6, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryUpVectorDown) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::DOWN, 0);
  FSM.userInput(s21::UserAction_t::Up, true);

  EXPECT_EQ(11, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryDownVectorDown) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::DOWN, 0);
  FSM.userInput(s21::UserAction_t::Down, true);

  EXPECT_EQ(11, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryRightVectorDown) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::DOWN, 0);
  FSM.userInput(s21::UserAction_t::Right, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(6, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryLeftVectorDown) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::DOWN, 0);
  FSM.userInput(s21::UserAction_t::Left, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(4, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryLeftVectorLeft) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::LEFT, 0);
  FSM.userInput(s21::UserAction_t::Left, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(4, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryRightVectorLeft) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::LEFT, 0);
  FSM.userInput(s21::UserAction_t::Right, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(4, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryUpVectorLeft) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::LEFT, 0);
  FSM.userInput(s21::UserAction_t::Up, true);

  EXPECT_EQ(9, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryDownVectorLeft) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::LEFT, 0);
  FSM.userInput(s21::UserAction_t::Down, true);

  EXPECT_EQ(11, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryLeftVectorRight) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::RIGHT,
                             0);
  FSM.userInput(s21::UserAction_t::Left, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(6, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryRightVectorRight) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::RIGHT,
                             0);
  FSM.userInput(s21::UserAction_t::Right, true);

  EXPECT_EQ(10, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(6, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryUpVectorRight) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::RIGHT,
                             0);
  FSM.userInput(s21::UserAction_t::Up, true);

  EXPECT_EQ(9, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, ordinaryDownVectorRight) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::RIGHT,
                             0);
  FSM.userInput(s21::UserAction_t::Down, true);

  EXPECT_EQ(11, FSM.getSnake().getBody().front().first);
  EXPECT_EQ(5, FSM.getSnake().getBody().front().second);
}

TEST(move, accelerateAndHold) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.setAccelerate(true);
  FSM.userInput(s21::UserAction_t::Action, true);

  EXPECT_EQ(240, FSM.getDelay());
  EXPECT_TRUE(FSM.getAccelerate());
}

TEST(move, accelerateWithoutHold) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Action, false);

  EXPECT_EQ(440, FSM.getDelay());
  EXPECT_FALSE(FSM.getAccelerate());
  EXPECT_FALSE(FSM.getHold());
}

TEST(FSM, startToCheck) {
  s21::SnakeStateMachine FSM(s21::States::Start, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Start, true);

  EXPECT_EQ(s21::States::Check, FSM.getCurrentState());
}

TEST(FSM, startToExit) {
  s21::SnakeStateMachine FSM(s21::States::Start, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Terminate, true);

  EXPECT_EQ(s21::States::Exit, FSM.getCurrentState());
}

TEST(FSM, checkToPause) {
  s21::SnakeStateMachine FSM(s21::States::Check, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Pause, true);

  EXPECT_EQ(s21::States::Pause, FSM.getCurrentState());
}

TEST(FSM, CheckToGameOver) {
  s21::SnakeStateMachine FSM(s21::States::Check, 5, -1, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Up, true);

  EXPECT_EQ(s21::States::GameOver, FSM.getCurrentState());
}

TEST(FSM, CheckToMove) {
  s21::SnakeStateMachine FSM(s21::States::Check, 5, 0, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Down, true);

  EXPECT_EQ(s21::States::Move, FSM.getCurrentState());
}

TEST(FSM, CheckToWin) {
  s21::SnakeStateMachine FSM(s21::States::Check, 5, 10, s21::Direction::UP,
                             200);
  FSM.userInput(s21::UserAction_t::Start, true);

  EXPECT_EQ(s21::States::Win, FSM.getCurrentState());
}

TEST(FSM, pauseToCheck) {
  s21::SnakeStateMachine FSM(s21::States::Pause, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Pause, true);

  EXPECT_EQ(s21::States::Check, FSM.getCurrentState());
}

TEST(FSM, pauseToExit) {
  s21::SnakeStateMachine FSM(s21::States::Pause, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Terminate, true);

  EXPECT_EQ(s21::States::Exit, FSM.getCurrentState());
}

TEST(FSM, winToExit) {
  s21::SnakeStateMachine FSM(s21::States::Win, 5, 10, s21::Direction::UP, 200);
  FSM.userInput(s21::UserAction_t::Terminate, true);

  EXPECT_EQ(s21::States::Exit, FSM.getCurrentState());
}

TEST(FSM, gameOverToStart) {
  s21::SnakeStateMachine FSM(s21::States::GameOver, 5, 10, s21::Direction::UP,
                             0);
  FSM.userInput(s21::UserAction_t::Start, true);

  EXPECT_EQ(s21::States::Start, FSM.getCurrentState());
  EXPECT_EQ(s21::UserAction_t::Down, FSM.getCurrentAction());
}

TEST(FSM, gameOverToExit) {
  s21::SnakeStateMachine FSM(s21::States::GameOver, 5, 10, s21::Direction::UP,
                             0);
  FSM.userInput(s21::UserAction_t::Terminate, true);

  EXPECT_EQ(s21::States::Exit, FSM.getCurrentState());
}

TEST(FSM, MoveToCheck) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.userInput(s21::UserAction_t::Up, true);

  EXPECT_EQ(s21::States::Check, FSM.getCurrentState());
}

TEST(Snake, eatAppleTailDown) {
  s21::SnakeStateMachine FSM(s21::States::Move, 5, 10, s21::Direction::UP, 0);
  FSM.getSnake().testPlaceApple();
  FSM.userInput(s21::UserAction_t::Up, true);
  FSM.userInput(s21::UserAction_t::Up, false);

  EXPECT_EQ(1, FSM.updateCurrentState().score);
}

TEST(Snake, eatAppleTailLeft) {
  s21::SnakeStateMachine FSM(s21::States::Move, 1, 9, s21::Direction::RIGHT, 0);
  FSM.getSnake().testPlaceApple();
  while (FSM.updateCurrentState().score != 1)
    FSM.userInput(s21::UserAction_t::Right, true);

  EXPECT_EQ(1, FSM.updateCurrentState().score);
}

TEST(Snake, eatAppleTailRight) {
  s21::SnakeStateMachine FSM(s21::States::Move, 9, 9, s21::Direction::LEFT, 0);
  FSM.getSnake().testPlaceApple();
  while (FSM.updateCurrentState().score != 1)
    FSM.userInput(s21::UserAction_t::Left, true);

  EXPECT_EQ(1, FSM.updateCurrentState().score);
}

TEST(Snake, eatAppleTailUp) {
  s21::SnakeStateMachine FSM(s21::States::Move, 9, 9, s21::Direction::UP, 0);
  FSM.getSnake().testPlaceApple();
  while (FSM.getSnake().getBody().front().first != 4)
    FSM.userInput(s21::UserAction_t::Up, true);

  while (FSM.getSnake().getBody().front().second != 5)
    FSM.userInput(s21::UserAction_t::Left, true);

  while (FSM.updateCurrentState().score != 1)
    FSM.userInput(s21::UserAction_t::Down, true);

  EXPECT_EQ(1, FSM.updateCurrentState().score);
}

TEST(Snake, Collision) {
  s21::SnakeStateMachine FSM(s21::States::Move, 1, 9, s21::Direction::RIGHT, 0);
  while (FSM.getSnake().getBody().front().second < 10)
    FSM.userInput(s21::UserAction_t::Right, true);
  FSM.userInput(s21::UserAction_t::Right, false);
  FSM.userInput(s21::UserAction_t::Right, false);

  EXPECT_EQ(s21::States::GameOver, FSM.getCurrentState());
}
