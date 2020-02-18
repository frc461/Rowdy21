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
#define ENCODER_INCH 111
#define AUTONOMOUS_LENGTH 50

class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;

private:
    DriveTrain* driveTrain;
    Control *control;
    Intake *intake;
    Limelight *limelight;
    Shooter *shooter;
    Conveyor *conveyor;
    Climber *climber;

    PID *autoPIDLeft, *autoPIDRight;
    int completeness;
};
