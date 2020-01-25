#include <frc/WPILib.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Joystick.h>
#include <ctre/Phoenix.h>
#include <cmath>

#include <frc/SmartDashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/smartdashboard/Sendable.h>

#include "CanStuff.h"
#include "ThrustMasters.h"

#include "PID.h"

#include <iostream>

class DriveTrain {
public:
    DriveTrain();

    void Periodic();
private:
    WPI_VictorSPX *right2, *left2;
    WPI_TalonSRX *right1, *left1;
    WPI_VictorSPX *intakeMotor;

    frc::SpeedControllerGroup *left;
    frc::SpeedControllerGroup *right;

    frc::DifferentialDrive *driveTrain;

    frc::Joystick *leftJoystick;
    frc::Joystick *rightJoystick;

    nt::NetworkTableEntry leftSide;
    nt::NetworkTableEntry rightSide;
    nt::NetworkTableEntry ntTick;
    std::shared_ptr<nt::NetworkTable> table;

    frc::SmartDashboard *smartDashboard;

    int tick;

    bool tankDrive, arcadeDrive;
    float tx;
    float ta;

    PID *forwardPID;
    PID *outputPID;

    float fDistance;
};