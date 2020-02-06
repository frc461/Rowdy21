#include "Controls.h"

Control::Control() {
    leftJoystick = new frc::Joystick(2);
    rightJoystick = new frc::Joystick(3);
    xboxController = new frc::Joystick(1);
}

double Control::leftJoystickX() { return leftJoystick->GetRawAxis(xAxisJS); }
double Control::leftJoystickY() { return leftJoystick->GetRawAxis(yAxisJS); }
double Control::rightJoystickX() { return rightJoystick->GetRawAxis(xAxisJS); }
double Control::rightJoystickY() { return rightJoystick->GetRawAxis(yAxisJS); }

bool Control::LimelightAiming() { return rightJoystick->GetRawButton(8); }
bool Control::LimelightLightActivate() { return rightJoystick->GetRawButton(9); }

bool Control::ShooterLoadUp() { return xboxController->GetRawButton(XboxButtonRightBumper); } // right bumper
bool Control::ConveyAndHopperForward() { return xboxController->GetRawButton(XboxButtonLeftBumper); } // Left bumper
bool Control::ConveyAndHopperReverse() { return xboxController->GetRawButton(XboxButtonX); } // X
double Control::ManualShooterAdjustment() { return xboxController->GetRawAxis(XboxAxisRightStickY); } // right joysitkc
bool Control::PresetPosition1() { return xboxController->GetRawButton(XboxButtonY); } // Y
bool Control::PresetPosition2() { return xboxController->GetRawButton(XboxButtonB); } // B
double Control::ClimberUp() { return xboxController->GetRawAxis(XboxAxisLeftTrigger); } // Left trigger
double Control::ClimberDown() { return xboxController->GetRawAxis(XboxAxisRightTrigger); } // A
bool Control::IntakeIn() { return (xboxController->GetPOV() >= XboxDPadUp) ? 1 : 0; }
bool Control::IntakeOut() { return (xboxController->GetPOV() >= XboxDPadDown) ? 1 : 0; }//willium likes pp
double Control::IntakeControl() { return xboxController->GetRawAxis(XboxAxisLeftStickY); } // y Axix left ohystikv
double Control::WheelOfFortune() { return xboxController->GetRawAxis(XboxAxisLeftStickX); } // X-axis left joyistivk
bool Control::AutoSelect() { return 0; } // left & right dpad 