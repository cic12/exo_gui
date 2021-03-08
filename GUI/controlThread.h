#pragma once

#include "ui_GUI.h"
#include "motorThread.h"

using namespace std;

struct testParams {
	bool Device = 0;
	double T = 600.0;
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
	bool mpc_initialised = false;
	int iMPC = 0;

	double quat[4] = {};
	double quat_3[4] = {};
	double quat_4[4] = {};
	double nano[4] = {};
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

	FILE *file_x, *file_xdes,
		*file_u, *file_udes, *file_t,
		*file_quat, * file_quat_3, * file_quat_4,
		*file_nano, *file_hebi_quat;

	void open_files();
	void print2Files();
	void close_files();
signals:
	void GUIComms(QString);
};

void openFile(FILE **file, const char *name);
void printNumVector2File(FILE *file, const double *const val, const int size);