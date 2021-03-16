#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include "ui_GUI.h"
#include "controlThread.h"
#include "qcustomplot.h"

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(QWidget *parent = Q_NULLPTR);
	ControlThread *controlThread;
	QTimer *timer;
private:
	QSerialPort* _sp_2;

	Ui::GUIClass ui;

	bool gui_reset;
	bool gui_done;
	double time;
	plotVars plot_vars;

	void initPlots();
	void clearPlots();
	void addPoints(plotVars);
	void plot();
private slots:
	void on_btn_start_clicked();
	void on_btn_stop_clicked();
	void on_btn_reset_clicked();
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

public slots:
	void onGUIComms(QString);
	void onTimeout();
};
