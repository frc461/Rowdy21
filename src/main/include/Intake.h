#pragma once
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>

#include "Controls.h"

class Intake 
{
public:
    Intake(Control *control);
    ~Intake();

    void Periodic();

    void ToggleState();

    void Reset();

private:
    Control *control;
    frc::DoubleSolenoid *push;
    WPI_VictorSPX *roller;

    frc::DigitalInput *retractionLimit;

    double rollerSpeed;
    bool bIntake;
};