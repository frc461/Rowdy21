#include "DJ_Spinner.h"

DJ_Spinner::DJ_Spinner(Control *control) {
    wheel = new frc::PWMVictorSPX(0);
    this->control = control;
}

void DJ_Spinner::Periodic() {
    if (abs(control->WheelOfFortune()) > 0.05) {
        wheel->Set(control->WheelOfFortune());
    }
    else {
        wheel->Set(0);
    }
}