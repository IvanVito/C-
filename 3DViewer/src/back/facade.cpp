#include "facade.h"

void s21::Facade::parseFile(const std::string& fileName) {
  object_.vertexes_.clear();
  object_.poligons_.clear();
  object_.parser(fileName);
  AffinMove::clearStaticVariable();
  AffinRotate::clearStaticVariable();
  AffinScale::clearStaticVariable();

  if (object_.error_) {
    object_.vertexes_.clear();
    object_.poligons_.clear();
    object_.error_ = false;
  } else {
    if (!object_.vertexes_.empty()) {
      scale(otherTrans_.adaptScale());
      AffinScale::clearStaticVariable();
      centerModel();
    }
  }
}

size_t s21::Facade::getSizeVertexes() { return object_.vertexes_.size(); }
size_t s21::Facade::getSizePoligons() { return object_.poligons_.size(); }

std::vector<std::vector<double>>& s21::Facade::getVertexes() {
  return object_.vertexes_;
}

std::vector<std::vector<int>>& s21::Facade::getPoligons() {
  return object_.poligons_;
}

void s21::Facade::scale(double scale) {
  if (!object_.vertexes_.empty() && scale >= 0) {
    scaleXYZ(scale, scale, scale);
  }
}

void s21::Facade::centerModel() {
  if (!object_.vertexes_.empty()) otherTrans_.makeCenter();
  AffinMove::clearStaticVariable();
}

void s21::Facade::move(double x, double y, double z) {
  if (!object_.vertexes_.empty()) {
    s21::AffinMove moveObj(x, y, z);
    moveObj.transform();
  }
}
void s21::Facade::rotate(double degree, char axis) {
  if (!object_.vertexes_.empty()) {
    s21::AffinRotate rotateObj(degree, axis);
    rotateObj.transform();
  }
}

void s21::Facade::scaleXYZ(double scaleX, double scaleY, double scaleZ) {
  if (!object_.vertexes_.empty() && scaleX >= 0 && scaleY >= 0 && scaleZ >= 0) {
    s21::AffinScale scaleObj(scaleX, scaleY, scaleZ);
    scaleObj.transform();
  }
}

bool s21::Facade::isValidNumber(const std::string& numberStr) {
  std::regex decimalRegex(R"(^-?\d+(\.\d+)?$)");
  return std::regex_match(numberStr, decimalRegex);
}
