#include "Intake.h"

Intake::Intake() {
    control = new Control();
    intakeMotor = new WPI_VictorSPX(3);
}

void Intake::Periodic() {
    if (control->IntakeIn()) {
        intakeMotor->Set(0.8);
    }
    else if (control->IntakeOut()) {
        intakeMotor->Set(-0.8);
    }
    else {
        intakeMotor->Set(0);
    }
}