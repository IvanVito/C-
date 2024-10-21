#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "../back/controller.h"
#include "gifcreator.h"
#include "vieweropenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Главный класс-виджет, содержащий в себе виджет ViewerOpenGLWidget
 * отображения obj-модели и механизмы управления её отображением.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса MainWindow
   * @param parent указатель на родительский объект для текущего виджета
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Деструктор класса MainWindow
   */
  ~MainWindow();

 private slots:
  /**
   * @brief Метод для установки сигнально-слотовых отношений в программе
   * 3DViewer.
   */
  void setConnects();

  /**
   * @brief Метод для установки сигнально-слотовых отношений в программе
   3DViewer для совершения двигательных операций над моделью.
   */
  void setMovementsConnects();

  /**
   * @brief Метод для выбора цвета фона окна-виджета ViewerOpenGLWidget.
   */
  void clickButtonBackground();

  /**
   * @brief Метод, с помощью которого можно выбрать файл .obj для загрузки
   * выбранной модели в программу.
   */
  void clickButtonModelLoading();

  /**
   * @brief Метод, с помощью которого можно загрузить из файла .obj выбранную
   * модель в программу по указанному в поле пути.
   */
  void changeLineModelPath();

  /**
   * @brief Метод для загрузки выбранной модели в программу 3DViewer.
   *
   * @param fileName Имя файла .obj с моделью.
   */
  void fileLoading(const QString &fileName);

  /**
   * @brief Метод, который задает диапазон значений для всех ползунков.
   */
  void setSliderHalf();

  /**
   * @brief Метод, позволяющий масштабировать модель в указанное число раз с
   * помощью ползунка.
   *
   * @param value Значение, в которое число раз маштабируется модель.
   */
  void changeScaleSlider(int value);

  /**
   * @brief Метод, позволяющий изменять размер отображения вершин с помощью
   * ползунка.
   *
   * @param value Значение, на которое меняется размер отображения вершин.
   */
  void changeSizeVertices(int value);

  /**
   * @brief Метод, меняющий форму вершин.
   *
   * @param form Новая форма вершин.
   */
  void changeFormVertices(int form);

  /**
   * @brief Метод, меняющий цвет отображения вершин.
   */
  void clickButtonColorVertices();

  /**
   * @brief Метод, меняющий цвет отображения ребер.
   */
  void clickButtonColorEdges();

  /**
   * @brief Метод, меняющий толщину ребер.
   *
   * @param value Новый толщина ребер.
   */
  void changeThickEdges(int value);

  /**
   * @brief Метод, меняющий тип отображения ребер.
   *
   * @param type Новый тип ребер.
   */
  void changeTypeEdges(int type);

  /**
   * @brief Метод, меняющий тип проекции отображения модели.
   *
   * @param type Новый тип проекции.
   */
  void changeProjectionType(int type);

  /**
   * @brief Метод, который загружает сохраненные настройки отображения модели.
   */
  void loadingCustomize();

  /**
   * @brief Метод, позволяющий сохранить изображение текущего окна-виджета
   * ViewerOpenGLWidget.
   */
  void saveImage();

  /**
   * @brief Метод, позволяющий переместить модель по оси X на указанное значение
   * с помощью ползунка.
   *
   * @param value Значение, на которое переместится модель по оси X.
   */
  void changeXTranslate(int value);

  /**
   * @brief Метод, позволяющий переместить модель по оси Y на указанное значение
   * с помощью ползунка.
   *
   * @param value Значение, на которое переместится модель по оси Y.
   */
  void changeYTranslate(int value);

  /**
   * @brief Метод, позволяющий переместить модель по оси Z на указанное значение
   * с помощью ползунка.
   *
   * @param value Значение, на которое переместится модель по оси Z.
   */
  void changeZTranslate(int value);

  /**
   * @brief Метод, позволяющий повернуть модель по оси X на указанное значение с
   * помощью ползунка.
   *
   * @param value Значение, на которое повернется модель по оси X.
   */
  void changeXRotate(int value);

  /**
   * @brief Метод, позволяющий повернуть модель по оси Y на указанное значение с
   * помощью ползунка.
   *
   * @param value Значение, на которое повернется модель по оси Y.
   */
  void changeYRotate(int value);

  /**
   * @brief Метод, позволяющий повернуть модель по оси Z на указанное значение с
   * помощью ползунка.
   *
   * @param value Значение, на которое повернется модель по оси Z.
   */
  void changeZRotate(int value);

  /**
   * @brief Метод, позволяющий масштабировать модель в указанное число раз в
   * поле ввода.
   */
  void changeLineScale();

  /**
   * @brief Метод, позволяющий переместить модель по оси X на указанное значение
   * в поле ввода.
   */
  void changeLineXTranslate();

  /**
   * @brief Метод, позволяющий переместить модель по оси Y на указанное значение
   * в поле ввода.
   */
  void changeLineYTranslate();

  /**
   * @brief Метод, позволяющий переместить модель по оси Z на указанное значение
   * в поле ввода.
   */
  void changeLineZTranslate();

  /**
   * @brief Метод, позволяющий повернуть модель по оси X на указанное значение в
   * поле ввода.
   */
  void changeLineXRotate();

  /**
   * @brief Метод, позволяющий повернуть модель по оси Y на указанное значение в
   * поле ввода.
   */
  void changeLineYRotate();

  /**
   * @brief Метод, позволяющий повернуть модель по оси Z на указанное значение в
   * поле ввода.
   */
  void changeLineZRotate();

  /**
   * @brief Метод, устанавливающий все ползунки и поля ввода в первоначальное
   * состояние.
   */
  void setDefaultSliders();

  /**
   * @brief Метод, сохраняющий настройки отображения модели.
   */
  void saveSettings();

  /**
   * @brief Метод, перемещающий модель в центр виджета ViewerOpenGLWidget.
   */
  void clickButtonCenter();

  /**
   * @brief Метод, возвращающий модель в первоначальное состояние после
   * загрузки.
   */
  void clickButtonDefault();

 protected:
  /**
   * @brief Виртуальный метод класса QWidget, используется для выполнения
   * дополнительных действий перед закрытием виджета, в нашем случае для
   * сохранения настроек отображения модели.
   *
   * @param event Указатель, который содержит информацию о событии закрытия
   * виджета.
   */
  void closeEvent(QCloseEvent *event) override;

  /**
   * @brief Обработка событий, которые происходят посел нажатия на клавиши с
   * клавиатуры.
   *
   * @param e Указатель на объект, который представляет событие нажатия клавиши
   * на клавиатуре в Qt.
   */
  void keyPressEvent(QKeyEvent *e) override;

 private:
  Ui::MainWindow
      *ui;  ///< Указатель на пользовательский интерфейс программы 3DViewer
  s21::ViewerOpenGLWidget
      *openGLWidget;  ///< Указатель на класс ViewerOpenGLWidget для работы с
                      ///< отображением модели.
  s21::Controller obj;  ///< Класс Controller для соединения с логикой(моделью)
                        ///< для расчетов Афинных преобразований.
  s21::GifCreator *gifCreator;  ///< Указатель на класс GifCreator, с помощью
                                ///< которого создается GIF.
};

#endif  // MAINWINDOW_H
