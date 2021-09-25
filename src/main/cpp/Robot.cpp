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

    climber->ClimberBrakeOn();

    drivePID = new PID(0.0005, 0.0, 0.0, "dpid");
    turnPID = new PID(0.075, 0.0, 0.0, "tpid");

    frc::SmartDashboard::PutBoolean("AUTO_VISION_TRACK", true);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
    counter = 0;
}

bool Robot::Go(int inches) {
    double l = std::min(1.0, drivePID->OutputPID(driveTrain->GetEncoderValueL(), -inches*ENCODER_INCH));
    double r = std::min(1.0, drivePID->OutputPID(driveTrain->GetEncoderValueR(), inches*ENCODER_INCH));
    driveTrain->driveTrain->TankDrive(-l,r);

    sumGo += abs(driveTrain->GetEncoderValueR());
    nGo++;
    int avg = sumGo / nGo;

    return (abs(abs(inches*ENCODER_INCH) - avg) < 100);
}

bool Robot::Turn(int degs) {
    double p = std::min(1.0, turnPID->OutputPID(driveTrain->GetAngle(), degs));
    std::cout << driveTrain->GetAngle() << " " << degs << std::endl;
    driveTrain->driveTrain->TankDrive(p, -p);

    sumTurn += abs(driveTrain->GetAngle());
    nTurn++;
    int avg = sumTurn / nTurn;

    return (abs(abs(degs) - avg) < 2);
}

void Robot::StartCounter() {
    while (!finished) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
    }
}

void Robot::AutonomousInit() {
    counterThread = std::thread(&Robot::StartCounter, this);
    counterThread.detach();

    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    counter = sumGo = nGo = sumTurn = nTurn = 0;
    shot = true;
    secondShoot = false;
    step1 = true;
    setAngle = false;
    shooterSpeed = 12000;
    
    driveTrain->EnableBreakMode();

    sCount = true;
    finished = false;
    comeBack = false;
    turnedOnce = false;
    s= true;
    reset = false;
}

//( ͡° ͜ʖ ͡°)
void Robot::AutonomousPeriodic() {
    if (!shot){
        /*if (frc::SmartDashboard::GetBoolean("AUTO_VISION_TRACK", true)) {
            std::cout << "TRACC ON" << std::endl;
            //limelight->SetLimelightLight(1);
            //limelight->LimelightAiming();
        }*/

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
                shot = sCount = true;
            }
        }
    }
    else if (shot && secondShoot) {
        finished = true;
    }
    else {
        while(!turnedOnce && driveTrain->GetAngle() < ROTATE_ANGLE){
            driveTrain->driveTrain->TankDrive(0.5,-0.5);
        }
        turnedOnce = true;
        
        if (!reset){
            intake->AutoRun();
            
            intake->SetPosition(true);
            
            driveTrain->ResetEncoders();
            reset = true;

            timer.Reset();
            timer.Start();
        }
        else if (reset && timer.Get() > 0.5 && !comeBack) {
            if (Go(-GO_DISTANCE)) {
                comeBack = true;
                driveTrain->ResetEncoders();

                timer.Reset();
                timer.Start();

                intake->IntakeOff();
                intake->SetPosition(false);
            }
        }

        if (comeBack) {
            if(Go(GO_DISTANCE) && timer.Get() > 0.5) {
                while(driveTrain->GetAngle() > 0){
                    driveTrain->driveTrain->TankDrive(-0.5,0.5);
                }
                shot = false;
                secondShoot = true;
            }
        }
    }
}

void Robot::TeleopInit() {
    climber->ClimberBrakeOff();
    driveTrain->ResetEncoders();
    driveTrain->ResetGyro();
}

void Robot::TeleopPeriodic() {
    std::cout << driveTrain->GetAngle() << std::endl;
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