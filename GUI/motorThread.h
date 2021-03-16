#pragma once

#include <QThread>
#include <QMutex>

#include "hebi.h"
#include "lookup.hpp"
#include "group_command.hpp"
#include "group_feedback.hpp"
#include "log_file.hpp"

using namespace hebi;

class MotorThread : public QThread
{
	Q_OBJECT

public:
	MotorThread(QObject *parent);
	~MotorThread();
	void run();

	bool motor_initialised = false;
    bool control_complete = false;
	double demandedTorque = 0;
	double currentTorque = 0;
	double motor_comms_count = 0;
	double currentPosition = 0.2 + 0.625 * M_PI;
	double previousPosition = 0;
	double currentVelocity = 0;
	double hebi_quat[4] = {};
	float voltage = 0;

private:
	Lookup lookup;
	std::shared_ptr<hebi::Group> group;
	QMutex mutex;
};
