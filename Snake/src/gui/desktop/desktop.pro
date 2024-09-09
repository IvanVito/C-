QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

contains(CONFIG, snake) {

    QMAKE_CXXFLAGS += -D SNAKE 

    SOURCES += \
        ../../brick_game/snake/controller.cpp \
        ../../brick_game/snake/snake.cpp \
        ../../brick_game/snake/fsm.cpp \
        snakeQT.cpp \

    HEADERS += \
        ../../brick_game/snake/controller.h \
        ../../brick_game/snake/fsm.h \
        ../../brick_game/snake/snake.h \
        snakeQT.h \

   TARGET = ../../build/desktop/snake
}

contains(CONFIG, tetris) {

    QMAKE_CXXFLAGS += -D TETRIS 

    SOURCES += \
        ../../brick_game/brick_game/tetris.c \
        ../../brick_game/brick_game/fsm.c \
        tetrisQT.cpp

    HEADERS += \
        ../../brick_game/brick_game/tetris.h \
        ../../brick_game/brick_game/fsm.h \
        tetrisQT.h

    TARGET = ../../build/desktop/tetris 
}

contains(CONFIG, menu) {
    QMAKE_CXXFLAGS += -D MENU 
    SOURCES += \
        ../../brick_game/menu/menuQT.cpp \

    HEADERS += ../../brick_game/menu/menuQT.h

    TARGET = ../../build/desktop/desktopMenu
}

SOURCES += \
    mainwindow.cpp \

HEADERS += \
    mainwindow.h \

FORMS += \
    mainwindow.ui
    
RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
