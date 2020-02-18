#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
    control = new Control();

    driveTrain = new DriveTrain(control);
    intake = new Intake(control);
    limelight = new Limelight(control, driveTrain);
    shooter = new Shooter(control);
    conveyor = new Conveyor(control);
    climber = new Climber(control);

    autoPIDLeft = new PID(-0.000125, 0, 0, "autoTest_L");
    autoPIDRight = new PID(0.000125, 0, 0, "autoTest_R");
    completeness = 0;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    shooter->ZeroAlign();
    driveTrain->ResetEncoders();
}

void Robot::AutonomousPeriodic() {
    if (driveTrain->GetEncoderValueL() >= -AUTONOMOUS_LENGTH*ENCODER_INCH) {
        driveTrain->driveTrain->TankDrive(std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetEncoderValueL(), -AUTONOMOUS_LENGTH*ENCODER_INCH)), std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetEncoderValueR(), AUTONOMOUS_LENGTH*ENCODER_INCH)));
       /* if(driveTrain->GetEncoderValueL() <= -AUTONOMOUS_LENGTH*ENCODER_INCH){
            completeness = 1;
        }
        std::cout<<completeness<<std::endl;*/
      /*  if(completeness = 1){
            driveTrain->driveTrain->TankDrive(std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetEncoderValueL()*-1, -AUTONOMOUS_LENGTH*ENCODER_INCH)), std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetEncoderValueR(), AUTONOMOUS_LENGTH*ENCODER_INCH)));
        }*/
    } else {
        driveTrain->driveTrain->TankDrive(0, 0);
    }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    driveTrain->Periodic();
    intake->Periodic();
    limelight->Periodic();
    shooter->Periodic();
    conveyor->Periodic();
    climber->Periodic();
    // driveTrain->SetDriveMode(DriveTrain::DriveMode::Arcade);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif