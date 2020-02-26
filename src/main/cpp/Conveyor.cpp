#include "Conveyor.h"

Conveyor::Conveyor(Control *control){
    this->control = control;
    tower = new WPI_VictorSPX(TOWER_MOTOR);
    hopper = new WPI_VictorSPX(HOPPER_MOTOR);
}
void Conveyor::Lift(){
    tower->Set(1);
}
void Conveyor::Periodic(){
    if(control->ConveyForward()){
        hopper->Set(-1);
        tower->Set(1);
    }
    else if(control->ConveyReverse()){
        hopper->Set(1);
        tower->Set(-1);
    }
    else{
        hopper->Set(0);
        tower->Set(0);
    }
}

void Conveyor::Stop(){
    hopper->Set(0);
    tower->Set(0);
}