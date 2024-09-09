#include "tetrisQT.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  TetrisQT Tetris;
  Tetris.show();

  return app.exec();
}

TetrisQT::TetrisQT() : action(Start), hold(false) {
  srand(time(NULL));
  frame = updateCurrentState();
  tetr = update_current_figure();
  stateFSM = START;
  action = Nosig;
  bricks = QPixmap(":/imagesTetris/bricks.jpg");
  backGround = QPixmap(":/imagesMenu/backGround.jpg");
  GameWindow();

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TetrisQT::sendPeriodicSignal);
  timer->start(16);
}

void TetrisQT::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);

  QRect borderRectGame(0, 0, FIELD_WIDTH + 2 * BORDER_THICKNESS,
                       FIELD_HEIGHT + 2 * BORDER_THICKNESS);

  borderAndMenuPainter(painter, borderRectGame, backGround);

  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS; ++col) {
      QRect cellRect(col * CELL_WIDTH + BORDER_THICKNESS,
                     row * CELL_HEIGHT + BORDER_THICKNESS, CELL_WIDTH,
                     CELL_HEIGHT);
      int cellValue = frame.field[row][col];
      if (cellValue == 1 || cellValue == 2) {
        painter.drawPixmap(cellRect.x(), cellRect.y(), bricks);
      } else {
        painter.drawPixmap(cellRect.x(), cellRect.y(), backGround);
      }
    }
  }
  if (stateFSM == PAUSE)
    printPause(painter, borderRectGame);
  else if (stateFSM == START)
    printStart(painter, borderRectGame, "Tetris");
  else if (stateFSM == GAME_OVER)
    printGameOver(painter, borderRectGame);
}

void TetrisQT::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  getSignal(key, hold);
  if (action == Pause && stateFSM != START) {
    if (stateFSM == PAUSE)
      stateFSM = MOVE_FIGURE;
    else
      stateFSM = PAUSE;
  }
  if (action == Terminate) stateFSM = EXIT;
  if (action == Start && stateFSM == GAME_OVER) {
    stateFSM = START;
    score(&frame, 0, RESTART);
  }

  userInput(action, hold);
}

void TetrisQT::getSignal(int userInput, bool hold) {
  (void)hold;
  switch (userInput) {
    case Qt::Key_Up:
      action = Up;
      break;
    case Qt::Key_Down:
      action = Down;
      break;
    case Qt::Key_Left:
      action = Left;
      break;
    case Qt::Key_Right:
      action = Right;
      break;
    case Qt::Key_Escape:
      action = Terminate;
      close();
      break;
    case Qt::Key_P:
      action = Pause;
      break;
    case Qt::Key_Space:
      action = Action;
      break;
    case Qt::Key_Return:
      action = Start;
      break;
    case Qt::Key_Enter:
      action = Start;
      break;
    default:
      action = Nosig;
      break;
  }
}

void TetrisQT::updateField() {
  updateMenu();
  update();
}

void TetrisQT::userInput(UserAction_t action, int hold) {
  (void)hold;
  if (stateFSM != START || action == Start) {
    if (stateFSM != PAUSE && stateFSM != GAME_OVER)
      sigact(&action, &stateFSM, &frame, &tetr, &last_fall);
    frame = updateCurrentState();
    updateField();
  }
}

void TetrisQT::sendPeriodicSignal() {
  frame = updateCurrentState();
  if (stateFSM != START || action == Start) {
    if (stateFSM != PAUSE && stateFSM != GAME_OVER)
      sigact(&action, &stateFSM, &frame, &tetr, &last_fall);
    if (stateFSM == MOVE_FIGURE) action = Nosig;
    if (stateFSM == GAME_OVER) {
      clear_sector(frame.field, MAP_ROWS, MAP_COLS);
      clear_sector(frame.next, FIGURE_ROWS, FIGURE_COLS);
    }
    frame = updateCurrentState();
    updateField();
  }
}
