#include "PID.h"

PID::PID(double kp, double ki, double kd, std::string name)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    error = errorSum = lastError = 0;

    pidName = name;

    frc::SmartDashboard::PutNumber(pidName + " kp", kp);
    frc::SmartDashboard::PutNumber(pidName + " ki", ki);
    frc::SmartDashboard::PutNumber(pidName + " kd", kd);
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
    kp = frc::SmartDashboard::GetNumber(pidName + " kp", 0);
    ki = frc::SmartDashboard::GetNumber(pidName + " ki", 0);
    kd = frc::SmartDashboard::GetNumber(pidName + " kd", 0);
}