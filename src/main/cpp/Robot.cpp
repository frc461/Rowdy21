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

    drivePID = new PID(0.0003, 0.0, 0.0, "lmao ok");
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
    counter = 0;
}

void Robot::Go(int inches) {
    double l = std::min(1.0, drivePID->OutputPID(driveTrain->GetEncoderValueL(), -inches*ENCODER_INCH));
    double r = std::min(1.0, drivePID->OutputPID(driveTrain->GetEncoderValueR(), inches*ENCODER_INCH));
    //std::cout << l << " " << r << std::endl;
    //std::cout << driveTrain->GetEncoderValueL() << " " << driveTrain->GetEncoderValueR() << std::endl;
    driveTrain->driveTrain->TankDrive(-l,r);
}

void Robot::StartCounter() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
    }
}

void Robot::AutonomousInit() {
    counterThread = std::thread(&Robot::StartCounter, this);
    counterThread.detach();

    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    counter = 0;
    shot = false;
    step1 = true;
    setAngle = false;
    shooterSpeed = 12000;

    sCount = true;
    s= true;
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!shot) {
        limelight->SetLimelightLight(1);
        limelight->LimelightAiming();

        if (step1) {
            shooter->tilt->ZeroAlign();
            if (sCount) startCount = counter; 
            sCount = false;

            if (counter - startCount == 1) {
                step1 = false;
                sCount = false;
            }
        }
        else {
            if (!setAngle) encVal = shooter->tilt->GetEncoder();
            setAngle = true;

            if (shooter->tilt->GetEncoder() < encVal+720) shooter->tilt->RunSafe(0.7);
            else shooter->tilt->RunSafe(0.0);

            shooter->RunAtVelocity(shooterSpeed);

            if (sCount) startCount = counter; 
            sCount = false;
            int passed = counter - startCount;
            if (passed >= 4 && passed <= 6) {
                conveyor->Up();
            }
            else if (passed > 6) {
                conveyor->No();
                shooter->RunAtVelocity(0);
                shot = true;
            }
        }
    }
    else {
        Go(55);
    }
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