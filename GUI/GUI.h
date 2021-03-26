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
    ximu::SerialPort _sp_3;
    ximu::SerialPort _sp_4;

    ximu::SerialPort::Message _state;
    ximu::SerialPort::Message _state_3;
    ximu::SerialPort::Message _state_4;

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
    // Port 1
    void on_openClose_triggered();
    void on_message_received(ximu::SerialPort::Message m);
    void on_quaternion_received(const ximu::QuaternionData & q);
    void on_text_changed();
    // Port 3
    void on_openClose_triggered_3();
    void on_message_received_3(ximu::SerialPort::Message m);
    void on_quaternion_received_3(const ximu::QuaternionData& q);
    void on_text_changed_3();
    // Port 4
    void on_openClose_triggered_4();
    void on_message_received_4(ximu::SerialPort::Message m);
    void on_quaternion_received_4(const ximu::QuaternionData& q);
    void on_text_changed_4();

    // Port 2
    void on_openClose_triggered_2();
    void on_data_received();
    void on_text_changed_2();
public slots:
	void onGUIComms(QString);
	void onTimeout();
};
