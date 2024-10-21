#include "controller.h"

void s21::Controller::parseFile(const std::string& fileName) {
  facade.parseFile(fileName);
}

size_t s21::Controller::getSizeVertexes() { return facade.getSizeVertexes(); }

size_t s21::Controller::getSizePoligons() { return facade.getSizePoligons(); }

std::vector<std::vector<double>>& s21::Controller::getVertexes() {
  return facade.getVertexes();
}

std::vector<std::vector<int>>& s21::Controller::getPoligons() {
  return facade.getPoligons();
}

void s21::Controller::scale(double scale) { facade.scale(scale); }

void s21::Controller::centerModel() { facade.centerModel(); }

void s21::Controller::move(double x, double y, double z) {
  facade.move(x, y, z);
}

void s21::Controller::rotate(double degree, char axis) {
  facade.rotate(degree, axis);
}

void s21::Controller::scaleXYZ(double scaleX, double scaleY, double scaleZ) {
  facade.scaleXYZ(scaleX, scaleY, scaleZ);
}

bool s21::Controller::isValidNumber(const std::string& numberStr) {
  return facade.isValidNumber(numberStr);
}