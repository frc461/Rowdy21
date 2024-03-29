#pragma once

#include "Controls.h"
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/Solenoid.h>
#include <frc/SmartDashboard/SmartDashboard.h>
class Climber {
public:
    Climber(Control *control);
    void Periodic();

    void ClimberBrakeOff();
    void ClimberBrakeOn();

    void ToggleBrake();

private:
    WPI_TalonSRX *lifter1, *lifter2;
    Control *control;
    frc::DigitalInput *limitTop;
    frc::DigitalInput *limitDown;
    frc::Solenoid *brake;

    double speed;

    bool enter, hold, up, down;

    int counter;
};