#include "Controls.h"

Control::Control() {
    leftJoystick = new frc::Joystick(2);
    rightJoystick = new frc::Joystick(3);
}

double Control::leftJoystickX() { return leftJoystick->GetRawAxis(xAxisJS); }
double Control::leftJoystickY() { return leftJoystick->GetRawAxis(yAxisJS); }
double Control::rightJoystickX() { return rightJoystick->GetRawAxis(xAxisJS); }
double Control::rightJoystickY() { return rightJoystick->GetRawAxis(yAxisJS); }

bool Control::IntakeIn() { return leftJoystick->GetRawButton(rightButton); }
bool Control::IntakeOut() { return leftJoystick->GetRawButton(rightButton); }
bool Control::IntakeForward() { return leftJoystick->GetRawButton(thumbSwitch); }

bool Control::LimelightAiming() { return rightJoystick->GetRawButton(8); }
bool Control::LimelightLightActivate() { return rightJoystick->GetRawButton(9); }