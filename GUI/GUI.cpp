#include "GUI.h"

GUI::GUI(QWidget *parent)
	: QMainWindow(parent),
	_state(ximu::SerialPort::Message::OKE),
	_state_3(ximu::SerialPort::Message::OKE),
	_state_4(ximu::SerialPort::Message::OKE)
{
	ui.setupUi(this);

	gui_reset = true;
	gui_done = false;

	initPlots();

	controlThread = new ControlThread(this);
	timer = new QTimer(this);
	timer->setTimerType(Qt::PreciseTimer);

	connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::onTimeout)); // GUI update
	connect(controlThread, SIGNAL(GUIComms(QString)), this, SLOT(onGUIComms(QString))); // GUI print function

	ui.comboBoxBaudRates->addItem("115200", QVariant(115200));
	ui.comboBoxBaudRates_2->addItem("115200", QVariant(115200));
	ui.comboBoxBaudRates_3->addItem("115200", QVariant(115200));
	ui.comboBoxBaudRates_4->addItem("115200", QVariant(115200));

	for (auto& port : QSerialPortInfo::availablePorts()) {
		ui.comboBoxPortNames->addItem(port.systemLocation());
		ui.comboBoxPortNames_2->addItem(port.systemLocation());
		ui.comboBoxPortNames_3->addItem(port.systemLocation());
		ui.comboBoxPortNames_4->addItem(port.systemLocation());
	}
	
	// QSerialPort
	_sp_2 = new QSerialPort(this);
	connect(_sp_2, &QSerialPort::readyRead, this, &GUI::on_data_received);

	// gui::button open/close
	connect(ui.pushButtonOnOff, &QPushButton::clicked, this, &GUI::on_openClose_triggered);
	connect(ui.pushButtonOnOff_2, &QPushButton::clicked, this, &GUI::on_openClose_triggered_2);
	connect(ui.pushButtonOnOff_3, &QPushButton::clicked, this, &GUI::on_openClose_triggered_3);
	connect(ui.pushButtonOnOff_4, &QPushButton::clicked, this, &GUI::on_openClose_triggered_4);
	
	// serialport::quaternion
	connect(&_sp, &ximu::SerialPort::quaternion, this, &GUI::on_quaternion_received);
	connect(&_sp_3, &ximu::SerialPort::quaternion, this, &GUI::on_quaternion_received_3);
	connect(&_sp_4, &ximu::SerialPort::quaternion, this, &GUI::on_quaternion_received_4);
	
	// serialport::messages
	connect(&_sp, &ximu::SerialPort::messages, this, &GUI::on_message_received);
	connect(&_sp_3, &ximu::SerialPort::messages, this, &GUI::on_message_received_3);
	connect(&_sp_4, &ximu::SerialPort::messages, this, &GUI::on_message_received_4);
	
	// text changed
	connect(ui.textArea, &QPlainTextEdit::textChanged, this, &GUI::on_text_changed);
	connect(ui.textArea_2, &QPlainTextEdit::textChanged, this, &GUI::on_text_changed_2);
	connect(ui.textArea_3, &QPlainTextEdit::textChanged, this, &GUI::on_text_changed_3);
	connect(ui.textArea_4, &QPlainTextEdit::textChanged, this, &GUI::on_text_changed_4);
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
	ui.label_voltage->setText("Voltage: " + QString::number(controlThread->voltage));
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
//	controlThread->quat[0] = q.w();
//	controlThread->quat[1] = q.x();
//	controlThread->quat[2] = q.y();
//	controlThread->quat[3] = q.z();
}

void GUI::on_text_changed() {
	if (ui.textArea->document()->lineCount() > 5)
		ui.textArea->clear();
}

void GUI::on_openClose_triggered_3()
{
	switch (_state_3)
	{
	case ximu::SerialPort::Message::OKE:
	case ximu::SerialPort::Message::CLOSED:
	case ximu::SerialPort::Message::COULD_NOT_OPEN:
	{
		_sp_3.open(
			ui.comboBoxPortNames_3->currentText().toStdString(),
			ui.comboBoxBaudRates_3->currentData().toInt()
		);
		break;
	}
	case ximu::SerialPort::OPEN:
	{
		_sp_3.close();
	}
	}
}

void GUI::on_message_received_3(ximu::SerialPort::Message m)
{
	_state_3 = m;
	switch (_state_3)
	{
	case ximu::SerialPort::Message::OPEN:
		ui.comboBoxPortNames_3->setEnabled(false);
		ui.comboBoxBaudRates_3->setEnabled(false);
		ui.pushButtonOnOff_3->setText(tr("close"));
		break;

	case ximu::SerialPort::Message::CLOSED:
		ui.comboBoxPortNames_3->setEnabled(true);
		ui.comboBoxBaudRates_3->setEnabled(true);
		ui.pushButtonOnOff_3->setText(tr("open"));
		break;

	case ximu::SerialPort::Message::COULD_NOT_OPEN:
		ui.textArea_3->appendPlainText(tr("[ERR] Could not open port"));
	}
}

void GUI::on_quaternion_received_3(const ximu::QuaternionData& q)
{
	std::stringstream ss;
	ss << "Quaternion (" << q.w() << "," << q.x() << "," << q.y() << "," << q.z() << ")";
	ui.textArea_3->appendPlainText(QString::fromStdString(ss.str()));
//	controlThread->quat_3[0] = q.w();
//	controlThread->quat_3[1] = q.x();
//	controlThread->quat_3[2] = q.y();
//	controlThread->quat_3[3] = q.z();
}

void GUI::on_text_changed_3()
{
	if (ui.textArea_3->document()->lineCount() > 5)
		ui.textArea_3->clear();
}

void GUI::on_openClose_triggered_4()
{
	switch (_state_4)
	{
	case ximu::SerialPort::Message::OKE:
	case ximu::SerialPort::Message::CLOSED:
	case ximu::SerialPort::Message::COULD_NOT_OPEN:
	{
		_sp_4.open(
			ui.comboBoxPortNames_4->currentText().toStdString(),
			ui.comboBoxBaudRates_4->currentData().toInt()
		);
		break;
	}
	case ximu::SerialPort::OPEN:
	{
		_sp_4.close();
	}
	}
}

void GUI::on_message_received_4(ximu::SerialPort::Message m)
{
	_state_4 = m;
	switch (_state_4)
	{
	case ximu::SerialPort::Message::OPEN:
		ui.comboBoxPortNames_4->setEnabled(false);
		ui.comboBoxBaudRates_4->setEnabled(false);
		ui.pushButtonOnOff_4->setText(tr("close"));
		break;

	case ximu::SerialPort::Message::CLOSED:
		ui.comboBoxPortNames_4->setEnabled(true);
		ui.comboBoxBaudRates_4->setEnabled(true);
		ui.pushButtonOnOff_4->setText(tr("open"));
		break;

	case ximu::SerialPort::Message::COULD_NOT_OPEN:
		ui.textArea_4->appendPlainText(tr("[ERR] Could not open port"));
	}
}

void GUI::on_quaternion_received_4(const ximu::QuaternionData& q)
{
	std::stringstream ss;
	ss << "Quaternion (" << q.w() << "," << q.x() << "," << q.y() << "," << q.z() << ")";
	ui.textArea_4->appendPlainText(QString::fromStdString(ss.str()));
//	controlThread->quat_4[0] = q.w();
//	controlThread->quat_4[1] = q.x();
//	controlThread->quat_4[2] = q.y();
//	controlThread->quat_4[3] = q.z();
}

void GUI::on_text_changed_4()
{
	if (ui.textArea_4->document()->lineCount() > 5)
		ui.textArea_4->clear();
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
//	controlThread->nano[0] = data[0].toDouble();
//	controlThread->nano[1] = data[1].toDouble();
//	controlThread->nano[2] = data[2].toDouble();
//	controlThread->nano[3] = data[3].toDouble();
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

	// add plots
	ui.plot->addGraph();
	ui.plot->graph(0)->setPen(QPen(Qt::blue));
	ui.plot->addGraph();
	ui.plot->graph(1)->setPen(QPen(Qt::red));

	// axes settings
	ui.plot->xAxis->setAutoTickStep(false);
	ui.plot->xAxis->setTickStep(1);
	ui.plot->yAxis->setAutoTickStep(false);
	ui.plot->yAxis->setTickStep(0.2);

	ui.plot->xAxis->setRange(0, 4);
	ui.plot->yAxis->setRange(-0.2, 0.2);
}

void GUI::clearPlots()
{
	ui.plot->graph(0)->data()->clear();
	ui.plot->graph(1)->data()->clear();
}

void GUI::addPoints(plotVars vars)
{
	int span = 4;

	// Add data
	ui.plot->graph(0)->addData(vars.time, vars.u);
	ui.plot->graph(1)->addData(vars.time, vars.u_cmd);

	// Remove data
	ui.plot->graph(0)->removeDataBefore(vars.time - span);
	ui.plot->graph(1)->removeDataBefore(vars.time - span);

	ui.plot->xAxis->setRange(vars.time, span, Qt::AlignRight);

	plot();
}

void GUI::plot()
{
	ui.plot->replot();
}
