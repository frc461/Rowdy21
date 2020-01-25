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

    return (kp * error + ki * errorSum + kd * errorRate);
}
