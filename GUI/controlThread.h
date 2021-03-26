#pragma once

#include "ui_GUI.h"
#include "motorThread.h"
#include "libgrampc.h"
#include "tmsicontroller.h"

using namespace std;

struct testParams {
    bool exo = 1; // Set 1 or 0 to turn on/off exoskeleton control
    bool emg = 1; // Set 1 or 0 to turn on/off emg recording
    double T = 4.0; // Set to limit trial time (s)
	int delay_time = 100; // Delay time before each test in ms 
};

struct plotVars {
	double time = 0,
        x = 0, x_des = 0,
        u = 0, u_cmd = 0,
        quat[4] = {},
        emg[4] = {};
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

    double imu_quat[4] = {};
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

    TMSiController *TMSi;

    double evec[4] = {};

    FILE *file_t, *file_emg,
        *file_x, *file_xdes,
        *file_u, *file_udes,
        *file_hebi_quat,
        *file_imu_quat,
        *file_nano;

	void open_files();
	void print2Files();
	void close_files();
signals:
	void GUIComms(QString);
};

void openFile(FILE **file, const char *name);
void printNumVector2File(FILE *file, const double *const val, const int size);
