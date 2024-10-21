#include "affinTrans.h"

// Определение статических переменных для класса AffinMove
double s21::AffinMove::lastMoveX = 0.0;
double s21::AffinMove::lastMoveY = 0.0;
double s21::AffinMove::lastMoveZ = 0.0;

// Определение статических переменных для класса AffinScale
double s21::AffinScale::lastScaleX = 1;
double s21::AffinScale::lastScaleY = 1;
double s21::AffinScale::lastScaleZ = 1;

// Определение статических переменных для класса AffinRotate
double s21::AffinRotate::lastRotateX = 0.0;
double s21::AffinRotate::lastRotateY = 0.0;
double s21::AffinRotate::lastRotateZ = 0.0;

void s21::AffinTrans::transform() {
  S21Matrix matrix = createTransMatrix();
  transformation(matrix);
}

void s21::AffinTrans::initMatrix() {
  matrixTrans.fillMatrixStr("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1");

  trans_.sortXYZ();
  oldCenterX = trans_.findCoordinateCenter(trans_.x_);
  oldCenterY = trans_.findCoordinateCenter(trans_.y_);
  oldCenterZ = trans_.findCoordinateCenter(trans_.z_);

  matrixMoveToOrigin.fillMatrixStr("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1");
  matrixMoveToOrigin(0, 3) = -oldCenterX;
  matrixMoveToOrigin(1, 3) = -oldCenterY;
  matrixMoveToOrigin(2, 3) = -oldCenterZ;

  matrixMoveBack.fillMatrixStr("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1");
  matrixMoveBack(0, 3) = oldCenterX;
  matrixMoveBack(1, 3) = oldCenterY;
  matrixMoveBack(2, 3) = oldCenterZ;
}

void s21::AffinMove::clearStaticVariable() {
  lastMoveX = 0;
  lastMoveY = 0;
  lastMoveZ = 0;
};

void s21::AffinRotate::clearStaticVariable() {
  lastRotateX = 0;
  lastRotateY = 0;
  lastRotateZ = 0;
};

void s21::AffinScale::clearStaticVariable() {
  lastScaleX = 1;
  lastScaleY = 1;
  lastScaleZ = 1;
};

void s21::AffinTrans::transformation(S21Matrix& matrix) {
  s21::Parser& obj = s21::Parser::getObject();
  S21Matrix matrixVertex(4, 1);

  for (size_t i = 0; i < obj.vertexes_.size(); ++i) {
    matrixVertex(0, 0) = obj.vertexes_[i][0];
    matrixVertex(1, 0) = obj.vertexes_[i][1];
    matrixVertex(2, 0) = obj.vertexes_[i][2];
    matrixVertex(3, 0) = 1;

    S21Matrix matrixNewVertex = matrix * matrixVertex;

    obj.vertexes_[i][0] = matrixNewVertex(0, 0);
    obj.vertexes_[i][1] = matrixNewVertex(1, 0);
    obj.vertexes_[i][2] = matrixNewVertex(2, 0);
  }
}

S21Matrix s21::AffinMove::createTransMatrix() {
  S21Matrix matrixMove(4, 4);
  matrixMove.fillMatrixStr("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1");

  double deltaX = x_ - lastMoveX;
  double deltaY = y_ - lastMoveY;
  double deltaZ = z_ - lastMoveZ;

  if (x_ != 0) {
    matrixMove(0, 3) = deltaX;
    lastMoveX = x_;
  } else
    matrixMove(0, 3) = 0;

  if (y_ != 0) {
    matrixMove(1, 3) = deltaY;
    lastMoveY = y_;
  } else
    matrixMove(1, 3) = 0;

  if (z_ != 0) {
    matrixMove(2, 3) = deltaZ;
    lastMoveZ = z_;
  } else
    matrixMove(2, 3) = 0;

  return matrixMove;
}

S21Matrix s21::AffinRotate::createTransMatrix() {
  initMatrix();
  double radians, cosAngle, sinAngle;

  if (axis_ == 'x') {
    double deltaAngleX = degree_ - lastRotateX;
    radians = deltaAngleX * M_PI / 180.0;
    cosAngle = cos(radians);
    sinAngle = sin(radians);

    matrixTrans(1, 1) = cosAngle;
    matrixTrans(1, 2) = -sinAngle;
    matrixTrans(2, 1) = sinAngle;
    matrixTrans(2, 2) = cosAngle;

    lastRotateX = degree_;
  } else if (axis_ == 'y') {
    double deltaAngleY = degree_ - lastRotateY;
    radians = deltaAngleY * M_PI / 180.0;
    cosAngle = cos(radians);
    sinAngle = sin(radians);

    matrixTrans(0, 0) = cosAngle;
    matrixTrans(0, 2) = sinAngle;
    matrixTrans(2, 0) = -sinAngle;
    matrixTrans(2, 2) = cosAngle;

    lastRotateY = degree_;
  } else if (axis_ == 'z') {
    double deltaAngleZ = degree_ - lastRotateZ;
    radians = deltaAngleZ * M_PI / 180.0;
    cosAngle = cos(radians);
    sinAngle = sin(radians);

    matrixTrans(0, 0) = cosAngle;
    matrixTrans(0, 1) = -sinAngle;
    matrixTrans(1, 0) = sinAngle;
    matrixTrans(1, 1) = cosAngle;

    lastRotateZ = degree_;
  }

  trans_.makeCenter();
  transformation(matrixTrans);
  trans_.sortXYZ();
  matrixMoveBack(0, 3) = oldCenterX - trans_.findCoordinateCenter(trans_.x_);
  matrixMoveBack(1, 3) = oldCenterY - trans_.findCoordinateCenter(trans_.y_);
  matrixMoveBack(2, 3) = oldCenterZ - trans_.findCoordinateCenter(trans_.z_);

  return matrixMoveBack;
}

S21Matrix s21::AffinScale::createTransMatrix() {
  matrixTrans.fillMatrixStr("1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1");

  double deltaX = scaleX_ / lastScaleX;
  double deltaY = scaleY_ / lastScaleY;
  double deltaZ = scaleZ_ / lastScaleZ;

  matrixTrans(0, 0) = deltaX;
  matrixTrans(1, 1) = deltaY;
  matrixTrans(2, 2) = deltaZ;

  lastScaleX = scaleX_;
  lastScaleY = scaleY_;
  lastScaleZ = scaleZ_;

  return matrixTrans;
}
