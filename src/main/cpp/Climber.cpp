#include "Climber.h"

Climber::Climber(Control *control) {
    this->control = control;
    //limitTop = new frc::DigitalInput(1);
    //limitDown = new frc::DigitalInput(2);
    lifter1 = new WPI_TalonSRX(7);
    lifter2 = new WPI_TalonSRX(8);
    brake = new frc::DoubleSolenoid(0, 1);
}

void Climber::Periodic() {
    if(control->ClimberUp() > 0.1 && control->ClimberDown() > 0.1){
    }
    else if(control->ClimberUp() > 0.1){// && !limitTop->Get()){
        lifter1->Set(-control->ClimberUp());
        lifter2->Set(-control->ClimberUp());
    }
    else if(control->ClimberDown() > 0.1){// && !limitDown->Get()){
        lifter1->Set(control->ClimberDown());
        lifter2->Set(control->ClimberDown());
    }
    else {
        lifter1->Set(0);
        lifter2->Set(0);
    }

    if (control->ClimberBrake()) {
        ToggleBrake();
    }
}

void Climber::ToggleBrake() {
    if (brake->Get() == frc::DoubleSolenoid::Value::kReverse) {
        brake->Set(frc::DoubleSolenoid::Value::kForward);
    }
    else if (brake->Get() == frc::DoubleSolenoid::Value::kForward) {
        brake->Set(frc::DoubleSolenoid::Value::kReverse);
    }
}

void Climber::ClimberBrakeOff() {
    brake->Set(frc::DoubleSolenoid::Value::kOff);
}
void Climber::ClimberBrakeOn() {
    brake->Set(frc::DoubleSolenoid::Value::kForward);
}