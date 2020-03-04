#include "Climber.h"

Climber::Climber(Control *control) {
    this->control = control;
    //limitTop = new frc::DigitalInput(1);
    //limitDown = new frc::DigitalInput(2);
    lifter1 = new WPI_TalonSRX(7);
    lifter2 = new WPI_TalonSRX(8);
    brake = new frc::Solenoid(0);

    speed = 0.6;
}

void Climber::Periodic() {
    frc::SmartDashboard::PutBoolean("BreakStatus", brake->Get());
    if(control->ClimberUp() > 0.1 && control->ClimberDown() > 0.1){
    }
    else if(control->ClimberUp()){// && !limitTop->Get()){
        lifter1->Set(-speed);
        lifter2->Set(-speed);
    }
    else if(control->ClimberDown()){// && !limitDown->Get()){
        lifter1->Set(speed);
        lifter2->Set(speed);
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
    if (brake->Get()) {
        brake->Set(0);
    }
    else if (!brake->Get()) {
        brake->Set(1);
    }
}

void Climber::ClimberBrakeOff() {
    brake->Set(0);
}
void Climber::ClimberBrakeOn() {
    brake->Set(1);
}