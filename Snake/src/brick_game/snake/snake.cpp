#include "snake.h"

using namespace s21;
using Coordinate = std::pair<int, int>;

GameInfo_t::GameInfo_t()
    : score(0), high_score(0), level(1), speed(20), pause(0) {
  for (auto& row : field) row.fill(0);
  for (auto& row : next) row.fill(0);
}

Snake::Snake() {
  for (int i = 0; i < INIT_SIZE_SNAKE; ++i)
    body_.emplace_back((MAP_ROWS - INIT_SIZE_SNAKE) / 2 + i, MAP_COLS / 2);
  std::srand(std::time(nullptr));
}

Snake::Snake(int initial_length, Coordinate initial_position, Direction dir)
    : dir_(dir) {
  for (int i = 0; i < initial_length; ++i)
    body_.emplace_back(initial_position.first + i, initial_position.second);
  std::srand(std::time(nullptr));
}

void Snake::handleInput(UserAction_t action) {
  switch (action) {
    case UserAction_t::Left:
      if (dir_ == UP || dir_ == DOWN) dir_ = LEFT;
      break;
    case UserAction_t::Right:
      if (dir_ == UP || dir_ == DOWN) dir_ = RIGHT;
      break;
    case UserAction_t::Up:
      if (dir_ == LEFT || dir_ == RIGHT) dir_ = UP;
      break;
    case UserAction_t::Down:
      if (dir_ == LEFT || dir_ == RIGHT) dir_ = DOWN;
      break;
    default:
      break;
  }
}

void Snake::move() {
  int x = 0, y = 0;
  switch (dir_) {
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
  }

  Coordinate new_head = {body_.front().first + y, body_.front().second + x};
  body_.push_front(new_head);
  if (body_.front() != applePosition_)
    body_.pop_back();
  else {
    score();
    placeApple();
  }
}

void Snake::clearPastState() {
  for (const auto& segment : body_)
    if (segment.first >= 0 && segment.second >= 0)
      info_.field[segment.first][segment.second] = 0;
}

void Snake::printSnake() {
  for (const auto& segment : body_)
    if (segment.first >= 0 && segment.second >= 0)
      info_.field[segment.first][segment.second] = 1;
}

void Snake::clearField() {
  for (auto& row : info_.field) row.fill(0);
}

void Snake::placeApple(bool test) {
  bool validPosition = false;
  while (!validPosition) {
    int row, col;
    if (test == 0) {
      row = std::rand() % MAP_ROWS;
      col = std::rand() % MAP_COLS;
    } else {
      row = 9;
      col = 5;
    }
    applePosition_ = {row, col};
    validPosition = !std::any_of(
        body_.begin(), body_.end(),
        [this](const auto& segment) { return segment == applePosition_; });
  }
  info_.field[applePosition_.first][applePosition_.second] = 2;
}

void Snake::readRecord() {
  std::ifstream inputFile("recordSnake.txt");
  if (!inputFile.is_open()) {
    std::ofstream outputFile("recordSnake.txt");
    if (!outputFile.is_open())
      std::cerr << "Ошибка создания файла" << std::endl;
    outputFile << 0;
    outputFile.close();
    inputFile.open("recordSnake.txt");
    if (!inputFile.is_open())
      std::cerr << "Ошибка открытия файла после создания" << std::endl;
  }

  int readValue = 0;
  if (!(inputFile >> readValue)) {
    std::cerr << "Ошибка чтения рекорда из открытого файла" << std::endl;
    inputFile.close();
  }
  info_.high_score = readValue;
  inputFile.close();
}

void Snake::writeRecord(int record) {
  std::ofstream file("recordSnake.txt");

  if (!file.is_open())
    std::cerr << "Ошибка открытия файла" << std::endl;
  else {
    file << record;
    if (file.fail()) std::cerr << "Ошибка записи в файл" << std::endl;
  }

  if (file.is_open()) {
    file.close();
    if (file.fail()) std::cerr << "Ошибка закрытия файла" << std::endl;
  }
}

void Snake::score() {
  info_.score += 1;
  if (info_.level < MAX_LVL) info_.level = (info_.score / LVL_STEP) + 1;
  if (info_.score > info_.high_score) {
    writeRecord(info_.score);
    info_.high_score = info_.score;
  }
  info_.speed = SPEED_STEP * info_.level;
}

bool Snake::checkCollision() const {
  bool collision = false;
  int head_row = body_.front().first;
  int head_col = body_.front().second;

  if (head_row < 0 || head_row >= MAP_ROWS || head_col < 0 ||
      head_col >= MAP_COLS)
    collision = true;

  for (auto it = body_.begin() + 1; it != body_.end(); ++it)
    if (body_.front() == *it) collision = true;

  return collision;
}

std::deque<Coordinate> Snake::getBody() { return body_; }
Direction Snake::getDirection() { return dir_; }
void Snake::testPlaceApple(bool test) { placeApple(test); }
