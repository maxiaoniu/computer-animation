/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "filereader.h"
#include "view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    view *openGLWidget;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    FileReader *filereader;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QComboBox *comboBox;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new view(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(200, 0, 600, 600));
        openGLWidget->setMinimumSize(QSize(600, 600));
        openGLWidget->setMaximumSize(QSize(600, 600));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 190, 600));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 181, 41));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        filereader = new FileReader(gridLayoutWidget);
        filereader->setObjectName(QStringLiteral("filereader"));

        gridLayout->addWidget(filereader, 0, 0, 1, 1);

        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 70, 175, 94));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinBox = new QSpinBox(formLayoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimumSize(QSize(100, 0));
        spinBox->setMinimum(-360);
        spinBox->setMaximum(360);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBox);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        spinBox_4 = new QSpinBox(formLayoutWidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMinimumSize(QSize(100, 0));
        spinBox_4->setMinimum(-360);
        spinBox_4->setMaximum(360);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBox_4);

        spinBox_5 = new QSpinBox(formLayoutWidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMinimumSize(QSize(100, 0));
        spinBox_5->setMinimum(-360);
        spinBox_5->setMaximum(360);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBox_5);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 190, 171, 26));
        formLayoutWidget_2 = new QWidget(groupBox);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(10, 220, 175, 94));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        spinBox_2 = new QSpinBox(formLayoutWidget_2);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(100, 0));
        spinBox_2->setMinimum(-360);
        spinBox_2->setMaximum(360);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinBox_2);

        label_6 = new QLabel(formLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(formLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        spinBox_6 = new QSpinBox(formLayoutWidget_2);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMinimumSize(QSize(100, 0));
        spinBox_6->setMinimum(-360);
        spinBox_6->setMaximum(360);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, spinBox_6);

        spinBox_7 = new QSpinBox(formLayoutWidget_2);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setMinimumSize(QSize(100, 0));
        spinBox_7->setMinimum(-360);
        spinBox_7->setMaximum(360);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, spinBox_7);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(filereader, SIGNAL(fileChanged(QString)), openGLWidget, SLOT(recFile(QString)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), openGLWidget, SLOT(worldRotationX(int)));
        QObject::connect(spinBox_4, SIGNAL(valueChanged(int)), openGLWidget, SLOT(worldRotationY(int)));
        QObject::connect(spinBox_5, SIGNAL(valueChanged(int)), openGLWidget, SLOT(worldRotationZ(int)));
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), openGLWidget, SLOT(jointSelect(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), openGLWidget, SLOT(localRotationX(int)));
        QObject::connect(spinBox_6, SIGNAL(valueChanged(int)), openGLWidget, SLOT(localRotationY(int)));
        QObject::connect(spinBox_7, SIGNAL(valueChanged(int)), openGLWidget, SLOT(localRotationZ(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Option", 0));
        label->setText(QApplication::translate("MainWindow", "X Axis:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Y Axis:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Z Axis:", 0));
        label_2->setText(QApplication::translate("MainWindow", "X Axis:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Y Axis:", 0));
        label_7->setText(QApplication::translate("MainWindow", "Z Axis:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
