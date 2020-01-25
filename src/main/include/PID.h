#pragma once

#include <frc/SmartDashboard/SmartDashboard.h>

class PID
{
public:
    PID(double kp, double ki, double kd);
    ~PID();

    double kp, ki, kd;

    double OutputPID(double val, double ideal);

    void getPIDvalues();

private:
    double error, errorSum, lastError;
};