#include "Intake.h"

#define INTAKE_SOLENOID_ADDRESS 0

Intake::Intake(Control *control) {
    intakePush = new frc::DoubleSolenoid(0, INTAKE_SOLENOID_ADDRESS, 1);
    this->control = control;
    intakeMotor = new WPI_VictorSPX(3);
    // hopper = new WPI_TalonSRX(1);

    retractionLimit = new frc::DigitalInput(0);

    switchState = prevSwitchState = 0;

    intakeMotorSpeed = 0;
}

void Intake::Periodic() {
    // switchState = control->IntakeExtend();
    // if(switchState != prevSwitchState && switchState == 1){
    //     ToggleState();
    // }
    // prevSwitchState = switchState;
    if (control->IntakeIn()){
        intakePush->Set(frc::DoubleSolenoid::Value::kForward);
        intakeMotorSpeed = 0.8;
    }
    else if (control->IntakeOut()){
        intakePush->Set(frc::DoubleSolenoid::Value::kForward);
        intakeMotorSpeed = -0.8;
    } 
    else {
        intakePush->Set(frc::DoubleSolenoid::Value::kReverse);
        if(!retractionLimit->Get()){
            intakeMotorSpeed = 0;
        }
    }

    intakeMotor->Set(intakeMotorSpeed);

    if(control->ConveyAndHopperForward()){
       // hopper->Set(1);
    }
    else if(control->ConveyAndHopperReverse()){
       // hopper->Set(-1);
    }
}

void Intake::ToggleState() {
    if (intakePush->Get() == frc::DoubleSolenoid::Value::kForward) {
        intakePush->Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else if (intakePush->Get() == frc::DoubleSolenoid::Value::kReverse) {
        intakePush->Set(frc::DoubleSolenoid::Value::kForward);
    }
    else {
        intakePush->Set(frc::DoubleSolenoid::Value::kOff);
    }
}