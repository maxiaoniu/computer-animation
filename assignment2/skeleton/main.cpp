#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "skelontonparser.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile  mfile(QString("/Users/mayue/test.skel"));
    qDebug()<<mfile.isOpen();
    SkelontonParser p(&mfile);

    MainWindow w;
    w.show();

    return a.exec();
}
