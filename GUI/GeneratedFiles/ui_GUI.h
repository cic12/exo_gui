/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QWidget *centralWidget;
    QCustomPlot *plot;
    QLabel *label_21;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QLabel *label_3;
    QLabel *label_4;
    QPlainTextEdit *plainTextEdit;
    QPushButton *btn_reset;
    QLabel *label_voltage;
    QCustomPlot *plot_2;
    QLabel *label_22;
    QCustomPlot *plot_3;
    QLabel *label_23;
    QCustomPlot *plot_4;
    QLabel *label_24;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QString::fromUtf8("GUIClass"));
        GUIClass->resize(702, 607);
        GUIClass->setFocusPolicy(Qt::NoFocus);
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(190, 10, 501, 121));
        label_21 = new QLabel(plot);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(210, 0, 61, 21));
        btn_start = new QPushButton(centralWidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(10, 70, 71, 23));
        btn_stop = new QPushButton(centralWidget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        btn_stop->setGeometry(QRect(110, 70, 71, 23));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 40, 41, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 40, 41, 21));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(false);
        plainTextEdit->setGeometry(QRect(10, 140, 171, 411));
        plainTextEdit->setReadOnly(true);
        btn_reset = new QPushButton(centralWidget);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setGeometry(QRect(110, 40, 71, 23));
        label_voltage = new QLabel(centralWidget);
        label_voltage->setObjectName(QString::fromUtf8("label_voltage"));
        label_voltage->setGeometry(QRect(10, 10, 131, 21));
        plot_2 = new QCustomPlot(centralWidget);
        plot_2->setObjectName(QString::fromUtf8("plot_2"));
        plot_2->setGeometry(QRect(190, 150, 501, 121));
        label_22 = new QLabel(plot_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(210, 0, 61, 21));
        plot_3 = new QCustomPlot(centralWidget);
        plot_3->setObjectName(QString::fromUtf8("plot_3"));
        plot_3->setGeometry(QRect(190, 290, 501, 121));
        label_23 = new QLabel(plot_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(200, 0, 61, 21));
        plot_4 = new QCustomPlot(centralWidget);
        plot_4->setObjectName(QString::fromUtf8("plot_4"));
        plot_4->setGeometry(QRect(190, 430, 501, 121));
        label_24 = new QLabel(plot_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(220, 0, 61, 21));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 110, 70, 17));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(110, 110, 70, 17));
        GUIClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUIClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 702, 21));
        GUIClass->setMenuBar(menuBar);

        retranslateUi(GUIClass);
        QObject::connect(btn_start, SIGNAL(clicked()), GUIClass, SLOT(on_btn_start_clicked()));
        QObject::connect(btn_stop, SIGNAL(clicked()), GUIClass, SLOT(on_btn_stop_clicked()));
        QObject::connect(btn_reset, SIGNAL(clicked()), GUIClass, SLOT(on_btn_reset_clicked()));

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QCoreApplication::translate("GUIClass", "GUI", nullptr));
        label_21->setText(QCoreApplication::translate("GUIClass", "Position", nullptr));
        btn_start->setText(QCoreApplication::translate("GUIClass", "Start", nullptr));
        btn_stop->setText(QCoreApplication::translate("GUIClass", "Stop", nullptr));
        label_3->setText(QCoreApplication::translate("GUIClass", "0.000", nullptr));
        label_4->setText(QCoreApplication::translate("GUIClass", "Time (s):", nullptr));
        plainTextEdit->setPlainText(QString());
        btn_reset->setText(QCoreApplication::translate("GUIClass", "Reset", nullptr));
        label_voltage->setText(QCoreApplication::translate("GUIClass", "Voltage (V):", nullptr));
        label_22->setText(QCoreApplication::translate("GUIClass", "Torque", nullptr));
        label_23->setText(QCoreApplication::translate("GUIClass", "Orientation", nullptr));
        label_24->setText(QCoreApplication::translate("GUIClass", "EMG", nullptr));
        checkBox->setText(QCoreApplication::translate("GUIClass", "Exo", nullptr));
        checkBox_2->setText(QCoreApplication::translate("GUIClass", "EMG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
