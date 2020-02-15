#include "Intake.h"

#define INTAKE_SOLENOID_CHANNEL 1
#define ROLLER_PORT 11
#define LIMIT_SWITCH 2

Intake::Intake(Control *control) {
    push = new frc::Solenoid(INTAKE_SOLENOID_CHANNEL);
    this->control = control;
    roller = new WPI_VictorSPX(ROLLER_PORT);

    retractionLimit = new frc::DigitalInput(LIMIT_SWITCH);

    rollerSpeed = 0;
    bIntake = false;
}

void Intake::Periodic() {
    if (control->IntakeIn()){
        rollerSpeed = -0.8;
    }
    else if (control->IntakeOut()){
        rollerSpeed = 0.8;
    }
    else if (!bIntake && retractionLimit->Get()){
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
    if (!push->Get()) {
        push->Set(1);
    }
    else if (push->Get()) {
        push->Set(0);
    }
    else {
        push->Set(0);
    }
}