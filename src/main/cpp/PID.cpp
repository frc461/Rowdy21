#include "PID.h"

PID::PID(double kp, double ki, double kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    error = errorSum = lastError = 0;
}

PID::~PID() {}

double PID::OutputPID(double value, double ideal)
{
    error = ideal - value;
    errorSum += error;

    double errorRate = (lastError - error);

    lastError = error;

    //frc::SmartDashboard::PutNumber("pid", kp * error + ki * errorSum + kd * errorRate);

    return (kp * error + ki * errorSum + kd * errorRate);
}

void PID::getPIDvalues() {
    kp = frc::SmartDashboard::GetNumber("kp", 0);
    ki = frc::SmartDashboard::GetNumber("ki", 0);
    kd = frc::SmartDashboard::GetNumber("kd", 0);

}