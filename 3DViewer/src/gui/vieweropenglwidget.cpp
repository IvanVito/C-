#include "vieweropenglwidget.h"

using namespace s21;

ViewerOpenGLWidget::ViewerOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      backgroundColor_(51, 128, 204),
      pointSize_(DEFAULT * 5),
      formVert_(ZERO),
      verticesColor_(DEFAULT, DEFAULT, DEFAULT),
      edgesColor_(DEFAULT, DEFAULT, DEFAULT),
      thickEdges_(DEFAULT),
      typeEdges_(ZERO),
      projectionType_(ZERO) {}

void ViewerOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_MULTISAMPLE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(-DEFAULT, -DEFAULT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void ViewerOpenGLWidget::paintGL() {
  glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(),
               backgroundColor_.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (!vert_.empty() && !poli_.empty()) {
    float aspectRatio =
        static_cast<float>(width()) / static_cast<float>(height());
    float nearPlane = 1.0f, farPlane = 100.0f;

    if (projectionType_ == ZERO) {
      float size = 2.0f;
      float left = -size * aspectRatio;
      float right = size * aspectRatio;
      float bottom = -size;
      float top = size;
      glOrtho(left, right, bottom, top, nearPlane, farPlane);
    } else if (projectionType_ == 1) {
      float fov = 45.0f;
      gluPerspective(fov, aspectRatio, nearPlane, farPlane);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, -5);
    paintEdges();
    paintVertices();
  }
}

void ViewerOpenGLWidget::paintEdges() {
  glColor3d(edgesColor_.redF(), edgesColor_.greenF(), edgesColor_.blueF());
  if (typeEdges_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(6, 0x0F0F);
  }
  glLineWidth(thickEdges_);

  glEnable(GL_POLYGON_OFFSET_LINE);
  glEnable(GL_LINE_SMOOTH);
  glPolygonOffset(-DEFAULT, -DEFAULT);
  for (const auto &polygon : poli_) {
    glBegin(GL_LINE_LOOP);
    for (const auto &index : polygon) {
      const auto &vertex = vert_[index];
      glVertex3d(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();
  }
  if (typeEdges_ == 1) glDisable(GL_LINE_STIPPLE);
  glDisable(GL_POLYGON_OFFSET_LINE);
  glDisable(GL_LINE_SMOOTH);
  glDisable(GL_DEPTH_TEST);
}

void ViewerOpenGLWidget::paintVertices() {
  glPointSize(pointSize_);
  glColor3d(verticesColor_.redF(), verticesColor_.greenF(),
            verticesColor_.blueF());

  if (formVert_ == ZERO)
    glEnable(GL_POINT_SMOOTH);
  else if (formVert_ == 1)
    glDisable(GL_POINT_SMOOTH);

  if (formVert_ != 2) {
    glBegin(GL_POINTS);
    for (const auto &vertex : vert_)
      glVertex3d(vertex[0], vertex[1], vertex[2] + 0.001);
    glEnd();
  }
  glEnable(GL_DEPTH_TEST);
}

void ViewerOpenGLWidget::setBackgroundColor(const QColor &color) {
  backgroundColor_ = color;
}

QColor ViewerOpenGLWidget::getBackgroundColor() const {
  return backgroundColor_;
}

void ViewerOpenGLWidget::setVertecies(
    const std::vector<std::vector<double>> &vertexes) {
  vert_ = vertexes;
}

void ViewerOpenGLWidget::setPoligons(
    const std::vector<std::vector<int>> &poligons) {
  poli_ = poligons;
}

void ViewerOpenGLWidget::resizeGL(int width, int height) {
  glViewport(ZERO, ZERO, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double aspectRatio = static_cast<double>(width) / height;
  double left = -DEFAULT, right = DEFAULT, bottom = -DEFAULT, top = DEFAULT;

  if (aspectRatio > DEFAULT) {
    left *= aspectRatio;
    right *= aspectRatio;
  } else {
    bottom /= aspectRatio;
    top /= aspectRatio;
  }
  glOrtho(left, right, bottom, top, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
}

void ViewerOpenGLWidget::setPointSize(double newPointSize) {
  pointSize_ = newPointSize;
}

void ViewerOpenGLWidget::setFormVertices(const int &newForm) {
  formVert_ = newForm;
}

void ViewerOpenGLWidget::setVerticesColor(const QColor &color) {
  verticesColor_ = color;
}

QColor ViewerOpenGLWidget::getVerticesColor() const { return verticesColor_; }

QColor ViewerOpenGLWidget::getEdgesColor() const { return edgesColor_; }

void ViewerOpenGLWidget::setEdgesColor(const QColor &color) {
  edgesColor_ = color;
}

void ViewerOpenGLWidget::setThickEdges(double newThickEdges) {
  thickEdges_ = newThickEdges;
}

void ViewerOpenGLWidget::setTypeEdges(const int &newType) {
  typeEdges_ = newType;
}

void ViewerOpenGLWidget::setProjectionType(const int &newType) {
  projectionType_ = newType;
}

void ViewerOpenGLWidget::saveImageWidget(const QString &fileName,
                                         const char *format) {
  QImage image = grabFramebuffer();
  if (!image.save(fileName, format))
    QMessageBox::warning(this, "Error!", "Image not saved!");
  else
    QMessageBox::information(this, "Success!", "Image saved successfully!");
}

QColor ViewerOpenGLWidget::getBackgroundColor() { return backgroundColor_; }

double ViewerOpenGLWidget::getPointSize() { return pointSize_; }

int ViewerOpenGLWidget::getFormVertices() { return formVert_; }

double ViewerOpenGLWidget::getThickEdges() { return thickEdges_; }

int ViewerOpenGLWidget::getTypeEdges() { return typeEdges_; }

int ViewerOpenGLWidget::getProjectionType() { return projectionType_; }
