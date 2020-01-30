#include <frc/WPILib.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <ctre/Phoenix.h>
#include <cmath>

#include <frc/SmartDashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/smartdashboard/Sendable.h>

#include "CanStuff.h"
#include "ThrustMasters.h"

#include "Controls.h"

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

    nt::NetworkTableEntry leftSide;
    nt::NetworkTableEntry rightSide;
    nt::NetworkTableEntry ntTick;
    std::shared_ptr<nt::NetworkTable> table;

    frc::SmartDashboard *smartDashboard;

    Control *control;

    int tick;

    bool intakeForeward;
    float tx;
    float ta;

    PID *forwardPID;
    PID *outputPID;

    float fDistance;
    double throttleCap;
    bool driveMode;

};