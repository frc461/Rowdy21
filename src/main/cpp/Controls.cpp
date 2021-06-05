#include "Controls.h"

Control::Control() {
    leftJoystick = new frc::Joystick(2);
    rightJoystick = new frc::Joystick(3);
    xboxController = new frc::Joystick(1);

    BToggleIntake = new Control::ButtonDebounce();
    BPresetPos1 = new Control::ButtonDebounce();
    BPresetPos2 = new Control::ButtonDebounce();
    BPresetPos3 = new Control::ButtonDebounce();
    BClimberBrake = new Control::ButtonDebounce();
}

double Control::leftJoystickX() { return leftJoystick->GetRawAxis(xAxisJS); } //doesn't need to be changed; ready
double Control::leftJoystickY() { return leftJoystick->GetRawAxis(yAxisJS); } //doesn't need to be changed; ready
double Control::rightJoystickX() { return rightJoystick->GetRawAxis(xAxisJS); } //doesn't need to be changed; ready
double Control::rightJoystickY() { return rightJoystick->GetRawAxis(yAxisJS); } //doesn't need to be changed; ready

bool Control::LimelightAiming() { return rightJoystick->GetRawButton(8); } //I have no idea if these need to be changed or not... William?
bool Control::LimelightLightActivate() { return rightJoystick->GetRawButton(9); } //I have no idea if these need to be changed or not... William?

bool Control::ShooterLoadUp() { return xboxController->GetRawAxis(XboxAxisRightTrigger) > 0.2; } //might need to be changed later; ready
bool Control::ConveyForward() { return xboxController->GetRawAxis(XboxAxisLeftTrigger) > 0.2; } //might need to be changed later; ready
bool Control::ConveyReverse() { return xboxController->GetPOV() == XboxDPadDown; } //might need to be changed later; ready

double Control::ManualShooterAdjustment() { return xboxController->GetRawAxis(XboxAxisRightStickY); } //ready
bool Control::PresetPosition1() { return BPresetPos1->Get(xboxController->GetRawButton(XboxButtonY)); } //high position; ready
bool Control::PresetPosition2() { return BPresetPos2->Get(xboxController->GetRawButton(XboxButtonX)); } //mid position; ready
bool Control::PresetPosition3() { return BPresetPos3->Get(xboxController->GetRawButton(XboxButtonA)); } //low position; ready
bool Control::ShooterReset() { return xboxController->GetRawButton(XboxButtonB); } //re-zero; ready

double Control::ClimberUp() { return xboxController->GetRawAxis(xboxController->GetRawAxis(XboxAxisLeftStickY)) < -0.2; } //now on operator; ready
double Control::ClimberDown() { return xboxController->GetRawAxis(xboxController->GetRawAxis(XboxAxisLeftStickY)) > 0.2; } //now on operator; ready
bool Control::ClimberBrake() { return BClimberBrake->Get(xboxController->GetRawButton(XboxButtonBack)); } //doesn't need to be changed; ready

//re-written
// bool Control::IntakeIn() { return (xboxController->GetPOV() == XboxDPadUp); }
// bool Control::IntakeOut() { return (xboxController->GetPOV() == XboxDPadDown); }
// bool Control::JustIntakeMotor() { return (xboxController->GetRawAxis(XboxAxisLeftStickY) < -0.1 || xboxController->GetRawAxis(XboxAxisLeftStickY) > 0.1); }
// bool Control::ToggleIntake() { return BToggleIntake->Get(xboxController->GetRawButton(XboxButtonA));} //needs to be changed

bool Control::IntakeIn() { return xboxController->GetRawButton(XboxButtonRightBumper); } //puts roller out and runs intake; ready
bool Control::IntakeOut() { return xboxController->GetRawButton(XboxButtonLeftBumper); } //pulls roller in and runs intake; ready
// bool Control::JustIntakeMotor() {  } //just intake motor; if this is important then fill it out yourself!


// double Control::WheelOfFortune() {  } //if this is important then fill it out yourself! X-axis left joystick
// bool Control::AutoSelect() { return 0; } //if this is important then fill it out yourself! left & right dpad 

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