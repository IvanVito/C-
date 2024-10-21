#include "mainwindow.h"

#include "ui_mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFocus();
  openGLWidget = ui->viewWidget;
  gifCreator = new GifCreator(openGLWidget, this);
  loadingCustomize();
  setConnects();
  setMovementsConnects();
}

void MainWindow::setConnects() {
  connect(ui->pushButtonBackground, &QPushButton::clicked, this,
          &MainWindow::clickButtonBackground);
  connect(ui->pushButtonModelLoading, &QPushButton::clicked, this,
          &MainWindow::clickButtonModelLoading);
  connect(ui->lineEditModelLoading, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineModelPath);
  connect(ui->horizontalSliderSizeVertices, &QSlider::valueChanged, this,
          &MainWindow::changeSizeVertices);
  connect(ui->comboBoxFormVertices,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &MainWindow::changeFormVertices);
  connect(ui->comboBoxTypeEdges,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &MainWindow::changeTypeEdges);
  connect(ui->comboBoxProjectionType,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &MainWindow::changeProjectionType);
  connect(ui->pushButtonColorVertices, &QPushButton::clicked, this,
          &MainWindow::clickButtonColorVertices);
  connect(ui->pushButtonColorEdges, &QPushButton::clicked, this,
          &MainWindow::clickButtonColorEdges);
  connect(ui->horizontalSliderThickEdges, &QSlider::valueChanged, this,
          &MainWindow::changeThickEdges);
  connect(ui->pushButtonBmpJpeg, &QPushButton::clicked, this,
          &MainWindow::saveImage);
  connect(ui->pushButtonGif, &QPushButton::clicked, gifCreator,
          &GifCreator::saveGif);
}

void MainWindow::setMovementsConnects() {
  connect(ui->pushButtonCenter, &QPushButton::clicked, this,
          &MainWindow::clickButtonCenter);
  connect(ui->pushButtonDefault, &QPushButton::clicked, this,
          &MainWindow::clickButtonDefault);
  connect(ui->horizontalSliderXTranslation, &QSlider::valueChanged, this,
          &MainWindow::changeXTranslate);
  connect(ui->horizontalSliderYTranslation, &QSlider::valueChanged, this,
          &MainWindow::changeYTranslate);
  connect(ui->horizontalSliderZTranslation, &QSlider::valueChanged, this,
          &MainWindow::changeZTranslate);
  connect(ui->horizontalSliderXRotation, &QSlider::valueChanged, this,
          &MainWindow::changeXRotate);
  connect(ui->horizontalSliderYRotation, &QSlider::valueChanged, this,
          &MainWindow::changeYRotate);
  connect(ui->horizontalSliderZRotation, &QSlider::valueChanged, this,
          &MainWindow::changeZRotate);
  connect(ui->horizontalSliderScaling, &QSlider::valueChanged, this,
          &MainWindow::changeScaleSlider);
  connect(ui->lineEditScaling, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineScale);
  connect(ui->lineEditXTranslation, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineXTranslate);
  connect(ui->lineEditYTranslation, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineYTranslate);
  connect(ui->lineEditZTranslation, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineZTranslate);
  connect(ui->lineEditXRotation, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineXRotate);
  connect(ui->lineEditYRotation, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineYRotate);
  connect(ui->lineEditZRotation, &QLineEdit::returnPressed, this,
          &MainWindow::changeLineZRotate);
}

void MainWindow::loadingCustomize() {
  QSettings settings("3DViewer", "S21");
  QColor savedColorBlue =
      settings.value("backgroundColor", QColor(51, 128, 204)).value<QColor>();
  openGLWidget->setBackgroundColor(savedColorBlue);
  QColor savedColorVertices =
      settings.value("verticesColor", QColor(255, 255, 255)).value<QColor>();
  openGLWidget->setVerticesColor(savedColorVertices);
  QColor savedColorEdges =
      settings.value("edgesColor", QColor(255, 255, 255)).value<QColor>();
  openGLWidget->setEdgesColor(savedColorEdges);
  QString styleVertices =
      QString("background-color: %1").arg(savedColorVertices.name());
  ui->pushButtonColorVertices->setStyleSheet(styleVertices);
  QString styleEdges =
      QString("background-color: %1").arg(savedColorEdges.name());
  ui->pushButtonColorEdges->setStyleSheet(styleEdges);

  setSliderHalf();

  double savedPointSize = settings.value("pointSize", 5.0).toDouble();
  openGLWidget->setPointSize(savedPointSize);
  ui->horizontalSliderSizeVertices->setValue(savedPointSize);
  int savedFormVertices = settings.value("formVertices", 0).toInt();
  openGLWidget->setFormVertices(savedFormVertices);
  ui->comboBoxFormVertices->setCurrentIndex(savedFormVertices);
  int savedThickEdges = settings.value("thickEdges", 1.0).toDouble();
  openGLWidget->setThickEdges(savedThickEdges);
  ui->horizontalSliderThickEdges->setValue(savedThickEdges);
  int savedTypeEdges = settings.value("typeEdges", 0).toInt();
  openGLWidget->setTypeEdges(savedTypeEdges);
  ui->comboBoxTypeEdges->setCurrentIndex(savedTypeEdges);
  int savedProjectionType = settings.value("projectionType", 0).toInt();
  openGLWidget->setProjectionType(savedProjectionType);
  ui->comboBoxProjectionType->setCurrentIndex(savedProjectionType);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)
    saveImage();
  else if (e->key() == Qt::Key_G && e->modifiers() == Qt::ControlModifier)
    gifCreator->saveGif();
}

void MainWindow::clickButtonBackground() {
  QColorDialog colorDialog;
  colorDialog.setCustomColor(0, QColor(51, 128, 204));
  QColor selectedColor = QColorDialog::getColor(
      openGLWidget->getBackgroundColor(), this, "Select background color");
  if (selectedColor.isValid()) {
    openGLWidget->setBackgroundColor(selectedColor);
    openGLWidget->update();
  }
}

void MainWindow::clickButtonModelLoading() {
  QDir dir(QCoreApplication::applicationDirPath());
  dir.cd("../models");
  QString fileName = QFileDialog::getOpenFileName(
      this, "Choose .obj File", dir.path(), "OBJ Files (*.obj)");
  fileLoading(fileName);
}

void MainWindow::changeLineModelPath() {
  ui->labelVerticesQuantity->setText("");
  ui->labelEdgesQuantity->setText("");
  QString fileName = ui->lineEditModelLoading->text();
  fileLoading(fileName);
  ui->lineEditModelLoading->clearFocus();
}

void MainWindow::fileLoading(const QString &fileName) {
  if (!fileName.isEmpty()) {
    if (fileName.endsWith(".obj", Qt::CaseInsensitive)) {
      ui->lineEditModelLoading->setText(fileName);
      obj.parseFile(fileName.toStdString());
      if (obj.getSizeVertexes() != 0) {
        openGLWidget->setVertecies(obj.getVertexes());
        openGLWidget->setPoligons(obj.getPoligons());
        openGLWidget->update();
      } else
        QMessageBox::warning(this, "Error!",
                             "File is empty or contains errors!");

      ui->labelVerticesQuantity->setText(
          QString::number(obj.getSizeVertexes()));
      ui->labelEdgesQuantity->setText(QString::number(obj.getSizePoligons()));
      setDefaultSliders();
    } else
      QMessageBox::warning(this, "Error!", "Choose .obj file!");
  }
}

void MainWindow::setSliderHalf() {
  int minRange = 1;
  int maxRange = 100;
  int maxSmallRange = 10;
  int halfRange = 50;
  int halfSmallRange = 5;
  int moveCentral = 0;
  int moveRange = 200;
  int rotateRange = 360;

  ui->horizontalSliderScaling->setRange(minRange, maxRange);
  ui->horizontalSliderScaling->setValue(halfRange);

  ui->horizontalSliderXTranslation->setRange(-moveRange, moveRange);
  ui->horizontalSliderXTranslation->setValue(moveCentral);

  ui->horizontalSliderYTranslation->setRange(-moveRange, moveRange);
  ui->horizontalSliderYTranslation->setValue(moveCentral);

  ui->horizontalSliderZTranslation->setRange(-moveRange, moveRange);
  ui->horizontalSliderZTranslation->setValue(moveCentral);

  ui->horizontalSliderXRotation->setRange(moveCentral, rotateRange);
  ui->horizontalSliderXRotation->setValue(moveCentral);

  ui->horizontalSliderYRotation->setRange(moveCentral, rotateRange);
  ui->horizontalSliderYRotation->setValue(moveCentral);

  ui->horizontalSliderZRotation->setRange(moveCentral, rotateRange);
  ui->horizontalSliderZRotation->setValue(moveCentral);

  ui->horizontalSliderSizeVertices->setRange(halfSmallRange, halfRange);
  ui->horizontalSliderSizeVertices->setValue(halfSmallRange);
  ui->comboBoxFormVertices->setCurrentIndex(0);
  ui->horizontalSliderThickEdges->setRange(minRange, maxSmallRange);
  ui->horizontalSliderThickEdges->setValue(minRange);
  ui->comboBoxTypeEdges->setCurrentIndex(0);
  ui->comboBoxProjectionType->setCurrentIndex(0);
}

void MainWindow::changeScaleSlider(int value) {
  double scaleValue = static_cast<double>(value) / 50.0;
  obj.scale(scaleValue);

  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeSizeVertices(int value) {
  openGLWidget->setPointSize(static_cast<double>(value));
  openGLWidget->update();
}

void MainWindow::changeFormVertices(int form) {
  openGLWidget->setFormVertices(form);
  openGLWidget->update();
}

void MainWindow::clickButtonColorVertices() {
  QColorDialog colorDialog;
  colorDialog.setCustomColor(0, QColor(255, 255, 255));

  QColor selectedColor = QColorDialog::getColor(
      openGLWidget->getVerticesColor(), this, "Select vertices color");
  if (selectedColor.isValid()) {
    openGLWidget->setVerticesColor(selectedColor);
    openGLWidget->update();
    QString colorStyle =
        QString("background-color: %1;").arg(selectedColor.name());
    ui->pushButtonColorVertices->setStyleSheet(colorStyle);
  }
}

void MainWindow::clickButtonColorEdges() {
  QColorDialog colorDialog;
  colorDialog.setCustomColor(0, QColor(255, 255, 255));

  QColor selectedColor = QColorDialog::getColor(openGLWidget->getEdgesColor(),
                                                this, "Select edges color");
  if (selectedColor.isValid()) {
    openGLWidget->setEdgesColor(selectedColor);
    openGLWidget->update();
    QString colorStyle =
        QString("background-color: %1;").arg(selectedColor.name());
    ui->pushButtonColorEdges->setStyleSheet(colorStyle);
  }
}

void MainWindow::changeThickEdges(int value) {
  openGLWidget->setThickEdges(static_cast<double>(value));
  openGLWidget->update();
}

void MainWindow::changeTypeEdges(int type) {
  openGLWidget->setTypeEdges(type);
  openGLWidget->update();
}

void MainWindow::changeProjectionType(int type) {
  openGLWidget->setProjectionType(type);
  openGLWidget->update();
}

void MainWindow::saveImage() {
  QDir dir(QCoreApplication::applicationDirPath());
  dir.cd("../images");
  QString selectedFilter;
  QString fileName = QFileDialog::getSaveFileName(
      openGLWidget, "Save image", dir.path(),
      "BMP Files (*.bmp);;JPEG Files (*.jpg)", &selectedFilter);
  if (!fileName.isEmpty()) {
    if (fileName.endsWith(".bmp"))
      openGLWidget->saveImageWidget(fileName, "BMP");
    else if (fileName.endsWith(".jpg") || fileName.endsWith(".jpeg"))
      openGLWidget->saveImageWidget(fileName, "JPEG");
    else if (selectedFilter.contains("JPEG", Qt::CaseInsensitive)) {
      fileName += ".jpg";
      openGLWidget->saveImageWidget(fileName, "JPEG");
    } else {
      fileName += ".bmp";
      openGLWidget->saveImageWidget(fileName, "BMP");
    }
  } else {
    QMessageBox::warning(this, "Error!",
                         "Empty file name. Picture was not saved!");
  }
}

void MainWindow::changeXTranslate(int value) {
  double translateXValue = static_cast<double>(value) / 50.0;
  obj.move(translateXValue, 0.0, 0.0);
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeYTranslate(int value) {
  double translateYValue = static_cast<double>(value) / 50.0;
  obj.move(0.0, translateYValue, 0.0);
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeZTranslate(int value) {
  double translateZValue = static_cast<double>(value) / 50.0;
  obj.move(0.0, 0.0, translateZValue);
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeXRotate(int value) {
  obj.rotate(value, 'x');
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeYRotate(int value) {
  obj.rotate(value, 'y');
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeZRotate(int value) {
  obj.rotate(value, 'z');
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());
  openGLWidget->update();
}

void MainWindow::changeLineScale() {
  if (obj.isValidNumber(ui->lineEditScaling->text().toStdString())) {
    double value = ui->lineEditScaling->text().toDouble();
    if (value > 0) {
      obj.scale(value);
      openGLWidget->setVertecies(obj.getVertexes());
      openGLWidget->setPoligons(obj.getPoligons());
      openGLWidget->update();
    } else if (value == 0)
      QMessageBox::warning(this, "Error!", "Scale can not be equal 0!");
    else
      QMessageBox::warning(this, "Error!", "Scale can not be negative!");
  } else
    QMessageBox::warning(this, "Error!", "Scaling value isn't correct!");
}

void MainWindow::changeLineXTranslate() {
  if (obj.isValidNumber(ui->lineEditXTranslation->text().toStdString())) {
    double value = ui->lineEditXTranslation->text().toDouble();
    obj.move(value, 0.0, 0.0);
    openGLWidget->setVertecies(obj.getVertexes());
    openGLWidget->setPoligons(obj.getPoligons());
    openGLWidget->update();
  } else
    QMessageBox::warning(this, "Error!", "Translation X value isn't correct!");
}

void MainWindow::changeLineYTranslate() {
  if (obj.isValidNumber(ui->lineEditYTranslation->text().toStdString())) {
    double value = ui->lineEditYTranslation->text().toDouble();
    obj.move(0.0, value, 0.0);
    openGLWidget->setVertecies(obj.getVertexes());
    openGLWidget->setPoligons(obj.getPoligons());
    openGLWidget->update();
  } else
    QMessageBox::warning(this, "Error!", "Translation Y value isn't correct!");
}

void MainWindow::changeLineZTranslate() {
  if (obj.isValidNumber(ui->lineEditZTranslation->text().toStdString())) {
    double value = ui->lineEditZTranslation->text().toDouble();
    obj.move(0.0, 0.0, value);
    openGLWidget->setVertecies(obj.getVertexes());
    openGLWidget->setPoligons(obj.getPoligons());
    openGLWidget->update();
  } else
    QMessageBox::warning(this, "Error!", "Translation Z value isn't correct!");
}

void MainWindow::changeLineXRotate() {
  if (obj.isValidNumber(ui->lineEditXRotation->text().toStdString())) {
    double value = ui->lineEditXRotation->text().toDouble();
    obj.rotate(value, 'x');
    openGLWidget->setVertecies(obj.getVertexes());
    openGLWidget->setPoligons(obj.getPoligons());
    openGLWidget->update();
  } else
    QMessageBox::warning(this, "Error!", "Rotation X value isn't correct!");
}

void MainWindow::changeLineYRotate() {
  if (obj.isValidNumber(ui->lineEditYRotation->text().toStdString())) {
    double value = ui->lineEditYRotation->text().toDouble();
    obj.rotate(value, 'y');
    openGLWidget->setVertecies(obj.getVertexes());
    openGLWidget->setPoligons(obj.getPoligons());
    openGLWidget->update();
  } else
    QMessageBox::warning(this, "Error!", "Rotation Y value isn't correct!");
}

void MainWindow::changeLineZRotate() {
  if (obj.isValidNumber(ui->lineEditZRotation->text().toStdString())) {
    double value = ui->lineEditZRotation->text().toDouble();
    obj.rotate(value, 'z');
    openGLWidget->setVertecies(obj.getVertexes());
    openGLWidget->setPoligons(obj.getPoligons());
    openGLWidget->update();
  } else
    QMessageBox::warning(this, "Error!", "Rotation Z value isn't correct!");
}

void MainWindow::setDefaultSliders() {
  int halfRange = 50;
  int moveCentral = 0;
  ui->horizontalSliderScaling->setValue(halfRange);
  ui->horizontalSliderXTranslation->setValue(moveCentral);
  ui->horizontalSliderYTranslation->setValue(moveCentral);
  ui->horizontalSliderZTranslation->setValue(moveCentral);
  ui->horizontalSliderXRotation->setValue(moveCentral);
  ui->horizontalSliderYRotation->setValue(moveCentral);
  ui->horizontalSliderZRotation->setValue(moveCentral);
  ui->lineEditScaling->setText("1.00");
  ui->lineEditXTranslation->setText("0.00");
  ui->lineEditYTranslation->setText("0.00");
  ui->lineEditZTranslation->setText("0.00");
  ui->lineEditXRotation->setText("0.00");
  ui->lineEditYRotation->setText("0.00");
  ui->lineEditZRotation->setText("0.00");
}

void MainWindow::closeEvent(QCloseEvent *event) {
  saveSettings();
  QMainWindow::closeEvent(event);
}

void MainWindow::saveSettings() {
  QSettings settings("3DViewer", "S21");
  settings.setValue("backgroundColor", openGLWidget->getBackgroundColor());
  settings.setValue("pointSize", openGLWidget->getPointSize());
  settings.setValue("formVertices", openGLWidget->getFormVertices());
  settings.setValue("verticesColor", openGLWidget->getVerticesColor());
  settings.setValue("edgesColor", openGLWidget->getEdgesColor());
  settings.setValue("thickEdges", openGLWidget->getThickEdges());
  settings.setValue("typeEdges", openGLWidget->getTypeEdges());
  settings.setValue("projectionType", openGLWidget->getProjectionType());
}

void MainWindow::clickButtonCenter() {
  int moveCentral = 0;
  obj.centerModel();
  openGLWidget->setVertecies(obj.getVertexes());
  openGLWidget->setPoligons(obj.getPoligons());

  ui->horizontalSliderXTranslation->setValue(moveCentral);
  ui->horizontalSliderYTranslation->setValue(moveCentral);
  ui->horizontalSliderZTranslation->setValue(moveCentral);

  ui->lineEditXTranslation->setText("0.00");
  ui->lineEditYTranslation->setText("0.00");
  ui->lineEditZTranslation->setText("0.00");
  openGLWidget->update();
}

void MainWindow::clickButtonDefault() {
  fileLoading(ui->lineEditModelLoading->text());
}
