#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      framePixmap(":/imagesSnake/frame.jpg"),
      bricksPixmap(":/imagesTetris/bricks.jpg") {
  ui->setupUi(this);
}

void MainWindow::GameWindow() {
  QFont font;
  font.setPointSize(16);

  // Настройка компоновки основного окна
  QWidget *centralWidget = new QWidget(this);
  QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

  // Игровое поле
  QWidget *gameField = new QWidget(this);
  gameField->setMinimumSize(300, 600);
  mainLayout->addWidget(gameField);

  // Меню
  QVBoxLayout *menuLayout = new QVBoxLayout();
  menuLayout->setAlignment(Qt::AlignCenter);
  setupMenuLayout(menuLayout, font);

  mainLayout->addLayout(menuLayout);

  setCentralWidget(centralWidget);
  setFixedSize(540, 620);
}

MainWindow::~MainWindow() { delete ui; }

QLabel *MainWindow::createLabel(const QString &text, const QFont &font) {
  QLabel *label = new QLabel(text, this);
  label->setFont(font);
  return label;
}

void MainWindow::setupMenuLayout(QVBoxLayout *menuLayout, const QFont &font) {
  QLabel *highScoreLabel = createLabel("High Score:", font);
  QLabel *scoreLabel = createLabel("Score:", font);
  QLabel *levelLabel = createLabel("Level:", font);
  QLabel *nextLabel = createLabel("Next", font);
  QLabel *exitLabel = createLabel("Exit: \"ESC\"", font);
  QLabel *pauseLabel = createLabel("Pause: \"P\"", font);

  menuLayout->addWidget(highScoreLabel, 0, Qt::AlignCenter);
  menuLayout->addWidget(highScoreValue, 0, Qt::AlignCenter);
  menuLayout->addSpacing(20);

  menuLayout->addWidget(scoreLabel, 0, Qt::AlignCenter);
  menuLayout->addWidget(scoreValue, 0, Qt::AlignCenter);
  menuLayout->addSpacing(20);

  menuLayout->addWidget(levelLabel, 0, Qt::AlignCenter);
  menuLayout->addWidget(levelValue, 0, Qt::AlignCenter);
  menuLayout->addSpacing(20);

  menuLayout->addWidget(nextLabel, 0, Qt::AlignCenter);
  menuLayout->addSpacing(240);

  menuLayout->addWidget(exitLabel, 0, Qt::AlignCenter);
  menuLayout->addWidget(pauseLabel, 0, Qt::AlignCenter);
}

void MainWindow::updateMenu() {
  QFont font;
  font.setPointSize(16);
#ifdef SNAKE
  s21::GameInfo_t state = control.fsm.updateCurrentState();
#endif  // SNAKE

#ifdef TETRIS
  GameInfo_t state = updateCurrentState();
#endif  // TETRIS

#ifndef MENU
  highScoreValue->setText(QString::number(state.high_score));
  scoreValue->setText(QString::number(state.score));
  levelValue->setText(QString::number(state.level));
  highScoreValue->setFont(font);
  scoreValue->setFont(font);
  levelValue->setFont(font);
#endif  // MENU
}

void MainWindow::borderAndMenuPainter(QPainter &painter, QRect &borderRectGame,
                                      QPixmap &backGround) {
  int menuWidth = width() - FIELD_WIDTH - BORDER_THICKNESS;
  int menuHeight = height();
  painter.fillRect(borderRectGame, framePixmap);

  QRect borderRectMenu(FIELD_WIDTH + 2 * BORDER_THICKNESS, 0, menuWidth,
                       menuHeight);
  painter.fillRect(borderRectMenu, framePixmap);
  QRect rectMenu(FIELD_WIDTH + 2 * BORDER_THICKNESS, BORDER_THICKNESS,
                 menuWidth - 2 * BORDER_THICKNESS,
                 menuHeight - 2 * BORDER_THICKNESS);
  painter.fillRect(rectMenu, QColor("white"));
  QRect borderNextFigure(
      FIELD_WIDTH + 2 * BORDER_THICKNESS + menuWidth / 2 - 95, menuHeight - 330,
      170, 200);
  painter.fillRect(borderNextFigure, framePixmap);
  QRect nextFigure(FIELD_WIDTH + 3 * BORDER_THICKNESS + menuWidth / 2 - 95,
                   menuHeight - 330 + BORDER_THICKNESS,
                   170 - 2 * BORDER_THICKNESS, 200 - 2 * BORDER_THICKNESS);
  printNext(painter, nextFigure, backGround);
}

void MainWindow::printNext(QPainter &painter, QRect &nextFigure,
                           QPixmap &backGround) {
#ifdef TETRIS
  auto frame = updateCurrentState();
#endif

  int step = 30;
  for (int y = nextFigure.top(); y < nextFigure.bottom(); y += step) {
    for (int x = nextFigure.left(); x < nextFigure.right(); x += step) {
      QRect rect(x, y, step, step);
#ifdef TETRIS
      int newY = (y - nextFigure.top() - 2 * step) / step;
      int newX = (x - nextFigure.left() - step) / step;

      if (newY < 4 && newX < 4 && newY >= 0 && newX >= 0 &&
          frame.next[newY][newX] == 1)
        painter.drawPixmap(rect, bricksPixmap);
      else
        painter.drawPixmap(rect, backGround);
#else
      painter.drawPixmap(rect, backGround);
#endif
    }
  }
}

void MainWindow::printPause(QPainter &painter, QRect &borderRectGame) {
  drawCenteredText(painter, borderRectGame, "Paused", Qt::white, 30);
}

void MainWindow::printGameOver(QPainter &painter, QRect &borderRectGame) {
  drawCenteredText(painter, borderRectGame, "Game Over", Qt::white, 30);
  drawCenteredText(painter,
                   QRect(0, 50, FIELD_WIDTH + 2 * BORDER_THICKNESS,
                         FIELD_HEIGHT + 2 * BORDER_THICKNESS),
                   "Press \"Enter\" to start", Qt::white, 15);
}

void MainWindow::printWin(QPainter &painter, QRect &borderRectGame) {
  drawCenteredText(painter, borderRectGame, "You Win", Qt::white, 30);
  drawCenteredText(painter,
                   QRect(0, 50, FIELD_WIDTH + 2 * BORDER_THICKNESS,
                         FIELD_HEIGHT + 2 * BORDER_THICKNESS),
                   "Press \"Escape\" to exit", Qt::white, 15);
}

void MainWindow::printStart(QPainter &painter, const QRect &borderRectGame,
                            const QString &text) {
  drawCenteredText(painter, borderRectGame, text, Qt::white, 30);
  drawCenteredText(painter,
                   QRect(0, 50, FIELD_WIDTH + 2 * BORDER_THICKNESS,
                         FIELD_HEIGHT + 2 * BORDER_THICKNESS),
                   "Press \"Enter\" to start", Qt::white, 15);
}

void MainWindow::drawCenteredText(QPainter &painter, const QRect &rect,
                                  const QString &text, QColor color,
                                  int fontSize) {
  painter.setPen(color);
  painter.setFont(QFont("Arial", fontSize, QFont::Bold));
  painter.drawText(rect, Qt::AlignCenter, text);
}
