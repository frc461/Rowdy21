#pragma once
#include "Controls.h"
#include <ctre/Phoenix.h>

class Climber
{
public:
    Climber(Control *control);
    void Periodic();

private:
WPI_TalonSRX *lifter1, *lifter2;
Control *control;
};