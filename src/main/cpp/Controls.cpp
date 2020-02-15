#include "Controls.h"

Control::Control() {
    leftJoystick = new frc::Joystick(2);
    rightJoystick = new frc::Joystick(3);
    xboxController = new frc::Joystick(1);

    BToggleIntake = new Control::ButtonDebounce();
    BPresetPos1 = new Control::ButtonDebounce();
    BPresetPos2 = new Control::ButtonDebounce();
}
double Control::leftJoystickX() { return leftJoystick->GetRawAxis(xAxisJS); }
double Control::leftJoystickY() { return leftJoystick->GetRawAxis(yAxisJS); }
double Control::rightJoystickX() { return rightJoystick->GetRawAxis(xAxisJS); }
double Control::rightJoystickY() { return rightJoystick->GetRawAxis(yAxisJS); }

bool Control::LimelightAiming() { return rightJoystick->GetRawButton(8); }
bool Control::LimelightLightActivate() { return rightJoystick->GetRawButton(9); }

bool Control::ShooterLoadUp() { return (xboxController->GetRawButton(XboxButtonLeftBumper)); } // left bumper
bool Control::ConveyForward() { return (xboxController->GetRawButton(XboxButtonLeftBumper)); } // Left bumper
bool Control::ConveyReverse() { return (xboxController->GetRawButton(XboxButtonX)); } // X
double Control::ManualShooterAdjustment() { return xboxController->GetRawAxis(XboxAxisRightStickY); } // right joysitkc
bool Control::PresetPosition1() { return BPresetPos1->Get(xboxController->GetRawButton(XboxButtonY)); } // Y
bool Control::PresetPosition2() { return BPresetPos1->Get(xboxController->GetRawButton(XboxButtonB)); } // B
double Control::ClimberUp() { return xboxController->GetRawAxis(XboxAxisLeftTrigger); } // Left trigger
double Control::ClimberDown() { return xboxController->GetRawAxis(XboxAxisRightTrigger); }
bool Control::IntakeIn() { return (xboxController->GetPOV() == XboxDPadUp); }
bool Control::IntakeOut() { return (xboxController->GetPOV() == XboxDPadDown); }
bool Control::JustIntakeMotor() { return (xboxController->GetRawAxis(XboxAxisLeftStickY) < -0.1 || xboxController->GetRawAxis(XboxAxisLeftStickY) > 0.1); }
double Control::IntakeControl() { return xboxController->GetRawAxis(XboxAxisLeftStickY); } // y Axix left ohystikv
double Control::WheelOfFortune() { return xboxController->GetRawAxis(XboxAxisLeftStickX); } // X-axis left joyistivk
bool Control::ToggleIntake() { return BToggleIntake->Get(xboxController->GetRawButton(XboxButtonA));}
bool Control::AutoSelect() { return 0; } // left & right dpad 

Control::ButtonDebounce::ButtonDebounce() {
    latest = 0;
}
bool Control::ButtonDebounce::Get(bool input) {
    if(input) {
        if((frc::Timer::GetFPGATimestamp()-latest) > 0.2) {
            latest = frc::Timer::GetFPGATimestamp();
            return true;
        }
    }
    return false;
}