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
bool Control::ConveyReverse() { return xboxController->GetRawButton(XboxButtonBack); } //might need to be changed later; ready

double Control::ManualShooterAdjustment() { return xboxController->GetRawAxis(XboxAxisRightStickY); } //ready
bool Control::PresetPosition1() { return BPresetPos1->Get(xboxController->GetRawButton(XboxButtonY)); } //high position; ready
bool Control::PresetPosition2() { return BPresetPos2->Get(xboxController->GetRawButton(XboxButtonX)); } //mid position; ready
bool Control::PresetPosition3() { return BPresetPos3->Get(xboxController->GetRawButton(XboxButtonA)); } //low position; ready
bool Control::ShooterReset() { return xboxController->GetRawButton(XboxButtonB); } //re-zero; ready

double Control::ClimberUp() { return rightJoystick->GetRawButton(thumbSwitch); } //all on driver (because that is a GREAT idea); ready
double Control::ClimberDown() { return leftJoystick->GetRawButton(thumbSwitch); } //all on driver (because that is a GREAT idea); ready
bool Control::ClimberBrake() { return BClimberBrake->Get(leftJoystick->GetRawButton(flipOffTop)); } //all on driver (I guess it was supposed to be?); ready

// bool Control::IntakeIn() { return xboxController->GetPOV(XboxDPadDown); } //puts roller out and runs intake; ready
// bool Control::IntakeOut() { return xboxController->GetPOV(XboxDPadUp); } //pulls roller in and runs intake; ready
bool Control::IntakeMotorIn() { return xboxController->GetRawButton(XboxButtonLeftBumper); } 
bool Control::IntakeMotorOut() { return xboxController->GetRawButton(XboxButtonRightBumper); }
double Control::IntakeControl() { return xboxController->GetRawAxis(XboxAxisLeftStickY); }

double Control::WheelOfFortune() { return xboxController->GetRawAxis(XboxAxisRightStickX); } //this is needed for the rest of the code... so it isn't important and just returns something
bool Control::AutoSelect() { return false; } //this is needed for the rest of the code... so it isn't important and just returns something

bool Control::BeginStore() { return rightJoystick->GetRawButton(3); }
bool Control::EndStore() { return rightJoystick->GetRawButton(4); }

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