#include "Arduino.h"

Arduino::Arduino() {
    i2c = new frc::I2C(frc::I2C::Port::kOnboard, 4);
    counter = 0;
}

Arduino::~Arduino() {}

Arduino::colorState Arduino::getColor() {
    counter++;
    colorState color;

    if (counter % 20 == 0)
        i2c->Transaction(0, 0, colorData, 1);

    if (colorData[0] == ARD_RED) {
        color = colorState::red;
    }
    else if (colorData[0] == ARD_BLUE) {
        color = colorState::blue;
    }
    else if (colorData[0] == ARD_GREEN) {
        color = colorState::green;
    }
    else if (colorData[0] == ARD_YELLOW) {
        color = colorState::yellow;
    }
    return color;
}

void Arduino::SendData(uint8_t sendingData){
    counter++;
    if (counter % 20 == 0){
        i2c->Write(1, sendingData);
    }
}