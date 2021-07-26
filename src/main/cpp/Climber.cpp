#include "Climber.h"

Climber::Climber(Control *control) {
    this->control = control;
    limitTop = new frc::DigitalInput(3);
    limitDown = new frc::DigitalInput(4);
    lifter1 = new WPI_TalonSRX(7);
    lifter2 = new WPI_TalonSRX(8);
    brake = new frc::Solenoid(0);

    speed = 0.6;

    enter = hold = true;
    up = down = false;

    counter = 0;
}

void Climber::Periodic() {
    frc::SmartDashboard::PutBoolean("BreakStatus", brake->Get());

    // if (control->ClimberUp() || control->ClimberDown()) {
    //     if (enter) {
    //         brake->Set(1);
    //         enter = false;
    //         hold = true;
    //     }
    // }
    // else {
    //     if (hold) {
    //         brake->Set(0);
    //         hold = false;
    //         enter = true;
    //     }
    // }
    
    if(control->ClimberUp()){// && limitTop->Get()){
        if (counter > 5) {
            lifter1->Set(-speed*0.5);
            lifter2->Set(-speed*0.5);
        } else counter++;

        if (enter) {
            brake->Set(1);
            enter = false;
            hold = true;
        }
    }
    else if(control->ClimberDown()){
        if (counter > 5) {
            lifter1->Set(speed);
            lifter2->Set(speed);
        } else counter++;

        if (enter) {
            brake->Set(1);
            enter = false;
            hold = true;
        }
    }
    else {
        lifter1->Set(0);
        lifter2->Set(0);

        if (hold) {
            brake->Set(0);
            hold = false;
            enter = true;
        }
        counter = 0;
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