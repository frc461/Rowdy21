#include <ctre/Phoenix.h>

#include "Controls.h"

class DJ_Spinner
{
public:
    DJ_Spinner(Control *control);

    void Periodic();

private:
    WPI_VictorSPX *wheel;
    Control *control;
};