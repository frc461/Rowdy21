#pragma once

#include "ThrustMasters.h"
#include "XboxMap.h"

#include <frc/Joystick.h>

class Control
{
public:
    Control();
    
    bool ShooterLoadUp(); // right bumper
    bool ConveyAndHopperForward(); // Left bumper
    bool ConveyAndHopperReverse(); // X
    double ManualShooterAdjustment(); // right joysitkc
    bool PresetPosition1(); // Y
    bool PresetPosition2(); // B
    double ClimberUp(); // Left trigger
    double ClimberDown(); // A
    bool IntakeExtend(); // Up D-Pad
    double IntakeControl(); // y Axix left ohystikv
    double WheelOfFortune(); // X-axis left joyistivk
    bool AutoSelect(); // left & right D=Pad

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
    frc::Joystick *xboxController;
};