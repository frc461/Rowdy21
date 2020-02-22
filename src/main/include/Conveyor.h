#include "CanStuff.h"
#include "Controls.h"

#include <iostream>
#include <ctre/Phoenix.h>

#define TOWER_MOTOR1 10
#define TOWER_MOTOR2 13
#define HOPPER_MOTOR 9

class Conveyor {
    public: 
        Conveyor(Control *control);
        ~Conveyor();

        void Periodic();
        
        void Lift();
    private:
        Control *control;
        WPI_VictorSPX *hopper;
        WPI_VictorSPX *tower, *tower2;
};