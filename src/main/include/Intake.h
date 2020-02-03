#pragma once
#include <frc/DoubleSolenoid.h>
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
    frc::DoubleSolenoid *intakePush;
    WPI_VictorSPX *intakeMotor;
    WPI_TalonSRX *conveyor, *hopper;

    bool switchState, prevSwitchState;
};