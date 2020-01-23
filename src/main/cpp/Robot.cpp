#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
    driveTrain = new DriveTrain();
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    driveTrain->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
