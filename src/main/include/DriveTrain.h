#pragma once

#define DTR1 3
#define DTR2 4

#define DTL1 1
#define DTL2 2

#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <ctre/Phoenix.h>
#include <cmath>

#include <frc/ADXRS450_Gyro.h>

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

    void EnableBreakMode();
    void DisableBreakMode();

    void ToggleDriveMode();
    void SetDriveMode(DriveMode mode);
    void ToggleDirection();

    void ResetEncoders();

    void ResetGyro();
    double GetAngle();

    double GetEncoderValueL();
    double GetEncoderValueR();

    void Periodic();
    void AutonomousPeriodic(int movenum);

    DriveMode driveMode;

    frc::DifferentialDrive *driveTrain;

private:
    WPI_TalonSRX *right2, *left2;
    WPI_TalonSRX *right1, *left1;

    frc::ADXRS450_Gyro *gyro;

    frc::SpeedControllerGroup *left;
    frc::SpeedControllerGroup *right;

    nt::NetworkTableEntry leftSide;
    nt::NetworkTableEntry rightSide;
    nt::NetworkTableEntry ntTick;

    frc::SmartDashboard *smartDashboard;

    PID *autoPIDLeft, *autoPIDRight;

    Control *control;
    bool switchState;
    bool prevSwitchState;
    int tick;

    bool intakeForeward;

    float fDistance;
    double throttleCap;
    int direction;
};