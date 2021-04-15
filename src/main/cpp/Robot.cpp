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
    autoDirection = 0;
    frc::SmartDashboard::PutNumber("auto delay", autoDelay);
    frc::SmartDashboard::PutBoolean("Front/Back Auto", autoDirection);

    compareImg = new CompareImg();
    runComp = true;
    startGetImage = false;
    
    i = 0;
    counter = camCnt = 0;
    store = false;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    driveTrain->EnableBreakMode();

    intake->AutoInit();
    
    // 0.02 | 0.0 | 0.05 (FOR FORWARD)
    autoPIDLeft = new PID(0.04, 0.0, 0.00008, "autoTest_L");
    autoPIDRight = new PID(0.04, 0.0, 0.00008, "autoTest_R");
    // 0.0064 (LEFT) | 0.008 (RIGHT) : FORWARD
    autoPIDLeftForward = new PID(0.004, 0.0, 0.0, "autoTest_L_F");
    autoPIDRightForward = new PID(1.0, 0.0, 0.0, "autoTest_R_F");

    //frc::SmartDashboard::PutNumber("actual angle", driveTrain->GetAngle());
    //frc::SmartDashboard::PutNumber("ideal angle", 35);
    
    //list = new AutoInfo(2);

    driveTrain->ResetGyro();
}

void Robot::DisabledInit(){
    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();
    intake->Reset();

    counter = camCnt = 0;
    runComp = true;
    store = false;
    startGetImage = false;
    compareImg->ResetImage();
    compareImg->SetImageGrabbed(false);
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!startGetImage) {
        // compareImg->StartPutImage();
        compareImg->StartGetImage();
        startGetImage = true;
    }
    if (runComp && compareImg->GetImageGrabbed()) {
        int n = compareImg->Compare();
        std::cout << n << std::endl;
        list = new AutoInfo(n);
        runComp = false;
    }
    if (!runComp) camCnt++;
    if (!store && !runComp && camCnt >= 30) {
        for (int j = 0; j < (int)list->list.size(); j++) {
            if (list->list.at(j)->angle > 0) {
                bool dir = list->list.at(j)->dir;
                moves.push_back((!dir) ? &Robot::TurnLeft : &Robot::TurnRight);
                moveVals.push_back(list->list.at(j)->angle);
            }
            moves.push_back(&Robot::RunForward);
            moveVals.push_back(list->list.at(j)->distance / 2.54);
            std::cout << moveVals.at(j) << std::endl;
        }
        store = true;
    }
    if (store) {
        intake->AutoRun();
        if (i == (int)moveVals.size() - 1) intake->IntakeIn();
        if ((this->*moves.at(i))(moveVals.at(i))) {
            driveTrain->ResetEncoders();
            driveTrain->ResetGyro();

            counter = 0;
            i++;
        }
    }
    std::cout << "A" << std::endl;
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
    //arduino->SendData(TELEOP);
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


