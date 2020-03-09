#pragma once

#include "ThrustMasters.h"
#include "XboxMap.h"

#include <frc/Joystick.h>
#include <frc/Timer.h>

#define HALF_IN_TRENCH 0.205
#define DISCO 1//angle is shy of target 0.6 power
#define THIRD_PRESET 1
#define ON_INIT_LINE 1012

class Control
{
public:
    Control();

    class ButtonDebounce {
    public:
        ButtonDebounce();
        bool Get(bool input);
        double latest;
    private:
        int timeout;
    };

    bool ShooterLoadUp(); // right bumper
    bool ConveyForward(); // Left bumper
    bool ConveyReverse(); // X
    double ManualShooterAdjustment(); // right joysitkc
    bool PresetPosition1(); // Y
    bool PresetPosition2(); // B
    bool PresetPosition3(); // TODO button

    double ClimberUp(); // Thumbbutton left
    double ClimberDown(); // Thumbbutton left
    bool ClimberBrake();
    bool IntakeIn(); // Up D-Pad
    bool IntakeOut(); // Down D-Pad  
    bool JustIntakeMotor(); // TODO: JUST THE INTAKE MROORT AM  
    double IntakeControl(); // y Axix left ohystikv
    double WheelOfFortune(); // X-axis left joyist
    bool ToggleIntake();
    bool AutoSelect(); // left & right D=Pad
    bool ShooterReset();//start

    double leftJoystickX();
    double leftJoystickY();
    double rightJoystickX();
    double rightJoystickY();

    bool LimelightAiming();
    bool LimelightLightActivate();

    Control::ButtonDebounce *BToggleIntake;
    Control::ButtonDebounce *BPresetPos1, *BPresetPos2, *BPresetPos3;
    Control::ButtonDebounce *BClimberBrake;

private:
    frc::Joystick *leftJoystick;
    frc::Joystick *rightJoystick;
    frc::Joystick *xboxController;

};
