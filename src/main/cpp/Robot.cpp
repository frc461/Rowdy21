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
    //0.00023
    //0.00064
    autoPIDLeft = new PID(0.012, 0, 0, "autoTest_L");
    autoPIDRight = new PID(0.0025, 0, 0, "autoTest_R");

    autoPIDRightForward = new PID(0.00064, 0, 0, "autoTest_R_F");
    autoPIDLeftForward = new PID(0.00064, 0, 0, "autoTest_L_F");

    gyroInitReading = driveTrain->GetAngle();
    driveTrain->ResetGyro();

    climber->ClimberBrakeOff();
    autoDirection = 0;
    frc::SmartDashboard::PutNumber("auto delay", autoDelay);
    frc::SmartDashboard::PutBoolean("Front/Back Auto", autoDirection);

    driveTrain->ResetEncoders();
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    autoDelay = frc::SmartDashboard::GetNumber("auto delay", autoDelay);
    //dont fkng move
    delayStart = frc::Timer::GetFPGATimestamp();
    while(frc::Timer::GetFPGATimestamp() - delayStart < autoDelay){
        //do absolutley nothing  
    }
    //driveTrain->EnableBreakMode();

    driveTrain->ResetGyro();

    shooter->tilt->ZeroAlign();
    driveTrain->ResetEncoders();
    autoStart = frc::Timer::GetFPGATimestamp();
    limelight->LimelightReset();
}

void Robot::DisabledInit(){
    intake->Reset();
}
//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    //arduino->SendData(AUTO);
    // autoPIDLeft->getPIDvalues();
    // autoPIDRight->getPIDvalues();
    // if(frc::Timer::GetFPGATimestamp() - autoStart < 5){
    //     //limelight->AutoLimelight();
    //     shooter->RunAtVelocity(13000);
    //     std::cout << fabs((shooter->tilt->GetPotVal() - shooter->tilt->baseVal)) << std::endl;
    //     if (fabs((shooter->tilt->GetPotVal() - shooter->tilt->baseVal) - PITCH_POT_IDEAL) <= 0.01) {
    //         conveyor->Lift();
    //         shooter->tilt->RunSafe(0);
    //     }
    //     /*if(shooter->tilt->GetPotVal() < PITCH_POT_IDEAL){
    //         shooter->tilt->SetAngle(PITCH_POT_IDEAL);
    //     }*/
    //     else {
    //         shooter->tilt->SetAngle(PITCH_POT_IDEAL);
    //     }
    // }
    // else if(frc::Timer::GetFPGATimestamp() - autoStart > 5) {
    //     double targetLeft;
    //     double targetRight;
    //     if(frc::SmartDashboard::GetBoolean("Front/Back Auto", autoDirection)) {
    //         targetLeft = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetEncoderValueL(), AUTONOMOUS_LENGTH*ENCODER_INCH));
    //         targetRight = std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetEncoderValueR(), -AUTONOMOUS_LENGTH*ENCODER_INCH));
    //     } else {
    //         targetLeft = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetEncoderValueL(), -AUTONOMOUS_LENGTH*ENCODER_INCH));
    //         targetRight = std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetEncoderValueR(), AUTONOMOUS_LENGTH*ENCODER_INCH));
    //     }
    //     driveTrain->driveTrain->TankDrive(targetLeft, targetRight);
    //     //std::cout << "Right Target" << targetRight << std::endl;
    //     shooter->RunAtVelocity(0);
    //     //limelight->LimelightReset();
    //     conveyor->Stop(); 
    // }
    /*if(driveTrain->GetAngle()<90){
        //std::cout << driveTrain->GetAngle() << std::endl;
        double left = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetAngle(), 90.0));
        std::cout << left << std::endl;
        driveTrain->driveTrain->TankDrive(left, -left);
    }*/
    //RunForward(30); // FIX!!!!!!!!!!!!!!!!!!
    TurnLeft(90);
}

void Robot::RunForward(double numInch) {
    //double left = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetAngle(), gyroInitReading));
    //double right = std::min(1.0, autoPIDRight->OutputPID(driveTrain->GetAngle(), gyroInitReading));
    //double leftSpeed = std::min(1.0, autoPIDLeftForward->OutputPID(driveTrain->GetEncoderValueL(), numInch*ENCODER_INCH));
    //double rightSpeed = std::min(1.0, autoPIDRightForward->OutputPID(driveTrain->GetEncoderValueR(), -numInch*ENCODER_INCH));
    if (driveTrain->GetEncoderValueL() > -numInch*ENCODER_INCH) {
        if (driveTrain->GetEncoderValueL() <=  -numInch*ENCODER_INCH*0.9) driveTrain->EnableBreakMode();
        else driveTrain->DisableBreakMode();
        driveTrain->driveTrain->TankDrive(0.5, 0.5);
    }
    std::cout << driveTrain->GetAngle() << std::endl;
}
void Robot::TurnRight(double degrees) {
    if(driveTrain->GetAngle() < degrees){
        double left = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetAngle(), degrees));
        driveTrain->driveTrain->TankDrive(left, -left);
    }
}
void Robot::TurnLeft(double degrees) {
    if (driveTrain->GetAngle() > -degrees) {
        double left = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetAngle(), -degrees));
        driveTrain->driveTrain->TankDrive(left, -left);
    }
}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
} 

void Robot::TeleopPeriodic() {
    arduino->SendData(TELEOP);
    driveTrain->Periodic();
    //std::cout << driveTrain->GetEncoderValueL() << " " << driveTrain->GetEncoderValueR() << std::endl;
    intake->Periodic();
    limelight->Periodic();
    shooter->Periodic();
    conveyor->Periodic();
    climber->Periodic();
    djSpinner->Periodic();
    std::cout << driveTrain->GetAngle() << std::endl;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif