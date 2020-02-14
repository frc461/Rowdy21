#include "Conveyor.h"

Conveyor::Conveyor(Control *control){
    tower = new WPI_VictorSPX(TOWER_MOTOR);
    hopper = new WPI_VictorSPX(HOPPER_MOTOR);
    this->control = control;
    deBounce = 0;
}
void Conveyor::Periodic(){
        if(control->ConveyForward()){
            deBounce = 0;
            hopper->Set(-1);
            tower->Set(1);
        }
        else if(control->ConveyReverse()){
            deBounce = 0;
            hopper->Set(1);
            tower->Set(-1);
        }
        else{
            deBounce++;
            if(deBounce > 10){
                deBounce = 0;
                hopper->Set(0);
                tower->Set(0);
            }
        }
}