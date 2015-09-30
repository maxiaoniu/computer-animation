#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "skelontonparser.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile mfile(QString("/Users/mayue/test.skel"));
    SkelontonParser p(&mfile);

    MainWindow w;
    w.show();

    return a.exec();
}
