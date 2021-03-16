#include "motorThread.h"

MotorThread::MotorThread(QObject *parent)
	: QThread(parent)
{
}

MotorThread::~MotorThread()
{

}

void MotorThread::run() {
	group = lookup.getGroupFromNames({ "X8-9" }, { "X-80768" });
	if (!group) {
		throw "Group not found!Check that the family and name of a module on the network matches what is given in the source file.";
		terminate();
	}
	GroupCommand group_command(group->size());
	Eigen::VectorXd efforts(1);
	GroupFeedback group_feedback(group->size());
	Feedback feedback();
	group->setFeedbackFrequencyHz(500);
    group->startLog("../../results/logs");

	motor_initialised = true;
	
    while (!control_complete) {
		if (!group->getNextFeedback(group_feedback)) {
			continue;
		}
		mutex.lock();
		efforts[0] = -demandedTorque;
		group_command.setEffort(efforts);
		group->sendCommand(group_command);
		auto pos = group_feedback.getPosition();
		auto vel = group_feedback.getVelocity();
		auto effort = group_feedback.getEffort();
		auto accel = group_feedback.getAccelerometer();
		auto volt = group_feedback.getVoltage();
		auto quat = group_feedback[0].imu().orientation().get();
		currentPosition = -pos[0];
		currentVelocity = -vel[0];
		currentTorque = -effort[0];
		hebi_quat[0] = quat.getW();
		hebi_quat[1] = quat.getX();
		hebi_quat[2] = quat.getY();
		hebi_quat[3] = quat.getZ();
		voltage = volt[0];
		motor_comms_count++;
		mutex.unlock();
	}
	auto log_file = group->stopLog();
	group->~Group();
}	
