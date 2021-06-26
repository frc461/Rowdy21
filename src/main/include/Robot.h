#pragma once

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
#include "DrivenPathStore.h"

#include <vector>
#include <string>
#include <ctime>

#define ENCODER_INCH 54.2
#define PITCH_ENCODER_IDEAL 820
/*
    Here is the autonomous preset value!!!
*/
#define PITCH_POT_IDEAL 0.305

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

    void Go(bool dir, int inches);

    int StartCounter();

private:
    DriveTrain *driveTrain;
    Control *control;
    Intake *intake;
    Limelight *limelight;
    Shooter *shooter;
    Conveyor *conveyor;
    Climber *climber;
    DJ_Spinner *djSpinner;
    //Arduino *arduino;

    PID *drivePID;

    bool shot;
    bool step1;
    bool setAngle;

    int counter;
    
    std::thread counterThread;
};
