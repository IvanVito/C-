#include "snakeQT.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  SnakeQT Snake;
  Snake.show();

  return app.exec();
}

SnakeQT::SnakeQT()
    : action(-1),
      hold(false),
      apple(":/imagesSnake/apple.jpg"),
      backGround(":/imagesSnake/front.jpg"),
      snakeHead(":/imagesSnake/snakeHead.jpg"),
      snakeBody(":/imagesSnake/snakeBody.jpg"),
      snakeBodyTurn(":/imagesSnake/snakeBodyTurn.jpg"),
      snakeTail(":/imagesSnake/snakeTail.jpg") {
  GameWindow();

  connect(timer, &QTimer::timeout, this, &SnakeQT::sendPeriodicSignal);
  timer->start(control.fsm.getDelay());
}

void SnakeQT::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);

  QRect borderRectGame(0, 0, FIELD_WIDTH + 2 * BORDER_THICKNESS,
                       FIELD_HEIGHT + 2 * BORDER_THICKNESS);

  borderAndMenuPainter(painter, borderRectGame, backGround);

  auto body = control.fsm.getSnake().getBody();
  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS; ++col) {
      QRect cellRect(col * CELL_WIDTH + BORDER_THICKNESS,
                     row * CELL_HEIGHT + BORDER_THICKNESS, CELL_WIDTH,
                     CELL_HEIGHT);
      int cellValue = control.fsm.updateCurrentState().field[row][col];
      auto it = std::find(body.begin(), body.end(), std::make_pair(row, col));
      if (cellValue == 1) {
        if (it == body.begin()) {
          drawSnakeHead(painter, cellRect);
        } else if (it == body.end() - 1) {
          drawSnakeTail(painter, cellRect, *(it - 1), std::make_pair(row, col));
        } else {
          drawSnakeBody(painter, cellRect, *(it - 1), *(it + 1),
                        std::make_pair(row, col));
        }
      } else if (cellValue == 2) {
        painter.drawPixmap(cellRect.x(), cellRect.y(), apple);
      } else {
        painter.drawPixmap(cellRect.x(), cellRect.y(), backGround);
      }
    }
  }
  auto currentState = control.fsm.getCurrentState();
  if (currentState == s21::States::Pause)
    printPause(painter, borderRectGame);
  else if (currentState == s21::States::Start)
    printStart(painter, borderRectGame, "Snake");
  else if (currentState == s21::States::GameOver)
    printGameOver(painter, borderRectGame);
  else if (currentState == s21::States::Win)
    printGameOver(painter, borderRectGame);
}

void SnakeQT::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  if (key == Qt::Key_Return || key == Qt::Key_Enter) key = ENTER;

  auto currentState = control.fsm.getCurrentState();

  if (currentState == s21::States::Start && key != ENTER &&
      key != Qt::Key_Escape) {
    key = -1;
  } else if (action == Qt::Key_P) {
    if (key == Qt::Key_P)
      key = 0;
    else
      key = (key == Qt::Key_Escape) ? Qt::Key_Escape : Qt::Key_P;
  } else if (currentState == s21::States::GameOver ||
             currentState == s21::States::Win) {
    if (key != ENTER && key != Qt::Key_Escape) key = -1;
  } else if (currentState == s21::States::Move) {
    hold = (key != Qt::Key_unknown);
    if (key == Qt::Key_Space) control.fsm.setAccelerate(true);
  }
  action = key;
}

void SnakeQT::drawSnakePart(QPainter &painter, const QRect &cellRect,
                            const QPixmap &pixmap, int angle) {
  QTransform transform;
  transform.rotate(angle);
  QPixmap rotatedPixmap =
      pixmap.transformed(transform, Qt::SmoothTransformation);
  painter.drawPixmap(cellRect.x(), cellRect.y(), rotatedPixmap);
}

void SnakeQT::drawSnakeHead(QPainter &painter, const QRect &cellRect) {
  s21::Direction direction = control.fsm.getSnake().getDirection();
  int angle = 0;
  switch (direction) {
    case s21::Direction::UP:
      angle = 180;
      break;
    case s21::Direction::DOWN:
      angle = 0;
      break;
    case s21::Direction::LEFT:
      angle = 90;
      break;
    case s21::Direction::RIGHT:
    default:
      angle = 270;
      break;
  }
  drawSnakePart(painter, cellRect, snakeHead, angle);
}

void SnakeQT::drawSnakeBody(QPainter &painter, const QRect &cellRect,
                            const std::pair<int, int> &prev,
                            const std::pair<int, int> &next,
                            const std::pair<int, int> &current) {
  bool isTurn = false;

  int angle = 0;
  if ((prev.first != next.first) && (prev.second != next.second)) {
    isTurn = true;
    if ((prev.first < current.first && next.second < current.second) ||
        (next.first < current.first && prev.second < current.second)) {
      angle = 0;
    } else if ((prev.first < current.first && next.second > current.second) ||
               (next.first < current.first && prev.second > current.second)) {
      angle = 90;
    } else if ((prev.first > current.first && next.second < current.second) ||
               (next.first > current.first && prev.second < current.second)) {
      angle = 270;
    } else if ((prev.first > current.first && next.second > current.second) ||
               (next.first > current.first && prev.second > current.second)) {
      angle = 180;
    }
  } else if (prev.first == next.first) {
    angle = 0;
  } else if (prev.second == next.second) {
    angle = 90;
  }

  QPixmap snakePartPixmap = isTurn ? snakeBodyTurn : snakeBody;
  drawSnakePart(painter, cellRect, snakePartPixmap, angle);
}

void SnakeQT::drawSnakeTail(QPainter &painter, const QRect &cellRect,
                            const std::pair<int, int> &prev,
                            const std::pair<int, int> &current) {
  int angle = 0;
  if (prev.first < current.first)
    angle = 270;
  else if (prev.first > current.first)
    angle = 90;
  else if (prev.second < current.second)
    angle = 180;
  else if (prev.second > current.second)
    angle = 0;

  drawSnakePart(painter, cellRect, snakeTail, angle);
}

void SnakeQT::getSignal(int userInput, bool hold) {
  switch (userInput) {
    case Qt::Key_Up:
      control.up(hold);
      break;
    case Qt::Key_Down:
      control.down(hold);
      break;
    case Qt::Key_Left:
      control.left(hold);
      break;
    case Qt::Key_Right:
      control.right(hold);
      break;
    case Qt::Key_Escape:
      control.terminate(hold);
      close();
      break;
    case Qt::Key_P:
      control.pause(hold);
      break;
    case Qt::Key_Space:
      control.action(hold);
      break;
    case ENTER:
      control.start(hold);
      break;
    default:
      control.currentAction(hold);
      break;
  }
}

void SnakeQT::sendPeriodicSignal() {
  getSignal(action, hold);
  auto currentState = control.fsm.getCurrentState();
  if (currentState == s21::States::Move) {
    timer->start(control.fsm.getDelay());
    control.fsm.setAccelerate(false);
    update();
    updateMenu();
  } else if (currentState == s21::States::Pause ||
             currentState == s21::States::GameOver ||
             currentState == s21::States::Win ||
             currentState == s21::States::Start) {
    update();
    if (currentState == s21::States::Win && action == Qt::Key_Escape) close();
  } else {
    timer->start(0);
  }

  if (action != Qt::Key_P) action = -1;
}
