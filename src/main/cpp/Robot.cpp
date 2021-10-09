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

    drivePID = new PID(0.001, 0.0, 0.0, "dpid");
    turnPID = new PID(0.15, 0.0, 0.0, "tpid");

    frc::SmartDashboard::PutBoolean("AUTO_VISION_TRACK", true);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
    counter = 0;
}

bool Robot::Go(int inches, int dir) {
    double l = std::min(0.6, drivePID->OutputPID(abs(driveTrain->GetEncoderValueL()), inches*ENCODER_INCH));
    double r = std::min(0.6, drivePID->OutputPID(abs(driveTrain->GetEncoderValueR()), inches*ENCODER_INCH));
    driveTrain->driveTrain->TankDrive(dir*l,dir*r);
    
    if (abs(driveTrain->GetEncoderValueR()) >= inches*ENCODER_INCH) goCrossed = true;

    if (goCrossed) {
        sumGo += abs(driveTrain->GetEncoderValueR());
        nGo++;
        goAvg = sumGo / nGo;
    }
    //std::cout << goAvg << " " << abs(inches*ENCODER_INCH) << std::endl;
    return (abs(abs(inches*ENCODER_INCH) - goAvg) < 100);
}

bool Robot::Turn(double degs, int dir) {
    double p = std::min(0.6, turnPID->OutputPID(fabs(driveTrain->GetAngle()), fabs(degs)));
    driveTrain->driveTrain->TankDrive(dir*p, -dir*p);

    if (fabs(driveTrain->GetAngle()) > fabs(degs)) turnCrossed = true;

    if (turnCrossed) {
        sumTurn += fabs(driveTrain->GetAngle());
        nTurn++;
        turnAvg = sumTurn / nTurn;
    }
    //std::cout<<abs(degs)<<" "<< turnAvg << std::endl;
    return (abs(abs(degs) - turnAvg) < 3);
}

void Robot::StartCounter() {
    while (!finished) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        counter++;
    }
}

void Robot::AutonomousInit() {
    //timer = new frc::Timer();
    counterThread = std::thread(&Robot::StartCounter, this);
    driveTrain->ResetGyro();
    driveTrain->ResetEncoders();

    counter = sumGo = nGo = sumTurn = nTurn = goAvg = turnAvg = 0;
    goCrossed = turnCrossed = false;
    shot = true;
    secondShoot = false;
    step1 = true;
    setAngle = false;
    shooterSpeed = 10000;
    
    driveTrain->EnableBreakMode();

    turned = false;
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
            step1 = false;
        }
        else {
            if (!setAngle) encVal = shooter->tilt->GetEncoder();
            setAngle = true;

            if (shooter->tilt->GetEncoder() < encVal+720) shooter->tilt->RunSafe(0.7);
            else shooter->tilt->RunSafe(0.0);

            shooter->RunAtVelocity(shooterSpeed);

            if (sCount) startCount = counter; 
            sCount = false;
            if (counter-startCount >= 3 && counter-startCount <= 5) {
                conveyor->Up();
            }
            else if (counter-startCount > 5) {
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
        if (!Turn(ROTATE_ANGLE,1)) {}
        else turned = true; 

        if (!reset && !turned){
            //intake->AutoRun();
            //intake->SetPosition(true);
            
            driveTrain->ResetEncoders();

            startCount = counter;
            finished = true;
            reset = true;
        }
        else if (reset && counter-startCount >= 1 && !comeBack) {
            if (Go(GO_DISTANCE,-1)) {
                driveTrain->ResetEncoders();
                driveTrain->ResetGyro();

                nGo = sumGo = 0;
                nTurn = sumTurn = 0;
                turnAvg = goAvg = 0;
                turnCrossed = goCrossed = false;

                //intake->IntakeOff();
                //intake->SetPosition(false);

                startCount = counter;
                comeBack = true;
            }
        }

        if (comeBack) {
            if (counter - startCount >= 2) {
                if(Go(GO_DISTANCE,1)) {
                    std::cout << "idawfi"; //Turn(ROTATE_ANGLE, -1) << std::endl;
                    // if (Turn(-ROTATE_ANGLE)) {
                    //     shot = false;
                    //     secondShoot = true;
                    //     finished = true;
                    // }
                }
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
    //std::cout << driveTrain->GetAngle() << std::endl;
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