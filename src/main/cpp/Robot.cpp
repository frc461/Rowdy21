#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "cameraserver/CameraServer.h"

//
//
//
//
//
//      DO      NOT     PUSH    THIS    CODE
//
//
//
//

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

    frc::SmartDashboard::PutNumber("leftPOWER", 0.0);
    frc::SmartDashboard::PutNumber("rightPOWER", 0.0);

    drivenPathStore = new DrivenPathStore();

    i = 0;
    counter = 0;

    beginStore = endStore = false;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
    driveTrain->EnableBreakMode();

    //intake->AutoInit();
    
    // 0.02 | 0.0 | 0.05 (FOR FORWARD)
    autoPIDLeft = new PID(0.04, 0.0, 0.00008, "autoTest_L");
    autoPIDRight = new PID(0.04, 0.0, 0.00008, "autoTest_R");
    // 0.0064 (LEFT) | 0.008 (RIGHT) : FORWARD
    autoPIDLeftForward = new PID(0.008, 0.0, 0.0, "autoTest_L_F");
    autoPIDRightForward = new PID(0.008, 0.0, 0.0, "autoTest_R_F");

    //frc::SmartDashboard::PutNumber("actual angle", driveTrain->GetAngle());
    //frc::SmartDashboard::PutNumber("ideal angle", 35);
    j = 0;

    driveTrain->ResetGyro();

    openFile =false;
}

void Robot::DisabledInit(){
    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();
    intake->Reset();

    counter = 0;
    beginStore = endStore = done = openFile = storeInArray = false;
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!openFile) {
        reader.open("home/lvuser/info.txt");
        openFile = true;
        startTime = clock();
    }
    
    double temp =  (clock() - startTime) / CLOCKS_PER_SEC;
    int t = (int)temp;
    if (t - lastTime > 0) {
        reader >> l >> r;
    }
    lastTime = t;
    
    double lp = std::min(autoPIDLeftForward->OutputPID(driveTrain->GetEncoderValueL(), l), 1.0);
    double rp = std::min(autoPIDRightForward->OutputPID(driveTrain->GetEncoderValueR(), r), 1.0);
    
    driveTrain->driveTrain->TankDrive(-lp,rp);
}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
}

void Robot::TeleopPeriodic() {
    // if (control->BeginStore() && !beginStore && !done) {
    //     beginStore = true;
    //     startTimer = clock();
    //     endStore = false;
    //     std::cout << "store" << std::endl;
    // }
    // if (control->EndStore() && !endStore && !done) {
    //     endStore = true;
    //     beginStore = false;
    //     std::cout << "end" << std::endl;
    // }

    // if (beginStore) {
    //     double temp =  (clock() - startTime) / CLOCKS_PER_SEC;
    //     int t = (int)temp;
    //     if (t - lastTime > 0) {
    //         drivenPathStore->Store(driveTrain->GetEncoderValueL(), driveTrain->GetEncoderValueR());
    //     }
    //     lastTime = t;
    // }
    // if (endStore) {
    //     drivenPathStore->End();
    //     endStore = false;
    //     done = true;
    // }
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