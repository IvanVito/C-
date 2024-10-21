#include "gifcreator.h"

#include "gif-h/gif.h"

using namespace s21;

GifCreator::GifCreator(ViewerOpenGLWidget* widget, QObject* parent)
    : QObject(parent),
      openGLWidget(widget),
      fps(10),
      duration(5000),
      frameCounter(0) {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GifCreator::saveFrames);
}

void GifCreator::saveGif() {
  QDir dir(QCoreApplication::applicationDirPath());
  dir.cd("../images");
  QString fileName = QFileDialog::getSaveFileName(
      openGLWidget, "Save GIF", dir.path(), "GIF Files (*.gif)");
  if (!fileName.isEmpty()) {
    if (!fileName.endsWith(".gif", Qt::CaseInsensitive)) fileName += ".gif";
    finGifName = fileName;
    frameCounter = 0;
    frames.clear();
    timer->start(1000 / fps);
  } else
    QMessageBox::warning(openGLWidget, "Error!",
                         "Empty file name. GIF was not saved!");
}

void GifCreator::saveFrames() {
  if (openGLWidget != nullptr) {
    int widthGif = 640;
    int heightGif = 480;
    QImage frame = openGLWidget->grabFramebuffer();
    frames.append(frame.scaled(widthGif, heightGif));
    if (++frameCounter >= fps * (duration / 1000)) {
      timer->stop();

      GifWriter gif;
      GifBegin(&gif, finGifName.toStdString().c_str(), widthGif, heightGif,
               fps);

      for (int i = 0; i < frames.size(); ++i) {
        QImage& img = frames[i];
        GifWriteFrame(&gif, img.bits(), widthGif, heightGif, fps);
      }
      if (GifEnd(&gif))
        QMessageBox::information(openGLWidget, "Success!",
                                 "GIF saved successfully!");
      else
        QMessageBox::warning(openGLWidget, "Error!", "Failed to save GIF!");
    }
  }
}
