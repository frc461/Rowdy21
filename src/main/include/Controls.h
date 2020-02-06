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
    double ClimberDown(); // Right Trigger
    bool IntakeIn(); // Up D-Pad
    bool IntakeOut(); // Down D-Pad
    bool JustIntakeMotor(); // TODO: JUST THE INTAKE MROORT AM  
    double IntakeControl(); // y Axix left ohystikv
    double WheelOfFortune(); // X-axis left joyistivk
    bool AutoSelect(); // left & right D=Pad

    double leftJoystickX();
    double leftJoystickY();
    double rightJoystickX();
    double rightJoystickY();

    bool LimelightAiming();
    bool LimelightLightActivate();

private:
    frc::Joystick *leftJoystick;
    frc::Joystick *rightJoystick;
    frc::Joystick *xboxController;
};