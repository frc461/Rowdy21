#include "CanStuff.h"
#include "Controls.h"

#include <iostream>
#include <ctre/Phoenix.h>

#define TOWER_MOTOR 10
#define HOPPER_MOTOR 9

class Conveyor {
    public: 
        Conveyor(Control *control);
        ~Conveyor();

        void Periodic();
        
        void Lift();

        void Stop();
    private:
        Control *control;
        WPI_VictorSPX *hopper;
        WPI_VictorSPX *tower;
};