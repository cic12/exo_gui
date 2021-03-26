#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent),
        _state(ximu::SerialPort::Message::OKE)
{
	ui.setupUi(this);

	gui_reset = true;
	gui_done = false;

	initPlots();

	controlThread = new ControlThread(this);
	timer = new QTimer(this);
	timer->setTimerType(Qt::PreciseTimer);

    ui.checkBox->setChecked(controlThread->test.exo);
    ui.checkBox_2->setChecked(controlThread->test.emg);

	connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::onTimeout)); // GUI update
	connect(controlThread, SIGNAL(GUIComms(QString)), this, SLOT(onGUIComms(QString))); // GUI print function

    ui.comboBoxBaudRates->addItem("115200", QVariant(115200));
    ui.comboBoxBaudRates_2->addItem("115200", QVariant(115200));

    for (auto& port : QSerialPortInfo::availablePorts()) {
        ui.comboBoxPortNames->addItem(port.systemLocation());
        ui.comboBoxPortNames_2->addItem(port.systemLocation());;
    }

    // QSerialPort
    _sp_2 = new QSerialPort(this);
    connect(_sp_2, &QSerialPort::readyRead, this, &GUI::on_data_received);

    // gui::button open/close
    connect(ui.pushButtonOnOff, &QPushButton::clicked, this, &GUI::on_openClose_triggered);
    connect(ui.pushButtonOnOff_2, &QPushButton::clicked, this, &GUI::on_openClose_triggered_2);

    // serialport::quaternion
    connect(&_sp, &ximu::SerialPort::quaternion, this, &GUI::on_quaternion_received);

    // serialport::messages
    connect(&_sp, &ximu::SerialPort::messages, this, &GUI::on_message_received);

    // text changed
    connect(ui.textArea, &QPlainTextEdit::textChanged, this, &GUI::on_text_changed);
    connect(ui.textArea_2, &QPlainTextEdit::textChanged, this, &GUI::on_text_changed_2);
}

void GUI::onTimeout()
{
	controlThread->mutex.lock();
    if (controlThread->control_initialised) {
		plot_vars = controlThread->vars;
		if (controlThread->Stop) {
			timer->stop();
		}
	}
	controlThread->mutex.unlock();
	ui.label_3->setText(QString::number(plot_vars.time, 'f', 3));
    ui.label_voltage->setText("Voltage (V):  " + QString::number(controlThread->voltage));
	addPoints(plot_vars);
}

void GUI::on_btn_start_clicked()
{
	if (gui_reset) {
		controlThread->start(QThread::TimeCriticalPriority);
		clearPlots();
		timer->start(20); // Timer period in ms controls GUI update frequency
		gui_reset = false;
	}
	else
	{
		on_btn_reset_clicked();
	}
}

void GUI::on_btn_stop_clicked()
{
	if (!gui_reset) {
		controlThread->Stop = true;
	}
}

void GUI::on_btn_reset_clicked()
{
	if (gui_done && !gui_reset) {
		controlThread = new ControlThread(this);
        controlThread->test.exo = ui.checkBox->checkState();
        controlThread->test.emg = ui.checkBox_2->checkState();
		clearPlots();
		plot();
		ui.plainTextEdit->clear();
		connect(controlThread, SIGNAL(GUIComms(QString)), this, SLOT(onGUIComms(QString))); // GUI print function
		gui_reset = true;
		gui_done = false;
	}
}

void GUI::on_openClose_triggered()
{
    switch (_state)
    {
    case ximu::SerialPort::Message::OKE:
    case ximu::SerialPort::Message::CLOSED:
    case ximu::SerialPort::Message::COULD_NOT_OPEN:
    {
        _sp.open(
            ui.comboBoxPortNames->currentText().toStdString(),
            ui.comboBoxBaudRates->currentData().toInt()
        );
        break;
    }
    case ximu::SerialPort::OPEN:
    {
        _sp.close();
    }
    }
}

void GUI::on_message_received(ximu::SerialPort::Message m)
{
    _state = m;
    switch (_state)
    {
    case ximu::SerialPort::Message::OPEN:
        ui.comboBoxPortNames->setEnabled(false);
        ui.comboBoxBaudRates->setEnabled(false);
        ui.pushButtonOnOff->setText(tr("close"));
        break;

    case ximu::SerialPort::Message::CLOSED:
        ui.comboBoxPortNames->setEnabled(true);
        ui.comboBoxBaudRates->setEnabled(true);
        ui.pushButtonOnOff->setText(tr("open"));
        break;

    case ximu::SerialPort::Message::COULD_NOT_OPEN:
        ui.textArea->appendPlainText(tr("[ERR] Could not open port"));
    }
}

void GUI::on_quaternion_received(const ximu::QuaternionData& q)
{
    std::stringstream ss;
    ss << "Quaternion (" << q.w() << "," << q.x() << "," << q.y() << "," << q.z() << ")";
    ui.textArea->appendPlainText(QString::fromStdString(ss.str()));
    controlThread->imu_quat[0] = q.w();
    controlThread->imu_quat[1] = q.x();
    controlThread->imu_quat[2] = q.y();
    controlThread->imu_quat[3] = q.z();
}

void GUI::on_text_changed() {
    if (ui.textArea->document()->lineCount() > 5)
        ui.textArea->clear();
}

void GUI::on_openClose_triggered_2()
{
    if (!_sp_2->isOpen()) {
        _sp_2->setPortName(ui.comboBoxPortNames_2->currentText());
        _sp_2->setBaudRate(ui.comboBoxBaudRates_2->currentData().toInt());

        if (_sp_2->open(QIODevice::ReadOnly)) {
            ui.comboBoxPortNames_2->setEnabled(false);
            ui.comboBoxBaudRates_2->setEnabled(false);
            ui.pushButtonOnOff_2->setText(tr("close"));
            ui.textArea_2->appendPlainText(tr("Port Open"));
        }
        else {
            ui.textArea_2->appendPlainText(tr("[ERR] Could not open port"));
        }
    }
    else {
        if (_sp_2->isOpen())
            _sp_2->close();
        ui.comboBoxPortNames_2->setEnabled(true);
        ui.comboBoxBaudRates_2->setEnabled(true);
        ui.pushButtonOnOff_2->setText(tr("open"));
        ui.textArea_2->appendPlainText(tr("Disconnected"));
    }
}

void GUI::on_data_received()
{
    while (_sp_2->canReadLine()) process_line(_sp_2->readLine());
}

void GUI::process_line(const QByteArray & line)
{
    ui.textArea_2->appendPlainText(QString::fromUtf8(line));
    auto data = line.split(' ');
    controlThread->nano[0] = data[0].toDouble();
    controlThread->nano[1] = data[1].toDouble();
    controlThread->nano[2] = data[2].toDouble();
    controlThread->nano[3] = data[3].toDouble();
}

void GUI::on_text_changed_2()
{
    if (ui.textArea_2->document()->lineCount() > 20)
        ui.textArea_2->clear();
}

void GUI::onGUIComms(QString message)
{
	if (message == "DONE") {
		gui_done = true;
	}
	else {
		ui.plainTextEdit->insertPlainText(message);
	}
}

void GUI::initPlots()
{
	QFont font; // include this to fully disable antialiasing for higher performance
	font.setStyleStrategy(QFont::NoAntialias);

    ui.plot->setNotAntialiasedElements(QCP::aeAll);
    ui.plot->xAxis->setTickLabelFont(font);
    ui.plot->yAxis->setTickLabelFont(font);
    ui.plot->legend->setFont(font);

    ui.plot_2->setNotAntialiasedElements(QCP::aeAll);
    ui.plot_2->xAxis->setTickLabelFont(font);
    ui.plot_2->yAxis->setTickLabelFont(font);
    ui.plot_2->legend->setFont(font);

    ui.plot_3->setNotAntialiasedElements(QCP::aeAll);
    ui.plot_3->xAxis->setTickLabelFont(font);
    ui.plot_3->yAxis->setTickLabelFont(font);
    ui.plot_3->legend->setFont(font);

    ui.plot_4->setNotAntialiasedElements(QCP::aeAll);
    ui.plot_4->xAxis->setTickLabelFont(font);
    ui.plot_4->yAxis->setTickLabelFont(font);
    ui.plot_4->legend->setFont(font);

	// add plots
    ui.plot->addGraph();
    ui.plot->graph(0)->setPen(QPen(Qt::blue));
    ui.plot->addGraph();
    ui.plot->graph(1)->setPen(QPen(Qt::red));

    ui.plot_2->addGraph();
    ui.plot_2->graph(0)->setPen(QPen(Qt::blue));
    ui.plot_2->addGraph();
    ui.plot_2->graph(1)->setPen(QPen(Qt::red));

    ui.plot_3->addGraph();
    ui.plot_3->graph(0)->setPen(QPen(Qt::blue));
    ui.plot_3->addGraph();
    ui.plot_3->graph(1)->setPen(QPen(Qt::red));
    ui.plot_3->addGraph();
    ui.plot_3->graph(2)->setPen(QPen(Qt::green));
    ui.plot_3->addGraph();
    ui.plot_3->graph(3)->setPen(QPen(Qt::yellow));

    ui.plot_4->addGraph();
    ui.plot_4->graph(0)->setPen(QPen(Qt::blue));
    ui.plot_4->addGraph();
    ui.plot_4->graph(1)->setPen(QPen(Qt::red));
    ui.plot_4->addGraph();
    ui.plot_4->graph(2)->setPen(QPen(Qt::green));
    ui.plot_4->addGraph();
    ui.plot_4->graph(3)->setPen(QPen(Qt::yellow));

	// axes settings
    ui.plot->xAxis->setAutoTickStep(false);
    ui.plot->xAxis->setTickStep(1);
    ui.plot->yAxis->setAutoTickStep(false);
    ui.plot->yAxis->setTickStep(0.5);

    ui.plot_2->xAxis->setAutoTickStep(false);
    ui.plot_2->xAxis->setTickStep(1);
    ui.plot_2->yAxis->setAutoTickStep(false);
    ui.plot_2->yAxis->setTickStep(20);

    ui.plot_3->xAxis->setAutoTickStep(false);
    ui.plot_3->xAxis->setTickStep(1);
    ui.plot_3->yAxis->setAutoTickStep(false);
    ui.plot_3->yAxis->setTickStep(1);

    ui.plot_4->xAxis->setAutoTickStep(false);
    ui.plot_4->xAxis->setTickStep(1);
    ui.plot_4->yAxis->setAutoTickStep(false);
    ui.plot_4->yAxis->setTickStep(0.25);

    // axes ranges
    ui.plot->xAxis->setRange(0, 4);
    ui.plot->yAxis->setRange(-2.0, 0.5);

    ui.plot_2->xAxis->setRange(0, 4);
    ui.plot_2->yAxis->setRange(-20, 20);

    ui.plot_3->xAxis->setRange(0, 4);
    ui.plot_3->yAxis->setRange(-1, 1);

    ui.plot_4->xAxis->setRange(0, 4);
    ui.plot_4->yAxis->setRange(-0.25, 0.25);
}

void GUI::clearPlots()
{
    ui.plot->graph(0)->data()->clear();
    ui.plot->graph(1)->data()->clear();

    ui.plot_2->graph(0)->data()->clear();
    ui.plot_2->graph(1)->data()->clear();

    ui.plot_3->graph(0)->data()->clear();
    ui.plot_3->graph(1)->data()->clear();
    ui.plot_3->graph(2)->data()->clear();
    ui.plot_3->graph(3)->data()->clear();

    ui.plot_4->graph(0)->data()->clear();
    ui.plot_4->graph(1)->data()->clear();
    ui.plot_4->graph(2)->data()->clear();
    ui.plot_4->graph(3)->data()->clear();
}

void GUI::addPoints(plotVars vars)
{
	int span = 4;

	// Add data
    ui.plot->graph(0)->addData(vars.time, vars.x);
    ui.plot->graph(1)->addData(vars.time, vars.x_des);

    ui.plot_2->graph(0)->addData(vars.time, vars.u);
    ui.plot_2->graph(1)->addData(vars.time, vars.u_cmd);

    ui.plot_3->graph(0)->addData(vars.time, vars.quat[0]);
    ui.plot_3->graph(1)->addData(vars.time, vars.quat[1]);
    ui.plot_3->graph(2)->addData(vars.time, vars.quat[2]);
    ui.plot_3->graph(3)->addData(vars.time, vars.quat[3]);

    ui.plot_4->graph(0)->addData(vars.time, vars.emg[0]);
    ui.plot_4->graph(1)->addData(vars.time, vars.emg[1]);
    ui.plot_4->graph(2)->addData(vars.time, vars.emg[2]);
    ui.plot_4->graph(3)->addData(vars.time, vars.emg[3]);

	// Remove data
    ui.plot->graph(0)->removeDataBefore(vars.time - span);
    ui.plot->graph(1)->removeDataBefore(vars.time - span);

    ui.plot_2->graph(0)->removeDataBefore(vars.time - span);
    ui.plot_2->graph(1)->removeDataBefore(vars.time - span);

    ui.plot_3->graph(0)->removeDataBefore(vars.time - span);
    ui.plot_3->graph(1)->removeDataBefore(vars.time - span);
    ui.plot_3->graph(2)->removeDataBefore(vars.time - span);
    ui.plot_3->graph(3)->removeDataBefore(vars.time - span);

    ui.plot_4->graph(0)->removeDataBefore(vars.time - span);
    ui.plot_4->graph(1)->removeDataBefore(vars.time - span);
    ui.plot_4->graph(2)->removeDataBefore(vars.time - span);
    ui.plot_4->graph(3)->removeDataBefore(vars.time - span);

    ui.plot->xAxis->setRange(vars.time, span, Qt::AlignRight);
    ui.plot_2->xAxis->setRange(vars.time, span, Qt::AlignRight);
    ui.plot_3->xAxis->setRange(vars.time, span, Qt::AlignRight);
    ui.plot_4->xAxis->setRange(vars.time, span, Qt::AlignRight);

	plot();
}

void GUI::plot()
{
    ui.plot->replot();
    ui.plot_2->replot();
    ui.plot_3->replot();
    ui.plot_4->replot();
}

void GUI::on_checkBox_clicked() // Exo
{
    if(controlThread->test.exo){
        controlThread->test.exo = 0;
    }else{
        controlThread->test.exo = 1;
    }
}

void GUI::on_checkBox_2_clicked() // EMG
{
    if(controlThread->test.emg){
        controlThread->test.emg = 0;
    }else{
        controlThread->test.emg = 1;
    }
}
