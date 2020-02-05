#pragma once

#include <ctre/Phoenix.h>

#include "PID.h"
#include "Controls.h"

#define SHOOTER_MOTOR_1 9
#define SHOOTER_MOTOR_2 1
#define ADJUSTING_MOTOR 2

#define PITCH_SPEED_CONTROL 0.5

class Shooter
{
public:
    Shooter(Control *control);

    void Periodic();

    void RunShooterAt(double LMotorSpeed, double RMotorSpeed);

    void VerticalAdjust();

private:
    WPI_TalonFX *shooterMotor1, *shooterMotor2;

    WPI_TalonFX *adjustingMotor;

    float motorValue1, motorValue2;
    float joyValue;

    Control *control;
    PID *pid;
};