#include "mainwindow.h"
#include <QSurfaceFormat>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4, 1);

    QSurfaceFormat::setDefaultFormat(format);
    MainWindow w;
    w.show();

    return a.exec();
}
