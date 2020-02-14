#include "Intake.h"

#define INTAKE_SOLENOID_CHANNEL 1
#define ROLLER_PORT 11
#define LIMIT_SWITCH 2
Intake::Intake(Control *control) {
    // push = new frc::DoubleSolenoid(0, INTAKE_SOLENOID_ADDRESS, 1);
    push = new frc::Solenoid(INTAKE_SOLENOID_CHANNEL);
    this->control = control;
    roller = new WPI_VictorSPX(ROLLER_PORT);
    // hopper = new WPI_TalonSRX(1);

    retractionLimit = new frc::DigitalInput(LIMIT_SWITCH);

    switchState = prevSwitchState = 0;

    rollerSpeed = 0;
    timeOut = 0;
}

void Intake::Periodic() {
    // switchState = control->IntakeExtend();
    // if(switchState != prevSwitchState && switchState == 1){
    //     ToggleState();
    // }
    // prevSwitchState = switchState;
    if (control->IntakeIn()){
        timeOut = 0;
        // push->Set(1);
        rollerSpeed = -0.8;
    }
    else if (control->IntakeOut()){
        timeOut = 0;
        // push->Set(1);
        rollerSpeed = 0.8;
    } 
    else{
        timeOut++;
        if(timeOut > 10){
            // push->Set(0);
        }
    }

    std::cout << control->ToggleIntake() << std::endl;
    

    if(control->ToggleIntake()){
        ToggleState();
    }

    if(!retractionLimit->Get()){
        rollerSpeed = 0;
    }
    roller->Set(rollerSpeed);

    /*
    if(control->ConveyAndHopperForward()){
       hopper->Set(1);
       convey->Set(1);
    }
    else if(control->ConveyAndHopperReverse()){
       hopper->Set(-1);
       convey->Set(-1);
    }
    */
}

void Intake::ToggleState() {
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