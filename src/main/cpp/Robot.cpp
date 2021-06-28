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

    step1 = true;
    setAngle = false;
}

void Robot::Go(bool dir, int inches) {
    double l = drivePID->OutputPID(driveTrain->GetEncoderValueL(), inches*ENCODER_INCH * ((dir) ? -1 : 1));
    double r = drivePID->OutputPID(driveTrain->GetEncoderValueR(), inches*ENCODER_INCH * ((dir) ? 1 : -1));
    driveTrain->driveTrain->TankDrive(l,r);
}

int Robot::StartCounter() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    counter++;
    std::cout << counter << std::endl;
    return counter;
}

void Robot::AutonomousInit() {
    drivePID = new PID(0.005, 0.0, 0.0, "lmao ok");

    counterThread = std::thread(&Robot::StartCounter, this);
    counterThread.detach();

    counter = 0;
    step1 = true;
    setAngle = false;
    shooterSpeed = 12000;
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!shot) {
        limelight->SetLimelightLight(1);
        limelight->LimelightAiming();

        if (step1) {
            shooter->tilt->ZeroAlign();
            counter = 0;
            step1 = false;
        }
        else {
            if (!setAngle) shooter->tilt->SetAngle(653);
            shooter->RunAtVelocity(shooterSpeed);

            int passed = StartCounter();
            if (passed >= 2 && passed <= 4) {
                conveyor->Up();
                setAngle = true;
            }
            else if (passed > 4) {
                conveyor->No();
                shooterSpeed = 0;
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