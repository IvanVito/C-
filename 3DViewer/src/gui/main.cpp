#include <QApplication>
#include <clocale>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  std::setlocale(LC_ALL, "C");
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("CPP4_3DViewer_v2.0 by lesleyle and lemongrb");
  w.show();
  return a.exec();
}
