#pragma once

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
#include "Intake.h"

#include "PID.h"

#include <iostream>

class DriveTrain {
public:
    DriveTrain(Control *control);

    enum DriveMode {
        Tank,
        Arcade,
        Disabled
    };

    void ToggleDriveMode();
    void SetDriveMode(DriveMode mode);
    void ToggleDirection();

    void Periodic();

    DriveMode driveMode;

    frc::DifferentialDrive *driveTrain;

private:
    WPI_VictorSPX *right2, *left2;
    WPI_TalonSRX *right1, *left1;

    frc::SpeedControllerGroup *left;
    frc::SpeedControllerGroup *right;

    nt::NetworkTableEntry leftSide;
    nt::NetworkTableEntry rightSide;
    nt::NetworkTableEntry ntTick;

    frc::SmartDashboard *smartDashboard;

    Intake *intake;

    Control *control;
    bool switchState;
    bool prevSwitchState;
    int tick;

    bool intakeForeward;

    float fDistance;
    double throttleCap;
    int direction;
};