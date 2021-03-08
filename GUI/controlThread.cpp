#include "controlThread.h"

ControlThread::ControlThread(QObject *parent)
	:QThread(parent)
{
	if (test.Device) {
		motorThread = new MotorThread(this);
	}
}

void ControlThread::run()
{
	control_init();

	if (test.Device) {
		motorThread->start(QThread::LowPriority);
		while (!motorThread->motor_initialised);
	}
	mpc_initialised = true;

	Sleep(100);

	last_time = clock();
	start_time = last_time;
	while (!Stop && t < test.T - 0.002) {
		control_loop();
		if (iMPC % 10 == 0)
		{
			mutex.lock();
			vars.time = t;
			vars.u = motorTorque;
			vars.u_cmd = demandedTorque;
			mutex.unlock();
		}
	}
	control_stop();
	terminate();
}

void ControlThread::control_init() {
	open_files();
	GUIComms("Init Complete\n");
}

void ControlThread::control_stop() {
	end_time = clock();
	double duration = (double)(end_time - start_time);
	Stop = 1;
	if (test.Device) {
		motorThread->mpc_complete = 1;
	}
	close_files();
	GUIComms("Real Duration, ms :" + QString::number(duration, 'f', 0) + "\n");
	if(test.Device)
		GUIComms("Command Cycles  :" + QString::number(motorThread->motor_comms_count, 'f', 0) + "\n");
	GUIComms("\n");
	GUIComms("DONE");
}

void ControlThread::control_loop() {
	if (!loopSlept) {
		this->usleep(800);
		loopSlept = true;
	}
	this_time = clock();
	time_counter += (double)(this_time - last_time);
	last_time = this_time;
	if (time_counter > (double)(0.002 * CLOCKS_PER_SEC)) // 1000 cps
	{
		referencePosition = 0;// (cos((0.25 * 2 * M_PI * (t - t_halt)) - M_PI)) / 2 + 0.7; // freq
		referenceVelocity = (referencePosition - xdes_previous) / 0.002;
		xdes_previous = referencePosition;

		if (test.Device) {
			demandedTorque = 0;
			motorThread->demandedTorque = demandedTorque;
			motorTorque = motorThread->currentTorque;
			currentPosition = motorThread->currentPosition - 0.125 * M_PI - 0.5 * M_PI;

			if (iMPC == 0) {
				motorThread->previousPosition = currentPosition; // takes initial position into account
			}
			currentVelocity = motorThread->currentVelocity;
			currentVelocity = alpha * currentVelocity + (1 - alpha) * previousVelocity;		// implement SMA for velocity until full state estimator is developed
			previousVelocity = currentVelocity;

			hebi_quat[0] = motorThread->hebi_quat[0];
			hebi_quat[1] = motorThread->hebi_quat[1];
			hebi_quat[2] = motorThread->hebi_quat[2];
			hebi_quat[3] = motorThread->hebi_quat[3];

			voltage = motorThread->voltage;
			if (voltage < 30) {
				GUIComms("Power supply voltage too low.");
				Stop = 1;
			}
		}
		print2Files();
		t = t + 0.002;
		iMPC++;
		loopSlept = false;
		time_counter -= (double)(0.002 * CLOCKS_PER_SEC);
	}
}

void ControlThread::open_files() {
	openFile(&file_x, "../res/xvec.txt");
	openFile(&file_xdes, "../res/xdesvec.txt");
	openFile(&file_u, "../res/uvec.txt");
	openFile(&file_udes, "../res/udes.txt");
	openFile(&file_t, "../res/tvec.txt");
	openFile(&file_quat, "../res/quat.txt");
	openFile(&file_quat_3, "../res/quat_3.txt");
	openFile(&file_quat_4, "../res/quat_4.txt");
	openFile(&file_nano, "../res/nano.txt");
	openFile(&file_hebi_quat, "../res/hebi_quat.txt");
}

void ControlThread::print2Files() {
	printNumVector2File(file_x, &currentPosition, 1);
	printNumVector2File(file_xdes, &referencePosition, 1);
	printNumVector2File(file_u, &motorTorque, 1);
	printNumVector2File(file_udes, &demandedTorque, 1);
	printNumVector2File(file_t, &t, 1);
	printNumVector2File(file_quat, quat, 4);
	printNumVector2File(file_quat_3, quat_3, 4);
	printNumVector2File(file_quat_4, quat_4, 4);
	printNumVector2File(file_nano, nano, 4);
	printNumVector2File(file_hebi_quat, hebi_quat, 4);
}

void ControlThread::close_files()
{
	fclose(file_x);
	fclose(file_xdes);
	fclose(file_u);
	fclose(file_udes);
	fclose(file_t);
	fclose(file_quat);
	fclose(file_quat_3);
	fclose(file_quat_4);
	fclose(file_nano),
	fclose(file_hebi_quat);
}

void openFile(FILE **file, const char *name) {
	*file = fopen(name, "w");
}

void printNumVector2File(FILE *file, const double * val, const int size) {
	int i;
	for (i = 0; i < size - 1; i++) {
		fprintf(file, "%.5f,", val[i]);
	}
	fprintf(file, "%.5f\n", val[size - 1]);
}