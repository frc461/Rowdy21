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
#include "DJ_Spinner.h"
#include "PID.h"
#include "Arduino.h"
#include <Math.h>

#define ENCODER_INCH 111.0
#define AUTONOMOUS_LENGTH 36.0
#define PITCH_ENCODER_IDEAL 820
#define PITCH_POT_IDEAL 0.31

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
    Limelight *limelight;
    Shooter *shooter;
    Conveyor *conveyor;
    Climber *climber;
    DJ_Spinner *djSpinner;
    Arduino *arduino;

    PID *autoPIDLeft, *autoPIDRight;
    int completeness;
    double autoStart;
    int autoDelay;
    int delayStart;
};
