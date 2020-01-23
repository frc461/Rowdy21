#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>
///Sendable.h>

#include "CanStuff.h"
#include "XboxJoystickMap.h"

#include "PID.h"

class DriveTrain {
    public:
        DriveTrain();

        void Periodic();
    private:
        WPI_TalonSRX *RMotor0;
        WPI_VictorSPX *RMotor1;

        WPI_TalonSRX *LMotor0;
        WPI_VictorSPX *LMotor1;

        frc::SpeedControllerGroup *DTLeft;
        frc::SpeedControllerGroup *DTRight;

        frc::DifferentialDrive *driveTrain;

        std::shared_ptr<NetworkTable> table;
        float tx;
        float ta;

        frc::Joystick *xbox;

        PID *forwardPID;
        PID *outputPID;

        float fDistance;

        //SmartDashboard *smartDashboard;
};