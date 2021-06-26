#include "Intake.h"

#define INTAKE_SOLENOID_CHANNEL 1
#define ROLLER_PORT 11
#define LIMIT_SWITCH 2

Intake::Intake(Control *control) {
    push = new frc::Solenoid(INTAKE_SOLENOID_CHANNEL); //false is in, true is all the way out
    this->control = control;
    roller = new WPI_VictorSPX(ROLLER_PORT);

    retractionLimit = new frc::DigitalInput(LIMIT_SWITCH);

    rollerSpeed = 0;
}

void Intake::AutoRun() {
    roller->Set(0.8);
}

void Intake::Periodic() {
    rollerSpeed = (fabs(control->IntakeControl()) > 0.2) ? 0.8 : 0.0;

    if (control->IntakeMotorIn()){
        push->Set(1);
    }
    else if (control->IntakeMotorOut()){ 
        push->Set(0);
    }

    roller->Set(rollerSpeed);
}