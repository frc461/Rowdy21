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

    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    climber->ClimberBrakeOff();
    autoDirection = 0;
    frc::SmartDashboard::PutNumber("auto delay", autoDelay);
    frc::SmartDashboard::PutBoolean("Front/Back Auto", autoDirection);

    list = new AutoInfo();

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
    driveTrain->EnableBreakMode();

    shooter->tilt->ZeroAlign();

    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    autoStart = frc::Timer::GetFPGATimestamp();
    limelight->LimelightReset();

    intake->AutoInit();

    // 0.02 | 0.0 | 0.05 (FOR FORWARD)
    autoPIDLeft = new PID(0.04, 0.0, 0.00008, "autoTest_L");
    autoPIDRight = new PID(0.04, 0.0, 0.00008, "autoTest_R");
    // 0.0064 (LEFT) | 0.008 (RIGHT) : FORWARD
    autoPIDLeftForward = new PID(0.004, 0.0, 0.0, "autoTest_L_F");
    autoPIDRightForward = new PID(1.0, 0.0, 0.0, "autoTest_R_F");

    frc::SmartDashboard::PutNumber("actual angle", driveTrain->GetAngle());
    frc::SmartDashboard::PutNumber("ideal angle", 35);

    for (int j = 0; j < (int)list->list.size(); j++) {
        if (list->list.at(j)->angle > 0) {
            bool dir = list->list.at(j)->dir;
            moves.push_back((!dir) ? &Robot::TurnLeft : &Robot::TurnRight);
            moveVals.push_back(list->list.at(j)->angle);
        }
        moves.push_back(&Robot::RunForward);
        moveVals.push_back(list->list.at(j)->distance / 2.54);
    }
    i = 0;
    counter = 0;
}

void Robot::DisabledInit(){
    intake->Reset();
}
//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    intake->AutoRun();
    if (i == moveVals.size() - 1) intake->IntakeIn();
    if ((this->*moves.at(i))(moveVals.at(i))) {
        driveTrain->ResetEncoders();
        driveTrain->ResetGyro();

        counter = 0;
        i++;
    }

    //RunForward(100);

    std::cout << driveTrain->GetAngle() << std::endl;

    //frc::SmartDashboard::PutNumber("actual angle", driveTrain->GetAngle());
    //frc::SmartDashboard::PutNumber("ideal angle", 90);
    //frc::SmartDashboard::PutNumber("time", frc::Timer::GetFPGATimestamp());
}

bool Robot::RunForward(double numInch) {
    if (driveTrain->GetEncoderValueL() < numInch*ENCODER_INCH) {
        double left = std::min(1.0, autoPIDLeftForward->OutputPID(driveTrain->GetEncoderValueL(), numInch*ENCODER_INCH));
        double right = std::min(1.0, autoPIDRightForward->OutputPID(driveTrain->GetEncoderValueR(), numInch*ENCODER_INCH));
        double val = (driveTrain->GetEncoderValueL() > numInch*ENCODER_INCH*0.9) ? 0 : 0.05;
        if (driveTrain->GetAngle() < 0) driveTrain->driveTrain->TankDrive(-left*0.6, -right*0.6 - val);
        else driveTrain->driveTrain->TankDrive(-left*0.6 - val, -right*0.6);
        return 0;
    }
    else {
        return 1;
    }
}
bool Robot::TurnRight(double degrees) {
    counter++;
    if(counter <= 50){
        double left = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetAngle(), degrees));
        driveTrain->driveTrain->TankDrive(left, -left);
        return 0;
    }
    else {
        return 1;
    }
}
bool Robot::TurnLeft(double degrees) {
    counter++;
    if (counter <= 50) {
        double left = std::min(1.0, autoPIDLeft->OutputPID(driveTrain->GetAngle(), -degrees));
        driveTrain->driveTrain->TankDrive(left, -left);
        return 0;
    }
    else {
        return 1;
    }
}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
} 

void Robot::TeleopPeriodic() {
    arduino->SendData(TELEOP);
    driveTrain->Periodic();
    std::cout << driveTrain->GetEncoderValueL() << " " << driveTrain->GetEncoderValueR() << std::endl;
    intake->Periodic();
    limelight->Periodic();
    shooter->Periodic();
    conveyor->Periodic();
    climber->Periodic();
    djSpinner->Periodic();
    //std::cout << driveTrain->GetAngle() << std::endl;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif


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
    //RunForward(30);
    //TurnLeft(90);