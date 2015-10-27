#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openGLWidget_updateJointNameSignal(const QStringList list)
{
    qDebug()<<"clidked";
    ui->comboBox->clear();
    ui->comboBox->insertItems(0,list);
}
