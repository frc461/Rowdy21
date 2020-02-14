#pragma once

#include "ThrustMasters.h"
#include "XboxMap.h"

#include <frc/Joystick.h>
#include <frc/Timer.h>

class Control
{
public:
    Control();

    class ButtonDebounce {
        public:
            ButtonDebounce();
            bool Get(bool input);
        private:
            int timeout;
            double latest;
    };
    
    bool ShooterLoadUp(); // right bumper
    bool ConveyForward(); // Left bumper
    bool ConveyReverse(); // X
    double ManualShooterAdjustment(); // right joysitkc
    bool PresetPosition1(); // Y
    bool PresetPosition2(); // B
    double ClimberUp(); // Left trigger
    double ClimberDown(); // Right Trigger
    bool IntakeIn(); // Up D-Pad
    bool IntakeOut(); // Down D-Pad
    bool JustIntakeMotor(); // TODO: JUST THE INTAKE MROORT AM  
    double IntakeControl(); // y Axix left ohystikv
    double WheelOfFortune(); // X-axis left joyist
    bool ToggleIntake();
    bool AutoSelect(); // left & right D=Pad

    double leftJoystickX();
    double leftJoystickY();
    double rightJoystickX();
    double rightJoystickY();

    bool LimelightAiming();
    bool LimelightLightActivate();

    Control::ButtonDebounce *BToggleIntake;

private:
    frc::Joystick *leftJoystick;
    frc::Joystick *rightJoystick;
    frc::Joystick *xboxController;
};
