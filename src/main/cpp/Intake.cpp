#include "Intake.h"
#define INTAKE_SOLENOID_ADDRESS 0
Intake::Intake() {
    intakePush = new frc::Solenoid(INTAKE_SOLENOID_ADDRESS);
    control = new Control();
    intakeMotor = new WPI_VictorSPX(3);
    conveyor = new WPI_TalonSRX(0);
    hopper = new WPI_TalonSRX(1);
}

void Intake::Periodic() {
    if(control->IntakeExtend()){
        intakePush->Set(1);
    }
    if (control->IntakeIn()) {
        intakeMotor->Set(0.8);
    }
    else if (control->IntakeOut()) {
        intakeMotor->Set(-0.8);
    }
    else {
        intakeMotor->Set(0);
    }
    if(control->ConveyAndHopperForward()){
        conveyor->Set(1);
        hopper->Set(1);
    }
    else if(control->ConveyAndHopperReverse()){
        conveyor->Set(1);
        hopper->Set(1);
    }
}