#include "controlThread.h"

ControlThread::ControlThread(QObject *parent)
	:QThread(parent)
{
    if (test.exo) {
		motorThread = new MotorThread(this);
	}
}

void ControlThread::run()
{
	control_init();

    if (test.emg == 1) { // TMSi
        TMSi = new TMSiController();
        TMSi->daq->daq_aiFile.open("../../results/aivec.txt");
        TMSi->startStream();
        TMSi->setRefCalculation(1);
    }

    if (test.exo) {
		motorThread->start(QThread::LowPriority);
		while (!motorThread->motor_initialised);
	}
    control_initialised = true;

    Sleep(100); // delay in ms

	last_time = clock();
	start_time = last_time;
	while (!Stop && t < test.T - 0.002) {
		control_loop();
        if (i_control % 10 == 0)
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

    if (test.emg == 1) { // TMSi
            TMSi->endStream();
            TMSi->reset();
            TMSi->daq->daq_aiFile.close();
    }

	Stop = 1;
    if (test.exo) {
        motorThread->control_complete = 1;
	}
    close_files();
	GUIComms("Real Duration, ms :" + QString::number(duration, 'f', 0) + "\n");
    if(test.exo)
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
        referencePosition = 0;
		referenceVelocity = (referencePosition - xdes_previous) / 0.002;
		xdes_previous = referencePosition;

        if (test.emg) { // TMSi
                mutex.lock();
                evec[0] = TMSi->daq->mgvec[0];
                evec[1] = TMSi->daq->mgvec[1];
                evec[2] = TMSi->daq->mgvec[2];
                evec[3] = TMSi->daq->mgvec[3];
                mutex.unlock();
        }

        if (test.exo) {

			demandedTorque = 0;

			motorThread->demandedTorque = demandedTorque;
			motorTorque = motorThread->currentTorque;
            currentPosition = motorThread->currentPosition;

            if (i_control == 0) {
				motorThread->previousPosition = currentPosition; // takes initial position into account
			}
			currentVelocity = motorThread->currentVelocity;
            currentVelocity = alpha * currentVelocity + (1 - alpha) * previousVelocity;
			previousVelocity = currentVelocity;

			hebi_quat[0] = motorThread->hebi_quat[0];
			hebi_quat[1] = motorThread->hebi_quat[1];
			hebi_quat[2] = motorThread->hebi_quat[2];
			hebi_quat[3] = motorThread->hebi_quat[3];

			voltage = motorThread->voltage;
			if (voltage < 30) {
                GUIComms("Power supply voltage too low\n\n");
				Stop = 1;
			}
		}
        print2Files();
		t = t + 0.002;
        i_control++;
		loopSlept = false;
		time_counter -= (double)(0.002 * CLOCKS_PER_SEC);
	}
}

void ControlThread::open_files() {
    errno_t err;
    err = fopen_s(&file_x, "../../results/xvec.txt", "w");
    err = fopen_s(&file_xdes, "../../results/xdesvec.txt", "w");
    err = fopen_s(&file_u, "../../results/uvec.txt", "w");
    err = fopen_s(&file_udes, "../../results/udes.txt", "w");
    err = fopen_s(&file_t, "../../results/tvec.txt", "w");
    err = fopen_s(&file_emg, "../../results/emg.txt", "w");
    err = fopen_s(&file_hebi_quat, "../../results/hebi_quat.txt", "w");
}

void ControlThread::print2Files() {
    printNumVector2File(file_x, &currentPosition, 1);
    printNumVector2File(file_xdes, &referencePosition, 1);
    printNumVector2File(file_u, &motorTorque, 1);
    printNumVector2File(file_udes, &demandedTorque, 1);
    printNumVector2File(file_t, &t, 1);
    printNumVector2File(file_emg, evec, 4);
    printNumVector2File(file_hebi_quat, hebi_quat, 4);
}

void ControlThread::close_files()
{
    fclose(file_x);
    fclose(file_xdes);
    fclose(file_u);
    fclose(file_udes);
    fclose(file_t);
    fclose(file_emg);
    fclose(file_hebi_quat);
}

void printNumVector2File(FILE *file, const double * val, const int size) {
	int i;
	for (i = 0; i < size - 1; i++) {
		fprintf(file, "%.5f,", val[i]);
	}
	fprintf(file, "%.5f\n", val[size - 1]);
}
