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
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();
}

void Robot::Go(bool dir, int inches) {
    int dis = inches*ENCODER_INCH;
    dis *= (dir) ? 1 : -1;
    double l = drivePID->OutputPID(driveTrain->GetEncoderValueL(), dis);
    double r = drivePID->OutputPID(driveTrain->GetEncoderValueR(), dis);
    driveTrain->driveTrain->TankDrive(l,r);
}

int Robot::StartCounter() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter++;
    std::cout << "wow" << std::endl;
    return counter;
}

void Robot::AutonomousInit() {
    drivePID = new PID(0.005, 0.0, 0.0, "lmao ok");

    counterThread = std::thread(&Robot::StartCounter, this);

    counter = 0;
    step1 = true;
    setAngle = false;
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!shot) {
        limelight->SetLimelightLight(1);
        limelight->LimelightAiming();

        if (step1) {
            shooter->tilt->ZeroAlign();
            step1 = false;
            counter = 0;
        }
        else {
            if (!setAngle) shooter->tilt->SetAngle(653);
            shooter->RunAtVelocity(12000);

            int passed = StartCounter();
            if (passed >= 2 && passed <= 5) {
                conveyor->Up();
                setAngle = true;
            }
            else if (passed > 5) {
                conveyor->No();
                shot = true;
            }
        }
    }
    else {
        Go(false, 40);
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