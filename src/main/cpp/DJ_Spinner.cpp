#include "DJ_Spinner.h"

DJ_Spinner::DJ_Spinner(Control *control) {
    wheel = new WPI_VictorSPX(0);
    this->control = control;
}

void DJ_Spinner::Periodic() {
    wheel->Set(control->WheelOfFortune());
}