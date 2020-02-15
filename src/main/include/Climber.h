#pragma once

#include "Controls.h"
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <frc/Solenoid.h>
class Climber {
public:
    Climber(Control *control);
    void Periodic();

private:
    WPI_TalonSRX *lifter1, *lifter2;
    Control *control;
    frc::DigitalInput *limitTop;
    frc::DigitalInput *limitDown;
    frc::Solenoid *brake;
};