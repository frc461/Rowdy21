#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
    control = new Control();

    driveTrain = new DriveTrain(control);
    intake = new Intake(control);
    shooter = new Shooter(control);
    conveyor = new Conveyor(control);

    autoPIDLeft = new PID(-0.000175, 0, 0, "autoTest_L");
    autoPIDRight = new PID(0.000175, 0, 0, "autoTest_R");
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    shooter->ZeroAlign();
    driveTrain->ResetEncoders();
    autoStart = frc::Timer::GetFPGATimestamp();
}

void Robot::DisabledInit(){
    intake->Reset();
}
//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    
    autoPIDLeft->getPIDvalues();
    autoPIDRight->getPIDvalues();
    if(frc::Timer::GetFPGATimestamp() - autoStart > 5){
        driveTrain->driveTrain->TankDrive(std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetEncoderValueL(), AUTONOMOUS_LENGTH*ENCODER_INCH)), std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetEncoderValueR(), -AUTONOMOUS_LENGTH*ENCODER_INCH)));
        shooter->Rev(0);
    }

    shooter->Rev(0.6);
    if (abs(shooter->GetAdj() - PITCH_ENCODER_IDEAL) <= 30) {
        conveyor->Lift();
    }

    if(shooter->GetAdj() < PITCH_ENCODER_IDEAL){
        shooter->SetAdj(0.8);
    }
    else{
        shooter->SetAdj(-0.8);
    }
}

void Robot::TeleopInit() {
} 

void Robot::TeleopPeriodic() {
    driveTrain->Periodic();
    intake->Periodic();
    shooter->Periodic();
    conveyor->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif