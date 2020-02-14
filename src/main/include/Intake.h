#pragma once
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include "Controls.h"

#include <ctre/Phoenix.h>

class Intake 
{
public:
    Intake(Control *control);
    ~Intake();

    void Periodic();

    void ToggleState();

private:
    Control *control;
    frc::Solenoid *push;
    WPI_VictorSPX *roller;

    frc::DigitalInput *retractionLimit;

    bool switchState, prevSwitchState;
    int timeOut;
    double rollerSpeed;
};