#include <frc/I2C.h>

#include <iostream>
#include <vector>

#define ON_NO_COM 0x06
#define ON_AND_COM 0x07
#define AUTO 0x08
#define TELEOP 0x09
#define COLOR 0x0A
#define SPIN_THE_WHEEL 0x0B
#define FLY_WHEEL 0x0C
#define SHOOTING 0x0D
#define LOW_VOLT 0x0E
#define OVER_CURRENT 0x0F
#define LOW_PRESSURE 0x10
#define CLIMB 0x11
#define PARTY 0x12
#define LIME_LIGHT 0x13
#define INTAKE_OUT 0x14
#define INTAKE_IN 0x15

class Arduino
{
public:
    Arduino();
    ~Arduino();

    void SendData(uint8_t sendingData);

private:
    frc::I2C *i2c;
    
    std::vector<uint8_t> dataBeingSent = {0};

    int counter;
};