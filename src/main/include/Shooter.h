#pragma once

#include <ctre/Phoenix.h>

#include "PID.h"
#include "Controls.h"

#define SHOOTER_MOTOR_1 5
#define SHOOTER_MOTOR_2 6
#define ADJUSTING_MOTOR 12

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

    WPI_VictorSPX *adjustingMotor;

    float motorValue1, motorValue2;
    float joyValue;

    Control *control;
    PID *pid;
};