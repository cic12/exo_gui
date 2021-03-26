#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include "ximuapi/io/serial_port.h"
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

    ximu::SerialPort _sp;

    ximu::SerialPort::Message _state;

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
    void process_line(const QByteArray & line);
private slots:
	void on_btn_start_clicked();
	void on_btn_stop_clicked();
	void on_btn_reset_clicked();
    void on_checkBox_clicked();
    void on_checkBox_2_clicked();

    // x-IMU Port
    void on_openClose_triggered();
    void on_message_received(ximu::SerialPort::Message m);
    void on_quaternion_received(const ximu::QuaternionData & q);
    void on_text_changed();

    // Nano Port
    void on_openClose_triggered_2();
    void on_data_received();
    void on_text_changed_2();
public slots:
	void onGUIComms(QString);
	void onTimeout();
};
