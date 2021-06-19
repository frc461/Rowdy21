#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "cameraserver/CameraServer.h"

void Robot::RobotInit() {
    control = new Control();

    driveTrain = new DriveTrain(control);
    intake = new Intake(control);
    limelight = new Limelight(control, driveTrain);
    shooter = new Shooter(control);
    conveyor = new Conveyor(control);
    climber = new Climber(control);
    djSpinner = new DJ_Spinner(control);
    //arduino = new Arduino();

    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    climber->ClimberBrakeOff();

    frc::SmartDashboard::PutNumber("leftPOWER", 0.0);
    frc::SmartDashboard::PutNumber("rightPOWER", 0.0);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    driveTrain->EnableBreakMode();
    
    // 0.02 | 0.0 | 0.05 (FOR FORWARD)
    autoPIDLeft = new PID(0.04, 0.0, 0.00008, "autoTest_L");
    autoPIDRight = new PID(0.04, 0.0, 0.00008, "autoTest_R");
    autoPIDLeftForward = new PID(0.008, 0.0, 0.0, "autoTest_L_F");
    autoPIDRightForward = new PID(0.008, 0.0, 0.0, "autoTest_R_F");
}

void Robot::DisabledInit(){
    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
}

void Robot::TeleopPeriodic() {
    driveTrain->Periodic();
    intake->Periodic();
    limelight->Periodic();
    shooter->Periodic();
    conveyor->Periodic();
    climber->Periodic();
    djSpinner->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif