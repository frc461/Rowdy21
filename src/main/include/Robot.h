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
#include "DrivenPathStore.h"

#include <Math.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <fstream>

#define p1(s) std::cout << s << std::endl;
#define p2(a,b) std::cout << a << " " << b << std::endl;

#define ENCODER_INCH 54.2
#define AUTONOMOUS_LENGTH 33.77
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

    DrivenPathStore *drivenPathStore;

    PID *autoPIDLeft, *autoPIDRight;
    PID *autoPIDLeftForward, *autoPIDRightForward;
    int completeness;
    double autoStart;
    int autoDelay;
    int delayStart;
    bool autoDirection;

    int i;
    int j;

    typedef bool (Robot::*Moves)(double);
    std::vector<Moves> moves;
    std::vector<double> moveVals;

    std::clock_t start;
    bool startTimer;

    int counter;

    std::vector<std::pair<int,int>> info;

    clock_t startTime;
    int lastTime;
    bool openFile;
    bool storeInArray;
    int l, r;

    bool beginStore;
    bool endStore;
    bool done;

    std::ifstream reader;
};
