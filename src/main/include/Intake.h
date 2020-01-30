#pragma once

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
    
    WPI_VictorSPX *intakeMotor;
};