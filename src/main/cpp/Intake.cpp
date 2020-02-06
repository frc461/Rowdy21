#include "Intake.h"

#define INTAKE_SOLENOID_ADDRESS 0

Intake::Intake(Control *control) {
    intakePush = new frc::DoubleSolenoid(0, INTAKE_SOLENOID_ADDRESS, 1);
    this->control = control;
    intakeMotor = new WPI_VictorSPX(3);
    // conveyor = new WPI_TalonSRX(7);
    // hopper = new WPI_TalonSRX(1);

    retractionLimit = new frc::DigitalInput(0);

    switchState = prevSwitchState = 0;
}

void Intake::Periodic() {
    // switchState = control->IntakeExtend();
    // if(switchState != prevSwitchState && switchState == 1){
    //     std::cout<<switchState<<"\n";
    //     ToggleState();
    // }
    // prevSwitchState = switchState;
    // }else {
    //     intakePush->Set(frc::DoubleSolenoid::Value::kReverse);
    // }
    if (control->IntakeIn()){
        intakeMotor->Set(0.8);
        intakePush->Set(frc::DoubleSolenoid::Value::kForward);
    }
    else {
        intakePush->Set(frc::DoubleSolenoid::Value::kReverse);
        if (!retractionLimit->Get()) {
            intakeMotor->Set(0);
        }
        else {
            intakeMotor->Set(0); // Fix to keep running
        }
    }

    if (control->IntakeOut()){
        intakeMotor->Set(-0.8);
        intakePush->Set(frc::DoubleSolenoid::Value::kForward);
    } else {
        intakePush->Set(frc::DoubleSolenoid::Value::kReverse);
        if(!retractionLimit->Get()){
            intakeMotor->Set(0);
        } else {
            intakeMotor->Set(0); // Fix to keep running
        }
    }
    

    if(control->ConveyAndHopperForward()){
       // conveyor->Set(1);
       // hopper->Set(1);
    }
    else if(control->ConveyAndHopperReverse()){
       // conveyor->Set(1);
       // hopper->Set(1);
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