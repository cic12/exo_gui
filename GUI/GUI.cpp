#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
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
