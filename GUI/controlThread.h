#pragma once

#include "ui_GUI.h"
#include "motorThread.h"
#include "tmsicontroller.h"

using namespace std;

struct testParams {
    bool exo = 1; // Set 1 or 0 to turn on/off exoskeleton control
    bool emg = 1; // Set 1 or 0 to turn on/off emg recording
    double T = 40.0; // Set to limit trial time (s)
};

struct plotVars {
	double time = 0,
		u = 0, u_cmd = 0;
};
	
class ControlThread : public QThread
{
	Q_OBJECT

public:
	ControlThread(QObject *parent);

	void run();
	bool Stop = false;
    bool control_initialised = false;
    int i_control = 0;
	float voltage = 0;

	plotVars vars;
	testParams test;

	QMutex mutex;

	MotorThread *motorThread;

	void control_init();
	void control_loop();
	void control_stop();

private:
	bool loopSlept = false;
	double referencePosition = 0, referenceVelocity = 0;
	double currentPosition = 0;
	double currentVelocity = 0, previousVelocity = 0, alpha = 0.01, xdes_previous = 0.2;
	double motorTorque = 0, demandedTorque = 0;
	double hebi_quat[4] = {};

	double t = 0.0, t_halt = 0.0;
	double time_counter = 0.0;
	clock_t this_time, last_time, start_time, end_time;

    TMSiController *TMSi;
    QVector<double> e1vec = { 0 }, e2vec = { 0 }, e3vec = { 0 }, e4vec = { 0 };

    double evec[4] = {};

    FILE *file_x, *file_xdes,
        *file_u, *file_udes,
        *file_t, *file_emg,
        *file_hebi_quat;

	void open_files();
	void print2Files();
	void close_files();
signals:
	void GUIComms(QString);
};

void openFile(FILE **file, const char *name);
void printNumVector2File(FILE *file, const double *const val, const int size);
