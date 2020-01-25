#include <frc/WPILib.h>

#include <iostream>
#include <vector>

class Arduino
{
public:
    Arduino();
    ~Arduino();

    enum colorState {
        red,
        blue,
        green, 
        yellow,
        something
    };

    Arduino::colorState getColor();

    void SendData(uint8_t sendingData);

private:
    frc::I2C *i2c;

    uint8_t colorData[1] = {0x00};
    std::vector<uint8_t> dataBeingSent = {0};

    int counter;
    int counter2;
};