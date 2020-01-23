#pragma once

class PID
{
public:
    PID(double kp, double ki, double kd);
    ~PID();

    double kp, ki, kd;

    double OutputPID(double val, double ideal);

private:
    double error, errorSum, lastError;
};