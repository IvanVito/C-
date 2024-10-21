QT += core gui widgets opengl openglwidgets

CONFIG += c++17

win32 {
    LIBS += -lglu32 -lopengl32
}

unix {
    LIBS += -lGLU -lGL
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../gui/gifcreator.cpp \
    ../gui/main.cpp \
    ../gui/mainwindow.cpp \
    ../gui/vieweropenglwidget.cpp \
    ../back/controller.cpp \
    ../back/parser.cpp \
    ../back/affinTrans.cpp \
    ../back/matrix/s21MatrixOop.cpp \
    ../back/otherTrans.cpp \
    ../back/facade.cpp \

HEADERS += \
    ../gui/gifcreator.h \
    ../gui/mainwindow.h \
    ../gui/vieweropenglwidget.h \
    ../back/controller.h \
    ../back/parser.h \
    ../back/affinTrans.h \
    ../back/matrix/s21MatrixOop.h \
    ../back/otherTrans.h \
    ../back/facade.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
