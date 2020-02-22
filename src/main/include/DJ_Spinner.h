#include <frc/PWMVictorSPX.h>

#include "Controls.h"

#include <cmath>

class DJ_Spinner
{
public:
    DJ_Spinner(Control *control);

    void Periodic();

private:
    frc::PWMVictorSPX *wheel;
    Control *control;
};