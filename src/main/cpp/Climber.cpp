#include "Climber.h"

Climber::Climber(Control *control) {
    this->control = control;
    limitTop = new frc::DigitalInput(1);
    limitDown = new frc::DigitalInput(2);
    // lifter1 = new WPI_TalonSRX(0);
    // lifter2 = new WPI_TalonSRX(1);
}
void Climber::Periodic() {
    
    /* if(control->ClimberUp() >0 && control->ClimberDown() >0){} 
     else if(control->ClimberUp() > 0 && !limitTop->Get()){
         lifter1->Set(-control->ClimberUp());
         lifter2->Set(control->ClimberUp());
     }
     else if(control->ClimberDown() > 0 && !limitDown->Get()){
         lifter1->Set(-control->ClimberDown());
         lifter2->Set(control->ClimberDown());
     }
     */
}