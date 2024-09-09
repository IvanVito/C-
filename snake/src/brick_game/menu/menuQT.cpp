#include "menuQT.h"

#include <cstdlib>

void MenuWindow::launchGame(const char *game) {
  std::string command = "build/desktop/";
  command += game;
  bool err = std::system(command.c_str());
  if (err != 0) std::cerr << "Command failed with code " << err << std::endl;
}

MenuWindow::MenuWindow() : highlight(0) {
  choices[0] = "Snake";
  choices[1] = "Tetris";
  nChoices = sizeof(choices) / sizeof(choices[0]);
  GameWindow();
}

void MenuWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);

  QFont font("Arial", 20);
  painter.setFont(font);

  QPixmap backGround(":/imagesMenu/backGround.jpg");

  QRect borderRectGame(0, 0, FIELD_WIDTH + 2 * BORDER_THICKNESS,
                       FIELD_HEIGHT + 2 * BORDER_THICKNESS);
  borderAndMenuPainter(painter, borderRectGame, backGround);

  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS; ++col) {
      QRect cellRect(col * CELL_WIDTH + BORDER_THICKNESS,
                     row * CELL_HEIGHT + BORDER_THICKNESS, CELL_WIDTH,
                     CELL_HEIGHT);
      painter.drawPixmap(cellRect.x(), cellRect.y(), backGround);
    }
  }

  for (int i = 0; i < nChoices; ++i) {
    if (i == highlight) {
      painter.setPen(Qt::red);
    } else {
      painter.setPen(Qt::white);
    }
    painter.drawText(FIELD_WIDTH / 2 - 30, (FIELD_HEIGHT - 30 * i) / 2 + i * 45,
                     choices[i]);
  }
}

void MenuWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Up:
      if (highlight > 0) --highlight;
      break;
    case Qt::Key_Down:
      if (highlight < nChoices - 1) ++highlight;
      break;
    case Qt::Key_Return:
      launchGame((highlight == SNAKE_GAME) ? "snake" : "tetris");
      break;
    case Qt::Key_Escape:
      QApplication::quit();
      break;
    default:
      QMainWindow::keyPressEvent(event);
  }
  update();
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MenuWindow window;
  window.show();

  return app.exec();
}