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
    skelontonparser.cpp

HEADERS  += mainwindow.h \
    balljoint.h \
    skelonton.h \
    skelontonparser.h

FORMS    += mainwindow.ui
