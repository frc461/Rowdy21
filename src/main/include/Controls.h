#pragma once

#include "ThrustMasters.h"
#include "CanStuff.h"

#include <frc/Joystick.h>

class Control
{
public:
    Control();

    double leftJoystickX();
    double leftJoystickY();
    double rightJoystickX();
    double rightJoystickY();

    bool IntakeIn();
    bool IntakeOut();
    bool IntakeForward();

    bool LimelightAiming();
    bool LimelightLightActivate();

private:
    frc::Joystick *leftJoystick;
    frc::Joystick *rightJoystick;
};