#pragma once
#include <frc/Solenoid.h>
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

    void AutoInit();
    void IntakeIn();
    void AutoRun();

    void Reset();

private:
    Control *control;
    frc::Solenoid *push;
    WPI_VictorSPX *roller;

    frc::DigitalInput *retractionLimit;

    double rollerSpeed;
    bool bIntake;
};