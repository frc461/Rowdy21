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

#define ROTATE_ANGLE 18
#define GO_DISTANCE 70
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

    bool Go(int inches);
    bool Turn(int degs);

    void StartCounter();

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

    PID *drivePID, *turnPID;

    bool shot;
    bool step1;
    bool setAngle;
    int shooterSpeed;
    int encVal;

    int counter;
    
    bool sCount;
    int startCount;

    bool s;
    bool finished;
    
    std::thread counterThread;
    frc::Timer timer;
    bool reset;

    bool turnedOnce;
    bool comeBack;

    int sumGo, nGo;
    int sumTurn, nTurn;
    bool secondShoot;
};
