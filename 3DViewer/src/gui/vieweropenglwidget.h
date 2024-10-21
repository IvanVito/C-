#ifndef VIEWEROPENGLWIDGET_H
#define VIEWEROPENGLWIDGET_H

#include <GL/glu.h>

#include <QColor>
#include <QImage>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>

#define ZERO 0
#define DEFAULT 1.0

namespace s21 {
/**
 * @brief Класс для отображения загруженной obj-модели.
 *
 * Класс позволяет изменять настройки отображения видимой модели.
 */
class ViewerOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  /**
   * @brief Конструктор класса ViewerOpenGLWidget.
   *
   * @param parent указатель на родительский объект для текущего виджета.
   */
  ViewerOpenGLWidget(QWidget *parent = nullptr);

  /**
   * @brief Метод для изменения фона виджета ViewerOpenGLWidget.
   *
   * @param color Ссылка на выбранный новый цвет фона.
   */
  void setBackgroundColor(const QColor &color);

  /**
   * @brief Взятие текущего цвета фона виджета ViewerOpenGLWidget.
   *
   * @return Текущий цвет фона в формате RGBA.
   */
  QColor getBackgroundColor() const;

  /**
   * @brief Метод для установки указанных вершин отображаемой модели.
   *
   * @param vertexes Ссылка на вектор векторов с координатами (x, y, z)
   * вершин.
   */
  void setVertecies(const std::vector<std::vector<double>> &vertexes);

  /**
   * @brief Метод для установки указанных полигонов отображаемой модели.
   *
   * @param poligons Ссылка на вектор векторов со списком полигонов,
   * составляющие отображаемую модель.
   */
  void setPoligons(const std::vector<std::vector<int>> &poligons);

  /**
   * @brief Метод для установки указанного размера вершин отображаемой модели.
   *
   * @param newPointSize Новый размер вершин.
   */
  void setPointSize(double newPointSize);

  /**
   * @brief Метод для установки указанной формы вершин отображаемой модели.
   *
   * @param newForm Новая форма вершин.
   */
  void setFormVertices(const int &newForm);

  /**
   * @brief Метод для установки указанного цвета вершин отображаемой модели.
   *
   * @param color Новый цвет вершин.
   */
  void setVerticesColor(const QColor &color);

  /**
   * @brief Метод получения информации о текущем цвете вершин отображаемой
   * модели.
   *
   * @return Текущий цвет вершин.
   */
  QColor getVerticesColor() const;

  /**
   * @brief Метод для установки указанного цвета ребер отображаемой модели.
   *
   * @param color Новый цвет ребер.
   */
  void setEdgesColor(const QColor &color);

  /**
   * @brief Метод получения информации о текущем цвете ребер отображаемой
   * модели.
   *
   * @return Текущий цвет ребер.
   */
  QColor getEdgesColor() const;

  /**
   * @brief Метод для установки указанной толщины ребер отображаемой модели.
   *
   * @param newThickEdges Новый размер ребер.
   */
  void setThickEdges(double newThickEdges);

  /**
   * @brief Метод для установки указанного типа ребер отображаемой модели.
   *
   * @param newType Новый тип отображения ребер.
   */
  void setTypeEdges(const int &newType);

  /**
   * @brief Метод для установки указанного типа проекции.
   *
   * @param newType Новый тип проекции.
   */
  void setProjectionType(const int &newType);

  /**
   * @brief Метод для сохранения изображения виджета ViewerOpenGLWidget.
   *
   * @param fileName Имя сохраняемого изображения.
   * @param format Формат сохраняемого изоражения.
   */
  void saveImageWidget(const QString &fileName, const char *format);

  /**
   * @brief Метод получения информации о текущем цвете фона виджета,
   * отображающего obj-модель.
   *
   * @return Текущий цвет фона виджета ViewerOpenGLWidget.
   */
  QColor getBackgroundColor();

  /**
   * @brief Метод получения информации о текущем размере отображаемых вершин
   * модели.
   *
   * @return Текущий размер вершин.
   */
  double getPointSize();

  /**
   * @brief Метод получения информации о текущем типе отображения вершин
   * модели.
   *
   * @return Текущий тип вершин.
   */
  int getFormVertices();

  /**
   * @brief Метод получения информации о текущей толщине отображаемых ребер
   * модели.
   *
   * @return Толщина ребер в пикселях.
   */
  double getThickEdges();

  /**
   * @brief Метод получения информации о текущем типе отображения ребер
   * модели.
   *
   * @return Текущий тип ребер.
   */
  int getTypeEdges();

  /**
   * @brief Метод получения информации о текущем типе проекции.
   *
   * @return Текущий тип проекции.
   */
  int getProjectionType();

 protected:
  /**
   * @brief Метод, использующийся для инициализации контекста OpenGL,
   * настройки параметров отображения и загрузки ресурсов.
   */
  void initializeGL() override;

  /**
   * @brief Метод, использующийся для отрисовки графики на экране виджета
   * ViewerOpenGLWidget.
   */
  void paintGL() override;

  /**
   * @brief Данный метод используется для обновления размеров области
   * просмотра OpenGL в соответствии с новыми размерами виджета.
   *
   * @param width Новая ширина экрана в пикселях
   * @param height Новая высота экрана в пикселях
   */
  void resizeGL(int width, int height) override;

 private:
  QColor backgroundColor_;  ///< Текущий цвет фона виджета ViewerOpenGLWidget.
  std::vector<std::vector<double>>
      vert_;  ///< Вектор векторов, хранящий в себе x, y, z координаты вершин.
  std::vector<std::vector<int>>
      poli_;  ///< Вектор векторов, хранящий в себе последовательность
              ///< соединений вершин для отрисовки модели (полигонов).

  double pointSize_;  ///< Размер отображаемых вершин в пикселях.
  int formVert_;  ///< Текущая форма отображаемых вершин.
  QColor verticesColor_;  ///< Текущий цвет отображаемых вершин.
  QColor edgesColor_;  ///< Текущий цвет отображаемых ребер.
  double thickEdges_;  ///< Толщина отображаемых ребер в пикселях.
  int typeEdges_;  ///< Текущая форма отображаемых ребер.
  int projectionType_;  ///< Тип проекции.

  /**
   * @brief Метод для отрисовки ребер на виджете ViewerOpenGLWidget.
   *
   */
  void paintEdges();

  /**
   * @brief Метод для отрисовки вершин на виджете ViewerOpenGLWidget.
   *
   */
  void paintVertices();
};

}  // namespace s21

#endif  // VIEWEROPENGLWIDGET_H
