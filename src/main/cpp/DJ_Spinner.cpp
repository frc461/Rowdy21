#include "DJ_Spinner.h"

DJ_Spinner::DJ_Spinner(Control *control) {
    wheel = new frc::PWMVictorSPX(0);
    this->control = control;
}

void DJ_Spinner::Periodic() {
    if (fabs(control->WheelOfFortune()) > 0.1000000000000) {
        wheel->Set(control->WheelOfFortune()*0.5);
    }
    else {
        wheel->Set(0);
    }
}