#pragma once

#include <ctre/Phoenix.h>

#include "PID.h"
#include "Controls.h"

#include <frc/DigitalInput.h>
#include <frc/Encoder.h>
#include <frc/Timer.h>
#include <frc/DigitalOutput.h>
#include <frc/Relay.h>

#define SHOOTER_MOTOR_1 5
#define SHOOTER_MOTOR_2 6
#define ADJUSTING_MOTOR 12

#define PITCH_SPEED_CONTROL 0.5

#define LIMIT_SW 6

class Shooter
{
public:
    Shooter(Control *control);

    void Periodic();

    void RunShooterAt(double LMotorSpeed, double RMotorSpeed);

    void VerticalAdjust();

    void SetAdj(double speed);

    bool GetLimit();

    void ZeroAlign();

    int GetAdj();

    void Rev(double speed);

    void Angle(double angle);
private:
    double minShootRPM;
    WPI_TalonFX *shooterMotor1, *shooterMotor2;

    WPI_VictorSPX *adjustingMotor;

    float motorValue1, motorValue2;
    float joyValue;

    Control *control;

    frc::DigitalInput *limit;

    frc::Encoder *encoder;

    PID *anglePID;

    int shooterPos;

    frc::Relay *flashlight;

    bool shooterSpeed;

    int shooterPower;

    std::string _sb;
    int _loops;

};