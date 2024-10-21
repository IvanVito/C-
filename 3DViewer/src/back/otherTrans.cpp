#include "otherTrans.h"

void s21::OtherTrans::sortXYZ() {
  const s21::Parser& obj = s21::Parser::getObject();
  x_.clear();
  y_.clear();
  z_.clear();

  for (auto myVector : obj.vertexes_) {
    x_.push_back(myVector[0]);
    y_.push_back(myVector[1]);
    z_.push_back(myVector[2]);
  }
}

double s21::OtherTrans::findMin(std::vector<double> axis) {
  auto min = std::min_element(axis.begin(), axis.end());
  return *min;
}

double s21::OtherTrans::findMax(std::vector<double> axis) {
  auto max = std::max_element(axis.begin(), axis.end());
  return *max;
}

void s21::OtherTrans::makeCenter() {
  sortXYZ();
  s21::Parser& obj = s21::Parser::getObject();

  double centerX = findCoordinateCenter(x_);
  double centerY = findCoordinateCenter(y_);
  double centerZ = findCoordinateCenter(z_);

  for (auto& myVector : obj.vertexes_) {
    myVector[0] -= centerX;
    myVector[1] -= centerY;
    myVector[2] -= centerZ;
  };
}

double s21::OtherTrans::findCoordinateCenter(std::vector<double>& coordinats) {
  double max = findMax(coordinats);
  double min = findMin(coordinats);
  double center = min + (max - min) / 2.0;
  return center;
}

double s21::OtherTrans::adaptScale() {
  sortXYZ();
  double minX = findMin(x_);
  double maxX = findMax(x_);
  double minY = findMin(y_);
  double maxY = findMax(y_);
  double minZ = findMin(z_);
  double maxZ = findMax(z_);

  double modelWidth = maxX - minX;
  double modelHeight = maxY - minY;
  double modelDepth = maxZ - minZ;

  double scaleX = 2 / modelWidth;
  double scaleY = 2 / modelHeight;
  double scaleZ = 2 / modelDepth;

  double minScale = std::min({scaleX, scaleY, scaleZ});

  return minScale;
}