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
    djSpinner = new DJ_Spinner(control);
    arduino = new Arduino();

    autoPIDLeft = new PID(-0.0003, 0, 0, "autoTest_L");
    autoPIDRight = new PID(0.0003 , 0, 0, "autoTest_R");

    climber->ClimberBrakeOff();
    frc::SmartDashboard::PutNumber("auto( ͡° ͜ʖ ͡°)delay", autoDelay);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    autoDelay = frc::SmartDashboard::GetNumber("auto( ͡° ͜ʖ ͡°)delay", autoDelay);
    //dont fkng move
    delayStart = frc::Timer::GetFPGATimestamp();
    while(frc::Timer::GetFPGATimestamp() - delayStart < autoDelay){
        //do absolutley nothing  
    }
    // shooter->ZeroAlign();
    driveTrain->ResetEncoders();
    autoStart = frc::Timer::GetFPGATimestamp();
    limelight->LimelightReset();
}

void Robot::DisabledInit(){
    intake->Reset();
}
//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    arduino->SendData(AUTO);
    autoPIDLeft->getPIDvalues();
    autoPIDRight->getPIDvalues();
    if(frc::Timer::GetFPGATimestamp() - autoStart < 5){
        limelight->AutoLimelight();
        // shooter->Rev(0.6);
        if (abs(shooter->tilt->GetEncoder() - PITCH_ENCODER_IDEAL) <= 30) {
            // conveyor->Lift();
        }
        if(shooter->tilt->GetEncoder() < PITCH_ENCODER_IDEAL){
            // shooter->SetAdj(0.8);
        } 
        else {
            // shooter->SetAdj(-0.8);
        }
    }
    else if(frc::Timer::GetFPGATimestamp() - autoStart > 5) {
        double targetLeft = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetEncoderValueL(), AUTONOMOUS_LENGTH*ENCODER_INCH));
        double targetRight = std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetEncoderValueR(), -AUTONOMOUS_LENGTH*ENCODER_INCH));
        driveTrain->driveTrain->TankDrive(targetLeft, targetRight);
        //std::cout << "Right Target" << targetRight << std::endl;
        // shooter->Rev(0);
        limelight->LimelightReset();
        conveyor->Stop();
    }
}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
} 

void Robot::TeleopPeriodic() {
    arduino->SendData(TELEOP);
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