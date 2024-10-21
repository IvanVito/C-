#ifndef GIFCREATOR_H
#define GIFCREATOR_H

#include <QDir>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>

#include "vieweropenglwidget.h"

namespace s21 {

/**
 * @brief Класс для создания GIF-анимации поля с загруженной obj-моделью
 * (размеры GIF:640x480, 10fps, 5s).
 *
 * Класс позволяет собрать готовую GIF из изображений-захватов виджета поля
 * OpenGLWidget.
 */
class GifCreator : public QObject {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса GifCreator.
   *
   * @param widget Виджет, с которого будет происходить захват кадров для
   * создания GIF.
   *
   * @param parent указатель на родительский объект для текущего виджета.
   */
  explicit GifCreator(ViewerOpenGLWidget* widget, QObject* parent = nullptr);

  /**
   * @brief Метод для выбора названия будущей GIF и старта отсчета таймера для
   * захвата изображений экрана.
   */
  void saveGif();

 private:
  QTimer* timer;  ///< Таймер, по окончанию которого, будет производится захват
                  ///< изображения поля.
  s21::ViewerOpenGLWidget*
      openGLWidget;  ///< Указатель на виджет поля с моделью.
  QList<QImage> frames;  ///< Список с захваченными изображениями.
  QString finGifName;  ///< Название GIF-файла.
  int fps;  ///< Скорость захвата кадров в секунду.
  int duration;  ///< Продолжительность захвата кадров.
  int frameCounter;  ///< Счетчик захваченных кадров.

  /**
   * @brief Метод захвата изображений поля с моделью в один GIF-файл.
   */
  void saveFrames();
};

}  // namespace s21
#endif  // GIFCREATOR_H
