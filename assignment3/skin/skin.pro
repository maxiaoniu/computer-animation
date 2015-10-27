#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T16:06:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    view.cpp \
    filereader.cpp \
    balljoint.cpp \
    skelontonparser.cpp \
    skelonton.cpp \
    camera.cpp \
    trackball.cpp \
    skinparser.cpp

HEADERS  += mainwindow.h \
    view.h \
    balljoint.h \
    skelontonparser.h \
    vertex.h \
    skelonton.h \
    camera.h \
    filereader.h \
    trackball.h \
    skinparser.h

RESOURCES += \
    shader.qrc

FORMS += \
    mainwindow.ui

DISTFILES += \
    skin.pro.user \
    skeleton.pro.user
