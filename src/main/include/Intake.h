#pragma once
#include <frc/Solenoid.h>
#include "Controls.h"

#include <ctre/Phoenix.h>

class Intake 
{
public:
    Intake();
    ~Intake();

    void Periodic();

private:
    Control *control;
    frc::Solenoid *intakePush;
    WPI_VictorSPX *intakeMotor;
    WPI_TalonSRX *conveyor, *hopper;
};