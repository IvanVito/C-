#include "parser.h"

bool s21::Parser::isNumberPoligon(const std::string& str) {
  bool num = true;
  size_t space = 0;
  if (str[0] == ' ') space = 1;

  for (size_t i = space; i < str.length() && num == true; ++i)
    if (!std::isdigit(str[i]) || str[i] == 0) num = false;

  return num;
}

void s21::Parser::pushPoligon(const std::string& num,
                              std::vector<int>& poligon) {
  if (!num.empty()) {
    if (isNumberPoligon(num))
      poligon.push_back(std::stoi(num) - OBJ_INDEX);
    else
      error_ = true;
  }
}

void s21::Parser::parserVertex(std::ifstream& inputFile) {
  std::string line;
  while (std::getline(inputFile, line) && error_ == false) {
    if (line.substr(0, 2) == "v ") {
      std::istringstream stringStream(line.substr(2));
      std::vector<double> vertex;
      double value;

      while (stringStream >> value) vertex.push_back(value);

      if (vertex.size() == 3)
        vertexes_.push_back(vertex);
      else
        error_ = true;
    }
  }
}

void s21::Parser::parserPoligon(std::ifstream& inputFile) {
  std::string line;
  while (std::getline(inputFile, line) && error_ == false) {
    if (line.substr(0, 2) == "f ") {
      std::istringstream stringStream(line.substr(2));
      std::vector<int> poligon;
      std::string num;

      while (stringStream >> num) {
        size_t slashPos = num.find('/');
        if (slashPos != std::string::npos) {
          num = num.substr(0, slashPos);
        }
        pushPoligon(num, poligon);
      }

      if (!poligon.empty()) poligons_.push_back(poligon);
    }
  }
}

void s21::Parser::parser(const std::string& fileName) {
  std::ifstream inputFile(fileName);
  if (inputFile.is_open()) {
    parserVertex(inputFile);
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);
    parserPoligon(inputFile);
    inputFile.close();
  }
}

s21::Parser& s21::Parser::getObject() {
  static Parser object;
  return object;
}