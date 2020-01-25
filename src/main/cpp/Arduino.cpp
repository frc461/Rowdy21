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

    if (colorData[0] == 0x01) {
        color = colorState::red;
    }
    else if (colorData[0] == 0x02) {
        color = colorState::blue;
    }
    else if (colorData[0] == 0x03) {
        color = colorState::green;
    }
    else if (colorData[0] == 0x04) {
        color = colorState::yellow;
    }
    return color;
}

void Arduino::SendData(uint8_t sendingData){
    counter2++;
    dataBeingSent.clear();
    dataBeingSent.push_back(sendingData);
    if(counter2 %20 == 0){
    i2c->Write (4, dataBeingSent[0]);
    }
    else {
        //this is useless
    }

}