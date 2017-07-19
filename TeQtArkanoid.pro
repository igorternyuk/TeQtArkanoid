#-------------------------------------------------
#
# Project created by QtCreator 2017-07-18T07:59:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeQtArkanoid
TEMPLATE = app

DEFINES += DEBUG

SOURCES += main.cpp\
        widget.cpp \
    scene.cpp \
    ball.cpp \
    paddle.cpp \
    tethread.cpp \
    brick.cpp \
    entity.cpp \
    controller.cpp

HEADERS  += widget.h \
    scene.h \
    ball.h \
    paddle.h \
    tethread.h \
    brick.h \
    arkanoidGlobalDefines.h \
    entity.h \
    controller.h

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=c++14
