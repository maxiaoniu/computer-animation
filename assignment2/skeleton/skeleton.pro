#-------------------------------------------------
#
# Project created by QtCreator 2015-09-27T19:31:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skeleton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    balljoint.cpp \
    skelonton.cpp \
    skelontonparser.cpp \
    view.cpp \
    camera.cpp \
    trackball.cpp \
    filereader.cpp

HEADERS  += mainwindow.h \
    balljoint.h \
    skelonton.h \
    skelontonparser.h \
    view.h \
    vertex.h \
    camera.h \
    trackball.h \
    filereader.h

FORMS    += mainwindow.ui

RESOURCES += \
    shader.qrc
