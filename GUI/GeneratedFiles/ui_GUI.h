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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_21;
    QPlainTextEdit *plainTextEdit;
    QPushButton *btn_reset;
    QGroupBox *groupBoxBaudrates;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBoxBaudRates;
    QComboBox *comboBoxPortNames;
    QLabel *label_12;
    QPushButton *pushButtonOnOff;
    QPlainTextEdit *textArea;
    QGroupBox *groupBoxBaudrates_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonOnOff_2;
    QLabel *label_14;
    QLabel *label_13;
    QComboBox *comboBoxBaudRates_2;
    QComboBox *comboBoxPortNames_2;
    QPlainTextEdit *textArea_2;
    QLabel *label_voltage;
    QGroupBox *groupBoxBaudrates_3;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QComboBox *comboBoxBaudRates_3;
    QComboBox *comboBoxPortNames_3;
    QLabel *label_15;
    QPushButton *pushButtonOnOff_3;
    QPlainTextEdit *textArea_3;
    QGroupBox *groupBoxBaudrates_4;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QComboBox *comboBoxBaudRates_4;
    QComboBox *comboBoxPortNames_4;
    QLabel *label_16;
    QPushButton *pushButtonOnOff_4;
    QPlainTextEdit *textArea_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QString::fromUtf8("GUIClass"));
        GUIClass->resize(712, 745);
        GUIClass->setFocusPolicy(Qt::NoFocus);
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(10, 30, 691, 181));
        btn_start = new QPushButton(centralWidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(10, 670, 71, 23));
        btn_stop = new QPushButton(centralWidget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        btn_stop->setGeometry(QRect(110, 670, 71, 23));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 640, 41, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 640, 41, 21));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 10, 61, 16));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(false);
        plainTextEdit->setGeometry(QRect(10, 250, 171, 381));
        plainTextEdit->setReadOnly(true);
        btn_reset = new QPushButton(centralWidget);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setGeometry(QRect(110, 640, 71, 23));
        groupBoxBaudrates = new QGroupBox(centralWidget);
        groupBoxBaudrates->setObjectName(QString::fromUtf8("groupBoxBaudrates"));
        groupBoxBaudrates->setGeometry(QRect(200, 220, 241, 81));
        gridLayout = new QGridLayout(groupBoxBaudrates);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBoxBaudrates);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxBaudRates = new QComboBox(groupBoxBaudrates);
        comboBoxBaudRates->setObjectName(QString::fromUtf8("comboBoxBaudRates"));

        gridLayout->addWidget(comboBoxBaudRates, 1, 1, 1, 1);

        comboBoxPortNames = new QComboBox(groupBoxBaudrates);
        comboBoxPortNames->setObjectName(QString::fromUtf8("comboBoxPortNames"));

        gridLayout->addWidget(comboBoxPortNames, 1, 0, 1, 1);

        label_12 = new QLabel(groupBoxBaudrates);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 0, 1, 1, 1);

        pushButtonOnOff = new QPushButton(groupBoxBaudrates);
        pushButtonOnOff->setObjectName(QString::fromUtf8("pushButtonOnOff"));
        pushButtonOnOff->setCheckable(false);

        gridLayout->addWidget(pushButtonOnOff, 1, 2, 1, 1);

        textArea = new QPlainTextEdit(centralWidget);
        textArea->setObjectName(QString::fromUtf8("textArea"));
        textArea->setGeometry(QRect(200, 310, 241, 61));
        groupBoxBaudrates_2 = new QGroupBox(centralWidget);
        groupBoxBaudrates_2->setObjectName(QString::fromUtf8("groupBoxBaudrates_2"));
        groupBoxBaudrates_2->setGeometry(QRect(460, 220, 241, 81));
        gridLayout_2 = new QGridLayout(groupBoxBaudrates_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButtonOnOff_2 = new QPushButton(groupBoxBaudrates_2);
        pushButtonOnOff_2->setObjectName(QString::fromUtf8("pushButtonOnOff_2"));
        pushButtonOnOff_2->setCheckable(false);

        gridLayout_2->addWidget(pushButtonOnOff_2, 1, 2, 1, 1);

        label_14 = new QLabel(groupBoxBaudrates_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        label_13 = new QLabel(groupBoxBaudrates_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 0, 1, 1, 1);

        comboBoxBaudRates_2 = new QComboBox(groupBoxBaudrates_2);
        comboBoxBaudRates_2->setObjectName(QString::fromUtf8("comboBoxBaudRates_2"));

        gridLayout_2->addWidget(comboBoxBaudRates_2, 1, 1, 1, 1);

        comboBoxPortNames_2 = new QComboBox(groupBoxBaudrates_2);
        comboBoxPortNames_2->setObjectName(QString::fromUtf8("comboBoxPortNames_2"));

        gridLayout_2->addWidget(comboBoxPortNames_2, 1, 0, 1, 1);

        textArea_2 = new QPlainTextEdit(centralWidget);
        textArea_2->setObjectName(QString::fromUtf8("textArea_2"));
        textArea_2->setGeometry(QRect(460, 310, 241, 381));
        label_voltage = new QLabel(centralWidget);
        label_voltage->setObjectName(QString::fromUtf8("label_voltage"));
        label_voltage->setGeometry(QRect(20, 220, 131, 21));
        groupBoxBaudrates_3 = new QGroupBox(centralWidget);
        groupBoxBaudrates_3->setObjectName(QString::fromUtf8("groupBoxBaudrates_3"));
        groupBoxBaudrates_3->setGeometry(QRect(200, 380, 241, 81));
        gridLayout_3 = new QGridLayout(groupBoxBaudrates_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_2 = new QLabel(groupBoxBaudrates_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        comboBoxBaudRates_3 = new QComboBox(groupBoxBaudrates_3);
        comboBoxBaudRates_3->setObjectName(QString::fromUtf8("comboBoxBaudRates_3"));

        gridLayout_3->addWidget(comboBoxBaudRates_3, 1, 1, 1, 1);

        comboBoxPortNames_3 = new QComboBox(groupBoxBaudrates_3);
        comboBoxPortNames_3->setObjectName(QString::fromUtf8("comboBoxPortNames_3"));

        gridLayout_3->addWidget(comboBoxPortNames_3, 1, 0, 1, 1);

        label_15 = new QLabel(groupBoxBaudrates_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 0, 1, 1, 1);

        pushButtonOnOff_3 = new QPushButton(groupBoxBaudrates_3);
        pushButtonOnOff_3->setObjectName(QString::fromUtf8("pushButtonOnOff_3"));
        pushButtonOnOff_3->setCheckable(false);

        gridLayout_3->addWidget(pushButtonOnOff_3, 1, 2, 1, 1);

        textArea_3 = new QPlainTextEdit(centralWidget);
        textArea_3->setObjectName(QString::fromUtf8("textArea_3"));
        textArea_3->setGeometry(QRect(200, 470, 241, 61));
        groupBoxBaudrates_4 = new QGroupBox(centralWidget);
        groupBoxBaudrates_4->setObjectName(QString::fromUtf8("groupBoxBaudrates_4"));
        groupBoxBaudrates_4->setGeometry(QRect(200, 540, 241, 81));
        gridLayout_4 = new QGridLayout(groupBoxBaudrates_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_5 = new QLabel(groupBoxBaudrates_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        comboBoxBaudRates_4 = new QComboBox(groupBoxBaudrates_4);
        comboBoxBaudRates_4->setObjectName(QString::fromUtf8("comboBoxBaudRates_4"));

        gridLayout_4->addWidget(comboBoxBaudRates_4, 1, 1, 1, 1);

        comboBoxPortNames_4 = new QComboBox(groupBoxBaudrates_4);
        comboBoxPortNames_4->setObjectName(QString::fromUtf8("comboBoxPortNames_4"));

        gridLayout_4->addWidget(comboBoxPortNames_4, 1, 0, 1, 1);

        label_16 = new QLabel(groupBoxBaudrates_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_4->addWidget(label_16, 0, 1, 1, 1);

        pushButtonOnOff_4 = new QPushButton(groupBoxBaudrates_4);
        pushButtonOnOff_4->setObjectName(QString::fromUtf8("pushButtonOnOff_4"));
        pushButtonOnOff_4->setCheckable(false);

        gridLayout_4->addWidget(pushButtonOnOff_4, 1, 2, 1, 1);

        textArea_4 = new QPlainTextEdit(centralWidget);
        textArea_4->setObjectName(QString::fromUtf8("textArea_4"));
        textArea_4->setGeometry(QRect(200, 630, 241, 61));
        GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 712, 21));
        GUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUIClass->setStatusBar(statusBar);
#if QT_CONFIG(shortcut)
        label->setBuddy(comboBoxPortNames);
        label_12->setBuddy(comboBoxBaudRates);
        label_14->setBuddy(comboBoxPortNames);
        label_13->setBuddy(comboBoxBaudRates);
        label_2->setBuddy(comboBoxPortNames);
        label_15->setBuddy(comboBoxBaudRates);
        label_5->setBuddy(comboBoxPortNames);
        label_16->setBuddy(comboBoxBaudRates);
#endif // QT_CONFIG(shortcut)

        retranslateUi(GUIClass);
        QObject::connect(btn_start, SIGNAL(clicked()), GUIClass, SLOT(on_btn_start_clicked()));
        QObject::connect(btn_stop, SIGNAL(clicked()), GUIClass, SLOT(on_btn_stop_clicked()));
        QObject::connect(btn_reset, SIGNAL(clicked()), GUIClass, SLOT(on_btn_reset_clicked()));

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QCoreApplication::translate("GUIClass", "GUI", nullptr));
        btn_start->setText(QCoreApplication::translate("GUIClass", "Start", nullptr));
        btn_stop->setText(QCoreApplication::translate("GUIClass", "Stop", nullptr));
        label_3->setText(QCoreApplication::translate("GUIClass", "0.000", nullptr));
        label_4->setText(QCoreApplication::translate("GUIClass", "Time", nullptr));
        label_21->setText(QCoreApplication::translate("GUIClass", "Tau", nullptr));
        plainTextEdit->setPlainText(QString());
        btn_reset->setText(QCoreApplication::translate("GUIClass", "Reset", nullptr));
        groupBoxBaudrates->setTitle(QCoreApplication::translate("GUIClass", "X-IMU", nullptr));
        label->setText(QCoreApplication::translate("GUIClass", "&Com:", nullptr));
        label_12->setText(QCoreApplication::translate("GUIClass", "&Baudrate:", nullptr));
        pushButtonOnOff->setText(QCoreApplication::translate("GUIClass", "open", nullptr));
        groupBoxBaudrates_2->setTitle(QCoreApplication::translate("GUIClass", "Nano", nullptr));
        pushButtonOnOff_2->setText(QCoreApplication::translate("GUIClass", "open", nullptr));
        label_14->setText(QCoreApplication::translate("GUIClass", "&Com:", nullptr));
        label_13->setText(QCoreApplication::translate("GUIClass", "&Baudrate:", nullptr));
        label_voltage->setText(QCoreApplication::translate("GUIClass", "Voltage:", nullptr));
        groupBoxBaudrates_3->setTitle(QCoreApplication::translate("GUIClass", "X-IMU", nullptr));
        label_2->setText(QCoreApplication::translate("GUIClass", "&Com:", nullptr));
        label_15->setText(QCoreApplication::translate("GUIClass", "&Baudrate:", nullptr));
        pushButtonOnOff_3->setText(QCoreApplication::translate("GUIClass", "open", nullptr));
        groupBoxBaudrates_4->setTitle(QCoreApplication::translate("GUIClass", "X-IMU", nullptr));
        label_5->setText(QCoreApplication::translate("GUIClass", "&Com:", nullptr));
        label_16->setText(QCoreApplication::translate("GUIClass", "&Baudrate:", nullptr));
        pushButtonOnOff_4->setText(QCoreApplication::translate("GUIClass", "open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
