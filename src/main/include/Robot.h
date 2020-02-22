#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <iostream>
#include <algorithm>

#include "networkTables/NetworkTableInstance.h"
#include "networktables/NetworkTable.h"
#include "networkTables/NetworkTableEntry.h"

#include "DriveTrain.h"
#include "Intake.h"
#include "Limelight.h"
#include "Shooter.h"
#include "Conveyor.h"
#include "Climber.h"
#include "PID.h"
#include <Math.h>

#define ENCODER_INCH 111.0
#define AUTONOMOUS_LENGTH 14.0
#define PITCH_ENCODER_IDEAL 900

class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    void DisabledInit() override;

private:
    DriveTrain* driveTrain;
    Control *control;
    Intake *intake;
    Shooter *shooter;
    Conveyor *conveyor;

    PID *autoPIDLeft, *autoPIDRight;
    int completeness;
    double autoStart;
};
