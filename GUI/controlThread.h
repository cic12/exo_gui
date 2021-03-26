#pragma once

#include "ui_GUI.h"
#include "motorThread.h"
#include "grampc.hpp"
#include "tmsicontroller.h"

#define NX    	4
#define NU  	1
#define NH      4

using namespace std;

struct testParams {
    bool exo = 0; // Set 1 or 0 to turn on/off exoskeleton control
    bool emg = 0; // Set 1 or 0 to turn on/off emg recording
    bool mpc = 1;
    int human = 0;
    double T = 4.0; // Set to limit trial time (s)
	int delay_time = 100; // Delay time before each test in ms 
};

// MPC
struct modelParams {
    // None, Chris ID, Chris, Annika, Felix
    double J_h[5] =     { 0, 0.4351 , 0.2383 , 0.1927 , 0.3060  };
    double B_h[5] =     { 0, 0.1676 , 0.1676 , 2      , 2       };
    double A_h[5] =     { 0, 0      , 0      , 0      , 0       };
    double tau_g_h[5] = { 0, 14.256 , 9.4162 , 7.5008 , 10.5946 };
    double J_e = 0.0377, J = 0;
    double B_e = 0.0207, B = 0;
    double A_e = 0.0000, A = 0;
    double tau_g_e = 1.7536, tau_g = 0;
};

// MPC
struct mpcParams {
    double JScale = 10000;
    double w_theta = 50000/JScale, w_tau = 100/JScale;
    double x1min = 0, x1max = 1.4, x2min = -2, x2max = 2;
    double pSys[10] = { 0, 0, 0, 0, w_theta, w_tau, x1min, x1max, x2min, x2max };

    double rwsReferenceIntegration[2 * NX] = {};
    const double x0[NX] = { 0.2 , 0.0 , 0.0 , 1.0 };
    double xdes[NX] = { 0.2 , 0.0 , 0.0 , 1.0 };
    double xdes_shifted[NX] = { 0.0, 0.0, 0.0, 1.0 };
    const double u0[NU] = { 0.0 }, udes[NU] = { 0.0 }, umin[NU] = { -20.0 }, umax[NU] = { 20.0 }; // set in inequality constraints
    const double Thor = 0.2, dt = 0.002;
    const int Nhor = 20, MaxGradIter = 4, MaxMultIter = 6;
    const char * IntegralCost = "on", * TerminalCost = "off";
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

    // MPC
    void mpcInit();
    void modelParamSet();

	bool Stop = false;
    bool control_initialised = false;
    int i_control = 0;

    double imu_quat[4] = {};
    double nano[4] = {};
	float voltage = 0;

	plotVars vars;
	testParams test;

    // MPC
    mpcParams mpc;
    modelParams model;

	QMutex mutex;

	MotorThread *motorThread;

    // MPC
    typeGRAMPC* grampc_;

	void control_init();
	void control_loop();
	void control_stop();
    double controlInput();
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
