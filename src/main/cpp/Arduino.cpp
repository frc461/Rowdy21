#include "Arduino.h"

Arduino::Arduino() {
    i2c = new frc::I2C(frc::I2C::Port::kOnboard, 4);
    counter = 0;
}

Arduino::~Arduino() {}

void Arduino::SendData(uint8_t sendingData){
    counter++;
    if (counter % 20 == 0){
        i2c->Write(1, sendingData);
    }
}