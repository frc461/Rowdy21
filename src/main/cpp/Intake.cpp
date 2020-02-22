#include "Intake.h"

#define INTAKE_SOLENOID_CHANNEL 1
#define ROLLER_PORT 30
#define LIMIT_SWITCH 0

Intake::Intake(Control *control) {
    push = new frc::DoubleSolenoid(0, 1);
    this->control = control;
    roller = new WPI_VictorSPX(ROLLER_PORT);

    retractionLimit = new frc::DigitalInput(LIMIT_SWITCH);

    rollerSpeed = 0;
    bIntake = false;
}

void Intake::Periodic() {
    if (control->ConveyForward()) {
        rollerSpeed = -0.8;
    }
    else if (control->IntakeIn()){
        rollerSpeed = 0.8;
    }
    else if (control->IntakeOut()){
        rollerSpeed = -0.8;
    }
    else {
        rollerSpeed = 0;
    }

    if(control->ToggleIntake()){
        ToggleState();
    }
    roller->Set(rollerSpeed);
}

void Intake::ToggleState() {
    bIntake = !bIntake;
    if (push->Get() == frc::DoubleSolenoid::Value::kReverse) { 
        push->Set(frc::DoubleSolenoid::Value::kForward);
    }
    else if (push->Get() == frc::DoubleSolenoid::Value::kForward) {
        push->Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else {
        push->Set(frc::DoubleSolenoid::Value::kReverse);
    }
}

void Intake::Reset(){
    bIntake = false;
    push->Set(frc::DoubleSolenoid::Value::kReverse);
}